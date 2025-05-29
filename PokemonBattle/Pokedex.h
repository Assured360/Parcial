#ifndef POKEDEX_H
#define POKEDEX_H

#include <string>
#include <vector>

// Estructura para definir un ataque
struct Ataque {
    std::string nombre;
    std::string tipo;
    int poder;
    int precision;
    int pp;

    // Constructor por defecto
    Ataque() : nombre(""), tipo(""), poder(0), precision(0), pp(0) {}

    // Constructor con parámetros
    Ataque(const std::string& n, const std::string& t, int pow, int prec, int puntos)
        : nombre(n), tipo(t), poder(pow), precision(prec), pp(puntos) {
    }
};

// Estructura para definir un Pokémon
struct Pokemon {
    int numero;
    std::string nombre;
    std::string tipo1;
    std::string tipo2;
    int hp;
    int ataque;
    int defensa;
    int velocidad;
    int ataqueEspecial;
    std::vector<Ataque> ataques;

    // Constructor por defecto
    Pokemon() : numero(0), nombre(""), tipo1(""), tipo2(""),
        hp(0), ataque(0), defensa(0), velocidad(0), ataqueEspecial(0) {
    }

    // Constructor con parámetros
    Pokemon(int num, const std::string& nom, const std::string& t1, const std::string& t2,
        int vida, int att, int def, int vel, int attEsp, const std::vector<Ataque>& movs)
        : numero(num), nombre(nom), tipo1(t1), tipo2(t2),
        hp(vida), ataque(att), defensa(def), velocidad(vel), ataqueEspecial(attEsp), ataques(movs) {
    }
};

// Declaración externa de variables globales definidas en Pokedex.cpp
extern std::vector<Ataque> listaAtaques;
extern std::vector<Pokemon> pokedex;

// Declaración de funciones que podrían ser útiles (opcional)
// Estas funciones se pueden implementar en Pokedex.cpp o en otros archivos

// Función para buscar un Pokémon por número
Pokemon* buscarPokemonPorNumero(int numero);

// Función para buscar un Pokémon por nombre
Pokemon* buscarPokemonPorNombre(const std::string& nombre);

// Función para mostrar información básica de un Pokémon
void mostrarPokemon(const Pokemon& pokemon);

// Función para mostrar la lista completa de Pokémon
void mostrarPokedexCompleta();

// Función para buscar ataques por tipo
std::vector<Ataque*> buscarAtaquesPorTipo(const std::string& tipo);

// Función para obtener Pokémon por tipo
std::vector<Pokemon*> obtenerPokemonPorTipo(const std::string& tipo);

// Función para inicializar la Pokédex (si se necesita alguna configuración especial)
void inicializarPokedex();

#endif // POKEDEX_H