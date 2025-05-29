#pragma once
#include <vector>
#include <string>

// Versión de prueba de la interfaz de combate
void testCombate(const std::string& nombreJugador, const std::string& nombreRival);

// Versión oficial del combate con lógica completa
void mostrarCombate(const std::vector<int>& equipoJugadorIds, const std::vector<int>& equipoRivalIds);
