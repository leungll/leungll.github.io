<!--
 * @Author: Lili Liang
 * @Date: 2024-06-21 23:29:12
 * @LastEditors: leungll l.liang0316@gmail.com
 * @LastEditTime: 2025-01-04 23:12:09
 * @Description: Please set description
-->
## Timeline
- **May, 2019**: Hello world, the site was deployed and online.

- **Jul, 2019**: Changed the 1st version theme: [Matery](https://github.com/blinkfox/hexo-theme-matery) .

- **Apr 2, 2020**: Changed the 2nd version theme: [Chic](https://github.com/Siricee/hexo-theme-Chic) , and officially launched my personal blog.

- **Apr 3, 2020**：
    - Optimized `About` page.
    - Solved `Permalink` problem.
      - The design `urlname` method was adopted.
      - The previous method was `Chinese links to pinyin`: [hexo-permalink-pinyin](https://github.com/viko16/hexo-permalink-pinyin) plugin.
      - You can also consider using [hexo-abbrlink](https://github.com/rozbo/hexo-abbrlink) plugin to generate non-Chinese links.

- **Apr 4, 2020**：
    - Added site uptime.
    - Added blog comment function: [Valine](https://valine.js.org/) && [LeanCloud](https://www.leancloud.cn/) .
    - Applied site traffic analysis tools: [Baidu Tongji](https://tongji.baidu.com) .
    - Added article word count and reading time statistics.

- **Apr 6, 2020**：Submitted to the Baidu search engine for inclusion, you can refer to the [blog](https://leungll.site/2020/04/06/hexo-blog-seo/) .
  
- **May 5, 2020**：Used [Github](https://github.com/leungll/ImgHosting) && [jsDelivr](https://github.com/Molunerfinn/picgo/releases) && [PicGo](https://github.com/Molunerfinn/picgo/releases) to build a personal CDN.

- **Jan 28, 2021**：Added `RSS` subscription: <https://leungll.site/atom.xml> .

- **May 14, 2021**：Configured new domain name: `.site` .

- **Apr 27, 2024**：Changed the 3rd version theme: [ZenMind](https://github.com/LenChou95/hexo-theme-ZenMind) .
  - Optimized blog style.
  - Dealed with [Mathjax](https://www.mathjax.org/) rendering failure problem, you can refer to the [blog](https://www.jianshu.com/p/e8d433a2c5b7) .
  - Redesigned `About` page.
  - For domain name: <https://leungll.site>, configured [Google  Search Console](https://search.google.com/search-console/about) && [Google Analytics](https://developers.google.com/analytics/learn) && [Baidu Inclusion](https://ziyuan.baidu.com/dashboard) && [Baidu Tongji](https://tongji.baidu.com) .
  - Rebuilded personal CDN.

- **Jun 06, 2024**: Added blog mirror source: [Vercel](https://vercel.com), resolve Baidu crawler to domain name: <https://l2liang.site>.

- **Jan 01, 2025**: Solve the issue of article directory jump, use plugin: `hexo-toc`.

- **Jan 05, 2025**: Added article update time record.

## Notice
- The [CDN repo](https://github.com/leungll/MyImgHosting) cannot be changed to private，otherwise all the images on the image bed will be invisible.
- For the [MathJax](https://www.mathjax.org) configured in the [ZenMind](https://github.com/LenChou95/hexo-theme-ZenMind), if `hexo clean && hexo g` causes the code highlighting to not take effect, you can re-execute the command.
- If you want to change the theme of the blog, you need to reconfigure the Google, Bing and Baidu SEO verification in the new theme.

## TODO
- [x] To submit to the Baidu search engine for inclusion.
- [x] There is a script in the plugin which is placed on [unpkg](https://unpkg.com/valine@1.3.10/dist/Valine.min.js). Sometimes the connection is slow and needs to be optimized.
- [x] To use Github && jsDelivr && PicGo to build a image bed. Addtionally, the [imgchr](https://imgchr.com/) can also meet the needs.
- [x] To use jsDelivr && Github to build a CDN, which can optimize the site loading speed.
- [x] To add `RSS` subscription.
- [x] To solve Baidu crawler problem.
- [x] Solve the jump problem of directories with symbols and spaces.
- [x] To add article update time record.
- [ ] To use [hexo-git-backup](https://github.com/coneycode/hexo-git-backup) for blog backup.
- [ ] To enable blog comment: [Valine](https://valine.js.org/) .
