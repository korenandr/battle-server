# Use CMake to deploy Battle-Server locally

This page walks you through the steps required to deploy the [Battle-Server](https://github.com/korenandr/battle-server) sample application locally using CMake.

## Prerequisites

- **CMake:** 3.27+
- **Compiler:** gcc 14+ / clang 15+
- **C++ standart:** C++17

## Deploy the sample application

1. Clone the Github repository.

    ```bash
    git clone https://github.com/korenandr/battle-server.git
    ```

2. Create and navigate to the build directory.

    ```bash
    cd battle-server
    mkdir build && cd build
    ```

3. Configure and build the project with CMake.

    ```bash
    cmake ..
    cmake --build .
    ```

## Clean up

1. Clean CMake build files (optional).

    ```bash
    rm -rf build/
    ```