# AmongUs-Mumble
Mumble VoIP Plugin and mod for the popular game "Among Us" to enable **Proximity and Directional Voice Chat**. Currently only for Windows PCs and the Steam version. On Linux and OSX a small Mumble fake plugin is provided, which just sets your ingame position to `(0, 0)`.

| Game version | DLL release                                                                   | GAME_VERSION |
| ------------ | ----------------------------------------------------------------------------- | ------------ |
| 2020.9.22s   | [1.0.0.1](https://github.com/StarGate01/AmongUs-Mumble/releases/tag/v1.0.0.1) | `2020922`    |
| 2020.10.22s  | [1.0.0.4](https://github.com/StarGate01/AmongUs-Mumble/releases/tag/v1.0.0.4) | `20201022`   |

Please ensure that you use the correct version for your game installation. All binaries are 32 bit, because the game ist 32 bit and also the free version of the Detours library cant do 64 bit. However, everything runs fine on a 64 bit system.

## State of the Project

 - [x] Load into the game using a DLL proxy
 - [x] Hook into the game logic
 - [x] Extract the player position
 - [x] Pass the position to Mumble via the Link API
 - [x] Handle mute after death, and unmute at game start
 - [x] Handle voting events
 - [x] Port to 2020.10.22s
 - [ ] Implement differentiation between multiple lobbies in the same voice channel
 - [ ] Port to Linux / Proton

## Installation

Download the latest compatible release from https://github.com/StarGate01/AmongUs-Mumble/releases/ , or build it yourself (see below). Drop the `winhttp.dll` file into the same directory as the `Among Us.exe` program. 

If you don't have the `Visual C++ Redistributable for Visual Studio 2015` installed, get it from https://www.microsoft.com/en-us/download/details.aspx?id=48145 . Choose the x86 version, even if your PC is 64 bit.

Install Mumble (Tested: Version 1.3.3) if you have not already: https://www.mumble.info/downloads/ . If the path Mumble was installed to is not `C:\Program Files (x86)\Mumble\mumble.exe` (if you installed the 32 bit version), you have to specify it by editing the Steam launch options of Among Us, for example like this: `-m "C:\Program Files\Mumble\mumble.exe"` if you installed the 64 bit version.

In Mumble, the proximity audio options have to be enabled and configured beforehand:
 - Run `Configure -> Audio Wizard` and configure your Headset
 - Enable `Plugins -> Options -> Link to Game and Transmit Position`
 - Enable `Plugins -> Plugins -> Link v1.2.0` if its not already (note that the version can differ)
 - Enable `Audio Output -> Interface -> Positional Audio`
 - Set `Audio Output -> Positional Audio -> Minimum Distance` to 1.0m (lowest setting)
 - Set `Audio Output -> Positional Audio -> Maximum Distance` to something between 2m and 6m - or even more, according to your preferences
 - Set `Audio Output -> Positional Audio -> Minimum Volume` to 0% (lowest setting)
 
Then run the game and observe the output of the console window (if you run the game in full screen, you might want to tab out or switch to windowed mode). Ensure that the mumble binary path is correct. Mumble should notify when the game connects.

If you have any issues or find bugs, report them here: https://github.com/StarGate01/AmongUs-Mumble/issues .

## How it works

This is a DLL sideloading/hijacking proxy (proxies `winhttp.dll`), which hooks the IL2CPP functions in memory (using the Microsoft Detours library) and exposes the game state to Mumble via shared memory. Originally, I tried a memory-scanning approach (akin to https://github.com/shlifedev/AmongUsMemory/), but this proved to be way to slow. In addition, Mumble is instrumented using RPC commands (for muting and unmuting).

Your anti-virus might flag this as malware, because some of these methods are also sometimes used by malware. If you dont trust me, read and compile the code for yourself.

## FAQ

Does this work on mobile (Android / iOS)?
 - No. It might however be possible to implement a similar hooking mechanism on rooted / jailbroken devices. This would require a mobile Mumble client which is capable of the Mumble Link API. When all baseline features are implemented, I might look into this. When Among Us eventually becomes open source software, this change of course becomes triveal.
 
Does this work on Linux / OSX?
 - Not yet. As there is no native build of the game (runs via Proton), the native OS IPC methods cant be used, which complicates the whole thing. But it is planned for the future.
 - However, a small fake client is provided, which just sets your ingame position to `(0, 0)`.

Why are you releasing this codebase? Hackers will use it to ruin the game!
 - (1) They already do, I have not invented something totally new here. Maybe try playing only with people you know. (2) Trust in this kind of software can only be achieved by open sourcing it. (3) It might lead to more cool mods by the community.
 
Somebody could just turn up the sliders in Mumble and listen to the whole map!
 - Yes. This tool is intended to be used by a group of friends who all play fair.

## Development

For building, use *Visual Studio Community 2019*.

Please note that no decompiled source code of the game is provided, instead you must download `Il2CppInspector` and then run `decompile.bat` after adjusting the file locations in the script. This will decompile your own copy of the game. You might have to add `Il2CppInspector` to your PATH.

A post-build task ist defined in Visual Studio, which calls the file `vmupload.bat`. This script copies the compiled DLL to the Steam game installation directory, and pushes it to a few test VMs. You will probably have to disable or modify it. 

For testing, I recommend setting up a private game server using https://github.com/Impostor/Impostor .

If you want to build for a specific version of the game (each build uses different obfuscated names), append the preprocessor macro `GAME_VERSION` in the project configuration like this: `GAME_VERSION=2020922`. See the table above for version numbers.

### Using the POSIX fake client

The fake client binds to the Mumble Link plugin on Linux and Mac OSX and sets your ingame position to zero. This is not optimal, but better than nothing.

Install `make` and `g++`, on OSX you can use Homebrew (https://brew.sh). Then open your terminal, change into the `POSIX` directory. Run `make` to build the tool, and `make run` to run it.

## Thanks to / Sources

 - https://github.com/djkaty/Il2CppInspector
 - https://github.com/microsoft/Detours
 - https://github.com/maluramichael/dll-proxy-generator
 - https://wiki.mumble.info/wiki/Link
 - https://github.com/shlifedev/AmongUsMemory
 - https://github.com/NeighTools/UnityDoorstop
 - https://github.com/Impostor/Impostor
 - https://github.com/denverquane/amonguscapture
 - https://github.com/ExtraConcentratedJuice/ChristWareAmongUs
 - https://github.com/CLIUtils/CLI11
 - https://github.com/TheNullicorn/among-us-api


## Disclaimer

This modification would be detected by any simple anti-cheat engine. At the time of writing, Among Us uses no such technology. However, I am not responsible for any bans or other problems arising from the usage of this mod. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
