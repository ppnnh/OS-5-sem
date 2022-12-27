@echo off
@chcp 65001
@echo -- parametres: %*
@echo -- parameter 1: %1
@echo -- parameter 2: %2
@echo -- parameter 3: %3
@echo off
set /a res= %1 %3 %2
echo -- result: %res%
@pause