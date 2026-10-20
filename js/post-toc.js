(() => {
    'use strict';

    const layout = document.querySelector('[data-post-layout]');
    const toc = document.querySelector('[data-post-toc]');
    const content = layout && layout.querySelector('.post-md');
    if (!toc || !content) return;

    const headings = Array.from(content.querySelectorAll('h1, h2, h3, h4, h5, h6'))
        .filter(heading => heading.textContent.trim());
    if (headings.length < 2) return;

    const panel = toc.querySelector('details');
    const summary = toc.querySelector('summary');
    const nav = toc.querySelector('nav');
    const list = toc.querySelector('.post-toc-list');
    const current = toc.querySelector('.post-toc-current');
    const desktop = window.matchMedia('(min-width: 1180px)');
    const reduceMotion = window.matchMedia('(prefers-reduced-motion: reduce)');
    const usedIds = new Set();
    const branches = [];
    const links = [];

    headings.forEach((heading, index) => {
        // Some Hexo renderers put the permalink on a span inside the heading.
        let id = heading.id || (heading.querySelector('[id]') || {}).id;
        if (!id || usedIds.has(id)) {
            const stem = heading.textContent.trim().toLowerCase()
                .replace(/[^\p{L}\p{N}]+/gu, '-').replace(/^-|-$/g, '') || 'section';
            id = stem;
            let suffix = 2;
            while (document.getElementById(id) || usedIds.has(id)) id = `${stem}-${suffix++}`;
            heading.id = id;
        }
        usedIds.add(id);
        const level = Number(heading.tagName.slice(1));
        while (branches.length && branches[branches.length - 1].level >= level) branches.pop();
        let parent = list;
        if (branches.length) {
            const item = branches[branches.length - 1].item;
            parent = item.querySelector(':scope > ol');
            if (!parent) {
                parent = document.createElement('ol');
                item.appendChild(parent);
            }
        }
        const item = document.createElement('li');
        const link = document.createElement('a');
        link.href = `#${encodeURIComponent(id)}`;
        link.textContent = heading.textContent.trim();
        item.appendChild(link);
        parent.appendChild(item);
        branches.push({ level, item });
        links.push(link);

        link.addEventListener('click', event => {
            // Preserve normal new-tab and modified-link behavior.
            if (event.button || event.metaKey || event.ctrlKey || event.shiftKey || event.altKey) return;
            event.preventDefault();
            if (!desktop.matches) panel.open = false;
            if (location.hash !== link.hash) history.pushState(history.state, '', link.hash);
            heading.setAttribute('tabindex', '-1');
            heading.focus({ preventScroll: true });
            heading.scrollIntoView({ behavior: reduceMotion.matches ? 'instant' : 'smooth', block: 'start' });
        });
    });

    toc.hidden = false;
    layout.classList.add('has-toc');
    document.body.classList.add('has-post-toc');
    const syncPanel = () => {
        panel.open = desktop.matches;
        summary.tabIndex = desktop.matches ? -1 : 0;
    };
    syncPanel();
    desktop.addEventListener('change', syncPanel);
    summary.addEventListener('click', event => {
        if (desktop.matches) event.preventDefault();
    });

    let active = -1;
    let offsets = [];
    let pending = false;
    let needsMeasure = true;
    const update = () => {
        pending = false;
        if (desktop.matches) {
            const available = window.innerHeight - Math.max(32, toc.getBoundingClientRect().top)
                - summary.offsetHeight - 24;
            toc.style.setProperty('--toc-available-height', `${Math.max(160, available)}px`);
        } else {
            toc.style.removeProperty('--toc-available-height');
        }
        const measured = needsMeasure;
        if (needsMeasure) {
            offsets = headings.map(heading => heading.getBoundingClientRect().top + window.scrollY);
            needsMeasure = false;
        }
        // Include rounding tolerance around the 100px anchor offset.
        const threshold = window.scrollY + Math.max(102, desktop.matches ? 0 : summary.offsetHeight + 48);
        let next = 0;
        for (let i = 0; i < offsets.length && offsets[i] <= threshold; i++) next = i;
        if (window.scrollY > 0 && window.innerHeight + window.scrollY >= document.documentElement.scrollHeight - 4) {
            next = headings.length - 1;
        }
        if (next === active && !measured) return;
        if (active >= 0) {
            links[active].classList.remove('is-active');
            links[active].removeAttribute('aria-current');
        }
        active = next;
        const link = links[active];
        link.classList.add('is-active');
        link.setAttribute('aria-current', 'location');
        current.textContent = link.textContent;
        // Scroll the TOC itself, never the article. Leave manual exploration alone.
        if (panel.open && !toc.matches(':hover, :focus-within')) {
            const itemBounds = link.getBoundingClientRect();
            const navBounds = nav.getBoundingClientRect();
            if (itemBounds.top < navBounds.top + 12) nav.scrollTop += itemBounds.top - navBounds.top - 12;
            else if (itemBounds.bottom > navBounds.bottom - 12) nav.scrollTop += itemBounds.bottom - navBounds.bottom + 12;
        }
    };
    const schedule = (measure = false) => {
        if (measure) needsMeasure = true;
        if (!pending) {
            pending = true;
            requestAnimationFrame(update);
        }
    };
    panel.addEventListener('toggle', () => schedule(true));
    window.addEventListener('scroll', () => schedule(), { passive: true });
    window.addEventListener('resize', () => schedule(true), { passive: true });
    window.addEventListener('load', () => schedule(true), { once: true });
    if ('ResizeObserver' in window) new ResizeObserver(() => schedule(true)).observe(content);
    if (document.fonts) document.fonts.ready.then(() => schedule(true));
    schedule(true);
})();
