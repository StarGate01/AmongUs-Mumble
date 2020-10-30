@echo off

set "AMONGUS=D:\Steam\steamapps\common\Among Us"

Il2CppInspector-cli.exe -i "%AMONGUS%\GameAssembly.dll" -m "%AMONGUS%\Among Us_Data\il2cpp_data\Metadata\global-metadata.dat" -h "AUMPayload" --cpp-compiler MSVC

del il2cpp.py metadata.json types.cs

git checkout -- AUMPayload

pause