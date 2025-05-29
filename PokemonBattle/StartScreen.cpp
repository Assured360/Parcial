#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <algorithm>

void mostrarStartScreen() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Pokemon Battle", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    sf::Texture texture;
    if (!texture.loadFromFile("C:\\Proyectos\\PokemonBattle\\x64\\Debug\\resources\\sprites\\startscreen.png")) {
        std::cerr << "Error al cargar startscreen.png\n";
        return;
    }

    const int frameWidth = 240;
    const int frameHeight = 160;
    const int frameY = 1683;
    const int framesCount = 3;
    int currentFrame = 0;

    sf::Sprite sprite(texture);
    sprite.setTextureRect(sf::IntRect(8, frameY, frameWidth, frameHeight));

    // Obtener dimensiones de la pantalla
    sf::Vector2u screenSize = window.getSize();

 
    float scaleX = static_cast<float>(screenSize.x) / frameWidth;
    float scaleY = static_cast<float>(screenSize.y) / frameHeight;

    
    float scale = std::min(scaleX, scaleY); 

    sprite.setScale(scale, scale);

    // Centrar el sprite en escala
    float scaledWidth = frameWidth * scale;
    float scaledHeight = frameHeight * scale;
    sprite.setPosition(
        (screenSize.x - scaledWidth) / 2.f,
        (screenSize.y - scaledHeight) / 2.f
    );

    sf::Clock animationClock;
    const sf::Time frameDuration = sf::milliseconds(500);
    bool animationFinished = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && animationFinished) {
                std::cout << "Iniciando el juego...\n";
                window.close();
            }
        }

        if (!animationFinished && animationClock.getElapsedTime() >= frameDuration) {
            currentFrame++;
            if (currentFrame >= framesCount) {
                currentFrame = framesCount - 1;
                animationFinished = true;
            }
            sprite.setTextureRect(sf::IntRect(8 + currentFrame * frameWidth, frameY, frameWidth, frameHeight));
            animationClock.restart();
        }

        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.display();
    }
}