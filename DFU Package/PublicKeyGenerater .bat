@echo off
title 深圳栋邦国际 DFU Public key生成器

:continue
cls

@echo ******************** (C) COPYRIGHT 2014-2024,DBGJ.Co.,Ltd. ****************
@echo * File Name：Public Key Generater.bat
@echo * Author: Jason
@echo * Version: 1.0
@echo * Date: 2017/7/31
@echo * Desciption: 用于生成DFU所需的Public key
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

nrfutil.exe keys display --key pk --format code private.key --out_file public_key.c

@echo  请按任意键继续
pause>hul

goto :continue


PublicKeyGenerater.bat