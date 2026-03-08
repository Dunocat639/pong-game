#include <stdio.h>
#include <math.h>
#include <raylib.h>

#include "main.h"
#include "jugadors.h"
#include "bola.h"

int main(void) {

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
        .velocitat = {300, 200},
        .maxVel = {950, bola.velocitat.y} // La velocitat Y no importa
    };
    
    const char títol[] = "Joc del pong";

    InitWindow(ampladaPantalla, alturaPantalla, títol);

    SetTargetFPS(240);

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


        // Col·lisió bola amb jugadors
        if (CheckCollisionCircleRec(bola.posició, bola.radi, (Rectangle){j1.posició.x, j1.posició.y, j1.mida.x, j1.mida.y})){ // Jugador 1
            limitarVelBola(&bola);
            bola.posició.x = j1.posició.x + j1.mida.x + bola.radi; // Seguretat
        }
        else if (CheckCollisionCircleRec(bola.posició, bola.radi, (Rectangle){j2.posició.x, j2.posició.y, j2.mida.x, j2.mida.y})){ // Jugador 2
            limitarVelBola(&bola);
            bola.posició.x = j2.posició.x - bola.radi; // Seguretat
        }

        BeginDrawing();

                ClearBackground(BLACK);

                //Dibuixar bola
                DrawCircleV(bola.posició, bola.radi, WHITE);

                // Dibuixar jugador 1 i 2
                DrawRectangleV(j1.posició, j1.mida, WHITE);
                DrawRectangleV(j2.posició, j2.mida, WHITE);

                // Dibuixar puntuació
                DrawText(TextFormat("Puntuació J1: %d", j1.punts), ampladaPantalla / 20, alturaPantalla / 20, 24, WHITE);
                DrawText(TextFormat("Puntuació J2: %d", j2.punts), ampladaPantalla - (ampladaPantalla / 4), alturaPantalla / 20, 24, WHITE);
                

        EndDrawing();
    }

    CloseWindow();

    return 0;
}