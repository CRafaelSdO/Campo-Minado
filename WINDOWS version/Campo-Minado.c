# include <allegro5\allegro.h>
# include <allegro5\allegro_native_dialog.h>
# include <allegro5\allegro_ttf.h>
# include <allegro5\allegro_font.h>
# include <allegro5\allegro_primitives.h>
# include <allegro5\allegro_image.h>
# include <allegro5\allegro_audio.h>
# include <allegro5\allegro_acodec.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#define all_directions jogada_coluna >= 0 && jogada_coluna < largura && jogada_linha < altura && jogada_linha >= 0

typedef struct ALLEGRO_MOUSE_STATE ALLEGRO_MOUSE_STATE;

const int LARGURA_TELA = 1280;
const int ALTURA_TELA = 720;
int largura, altura, bombas, compensacao, flags; char stringFlags[100];
int **tabuleiro;
char **tabuleiro2;
FILE *campo;
int FRAMES_POR_SEGUNDO = 120;
double tempoInicial = 0, cronometro, newTempo; char stringTempo[100];
int distanciax;
int distanciay;
float multiplicador_tamanho;
int firstI = -1, firstJ = -1;
int win, lose, aux;
int dificuldade;

//Declara eventos
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
ALLEGRO_MOUSE_STATE state;

//Declara BITMAPS
ALLEGRO_BITMAP *botao_sair = NULL;
ALLEGRO_BITMAP *imagem = NULL, *vazio = NULL, *um = NULL, *dois = NULL, *tres = NULL;
ALLEGRO_BITMAP *quatro = NULL, *cinco = NULL, *seis = NULL, *sete = NULL, *oito = NULL;
ALLEGRO_BITMAP *bomba = NULL, *flag = NULL;

//Declara fontes e cores
ALLEGRO_FONT *font;
ALLEGRO_COLOR branco;

//Declara sons
ALLEGRO_SAMPLE *musica = NULL;
ALLEGRO_SAMPLE *clique_jogo = NULL;
ALLEGRO_SAMPLE *clique_menu = NULL;
ALLEGRO_SAMPLE *explosao = NULL;
ALLEGRO_SAMPLE *floodfill_som = NULL;
ALLEGRO_SAMPLE *inicio = NULL;
ALLEGRO_SAMPLE *set_flag = NULL;
ALLEGRO_SAMPLE *take_flag = NULL;
ALLEGRO_SAMPLE *game_over = NULL;
ALLEGRO_SAMPLE *victory = NULL;
ALLEGRO_SAMPLE_ID *id_music = NULL;
ALLEGRO_SAMPLE_ID *id_game_over = NULL;
ALLEGRO_SAMPLE_ID *id_victory = NULL;

//Declara a janela
ALLEGRO_DISPLAY *janela = NULL;

int music = 0;
int menu = 1;

# include "RankingFunctions.h"
score array[100];
# include "Ranking.h"
# include "Credits.h"
# include "Jogar.h"
# include "Ganhou.h"
# include "Perdeu.h"
# include "Escolher_Dificuldade.h"
# include "informacao.h"

