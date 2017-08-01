@echo off
title 深圳栋邦国际BootLoader Setting生成器

:continue
cls

@echo ******************** (C) COPYRIGHT 2014-2024,DBGJ.Co.,Ltd. ****************
@echo * File Name：DFU Package Generater.bat
@echo * Author: Jason
@echo * Version: 1.0
@echo * Date: 2017/7/31
@echo * Desciption: 用于生成BootLoader Setting文件
@echo * 版本说明: 1.0:创建
@echo * 办公室路劲：cd D:\nRF52832\FactoryTools
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

cd D:\Code\nRF52832-Tcore\FactoryTools

nrfutil settings generate --family NRF52 --application tcore.hex --application-version 0 --bootloader-version 0 --bl-settings-version 1 bootloader_setting.hex

@echo  请按任意键继续
pause>hul

goto :continue

BootLoaderSettingGenerater.bat