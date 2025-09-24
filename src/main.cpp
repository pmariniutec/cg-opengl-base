#include "Application.h"
#include <iostream>

int main() {
    Application app(800, 600, "OpenGL 4.5 - Points & Lines Demo");

    if (!app.Initialize()) {
        std::cerr << "Failed to initialize application" << std::endl;
        return -1;
    }

    std::cout << "Application initialized successfully!" << std::endl;
    
    app.Run();

    std::cout << "Application shutting down..." << std::endl;
    return 0;
}
