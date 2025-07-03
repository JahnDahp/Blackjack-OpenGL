A fully playable Blackjack game built with modern C++20 and OpenGL. This project uses:

All dependencies are automatically installed via vcpkg (https://github.com/microsoft/vcpkg):

- glfw3
- glew
- glm
- freetype

Make sure the following tools are installed and available in your PATH:

- Git
- CMake (https://cmake.org/download/)
- Ninja (https://ninja-build.org/)
- Compiler C++20 compatible (MSVC, Clang, GCC, etc.)

How to build:

- git clone --recurse-submodules https://github.com/JahnDahp/Blackjack.git
- cd Blackjack
- cmake --preset=Default
- cmake --build --preset=Default
- cd Bin
- Blackjack.exe
