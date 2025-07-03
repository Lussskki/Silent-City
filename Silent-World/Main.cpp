#include "Game.hpp"
#include "Menu.hpp"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Silent World - Menu");

    Menu menu(800, 600);
    int selected = menu.run(window);

    if (selected == 0) { // Play selected
        Game game;
        game.run();
    }
    else if (selected == 1) {
        // You can later add settings/options screen here
        std::cout << "Options selected (not yet implemented).\n";
    }
    else if (selected == 2) {
        std::cout << "Exiting...\n";
    }

    return 0;
}
