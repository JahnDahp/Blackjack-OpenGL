This is a Blackjack game meant to simulate most real Blackjack games found in casinos across the United States.

Features
--------
  - Blackjack payout
  - Dealer hitting/staying on soft 17
  - Number of decks
  - Doubling after a split
  - Number of hands to split to
  - Draw on split aces
  - Resplit aces
  - Late surrender
  - Deck penetration
  - Totals where doubling is allowed
  - Variable bets and bankroll sizes
  - Insurance

Code Details
--------
Libraries used
  - [glew](https://github.com/nigels-com/glew) for loading OpenGL.
  - [glfw](https://github.com/StudioClockWork/GLFW) for creating the window.
  - [glm](https://github.com/g-truc/glm) for matrix operations.
  - [stb_image](https://github.com/nothings/stb) for image rendering.
  - [freetype](https://github.com/cpuimage/freetype) for text rendering.
  - [vcpkg](https://github.com/microsoft/vcpkg.git) for managing dependencies.

Build Instructions
--------
Requirements:
  - [CMake](https://cmake.org/)
  - C++20 compiler/build tools ([MSVC](https://visualstudio.microsoft.com/vs/features/cplusplus/), [GCC](https://gcc.gnu.org/install/), [Ninja](https://github.com/ninja-build/ninja), or [Clang](https://github.com/llvm/llvm-project/releases). On Windows, this comes with Visual Studio or Build Tools for Visual Studio.

Run the bootstrap to generate in the executable in Bin. Run bootstrap.bat for windows, bootstrap.sh for MacOS/Linux.
