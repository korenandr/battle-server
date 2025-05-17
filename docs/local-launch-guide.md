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
    cd ./battle-server
    ```

2. Configure and build the project with CMake.

    ```bash
    cmake -S . -B build
    cmake --build build
    ```

4. Launch Unit tests.

    ```bash
    cd build/tests && ctest
    ```

## Clean up

1. Clean CMake build files (optional).

    ```bash
    rm -rf build/
    ```