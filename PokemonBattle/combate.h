#pragma once
#include <vector>
#include <string>

// Versi�n de prueba de la interfaz de combate
void testCombate(const std::string& nombreJugador, const std::string& nombreRival);

// Versi�n oficial del combate con l�gica completa
void mostrarCombate(const std::vector<int>& equipoJugadorIds, const std::vector<int>& equipoRivalIds);
