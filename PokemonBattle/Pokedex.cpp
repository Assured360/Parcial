#include "Pokedex.h"
#include <iostream>
#include <algorithm>
#include "pokedex.h"

// Definición global de la pokedex


// Implementación de la función para buscar un Pokémon por número
Pokemon* buscarPokemonPorNumero(int numero) {
    if (numero >= 1 && numero <= static_cast<int>(pokedex.size())) {
        return &pokedex[numero - 1];
    }
    return nullptr;
}

// Base de datos completa de ataques de la Primera Generación
std::vector<Ataque> listaAtaques = {
    // Ataques Normales
    {"Placaje", "Normal", 40, 100, 35},           // 0
    {"Karate", "Normal", 50, 100, 25},            // 1
    {"Golpe Cabeza", "Normal", 70, 100, 15},      // 2
    {"Cornada", "Normal", 65, 100, 25},           // 3
    {"Stomping", "Normal", 65, 100, 20},          // 4
    {"Patada Doble", "Normal", 30, 100, 30},      // 5
    {"Megapatada", "Normal", 120, 75, 5},         // 6
    {"Patada Salto", "Normal", 100, 95, 10},      // 7
    {"Patada Giro", "Normal", 60, 85, 15},        // 8
    {"Arañazo", "Normal", 40, 100, 35},           // 9
    {"Agarre", "Normal", 55, 100, 30},            // 10
    {"Guillotina", "Normal", 999, 30, 5},         // 11
    {"Viento Cortante", "Normal", 80, 100, 10},   // 12
    {"Danza Espada", "Normal", 0, 100, 20},       // 13
    {"Corte", "Normal", 50, 95, 30},              // 14
    {"Ráfaga", "Normal", 40, 100, 35},            // 15
    {"Ataque Ala", "Normal", 60, 100, 35},        // 16
    {"Torbellino", "Normal", 35, 85, 15},         // 17
    {"Vuelo", "Normal", 90, 95, 15},              // 18
    {"Constricción", "Normal", 10, 100, 35},      // 19
    {"Látigo", "Normal", 0, 100, 30},             // 20
    {"Pisotón", "Normal", 65, 100, 20},           // 21
    {"Doble Patada", "Normal", 30, 100, 30},      // 22
    {"Megapatada", "Normal", 120, 75, 5},         // 23
    {"Patada Salto", "Normal", 100, 95, 10},      // 24
    {"Patada Giro", "Normal", 60, 85, 15},        // 25
    {"Arena", "Normal", 0, 100, 15},              // 26
    {"Golpe Cabeza", "Normal", 70, 100, 15},      // 27
    {"Cornada", "Normal", 65, 100, 25},           // 28
    {"Embestida", "Normal", 90, 85, 20},          // 29
    {"Látigo Cepa", "Normal", 45, 100, 25},       // 30
    {"Pisotón", "Normal", 65, 100, 20},           // 31
    {"Doble Patada", "Normal", 30, 100, 30},      // 32
    {"Megapatada", "Normal", 120, 75, 5},         // 33
    {"Patada Salto", "Normal", 100, 95, 10},      // 34
    {"Patada Giro", "Normal", 60, 85, 15},        // 35
    {"Hiperrayo", "Normal", 150, 90, 5},          // 36
    {"Picotazo", "Normal", 35, 100, 35},          // 37
    {"Taladro", "Normal", 80, 100, 20},           // 38
    {"Sumisión", "Normal", 80, 80, 20},           // 39
    {"Contador", "Normal", 999, 100, 20},         // 40
    {"Fuerza Sísmica", "Normal", 999, 100, 20},   // 41
    {"Fuerza", "Normal", 80, 100, 15},            // 42
    {"Absorber", "Normal", 20, 100, 25},          // 43
    {"Megaagotar", "Normal", 40, 100, 15},        // 44
    {"Drenadoras", "Normal", 20, 100, 25},        // 45
    {"Crecimiento", "Normal", 0, 100, 20},        // 46
    {"Hoja Afilada", "Normal", 55, 95, 25},       // 47
    {"Rayo Solar", "Normal", 120, 100, 10},       // 48
    {"Polvo Veneno", "Normal", 0, 75, 35},        // 49
    {"Paralizador", "Normal", 0, 75, 30},         // 50
    {"Somnífero", "Normal", 0, 75, 15},           // 51
    {"Danza Pétalo", "Normal", 120, 100, 10},     // 52
    {"Disparo Demora", "Normal", 40, 100, 20},    // 53
    {"Disable", "Normal", 0, 100, 20},            // 54
    {"Ácido", "Normal", 40, 100, 30},             // 55
    {"Ascuas", "Fuego", 40, 100, 25},             // 56
    {"Lanzallamas", "Fuego", 90, 100, 15},        // 57
    {"Niebla", "Hielo", 0, 100, 30},              // 58
    {"Pistola Agua", "Agua", 40, 100, 25},        // 59
    {"Hidrobomba", "Agua", 110, 80, 5},           // 60
    {"Surf", "Agua", 90, 100, 15},                // 61
    {"Rayo Hielo", "Hielo", 90, 100, 10},         // 62
    {"Ventisca", "Hielo", 110, 70, 5},            // 63
    {"Psicorrayo", "Psíquico", 65, 100, 20},      // 64
    {"Rayo Burbuja", "Agua", 65, 100, 20},        // 65
    {"Rayo Aurora", "Hielo", 65, 100, 20},        // 66
    {"Hiperrayo", "Normal", 150, 90, 5},          // 67
    {"Picotazo", "Volador", 35, 100, 35},         // 68
    {"Ataque Taladro", "Volador", 80, 100, 20},   // 69
    {"Sumisión", "Lucha", 80, 80, 20},            // 70
    {"Patada Baja", "Lucha", 65, 100, 20},        // 71
    {"Contador", "Lucha", 999, 100, 20},          // 72
    {"Fuerza Sísmica", "Lucha", 999, 100, 20},    // 73
    {"Fuerza", "Normal", 80, 100, 15},            // 74
    {"Absorber", "Planta", 20, 100, 25},          // 75
    {"Megaagotar", "Planta", 40, 100, 15},        // 76
    {"Drenadoras", "Planta", 20, 100, 25},        // 77
    {"Crecimiento", "Normal", 0, 100, 20},        // 78
    {"Hoja Afilada", "Planta", 55, 95, 25},       // 79
    {"Rayo Solar", "Planta", 120, 100, 10},       // 80
    {"Polvo Veneno", "Veneno", 0, 75, 35},        // 81
    {"Paralizador", "Planta", 0, 75, 30},         // 82
    {"Somnífero", "Planta", 0, 75, 15},           // 83
    {"Danza Pétalo", "Planta", 120, 100, 10},     // 84
    {"Disparo Demora", "Planta", 40, 100, 20},    // 85
    {"Disable", "Normal", 0, 100, 20},            // 86
    {"Ácido", "Veneno", 40, 100, 30},             // 87
    {"Ascuas", "Fuego", 40, 100, 25},             // 88
    {"Lanzallamas", "Fuego", 90, 100, 15},        // 89
    {"Niebla", "Hielo", 0, 100, 30},              // 90
    {"Pistola Agua", "Agua", 40, 100, 25},        // 91
    {"Hidrobomba", "Agua", 110, 80, 5},           // 92
    {"Surf", "Agua", 90, 100, 15},                // 93
    {"Rayo Hielo", "Hielo", 90, 100, 10},         // 94
    {"Ventisca", "Hielo", 110, 70, 5},            // 95
    {"Psicorrayo", "Psíquico", 65, 100, 20},      // 96
    {"Rayo Burbuja", "Agua", 65, 100, 20},        // 97
    {"Rayo Aurora", "Hielo", 65, 100, 20},        // 98
    {"Impactrueno", "Eléctrico", 40, 100, 30},    // 99
    {"Rayo", "Eléctrico", 90, 100, 15},           // 100
    {"Onda Trueno", "Eléctrico", 0, 90, 20},      // 101
    {"Trueno", "Eléctrico", 110, 70, 10},         // 102
    {"Lanzarrocas", "Roca", 50, 90, 15},          // 103
    {"Terremoto", "Tierra", 100, 100, 10},        // 104
    {"Fisura", "Tierra", 999, 30, 5},             // 105
    {"Excavar", "Tierra", 80, 100, 10},           // 106
    {"Tóxico", "Veneno", 0, 90, 10},              // 107
    {"Confusión", "Psíquico", 50, 100, 25},       // 108
    {"Psíquico", "Psíquico", 90, 100, 10},        // 109
    {"Hipnosis", "Psíquico", 0, 60, 20},          // 110
    {"Meditación", "Psíquico", 0, 100, 40},       // 111
    {"Agilidad", "Psíquico", 0, 100, 30},         // 112
    {"Ataque Rápido", "Normal", 40, 100, 30},     // 113
    {"Furia", "Normal", 20, 100, 20},             // 114
    {"Teletransporte", "Psíquico", 0, 100, 20},   // 115
    {"Sombra Nocturna", "Fantasma", 999, 100, 15}, // 116
    {"Mimético", "Normal", 0, 100, 10},           // 117
    {"Grito", "Normal", 0, 100, 40},              // 118
    {"Joya de Luz", "Normal", 0, 70, 5},          // 119
    {"Psiconda", "Psíquico", 0, 100, 15},         // 120
    {"Recuperación", "Normal", 0, 100, 5},        // 121
    {"Endurecimiento", "Normal", 0, 100, 30},     // 122
    {"Minimizar", "Normal", 0, 100, 10},          // 123
    {"Pantalla de Humo", "Normal", 0, 100, 20},   // 124
    {"Rayo Confuso", "Fantasma", 0, 100, 10},     // 125
    {"Retirada", "Agua", 0, 100, 40},             // 126
    {"Fortaleza", "Normal", 0, 100, 30},          // 127
    {"Barrera", "Psíquico", 0, 100, 20},          // 128
    {"Pantalla de Luz", "Psíquico", 0, 100, 30},  // 129
    {"Neblina", "Hielo", 0, 100, 30},             // 130
    {"Reflejo", "Psíquico", 0, 100, 20},          // 131
    {"Foco Energía", "Normal", 0, 100, 30},       // 132
    {"Venganza", "Normal", 70, 100, 5},           // 133
    {"Metamorfosis", "Normal", 0, 100, 10},       // 134
    {"Mareo", "Normal", 0, 80, 20},               // 135
    {"Espora", "Planta", 0, 100, 15},             // 136
    {"Destello", "Normal", 0, 100, 20},           // 137
    {"Onda Psíquica", "Psíquico", 0, 100, 15},    // 138
    {"Salpicadura", "Normal", 0, 100, 40},        // 139
    {"Transformación", "Normal", 0, 100, 10},     // 140
    {"Autodestrucción", "Normal", 200, 100, 5},   // 141
    {"Explosión", "Normal", 250, 100, 5},         // 142
    {"Golpe Fantasma", "Fantasma", 0, 100, 15},   // 143
    {"Hueso Palo", "Tierra", 65, 85, 20},         // 144
    {"Lanzahuesos", "Tierra", 90, 85, 10},        // 145
    {"Descanso", "Psíquico", 0, 100, 10},         // 146
    {"Avalancha", "Roca", 75, 90, 10},            // 147
    {"Hiper Colmillo", "Normal", 80, 90, 15},     // 148
    {"Afilar", "Normal", 0, 100, 30},             // 149
    {"Conversión", "Normal", 0, 100, 30},         // 150
    {"Triataque", "Normal", 80, 100, 10},         // 151
    {"Supersonido", "Normal", 0, 55, 20},         // 152
    {"Sonicboom", "Normal", 20, 90, 20},          // 153
    {"Anulación", "Psíquico", 0, 100, 20}         // 154
};

