void iniciarTimer();
double obterTempoTimer();
void drawTempo();
void load_images();
int** alocaMatriz();
char** alocaMatrizChar();
void drawCampo(char espaco, int j, int i);
void floodfill(int jogada_linha, int jogada_coluna);
void completarFloodfill();
void explodir_tudo(int jogada_linha, int jogada_coluna);
void contorno(int jogada_linha, int jogada_coluna);
void gerarTabuleiro();
void jogada(int jogada_linha, int jogada_coluna);
void liberaMatriz();
void fprintaMatriz();
int EstaNoCampo(int x, int y);
void Checar(int x, int y);
void fazerTabuleiro();
int GdT();
void leMatriz();
int jogar(ALLEGRO_BITMAP *backgr, ALLEGRO_BITMAP *bomba);

void iniciarTimer()
{
	tempoInicial = al_get_time();
}

double obterTempoTimer()
{
	return al_get_time() - tempoInicial;
}

void drawTempo()
{
	cronometro = al_get_time() - newTempo;
	sprintf(stringTempo, "%.3lf", cronometro);
	al_draw_filled_rectangle( 25 , 170, 300, 266, al_map_rgba_f(0, 0, 0, 1));
	al_draw_filled_rectangle( 25 , 290, 300, 386, al_map_rgba_f(0, 0, 0, 1));
	al_draw_text(font, branco, 160, 180, ALLEGRO_ALIGN_CENTRE, "TEMPO:");
	al_draw_text(font, branco, 160, 230, ALLEGRO_ALIGN_CENTRE, stringTempo);
	sprintf(stringFlags, "%d", flags);
	al_draw_text(font, branco, 160, 300, ALLEGRO_ALIGN_CENTRE, "BOMBAS:");
	al_draw_text(font, branco, 160, 350, ALLEGRO_ALIGN_CENTRE, stringFlags);
}

void load_images()
{
	imagem = al_load_bitmap("imgs/bl.png");
	vazio = al_load_bitmap("imgs/vazio.png");
	um = al_load_bitmap("imgs/1.png");
	dois = al_load_bitmap("imgs/2.png");
	tres = al_load_bitmap("imgs/3.png");
	quatro = al_load_bitmap("imgs/4.png");
	cinco = al_load_bitmap("imgs/5.png");
	seis = al_load_bitmap("imgs/6.png");
	sete = al_load_bitmap("imgs/7.png");
	oito = al_load_bitmap("imgs/8.png");
	bomba = al_load_bitmap("imgs/bomba.png");
	flag = al_load_bitmap("imgs/flag.png");
}

int** alocaMatriz()
{
	int i;
	int** matriz = (int**)calloc(altura, sizeof(int*));
	for (i = 0; i < altura; i++)
	{
		matriz[i] = (int*)calloc(largura, sizeof(int));
	}
	return matriz;
}

char** alocaMatrizChar()
{
	int i;
	char** matriz = (char**)calloc(altura, sizeof(char*));
	for (i = 0; i < altura; i++)
	{
		matriz[i] = (char*)calloc(largura, sizeof(char));
	}
	return matriz;
}

