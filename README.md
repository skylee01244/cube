# Spinning Cube


A high-performance 3D ASCII renderer built in C++ that projects rotating cubes using custom transformations and depth buffering. Leveraging advanced low-level optimization and efficient memory management, this project demonstrates expert proficiency in modern C++ techniques such as lambda functions and optimized buffer management and object-oriented design.

![Screenshot of Game Screen.](/images/cube_screen.png)

## Build Instructions
How To Build:
1) **Install CMake**  
   Download and install CMake from https://cmake.org/download/
2) **Navigate to Your Project Directory**  
   Open your terminal and navigate to the project directory where `CMakeLists.txt` is located.
3) **Build using CMake**
    > For a multi-configuration generator (Windows)
    ```
    cmake -S . -B build
    cmake --build build --config Release
    ```
    > For a single-configuration generator (LINUX & MACOS)
    ```
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build
    ```
4) **Run the Application**  
   Execute the `cube.exe` (Windows) or `./cube` (Linux/macOS) file located in `build/Release/` (Windows) or `build/` (Linux/macOS).




## Notes
Made with references to: https://en.wikipedia.org/wiki/Rotation_matrix