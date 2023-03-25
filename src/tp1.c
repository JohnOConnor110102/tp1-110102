#include "tp1.h"

#include "pokemon.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FORMATO_LECTURA_ARCHIVO "%s"
#define FIN_DE_LINEA "\n"

const int LINEA_LEIDA = 1;
const size_t MAX_CARACTERES_LINEA = 30;

struct _hospital_pkm_t {
	pokemon_t **pokemones;
	size_t cantidad_pokemon;
	size_t cantidad_entrenadores;
};

hospital_t *hospital_crear_desde_archivo(const char *nombre_archivo)
{
	if (nombre_archivo == NULL)
		return NULL;

	FILE *archivo = fopen(nombre_archivo, "r");
	if (archivo == NULL)
		return NULL;

	hospital_t *hospital = malloc(sizeof(hospital_t));
	if (hospital == NULL)
		return NULL;

	hospital->pokemones = malloc(sizeof(char *));
	if (hospital->pokemones == NULL)
		return NULL;

	char *linea_leida = malloc(MAX_CARACTERES_LINEA * sizeof(char));
	if (linea_leida == NULL)
		return NULL;

	int leido = fscanf(archivo, FORMATO_LECTURA_ARCHIVO, linea_leida);
	if (leido != LINEA_LEIDA) {
		return NULL;
	}

	int i = 0;
	size_t cantidad_pokemon = 0;
	size_t cantidad_entrenadores = 0;

	while (leido == LINEA_LEIDA) {
		hospital->pokemones[i] =
			pokemon_crear_desde_string(linea_leida);
		if (hospital->pokemones[i] == NULL)
			return NULL;

		cantidad_pokemon++;
		cantidad_entrenadores++;

		pokemon_t **pokemones_aux =
			realloc(hospital->pokemones,
				(cantidad_pokemon + 1) * sizeof(char *));
		if (pokemones_aux == NULL) {
			free(hospital->pokemones);
			return NULL;
		}
		hospital->pokemones = pokemones_aux;

		i++;
		leido = fscanf(archivo, FORMATO_LECTURA_ARCHIVO, linea_leida);
	}

	hospital->cantidad_entrenadores = cantidad_entrenadores;
	hospital->cantidad_pokemon = cantidad_pokemon;

	bool esta_ordenado = false;
	while (!esta_ordenado) {
		esta_ordenado = true;
		for (int i = 0; i < (hospital->cantidad_pokemon) - 1; i++) {
			if (pokemon_salud(hospital->pokemones[i + 1]) <
			    pokemon_salud(hospital->pokemones[i])) {
				esta_ordenado = false;
				pokemon_t *aux =
					pokemon_copiar(hospital->pokemones[i]);
				hospital->pokemones[i] = pokemon_copiar(
					hospital->pokemones[i + 1]);
				hospital->pokemones[i + 1] =
					pokemon_copiar(aux);
			}
		}
	}

	return hospital;
}

size_t hospital_cantidad_pokemones(hospital_t *hospital)
{
	if (hospital == NULL)
		return 0;

	return hospital->cantidad_pokemon;
}

size_t hospital_a_cada_pokemon(hospital_t *hospital,
			       bool (*funcion)(pokemon_t *p, void *aux),
			       void *aux)
{
	return 0;
}

int hospital_aceptar_emergencias(hospital_t *hospital,
				 pokemon_t **pokemones_ambulancia,
				 size_t cant_pokes_ambulancia)
{
	return ERROR;
}

pokemon_t *hospital_obtener_pokemon(hospital_t *hospital, size_t prioridad)
{
	for (int i = 0; i < hospital->cantidad_pokemon; i++) {
		if (pokemon_id(hospital->pokemones[i]) == prioridad) {
			return hospital->pokemones[i];
		}
	}

	return NULL;
}

void hospital_destruir(hospital_t *hospital)
{
	for (size_t i = 0; i < hospital->cantidad_pokemon; i++) {
		free(hospital->pokemones[i]);
	}
	free(hospital->pokemones);
	free(hospital);
}