void drawCampo(char espaco, int j, int i)
{
	iniciarTimer();
	if (espaco == '0' || espaco == '9')
		al_draw_bitmap(vazio, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	else if (espaco == '1')
		al_draw_bitmap(um, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	else if (espaco == '2')
		al_draw_bitmap(dois, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	else if (espaco == '3')
		al_draw_bitmap(tres, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	else if (espaco == '4')
		al_draw_bitmap(quatro, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	else if (espaco == '5')
		al_draw_bitmap(cinco, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	else if (espaco == '6')
		al_draw_bitmap(seis, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	else if (espaco == '7')
		al_draw_bitmap(sete, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	else if (espaco == '8')
		al_draw_bitmap(oito, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	else if (espaco == '/')
		al_draw_bitmap(bomba, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	else if (espaco == 'f')
		al_draw_bitmap(flag, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	else
		al_draw_bitmap(imagem, (distanciax + i * 25) * multiplicador_tamanho, (distanciay + j * 25) * multiplicador_tamanho, 0);
	drawTempo();

	if ((obterTempoTimer() < 1.0 / FRAMES_POR_SEGUNDO))
		al_rest((1.0 / FRAMES_POR_SEGUNDO) - obterTempoTimer());
	al_flip_display();
}

void floodfill(int jogada_linha, int jogada_coluna)
{
	iniciarTimer();
	if(tabuleiro[jogada_linha][jogada_coluna] == 0)
	{
		tabuleiro[jogada_linha][jogada_coluna] = 9;
		tabuleiro2[jogada_linha][jogada_coluna] = '0';

		win --;

		al_draw_bitmap(vazio, (distanciax + jogada_coluna * 25) * multiplicador_tamanho, (distanciay + jogada_linha * 25) * multiplicador_tamanho, 0);
		drawTempo();
		if ((obterTempoTimer() < 1.0 / FRAMES_POR_SEGUNDO))
			al_rest((1.0 / FRAMES_POR_SEGUNDO) - obterTempoTimer());
		al_flip_display();

		if(jogada_linha > 0 && jogada_coluna > 0)
			floodfill(jogada_linha - 1, jogada_coluna - 1);

		if(jogada_linha > 0 && jogada_coluna < largura - 1)
			floodfill(jogada_linha - 1, jogada_coluna + 1);

		if(jogada_linha < altura - 1 && jogada_coluna > 0)
			floodfill(jogada_linha + 1, jogada_coluna - 1);

		if(jogada_linha > 0 && jogada_coluna < largura - 1)
			floodfill(jogada_linha - 1, jogada_coluna + 1);

		if(jogada_linha < altura - 1)
			floodfill(jogada_linha + 1, jogada_coluna);

		if(jogada_coluna < largura - 1)
			floodfill(jogada_linha, jogada_coluna + 1);

		if(jogada_linha > 0)
			floodfill(jogada_linha - 1, jogada_coluna);

		if(jogada_coluna > 0)
			floodfill(jogada_linha , jogada_coluna - 1);
	}
	else
		return;
}

void completarFloodfill()
{
	int i;
	int j;
	for(i = 0; i < altura; i++)
	{
		for(j = 0; j < largura; j++)
		{
			if(tabuleiro2[i][j] == '0')
			{
				if(i > 0 && j > 0 && tabuleiro2[i - 1][j - 1] == '#')
				{
					tabuleiro2[i - 1][j - 1] = '0' + tabuleiro[i - 1][j - 1];
					drawCampo(tabuleiro2[i - 1][j - 1], i - 1, j - 1);
					win --;
				}
				if(i > 0 && tabuleiro2[i - 1][j] == '#')
				{
					tabuleiro2[i - 1][j] = '0' + tabuleiro[i - 1][j];
					drawCampo(tabuleiro2[i - 1][j], i - 1, j);
					win --;
				}
				if(i > 0 && j < largura - 1 && tabuleiro2[i - 1][j + 1] == '#')
				{
					tabuleiro2[i - 1][j + 1] = '0' + tabuleiro[i - 1][j + 1];
					drawCampo(tabuleiro2[i - 1][j + 1], i - 1, j + 1);
					win --;
				}

				if(j > 0 && tabuleiro2[i][j - 1] == '#')
				{
					tabuleiro2[i][j - 1] = '0' + tabuleiro[i][j - 1];
					drawCampo(tabuleiro2[i][j - 1], i, j - 1);
					win --;
				}
				if(j < altura - 1 && tabuleiro2[i][j + 1] == '#')
				{
					tabuleiro2[i][j + 1] = '0' + tabuleiro[i][j + 1];
					drawCampo(tabuleiro2[i][j + 1], i, j + 1);
					win --;
				}

				if(i < altura - 1 && j > 0 && tabuleiro2[i + 1][j - 1] == '#')
				{
					tabuleiro2[i + 1][j - 1] = '0' + tabuleiro[i + 1][j - 1];
					drawCampo(tabuleiro2[i + 1][j - 1], i + 1, j - 1);
					win --;
				}
				if(i < altura - 1 && tabuleiro2[i + 1][j] == '#')
				{
					tabuleiro2[i + 1][j] = '0' + tabuleiro[i + 1][j];
					drawCampo(tabuleiro2[i + 1][j], i + 1, j);
					win --;
				}
				if(i < altura - 1 && j < largura - 1 && tabuleiro2[i + 1][j + 1] == '#')
				{
					tabuleiro2[i + 1][j + 1] = tabuleiro[i + 1][j + 1] + '0';
					drawCampo(tabuleiro2[i + 1][j + 1], i + 1, j + 1);
					win --;
				}
			}
		}
	}
}

void explodir_tudo(int jogada_linha, int jogada_coluna)
{
	FRAMES_POR_SEGUNDO = 60;
	int i, j, iFim = 2, jFim = 2;
	while (bombas > 1)
	{
		for (i = 1; i < iFim; i ++)
		{
			jogada_linha --;
			if (all_directions)
			{
				if (tabuleiro[jogada_linha][jogada_coluna] == -1)
				{
					bombas --;
					jogada(jogada_linha, jogada_coluna);
				}
			}
		}
		for (j = 1; j < jFim; j ++)
		{
			jogada_coluna ++;
			if (all_directions)
			{
				if (tabuleiro[jogada_linha][jogada_coluna] == -1)
				{
					bombas --;
					jogada(jogada_linha, jogada_coluna);
				}
			}
		}
		iFim ++; jFim ++;
		for (i = 1; i < iFim; i ++)
		{
			jogada_linha ++;
			if (all_directions)
			{
				if (tabuleiro[jogada_linha][jogada_coluna] == -1)
				{
					bombas --;
					jogada(jogada_linha, jogada_coluna);
				}
			}
		}
		for (j = 1; j < jFim; j ++)
		{
			jogada_coluna --;
			if (all_directions)
			{
				if (tabuleiro[jogada_linha][jogada_coluna] == -1)
				{
					bombas --;
					jogada(jogada_linha, jogada_coluna);
				}
			}
		}
		iFim ++; jFim ++;
	}
}

void contorno(int jogada_linha, int jogada_coluna)
{
	int i, j;
	for (i = jogada_linha - 1; i < jogada_linha + 2; i ++)
	{
		for (j = jogada_coluna - 1; j < jogada_coluna + 2; j ++)
		{
			if (i >= 0 && j >= 0 && i < altura && j < largura && tabuleiro2[i][j] == '#')
			{
				jogada(i, j);
			}
		}
	}
}

void gerarTabuleiro()
{
	int i, j;
	for(i = 0; i < altura; i++)
	{
		for(j = 0; j < largura; j++)
		{
			tabuleiro2[i][j] = '#';
		}
	}
}

void jogada(int jogada_linha, int jogada_coluna)
{
	ALLEGRO_SAMPLE_ID *id_sample = NULL;
	id_sample = malloc(sizeof(ALLEGRO_SAMPLE_ID));
	clique_menu = al_load_sample("songs/clique_menu.wav");
	explosao = al_load_sample("songs/explosao.wav");
	floodfill_som = al_load_sample("songs/floodfill.wav");

	tabuleiro2[jogada_linha][jogada_coluna] = '0' + tabuleiro[jogada_linha][jogada_coluna];
	drawCampo(tabuleiro2[jogada_linha][jogada_coluna], jogada_linha, jogada_coluna);
	if(tabuleiro[jogada_linha][jogada_coluna] == -1)
	{
		al_play_sample(explosao, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		lose = 1;
	}
	else if(tabuleiro[jogada_linha][jogada_coluna] == 0)
	{
		al_play_sample(floodfill_som, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, id_sample);
		floodfill(jogada_linha, jogada_coluna);
		completarFloodfill();
		al_rest(0.01);
		al_stop_sample(id_sample);
	}
	else
	{
		al_play_sample(clique_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		win --;
	}
}

void liberaMatriz()
{
	int i;
	for (i = 0; i < altura; i++)
	{
		free(tabuleiro[i]);
	}
	free(tabuleiro);
}

void fprintaMatriz()
{
	int i, j;
	for (i = 0; i < altura; i++)
	{
		for (j = 0; j < largura; j++)
		{
			if (tabuleiro[i][j] >= 0)
			{
				fprintf(campo, " ");
			}
			fprintf(campo, "%d ", tabuleiro[i][j]);
		}
		fprintf(campo, "\n");
	}
	fprintf(campo, "\n");
}

int EstaNoCampo(int x, int y)
{
	if (x >= 0 && x < altura)
	{
		if (y >= 0 && y < largura)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

void Checar(int x, int y)
{
	int aux = 0, i, j;
	for (i = x - 1; i <= x + 1; i++)
	{
		for (j = y - 1; j <= y + 1; j++)
		{
			if (EstaNoCampo(i, j))
			{
				if (tabuleiro[i][j] == -1)
				{
					aux++;
				}
			}
		}
	}
	tabuleiro[x][y] = aux;
}

void fazerTabuleiro()
{
	int x, y, random = 1, i, j;
	if (!bombas){
		for (i = 0; i < altura; i++)
		{
			for (j = 0; j < largura; j++)
			{
				if (tabuleiro[i][j] == 0)
				{
					Checar(i, j);
				}
			}
		}
		fprintaMatriz();
		for (i = 0; i < altura; i++)
		{
			for (j = 0; j < largura; j++)
			{
				if (tabuleiro[i][j] > 0)
				{
					tabuleiro[i][j] = 0;
				}
			}
		}
	}
	else
	{
		srand((time(NULL)) / bombas);
		while(random)
		{
			y = rand() % largura;
			x = rand() % altura;
			random--;
			if (tabuleiro[x][y] == -1 || (x == firstI && y == firstJ))
				random++;
		}
		tabuleiro[x][y] = -1;
		bombas --;
		fazerTabuleiro();
	}
}

int GdT()
{
	tabuleiro = alocaMatriz();
	campo = fopen("campo.txt", "w");
	fazerTabuleiro();
	liberaMatriz();
	fclose(campo);
	return 0;
}

void leMatriz()
{
	int i, j;
	for (i = 0; i < altura; i++)
	{
		for (j = 0; j < largura; j++)
		{
			fscanf(campo, "%d", &tabuleiro[i][j]);
		}
	}
}

int jogar(ALLEGRO_BITMAP *backgr, ALLEGRO_BITMAP *bomba)
{
	font = al_load_ttf_font("fonts/retro.ttf", 35, 0);
	branco = al_map_rgb(255, 255, 255);

	score atual;
	double cronometroInicial, cronometroFinal;
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(backgr, 0, 0, 0);
	al_draw_bitmap(bomba, LARGURA_TELA / 2 - 256, ALTURA_TELA / 2 - 256, 0);
	int i, j;
	int temp, mousex, mousey;
	lose = 0; win = 1;
	if (dificuldade == 1)
	{
		largura = 8; altura = 8; bombas = 9;
		distanciax = 220;
		distanciay = 80;
		multiplicador_tamanho = 2;
		compensacao = 200;
	}
	else if (dificuldade == 2)
	{
		largura = 10; altura = 10; bombas = 15;
		distanciax = 195;
		distanciay = 55;
		multiplicador_tamanho = 2;
		compensacao = 250;
	}
	else
	{
		largura = 12; altura = 12; bombas = 30;
		distanciax = 170;
		distanciay = 30;
		multiplicador_tamanho = 2;
		compensacao = 300;
	}
	win  = (largura * altura) - bombas;


	load_images();

	for (i = 0; i < altura; i ++)
	{
		for (j = 0; j < largura; j ++)
		{
			iniciarTimer();
			al_draw_bitmap(imagem, (distanciax + j * 25) * multiplicador_tamanho, (distanciay + i * 25) * multiplicador_tamanho, 0);
			if ((obterTempoTimer() < 1.0 / FRAMES_POR_SEGUNDO))
			{
				al_rest((1.0 / FRAMES_POR_SEGUNDO) - obterTempoTimer());
			}
			al_flip_display();
		}
	}

	clique_menu = al_load_sample("songs/clique_menu.wav");
	explosao = al_load_sample("songs/explosao.wav");
	floodfill_som = al_load_sample("songs/floodfill.wav");
	inicio = al_load_sample("songs/inicio.wav");
	set_flag = al_load_sample("songs/set_flag.wav");
	take_flag = al_load_sample("songs/take_flag.wav");

	al_play_sample(inicio, 1.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

	if(dificuldade == 1)
		al_draw_rectangle(438, 160, 843, 563, al_map_rgb(0, 0, 0), 5.0);
	if(dificuldade == 2)
		al_draw_rectangle(390, 110, 890, 610, al_map_rgb(0, 0, 0), 5.0);
	if(dificuldade == 3)
		al_draw_rectangle(337, 60, 943, 665, al_map_rgb(0, 0, 0), 5.0);

	ALLEGRO_COLOR Branco1;
	Branco1 = al_map_rgb(255,255,255);

	al_draw_rectangle( 20 , -10, 305, 805, al_map_rgb(0, 0, 0), 7.0);
	al_draw_rectangle( 22 , -10, 303, 803, al_map_rgb(253, 152, 0), 7.0);
	al_draw_filled_rectangle( 25 , -10, 300, 800, al_map_rgba_f(0, 0, 0, 0.5));
	ALLEGRO_FONT *font2 = al_load_ttf_font("fonts/retro.ttf", 35, 0);
	al_draw_text(font2, Branco1, 160, 500, ALLEGRO_ALIGN_CENTRE, "Reiniciar");
	al_draw_text(font2, Branco1, 160 , 600, ALLEGRO_ALIGN_CENTRE, "Voltar");


	int sair = 0, first = 0;

	while (!sair)
	{
		iniciarTimer();
		if (win == 0)
		{
			cronometroFinal = al_get_time() - cronometroInicial;
			atual.tempo = cronometroFinal;
			al_clear_to_color(al_map_rgb(255,255,255));
			ganhou(LARGURA_TELA, ALTURA_TELA, janela, backgr, bomba, atual);
			sair = 1; continue;
		}
		if (lose == 1)
		{
			explodir_tudo(i, j);
			FRAMES_POR_SEGUNDO = 120;
			al_rest(0.6);
			perdeu(LARGURA_TELA, ALTURA_TELA, janela, backgr, bomba);
			sair = 1; continue;
		}
		while (!al_is_event_queue_empty(fila_eventos))
		{
			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);

			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				al_get_mouse_state(&state);
				mousex = evento.mouse.x;
				mousey = evento.mouse.y;

				if((25 < mousex) && (mousex < 290) && (mousey > 490 ) && (mousey < 550))
				{
					al_play_sample(clique_jogo, 1.2, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					jogar( backgr, bomba);
				}

				if((25 < mousex) && (mousex < 290) && (mousey > 575 ) && (mousey < 660))
				{
					al_play_sample(clique_jogo, 1.2, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					sair = 1;
					break;
				}

				temp = mousex - LARGURA_TELA/2 + compensacao;
				j = temp / 50;
				temp = mousey - ALTURA_TELA/2 + compensacao;
				i = temp / 50;
				if (state.buttons & 1)
				{
					if(i >= 0 && i < altura && j >= 0 && j < largura)
					{
						if (first == 0)
						{
							aux = bombas;
							first = 1; firstI = i; firstJ = j;
							GdT();
							campo = fopen("campo.txt", "r");
							tabuleiro = alocaMatriz();
							tabuleiro2 = alocaMatrizChar();
							leMatriz();
							gerarTabuleiro();
							bombas = aux; flags = bombas;
							cronometroInicial = al_get_time();
							newTempo = al_get_time();
						}
						if (tabuleiro2[i][j] == '#')
						{
							jogada(i, j);
						}
						else if (tabuleiro2[i][j] != '/' && tabuleiro2[i][j] != 'f')
						{
							contorno(i, j);
						}
					}
				}
				if (state.buttons & 2)
				{
					if(i >= 0 && i < altura && j >= 0 && j < largura && first == 1)
					{
						if (tabuleiro2[i][j] == '#')
						{
							al_play_sample(set_flag, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
							tabuleiro2[i][j] = 'f';
							flags --;
							drawCampo(tabuleiro2[i][j], i, j);
						}
						else if (tabuleiro2[i][j] == 'f')
						{
							al_play_sample(take_flag, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
							tabuleiro2[i][j] = '#';
							flags ++;
							drawCampo(tabuleiro2[i][j], i, j);
						}
					}
					else
					{
						al_play_sample(take_flag, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					}
				}
			}
		}
		if (first != 0)
		{
			drawTempo();
		}

    // Atualiza a tela
		if ((obterTempoTimer() < 1.0 / FRAMES_POR_SEGUNDO))
		{
			al_rest((1.0 / FRAMES_POR_SEGUNDO) - obterTempoTimer());
		}
		al_flip_display();
	}
}
