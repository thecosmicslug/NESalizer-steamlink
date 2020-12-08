NESalizer for the Steam Link by TheCosmicSlug
======================================
[GPLv2]	(http://www.gnu.org/licenses/gpl-2.0.html)

A NES emulator using SDL2 originally written by 'ulfalizer' ported to the Steam Link. 
More of a Diet-Nesalizer, as alot of cool features suchh as rewind, movie recording and a built-in debugger were removed to allow it to run on the limited hardware of the Steamlink.
The input system has been re-done, hard-coded keyboard removed and Gamepad support has been added. in-memory save-states are working but I am still trying to work out how to save/load them from disk.

Right now I am teaching myself about creating a basic interface with ImGUI, to allow ROM selection & a configuration window.

## Thanks ##
 * ulfalizer for the original sdl version

 * https://github.com/Kevoot/NESalizer - Kevroot ported my striped down nesalizer to the nintendo switch, which I think is awsome work! infact seeing as he has added a GUI to his port motivated me to come back to mine and see if I can learn something new cooking up a basic GUI for the steamlink version.

 * https://github.com/usrshare/nesalizerX - Another interesting port of the original nesalizer, this guy seems to know what he is doing.

 * Shay Green (blargg) for the [blip\_buf](https://code.google.com/p/blip-buf/) waveform synthesis library.
 * Quietust for the Visual 2A03 and Visual 2C02 simulators.
 * beannaich, cpow, Disch, kevtris, Movax21, Lidnariq, loopy, thefox, Tepples and lots of other people on the [NesDev](http://nesdev.com) forums and wiki and in #nesdev for help, docs, tests, and discussion.

## Building ##
Requires the Steamlink-SDK available on github

git clone https://github.com/ValveSoftware/steamlink-sdk
cd steamlink-sdk/examples
git clone https://github.com/thecosmicslug/NESalizer
cd nesalizer
./build_steamlink.sh

## Running ##
 Right now it simply loads "Mario(E).nes" from the current folder unless you provide a filename.

## Controls ##

Movement:
SDL_CONTROLLER_BUTTON_DPAD_UP
SDL_CONTROLLER_BUTTON_DPAD_DOWN
SDL_CONTROLLER_BUTTON_DPAD_LEFT
SDL_CONTROLLER_BUTTON_DPAD_RIGHT

Buttons:
SDL_CONTROLLER_BUTTON_BACK 			= Select
SDL_CONTROLLER_BUTTON_START 			= Start
SDL_CONTROLLER_BUTTON_A			= A
SDL_CONTROLLER_BUTTON_B			= B

Emulation:
SDL_CONTROLLER_BUTTON_LEFTSHOULDER		= Load State
SDL_CONTROLLER_BUTTON_RIGHTSHOULDER		= Save State
SDL_CONTROLLER_BUTTON_GUIDE			= Exit Program
SDL_CONTROLLER_BUTTON_LEFTSTICK		= Screenshot (Will eventually bring up GUI Overlay)

## Compatibility ##
iNES mappers (support circuitry inside cartridges) supported so far: 
0, 1, 2, 3, 4, 5 (including ExGrafix, split screen, and PRG RAM swapping), 7, 9, 10, 11, 13, 28, 71, 232. This covers the majority of ROMs.

Supports tricky-to-emulate games like Mig-29 Soviet Fighter, Bee 52, Uchuu Keibitai SDF, Just Breed, and Battletoads.

## Technical ##
Uses a low-level renderer that simulates the rendering pipeline in the real PPU (NES graphics processor), following the model in [this timing diagram](http://wiki.nesdev.com/w/images/d/d1/Ntsc_timing.png) that ulfalizer put together with help from the NesDev community. 

(It won't make much sense without some prior knowledge of how graphics work on the NES.

Most prediction and catch-up (two popular emulator optimization techniques) is omitted in favor of straightforward and robust code. This makes many effects that require special handling in some other emulators work automatically
