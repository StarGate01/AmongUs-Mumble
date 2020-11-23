[![Discord](https://img.shields.io/discord/767166243303587882?color=cornflowerblue&label=Discord&logo=Discord&logoColor=white)](https://discord.gg/4UkHEJ5sqg)  [![GitHub all releases](https://img.shields.io/github/downloads/StarGate01/AmongUs-Mumble/total?label=Downloads)](https://github.com/StarGate01/AmongUs-Mumble/releases)

# AmongUs-Mumble
[Mumble VoIP](https://www.mumble.info/) Plugin and mod for the popular game "[Among Us](https://store.steampowered.com/app/945360/Among_Us/)" by [Innersloth](http://www.innersloth.com/) to enable **Proximity and Directional Voice Chat**.

Currently only for Windows PCs and the Steam version. On Linux and OSX a small Mumble fake plugin is provided, which just sets your ingame position to `(0, 0)`.

Version numbering: Release compatible builds use `1.0.0.X`, beta builds use `1.0.1.X`. See the table for compatibility. Please ensure that you use the correct version for your game installation. Please note *BETA BUILDS MIGHT BE UNSTABLE*.

| Game version | Game channel | DLL release                                                                   | GAME_VERSION |
| ------------ | ------------ | ----------------------------------------------------------------------------- | ------------ |
| 2020.11.4s   | Beta         | [1.0.1.6](https://github.com/StarGate01/AmongUs-Mumble/releases/tag/v1.0.1.6) | `202011040`  |
| 2020.10.22s  | Release      | [1.0.0.6](https://github.com/StarGate01/AmongUs-Mumble/releases/tag/v1.0.0.6) | `202010220`  |
| 2020.9.22s   | Release      | [1.0.0.1](https://github.com/StarGate01/AmongUs-Mumble/releases/tag/v1.0.0.1) | `20209220`   |

If you are looking for a community that uses this mod, join the [Discord server](https://discord.gg/4UkHEJ5sqg)!

If you have any issues or find bugs, report them on our [issue tracker](https://github.com/StarGate01/AmongUs-Mumble/issues) .

## Main Features
 - Real-time proximity voice chat based on ingame player position
 - Directional audio depending on relative position of players (Optional)
 - Works with any official or unofficial Among Us server
 - Works with any Mumble server
 - In-Game GUI for easy configuration
 - Automatic handling of round start, round end, emergency meetings and player deaths
 - Ghosts can always listen to emergency meetings
 - Three modes for ghosts:
   - *Purgatory:* Ghosts can talk to each other regardless of their position, but cannot listen to remaining players (Default)
   - *Spectate:* Ghosts are muted, but can listen to remaining players if they are close enough (Optional)
   - *Haunt:* Ghosts can talk and listen to remaining players if they are close enough (Optional)
 - Everyone gets muted during communication sabotage events
 - Automatic settings synchronisation for all players in a lobby.
 - Easy installation process, just copy one file
 - Smart linking, no need to start the game and Mumble in any particular order
 - Easy configuration using a configuration file or command line options

## Documentation
 - [Installation and Setup](https://github.com/StarGate01/AmongUs-Mumble/wiki/Installation-and-Setup)
 - [Frequently Asked Questions](https://github.com/StarGate01/AmongUs-Mumble/wiki/Frequently-Asked-Questions)
 - [How It Works](https://github.com/StarGate01/AmongUs-Mumble/wiki/How-It-Works)
 - [Development](https://github.com/StarGate01/AmongUs-Mumble/wiki/Development)
 - [Using the POSIX Fake Client](https://github.com/StarGate01/AmongUs-Mumble/wiki/Using-the-POSIX-Fake-Client)

## Project State
 - [Issues and Planned Features](https://github.com/StarGate01/AmongUs-Mumble/projects/1)
 - [Release branch](https://github.com/StarGate01/AmongUs-Mumble/tree/master)
 - [Beta branch](https://github.com/StarGate01/AmongUs-Mumble/tree/beta)
 - [Development branch](https://github.com/StarGate01/AmongUs-Mumble/tree/dev)

## Support
If you would like to donate to the project, You can do so on [Bountysource SALT](https://salt.bountysource.com/teams/team-esdg) .

Please note that we are NOT associated with [Innersloth](http://www.innersloth.com/), the original developer of "Among Us". Please support them as well by buying their games and merch.

### Sources

 - https://github.com/djkaty/Il2CppInspector For generating the Il2CPP framework
 - https://github.com/microsoft/Detours For hooking functions in memory
 - https://github.com/maluramichael/dll-proxy-generator For generating the proxy DLL prototypes
 - https://wiki.mumble.info/wiki/Link For the connection to Mumble
 - https://github.com/CLIUtils/CLI11 For command line and config file parsing
 - https://github.com/ocornut/imgui For the GUI
 - https://github.com/ExtraConcentratedJuice/ChristWareAmongUs For the IMGUI DirectX hook

### Thanks to

We thank the developers of Mumble for not only providing their software for free and open-source, but also for being open to suggestions and actively supporting this project.

 - https://github.com/shlifedev/AmongUsMemory For general info about game data structures
 - https://github.com/NeighTools/UnityDoorstop For inspiration for the proxy DLL
 - https://github.com/Impostor/Impostor For providing private testing servers
 - https://github.com/denverquane/amonguscapture For general info about game data structures
 - https://github.com/TheNullicorn/among-us-api For general info about the games network protocol
 - https://wiki.weewoo.net/wiki/Main_Page For detailed info about the games network protocol
 - https://github.com/willardf/Hazel-Networking For implementation info about the games network protocol


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
