# Proyecto: Procesamiento Concurrente de Números

## Descripción
Este proyecto consiste en un programa que recibe como parámetro un archivo de configuración `.txt` con formato clave-valor. Dicho archivo define la cantidad de números a procesar por cada hilo y la cantidad total de hilos que se ejecutarán.

Los parámetros aceptados en el archivo de configuración son:
- **`numbers_per_thread`**: Define la cantidad de números que recibirá cada hilo.
- **`thread_num`**: Define el número de hilos que procesarán los números.

Además, el programa puede recibir como argumento `--help` o `-h` para mostrar cómo ejecutar el binario correctamente.

---

## Estructura del Proyecto
El proyecto se divide en tres partes principales:
1. **Validación de argumentos**: Se verifica que los parámetros de entrada sean correctos.
2. **Parseo y validación del archivo de configuración**: Se procesa el archivo y se valida su formato.
3. **Ejecución**: Se generan listas aleatorias de números y se gestiona la concurrencia mediante hilos y mutexes.

Durante la ejecución:
- Se generan listas de números aleatorios que serán distribuidos entre los hilos.
- Se crean y gestionan los hilos, asegurando sincronización mediante `pthread_mutex_t`.
- Cada hilo procesa los números de la lista recibida y los añaden a dos listas compartidas
por todos: pares e impares.

Se imprimen los números procesados con su posición en la lista en el siguiente formato:
```
ODD NUMBERS:
Position: 0 --> Value: 1863
EVEN NUMBERS:
Position: 0 --> Value: 5508
```
En caso de errores, se generan mensajes explícitos por la salida estándar de error (`stderr`).

---

## Programación Concurrente
En este proyecto se aplicó **programación concurrente**, que es un paradigma donde múltiples procesos o hilos se ejecutan simultáneamente para mejorar la eficiencia del programa. En particular, se usó la **API de threads en C**, que permite la creación y gestión de hilos con funciones de la librería POSIX `pthread`:

### Principales funciones utilizadas:
- **`pthread_create`**: Crea un nuevo hilo.
- **`pthread_join`**: Espera la terminación de un hilo específico.
- **`pthread_mutex_init`**: Inicializa un mutex para control de acceso.
- **`pthread_mutex_lock`**: Bloquea un mutex para evitar data races.
- **`pthread_mutex_unlock`**: Desbloquea un mutex.
- **`pthread_mutex_destroy`**: Libera un mutex cuando ya no se necesita.

Se utilizó **Valgrind** para gestionar la memoria y **Helgrind** para detectar posibles data races.

---

## Estructuras de Datos
El programa usa las siguientes estructuras:

```c
typedef struct {
  Node **even;
  Node **odd;
  pthread_mutex_t *even_mutex;
  pthread_mutex_t *odd_mutex;
  pthread_t pthread;
  int *numbers_received;
  int list_size;
  int index; // Para debug
} Threads;

typedef struct {
  int numbers_per_thread;
  int thread_num;
  Node **even;
  Node **odd;
  pthread_mutex_t even_mutex;
  pthread_mutex_t odd_mutex;
  Threads *threads;
} Program;
```

---

## Compilación y Ejecución
Se usó `make` con `gcc` siguiendo las siguientes normas de compilación:
- **make** (compila el programa y genera el ejecutable Even_odd).
- **make clean** (elimina los archivos objeto .o).
- **make fclean** (elimina los archivos objeto y el ejecutable).
- **make re** (recompila completamente el proyecto).

Para compilar y ejecutar el programa:
```sh
make
./Even_odd -f path/to/config.txt
./Even_odd --file path/to/config.txt
```

Para ver la ayuda:
```sh
./Even_odd --help
./Even_odd -h
```

---

## Herramientas de Depuración
- **Valgrind**: Para detectar fugas de memoria.
- **Helgrind**: Para analizar posibles data races en la ejecución concurrente.

