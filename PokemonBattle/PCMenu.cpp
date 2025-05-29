#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "pokedex.h"

// Declaración de la función de combate
void mostrarCombate(const std::vector<int>& equipoJugador, const std::vector<int>& equipoRival);
void testCombate();

struct MiniaturaPokemon {
    sf::Sprite sprite;
    sf::IntRect frame1;
    sf::IntRect frame2;
    float animTimer = 0.f;
    bool showingFrame1 = true;
    int index; // de 1 a 151
};

struct EquipoSlot {
    bool ocupado = false;
    int indexPokemon = -1;
};

const std::vector<std::pair<int, int>> coordenadasColumnas = {
    {0, 34}, {134, 168}, {268, 302}, {402, 436}, {536, 570},
    {670, 704}, {804, 838}, {938, 972}, {1071, 1105}, {1205, 1239},
    {1339, 1373}, {1473, 1508}, {1608, 1641}, {1741, 1775}, {1875, 1909}
};

const std::vector<int> coordenadasFilas = {
    0, 168, 337, 505, 674, 842, 1011, 1179, 1347, 1516, 1684
};

std::vector<MiniaturaPokemon> cargarMiniaturas(sf::Texture& texturePokemon, float escala) {
    std::vector<MiniaturaPokemon> miniaturas;
    const int spriteWidth = 32;
    const int spriteHeight = 32;
    int totalPokemons = 151;
    int columnas = 15;

    for (int i = 0; i < totalPokemons; ++i) {
        int fila = i / columnas;
        int columna = i % columnas;

        if (fila >= (int)coordenadasFilas.size() || columna >= (int)coordenadasColumnas.size())
            continue;

        MiniaturaPokemon m;
        m.sprite.setTexture(texturePokemon);

        int x1 = coordenadasColumnas[columna].first;
        int x2 = coordenadasColumnas[columna].second;
        int y = coordenadasFilas[fila];

        m.frame1 = sf::IntRect(x1, y, spriteWidth, spriteHeight);
        m.frame2 = sf::IntRect(x2, y, spriteWidth, spriteHeight);
        m.sprite.setTextureRect(m.frame1);

        m.sprite.setScale(escala, escala);
        m.sprite.setPosition(60.f + columna * (spriteWidth * escala + 10), 60.f + fila * (spriteHeight * escala + 10));
        m.index = i + 1;
        miniaturas.push_back(m);
    }

    return miniaturas;
}

void dibujarNombre(sf::RenderWindow& window, sf::Texture& letrasTexture, const std::string& nombre, float x, float y) {
    // Coordenadas x para mayúsculas A-Z
    const int coordsMayus[26] = { 171, 178, 185, 192, 199, 206, 213, 220, 226, 233, 240, 247, 254, 261, 268, 275, 282, 289, 296, 302, 309, 316, 323, 330, 337, 343 };

    // Coordenadas x para minúsculas a-z
    const int coordsMinus[26] = { 170, 177, 184, 192, 199, 206, 213, 220, 226, 231, 238, 246, 253, 260, 267, 274, 280, 287, 294, 301, 308, 315, 322, 329, 336, 343 };

    float posX = x;
    for (size_t i = 0; i < nombre.size(); ++i) {
        char c = nombre[i];
        if (!isalpha(c)) continue;

        bool mayus = isupper(c);
        int letraIndex = toupper(c) - 'A';

        // Verificar que el índice esté en rango válido (0-25 para A-Z)
        if (letraIndex < 0 || letraIndex > 25) continue;

        int letraX = mayus ? coordsMayus[letraIndex] : coordsMinus[letraIndex];
        int letraY = mayus ? 123 : 142;
        int letraHeight = mayus ? 9 : 10;

        // Verificar que las coordenadas no excedan los límites del spritesheet
        sf::Vector2u textureSize = letrasTexture.getSize();
        if (letraX + 5 > (int)textureSize.x || letraY + letraHeight > (int)textureSize.y) {
            continue; // Saltar esta letra si está fuera de bounds
        }

        sf::Sprite letra(letrasTexture, sf::IntRect(letraX, letraY, 5, letraHeight));
        letra.setScale(2.0f, 2.0f);
        letra.setPosition(posX, y);
        window.draw(letra);

        // Avanzar posición para la siguiente letra
        posX += 5 * 2.0f + 3.f; // 10px de ancho escalado + 3px de espaciado
    }
}

