#include "StartScreen.hpp"
#include "PCMenu.hpp"
#include "combate.h"

int main() {

    // Mostrar pantalla de inicio y esperar tecla para continuar
    mostrarStartScreen();  // Esta funci�n debe controlar la espera de la tecla

    // Luego mostrar el men� del PC Pok�mon
    mostrarPCMenu();

    return 0;
}
