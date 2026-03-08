#ifndef JUGADORS_H
#define JUGADORS_H

#include <raylib.h>
#include "bola.h"

// Struct jugadors (inicialitazció)
typedef struct {
    Vector2 posició;
    Vector2 mida;
    const float velocitat;
    int punts;
} Jugador;

// Funció per als controls
void controls(int key, Jugador *p, float velocitat);

// Funció per a puntuar
void puntuar(Bola *b, Jugador *p);

#endif