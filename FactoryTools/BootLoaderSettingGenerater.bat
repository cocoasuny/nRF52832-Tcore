@echo off
title ���ڶ������BootLoader Setting������

:continue
cls

@echo ******************** (C) COPYRIGHT 2014-2024,DBGJ.Co.,Ltd. ****************
@echo * File Name��DFU Package Generater.bat
@echo * Author: Jason
@echo * Version: 1.0
@echo * Date: 2017/7/31
@echo * Desciption: ��������BootLoader Setting�ļ�
@echo * �汾˵��: 1.0:����
@echo * �칫��·����cd D:\nRF52832\FactoryTools
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

cd D:\Code\nRF52832-Tcore\FactoryTools

nrfutil settings generate --family NRF52 --application tcore.hex --application-version 0 --bootloader-version 0 --bl-settings-version 1 bootloader_setting.hex

@echo  �밴���������
pause>hul

goto :continue

BootLoaderSettingGenerater.bat