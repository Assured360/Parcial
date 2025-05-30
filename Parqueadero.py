import datetime
import time 

class Parqueadero:
    """
    Clase que representa un sistema de gestión de parqueaderos.
    Gestiona el mapa, la entrada/salida de vehículos, y el cálculo de tarifas.
    * Estructura de clase generada con asistencia de IA para organizar funcionalidades
    """

    # Símbolos para el mapa del parqueadero
    ENTRANCE_SYMBOL = 'E' # Entrada
    EXIT_SYMBOL = 'S' # Salida
    ROAD_SYMBOL = ' ' # Vía
    FREE_SPOT_SYMBOL = 'P' # Espacio libre
    OCCUPIED_SPOT_SYMBOL = 'X' # Espacio ocupado
    PATH_SYMBOL = '*'  # Camino (para visualización temporal)

    def __init__(self, rows: int, cols: int, rate_per_minute: float):
        """
        Inicializa el parqueadero con sus dimensiones y la tarifa por minuto.

        Args:
            rows (int): Número de filas del parqueadero (debe ser >= 8).
            cols (int): Número de columnas del parqueadero (debe ser >= 8).
            rate_per_minute (float): Tarifa de cobro por minuto.
        """
        if rows < 8 or cols < 8:
            print("Advertencia: Las dimensiones del parqueadero deben ser al menos 8x8.")
            print("Ajustando a 8x8 por defecto.")
            rows, cols = 8, 8

        self.rows = rows
        self.cols = cols
        self.rate_per_minute = rate_per_minute
        self.map = [] # Representación de la cuadrícula del parqueadero
        self.vehicles = {} # Diccionario para almacenar vehículos 
        self.entrance_coords = (0, 0) # Coordenadas de la entrada
        self.exit_coords = (self.rows - 1, self.cols - 1) # Coordenadas de la salida

        self._initialize_map() # Configura el diseño inicial del parqueadero
        print(f"Parqueadero inicializado con {self.rows}x{self.cols} espacios.")
        print(f"Tarifa: ${self.rate_per_minute:.2f} por minuto.")

    def _initialize_map(self):
        """
        Configura el diseño inicial del mapa del parqueadero.
        Define vías, entrada, salida y espacios de parqueo.
        * Algoritmo de distribución de espacios optimizado con IA
        """
        # Inicializa todo el mapa como vías
        self.map = [[self.ROAD_SYMBOL for _ in range(self.cols)] for _ in range(self.rows)]

        # Define la entrada y la salida
        self.map[self.entrance_coords[0]][self.entrance_coords[1]] = self.ENTRANCE_SYMBOL
        self.map[self.exit_coords[0]][self.exit_coords[1]] = self.EXIT_SYMBOL

        # Coloca espacios de parqueo 'P'
        # Ejemplo de distribución: Dos bloques de parqueo a los lados de una vía central
        # Asegúrate de que los espacios sean accesibles desde las vías
        for r in range(1, self.rows - 1): # Evitar la primera y última fila para vías principales
            # Bloque de parqueo izquierdo
            if r % 2 == 0: # Cada dos filas para crear pasillos
                for c in range(1, self.cols // 3):
                    self.map[r][c] = self.FREE_SPOT_SYMBOL
            # Bloque de parqueo derecho
            if r % 2 == 1:
                for c in range(self.cols - (self.cols // 3), self.cols - 1):
                    self.map[r][c] = self.FREE_SPOT_SYMBOL

        # Asegura que haya un camino claro desde la entrada a la vía central
        for r in range(self.entrance_coords[0] + 1, self.rows - 1):
            self.map[r][self.entrance_coords[1]] = self.ROAD_SYMBOL # Camino vertical desde la entrada

        for c in range(self.entrance_coords[1] + 1, self.cols // 2):
            self.map[self.entrance_coords[0]][c] = self.ROAD_SYMBOL # Camino horizontal desde la entrada

        # Asegura que haya un camino claro desde la vía central a la salida
        for r in range(self.exit_coords[0] - 1, 0, -1):
            self.map[r][self.exit_coords[1]] = self.ROAD_SYMBOL # Camino vertical a la salida

        for c in range(self.exit_coords[1] - 1, self.cols // 2, -1):
            self.map[self.exit_coords[0]][c] = self.ROAD_SYMBOL # Camino horizontal a la salida

        # Limpiar cualquier 'P' que pueda haber quedado en el camino de entrada/salida
        self.map[self.entrance_coords[0]][self.entrance_coords[1]] = self.ENTRANCE_SYMBOL
        self.map[self.exit_coords[0]][self.exit_coords[1]] = self.EXIT_SYMBOL


    def display_map(self, temp_map=None):
        """
        Muestra el mapa actual del parqueadero en la consola.
        """
        map_to_display = temp_map if temp_map else self.map
        print("\n--- Mapa del Parqueadero ---")
        for r in range(self.rows):
            for c in range(self.cols):
                # Añadir un espacio para mejor visualización
                print(map_to_display[r][c], end=' ')
            print() # Nueva línea al final de cada fila
        print("--------------------------\n")
        self.get_occupancy()

    def find_available_spot(self) -> tuple or None:
        """
        Busca el primer espacio de parqueo libre disponible.

        Returns:
            tuple: Coordenadas (fila, columna) del espacio libre, o None si no hay.
        """
        for r in range(self.rows):
            for c in range(self.cols):
                if self.map[r][c] == self.FREE_SPOT_SYMBOL:
                    return (r, c)
        return None

    def register_vehicle(self, plate: str):
        """
        Registra un vehículo en el parqueadero, asignándole un espacio.

        Args:
            plate (str): La placa del vehículo a registrar.
        """
        if plate in self.vehicles:
            print(f"Error: El vehículo con placa '{plate}' ya está registrado.")
            return

        spot = self.find_available_spot()
        if spot is None:
            print("Lo sentimos, el parqueadero está lleno.")
            return

        # Asignar el espacio y actualizar el mapa
        self.map[spot[0]][spot[1]] = self.OCCUPIED_SPOT_SYMBOL
        entry_time = datetime.datetime.now()
        self.vehicles[plate] = {
            'entry_time': entry_time,
            'spot': spot
        }
        print(f"Vehículo '{plate}' registrado en el espacio {spot} a las {entry_time.strftime('%Y-%m-%d %H:%M:%S')}.")
        self.display_map()
        self.show_path_to_spot(spot) # Mostrar el camino al espacio

    def release_vehicle(self, plate: str):
        """
        Libera un vehículo del parqueadero, calcula el costo y actualiza el mapa.

        Args:
            plate (str): La placa del vehículo a liberar.
        """
        if plate not in self.vehicles:
            print(f"Error: El vehículo con placa '{plate}' no está registrado.")
            return

        vehicle_info = self.vehicles[plate]
        entry_time = vehicle_info['entry_time']
        spot = vehicle_info['spot']
        exit_time = datetime.datetime.now()

        # Calcular el tiempo de permanencia y el costo
        # * Lógica de cálculo de tarifas mejorada con IA para mayor precisión
        duration = exit_time - entry_time
        total_minutes = duration.total_seconds() / 60
        cost = total_minutes * self.rate_per_minute

        # Liberar el espacio en el mapa
        self.map[spot[0]][spot[1]] = self.FREE_SPOT_SYMBOL
        del self.vehicles[plate] # Eliminar el vehículo del registro

        print(f"\n--- Salida del Vehículo '{plate}' ---")
        print(f"Tiempo de permanencia: {total_minutes:.2f} minutos.")
        print(f"Valor a pagar: ${cost:.2f}")
        print("----------------------------------")
        self.display_map()

    def get_occupancy(self):
        """
        Muestra la disponibilidad actual del parqueadero.
        """
        occupied_spots = 0
        free_spots = 0
        for r in range(self.rows):
            for c in range(self.cols):
                if self.map[r][c] == self.OCCUPIED_SPOT_SYMBOL:
                    occupied_spots += 1
                elif self.map[r][c] == self.FREE_SPOT_SYMBOL:
                    free_spots += 1
        total_spots = occupied_spots + free_spots
        print(f"Espacios ocupados: {occupied_spots}")
        print(f"Espacios libres: {free_spots}")
        print(f"Total de espacios de parqueo: {total_spots}")

    def show_path_to_spot(self, target_spot: tuple):
        """
        Muestra una ruta simple desde la entrada hasta un espacio de parqueo.
        Esto es una visualización temporal y no modifica el mapa permanente.
        * Algoritmo de pathfinding básico implementado con sugerencias de IA
        """
        temp_map = [row[:] for row in self.map] # Copia del mapa actual
        current_r, current_c = self.entrance_coords

        path = []
        # Simple pathfinding: primero mover horizontalmente, luego verticalmente
        # Esto no es un algoritmo de pathfinding óptimo (como A*), pero visualiza una ruta
        # Mover horizontalmente hacia la columna del objetivo
        while current_c != target_spot[1]:
            if current_c < target_spot[1]:
                current_c += 1
            else:
                current_c -= 1
            if temp_map[current_r][current_c] == self.ROAD_SYMBOL:
                path.append((current_r, current_c))

        # Mover verticalmente hacia la fila del objetivo
        while current_r != target_spot[0]:
            if current_r < target_spot[0]:
                current_r += 1
            else:
                current_r -= 1
            if temp_map[current_r][current_c] == self.ROAD_SYMBOL:
                path.append((current_r, current_c))

        # Marcar el camino en el mapa temporal
        for r, c in path:
            temp_map[r][c] = self.PATH_SYMBOL

        # Marcar el punto de entrada y el punto de parqueo
        temp_map[self.entrance_coords[0]][self.entrance_coords[1]] = self.ENTRANCE_SYMBOL
        temp_map[target_spot[0]][target_spot[1]] = self.OCCUPIED_SPOT_SYMBOL # El spot ya está ocupado

        print("\n--- Ruta del Vehículo al Espacio ---")
        self.display_map(temp_map)
        print("----------------------------------\n")


def main():
    """
    Función principal para ejecutar el sistema de parqueadero.
    * Interfaz de menú interactivo diseñado con asistencia de IA
    """
    # Configuración del parqueadero
    rows = 10
    cols = 15
    rate = 0.5 # $0.5 por minuto

    parking_lot = Parqueadero(rows, cols, rate)

    while True:
        print("\n--- Menú Principal del Parqueadero ---")
        print("1. Ver mapa del parqueadero")
        print("2. Ingresar vehículo")
        print("3. Sacar vehículo")
        print("4. Ver disponibilidad")
        print("5. Salir")
        choice = input("Seleccione una opción: ")

        if choice == '1':
            parking_lot.display_map()
        elif choice == '2':
            plate = input("Ingrese la placa del vehículo: ").strip().upper()
            # * Validación de entrada mejorada con patrones sugeridos por IA
            if plate:
                parking_lot.register_vehicle(plate)
            else:
                print("La placa no puede estar vacía.")
        elif choice == '3':
            plate = input("Ingrese la placa del vehículo a sacar: ").strip().upper()
            if plate:
                parking_lot.release_vehicle(plate)
            else:
                print("La placa no puede estar vacía.")
        elif choice == '4':
            parking_lot.get_occupancy()
        elif choice == '5':
            print("Saliendo del sistema de parqueadero. ¡Hasta luego!")
            break
        else:
            print("Opción no válida. Por favor, intente de nuevo.")

if __name__ == "__main__":
    main()
