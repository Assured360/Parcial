#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cctype>
#include <random>
#include <thread>
#include <chrono>
#include "pokedex.h"

// ------------------- ESTRUCTURAS -------------------
struct PokemonSpriteCoords {
    int frontalX, frontalY;
    int backX, backY;
};

std::map<std::string, PokemonSpriteCoords> spriteCoords = {
    {"Charmander", {192, 0, 192, 64}},
    {"Bulbasaur", {0, 0, 0, 64}},
};

enum EstadoCombate {
    SELECCION_ATAQUE,
    EJECUTANDO_ATAQUE_JUGADOR,
    EJECUTANDO_ATAQUE_RIVAL,
    MENSAJE,
    CAMBIO_POKEMON,
    POKEMON_DERROTADO,
    FIN_COMBATE
};

struct PokemonCombate {
    Pokemon* pokemon;
    int vidaActual;
    int vidaMaxima;
    bool derrotado;

    PokemonCombate(Pokemon* p) : pokemon(p), derrotado(false) {
        vidaMaxima = pokemon->hp;
        vidaActual = vidaMaxima;
    }
};

// ------------------- FUNCIONES DE DIBUJO -------------------
void dibujarTextoPersonalizado(sf::RenderWindow& window, sf::Texture& fuente, const std::string& texto, float x, float y) {
    const int ancho = 5;
    float escala = 2.5f;
    float posX = x;

    std::map<char, int> xMayus = {
        {'A',171},{'B',178},{'C',185},{'D',192},{'E',199},{'F',206},{'G',213},{'H',220},{'I',226},{'J',233},
        {'K',240},{'L',247},{'M',254},{'N',261},{'O',268},{'P',275},{'Q',282},{'R',289},{'S',296},{'T',302},
        {'U',309},{'V',316},{'W',323},{'X',330},{'Y',337},{'Z',343}
    };

    std::map<char, int> xMinus = {
        {'a',171},{'b',178},{'c',185},{'d',192},{'e',199},{'f',206},{'g',213},{'h',220},{'i',226},{'j',231},
        {'k',238},{'l',246},{'m',253},{'n',260},{'o',267},{'p',274},{'q',280},{'r',287},{'s',294},{'t',301},
        {'u',308},{'v',315},{'w',322},{'x',329},{'y',336},{'z',343},{'ó',349}
    };

    for (char c : texto) {
        // Verificar que el caracter esté en rango ASCII válido
        if (c < 0 || c > 127) {
            continue; // Saltar caracteres no ASCII
        }

        if (std::isupper(c) && xMayus.find(c) != xMayus.end()) {
            int letraX = xMayus[c];
            int letraY = 123;
            int alto = 9;
            sf::Sprite letraSprite(fuente);
            letraSprite.setTextureRect(sf::IntRect(letraX, letraY, ancho, alto));
            letraSprite.setScale(escala, escala);
            letraSprite.setPosition(posX, y);
            window.draw(letraSprite);
            posX += ancho * escala + 3;
        }
        else if (std::islower(c) && xMinus.find(c) != xMinus.end()) {
            int letraX = xMinus[c];
            int letraY = 142;
            int alto = 10;
            sf::Sprite letraSprite(fuente);
            letraSprite.setTextureRect(sf::IntRect(letraX, letraY, ancho, alto));
            letraSprite.setScale(escala, escala);
            letraSprite.setPosition(posX, y);
            window.draw(letraSprite);
            posX += ancho * escala + 3;
        }
        else if (c == ' ') {
            posX += ancho * escala + 3;
        }
        // Caracteres no reconocidos se ignoran
    }
}

// ------------------- FUNCIONES AUXILIARES -------------------
sf::IntRect obtenerRectFrontal(int id) {
    int columna = (id - 1) % 15;
    int fila = (id - 1) / 15;
    return sf::IntRect(columna * 64, fila * 128, 64, 64);
}

sf::IntRect obtenerRectEspalda(int id) {
    int columna = (id - 1) % 15;
    int fila = (id - 1) / 15;
    return sf::IntRect(columna * 64, fila * 128 + 64, 64, 64);
}

