<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TP1

## Repositorio de John O'Connor - 110102 - johnoc1712@gmail.com

- Para compilar:

```bash
línea de compilación
```

- Para ejecutar:

```bash
línea de ejecución
```

- Para ejecutar con valgrind:
```bash
línea con valgrind
```
---
##  Funcionamiento

En cuanto al desenvolvimiento del tp1, se modificaron y desarrollaron estructuras de algoritmos en dos archivos; `tp1.c` y `pokemon.c`.

Comenzando por `pokemon.c`:

`pokemon_crear_desde_string` en primera instancia, verifica que el string pasado por parámetro sea válido (distinto de `NULL` y no vacío). A continuación reserva un bloque de espacio en memoria dinámica mediante `malloc` para `*poke_leido` (verificando que se reserve correctamente), a fin de poder guardar los datos leidos del string mediante `sscanf` en los correspondientes campos de `*poke_leido`, para finalmente devolver `*poke_leido`, en caso de que se hayan leido bien los datos, o en caso contrario liberar el espacio reservado en memoria mediante `free` y devolver `NULL` en señal de error. El siguiente esquema representa el manejo de memoria al reservar el espacio con `malloc`:

<div align="center">
<img width="70%" src="img/diagrama1.svg">
</div>


Luego, `pokemon_copiar` verifica que el `pokemon_t` pasado por parámetro sea válido (distinto de `NULL`). Reserva un bloque de espacio en memoria dinámica por `malloc` para `*nuevo_poke` (verificando que se reserve correctamente). A continuación copia los datos de cada uno de los campos de `*poke` en `*nuevo_poke` y por último devuelve `*nuevo_poke`. El siguiente esquema representa el manejo de memoria al reservar el espacio con `malloc`: 

<div align="center">
<img width="70%" src="img/diagrama1.svg">
</div>


`pokemon_son_iguales`, verifica que ambos de los `pokemon_t` enviados por parámetro no sean `NULL`, devuelve `false` en caso de que alguno de los campos de `*pokemon1` sea igual al respectivo campo de `*pokemon2`, y `true` en caso contrario.

`pokemon_nombre` verifica que el `pokemon_t` enviado por parámetro no sea `NULL` y devuelve el campo `pokemon->nombre`.

`pokemon_entrenador` verifica que el `pokemon_t` enviado por parámetro no sea `NULL` y devuelve el campo `pokemon->nombre_entrenador`.

`pokemon_salud` verifica que el `pokemon_t` enviado por parámetro no sea `NULL` y devuelve el campo `pokemon->salud`.

`pokemon_id` verifica que el `pokemon_t` enviado por parámetro no sea `NULL` y devuelve el campo `pokemon->id`.

`pokemon_destruir` verifica que el `pokemon_t` enviado por parámetro no sea `NULL` y libera el bloque de espacio reservado en memoria para el mismo mediante `free`.






Explicación de cómo funcionan las estructuras desarrolladas en el TP y el funcionamiento general del mismo.

Aclarar en esta parte todas las decisiones que se tomaron al realizar el TP, cosas que no se aclaren en el enunciado, fragmentos de código que necesiten explicación extra, etc.

Incluír **EN TODOS LOS TPS** los diagramas relevantes al problema (mayormente diagramas de memoria para explicar las estructuras, pero se pueden utilizar otros diagramas si es necesario).

### Por ejemplo:

El programa funciona abriendo el archivo pasado como parámetro y leyendolo línea por línea. Por cada línea crea un registro e intenta agregarlo al vector. La función de lectura intenta leer todo el archivo o hasta encontrar el primer error. Devuelve un vector con todos los registros creados.

<div align="center">
<img width="70%" src="img/diagrama1.svg">
</div>

En el archivo `sarasa.c` la función `funcion1` utiliza `realloc` para agrandar la zona de memoria utilizada para conquistar el mundo. El resultado de `realloc` lo guardo en una variable auxiliar para no perder el puntero original en caso de error:

```c
int *vector = realloc(vector_original, (n+1)*sizeof(int));

if(vector == NULL)
    return -1;
vector_original = vector;
```


<div align="center">
<img width="70%" src="img/diagrama2.svg">
</div>

---

## Respuestas a las preguntas teóricas
Incluír acá las respuestas a las preguntas del enunciado (si aplica).
