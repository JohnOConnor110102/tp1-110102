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

void insertar_pokemones_ordenadamente(hospital_t *hospital,
				      pokemon_t **pokemones_ambulancia,
				      size_t cant_pokes_ambulancia)
{
	for (size_t i = 0; i < cant_pokes_ambulancia; i++) {
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

		for (size_t k = hospital->cantidad_pokemon;
		     k > indice_a_insertar; k--) {
			hospital->pokemones[k] = hospital->pokemones[k - 1];
		}

		hospital->pokemones[indice_a_insertar] =
			pokemones_ambulancia[i];
		hospital->cantidad_pokemon++;
	}
}

void ordenar_hospital(hospital_t *hospital)
{
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
}

hospital_t *hospital_crear_desde_archivo(const char *nombre_archivo)
{
	if (nombre_archivo == NULL)
		return NULL;

	FILE *archivo = fopen(nombre_archivo, "r");
	if (archivo == NULL)
		return NULL;

	hospital_t *hospital = malloc(sizeof(hospital_t));
	if (hospital == NULL) {
		fclose(archivo);
		return NULL;
	}
	hospital->pokemones = malloc(sizeof(char *));
	if (hospital->pokemones == NULL) {
		fclose(archivo);
		free(hospital);
		return NULL;
	}

	char *linea_leida = malloc(MAX_CARACTERES_LINEA * sizeof(char));
	if (linea_leida == NULL) {
		fclose(archivo);
		free(hospital->pokemones);
		free(hospital);
		return NULL;
	}
	int leido = fscanf(archivo, FORMATO_LECTURA_ARCHIVO, linea_leida);
	if (leido != LINEA_LEIDA) {
		fclose(archivo);
		free(linea_leida);
		free(hospital->pokemones);
		free(hospital);
		return NULL;
	}

	int i = 0;
	hospital->cantidad_entrenadores = 0;
	hospital->cantidad_pokemon = 0;

	while (leido == LINEA_LEIDA) {
		hospital->pokemones[i] =
			pokemon_crear_desde_string(linea_leida);
		if (hospital->pokemones[i] == NULL) {
			fclose(archivo);
			free(linea_leida);
			free(hospital->pokemones);
			free(hospital);
			return NULL;
		}

		hospital->cantidad_pokemon++;
		hospital->cantidad_entrenadores++;

		pokemon_t **pokemones_aux = realloc(
			hospital->pokemones,
			(hospital->cantidad_pokemon + 1) * sizeof(char *));
		if (pokemones_aux == NULL) {
			fclose(archivo);
			free(linea_leida);
			for (size_t i = 0; i < hospital->cantidad_pokemon;
			     i++) {
				free(hospital->pokemones[i]);
			}
			free(hospital->pokemones);
			free(hospital);
			return NULL;
		}
		hospital->pokemones = pokemones_aux;

		i++;
		leido = fscanf(archivo, FORMATO_LECTURA_ARCHIVO, linea_leida);
	}

	fclose(archivo);
	free(linea_leida);

	ordenar_hospital(hospital);

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
	if (hospital == NULL || funcion == NULL)
		return 0;

	size_t contador = 0;
	for (int i = 0; i < hospital->cantidad_pokemon; i++) {
		contador++;
		if (!funcion(hospital->pokemones[i], aux)) {
			return contador;
		}
	}

	return contador;
}

int hospital_aceptar_emergencias(hospital_t *hospital,
				 pokemon_t **pokemones_ambulancia,
				 size_t cant_pokes_ambulancia)
{
	if (hospital == NULL || pokemones_ambulancia == NULL)
		return ERROR;

	pokemon_t **pokemones_aux =
		realloc(hospital->pokemones,
			(hospital->cantidad_pokemon + cant_pokes_ambulancia) *
				sizeof(char *));

	if (pokemones_aux == NULL) {
		for (size_t i = 0; i < hospital->cantidad_pokemon; i++) {
			free(hospital->pokemones[i]);
		}
		free(hospital->pokemones);
		free(hospital);
		return ERROR;
	}
	hospital->pokemones = pokemones_aux;

	insertar_pokemones_ordenadamente(hospital, pokemones_ambulancia,
					 cant_pokes_ambulancia);
	return EXITO;
}

pokemon_t *hospital_obtener_pokemon(hospital_t *hospital, size_t prioridad)
{
	for (int i = 0; i < hospital->cantidad_pokemon; i++) {
		if (i == prioridad)
			return hospital->pokemones[i];
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