// ------------------- FUNCIONES DE COMBATE -------------------
int calcularDano(const PokemonCombate& atacante, const PokemonCombate& defensor, const Ataque& ataque) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> critico(1, 16);
    std::uniform_int_distribution<> precision(1, 100);
    std::uniform_int_distribution<> randomFactor(217, 255);

    // Verificar si el ataque acierta
    if (precision(gen) > ataque.precision) {
        return 0; // Fallo
    }

    // Si el ataque no tiene poder, no hace daño (ataques de estado)
    if (ataque.poder <= 0) {
        return 0;
    }

    int ataqueVal = atacante.pokemon->ataque;
    int defensaVal = defensor.pokemon->defensa;

    // Para ataques especiales, usar ataque especial
    if (ataque.tipo == "Psychic" || ataque.tipo == "Water" || ataque.tipo == "Fire" ||
        ataque.tipo == "Electric" || ataque.tipo == "Grass" || ataque.tipo == "Ice") {
        ataqueVal = atacante.pokemon->ataqueEspecial;
    }

    // Fórmula simplificada de daño de Pokémon
    float nivel = 50.0f; // Nivel fijo para simplicidad
    float dano = ((((2.0f * nivel + 10.0f) / 250.0f) * (ataqueVal / (float)defensaVal) * ataque.poder) + 2.0f);

    // Factor crítico
    if (critico(gen) == 1) {
        dano *= 1.5f;
        std::cout << "¡Golpe crítico!" << std::endl;
    }

    // Factor aleatorio
    dano *= (randomFactor(gen) / 255.0f);

    return std::max(1, (int)dano);
}

int seleccionarAtaqueIA(const PokemonCombate& pokemon) {
    std::random_device rd;
    std::mt19937 gen(rd());

    // Verificar que el Pokémon tenga ataques
    if (pokemon.pokemon->ataques.empty()) {
        return 0; // Sin ataques disponibles
    }

    // Filtrar ataques que tengan poder > 0 (ataques ofensivos)
    std::vector<int> ataquesOfensivos;
    int maxAtaques = std::min(4, (int)pokemon.pokemon->ataques.size());
    for (int i = 0; i < maxAtaques; i++) {
        if (pokemon.pokemon->ataques[i].poder > 0) {
            ataquesOfensivos.push_back(i);
        }
    }

    if (ataquesOfensivos.empty()) {
        // Si no hay ataques ofensivos, elegir cualquiera
        std::uniform_int_distribution<> dis(0, maxAtaques - 1);
        return dis(gen);
    }

    // Elegir un ataque ofensivo al azar
    std::uniform_int_distribution<> dis(0, ataquesOfensivos.size() - 1);
    return ataquesOfensivos[dis(gen)];
}

bool equipoTienePokemonVivo(const std::vector<PokemonCombate>& equipo) {
    for (const auto& p : equipo) {
        if (!p.derrotado) return true;
    }
    return false;
}

int siguientePokemonVivo(const std::vector<PokemonCombate>& equipo, int actual) {
    for (int i = 0; i < equipo.size(); i++) {
        if (i != actual && !equipo[i].derrotado) {
            return i;
        }
    }
    return -1;
}

void dibujarAtaques(sf::RenderWindow& window, sf::Texture& fuente, sf::Texture& texFlechas, const Pokemon* pokemon, int seleccionado) {
    // Posiciones para los 4 ataques en el cuadro (ajustadas para que quepan mejor)
    float posiciones[4][2] = {
        {385, 470},  // Ataque 1 (arriba izquierda)
        {570, 470},  // Ataque 2 (arriba derecha)
        {385, 500},  // Ataque 3 (abajo izquierda)
        {570, 500}   // Ataque 4 (abajo derecha)
    };

    for (int i = 0; i < 4 && i < pokemon->ataques.size(); i++) {
        std::string nombreAtaque = pokemon->ataques[i].nombre;

        // Truncar nombre si es muy largo
        if (nombreAtaque.length() > 12) {
            nombreAtaque = nombreAtaque.substr(0, 12);
        }

        dibujarTextoPersonalizado(window, fuente, nombreAtaque, posiciones[i][0], posiciones[i][1]);

        // Indicador visual para el ataque seleccionado con flecha
        if (i == seleccionado) {
            sf::Sprite flecha(texFlechas, sf::IntRect(550, 10, 8, 12));
            flecha.setScale(2.0f, 2.0f);
            flecha.setPosition(posiciones[i][0] - 25, posiciones[i][1] + 2);
            window.draw(flecha);
        }
    }
}