// Base de datos completa de los 151 Pokémon de la Primera Generación
std::vector<Pokemon> pokedex = {
    // #001-#009: Starters de Kanto
    {1, "Bulbasaur", "Planta", "Veneno", 45, 49, 49, 45, 65, {listaAtaques[0], listaAtaques[79], listaAtaques[82], listaAtaques[75]}},
    {2, "Ivysaur", "Planta", "Veneno", 60, 62, 63, 60, 80, {listaAtaques[79], listaAtaques[80], listaAtaques[82], listaAtaques[84]}},
    {3, "Venusaur", "Planta", "Veneno", 80, 82, 83, 80, 100, {listaAtaques[79], listaAtaques[80], listaAtaques[84], listaAtaques[104]}},
    {4, "Charmander", "Fuego", "", 39, 52, 43, 65, 50, {listaAtaques[9], listaAtaques[88], listaAtaques[118], listaAtaques[30]}},
    {5, "Charmeleon", "Fuego", "", 58, 64, 58, 80, 65, {listaAtaques[88], listaAtaques[89], listaAtaques[9], listaAtaques[118]}},
    {6, "Charizard", "Fuego", "Volador", 78, 84, 78, 100, 85, {listaAtaques[89], listaAtaques[18], listaAtaques[104], listaAtaques[69]}},
    {7, "Squirtle", "Agua", "", 44, 48, 65, 43, 50, {listaAtaques[0], listaAtaques[91], listaAtaques[20], listaAtaques[126]}},
    {8, "Wartortle", "Agua", "", 59, 63, 80, 58, 65, {listaAtaques[91], listaAtaques[97], listaAtaques[20], listaAtaques[126]}},
    {9, "Blastoise", "Agua", "", 79, 83, 100, 78, 85, {listaAtaques[92], listaAtaques[93], listaAtaques[104], listaAtaques[62]}},

    // #010-#012: Caterpie line
    {10, "Caterpie", "Bicho", "", 45, 30, 35, 45, 20, {listaAtaques[0], listaAtaques[53], listaAtaques[122], listaAtaques[20]}},
    {11, "Metapod", "Bicho", "", 50, 20, 55, 30, 25, {listaAtaques[122], listaAtaques[0], listaAtaques[20], listaAtaques[126]}},
    {12, "Butterfree", "Bicho", "Volador", 60, 45, 50, 70, 90, {listaAtaques[108], listaAtaques[96], listaAtaques[83], listaAtaques[18]}},

    // #013-#015: Weedle line
    {13, "Weedle", "Bicho", "Veneno", 40, 35, 30, 50, 20, {listaAtaques[81], listaAtaques[53], listaAtaques[0], listaAtaques[20]}},
    {14, "Kakuna", "Bicho", "Veneno", 45, 25, 50, 35, 25, {listaAtaques[122], listaAtaques[0], listaAtaques[20], listaAtaques[126]}},
    {15, "Beedrill", "Bicho", "Veneno", 65, 90, 40, 75, 45, {listaAtaques[69], listaAtaques[107], listaAtaques[114], listaAtaques[112]}},

    // #016-#018: Pidgey line
    {16, "Pidgey", "Normal", "Volador", 40, 45, 40, 56, 35, {listaAtaques[0], listaAtaques[15], listaAtaques[26], listaAtaques[113]}},
    {17, "Pidgeotto", "Normal", "Volador", 63, 60, 55, 71, 50, {listaAtaques[15], listaAtaques[17], listaAtaques[113], listaAtaques[112]}},
    {18, "Pidgeot", "Normal", "Volador", 83, 80, 75, 101, 70, {listaAtaques[36], listaAtaques[17], listaAtaques[18], listaAtaques[112]}},

    // #019-#020: Rattata line
    {19, "Rattata", "Normal", "", 30, 56, 35, 72, 25, {listaAtaques[0], listaAtaques[113], listaAtaques[36], listaAtaques[148]}},
    {20, "Raticate", "Normal", "", 55, 81, 60, 97, 50, {listaAtaques[148], listaAtaques[36], listaAtaques[114], listaAtaques[113]}},

    // #021-#022: Spearow line
    {21, "Spearow", "Normal", "Volador", 40, 60, 30, 70, 31, {listaAtaques[68], listaAtaques[114], listaAtaques[113], listaAtaques[118]}},
    {22, "Fearow", "Normal", "Volador", 65, 90, 65, 100, 61, {listaAtaques[69], listaAtaques[36], listaAtaques[112], listaAtaques[18]}},

    // #023-#024: Ekans line
    {23, "Ekans", "Veneno", "", 35, 60, 44, 55, 40, {listaAtaques[19], listaAtaques[87], listaAtaques[20], listaAtaques[118]}},
    {24, "Arbok", "Veneno", "", 60, 95, 69, 80, 65, {listaAtaques[87], listaAtaques[19], listaAtaques[20], listaAtaques[118]}},

    // #025-#026: Pikachu line
    {25, "Pikachu", "Eléctrico", "", 35, 55, 40, 90, 50, {listaAtaques[99], listaAtaques[113], listaAtaques[112], listaAtaques[101]}},
    {26, "Raichu", "Eléctrico", "", 60, 90, 55, 110, 90, {listaAtaques[100], listaAtaques[102], listaAtaques[39], listaAtaques[112]}},

    // #027-#028: Sandshrew line
    {27, "Sandshrew", "Tierra", "", 50, 75, 85, 40, 20, {listaAtaques[9], listaAtaques[26], listaAtaques[106], listaAtaques[127]}},
    {28, "Sandslash", "Tierra", "", 75, 100, 110, 65, 45, {listaAtaques[9], listaAtaques[106], listaAtaques[104], listaAtaques[13]}},

    // #029-#032: Nidoran lines
    {29, "Nidoran?", "Veneno", "", 55, 47, 52, 41, 40, {listaAtaques[9], listaAtaques[81], listaAtaques[0], listaAtaques[22]}},
    {30, "Nidorina", "Veneno", "", 70, 62, 67, 56, 55, {listaAtaques[9], listaAtaques[81], listaAtaques[22], listaAtaques[36]}},
    {31, "Nidoqueen", "Veneno", "Tierra", 90, 92, 87, 76, 75, {listaAtaques[39], listaAtaques[104], listaAtaques[36], listaAtaques[42]}},
    {32, "Nidoran?", "Veneno", "", 46, 57, 40, 50, 40, {listaAtaques[28], listaAtaques[81], listaAtaques[0], listaAtaques[22]}},
    {33, "Nidorino", "Veneno", "", 61, 72, 57, 65, 55, {listaAtaques[28], listaAtaques[81], listaAtaques[22], listaAtaques[36]}},
    {34, "Nidoking", "Veneno", "Tierra", 81, 102, 77, 85, 85, {listaAtaques[28], listaAtaques[104], listaAtaques[36], listaAtaques[42]}},

    // #035-#036: Clefairy line
    {35, "Clefairy", "Hada", "", 70, 45, 48, 35, 60, {listaAtaques[0], listaAtaques[117], listaAtaques[124], listaAtaques[134]}},
    {36, "Clefable", "Hada", "", 95, 70, 73, 60, 95, {listaAtaques[36], listaAtaques[134], listaAtaques[109], listaAtaques[117]}},

    // #037-#038: Vulpix line
    {37, "Vulpix", "Fuego", "", 38, 41, 40, 65, 50, {listaAtaques[88], listaAtaques[113], listaAtaques[20], listaAtaques[118]}},
    {38, "Ninetales", "Fuego", "", 73, 76, 75, 100, 81, {listaAtaques[89], listaAtaques[108], listaAtaques[96], listaAtaques[36]}},

    // #039-#040: Jigglypuff line
    {39, "Jigglypuff", "Normal", "Hada", 115, 45, 20, 20, 45, {listaAtaques[0], listaAtaques[118], listaAtaques[86], listaAtaques[36]}},
    {40, "Wigglytuff", "Normal", "Hada", 140, 70, 45, 45, 85, {listaAtaques[36], listaAtaques[39], listaAtaques[22], listaAtaques[109]}},

    // #041-#042: Zubat line
    {41, "Zubat", "Veneno", "Volador", 40, 45, 35, 55, 30, {listaAtaques[75], listaAtaques[152], listaAtaques[108], listaAtaques[110]}},
    {42, "Golbat", "Veneno", "Volador", 75, 80, 70, 90, 65, {listaAtaques[16], listaAtaques[152], listaAtaques[108], listaAtaques[110]}},

    // #043-#045: Oddish line
    {43, "Oddish", "Planta", "Veneno", 45, 50, 55, 30, 75, {listaAtaques[75], listaAtaques[81], listaAtaques[87], listaAtaques[83]}},
    {44, "Gloom", "Planta", "Veneno", 60, 65, 70, 40, 85, {listaAtaques[84], listaAtaques[81], listaAtaques[87], listaAtaques[83]}},
    {45, "Vileplume", "Planta", "Veneno", 75, 80, 85, 50, 110, {listaAtaques[84], listaAtaques[80], listaAtaques[87], listaAtaques[83]}},

    // #046-#047: Paras line
    {46, "Paras", "Bicho", "Planta", 35, 70, 55, 25, 45, {listaAtaques[9], listaAtaques[81], listaAtaques[83], listaAtaques[79]}},
    {47, "Parasect", "Bicho", "Planta", 60, 95, 80, 30, 60, {listaAtaques[9], listaAtaques[79], listaAtaques[83], listaAtaques[80]}},

    // #048-#049: Venonat line
    {48, "Venonat", "Bicho", "Veneno", 60, 55, 50, 45, 40, {listaAtaques[0], listaAtaques[86], listaAtaques[96], listaAtaques[83]}},
    {49, "Venomoth", "Bicho", "Veneno", 70, 65, 60, 90, 90, {listaAtaques[15], listaAtaques[96], listaAtaques[83], listaAtaques[109]}},

    // #050-#051: Diglett line
    {50, "Diglett", "Tierra", "", 10, 55, 25, 95, 35, {listaAtaques[9], listaAtaques[106], listaAtaques[26], listaAtaques[104]}},
    {51, "Dugtrio", "Tierra", "", 35, 100, 50, 120, 50, {listaAtaques[9], listaAtaques[106], listaAtaques[104], listaAtaques[105]}},

    // #052-#053: Meowth line
    {52, "Meowth", "Normal", "", 40, 45, 35, 90, 40, {listaAtaques[9], listaAtaques[68], listaAtaques[118], listaAtaques[113]}},
    {53, "Persian", "Normal", "", 65, 70, 60, 115, 65, {listaAtaques[9], listaAtaques[148], listaAtaques[118], listaAtaques[36]}},

    // #054-#055: Psyduck line
    {54, "Psyduck", "Agua", "", 50, 52, 48, 55, 65, {listaAtaques[9], listaAtaques[91], listaAtaques[86], listaAtaques[108]}},
    {55, "Golduck", "Agua", "Psíquico", 80, 82, 78, 85, 95, {listaAtaques[108], listaAtaques[92], listaAtaques[109], listaAtaques[112]}},

    // #056-#057: Mankey line
    {56, "Mankey", "Lucha", "", 40, 80, 35, 70, 35, {listaAtaques[9], listaAtaques[71], listaAtaques[114], listaAtaques[118]}},
    {57, "Primeape", "Lucha", "", 65, 105, 60, 95, 60, {listaAtaques[1], listaAtaques[39], listaAtaques[114], listaAtaques[118]}},

    // #058-#059: Growlithe line
    {58, "Growlithe", "Fuego", "", 55, 70, 45, 60, 70, {listaAtaques[68], listaAtaques[88], listaAtaques[29], listaAtaques[118]}},
    {59, "Arcanine", "Fuego", "", 90, 110, 80, 95, 100, {listaAtaques[89], listaAtaques[29], listaAtaques[36], listaAtaques[42]}},

    // #060-#062: Poliwag line
    {60, "Poliwag", "Agua", "", 40, 50, 40, 90, 40, {listaAtaques[97], listaAtaques[110], listaAtaques[91], listaAtaques[22]}},
    {61, "Poliwhirl", "Agua", "", 65, 65, 65, 90, 50, {listaAtaques[97], listaAtaques[39], listaAtaques[110], listaAtaques[36]}},
    {62, "Poliwrath", "Agua", "Lucha", 90, 95, 95, 70, 70, {listaAtaques[39], listaAtaques[92], listaAtaques[36], listaAtaques[70]}},

    // #063-#065: Abra line
    {63, "Abra", "Psíquico", "", 25, 20, 15, 90, 105, {listaAtaques[115], listaAtaques[108], listaAtaques[137], listaAtaques[0]}},
    {64, "Kadabra", "Psíquico", "", 40, 35, 30, 105, 120, {listaAtaques[108], listaAtaques[96], listaAtaques[115], listaAtaques[109]}},
    {65, "Alakazam", "Psíquico", "", 55, 50, 45, 120, 135, {listaAtaques[109], listaAtaques[96], listaAtaques[115], listaAtaques[121]}},

    // #066-#068: Machop line
    {66, "Machop", "Lucha", "", 70, 80, 50, 35, 35, {listaAtaques[1], listaAtaques[71], listaAtaques[39], listaAtaques[132]}},
    {67, "Machoke", "Lucha", "", 80, 100, 70, 45, 50, {listaAtaques[1], listaAtaques[39], listaAtaques[70], listaAtaques[132]}},
    {68, "Machamp", "Lucha", "", 90, 130, 80, 55, 65, {listaAtaques[39], listaAtaques[70], listaAtaques[42], listaAtaques[104]}},

    // #069-#071: Bellsprout line
    {69, "Bellsprout", "Planta", "Veneno", 50, 75, 35, 40, 70, {listaAtaques[30], listaAtaques[87], listaAtaques[19], listaAtaques[78]}},
    {70, "Weepinbell", "Planta", "Veneno", 65, 90, 50, 55, 85, {listaAtaques[30], listaAtaques[79], listaAtaques[87], listaAtaques[80]}},
    {71, "Victreebel", "Planta", "Veneno", 80, 105, 65, 70, 100, {listaAtaques[79], listaAtaques[80], listaAtaques[87], listaAtaques[83]}},

    // #072-#073: Tentacool line
    {72, "Tentacool", "Agua", "Veneno", 40, 40, 35, 70, 50, {listaAtaques[87], listaAtaques[19], listaAtaques[97], listaAtaques[110]}},
    {73, "Tentacruel", "Agua", "Veneno", 80, 70, 65, 100, 80, {listaAtaques[92], listaAtaques[87], listaAtaques[36], listaAtaques[110]}},

    // #074-#076: Geodude line
    {74, "Geodude", "Roca", "Tierra", 40, 80, 100, 20, 30, {listaAtaques[0], listaAtaques[103], listaAtaques[127], listaAtaques[122]}},
    {75, "Graveler", "Roca", "Tierra", 55, 95, 115, 35, 45, {listaAtaques[103], listaAtaques[104], listaAtaques[141], listaAtaques[127]}},
    {76, "Golem", "Roca", "Tierra", 80, 120, 130, 45, 55, {listaAtaques[104], listaAtaques[103], listaAtaques[142], listaAtaques[105]}},

    // #077-#078: Ponyta line
    {77, "Ponyta", "Fuego", "", 50, 85, 55, 90, 65, {listaAtaques[88], listaAtaques[31], listaAtaques[29], listaAtaques[112]}},
    {78, "Rapidash", "Fuego", "", 65, 100, 70, 105, 80, {listaAtaques[89], listaAtaques[29], listaAtaques[31], listaAtaques[112]}},

    // #079-#080: Slowpoke line
    {79, "Slowpoke", "Agua", "Psíquico", 90, 65, 65, 15, 40, {listaAtaques[108], listaAtaques[91], listaAtaques[86], listaAtaques[78]}},
    {80, "Slowbro", "Agua", "Psíquico", 95, 75, 110, 30, 100, {listaAtaques[108], listaAtaques[92], listaAtaques[109], listaAtaques[112]}},

    // #081-#082: Magnemite line
    {81, "Magnemite", "Eléctrico", "Acero", 25, 35, 70, 45, 95, {listaAtaques[99], listaAtaques[153], listaAtaques[101], listaAtaques[152]}},
    {82, "Magneton", "Eléctrico", "Acero", 50, 60, 95, 70, 120, {listaAtaques[100], listaAtaques[102], listaAtaques[153], listaAtaques[101]}},

    // #083: Farfetch'd
    {83, "Farfetch'd", "Normal", "Volador", 52, 90, 55, 60, 58, {listaAtaques[68], listaAtaques[14], listaAtaques[13], listaAtaques[112]}},

    // #084-#085: Doduo line
    {84, "Doduo", "Normal", "Volador", 35, 85, 45, 75, 35, {listaAtaques[68], listaAtaques[114], listaAtaques[15], listaAtaques[112]}},
    {85, "Dodrio", "Normal", "Volador", 60, 110, 70, 110, 60, {listaAtaques[69], listaAtaques[15], listaAtaques[114], listaAtaques[112]}},

    // #086-#087: Seel line
    {86, "Seel", "Agua", "", 65, 45, 55, 45, 45, {listaAtaques[2], listaAtaques[91], listaAtaques[66], listaAtaques[29]}},
    {87, "Dewgong", "Agua", "Hielo", 90, 70, 80, 70, 70, {listaAtaques[66], listaAtaques[62], listaAtaques[29], listaAtaques[146]}},

    // #088-#089: Grimer line
    {88, "Grimer", "Veneno", "", 80, 80, 50, 25, 40, {listaAtaques[0], listaAtaques[87], listaAtaques[86], listaAtaques[122]}},
    {89, "Muk", "Veneno", "", 105, 105, 75, 50, 65, {listaAtaques[87], listaAtaques[36], listaAtaques[86], listaAtaques[107]}},

    // #090-#091: Shellder line
    {90, "Shellder", "Agua", "", 30, 65, 100, 40, 45, {listaAtaques[0], listaAtaques[91], listaAtaques[126], listaAtaques[62]}},
    {91, "Cloyster", "Agua", "Hielo", 50, 95, 180, 70, 85, {listaAtaques[62], listaAtaques[36], listaAtaques[147], listaAtaques[142]}},

    // #092-#094: Gastly line
    {92, "Gastly", "Fantasma", "Veneno", 30, 35, 30, 80, 100, {listaAtaques[125], listaAtaques[110], listaAtaques[116], listaAtaques[108]}},
    {93, "Haunter", "Fantasma", "Veneno", 45, 50, 45, 95, 115, {listaAtaques[125], listaAtaques[116], listaAtaques[110], listaAtaques[109]}},
    {94, "Gengar", "Fantasma", "Veneno", 60, 65, 60, 110, 130, {listaAtaques[116], listaAtaques[109], listaAtaques[110], listaAtaques[36]}},

    // #095: Onix
    {95, "Onix", "Roca", "Tierra", 35, 45, 160, 70, 30, {listaAtaques[19], listaAtaques[103], listaAtaques[104], listaAtaques[122]}},

    // #096-#097: Drowzee line
    {96, "Drowzee", "Psíquico", "", 60, 48, 45, 42, 43, {listaAtaques[0], listaAtaques[110], listaAtaques[86], listaAtaques[108]}},
    {97, "Hypno", "Psíquico", "", 85, 73, 70, 67, 73, {listaAtaques[109], listaAtaques[110], listaAtaques[36], listaAtaques[111]}},

    // #098-#099: Krabby line
    {98, "Krabby", "Agua", "", 30, 105, 90, 50, 25, {listaAtaques[10], listaAtaques[16], listaAtaques[122], listaAtaques[0]}},
    {99, "Kingler", "Agua", "", 55, 130, 115, 75, 50, {listaAtaques[10], listaAtaques[36], listaAtaques[11], listaAtaques[42]}},

    // #100-#101: Voltorb line
    {100, "Voltorb", "Eléctrico", "", 40, 30, 50, 100, 55, {listaAtaques[0], listaAtaques[99], listaAtaques[153], listaAtaques[141]}},
    {101, "Electrode", "Eléctrico", "", 60, 50, 70, 150, 80, {listaAtaques[100], listaAtaques[153], listaAtaques[137], listaAtaques[142]}},

    // #102-#103: Exeggcute line
    {102, "Exeggcute", "Planta", "Psíquico", 60, 40, 80, 40, 60, {listaAtaques[129], listaAtaques[108], listaAtaques[47], listaAtaques[80]}},
    {103, "Exeggutor", "Planta", "Psíquico", 95, 95, 85, 55, 125, {listaAtaques[80], listaAtaques[109], listaAtaques[31], listaAtaques[36]}},

    // #104-#105: Cubone line
    {104, "Cubone", "Tierra", "", 50, 50, 95, 35, 40, {listaAtaques[144], listaAtaques[27], listaAtaques[118], listaAtaques[114]}},
    {105, "Marowak", "Tierra", "", 60, 80, 110, 45, 50, {listaAtaques[144], listaAtaques[145], listaAtaques[132], listaAtaques[114]}},

    // #106-#107: Hitmon- line
    {106, "Hitmonlee", "Lucha", "", 50, 120, 53, 87, 35, {listaAtaques[23], listaAtaques[24], listaAtaques[132], listaAtaques[112]}},
    {107, "Hitmonchan", "Lucha", "", 50, 105, 79, 76, 35, {listaAtaques[1], listaAtaques[21], listaAtaques[132], listaAtaques[112]}},

    // #108: Lickitung
    {108, "Lickitung", "Normal", "", 90, 55, 75, 30, 60, {listaAtaques[125], listaAtaques[86], listaAtaques[39], listaAtaques[0]}},

    // #109-#110: Koffing line
    {109, "Koffing", "Veneno", "", 40, 65, 95, 35, 60, {listaAtaques[0], listaAtaques[124], listaAtaques[87], listaAtaques[141]}},
    {110, "Weezing", "Veneno", "", 65, 90, 120, 60, 85, {listaAtaques[124], listaAtaques[36], listaAtaques[87], listaAtaques[142]}},

    // #111-#112: Rhyhorn line
    {111, "Rhyhorn", "Tierra", "Roca", 80, 85, 95, 25, 30, {listaAtaques[28], listaAtaques[31], listaAtaques[29], listaAtaques[118]}},
    {112, "Rhydon", "Tierra", "Roca", 105, 130, 120, 40, 45, {listaAtaques[28], listaAtaques[104], listaAtaques[36], listaAtaques[42]}},

    // #113: Chansey
    {113, "Chansey", "Normal", "", 250, 5, 5, 50, 35, {listaAtaques[0], listaAtaques[36], listaAtaques[121], listaAtaques[117]}},

    // #114: Tangela
    {114, "Tangela", "Planta", "", 65, 55, 115, 60, 100, {listaAtaques[19], listaAtaques[79], listaAtaques[80], listaAtaques[83]}},

    // #115: Kangaskhan
    {115, "Kangaskhan", "Normal", "", 105, 95, 80, 90, 40, {listaAtaques[0], listaAtaques[23], listaAtaques[36], listaAtaques[104]}},

    // #116-#117: Horsea line
    {116, "Horsea", "Agua", "", 30, 40, 70, 60, 70, {listaAtaques[97], listaAtaques[124], listaAtaques[112], listaAtaques[91]}},
    {117, "Seadra", "Agua", "", 55, 65, 95, 85, 95, {listaAtaques[92], listaAtaques[124], listaAtaques[112], listaAtaques[36]}},

    // #118-#119: Goldeen line
    {118, "Goldeen", "Agua", "", 45, 67, 60, 63, 35, {listaAtaques[68], listaAtaques[28], listaAtaques[16], listaAtaques[91]}},
    {119, "Seaking", "Agua", "", 80, 92, 65, 68, 65, {listaAtaques[28], listaAtaques[92], listaAtaques[16], listaAtaques[36]}},

    // #120-#121: Staryu line
    {120, "Staryu", "Agua", "", 30, 45, 55, 85, 70, {listaAtaques[0], listaAtaques[91], listaAtaques[121], listaAtaques[96]}},
    {121, "Starmie", "Agua", "Psíquico", 60, 75, 85, 115, 100, {listaAtaques[92], listaAtaques[109], listaAtaques[96], listaAtaques[121]}},

    // #122: Mr. Mime
    {122, "Mr. Mime", "Psíquico", "Hada", 40, 45, 65, 90, 100, {listaAtaques[108], listaAtaques[128], listaAtaques[129], listaAtaques[117]}},

    // #123: Scyther
    {123, "Scyther", "Bicho", "Volador", 70, 110, 80, 105, 55, {listaAtaques[14], listaAtaques[13], listaAtaques[112], listaAtaques[16]}},

    // #124: Jynx
    {124, "Jynx", "Hielo", "Psíquico", 65, 50, 35, 95, 115, {listaAtaques[108], listaAtaques[110], listaAtaques[62], listaAtaques[109]}},

    // #125: Electabuzz
    {125, "Electabuzz", "Eléctrico", "", 65, 83, 57, 105, 95, {listaAtaques[100], listaAtaques[102], listaAtaques[39], listaAtaques[112]}},

    // #126: Magmar
    {126, "Magmar", "Fuego", "", 65, 95, 57, 93, 100, {listaAtaques[89], listaAtaques[39], listaAtaques[36], listaAtaques[124]}},

    // #127: Pinsir
    {127, "Pinsir", "Bicho", "", 65, 125, 100, 85, 55, {listaAtaques[10], listaAtaques[11], listaAtaques[132], listaAtaques[39]}},

    // #128: Tauros
    {128, "Tauros", "Normal", "", 75, 100, 95, 110, 40, {listaAtaques[0], listaAtaques[29], listaAtaques[36], listaAtaques[104]}},

    // #129-#130: Magikarp line
    {129, "Magikarp", "Agua", "", 20, 10, 55, 80, 15, {listaAtaques[139], listaAtaques[0], listaAtaques[18], listaAtaques[114]}},
    {130, "Gyarados", "Agua", "Volador", 95, 125, 79, 81, 60, {listaAtaques[92], listaAtaques[36], listaAtaques[18], listaAtaques[104]}},

    // #131: Lapras
    {131, "Lapras", "Agua", "Hielo", 130, 85, 80, 60, 85, {listaAtaques[93], listaAtaques[62], listaAtaques[109], listaAtaques[36]}},

    // #132: Ditto
    {132, "Ditto", "Normal", "", 48, 48, 48, 48, 48, {listaAtaques[140], listaAtaques[0], listaAtaques[117], listaAtaques[134]}},

    // #133-#136: Eevee evolutions
    {133, "Eevee", "Normal", "", 55, 55, 50, 55, 45, {listaAtaques[0], listaAtaques[20], listaAtaques[113], listaAtaques[36]}},
    {134, "Vaporeon", "Agua", "", 130, 65, 60, 65, 110, {listaAtaques[92], listaAtaques[62], listaAtaques[36], listaAtaques[110]}},
    {135, "Jolteon", "Eléctrico", "", 65, 65, 60, 130, 110, {listaAtaques[100], listaAtaques[102], listaAtaques[36], listaAtaques[22]}},
    {136, "Flareon", "Fuego", "", 65, 130, 60, 65, 95, {listaAtaques[89], listaAtaques[36], listaAtaques[22], listaAtaques[124]}},

    // #137: Porygon
    {137, "Porygon", "Normal", "", 65, 60, 70, 40, 85, {listaAtaques[0], listaAtaques[96], listaAtaques[150], listaAtaques[121]}},

    // #138-#139: Omanyte line
    {138, "Omanyte", "Roca", "Agua", 35, 40, 100, 35, 90, {listaAtaques[19], listaAtaques[91], listaAtaques[126], listaAtaques[62]}},
    {139, "Omastar", "Roca", "Agua", 70, 60, 125, 55, 115, {listaAtaques[92], listaAtaques[36], listaAtaques[62], listaAtaques[31]}},

    // #140-#141: Kabuto line
    {140, "Kabuto", "Roca", "Agua", 30, 80, 90, 55, 55, {listaAtaques[9], listaAtaques[75], listaAtaques[122], listaAtaques[91]}},
    {141, "Kabutops", "Roca", "Agua", 60, 115, 105, 80, 65, {listaAtaques[9], listaAtaques[14], listaAtaques[92], listaAtaques[36]}},

    // #142: Aerodactyl
    {142, "Aerodactyl", "Roca", "Volador", 80, 105, 65, 130, 60, {listaAtaques[16], listaAtaques[147], listaAtaques[36], listaAtaques[29]}},

    // #143: Snorlax
    {143, "Snorlax", "Normal", "", 160, 110, 65, 30, 65, {listaAtaques[39], listaAtaques[36], listaAtaques[146], listaAtaques[104]}},

    // #144-#146: Legendary Birds
    {144, "Articuno", "Hielo", "Volador", 90, 85, 100, 85, 95, {listaAtaques[62], listaAtaques[95], listaAtaques[18], listaAtaques[112]}},
    {145, "Zapdos", "Eléctrico", "Volador", 90, 90, 85, 100, 125, {listaAtaques[100], listaAtaques[102], listaAtaques[18], listaAtaques[112]}},
    {146, "Moltres", "Fuego", "Volador", 90, 100, 90, 90, 125, {listaAtaques[89], listaAtaques[18], listaAtaques[36], listaAtaques[124]}},

    // #147-#149: Dratini line
    {147, "Dratini", "Dragón", "", 41, 64, 45, 50, 50, {listaAtaques[19], listaAtaques[101], listaAtaques[112], listaAtaques[118]}},
    { 148, "Dragonair", "Dragón", "", 61, 84, 65, 70, 70, {listaAtaques[19], listaAtaques[101], listaAtaques[112], listaAtaques[36]} },
    { 149, "Dragonite", "Dragón", "Volador", 91, 134, 95, 80, 100, {listaAtaques[36], listaAtaques[18], listaAtaques[104], listaAtaques[102]} },

    // #150-#151: Legendary Psychic
    { 150, "Mewtwo", "Psíquico", "", 106, 110, 90, 130, 154, {listaAtaques[109], listaAtaques[96], listaAtaques[36], listaAtaques[121]} },
    { 151, "Mew", "Psíquico", "", 100, 100, 100, 100, 100, {listaAtaques[109], listaAtaques[115], listaAtaques[134], listaAtaques[140]} }
};
 