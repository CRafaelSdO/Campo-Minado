
int credits(int screenwidth, int screenheight, ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *backgr, ALLEGRO_BITMAP *bomba)
{
  int voltar = 0;
  al_draw_bitmap(backgr, 0,0, NULL);
  al_draw_bitmap(bomba, screenwidth,screenheight , NULL);
  al_init_font_addon();
  al_init_ttf_addon();
  al_init_primitives_addon();

  //Definindo as cores a serem usadas
  ALLEGRO_COLOR Electric = al_map_rgb(255, 229, 32);
  ALLEGRO_COLOR BrightRed = al_map_rgb(250, 28, 3);
  ALLEGRO_COLOR Branco = al_map_rgb(255, 255, 255);
  ALLEGRO_COLOR Branco1, Branco2, Branco3, Branco4;
  ALLEGRO_BITMAP *area_menu_fundo = NULL;

  //Declarando o bitmap Voltar
  ALLEGRO_BITMAP *area_voltar = 0, *area_medio = 0, *area_facil = 0, *area_dificil = 0;
  area_voltar = al_create_bitmap(360, 76);
  int na_area_voltar = 0;

  //Carregando fontes
  ALLEGRO_FONT *font2 = al_load_ttf_font("fonts/retro.ttf", 35, NULL);
  ALLEGRO_FONT *font1 = al_load_ttf_font("fonts/retro3d.ttf", 150, NULL);

  //Carregando sons
  clique_jogo = al_load_sample("songs/clique.wav");

  //Carregando eventos
  ALLEGRO_EVENT_QUEUE *backpress = al_create_event_queue();
  al_register_event_source(backpress, al_get_display_event_source(display));
  al_register_event_source(backpress, al_get_mouse_event_source());
  ALLEGRO_EVENT eventback;

  float altura = 2.1;
  float distancia = 72;
  int done = 0;

  while(!done)
  {
    al_wait_for_event(backpress, &eventback);
    int mousex = eventback.mouse.x;
    int mousey = eventback.mouse.y;
    if(eventback.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
      if((screenwidth / 1.2 - 50 < mousex) && (mousex < screenwidth / 1.2 + 220) && (mousey > screenheight / 1.2 + 10 ) && (mousey < screenheight / 1.2  + 91))
      {
        al_play_sample(clique_jogo, 1.2, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
        done = 1;
      }
    }
    else if (eventback.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
      if((screenwidth / 1.2 - 50 < mousex) && (mousex < screenwidth / 1.2 + 220) && (mousey > screenheight / 1.2 + 10 ) && (mousey < screenheight / 1.2  + 91))
        na_area_voltar = 1;
      else
        na_area_voltar = 0;
    }

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(backgr, 0, 0, NULL);
    al_draw_bitmap(bomba, screenwidth / 2 - 256, screenheight / 2 - 256, NULL);

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

    al_set_target_bitmap(al_get_backbuffer(display));

    al_draw_bitmap(area_voltar, screenwidth / 1.2 - 50  , screenheight / 1.2 + 13 , 0.5);

    al_draw_text(font1,al_map_rgb(255,229,32),screenwidth/2,screenheight/4 - 100,ALLEGRO_ALIGN_CENTRE,"Creditos");

    //Nossos nomes
    al_draw_text(font2, Branco, screenwidth/2, screenheight/altura , ALLEGRO_ALIGN_CENTER, "Cicero Rafael");
    al_draw_text(font2, Branco, screenwidth/2, screenheight/altura + distancia, ALLEGRO_ALIGN_CENTER, "Lucas Ribeiro Raggi");
    al_draw_text(font2, Branco, screenwidth/2, screenheight/altura + distancia*2, ALLEGRO_ALIGN_CENTER, "Nelson Gomes Neto");
    al_draw_text(font2, Branco, screenwidth/2, screenheight/altura + distancia*3, ALLEGRO_ALIGN_CENTER, "Thiago");

    al_draw_rectangle(screenwidth / 1.2 - 50, screenheight / 1.2 + 10, screenwidth / 1.2 + 220, screenheight / 1.2 + 91, al_map_rgb(255, 255, 255), 6.0);
    al_draw_rectangle(screenwidth / 1.2 - 56, screenheight / 1.2 + 4, screenwidth / 1.2 + 226, screenheight / 1.2 + 97, al_map_rgb(0, 0, 0), 6.0);

    al_draw_text(font2, Branco1, 19*screenwidth / 20, 21*screenheight / 24, ALLEGRO_ALIGN_RIGHT, "Voltar");

    al_flip_display();
  }
}