inline std::string getPokemonName(int index) {
    if (index >= 1 && index <= static_cast<int>(pokedex.size())) {
        return pokedex[index - 1].nombre; // Corregido: usar index-1 ya que el índice va de 1 a 151
    }
    else {
        return "???";
    }
}

// Función para generar equipo rival con Pokémon fuertes (IDs 130-151)
std::vector<int> generarEquipoRival() {
    std::vector<int> pokemonsFuertes;
    // Llenar vector con IDs de 130 a 151 (Pokémon legendarios y muy fuertes)
    for (int i = 130; i <= 151; ++i) {
        pokemonsFuertes.push_back(i);
    }

    // Generar números aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(pokemonsFuertes.begin(), pokemonsFuertes.end(), gen);

    // Tomar los primeros 6
    std::vector<int> equipoRival(pokemonsFuertes.begin(), pokemonsFuertes.begin() + 6);
    return equipoRival;
}

// Función para verificar si el equipo está completo (6 Pokémon)
bool equipoCompleto(const std::vector<EquipoSlot>& equipo) {
    int contador = 0;
    for (const auto& slot : equipo) {
        if (slot.ocupado) contador++;
    }
    return contador == 6;
}

// Función para obtener el equipo del jugador como vector de índices
std::vector<int> obtenerEquipoJugador(const std::vector<EquipoSlot>& equipo) {
    std::vector<int> equipoJugador;
    for (const auto& slot : equipo) {
        if (slot.ocupado) {
            equipoJugador.push_back(slot.indexPokemon);
        }
    }
    return equipoJugador;
}

// Función para verificar si un Pokémon ya está en el equipo
bool pokemonYaEnEquipo(const std::vector<EquipoSlot>& equipo, int indexPokemon) {
    for (const auto& slot : equipo) {
        if (slot.ocupado && slot.indexPokemon == indexPokemon) {
            return true;
        }
    }
    return false;
}

void inicializarPokedex();

