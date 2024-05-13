<!--
 * @Author: Lili Liang
 * @Date: 2024-05-13 15:50:54
 * @LastEditors: Lili Liang
 * @LastEditTime: 2024-05-13 22:10:50
 * @Description: Please set description
-->
## Timeline
- **2019 年 05 月**：Hello World，站点正式部署上线

- **2019 年 07 月**：更换第 1 版主题：[Matery](https://github.com/blinkfox/hexo-theme-matery)

- **2020 年 04 月 02 日**：更新第 2 版皮肤：[Chic](https://github.com/Siricee/hexo-theme-Chic)，并正式启用个人博客

- **2020 年 04 月 03 日**：
    - 优化 `About` 页面
    - 解决 `Permalink` 问题
      - 采用的是设计 `urlname` 方式
      - 之前采取的是`中文链接转拼音`方式：[hexo-permalink-pinyin](https://github.com/viko16/hexo-permalink-pinyin) 插件
      - 也可使用 [hexo-abbrlink](https://github.com/rozbo/hexo-abbrlink) 插件生成非中文的链接

- **2020 年 04 月 04 日**：
    - 添加站点运行时间
    - 增加博文评论功能：[Valine](https://valine.js.org/) && [LeanCloud](https://www.leancloud.cn/)
    - 应用站点流量分析工具：[百度统计](https://tongji.baidu.com)
    - 增加文章字数及阅读时长统计

- **2020 年 04 月 06 日**：提交百度搜索引擎收录，参考 [博客](https://leungll.site/2020/04/06/hexo-blog-seo/)
  
- **2020 年 05 月 05 日**：使用 [Github](https://github.com/leungll/ImgHosting) && [jsDelivr](https://github.com/Molunerfinn/picgo/releases) && [PicGo](https://github.com/Molunerfinn/picgo/releases) 搭建个人CDN

- **2021 年 01 月 28 日**：添加 `RSS` 订阅：[Github](https://leungll.site/atom.xml)

- **2021 年 05 月 14 日**：配置新域名：`.site`

- **2024 年 04 月 27 日**：更换第 3 版主题：[ZenMind](https://github.com/LenChou95/hexo-theme-ZenMind)
  - 优化博客样式
  - 处理 Mathjax 渲染失效问题，参考 [博客](https://www.jianshu.com/p/e8d433a2c5b7)
  - 重新设计 About 页面
  - 对域名：<https://leungll.site>，配置谷歌收录、谷歌站长工具、百度收录、百度站长工具
  - 重新搭建个人 CDN

## 注意事项
- [CDN仓库](https://github.com/leungll/MyImgHosting) 不可改成私有，否则图床的图片全部不可见
- 对于 ZenMind 配置的 Mathjax，如果 `hexo clean && hexo g` 导致代码高亮不生效，重新执行命令

## TODO
- ~~提交百度搜索引擎收录~~
- ~~插件中有一个脚本放在了 [unpkg](https://unpkg.com/valine@1.3.10/dist/Valine.min.js) 上，有时连接会迟缓，需要优化一下~~
- ~~用 Github && jsDelivr && PicGo 搭图床，另外 [imgchr](https://imgchr.com/) 也能满足需求~~
- ~~用 jsDelivr && Github 搭一个CDN，优化站点加载速度~~
- ~~添加 `RSS` 订阅~~  
- 新增博文修改时间记录
- 用 [hexo-git-backup](https://github.com/coneycode/hexo-git-backup) 进行博客备份
- 启用博客评论：[Valine](https://valine.js.org/)
- 解决手机端适配问题
- etc.