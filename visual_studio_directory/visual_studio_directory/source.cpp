#include <SFML/Graphics.hpp>
#include <string>
#include "cell.h"
#include "gameManager.h"
#include <stdexcept>

vector<sf::Sprite> makeSprites(vector<Cell> &cells);
void drawSprites(vector<sf::Sprite>& sprites, vector<Cell> cells, sf::RenderWindow& window);


int main()
{   
    //initialisation

    GameManager game; 
    vector<Cell> cells = game.getAllCells();
    vector<sf::Sprite> sprites = makeSprites(cells);

    int tellertest = 0; 
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!", sf::Style::Fullscreen);
    
    sf::Font font;
    if (!font.loadFromFile("fonts/Arial.ttf"))
        return EXIT_FAILURE;
    sf::Text tekstObj("", font, 50);
   
    //framecapping
    sf::Clock klokje; 
    const sf::Time frameTime = sf::seconds(1.0f / 60.0f);//wordt 1 game tick

    //game logic
    std::cout << "test1";
    while (window.isOpen())
    {
        sf::Event event;
        std::cout << "test2";

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
        std::cout << "test3";

        window.clear();
        sf::Time elapsed = klokje.restart();


        //content
        std::string tekstje = "Fist bump counter: " + std::to_string(tellertest);
        tellertest++;
        tekstObj.setString(tekstje);
        window.draw(tekstObj);
        drawSprites(sprites, game.getAllCells(), window);
        game.nextTick();
        //ending loop
        window.display();
        sf::sleep(frameTime - elapsed);
        std::cout << "test4";

    }
    window.close();
    return EXIT_SUCCESS;
}


vector<sf::Sprite> makeSprites(vector<Cell> &cells) {
    int testteller = 0; 
    vector<sf::Sprite> sprites;
    std::cout << cells.size() << std::endl;
    for (Cell &cell : cells) {

        std::string cellType = "";
        if (cell.getAliveState()) {
            cellType = "cellAlive";
        }
        else {
            cellType = "cellDead";
        }

        sf::Texture texture;
        if (!texture.loadFromFile("images/"+cellType+".jpg"))
            throw std::invalid_argument("image could not be loaded");

        sf::Sprite sprite(texture);

        sprites.push_back(sprite);
        testteller++;
        std::cout << testteller<<std::endl;
    }
    return sprites;
}

void drawSprites(vector<sf::Sprite> &sprites, vector<Cell> cells, sf::RenderWindow &window) {
    int teller = 0;
 
    for (sf::Sprite &sprite : sprites) {
        sprite.setOrigin(4.0f, 4.0f);//set origin to the center
        float x = cells[teller].getX()+0.0f;
        float y = cells[teller].getY() + 0.0f;
        sprite.setPosition(x, window.getSize().y-y);//start drawing from bottom left instead of upper left
        window.draw(sprite);
        teller++;

    }


}




