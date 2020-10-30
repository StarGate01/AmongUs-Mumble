# AmongUs-Mumble
Mumble VoIP Plugin and mod for the popular game "Among Us" to enable **Proximity Voice Chat**

Tested: Version 2020.9.22s (Steam)

## Among Us client mod
A DLL hijacking proxy, which exposes game state via a named pipe. Created using:
 - https://github.com/djkaty/Il2CppInspector
 - https://github.com/microsoft/Detours
 - https://github.com/maluramichael/dll-proxy-generator
Please note that no decompiled source code of the game is provided, instead you must download Il2CppInspector and then run `decompile.bat` after adjusting the file locations. This will decompile your own copy of the game.

### Installation:
Drop the `winhttp.dll` file into the same directory as the `Among Us.exe` program.
 
## Mumble client plugin
Receives the game state data and generates positional audio data packets.
 - TBA
 
