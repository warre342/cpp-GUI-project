#include <SFML/Graphics.hpp>
#include <string>
#include "cell.h"
#include "gameManager.h"
#include <stdexcept>

void drawCells( vector<Cell> cells, sf::RenderWindow& window);


int main()
{   
    //initialisation

    GameManager game; 
    vector<Cell> cells = game.getAllCells();

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!", sf::Style::Fullscreen);
    
    //framecapping
    sf::Clock klokje; 
    const sf::Time frameTime = sf::seconds(10.0f);//wordt 1 game tick

    //game logic
    while(window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            //close game if escape 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {//kan ook (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
            }
        }
        //frames

        window.clear();
        sf::Time elapsed = klokje.restart();


        //content
        drawCells(game.getAllCells(), window);
        game.nextTick();
        //ending loop

        window.display();

        sf::sleep(frameTime - elapsed);

    }
    window.close();
    return EXIT_SUCCESS;
}


void drawCells( vector<Cell> cells, sf::RenderWindow &window) {
    int teller = 0;
    sf::Texture aliveTexture;
    sf::Texture deadTexture;
    if (!aliveTexture.loadFromFile("images/cellAlive.jpg"))
        throw std::invalid_argument("image could not be loaded");
    if (!deadTexture.loadFromFile("images/cellDead.jpg"))
        throw std::invalid_argument("image could not be loaded");
    sf::Sprite aliveSprite(aliveTexture);
    sf::Sprite deadSprite(deadTexture);
    
    sf::Sprite currentSprite; 
    std::cout << "amount of sprites: " << cells.size()<<std::endl;
    for (Cell& cell : cells) {
        if (cell.getAliveState()) {
            currentSprite=aliveSprite;
        }
        else {
            currentSprite = deadSprite;
        }
        currentSprite.setOrigin(4.0f, 4.0f);//set origin to the center
        float x = cell.getX() + 0.0f;
        float y = cell.getY() + 0.0f;
        currentSprite.setPosition(x, window.getSize().y-y);//start drawing from bottom left instead of upper left
        window.draw(currentSprite);
        teller++;
        std::cout <<teller << std::endl;
    }



    


}




