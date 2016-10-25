int informacao(int screenwidth, int screenheight, ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *backgr, ALLEGRO_BITMAP *bomba)
{
  //Desenha o PLano de Fundo
  al_draw_bitmap(backgr, 0,0, NULL);
  al_draw_bitmap(bomba, screenwidth,screenheight , NULL);
  //Inicia dependências do Allegro
  al_init_font_addon();
  al_init_ttf_addon();
  al_init_primitives_addon();
  //Definindo as cores a serem usadas
  ALLEGRO_COLOR Electric = al_map_rgb(255, 229, 32);
  ALLEGRO_COLOR BrightRed = al_map_rgb(250, 28, 3);
  ALLEGRO_COLOR Branco = al_map_rgb(255, 255, 255);
  ALLEGRO_COLOR Branco1, Branco2, Branco3, Branco4;
  ALLEGRO_COLOR Red  = al_map_rgb(250,31,3);
  ALLEGRO_COLOR Green  = al_map_rgb(102,241,10);
  ALLEGRO_COLOR Yellow = al_map_rgb(255,229,32);
  //Definindo Bitmaps
  ALLEGRO_BITMAP *area_voltar = 0, *area_medio = 0, *area_facil = 0, *area_dificil = 0;
  ALLEGRO_BITMAP *area_menu_fundo = NULL;
  area_voltar = al_create_bitmap(360, 76);
  int na_area_voltar = 0;
  //Carregando fontes
  ALLEGRO_FONT *font2 = al_load_ttf_font("fonts/retro.ttf", 35, NULL);
  ALLEGRO_FONT *font1 = al_load_ttf_font("fonts/retro.ttf", 100, NULL);
  ALLEGRO_FONT *font3 = al_load_ttf_font("fonts/retro.ttf", 45, NULL);
  //Carregando sons
  clique_jogo = al_load_sample("songs/clique.wav");
  //Carregando eventos
  ALLEGRO_EVENT_QUEUE *backpress = al_create_event_queue();
  al_register_event_source(backpress, al_get_display_event_source(display));
  al_register_event_source(backpress, al_get_mouse_event_source());
  ALLEGRO_EVENT eventback;
  //Variáveis de controle
  int done = 0;
  float altura = 5;
  float distancia = 72;
  int voltar = 0;
  //Inicia o loop de eventos
  while(!done)
  {
    al_wait_for_event(backpress, &eventback); //Espera por algum evento
    int mousex = eventback.mouse.x; //Pega a posição do mouse
    int mousey = eventback.mouse.y; //Pega a posição do mouse
    if(eventback.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) //Ao clicar
    {
      //Clique em "Voltar"
      if((screenwidth / 1.2 - 50 < mousex) && (mousex < screenwidth / 1.2 + 220) && (mousey > screenheight / 1.2 + 10 ) && (mousey < screenheight / 1.2  + 91))
      {
        al_play_sample(clique_jogo, 1.2, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
        done = 1; //Acaba com o loop
      }
    }
    else if (eventback.type == ALLEGRO_EVENT_MOUSE_AXES) //Apontando para
    {
      //Sobre "Voltar"
      if((screenwidth / 1.2 - 50 < mousex) && (mousex < screenwidth / 1.2 + 220) && (mousey > screenheight / 1.2 + 10 ) && (mousey < screenheight / 1.2  + 91))
        na_area_voltar = 1;
      else
        na_area_voltar = 0;
    }

    al_clear_to_color(al_map_rgb(0, 0, 0)); //Limpa a tela
    //Desenha o Plano de Fundo
    al_draw_bitmap(backgr, 0, 0, NULL);
    al_draw_bitmap(bomba, screenwidth / 2 - 256, screenheight / 2 - 256, NULL);
    //Modificando o Bitmap "area_voltar" com o efeito "Apontar"
    al_set_target_bitmap(area_voltar);
    if (!na_area_voltar)
    {
      al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));
      Branco1 = al_map_rgb(255,255,255);
    }
    else
    {
      al_clear_to_color(al_map_rgba_f(0.2, 0.2, 0.2, 0.5));
      Branco1 = al_map_rgb(255,229,32);
    }
    //Usando a tela
    al_set_target_bitmap(al_get_backbuffer(display));
    //Desenha os elementos na tela
    al_draw_bitmap(area_voltar, screenwidth / 1.2 - 50  , screenheight / 1.2 + 13 , 0.5);

    al_draw_text(font1,al_map_rgb(255,229,32),screenwidth/2,screenheight/4 - 170,ALLEGRO_ALIGN_CENTRE,"INFORMACAO");

    al_draw_text(font2, Green, 300 , screenheight/altura + 40, ALLEGRO_ALIGN_CENTER, "FACIL");
    al_draw_text(font2, BrightRed, 500 , screenheight/altura+ 40 , ALLEGRO_ALIGN_CENTER, "BOMBAS");
    al_draw_text(font2, Branco, 620, screenheight/altura+ 40 , ALLEGRO_ALIGN_CENTER, "9");
    al_draw_text(font2, BrightRed, 800 , screenheight/altura+ 40 , ALLEGRO_ALIGN_CENTER, "TAMANHO");
    al_draw_text(font2, Branco, 970 , screenheight/altura+ 40 , ALLEGRO_ALIGN_CENTER, "8X8");

    al_draw_text(font2, Yellow, 300 , screenheight/altura + 130, ALLEGRO_ALIGN_CENTER, "MEDIO");
    al_draw_text(font2, BrightRed, 500 , screenheight/altura+ 130 , ALLEGRO_ALIGN_CENTER, "BOMBAS");
    al_draw_text(font2, Branco, 620, screenheight/altura+ 130 , ALLEGRO_ALIGN_CENTER, "15");
    al_draw_text(font2, BrightRed, 800 , screenheight/altura+ 130 , ALLEGRO_ALIGN_CENTER, "TAMANHO");
    al_draw_text(font2, Branco, 970 , screenheight/altura+ 130 , ALLEGRO_ALIGN_CENTER, "10X10");

    al_draw_text(font2, Red, 308 , screenheight/altura + 220, ALLEGRO_ALIGN_CENTER, "DIFICIL");
    al_draw_text(font2, BrightRed, 500 , screenheight/altura+ 220 , ALLEGRO_ALIGN_CENTER, "BOMBAS");
    al_draw_text(font2, Branco, 620, screenheight/altura+ 220 , ALLEGRO_ALIGN_CENTER, "30");
    al_draw_text(font2, BrightRed, 800 , screenheight/altura+ 220 , ALLEGRO_ALIGN_CENTER, "TAMANHO");
    al_draw_text(font2, Branco, 970 , screenheight/altura+ 220 , ALLEGRO_ALIGN_CENTER, "12X12");

    al_draw_text(font2, Green, 308 , screenheight/altura + 310, NULL,
                "CLIQUE ESQUERDO -> ABRIR LOCAL");
    al_draw_text(font2, Red, 308 , screenheight/altura + 400, NULL,
                "CLIQUE DIREITO  -> MARCAR LOCAL");

    al_draw_rectangle(screenwidth /2 - 420, 150, screenwidth /2 + 420, 240, al_map_rgba_f(0, 0, 0, 0.8), 8.0);
    al_draw_rectangle(screenwidth /2 - 420, 240, screenwidth /2 + 420, 330, al_map_rgba_f(0, 0, 0, 0.8), 8.0);
    al_draw_rectangle(screenwidth /2 - 420, 330, screenwidth /2 + 420, 420, al_map_rgba_f(0, 0, 0, 0.8), 8.0);

    al_draw_rectangle(screenwidth / 1.2 - 50, screenheight / 1.2 + 10, screenwidth / 1.2 + 220, screenheight / 1.2 + 91, al_map_rgb(255, 255, 255), 6.0);
    al_draw_rectangle(screenwidth / 1.2 - 56, screenheight / 1.2 + 4, screenwidth / 1.2 + 226, screenheight / 1.2 + 97, al_map_rgb(0, 0, 0), 6.0);

    al_draw_text(font2, Branco1, 19*screenwidth / 20, 21*screenheight / 24, ALLEGRO_ALIGN_RIGHT, "Voltar");
    //Atualiza o frame
    al_flip_display();
  }
  //Limpa a memória RAM
  al_destroy_event_queue(backpress);
  al_destroy_font(font1);
  al_destroy_font(font2);
  al_destroy_bitmap(area_voltar);
  al_destroy_bitmap(area_facil);
  al_destroy_bitmap(area_medio);
  al_destroy_bitmap(area_dificil);
  al_destroy_bitmap(area_menu_fundo);
  al_destroy_sample(victory);
}
