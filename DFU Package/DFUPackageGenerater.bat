@echo off
title 深圳栋邦国际 DFU Package生成器

:continue
cls

@echo ******************** (C) COPYRIGHT 2014-2024,DBGJ.Co.,Ltd. ****************
@echo * File Name：DFU Package Generater.bat
@echo * Author: Jason
@echo * Version: 1.0
@echo * Date: 2017/7/31
@echo * Desciption: 用于生成DFU所需的升级包
@echo * 版本说明: 1.0:创建
@echo **************************************************************************



@echo  请按按键选择操作 
@echo g ：生成    q： 退出

set input=""
set /p input=  

if /i %input%==g goto Next
if /i %input%==q goto quit


:quit
@echo 退出
exit

:Next
@echo %date:~4% %time:~0,-3% 
cd D:\nRF52832\DFU Package

nrfutil pkg generate --hw-version 52 --application-version 1 --application tcore.hex --sd-req 0x98 --key-file private.key tcore_app_dfu_package.zip

@echo  请按任意键继续
pause>hul

goto :continue


PublicKeyGenerater.bat