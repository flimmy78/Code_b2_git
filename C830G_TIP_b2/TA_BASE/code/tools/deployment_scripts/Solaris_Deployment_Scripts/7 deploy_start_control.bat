@ECHO OFF

CALL GLOBAL.BAT
date /T > copy.log

for /F "tokens=1,2,3 delims= " %%i in (%SERVER%) do @(
    start deploy_start_control_stn.bat %%i %%j %%k
    .\sleep 1
)

pause
