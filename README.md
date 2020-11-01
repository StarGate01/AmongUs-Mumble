# AmongUs-Mumble
Mumble VoIP Plugin and mod for the popular game "Among Us" to enable **Proximity Voice Chat**. Currently only for Windows PCs.

Tested: Version 2020.9.22s (Steam, Windows)

All binaries are 32 bit, because the game ist 32 bit and also the free version of the detours library cant do 64 bit.

For building, I used *Visual Studio Community 2019*.

## Among Us client mod
A DLL hijacking proxy, which exposes game state via a named pipe. Created using:

 - https://github.com/djkaty/Il2CppInspector
 - https://github.com/microsoft/Detours
 - https://github.com/maluramichael/dll-proxy-generator
 
Please note that no decompiled source code of the game is provided, instead you must download `Il2CppInspector` and then run `decompile.bat` after adjusting the file locations in the script. This will decompile your own copy of the game. You might have to add `Il2CppInspector` to your PATH.

### Installation:
Drop the `winhttp.dll` file into the same directory as the `Among Us.exe` program.
 
## Mumble client plugin
Receives the game state data and generates positional audio data packets.
 - TBA
 
