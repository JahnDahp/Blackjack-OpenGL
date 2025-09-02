This is a Blackjack game meant to simulate most real Blackjack games found in casinos across the United States.

![BJ2](https://github.com/user-attachments/assets/2398608d-31a5-463b-bcd0-81bc314e3129)

![BJ3](https://github.com/user-attachments/assets/f400f296-a2f0-4c61-9c72-3da84d925b90)

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

![BJ1](https://github.com/user-attachments/assets/37e59882-9e1a-4d61-a8fb-34228b7b6638)

Code Details
--------
Libraries used
  - [glew](https://github.com/nigels-com/glew) for loading OpenGL.
  - [glfw](https://github.com/StudioClockWork/GLFW) for creating the window.
  - [glm](https://github.com/g-truc/glm) for matrix operations.
  - [stb_image](https://github.com/nothings/stb) for image rendering.
  - [freetype](https://github.com/cpuimage/freetype) for text rendering.

Build Instructions
--------
Requirements:
  - [CMake](https://cmake.org/)
  - C++20 compiler/build tools ([MSVC](https://visualstudio.microsoft.com/vs/features/cplusplus/), [GCC](https://gcc.gnu.org/install/), [Ninja](https://github.com/ninja-build/ninja), or [Clang](https://github.com/llvm/llvm-project/releases). On Windows, this comes with Visual Studio or Build Tools for Visual Studio.

Run `git clone --recursive https://github.com/JahnDahp/Blackjack-OpenGL/`. Then cd Blackjack-OpenGL && mkdir Build && cd Build && cmake .. -DCMAKE_BUILD_TYPE=Release && cmake --build . --config Release.
