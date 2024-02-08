#include <SFML/Graphics.hpp>
#include <string>
#include "GameLogic/cell.h"
#include "GameLogic/gameManager.h"
#include "GuiLogic/tile.h"
#include "GuiLogic/tileGrid.h"
#include <stdexcept>
#include <stdlib.h>
#include <iostream>
void startGame( GameManager& game, float tickTime);
void drawCells(vector<Cell> cells, sf::RenderWindow& window);
void requestSelection(TileGrid& grid);
void drawTiles(TileGrid& grid, sf::RenderWindow& window);


int main()
{   
    //initialisation
    TileGrid grid;
    grid.printGrid();
    requestSelection(grid);
    grid.printGrid();
    GameManager game(grid);
    startGame(game, 1+0.0f);
    

    return EXIT_SUCCESS;
}


void startGame(GameManager &game, float tickTime ) {

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Game of Life!, press escape to end", sf::Style::Fullscreen, sf::ContextSettings(24, 8, 2, 3, 2));//--
    //sf::Clock klokje;
    window.setFramerateLimit(tickTime);
    //const sf::Time frameTime = sf::seconds(tickTime);//wordt 1 game tick

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
        //sf::Time elapsed = klokje.restart();
        
        //content
        drawCells(game.getAllCells(), window);
        window.display();
        game.nextTick();
        //std::cout <<"time elapsed: "<< elapsed.asMilliseconds() << std::endl;
        //sf::sleep(frameTime);
        //std::cout << "frame printed" << std::endl;

    }
    window.close();

}
void drawCells(vector<Cell> cells, sf::RenderWindow& window) {
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
            currentSprite = aliveSprite;
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


void requestSelection(TileGrid& grid) {
    sf::RenderWindow window(sf::VideoMode(800, 450), "pattern selection", sf::Style::Default, sf::ContextSettings(24, 8, 2, 3, 2));//downsized version of 16x9 50x50 tiles
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {//kan ook (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int mouseX = event.mouseButton.x;
                    int mouseY = event.mouseButton.y;
                    cout << "x=" << mouseX << " y=" << mouseY<< endl;
                    int row = mouseY / (window.getSize().y / TileGrid::yMax);
                    int col = mouseX / (window.getSize().x / TileGrid::xMax);
                    cout << "row=" << row << " col=" << col << endl;

                    // Toggle the state of the clicked tile
                    grid.getTile(col,row).toggle();

                }
            }
        }
        window.clear();

        //content
        drawTiles(grid, window);

        window.display();

    }
    window.close();
}

void drawTiles(TileGrid& grid, sf::RenderWindow& window) {

    for (int row = 0; row < TileGrid::yMax; row++) {
        for (int col = 0; col < TileGrid::xMax; col++) {
            sf::Color kleurtje = grid.getTile(col, row).isActive() ? sf::Color::White : sf::Color::Black;

            sf::RectangleShape tileShape(sf::Vector2f(window.getSize().x / TileGrid::xMax, window.getSize().y / TileGrid::yMax));
            tileShape.setPosition(col * tileShape.getSize().x, row * tileShape.getSize().y);
            tileShape.setFillColor(kleurtje);

            window.draw(tileShape);
        }
    }
}



