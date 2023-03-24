#include "pokemon.h"
#include <string.h>
#include <stdio.h>
#include "pokemon_privado.h"

#define FORMATO_LECTURA_STRING "%lu,%[^,],%lu,%s"
const int CANT_CAMPOS_POKEMON_T = 4;
const int STRING_VACIO = 0;

pokemon_t *pokemon_crear_desde_string(const char *string)
{
	if (string == NULL || strlen(string) == STRING_VACIO)
		return NULL;

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
	pokemon_t *nuevo_poke = malloc(sizeof(pokemon_t));
	if (nuevo_poke == NULL)
		return NULL;

	nuevo_poke->id = poke->id;
	nuevo_poke->salud = poke->salud;
	strcpy(nuevo_poke->nombre, poke->nombre);
	strcpy(nuevo_poke->nombre_entrenador, poke->nombre_entrenador);

	return nuevo_poke;
}

bool pokemon_son_iguales(pokemon_t *pokemon1, pokemon_t *pokemon2)
{
	if () {
	}

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
	free(pkm);
}
