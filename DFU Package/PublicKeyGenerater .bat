@echo off
title ���ڶ������ DFU Public key������

:continue
cls

@echo ******************** (C) COPYRIGHT 2014-2024,DBGJ.Co.,Ltd. ****************
@echo * File Name��Public Key Generater.bat
@echo * Author: Jason
@echo * Version: 1.0
@echo * Date: 2017/7/31
@echo * Desciption: ��������DFU�����Public key
@echo * �汾˵��: 1.0:����
@echo **************************************************************************



@echo  �밴����ѡ����� 
@echo g ������    q�� �˳�

set input=""
set /p input=  

if /i %input%==g goto Next
if /i %input%==q goto quit


:quit
@echo �˳�
exit

:Next
@echo %date:~4% %time:~0,-3% 
cd D:\nRF52832\DFU Package

nrfutil.exe keys display --key pk --format code private.key --out_file public_key.c

@echo  �밴���������
pause>hul

goto :continue


PublicKeyGenerater.bat