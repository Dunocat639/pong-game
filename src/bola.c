#include "bola.h"
#include "main.h"

// Limitar velocitat de la bola
void limitarVelBola(Bola *b) {
    if (fabs(b->velocitat.x) < b->maxVel.x) {
    b->velocitat.x *= -1.1f;
    }
    else {
    b->velocitat.x *= -1.0f;
    }
}