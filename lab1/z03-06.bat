@echo off
echo -- parametres: %1  %2
echo -- mode: %1
echo -- name of file : %2

if "%1"=="" (goto case1) else (goto case2)
if "%2"=="" (
    echo file name not set 
    goto exit
) else if "%1" neq "create" or if "%1" neq "delete" (
    echo mode set incorrectly
    goto exit
)

:case1
    echo mode = {create,delete}
    echo file = file name 
    goto exit

:case2
    if "%2"=="" (goto case3) else (goto case4)

:case3
    echo file name not set 
    goto exit

:case4
if "%1" == "create" (goto create)
if "%1" == "delete" (goto delete) else (goto operation)
:operation
    echo mode set incorrectly
    goto exit

:create
if exist %2 (goto found)
copy NUL %2
echo file %2 created
goto exit

:delete
if not exist %2 (goto notfound)
del %2
echo file %2 deleted
goto exit

:found
echo file %2 found
goto exit

:notfound
echo file %2 not found
goto exit

:exit
@pause