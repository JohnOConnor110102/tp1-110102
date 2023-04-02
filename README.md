<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TP1

## Repositorio de John O'Connor - 110102 - johnoc1712@gmail.com

- Para compilar:

```bash
gcc src/*.c pruebas_chanutron.c -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g -o pruebas_chanutron
```

- Para ejecutar:

```bash
./pruebas_chanutron
```

- Para ejecutar con valgrind:
```bash
valgrind --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes ./pruebas_chanutron
```
---
##  Funcionamiento

En cuanto al desenvolvimiento del tp1, se modificaron y desarrollaron estructuras de algoritmos en dos archivos; `tp1.c` y `pokemon.c`.

Archivo `pokemon.c`:

`pokemon_crear_desde_string` devuelve `NULL` en caso de que el string pasado por parámetro sea `NULL` o este vacío , y caso contrario reserva un bloque de espacio en memoria dinámica, a fin de poder guardar los datos leidos del string. Luego devuelve los valores leidos en formato del struct `pokemon_t` en caso de que se hayan leido bien los datos, o en caso contrario libera el espacio reservado en memoria y devuelve `NULL` en señal de error. El siguiente esquema representa el manejo de memoria dentro de la función:

![Diagrama memoria pokemon_crear_desde_string](img/pokemon_crear_desde_string.jpeg)

Por otro lado, `pokemon_copiar` devuelve `NULL` en caso de que el pokemon pasado por parámetro no sea valido, y en caso contrario copia los datos del `pokemon_t` pasado por parámetro cada uno de los campos de un nuevo pokemon, reservando primero un bloque de espacio en memoria dinámica para el mismo, y finalmente devuelve el nuevo pokemon. El siguiente esquema representa el manejo de memoria en la función: 

![Diagrama memoria pokemon_copiar](img/pokemon_copiar.jpeg)


`pokemon_son_iguales`, devuelve `NULL` si alguno de los parámetros es `NULL` y caso contrario, devuelve `false` si alguno de los campos del primer pokemon es distinto al respectivo campo del segundo, y `true` en caso contrario.

`pokemon_nombre` devuelve `NULL` si el pokemon pasado por parámetro es `NULL` y devuelve el nombre del pokemon pasado por parámetro.

`pokemon_entrenador` devuelve `NULL` si el pokemon pasado por parámetro es `NULL` y devuelve el entrenador del pokemon pasado por parámetro..

`pokemon_salud` devuelve `NULL` si el pokemon pasado por parámetro es `NULL` y devuelve la salud del pokemon pasado por parámetro.

`pokemon_id` devuelve `NULL` si el pokemon pasado por parámetro es `NULL` y devuelve el id del pokemon pasado por parámetro.

`pokemon_destruir` devuelve `NULL` si el pokemon pasado por parámetro es `NULL` y libera el bloque de espacio reservado en memoria para el mismo.


Archivo `tp1.c`:

`hospital_crear_desde_archivo` devuelve `NULL` en caso de que el archivo pasado por parámetro sea invalido o si ocurre algún tipo de error durante la ejecución de la función. En principio la función lee el archivo guardando los datos leidos por cada linea en cada indice del vector de pokemones. En este proceso reservan bloques de espacio en memoria dinámica para el hospital y cada pokemon del vector de pokemones. En las verificaciones realizadas, el algoritmo se encarga de liberar los espacios en memoria correspondientes. Además se actulizan los valores correspondientes del `hospital` para reflejar los cambios de pokemones y entrenadores (asumiendo que los entrenadores no se repiten, aunque tengan el mismo nombre). 

Luego una vez ya leidos todos los pokemones, hace un llamado a la función `void ordenar_hospital`, donde se ordena mediante _burbujeo_ el vector creado con anterioridad, tomando como criterio el nivel de salud, de menor a mayor. Durante este proceso, sea realizan liberaciones de espacio de memoria correspondientes, evitando así pérdidas de memoria.

