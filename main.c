#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include "cmake-build-debug/objetos.h"

//VARIAVEIS GLOBAIS
const int largura_t = 800;
const int altura_t = 400;
const int FPS = 60;
const int NUM_BALAS = 5;


enum TECLAS {CIMA, BAIXO, ESQUERDA, DIREITA, SPACE};

//PROTÓTIPOS
void InitNave (struct NaveEspacial nave);
void DesenhaNave (struct NaveEspacial nave);
void MoveNaveCima (struct NaveEspacial nave);
void MoveNaveBaixo (struct NaveEspacial nave);
void MoveNaveDireita (struct NaveEspacial nave);
void MoveNaveEsquerda (struct NaveEspacial nave);

void InitBalas (struct Projeteis balas[], int tamanho);
void AtiraBalas (struct Projeteis balas[], int tamanho, struct NaveEspacial nave);
void AtualizaBalas (struct Projeteis balas[], int tamanho);
void DesenhaBalas (struct Projeteis balas[], int tamanho);

int main() {
    //VARIAVEIS DO JOGO
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
    ALLEGRO_TIMER *timer = NULL;

    bool fim = false;
    bool desenha = true;
    bool teclas[] = {false, false, false, false, false};

    //INICIALIZAÇÃO DE OBJETOS
    struct NaveEspacial nave;
    struct Projeteis bala[NUM_BALAS];

    //INICIALIZAÇÃO DA ALLEGRO E DO DISPLAY
    ALLEGRO_DISPLAY *display = NULL;

    if(!al_init()){
        al_show_native_message_box(NULL, "Aviso!", "Erro!", "Erro ao iniciar o allegro!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    display = al_create_display(largura_t, altura_t);

    if(!display){
        al_show_native_message_box(NULL, "Aviso!", "Erro!", "Erro ao iniciar o allegro!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    //INICIALIZAÇÃO DE ADDONS E INSTALAÇÕES
    al_init_primitives_addon();
    al_install_keyboard();

    //CRIAÇÃO DA FILA E DEMAIS DISPOSITIVOS
    fila_eventos = al_create_event_queue();
    timer = al_create_timer(1.0/FPS);

    //REGISTRO DE SOURCES
    al_register_event_source(fila_eventos, al_get_display_event_source(display));
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));

    //FUNÇÕES INICIAIS
    InitNave(nave);

    //LOOP PRINCIPAL
    al_start_timer(timer);

    while(!fim){
        ALLEGRO_EVENT ev;
        al_wait_for_event(fila_eventos, &ev);

        //EVENTOS E LOGICA DO JOGO
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            fim = true;
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(ev.keyboard.keycode){
                case ALLEGRO_KEY_ESCAPE:
                    fim = true;
                    break;

                case ALLEGRO_KEY_UP:
                    teclas[CIMA] = true;
                    break;

                case ALLEGRO_KEY_DOWN:
                    teclas[BAIXO] = true;
                    break;

                case ALLEGRO_KEY_RIGHT:
                    teclas[DIREITA] = true;
                    break;

                case ALLEGRO_KEY_LEFT:
                    teclas[ESQUERDA] = true;
                    break;

                case ALLEGRO_KEY_SPACE:
                    teclas[SPACE] = true;
                    break;
            }
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_UP){
            switch(ev.keyboard.keycode){
                case ALLEGRO_KEY_ESCAPE:
                    fim = true;
                    break;

                case ALLEGRO_KEY_UP:
                    teclas[CIMA] = true;
                    break;

                case ALLEGRO_KEY_DOWN:
                    teclas[BAIXO] = true;
                    break;

                case ALLEGRO_KEY_RIGHT:
                    teclas[DIREITA] = true;
                    break;

                case ALLEGRO_KEY_LEFT:
                    teclas[ESQUERDA] = true;
                    break;
            }
        }
        else if(ev.type == ALLEGRO_EVENT_TIMER){
            desenha = true;

            if(teclas[CIMA])
                MoveNaveCima(nave);
            if(teclas[BAIXO])
                MoveNaveBaixo(nave);
            if(teclas[DIREITA])
                MoveNaveDireita(nave);
            if(teclas[ESQUERDA])
                MoveNaveEsquerda(nave);
        }

        //DESENHO
        if(desenha && al_is_event_queue_empty(fila_eventos)){
            desenha = false;

            DesenhaNave(nave);

            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }

           

    }

    return 0;
}