void mostrarPCMenu() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "PC Pokemon", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);

    sf::Texture texturePokemons, textureUI, textureUIBTT;
    if (!texturePokemons.loadFromFile("C:\\Proyectos\\PokemonBattle\\x64\\Debug\\resources\\sprites\\pc_pokemon.png") ||
        !textureUI.loadFromFile("C:\\Proyectos\\PokemonBattle\\x64\\Debug\\resources\\sprites\\Interfaces.png") ||
        !textureUIBTT.loadFromFile("C:\\Proyectos\\PokemonBattle\\x64\\Debug\\resources\\sprites\\uibtt.png")) {
        std::cerr << "Error cargando texturas\n";
        return;
    }

    sf::Sprite fondo(textureUI, sf::IntRect(246, 1, 240, 160));
    sf::Vector2u screenSize = window.getSize();
    fondo.setScale((float)screenSize.x / 240.f, (float)screenSize.y / 160.f);

    auto miniaturas = cargarMiniaturas(texturePokemons, 2.5f);
    sf::Sprite cursor(textureUI, sf::IntRect(512, 2, 24, 24));
    cursor.setScale(2.f, 2.f);

    // Slots del equipo (6 slots)
    std::vector<EquipoSlot> equipo(6);
    sf::Vector2f posSlots(1450.f, 100.f);
    float espacioVertical = 40.f;

    // Configurar la flecha de combate (solo visible cuando el equipo está completo)
    sf::Sprite flecha(textureUI, sf::IntRect(549, 9, 10, 14));
    flecha.setScale(2.5f, 2.5f);
    sf::Vector2f posFlecha(posSlots.x + 15.f, posSlots.y + 6 * espacioVertical + 10.f);
    flecha.setPosition(posFlecha);

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();

            // CLIC IZQUIERDO: Seleccionar Pokémon o iniciar combate
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mouse((float)event.mouseButton.x, (float)event.mouseButton.y);

                // Verificar clic en flecha de combate (solo si equipo completo)
                if (equipoCompleto(equipo) && flecha.getGlobalBounds().contains(mouse)) {
                    // Generar equipo rival
                    std::vector<int> equipoRival = generarEquipoRival();
                    std::vector<int> equipoJugador = obtenerEquipoJugador(equipo);

                    // Mostrar equipos por consola
                    std::cout << "Equipo jugador seleccionado:\n";
                    for (int id : equipoJugador) std::cout << id << " ";
                    std::cout << "\n";

                    std::cout << "Equipo rival generado:\n";
                    for (int id : equipoRival) std::cout << id << " ";
                    std::cout << "\n";

                    // Cerrar ventana actual
                    window.close();

                    // Iniciar combate
                    mostrarCombate(equipoJugador, equipoRival);
                    return; // Salir de la función
                }

                // Verificar clic en Pokémon para agregar al equipo
                for (const auto& m : miniaturas) {
                    if (m.sprite.getGlobalBounds().contains(mouse)) {
                        // Solo agregar si el equipo no está completo y el Pokémon no está ya en el equipo
                        if (!equipoCompleto(equipo) && !pokemonYaEnEquipo(equipo, m.index)) {
                            for (auto& slot : equipo) {
                                if (!slot.ocupado) {
                                    slot.ocupado = true;
                                    slot.indexPokemon = m.index;
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
            }

            
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                sf::Vector2f mouse((float)event.mouseButton.x, (float)event.mouseButton.y);

                
                for (int i = 0; i < 6; ++i) {
                    float y = posSlots.y + i * espacioVertical;
                    sf::FloatRect slotBounds(posSlots.x, y, 200.f, espacioVertical);

                    if (slotBounds.contains(mouse) && equipo[i].ocupado) {
                        equipo[i].ocupado = false;
                        equipo[i].indexPokemon = -1;
                        break;
                    }
                }
            }
        }

        
        float delta = clock.restart().asSeconds();
        for (auto& m : miniaturas) {
            m.animTimer += delta;
            if (m.animTimer >= 0.5f) {
                m.animTimer = 0.f;
                m.showingFrame1 = !m.showingFrame1;
                m.sprite.setTextureRect(m.showingFrame1 ? m.frame1 : m.frame2);
            }
        }

        
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        cursor.setPosition((float)mousePos.x, (float)mousePos.y);

        
        window.clear();
        window.draw(fondo);

       
        for (const auto& m : miniaturas) {
            window.draw(m.sprite);
        }

        
        for (int i = 0; i < 6; ++i) {
            float y = posSlots.y + i * espacioVertical;
            if (equipo[i].ocupado) {
                
                sf::Sprite pokebola(textureUIBTT, sf::IntRect(132, 64, 9, 9));
                pokebola.setScale(3.f, 3.f);
                pokebola.setPosition(posSlots.x, y);
                window.draw(pokebola);
            }
            else {
                // Slot vacío - mostrar círculo
                sf::Sprite circulo(textureUIBTT, sf::IntRect(122, 64, 9, 9));
                circulo.setScale(3.f, 3.f);
                circulo.setPosition(posSlots.x, y);
                window.draw(circulo);
            }
        }

        
        for (int i = 0; i < 6; ++i) {
            float y = posSlots.y + i * espacioVertical;
            if (equipo[i].ocupado) {
                std::string nombre = getPokemonName(equipo[i].indexPokemon);
                dibujarNombre(window, textureUIBTT, nombre, posSlots.x + 50.f, y);
            }
        }

       
        if (equipoCompleto(equipo)) {
            window.draw(flecha);
        }

        // Dibujar cursor del mouse
        window.draw(cursor);
        window.display();
    }
}