```c
bool esta_ordenado = false;
while (!esta_ordenado) {
    esta_ordenado = true;
    for (int i = 0; i < (hospital->cantidad_pokemon) - 1; i++) {
        if (pokemon_salud(hospital->pokemones[i + 1]) <
            pokemon_salud(hospital->pokemones[i])) {
            esta_ordenado = false;
            pokemon_t *aux =
                pokemon_copiar(hospital->pokemones[i]);
            free(hospital->pokemones[i]);
            hospital->pokemones[i] = pokemon_copiar(
                hospital->pokemones[i + 1]);
            free(hospital->pokemones[i + 1]);
            hospital->pokemones[i + 1] =
                pokemon_copiar(aux);
            free(aux);
        }
    }
}
```

El respectivo diagrama de memoria:

![Diagrama memoria hospital_crear_desde_archivo.jpeg](img/hospital_crear_desde_archivo.jpeg)


`hospital_cantidad_pokemones` devuelve `0` en caso de que el hospital pasado por parámetro sea `NULL`, y devuelve la cantidad de pokemones en el hospital.

`hospital_a_cada_pokemon` devuelve `0` en caso de que los parámetros sean `NULL`, y aplica a cada indice del vector de pokemones la función pasada por parámetro, siempre y cuando esta devuelva `true` y todavía haya pokemones en dicho vector. Finalmente devuelve la cantidad de veces que se aplicó la función, independientemente del resultado.

`hospital_aceptar_emergencias` devuelve `ERROR` en caso de que los parámetros sean `NULL`, y luego aumenta el bloque de espacio en memoria dinámica reservado para el vector de pokemones mediante `realloc`, guardando el resultado de la función en un vector auxiliar, para no perder la dirección de memoria original en caso de que falle el `realloc`, y en caso contrario, iguala la dirección de memoria del vector original a la del auxiliar. Luego, se invoca a la función `insertar_pokemones_ordenadamente` para ingresar los pokemones en el vector de la ambulancia al hospital, ordenadamente tomando en cuenta la salud de los pokemones, de menor a mayor. Finalmente devuelve EXITO si se pudieron insertar los pokemones.

Más específicamente, dentro de la función `insertar_pokemones_ordenadamente`, este algoritmo determina el índice a insertar el puntero del correspondiente pokemon de la ambulandia, según su nivel de salud comparado con aquellos en el hospital.

```c
int indice_a_insertar = 0;
int j = 0;
bool indice_determinado = false;
while (j < hospital->cantidad_pokemon && !indice_determinado) {
    if (pokemon_salud(hospital->pokemones[j]) <=
        pokemon_salud(pokemones_ambulancia[i])) {
        indice_a_insertar++;
    } else {
        indice_determinado = true;
    }
    j++;
}
```
El siguente mueve los punteros de los pokemones en el vector del hospital, posteriores al indice a insertar, un indice después en el vector, haciendo lugar para el pokemon a insertar.

```c
for (size_t k = hospital->cantidad_pokemon;
     k > indice_a_insertar; k--) {
    hospital->pokemones[k] = hospital->pokemones[k - 1];
}
```

Y finalmente este algoritmo inserta el pokemon correspondiente de la ambulancia en el indice indicado de l vector del hospital, actualizando la cantidad de pokemones en el hospital.

```c
hospital->pokemones[indice_a_insertar] =
    pokemones_ambulancia[i];
hospital->cantidad_pokemon++;
```

A continuación el diagrama de memoria correspondiente a esta función.

![Diagrama memoria hospital_aceptar_emergencias](img/hospital_aceptar_emergencias.jpeg)


Por último, `hospital_destruir`, no realiza ninguna función en caso de que el hospital pasado por parámetro sea `NULL`, y caso contrario libera el espacio en memoria reservado para todos los indices del vector de pokemones en el hospital, para el vector de pokemones en sí y para el mismo hospital.


## Respuestas a las preguntas teóricas
En el código, en la función `hospital_aceptar_emergencias`, se optó por realizar insersión ordenada de los nuevos pokemones en el vector del hospital, ya que esta opción resulta más eficiente en términos de recursos y complejidad computacional, comparado con insertar normalmente y lueg ordenar el vector original.