# Install Materials Studio on Win10

## Uninstall previous verion 32bit
- [CSDN](https://blog.csdn.net/sinat_41351675/article/details/107403168)
1. 控制面板。程序，程序和功能，卸载四个BIOVIA的文件
2. 去C/programfiles x86/Acclerys，去D/Materials Studios 删除文件夹
3. win + R, regedit, 点击 HKEY_LOCAL_MACHINE, SOFTWARE，删除BIOVIA和Accelrys

## 安装 MS 2020 淘宝买压缩包rar
- 淘宝买压缩包rar，7zip解压到D盘，使用管理员运行setup.ext
- 英文用户名，安装位置改成D盘，新建文件夹 Materials Studio 2020 （不能有中文），然后默认安装，
- 文件夹，右键此电脑-属性，复制设备名称 DESKTOP-HBOPK2U，打开msi2020.lic 替换掉 this_host，然后复制到下面三个（BIOVIA替换Accelry）
  C:\Program Files (x86)\Accelrys\LicensePack\Licenses\
	C:\Program Files (x86)\Accelrys\LicensePack\share\data\
	C:\Program Files (x86)\Accelrys\LicensePack\win32\bin\


## Geometric Optimization
- 拖拽文字文件进来，卡住怎么办，把输入法兼容性打开 [CSDN](https://blog.csdn.net/qq_42168543/article/details/116310561)
- 
