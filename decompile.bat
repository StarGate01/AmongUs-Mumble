@ECHO OFF

CD /D "%~dp0"
CALL setup.bat

MKDIR tmp
CD tmp

REM Dump process memory and store loaded modules
MKDIR dump
"%PD32%" -p "Among Us.exe" -o "dump"
XCOPY "dump\*GameAssembly.dll*x86.dll" ".\GameAssembly.dll*" /Y

REM Decompile dumped module
"%IL2CPPINSPECTOR%" -i ".\GameAssembly.dll" -m "%AMONGUS%\Among Us_Data\il2cpp_data\Metadata\global-metadata.dat" -h "cpp" --cpp-compiler MSVC
XCOPY "cpp\appdata\*.*" "..\AUMInjector\appdata\" /K /D /H /Y

CD ..
DEL /s /q tmp\*  >NUL 2>&1
RMDIR /s /q tmp

PAUSE
