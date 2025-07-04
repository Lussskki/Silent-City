#include <SFML/Graphics.hpp>
#include "Menu.hpp"
#include "Game.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Silent City");

    Menu menu(window);
    int selected = menu.run(window);  // Runs inside same window

    if (selected == 0) { // Play
        Game game(window);
        game.run();
    }
    else if (selected == 2) {
        window.close();
    }

    return 0;
}
