(() => {
    document.querySelectorAll('.post-md img').forEach((image) => {
        let link = image.closest('a');
        if (!link) {
            const source = image.getAttribute('src');
            if (!source) return;
            link = document.createElement('a');
            link.setAttribute('href', source);
            image.replaceWith(link);
            link.append(image);
        }
        link.target = '_blank';
        link.relList.add('noopener', 'noreferrer');
    });
})();
