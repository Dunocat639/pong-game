#include <stdio.h>
#include <math.h>
#include <raylib.h>

const int ampladaPantalla = 1000;
const int alturaPantalla = 500;

// Struct jugadors (inicialitazció)
typedef struct {
    Vector2 posició;
    Vector2 mida;
    const float velocitat;
    int punts;
} Jugador;

// Struct bola (inicialitazció)
typedef struct {
    Vector2 posició;
    const float radi;
    const Vector2 defVel;
    Vector2 velocitat;
    Vector2 maxVel;
} Bola;

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
        b->posició = (Vector2){ampladaPantalla/2, alturaPantalla/2};
        b->velocitat = b->defVel; // Reiniciar velocitat
}

// Limitar velocitat
void limitarVelBola(Bola *b) {
    if (fabs(b->velocitat.x) < b->maxVel.x) {
    b->velocitat.x *= -1.1f;
    }
    else {
    b->velocitat.x *= -1.0f;
    }
}


int main(void) {
    
    const char títol[] = "Joc del pong";

    InitWindow(ampladaPantalla, alturaPantalla, títol);

    SetTargetFPS(240);

    // Struct jugador 1
    Jugador j1 = {
        .posició = {ampladaPantalla / 10, alturaPantalla / 2},
        .mida = {10, 80},
        .velocitat = 900,
        .punts = 0
    };

    // Struct jugador 2
    Jugador j2 = {
        .posició = {ampladaPantalla - (ampladaPantalla / 10), alturaPantalla / 2},
        .mida = {10, 80},
        .velocitat = 900,
        .punts = 0
    };

    // Struct bola
    Bola bola = {
        .posició = {ampladaPantalla/2, alturaPantalla/2},
        .radi = 10.0f,
        .defVel = {300, 200},
        .velocitat = bola.defVel,
        .maxVel = {900, bola.velocitat.y} // La velocitat Y no importa
    };

    while(!WindowShouldClose()){

        // Controls jugadors
        controls(KEY_W, &j1, -j1.velocitat);
        controls(KEY_S, &j1, j1.velocitat);
        controls(KEY_UP, &j2, -j2.velocitat);
        controls(KEY_DOWN, &j2, j2.velocitat);

        // Moviment bola
        bola.posició.x += bola.velocitat.x * GetFrameTime();
        bola.posició.y += bola.velocitat.y * GetFrameTime();

        // Puntuar amb bola col·lisió a parets
        if (bola.posició.x >= (ampladaPantalla - bola.radi)) { // Paret dreta
            puntuar(&bola, &j1); // Puntua jugador 1
        }
        else if (bola.posició.x <= bola.radi) { // Paret esquerra
            puntuar(&bola, &j2); // Puntua jugador 2
        }

        // Rebotar verticalment
        if (bola.posició.y >= (alturaPantalla - bola.radi) || bola.posició.y <= bola.radi) {
            bola.velocitat.y *= -1.0f;
        }

        BeginDrawing();

                ClearBackground(BLACK);

                //Dibuixar bola
                DrawCircleV(bola.posició, bola.radi, WHITE);

                // Dibuixar jugador 1 i 2
                DrawRectangleV(j1.posició, j1.mida, WHITE);
                DrawRectangleV(j2.posició, j2.mida, WHITE);

                // Col·lisió bola amb jugadors
                if (CheckCollisionCircleRec(bola.posició, bola.radi, (Rectangle){j1.posició.x, j1.posició.y, j1.mida.x, j1.mida.y})){ // Jugador 1
                    limitarVelBola(&bola);
                    bola.posició.x = j1.posició.x + j1.mida.x + bola.radi; // Seguretat
                }
                else if (CheckCollisionCircleRec(bola.posició, bola.radi, (Rectangle){j2.posició.x, j2.posició.y, j2.mida.x, j2.mida.y})){ // Jugador 2
                    limitarVelBola(&bola);
                    bola.posició.x = j2.posició.x - bola.radi;
                }

                DrawText(TextFormat("Puntuació J1: %d", j1.punts), ampladaPantalla / 20, alturaPantalla / 20, 24, WHITE);
                DrawText(TextFormat("Puntuació J2: %d", j2.punts), ampladaPantalla - (ampladaPantalla / 4), alturaPantalla / 20, 24, WHITE);
                

        EndDrawing();
    }

    CloseWindow();

    return 0;
}