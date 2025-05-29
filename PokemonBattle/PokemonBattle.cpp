#include "StartScreen.hpp"
#include "PCMenu.hpp"
#include "combate.h"

int main() {

    // Mostrar pantalla de inicio y esperar tecla para continuar
    mostrarStartScreen();  // Esta función debe controlar la espera de la tecla

    // Luego mostrar el menú del PC Pokémon
    mostrarPCMenu();

    return 0;
}
