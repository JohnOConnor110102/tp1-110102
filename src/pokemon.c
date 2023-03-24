#include "pokemon.h"
#include <string.h>
#include <stdio.h>
#include "pokemon_privado.h"

#define FORMATO_LECTURA_STRING "%lud,%[^,],%lud,%s"
const int CANT_CAMPOS_POKEMON_T = 4;

pokemon_t *pokemon_crear_desde_string(const char *string)
{
	pokemon_t *poke_leido = malloc(sizeof(pokemon_t));
	if (poke_leido == NULL)
		return NULL;

	int leido = sscanf(string, FORMATO_LECTURA_STRING, &(poke_leido->id),
			   poke_leido->nombre, &(poke_leido->salud),
			   poke_leido->nombre_entrenador);

	if (leido == CANT_CAMPOS_POKEMON_T)
		return poke_leido;

	return NULL;
}

pokemon_t *pokemon_copiar(pokemon_t *poke)
{
	return NULL;
}

bool pokemon_son_iguales(pokemon_t *pokemon1, pokemon_t *pokemon2)
{
	return true;
}

char *pokemon_nombre(pokemon_t *pokemon)
{
	return 0;
}

char *pokemon_entrenador(pokemon_t *pokemon)
{
	return 0;
}

size_t pokemon_salud(pokemon_t *pokemon)
{
	return 0;
}

size_t pokemon_id(pokemon_t *pokemon)
{
	return 0;
}

void pokemon_destruir(pokemon_t *pkm)
{
}
