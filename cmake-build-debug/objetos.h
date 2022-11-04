//
// Created by alan_ on 04/11/2022.
//

#include <stdbool.h>

#ifndef CODIGO_PROJETEIS_OBJETOS_H
#define CODIGO_PROJETEIS_OBJETOS_H

#endif //CODIGO_PROJETEIS_OBJETOS_H

//OBJETOS

enum IDS {JOGADOR, PROJETIL, INIMIGOS};

struct NaveEspacial {
    int ID;
    int x;
    int y;
    int vidas;
    int velocidade;
    int borda_x;
    int borda_y;
    int pontos;
};

struct Projeteis {
    int ID;
    int x;
    int y;
    int velocidade;
    bool ativo;
};
