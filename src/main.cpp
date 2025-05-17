#include <FSM/Game.hpp>

#include <iostream>

int main(int argc, char** argv) {
	try {
        // Check command line arguments and run application
        return sw::fsm::Game{argc, argv}.run();
    }
    catch (const std::exception& exc) {
        std::cerr << "Failed to run application: " << exc.what() << std::endl;
        return EXIT_FAILURE;
    }
}
