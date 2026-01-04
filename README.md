# Laboratorio Programación 2 FING 2024
Proyecto del curso Programación 2 - Facultad de Ingeniería - UdelaR - Semestre par 2024

# Descripción
Proyecto académico desarrollado en C++ para la materia Programación 2
(Facultad de Ingeniería, UdelaR).

El sistema modela un mercado ficticio y utiliza diversas estructuras de datos
como árboles binarios de búsqueda (ABB), listas enlazadas, colas y tablas hash.

El proyecto se divide en 4 tareas prácticas.  
Cada tarea es una extensión funcional de la anterior, incorporando nuevos requerimientos y complejidad.

Para facilitar la continuidad del trabajo, cada tarea parte de una solución base provista por la cátedra, sobre la cual se realizan las nuevas implementaciones solicitadas.

# Mi aporte
El programa principal, los archivos `.h`, los `Makefile` y los casos de prueba fueron proporcionados por la cátedra.

Mi trabajo consistió en la implementación de la lógica del sistema en los archivos `.cpp`, incluyendo:
- Alta, baja y modificación de clientes
- Gestión de listas de compras
- Manejo de promociones
- Uso de estructuras de datos dinámicas
- Manejo y corrección de errores de memoria

# Conceptos trabajados
- Tipos abstractos de datos (TAD)
- Manejo de memoria dinámica
- Modularización en C++
- Estructuras de datos (ABB, listas, colas, hash)
- Compilación con `make`
- Pruebas automáticas
- Detección de errores con Valgrind

# Tecnologías
- C++

# Compilación y ejecución
> Entorno recomendado: Linux / WSL

```bash
# Instalar compilador
sudo apt install g++

# Instalar Valgrind (opcional)
sudo apt install valgrind

# Dentro de la carpeta de una tarea
make
./principal
