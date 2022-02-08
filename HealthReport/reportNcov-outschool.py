#!/usr/bin/python
# Automatic upload your health situation outside school. For xidian.
# Based on "health-card-checkin" by hawa130, which could be found at https://github.com/hawa130/health-card-checkin
# Copyright 2022 SuperBart & hawa130. Released under Unlicense.

import asyncio
import pyppeteer

# USERNAME 输入你的学号 PASSWORD 输入你的统一认证密码(一定要输入在双引号内，这是个字符串)
USERNAME = ""
PASSWORD = ""
LOGIN = "https://xxcapp.xidian.edu.cn/ncov/wap/default/index"
REPORT = "https://xxcapp.xidian.edu.cn/ncov/wap/default/save"
# 从 https://geoinfo.hawa130.com/ 获取定位 贴在这里
# 注意: 贴进来*之前*要把所有的'"'改成'\"' 要不然python以为字符串各种丢失
LOCATION = ""

# 上报函数
async def commit(username, password):
    # 贴士 查阅一下你电脑的Chrome/Chromium安装地址 然后上网搜怎么加参数
    # 否则他会自动下载个新的chromium:-P
    browser = await pyppeteer.launcher.launch(executablePath="/bin/chromium")
    page = await browser.newPage()
    await page.goto(LOGIN)
    await page.evaluate("vm.username = " + str(username) + ";")
    await page.evaluate("vm.password = \"" + password + "\";")
    await page.evaluate("vm.login()")
    print("成功登陆")
    await page.waitForNavigation({ "waitUntil": "domcontentloaded" })
    print("已经准备好上报了")
    # 为啥不能直接运行这个 要能成功多方便啊
    # await page.evaluate("vm.getLocation()")
    await page.evaluate("vm.locatComplete(" + LOCATION + ")")
    await page.evaluate("() => vm.save()")
    situation = await page.waitForResponse(REPORT)
    print("上传成功，好耶!")
    print(await situation.json())
    await browser.close()

if __name__ == "__main__":
    asyncio.run(commit(USERNAME, PASSWORD))

## Got to get her into my life!
