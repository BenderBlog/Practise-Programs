# 西电健康卡脚本
## 如何执行(Windows)
1. 下载python：请去python.org下载，本处不再赘述。(安装前一定要选上ADD TO PATH)
2. 打开**管理员权限**的Powershell，执行`pip install pyppeteer`。
3. 看看电脑装没装Edge浏览器，要没有搞一个。
4. 将脚本放在一个重要的位置上，更改脚本:
    1. 填入自己的一站式账户和密码，用**半角**引号括起来(没有加密啊，一定要看好了！)
    2. LOCATION字段，从[这个链接](https://geoinfo.hawa130.com/)获取自己的地址信息。先将其拷贝到一个单独的文件中，然后将所有`'`变成`\'`之后，再将其拷贝至LOCATION。同样，要用**半角引号**括起该字段。
    3. 第22行，把`/bin/chromium`改成`C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe`
5. 测试：在同目录下执行 `python .\reportNcov-outschool.py`
6. windows计划任务简单过一遍。
    1. 打开“计划任务”，右面找"创建基本任务"，点击之。
    2. 打开的窗口中，起名字不说了。触发器选"每天"，自己选个合适的时间(电脑一定是开机状态)。在执行程序的时候写`C:\Users\SuperBart\AppData\Local\Programs\Python\Python310\python.exe`，参数就是你脚本的所在路径。最后完成。
    3. 优化：无论是接电还是电池都要执行etc
## 如何运行(Linux)
1. 安装软件包`python`和`python-pyppeteer`。相关命令看[这个](https://www.superbart.xyz/p/linux-in-quick-run.html#%E8%BD%AF%E4%BB%B6%E5%8C%85%E7%AE%A1%E7%90%86)。
2. 确保电脑有chromium内核的浏览器。
3. 更改脚本，请看Windows版本的相关内容。(更改你浏览器位置的字段请按需调整)
4. 测试。
5. 安装`cronie`软件包，没错，我们要配置自动运行了。
    1. 启动相关服务，对于cronie，是`systemctl enable cronie.service`(enable完了要start啊)
    2. 对于KDE，请使用kcron工具配置。或者使用zeit脚本。
    3. 命令行呢，首先，执行`crontab -e`命令，然后这么搞。前面的部分是时间，我设定为每天早晨9点到10点，每15分钟执行一次(多填几次安心)。后面的命令，自己找好路径吧。
    ```bash
    \*/15 9 * * *    /usr/bin/python /path/to/reportNcov-outschool.py
    ```
小声地告诉你，上网找个crontab在线生成网站。
## 配置Github Action