float calcularPorcentajeVida(const PokemonCombate& pokemon) {
    if (pokemon.vidaMaxima <= 0) return 0.0f;
    return (float)pokemon.vidaActual / (float)pokemon.vidaMaxima;
}

void dibujarNombresPokemon(sf::RenderWindow& window, sf::Texture& fuente, const PokemonCombate& jugador, const PokemonCombate& rival) {
    // Nombre del Pokémon aliado (abajo derecha)
    dibujarTextoPersonalizado(window, fuente, jugador.pokemon->nombre, 540, 320);

    // Nombre del Pokémon rival (arriba izquierda)
    dibujarTextoPersonalizado(window, fuente, rival.pokemon->nombre, 20, 40);

    // Mostrar vida actual/máxima para debug
    std::string vidaJugador = std::to_string(jugador.vidaActual) + "/" + std::to_string(jugador.vidaMaxima);
    std::string vidaRival = std::to_string(rival.vidaActual) + "/" + std::to_string(rival.vidaMaxima);

    dibujarTextoPersonalizado(window, fuente, vidaJugador, 520, 340);
    dibujarTextoPersonalizado(window, fuente, vidaRival, 20, 60);
}

// ------------------- FUNCIÓN DE COMBATE VISUAL -------------------
void mostrarCombate(const std::vector<int>& equipoJugadorIds, const std::vector<int>& equipoRivalIds) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Combate Pokémon");
    window.setFramerateLimit(60);

    // Cargar texturas
    sf::Texture texUI;
    if (!texUI.loadFromFile("C:/Proyectos/PokemonBattle/x64/Debug/resources/sprites/uibtt.png")) {
        std::cerr << "Error al cargar uibtt.png" << std::endl;
        return;
    }

    sf::Texture texPokemon;
    if (!texPokemon.loadFromFile("C:/Proyectos/PokemonBattle/x64/Debug/resources/sprites/pokebat.png")) {
        std::cerr << "Error al cargar pokebat.png" << std::endl;
        return;
    }

    sf::Texture texFlechas;
    if (!texFlechas.loadFromFile("C:/Proyectos/PokemonBattle/x64/Debug/resources/sprites/Interfaces.png")) {
        std::cerr << "Error al cargar Interfaces.png" << std::endl;
        return;
    }

    if (equipoJugadorIds.empty() || equipoRivalIds.empty()) return;

    // Crear equipos de combate
    std::vector<PokemonCombate> equipoJugador;
    std::vector<PokemonCombate> equipoRival;

    for (int id : equipoJugadorIds) {
        Pokemon* p = buscarPokemonPorNumero(id);
        if (p) equipoJugador.emplace_back(p);
    }

    for (int id : equipoRivalIds) {
        Pokemon* p = buscarPokemonPorNumero(id);
        if (p) equipoRival.emplace_back(p);
    }

    if (equipoJugador.empty() || equipoRival.empty()) return;

    // Variables de estado del combate
    EstadoCombate estado = SELECCION_ATAQUE;
    int pokemonJugadorActual = 0;
    int pokemonRivalActual = 0;
    int ataqueSeleccionado = 0;
    std::string mensajeCombate = "Ataque de " + equipoJugador[pokemonJugadorActual].pokemon->nombre;
    sf::Clock clockMensaje;
    bool esperandoInput = false;

    // Sprites base
    sf::Sprite fondo(texUI, sf::IntRect(368, 128, 240, 160));
    fondo.setScale(window.getSize().x / 240.f, window.getSize().y / 160.f);

    sf::Sprite cuadroDialogo(texUI, sf::IntRect(379, 249, 120, 26));
    cuadroDialogo.setScale(3.f, 3.f);
    cuadroDialogo.setPosition(50, 450);

    sf::Sprite cuadroAtaques(texUI, sf::IntRect(526, 249, 1, 1));
    cuadroAtaques.setScale(3.f, 3.f);
    cuadroAtaques.setPosition(400, 450);

    sf::Sprite barraAliado(texUI, sf::IntRect(0, 30, 104, 37));
    barraAliado.setScale(3.f, 3.f);
    barraAliado.setPosition(490, 300);

    sf::Sprite barraRival(texUI, sf::IntRect(0, 0, 100, 29));
    barraRival.setScale(3.f, 3.f);
    barraRival.setPosition(5, 22);

    std::cout << "Combate iniciado!" << std::endl;
    std::cout << "Jugador: " << equipoJugador[pokemonJugadorActual].pokemon->nombre << " (HP: " << equipoJugador[pokemonJugadorActual].vidaActual << ")" << std::endl;
    std::cout << "Rival: " << equipoRival[pokemonRivalActual].pokemon->nombre << " (HP: " << equipoRival[pokemonRivalActual].vidaActual << ")" << std::endl;

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed || (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)) {
                window.close();
            }

            // Manejo de entrada para selección de ataques
            if (estado == SELECCION_ATAQUE && e.type == sf::Event::KeyPressed) {
                int maxAtaques = std::min(4, (int)equipoJugador[pokemonJugadorActual].pokemon->ataques.size());

                if (e.key.code == sf::Keyboard::Up && ataqueSeleccionado >= 2) {
                    ataqueSeleccionado -= 2;
                }
                else if (e.key.code == sf::Keyboard::Down && ataqueSeleccionado < maxAtaques - 2) {
                    ataqueSeleccionado += 2;
                }
                else if (e.key.code == sf::Keyboard::Left && ataqueSeleccionado % 2 == 1) {
                    ataqueSeleccionado--;
                }
                else if (e.key.code == sf::Keyboard::Right && ataqueSeleccionado % 2 == 0 && ataqueSeleccionado + 1 < maxAtaques) {
                    ataqueSeleccionado++;
                }
                else if ((e.key.code == sf::Keyboard::Enter || e.key.code == sf::Keyboard::Z) && ataqueSeleccionado < maxAtaques) {
                    estado = EJECUTANDO_ATAQUE_JUGADOR;
                    clockMensaje.restart();
                    std::cout << "Jugador seleccionó: " << equipoJugador[pokemonJugadorActual].pokemon->ataques[ataqueSeleccionado].nombre << std::endl;
                }
            }
            // Manejo de entrada para mensajes
            else if ((estado == MENSAJE || estado == POKEMON_DERROTADO) && e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Enter || e.key.code == sf::Keyboard::Z) {
                    esperandoInput = false;

                    if (estado == POKEMON_DERROTADO) {
                        // Verificar si hay más Pokémon disponibles
                        if (!equipoTienePokemonVivo(equipoJugador)) {
                            estado = FIN_COMBATE;
                            mensajeCombate = "Has perdido el combate!";
                        }
                        else if (!equipoTienePokemonVivo(equipoRival)) {
                            estado = FIN_COMBATE;
                            mensajeCombate = "Has ganado el combate!";
                        }
                        else {
                            // Cambiar al siguiente Pokémon vivo
                            if (equipoJugador[pokemonJugadorActual].derrotado) {
                                int siguiente = siguientePokemonVivo(equipoJugador, pokemonJugadorActual);
                                if (siguiente != -1) {
                                    pokemonJugadorActual = siguiente;
                                    mensajeCombate = "Ve " + equipoJugador[pokemonJugadorActual].pokemon->nombre + "!";
                                    estado = MENSAJE;
                                    esperandoInput = true;
                                }
                            }
                            else if (equipoRival[pokemonRivalActual].derrotado) {
                                int siguiente = siguientePokemonVivo(equipoRival, pokemonRivalActual);
                                if (siguiente != -1) {
                                    pokemonRivalActual = siguiente;
                                    mensajeCombate = "El rival envia a " + equipoRival[pokemonRivalActual].pokemon->nombre + "!";
                                    estado = MENSAJE;
                                    esperandoInput = true;
                                }
                            }
                        }
                    }
                    else {
                        estado = SELECCION_ATAQUE;
                        mensajeCombate = "Que hara " + equipoJugador[pokemonJugadorActual].pokemon->nombre + "?";
                    }
                }
            }
            else if (estado == FIN_COMBATE && e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Enter || e.key.code == sf::Keyboard::Z) {
                    window.close();
                }
            }
        }

        // Lógica de combate automática
        if (estado == EJECUTANDO_ATAQUE_JUGADOR && clockMensaje.getElapsedTime().asSeconds() > 1.0f) {
            // Verificar que el ataque seleccionado sea válido
            if (ataqueSeleccionado >= 0 && ataqueSeleccionado < equipoJugador[pokemonJugadorActual].pokemon->ataques.size()) {
                // Ejecutar ataque del jugador
                const Ataque& ataque = equipoJugador[pokemonJugadorActual].pokemon->ataques[ataqueSeleccionado];
                int dano = calcularDano(equipoJugador[pokemonJugadorActual], equipoRival[pokemonRivalActual], ataque);

                if (dano > 0) {
                    equipoRival[pokemonRivalActual].vidaActual = std::max(0, equipoRival[pokemonRivalActual].vidaActual - dano);
                    mensajeCombate = equipoJugador[pokemonJugadorActual].pokemon->nombre + " uso " + ataque.nombre + "!";
                    std::cout << "Jugador hizo " << dano << " de daño!" << std::endl;
                    std::cout << "Vida rival: " << equipoRival[pokemonRivalActual].vidaActual << "/" << equipoRival[pokemonRivalActual].vidaMaxima << std::endl;
                }
                else {
                    mensajeCombate = equipoJugador[pokemonJugadorActual].pokemon->nombre + " fallo el ataque!";
                    std::cout << "El ataque del jugador falló!" << std::endl;
                }

                // Verificar si el Pokémon rival fue derrotado
                if (equipoRival[pokemonRivalActual].vidaActual <= 0) {
                    equipoRival[pokemonRivalActual].derrotado = true;
                    estado = POKEMON_DERROTADO;
                    mensajeCombate = equipoRival[pokemonRivalActual].pokemon->nombre + " fue derrotado!";
                    esperandoInput = true;
                    std::cout << equipoRival[pokemonRivalActual].pokemon->nombre << " fue derrotado!" << std::endl;
                }
                else {
                    estado = EJECUTANDO_ATAQUE_RIVAL;
                }
            }
            else {
                // Ataque inválido, volver a selección
                estado = SELECCION_ATAQUE;
                mensajeCombate = "Que hara " + equipoJugador[pokemonJugadorActual].pokemon->nombre + "?";
            }
            clockMensaje.restart();
        }
        else if (estado == EJECUTANDO_ATAQUE_RIVAL && clockMensaje.getElapsedTime().asSeconds() > 2.0f) {
            // Ejecutar ataque del rival
            if (equipoRival[pokemonRivalActual].vidaActual > 0) {
                int ataqueRival = seleccionarAtaqueIA(equipoRival[pokemonRivalActual]);
                const Ataque& ataqueRivalMov = equipoRival[pokemonRivalActual].pokemon->ataques[ataqueRival];
                int danoRival = calcularDano(equipoRival[pokemonRivalActual], equipoJugador[pokemonJugadorActual], ataqueRivalMov);

                if (danoRival > 0) {
                    equipoJugador[pokemonJugadorActual].vidaActual = std::max(0, equipoJugador[pokemonJugadorActual].vidaActual - danoRival);
                    mensajeCombate = equipoRival[pokemonRivalActual].pokemon->nombre + " uso " + ataqueRivalMov.nombre + "!";
                    std::cout << "Rival hizo " << danoRival << " de daño!" << std::endl;
                    std::cout << "Vida jugador: " << equipoJugador[pokemonJugadorActual].vidaActual << "/" << equipoJugador[pokemonJugadorActual].vidaMaxima << std::endl;
                }
                else {
                    mensajeCombate = equipoRival[pokemonRivalActual].pokemon->nombre + " fallo el ataque!";
                    std::cout << "El ataque del rival falló!" << std::endl;
                }

                // Verificar si el Pokémon del jugador fue derrotado
                if (equipoJugador[pokemonJugadorActual].vidaActual <= 0) {
                    equipoJugador[pokemonJugadorActual].derrotado = true;
                    estado = POKEMON_DERROTADO;
                    mensajeCombate = equipoJugador[pokemonJugadorActual].pokemon->nombre + " fue derrotado!";
                    esperandoInput = true;
                    std::cout << equipoJugador[pokemonJugadorActual].pokemon->nombre << " fue derrotado!" << std::endl;
                }
                else {
                    estado = MENSAJE;
                    esperandoInput = true;
                }
            }
            else {
                estado = MENSAJE;
                esperandoInput = true;
            }
            clockMensaje.restart();
        }

        // Dibujo
        window.clear();
        window.draw(fondo);

        // Pokémon actuales (solo si no están derrotados)
        if (!equipoJugador[pokemonJugadorActual].derrotado) {
            sf::Sprite spriteJugador(texPokemon, obtenerRectEspalda(equipoJugadorIds[pokemonJugadorActual]));
            spriteJugador.setScale(3.f, 3.f);
            spriteJugador.setPosition(120, 240);
            window.draw(spriteJugador);
        }

        if (!equipoRival[pokemonRivalActual].derrotado) {
            sf::Sprite spriteRival(texPokemon, obtenerRectFrontal(equipoRivalIds[pokemonRivalActual]));
            spriteRival.setScale(3.f, 3.f);
            spriteRival.setPosition(495, 100);
            window.draw(spriteRival);
        }

        // Barras de vida
        window.draw(barraAliado);
        window.draw(barraRival);

        // Barras verdes proporcionales a la vida
        float porcentajeVidaJugador = calcularPorcentajeVida(equipoJugador[pokemonJugadorActual]);
        float porcentajeVidaRival = calcularPorcentajeVida(equipoRival[pokemonRivalActual]);

        // Determinar color de la barra de vida (verde, amarillo, rojo)
        sf::Color colorVidaJugador = sf::Color::Green;
        sf::Color colorVidaRival = sf::Color::Green;

        if (porcentajeVidaJugador < 0.5f) colorVidaJugador = sf::Color::Yellow;
        if (porcentajeVidaJugador < 0.2f) colorVidaJugador = sf::Color::Red;

        if (porcentajeVidaRival < 0.5f) colorVidaRival = sf::Color::Yellow;
        if (porcentajeVidaRival < 0.2f) colorVidaRival = sf::Color::Red;

        sf::Sprite vidaVerdeAliado(texUI, sf::IntRect(98, 1, 1, 3));
        vidaVerdeAliado.setScale(144.f * porcentajeVidaJugador, 3.f);
        vidaVerdeAliado.setPosition(634, 351);
        vidaVerdeAliado.setColor(colorVidaJugador);
        window.draw(vidaVerdeAliado);

        sf::Sprite vidaVerdeRival(texUI, sf::IntRect(98, 1, 1, 3));
        vidaVerdeRival.setScale(148.f * porcentajeVidaRival, 3.f);
        vidaVerdeRival.setPosition(121, 73);
        vidaVerdeRival.setColor(colorVidaRival);
        window.draw(vidaVerdeRival);

        // Nombres y estadísticas de los Pokémon
        dibujarNombresPokemon(window, texUI, equipoJugador[pokemonJugadorActual], equipoRival[pokemonRivalActual]);

        // UI
        window.draw(cuadroDialogo);

        if (estado == SELECCION_ATAQUE) {
            window.draw(cuadroAtaques);
            dibujarAtaques(window, texUI, texFlechas, equipoJugador[pokemonJugadorActual].pokemon, ataqueSeleccionado);
        }

        // Mensaje de combate
        dibujarTextoPersonalizado(window, texUI, mensajeCombate, 60, 460);

        window.display();
    }
}  