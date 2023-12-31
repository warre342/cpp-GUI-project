#include <SFML/Graphics.hpp>
#include <string>
#include "cell.h"
#include "gameManager.h"
#include <stdexcept>
#include <stdlib.h>
#include <iostream>
void drawCells(vector<Cell> cells, sf::RenderWindow& window);
void startGame(sf::RenderWindow& window, GameManager& game, float tickTime);


int main()
{   
    //initialisation
    GameManager game; 
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!", sf::Style::Fullscreen);
    startGame(window, game, 1+0.0f);
    window.close();
    

    return EXIT_SUCCESS;
}


void drawCells(vector<Cell> cells, sf::RenderWindow &window) {//improvment: alleen de cells drawen die veranderd zijn
    //int teller = 0;
    sf::Texture aliveTexture;
    sf::Texture deadTexture;
    if (!aliveTexture.loadFromFile("images/cellAlive.jpg"))
        throw std::invalid_argument("image could not be loaded");
    if (!deadTexture.loadFromFile("images/cellDead.jpg"))
        throw std::invalid_argument("image could not be loaded");
    sf::Sprite aliveSprite(aliveTexture);
    sf::Sprite deadSprite(deadTexture);
    
    sf::Sprite currentSprite; 
    //std::cout << "amount of sprites: " << cells.size()<<std::endl;
    for (Cell& cell : cells) {
        if (cell.getAliveState()) {
            currentSprite=aliveSprite;
        }
        else {
            currentSprite = deadSprite;
        }
        float x = cell.getX() + 0.0f;
        float y = cell.getY() + 0.0f;
        currentSprite.setPosition(x, y);
        window.draw(currentSprite);
        //teller++;
        //std::cout <<"n'th box drawn: " << teller << std::endl;
    }

}

void startGame(sf::RenderWindow &window,GameManager &game, float tickTime ) {
    sf::Clock klokje;
    const sf::Time frameTime = sf::seconds(tickTime);//wordt 1 game tick

    //game loop
    while (window.isOpen())
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

        window.clear();
        sf::Time elapsed = klokje.restart();
        
        //content
        drawCells(game.getAllCells(), window);
        window.display();
        game.nextTick();
        std::cout <<"time elapsed: "<< elapsed.asMilliseconds() << std::endl;
        sf::sleep(frameTime);
        std::cout << "frame printed" << std::endl;

    }
    window.close();


}




