#ifndef BOLA_H
#define BOLA_H

#include <raylib.h>
#include <math.h>

// Struct bola (inicialitazció)
typedef struct {
    Vector2 posició;
    const float radi;
    const Vector2 defVel;
    Vector2 velocitat;
    Vector2 maxVel;
} Bola;

// Limitar velocitat de la bola
void limitarVelBola(Bola *b);

#endif