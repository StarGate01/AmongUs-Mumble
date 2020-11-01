# AmongUs-Mumble
Mumble VoIP Plugin and mod for the popular game "Among Us" to enable **Proximity Voice Chat**. Currently only for Windows PCs.

Tested: **Version 2020.9.22s (Steam, Windows 10 x64)**

All binaries are 32 bit, because the game ist 32 bit and also the free version of the detours library cant do 64 bit. However, everything runs fine on a 64 bit system, too.

For building, use *Visual Studio Community 2019*.

## Installation
Drop the `winhttp.dll` file into the same directory as the `Among Us.exe` program. Then run the game and observe the output of the console window. Mumble should notify when the game connects.

In Mumble, the proximity audio options have to be enabled beforehand.

## How it works
This is a DLL sideloading/hijacking proxy (proxies winhttp), which hooks the IL2CPP functions in memory and exposes game state to Mumble via the the Mumble Link protocol (shared memory). Created using:

 - https://github.com/djkaty/Il2CppInspector
 - https://github.com/microsoft/Detours
 - https://github.com/maluramichael/dll-proxy-generator
 - https://wiki.mumble.info/wiki/Link
 
Please note that no decompiled source code of the game is provided, instead you must download `Il2CppInspector` and then run `decompile.bat` after adjusting the file locations in the script. This will decompile your own copy of the game. You might have to add `Il2CppInspector` to your PATH.

Your anti-virus might flag this as malware, because some methods used are also sometimes used by malware. If you dont trust me, read and compile the code yourself.

