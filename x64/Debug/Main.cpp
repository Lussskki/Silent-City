#include <SFML/Graphics.hpp>
#include "Menu.hpp"
#include "Game.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Silent City");

    while (window.isOpen()) {
        Menu menu(window);
        int selected = menu.run(window);  // Show menu

        if (selected == 0) { // Play
            Game game(window);
            bool backToMenu = game.run(); // Run game and return to menu if requested

            // After returning from the game, reset the view!
            window.setView(sf::View(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y)));

            if (!backToMenu) {
                window.close(); // Player closed the window during gameplay
            }
        }
        else if (selected == 2) { // Exit
            window.close();
        }
    }

    return 0;
}
