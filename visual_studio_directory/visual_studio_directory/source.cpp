#include <SFML/Graphics.hpp>
#include <string>
int main()
{   
    
    //initialisation
    int tellertest = 0; 

    sf::RenderWindow window(sf::VideoMode(1920,1080), "SFML works!",sf::Style::Fullscreen);
    sf::Vector2u screenSize = window.getSize();

    sf::Texture texture;
    if (!texture.loadFromFile("images/fist.jpg"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    sf::Font font;
    if (!font.loadFromFile("fonts/Arial.ttf"))
        return EXIT_FAILURE;
    sf::Text tekstObj("", font, 50);
   
    //framecapping
    sf::Clock klokje; 
    const sf::Time frameTime = sf::seconds(1.0f / 60.0f);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //frames
        window.clear();
        sf::Time elapsed = klokje.restart();

        //content
        window.draw(sprite);
        std::string tekstje = "Fist bump counter: " + std::to_string(tellertest);
        tellertest++;
        tekstObj.setString(tekstje);
        window.draw(tekstObj);


        //ending loop
        window.display();
        sf::sleep(frameTime - elapsed);


    }
    window.close();
    return EXIT_SUCCESS;
}


void initialise() {
    


}




