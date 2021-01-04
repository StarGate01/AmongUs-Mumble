@ECHO OFF

CD /D "%~dp0"
CALL setup.bat

ECHO "Copying to %AMONGUS%"
COPY /b /v /y "%1" "%AMONGUS%\winhttp.dll"

IF DEFINED VM_UPLOAD (
    FOR %%x IN (%VM_SUFFIXES%) DO (
        ECHO "Copying to VM %VM_BASENAME%%%x"
        COPY /b /v /y "%1" "\\%VM_BASENAME%%%x\%VM_AMONGUS%\winhttp.dll"
    )
)