int main(void)
{
  ALLEGRO_BITMAP *botao_sair = NULL, *area_jogar = 0, *area_informacao = 0, *area_ver_recordes = 0, *area_creditos = 0, *area_sair_do_jogo = 0, *area_menu_fundo = NULL;

  // Flag que condicionar� nosso looping
  int sair = 0;
  int creditos = 0;
  int escolher = 0;

  //Inicia o Allegro
  if (!al_init())
  {
    fprintf(stderr, "Falha ao inicializar a Allegro.\n");
    return -1;
  }

  //Cria a janela
  janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
  if (!janela)
  {
    fprintf(stderr, "Falha ao criar janela.\n");
    return -1;
  }

  // Configura o título da janela
  al_set_window_title(janela, "Campo Minado");

  // Torna apto o uso de mouse na aplição
  if (!al_install_mouse())
  {
    fprintf(stderr, "Falha ao inicializar o mouse.\n");
    al_destroy_display(janela);
    return -1;
  }

  // Atribui o cursor padrão do sistema para ser usado
  if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
  {
    fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
    al_destroy_display(janela);
    return -1;
  }

  // Alocamos os retângulos da tela
  area_menu_fundo =   al_create_bitmap(360, 360);
  area_jogar =        al_create_bitmap(360, 72);
  area_informacao =   al_create_bitmap(360, 72);
  area_ver_recordes = al_create_bitmap(360, 72);
  area_creditos =     al_create_bitmap(360, 72);
  area_sair_do_jogo = al_create_bitmap(360, 72);

  // Alocamos o botão para fechar a aplicação
  botao_sair = al_create_bitmap(100, 50);
  if (!botao_sair)
  {
    fprintf(stderr, "Falha ao criar botãoo de saída.\n");
    al_destroy_display(janela);
    return -1;
  }

  // Flag indicando se o mouse est� sobre cada op�ao do menu
  int na_area_jogar = 0;
  int na_area_informacao = 0;
  int na_area_ver_recordes = 0;
  int na_area_creditos = 0;
  int na_area_sair_do_jogo = 0;

  //Inicializando
  al_init_image_addon();
  ALLEGRO_BITMAP *backgr;
  ALLEGRO_BITMAP *bomba;
  backgr = al_load_bitmap("imgs/background.png");
  bomba = al_load_bitmap("imgs/bombaBG.png");

  //Carregando fontes
  al_init_font_addon();
  al_init_ttf_addon();
  ALLEGRO_FONT *font1 = al_load_ttf_font("fonts/retro3d.ttf",150,NULL),*font2 = al_load_ttf_font("fonts/retro.ttf",35,NULL);

  //Carregando cores
  al_init_primitives_addon();
  ALLEGRO_COLOR Azul = al_map_rgb(44,117,255);
  ALLEGRO_COLOR VermelhoClaro = al_map_rgb(250,28,3);
  ALLEGRO_COLOR Preto = al_map_rgb(0, 0, 0);
  ALLEGRO_COLOR Cinza = al_map_rgb(172, 166, 166);
  ALLEGRO_COLOR Branco1, Branco2, Branco3, Branco4, Branco5;

  //Carregando sons
  al_install_audio();
  al_init_acodec_addon();
  al_reserve_samples(3);
  id_music = malloc(sizeof(ALLEGRO_SAMPLE_ID));
  musica = al_load_sample("songs/background.wav");
  clique_jogo = al_load_sample("songs/clique.wav");
  al_play_sample(musica, 0.7, 0, 1, ALLEGRO_PLAYMODE_LOOP, id_music);

  al_draw_filled_rectangle( 25 , 100, 300, 600, al_map_rgba_f(1, 1, 1, 0.5));

  float altura = 2.1;
  float distancia = 72;
  int play = 0;

  while (true)
  {
    if(music == 1)
    {
      al_play_sample(musica, 0.7, 0, 1, ALLEGRO_PLAYMODE_LOOP, id_music);
      music = 0;
    }
    fila_eventos = al_create_event_queue();

    // Dizemos que vamos tratar os eventos vindos do mouse
    al_register_event_source(fila_eventos, al_get_mouse_event_source());

    ALLEGRO_EVENT evento;
    al_wait_for_event(fila_eventos, &evento);

    // Limpamos a tela
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(backgr, 0, 0, NULL);
    al_draw_bitmap(bomba, LARGURA_TELA / 2 - 256, ALTURA_TELA / 2 - 256, NULL);

    // Desenhamos os retângulos na tela
    al_draw_bitmap(area_menu_fundo, LARGURA_TELA / 2.8  , ALTURA_TELA / 2.2 , 0.5);
    al_draw_bitmap(area_jogar, LARGURA_TELA/2.8  , ALTURA_TELA / 2.2 , 0.5);
    al_draw_bitmap(area_informacao, LARGURA_TELA / 2.8  , ALTURA_TELA / 2.2 + distancia , 0.5);
    al_draw_bitmap(area_ver_recordes, LARGURA_TELA / 2.8  , ALTURA_TELA / 2.2 + distancia*2, 0.5);
    al_draw_bitmap(area_creditos, LARGURA_TELA / 2.8  , ALTURA_TELA / 2.2 + distancia*3 , 0.5);
    al_draw_bitmap(area_sair_do_jogo, LARGURA_TELA / 2.8  , ALTURA_TELA / 2.2 + distancia*4 , 0.5);

    al_draw_text(font1,al_map_rgb(255,229,32),LARGURA_TELA/2,ALTURA_TELA/4 - 100,ALLEGRO_ALIGN_CENTRE,"CAMPO MINADO");
    al_draw_rectangle(LARGURA_TELA/2 - 180, ALTURA_TELA/altura - 15, LARGURA_TELA/2 + 180, ALTURA_TELA/altura + distancia*5 - 10, al_map_rgb(255, 255, 255), 6.0);
    al_draw_rectangle(LARGURA_TELA/2 - 186, ALTURA_TELA/altura - 21, LARGURA_TELA/2 + 186, ALTURA_TELA/altura + distancia*5 - 4, al_map_rgb(0, 0, 0), 6.0);
    al_draw_text(font2, Branco1, LARGURA_TELA/2, ALTURA_TELA/altura + 5, ALLEGRO_ALIGN_CENTER, "JOGAR");
    al_draw_text(font2, Branco2, LARGURA_TELA/2, ALTURA_TELA/altura + distancia, ALLEGRO_ALIGN_CENTER, "INFORMACOES");
    al_draw_text(font2, Branco3, LARGURA_TELA/2, ALTURA_TELA/altura + distancia*2, ALLEGRO_ALIGN_CENTER, "VER RECORDES");
    al_draw_text(font2, Branco4, LARGURA_TELA/2, ALTURA_TELA/altura + distancia*3, ALLEGRO_ALIGN_CENTER, "CREDITOS");
    al_draw_text(font2, Branco5, LARGURA_TELA/2, ALTURA_TELA/altura + distancia*4, ALLEGRO_ALIGN_CENTER, "SAIR DO JOGO");
    al_flip_display();

    al_set_target_bitmap(area_jogar);
    if (!na_area_jogar)
    {
      al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));
      Branco1 = al_map_rgb(255,255,255);
    }
    else
    {
      al_clear_to_color(al_map_rgba_f(0.2, 0.2, 0.2, 0.5));
      Branco1 = al_map_rgb(255,229,32);
    }

    al_set_target_bitmap(area_informacao);
    if (!na_area_informacao)
    {
      al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));
      Branco2 = al_map_rgb(255,255,255);
    }
    else
    {
      al_clear_to_color(al_map_rgba_f(0.2, 0.2, 0.2, 0.5));
      Branco2 = al_map_rgb(255,229,32);
    }

    al_set_target_bitmap(area_ver_recordes);
    if (!na_area_ver_recordes)
    {
      al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));
      Branco3 = al_map_rgb(255,255,255);
    }
    else
    {
      al_clear_to_color(al_map_rgba_f(0.2, 0.2, 0.2, 0.5));
      Branco3 = al_map_rgb(255,229,32);
    }

    al_set_target_bitmap(area_creditos);
    if (!na_area_creditos)
    {
      al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));
      Branco4 = al_map_rgb(255,255,255);
    }
    else
    {
      al_clear_to_color(al_map_rgba_f(0.2, 0.2, 0.2, 0.5));
      Branco4 = al_map_rgb(255,229,32);
    }

    al_set_target_bitmap(area_sair_do_jogo);
    if (!na_area_sair_do_jogo)
    {
      al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));
      Branco5 = al_map_rgb(255,255,255);
    }
    else
    {
      al_clear_to_color(al_map_rgba_f(0.2, 0.2, 0.2, 0.5));
      Branco5 = al_map_rgb(255,229,32);
    }

    // Colorimos o bitmap do botãoo de sair
    al_set_target_bitmap(botao_sair);
    al_clear_to_color(al_map_rgb(255, 0, 0));

    al_set_target_bitmap(area_menu_fundo);
    al_clear_to_color(al_map_rgba_f(0, 0, 0, 0.5));


    al_set_target_bitmap(al_get_backbuffer(janela));

    al_install_mouse();

    if (evento.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
      if((400 < evento.mouse.x) && (evento.mouse.x < LARGURA_TELA / 1.7 + 65) && (evento.mouse.y > ALTURA_TELA / 2.21) && (evento.mouse.y < ALTURA_TELA / 2.2 + 72))
        na_area_jogar = 1;
      else
        na_area_jogar = 0;

      if((400 < evento.mouse.x) && (evento.mouse.x < LARGURA_TELA / 1.7 + 65) && (evento.mouse.y > ALTURA_TELA / 1.8) && (evento.mouse.y < ALTURA_TELA / 1.8 + 72))
        na_area_informacao = 1;
      else
        na_area_informacao = 0;

      if((400 < evento.mouse.x) && (evento.mouse.x < LARGURA_TELA / 1.7 + 65) && (evento.mouse.y > ALTURA_TELA / 1.53 + 1) && (evento.mouse.y < ALTURA_TELA / 1.53 + 72))
        na_area_ver_recordes = 1;
      else
        na_area_ver_recordes = 0;

      if((400 < evento.mouse.x) && (evento.mouse.x < LARGURA_TELA / 1.7 + 65) && (evento.mouse.y > ALTURA_TELA / 1.33 + 1) && (evento.mouse.y < ALTURA_TELA / 1.33 + 72))
        na_area_creditos = 1;
      else
        na_area_creditos = 0;

      if((400 < evento.mouse.x) && (evento.mouse.x < LARGURA_TELA / 1.7 + 65) && (evento.mouse.y > ALTURA_TELA / 1.17 - 2) && (evento.mouse.y < ALTURA_TELA / 1.17 + 72))
        na_area_sair_do_jogo = 1;
      else
        na_area_sair_do_jogo = 0;
    }
    // Ou se o evento foi um clique do mouse
    else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && menu == 1)
    {
      int mousex = evento.mouse.x;
      int mousey = evento.mouse.y;

      if((350 < mousex) && (mousex < LARGURA_TELA / 1.5) && (mousey > ALTURA_TELA / 1.17 - 2) && (mousey < ALTURA_TELA / 1.17 + 72))
      {
        al_play_sample(clique_jogo, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
        return 0;
      }
      if((400 < mousex) && (mousex < LARGURA_TELA / 1.7 + 65) && (mousey > ALTURA_TELA / 1.33 + 1) && (mousey < ALTURA_TELA / 1.33 + 72) )
      {
        menu = 0;
        al_play_sample(clique_jogo, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
        al_clear_to_color(al_map_rgb(255,255,255));
        credits(LARGURA_TELA, ALTURA_TELA, janela, backgr, bomba);
        menu = 1;
      }
      if((465 < mousex) && (mousex < 815) && (mousey > 400) && (mousey< 472))
      {
        menu = 0;
        al_play_sample(clique_jogo, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
        al_clear_to_color(al_map_rgb(255,255,255));
        informacao(LARGURA_TELA, ALTURA_TELA, janela, backgr, bomba);
        menu = 1;
      }
      if((400 < mousex) && (mousex < LARGURA_TELA / 1.7 + 65) && (mousey > ALTURA_TELA / 2.21) && (mousey < ALTURA_TELA / 2.21 + 72 ))
      {
        al_play_sample(clique_jogo, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
        play = choose(LARGURA_TELA, ALTURA_TELA, janela, backgr, bomba);
        dificuldade = play;
      }
      if((400 < mousex) && (mousex < LARGURA_TELA / 1.7 + 65) && (mousey > ALTURA_TELA / 1.53 + 1) && (mousey< ALTURA_TELA / 1.53 + 72))
      {
        menu = 0;
        al_play_sample(clique_jogo, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
        al_clear_to_color(al_map_rgb(255,255,255));
        dificuldade = choose(LARGURA_TELA, ALTURA_TELA, janela, backgr, bomba);
        ranking(LARGURA_TELA, ALTURA_TELA, janela, backgr, bomba);
        menu = 1;
      }
    }

    if(play != 0)
    {
      jogar(backgr, bomba);
      play = 0;
      menu = 1;
    }

  }

  // Desaloca os recursos utilizados na aplicação
  al_destroy_bitmap(botao_sair);
  al_destroy_event_queue(fila_eventos);
  al_destroy_font(font1);
  al_destroy_font(font2);
  al_destroy_bitmap(backgr);
  al_destroy_bitmap(bomba);
  al_destroy_display(janela);

  return 0;
}
