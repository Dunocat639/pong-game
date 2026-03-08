#include "jugadors.h"
#include "main.h"
#include "bola.h"

// Funció per als controls
void controls(int key, Jugador *p, float velocitat) {
    if(IsKeyDown(key)) {
        p->posició.y += velocitat * GetFrameTime();
    }

    if (p->posició.y < 0) {
        p->posició.y = 0;
    }

    if (p->posició.y > (alturaPantalla - p->mida.y)) {
        p->posició.y = alturaPantalla - p->mida.y;
    }
}

// Funció per a puntuar
void puntuar(Bola *b, Jugador *p) {
        b->velocitat.x *= -1.0f;
        p->punts ++;
        b->posició = (Vector2){ampladaPantalla/2, alturaPantalla/2}; // Reiniciar posició de la vola
        b->velocitat = b->defVel; // Reiniciar velocitat de la bola
}