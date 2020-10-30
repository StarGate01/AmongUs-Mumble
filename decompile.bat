@echo off

set "AMONGUS=D:\Steam\steamapps\common\Among Us"

mkdir tmp
cd tmp

Il2CppInspector-cli.exe -i "%AMONGUS%\GameAssembly.dll" -m "%AMONGUS%\Among Us_Data\il2cpp_data\Metadata\global-metadata.dat" -h "cpp" --cpp-compiler MSVC
xcopy "cpp\appdata\*.*" "..\AUMInjector\appdata\" /K /D /H /Y

cd ..
del /s /q tmp\*  >nul 2>&1
rmdir /s /q tmp

pause