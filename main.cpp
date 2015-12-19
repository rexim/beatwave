#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Hello World - SFML");

    while (App.isOpen())
    {
        sf::Event Event;
        while (App.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
                App.close();
            else if (Event.type == sf::Event::) {
            }

        }
        App.clear(sf::Color(0,0,255));
        App.display();
    }
 
    return 0;
}
