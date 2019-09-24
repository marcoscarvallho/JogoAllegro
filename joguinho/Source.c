#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<allegro5/allegro.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_image.h> 
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_audio.h>
#include<allegro5/allegro_acodec.h>
#include<allegro5/allegro_primitives.h>

#define LARGURATELA 1024
#define ALTURATELA 768
#define FPS 5
#define DICA 100

void comojogar(ALLEGRO_FONT *fonte, ALLEGRO_FONT *fonte2, ALLEGRO_EVENT_QUEUE *fila_eventos, ALLEGRO_DISPLAY *janelaMenu,ALLEGRO_BITMAP *imagem[], ALLEGRO_EVENT evento);
void jogar(ALLEGRO_FONT *fonte, ALLEGRO_FONT *fonte2, ALLEGRO_EVENT_QUEUE *fila_eventos, ALLEGRO_DISPLAY *janelaMenu,ALLEGRO_BITMAP *imagem[], ALLEGRO_BITMAP *imagem2, ALLEGRO_EVENT evento, ALLEGRO_BITMAP *imagem5[], ALLEGRO_BITMAP *imagem0[], int resp1);
int carregar(ALLEGRO_BITMAP *imagem[],ALLEGRO_BITMAP *imagem0[]);
void carregarm(ALLEGRO_BITMAP *imagem3[]);
void carregarf(ALLEGRO_BITMAP *imagem5[]);

void error_msg(char *text){
	al_show_native_message_box(NULL,"ERRO",	"Ocorreu o seguinte erro e o programa sera finalizado:",text,NULL,ALLEGRO_MESSAGEBOX_ERROR);
}

int main (int argc, char **argv) {
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *imagem[17];
	ALLEGRO_BITMAP *imagem3[14];
	ALLEGRO_BITMAP *imagem4;
	ALLEGRO_BITMAP *imagem0[6];
	ALLEGRO_BITMAP *imagem5[6];
	ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
	ALLEGRO_BITMAP *imagem2 = NULL;
	ALLEGRO_DISPLAY *janelaMenu = NULL;
	ALLEGRO_FONT *fonte = NULL;
	ALLEGRO_FONT *fonte2= NULL;
	ALLEGRO_EVENT evento;
	ALLEGRO_AUDIO_STREAM *musica = NULL;
	int sair = 0,op=0, op1 = 0, op2= 0, resp=0, tempo = 0, tempoi = 0, resp1, j=0, ca = 1,b = 1500;
	float a = 0;
	int na_area_central = 0;
	al_init();
	if (!al_init()) {
		printf ("Allegro não funcionou ... \n\n");
		exit(1);
	}

	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	timer= al_create_timer(1.0/FPS);
	if(!timer){
		error_msg("falha ao criar temporizador");
		return 0;
	}
	janelaMenu = al_create_display(LARGURATELA, ALTURATELA);
	al_clear_to_color(al_map_rgb(0, 100, 0));
	if (!janelaMenu){
		printf("Falha ao criar janela");
		return -1;
	}
	fonte = al_load_font("fonte.ttf", 150, 0);
	if (!fonte){
		al_destroy_display(janelaMenu);
		printf("Falha ao carregar fonte\n");
		system("pause");
		return -1;
	}
	fonte2 = al_load_font("fonte.ttf", 48, 0);
	if (!fonte2){
		al_destroy_display(janelaMenu);
		printf("Falha ao carregar fonte\n");
		system("pause");
		return -1;
	}
	if (!al_install_mouse()){
		error_msg("Falha ao inicializar o mouse");
		al_destroy_display(janelaMenu);
		return -1;
	}
	if (!al_install_keyboard()){
		error_msg("Falha ao inicializar o teclado");
		return 0;
	}
	if (!al_set_system_mouse_cursor(janelaMenu, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)){
		error_msg("Falha ao atribuir ponteiro do mouse");
		al_destroy_display(janelaMenu);
		return -1;
	}
	fila_eventos = al_create_event_queue();
	if (!fila_eventos){
		error_msg("Falha ao inicializar o fila de eventos");
		al_destroy_display(janelaMenu);
		return -1;
	}
	if(!al_install_audio()){
		error_msg("Falha ao inicializar o audio");
		system("pause");
		return 0;
	}
	if (!al_init_acodec_addon())
	{
		fprintf(stderr, "Falha ao inicializar codecs de áudio.\n");
		system("pause");
		return false;
	}
	if (!al_reserve_samples(1))
	{
		fprintf(stderr, "Falha ao alocar canais de áudio.\n");
		system("pause");
		return false;
	}
	musica = al_load_audio_stream("Skyward-Bound.ogg", 4, 1024);
	if (!musica)
	{
		fprintf(stderr, "Falha ao carregar audio.\n");
		system("pause");
		return false;
	}
	al_register_event_source(fila_eventos, al_get_display_event_source(janelaMenu));
	al_flip_display();
	al_start_timer(timer);
	al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
	al_set_audio_stream_playing(musica, true);
	al_set_audio_stream_playmode(musica, ALLEGRO_PLAYMODE_LOOP);
	al_register_event_source(fila_eventos, al_get_mouse_event_source());
	al_register_event_source(fila_eventos, al_get_keyboard_event_source());
	imagem2 = al_load_bitmap("mapafinalreal.bmp");
	carregar(imagem, imagem0);
	carregarm(imagem3);
	imagem4 = al_load_bitmap("estrelas.bmp");
	carregarf(imagem5);
	al_convert_mask_to_alpha(imagem3[0],al_map_rgb(255,0,255));	
	al_convert_mask_to_alpha(imagem3[1],al_map_rgb(255,0,255));
	al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
	while (!sair){
		while (!al_is_event_queue_empty(fila_eventos)){
			al_wait_for_event(fila_eventos, &evento);
			if(evento.type == ALLEGRO_EVENT_TIMER){
				tempo = tempo + 1;
				if(tempo==14)
					tempo=0;
			}
			if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
				sair=1;
			if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
				if (evento.mouse.x >= LARGURATELA * 0.945 -30  && evento.mouse.y >= 710 && evento.mouse.x <= LARGURATELA * 0.945+70  && evento.mouse.y <= 750){
					op= 1;
				}else{
					op=0;			
				}
				if (evento.mouse.x >= LARGURATELA /2 -40  && evento.mouse.y >= 350 && evento.mouse.x <= LARGURATELA /2+40  && evento.mouse.y <= 380){
					op1= 1;
				}else{
					op1=0;			
				}
				if (evento.mouse.x >= LARGURATELA /2 -75  && evento.mouse.y >= 430 && evento.mouse.x <= LARGURATELA /2+75  && evento.mouse.y <= 460){
					op2= 1;
				}else{
					op2=0;			
				}

			}
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
				if (evento.mouse.x >= LARGURATELA * 0.945 -30  && evento.mouse.x <= LARGURATELA * 0.945+70 && evento.mouse.y <= 750  && evento.mouse.y >= 710 ){
					sair = 1;
				}
				else if(evento.mouse.x >= LARGURATELA /2 -75  && evento.mouse.y >= 430 && evento.mouse.x <= LARGURATELA /2+75  && evento.mouse.y <= 460){
					resp = 1;
				}
				else if(evento.mouse.x >= LARGURATELA /2 -40  && evento.mouse.y >= 350 && evento.mouse.x <= LARGURATELA /2+40  && evento.mouse.y <= 380){
					resp = 2;
				}
			}
			else if (evento.type == ALLEGRO_EVENT_KEY_UP){
				//verifica qual tecla foi pressionada
				switch(evento.keyboard.keycode){
				case ALLEGRO_KEY_ESCAPE:
					sair = 1;
				default:
					break;
				}
			}
		}
		al_set_target_bitmap(al_get_backbuffer(janelaMenu));
		al_draw_bitmap(imagem4, 0, 0, 0);
		if(tempo == 1)
			al_draw_bitmap(imagem3[1], 330, 240, 0);
		else if(tempo == 2)
			al_draw_bitmap(imagem3[2], 330, 240, 0);
		else if(tempo == 3)
			al_draw_bitmap(imagem3[3], 330, 240, 0);
		else if(tempo == 4)
			al_draw_bitmap(imagem3[4], 330, 240, 0);
		else if(tempo == 5)
			al_draw_bitmap(imagem3[5], 330, 240, 0);
		else if(tempo == 6)
			al_draw_bitmap(imagem3[6], 330, 240, 0);
		else if(tempo == 7)
			al_draw_bitmap(imagem3[7], 330, 240, 0);
		else if(tempo == 8)
			al_draw_bitmap(imagem3[8], 330, 240, 0);
		else if(tempo == 9)
			al_draw_bitmap(imagem3[9], 330, 240, 0);
		else if(tempo == 10)
			al_draw_bitmap(imagem3[10], 330, 240, 0);
		else if(tempo == 11)
			al_draw_bitmap(imagem3[11], 330, 240, 0);
		else if(tempo == 12)
			al_draw_bitmap(imagem3[12], 330, 240, 0);
		else if(tempo == 13)
			al_draw_bitmap(imagem3[13], 330, 240, 0);
		else
			al_draw_bitmap(imagem3[0], 330, 240, 0);
		switch (resp){
		case 0:
			if(op==0){
				if((tempo == 0||tempo == 3||tempo == 6||tempo == 9||tempo == 12) && ca == 1){
					a = a + 0.5;
					al_draw_bitmap(imagem[3], a, 680, 0);
				}
				else if ((tempo == 1||tempo == 4||tempo == 7||tempo == 10||tempo == 13) && ca == 1){
					a = a + 0.5;
					al_draw_bitmap(imagem[4], a, 680, 0);
				}
				else if(ca==1){
					a = a + 0.5;
					al_draw_bitmap(imagem[5], a, 680, 0);
				}	
				if((tempo == 0||tempo == 3||tempo == 6||tempo == 9||tempo == 12) && ca == 2){
					a = a - 0.5;
					al_draw_bitmap(imagem[9], a, 680, 0);
				}
				else if ((tempo == 1||tempo == 4||tempo == 7||tempo == 10||tempo == 13) && ca == 2){
					a = a - 0.5;
					al_draw_bitmap(imagem[10], a, 680, 0);
				}
				else if (ca == 2){
					a = a - 0.5;
					al_draw_bitmap(imagem[11], a, 680, 0);
				}
				al_draw_text(fonte2, al_map_rgb(255, 0, 0), LARGURATELA * 0.945 , 710, ALLEGRO_ALIGN_CENTRE, "Sair");
			}
			else{
				al_draw_bitmap(imagem[16], 840, 680, 0);
				if (tempoi == 0)
					al_draw_bitmap(imagem[15], a, 680, 0);
				else if(tempoi == 1)
					al_draw_bitmap(imagem[15], a, 680, 0);
				else
					al_draw_bitmap(imagem[15], a, 680, 0);
				al_draw_text(fonte2, al_map_rgb(255, 255, 255), LARGURATELA * 0.945 , 710, ALLEGRO_ALIGN_CENTRE, "Sair");
			}
			if(op2==0)
				al_draw_text(fonte2, al_map_rgb(0, 0, 0), LARGURATELA / 2, 420, ALLEGRO_ALIGN_CENTRE, "Instrucoes");
			else
				al_draw_text(fonte2, al_map_rgb(255, 0, 0), LARGURATELA / 2, 420, ALLEGRO_ALIGN_CENTRE, "Instrucoes");
			if(op1 ==0)
				al_draw_text(fonte2, al_map_rgb(0, 0, 0), LARGURATELA / 2, 340, ALLEGRO_ALIGN_CENTRE, "Jogar");
			else
				al_draw_text(fonte2, al_map_rgb(255, 0, 0), LARGURATELA / 2, 340, ALLEGRO_ALIGN_CENTRE, "Jogar");
			al_draw_text(fonte, al_map_rgb(255, 0, 0), LARGURATELA / 2, 70, ALLEGRO_ALIGN_CENTRE, "Olaf!");
			al_draw_text(fonte2, al_map_rgb(255, 255, 255), LARGURATELA / 2, 200, ALLEGRO_ALIGN_CENTRE, "O cachorro aventureiro");

			if(a>800)
				ca = 2;
			if(a<0)
				ca = 1;
			break;
		case 1:
			comojogar(fonte, fonte2, fila_eventos, janelaMenu, imagem, evento);
			resp=0;
			break;
		case 2:
			resp1 = carregar(imagem, imagem0);
			while(b != 0){
				//al_draw_ellipse(0,0,LARGURATELA, ALTURATELA, al_map_rgb(0,0,0),b);
				al_draw_circle(LARGURATELA/2, ALTURATELA/2,700, al_map_rgb(0,0,0),b);
				b = b - 50;
				al_flip_display();
				al_rest(0.02);
				al_draw_bitmap(imagem2, 0, 0, 0);
			}
			jogar(fonte, fonte2, fila_eventos, janelaMenu, imagem, imagem2, evento, imagem5, imagem0, resp1);
			resp = 0;
			while(b != 1500){
				al_draw_circle(LARGURATELA/2, ALTURATELA/2,700, al_map_rgb(0,0,0),b);
				b = b + 50;
				al_flip_display();
				al_rest(0.02);
			}
			break;
		}
		//al_rest(0.2);
		al_flip_display();
	}
	al_destroy_font(fonte);
	al_destroy_font(fonte2);
	al_destroy_display(janelaMenu);
	al_destroy_event_queue(fila_eventos);
	al_destroy_timer(timer);
	al_destroy_bitmap(imagem4);	
	al_destroy_bitmap(imagem2);
	al_destroy_audio_stream(musica);
	for(j=0;j<6;j = j+1){
		al_destroy_bitmap(imagem5[j]);
		al_destroy_bitmap(imagem0[j]);
	}
	for(j = 0; j<17; j = j+1){
		al_destroy_bitmap(imagem[j]);
	}
	for(j = 0; j<14; j = j+1){
		al_destroy_bitmap(imagem3[j]);
	}
	return 0;
}

void comojogar(ALLEGRO_FONT *fonte, ALLEGRO_FONT *fonte2, ALLEGRO_EVENT_QUEUE *fila_eventos, ALLEGRO_DISPLAY *janelaMenu,ALLEGRO_BITMAP *imagem[], ALLEGRO_EVENT evento){
	int resp = 0, op=0;
	al_clear_to_color(al_map_rgb(100, 100, 200));
	al_draw_text(fonte, al_map_rgb(255, 0, 0), LARGURATELA / 2, 70, ALLEGRO_ALIGN_CENTRE, "Instrucoes");
	al_draw_text(fonte2, al_map_rgb(255, 255, 255), LARGURATELA / 2, 200, ALLEGRO_ALIGN_CENTRE, "Ao comecar o jogo, Olaf se apresentara, ja com trajes tipicos do pais");
	al_draw_text(fonte2, al_map_rgb(255, 255, 255), LARGURATELA / 2, 240, ALLEGRO_ALIGN_CENTRE, "para onde viajara. Apos sua apresentacao, ele comecara um dialogo");
	al_draw_text(fonte2, al_map_rgb(255, 255, 255), LARGURATELA / 2, 280, ALLEGRO_ALIGN_CENTRE, "com o jogador, dialogo no qual ele contara curiosidades sobre seu");
	al_draw_text(fonte2, al_map_rgb(255, 255, 255), LARGURATELA / 2, 320, ALLEGRO_ALIGN_CENTRE, "destino, sem informar qual sera. Em todos os momentos o jogador podera");
	al_draw_text(fonte2, al_map_rgb(255, 255, 255), LARGURATELA / 2, 360, ALLEGRO_ALIGN_CENTRE, "escolher entre as opcoes o nome do pais que ele visitara, sendo o objetivo");
	al_draw_text(fonte2, al_map_rgb(255, 255, 255), LARGURATELA / 2, 400, ALLEGRO_ALIGN_CENTRE, "do usuario acertar o pais");
	al_draw_bitmap(imagem[3], 100, 100, 0);
	al_draw_bitmap(imagem[9], 824, 100, 0);
	al_register_event_source(fila_eventos, al_get_mouse_event_source());
	al_register_event_source(fila_eventos, al_get_keyboard_event_source());
	while (1){
		while (!al_is_event_queue_empty(fila_eventos)){
			al_wait_for_event(fila_eventos, &evento);
			if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
				return;
			if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
				if (evento.mouse.x >= LARGURATELA * 0.945 -40  && evento.mouse.y >= 710 && evento.mouse.x <= LARGURATELA * 0.945+20  && evento.mouse.y <= 750){
					op= 1;
				}
				else
					op= 0;
			}
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
				if (evento.mouse.x >= LARGURATELA * 0.945 -40  &&  evento.mouse.y <= 750  && evento.mouse.x <= LARGURATELA * 0.945+20 && evento.mouse.y >= 710 ){
					return;
				}
			}
			else if (evento.type == ALLEGRO_EVENT_KEY_UP){
				//verifica qual tecla foi pressionada
				switch(evento.keyboard.keycode){
				case ALLEGRO_KEY_ESCAPE:
					return;
				default:
					break;
				}
			}
		}

		if(op==0){
			al_draw_filled_rectangle(840,680,935,765,al_map_rgb(100,100,200));
			al_draw_text(fonte2, al_map_rgb(255, 0, 0), LARGURATELA * 0.945 , 710, ALLEGRO_ALIGN_CENTRE, "Voltar");
		}
		else{
			al_draw_bitmap(imagem[0], 865, 680, 0);
			al_draw_text(fonte2, al_map_rgb(0, 0, 0), LARGURATELA * 0.945 , 710, ALLEGRO_ALIGN_CENTRE, "Voltar");
		}
		al_flip_display();
	}
}

void jogar(ALLEGRO_FONT *fonte, ALLEGRO_FONT *fonte2, ALLEGRO_EVENT_QUEUE *fila_eventos, ALLEGRO_DISPLAY *janelaMenu,ALLEGRO_BITMAP *imagem[], ALLEGRO_BITMAP *imagem2, ALLEGRO_EVENT evento, ALLEGRO_BITMAP *imagem5[], ALLEGRO_BITMAP *imagem0[], int resp1){
	int resp = 0, op=0, sair = 0, j = 0, i=0, timer=0, op2=0, l=0, c=0, tecla = 0, m = 0, n = 0, bot1 = 0, bot2 = 0, tela = 0, verifica = 0, resposta, ab=0, az =0 ;
	char pais [6][30], paisjogo[4][30];
	ALLEGRO_BITMAP *imagemr[2];
	float a= LARGURATELA/2, b = ALTURATELA / 2;
	imagemr[0] = al_load_bitmap("all.bmp");
	imagemr[1] = al_load_bitmap("all2.bmp");
	strcpy(pais[0], "Alemanha\0");
	strcpy(pais[1], "Brasil\0");
	strcpy(pais[2], "Canada\0");
	strcpy(pais[3], "China\0");
	strcpy(pais[4], "Espanha\0");
	strcpy(pais[5], "Estados Unidos\0");
	srand(time(NULL));
	resposta = (rand()%4) + 1;
	do{
		ab = rand()%6;
		if(i != resposta - 1){
			strcpy(paisjogo[i],pais[ab]);
			az = 0;
			do{
				if((ab == resp1) || (strcmp(paisjogo[i],paisjogo[az])==0 && az != i)){
					do{
						ab = rand()%6;
					}while(ab == resp1);
					strcpy(paisjogo[i],pais[ab]);
					az = -1;
				}
				else if(az == i && i != resposta - 1){
					strcpy(paisjogo[i],pais[ab]);
					sair = 1;
				}
				else if((az == i && i != resposta - 1)){
					sair = 1;
				}
				az = az + 1;
			}while(!sair);
		}
		else if(i == resposta-1)
			strcpy(paisjogo[i], pais[resp1]);
		sair = 0;
		i = i + 1;
	}while(i!=4);
	i = 0;
	j = 4;
	al_register_event_source(fila_eventos, al_get_mouse_event_source());
	al_register_event_source(fila_eventos, al_get_keyboard_event_source());
	while (1){
		while (!al_is_event_queue_empty(fila_eventos)){
			al_wait_for_event(fila_eventos, &evento);
			if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
				return;
			if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
				if (evento.mouse.x >= LARGURATELA * 0.945 -40  && evento.mouse.y >= 710 && evento.mouse.x <= LARGURATELA * 0.945+20  && evento.mouse.y <= 750){
					op= 1;
				}
				else
					op= 0;
				if((evento.mouse.x >= 160  && evento.mouse.y >= 110 && evento.mouse.x <= 450  && evento.mouse.y <= 240) || (evento.mouse.x >= 20  && evento.mouse.y >= 180 && evento.mouse.x <= 380  && evento.mouse.y <= 300) || (evento.mouse.x >= 120  && evento.mouse.y >= 300 && evento.mouse.x <= 340  && evento.mouse.y <= 423)  ){
					op2 = 1;
				}
				else if(evento.mouse.x >= 220  && evento.mouse.y >= 425 && evento.mouse.x <= 400 && evento.mouse.y <= 650){
					op2 = 2;
				}
				else if(evento.mouse.x >= 458  && evento.mouse.y >= 138 && evento.mouse.x <= 597 && evento.mouse.y <= 342){
					op2 = 3;
				}
				else if(evento.mouse.x >= 600 && evento.mouse.y >= 138 && evento.mouse.x <= 1000 && evento.mouse.y <= 442){
					op2 = 4;
				}
				else if(evento.mouse.x >= 450 && evento.mouse.y >= 350 && evento.mouse.x <= 600 && evento.mouse.y <= 598){
					op2 = 5;
				}
				else if(evento.mouse.x >= 750 && evento.mouse.y >= 425 && evento.mouse.x <= 1000 && evento.mouse.y <= 620){
					op2 = 6;
				}
				else
					op2=0;
			}
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
				if (evento.mouse.x >= LARGURATELA * 0.945 -40  &&  evento.mouse.y <= 750  && evento.mouse.x <= LARGURATELA * 0.945+20 && evento.mouse.y >= 710 ){
					for(j=0;j<2;j = j+1){
						al_destroy_bitmap(imagemr[j]);
					}
					return;
				}
				if(resposta == bot1){
					if((evento.mouse.x >= 160  && evento.mouse.y >= 110 && evento.mouse.x <= 450  && evento.mouse.y <= 240) || (evento.mouse.x >= 20  && evento.mouse.y >= 180 && evento.mouse.x <= 380  && evento.mouse.y <= 300) || (evento.mouse.x >= 120  && evento.mouse.y >= 300 && evento.mouse.x <= 340  && evento.mouse.y <= 423)  ){
						bot2 = 1;
					}
					else if(evento.mouse.x >= 220  && evento.mouse.y >= 425 && evento.mouse.x <= 400 && evento.mouse.y <= 650){
						bot2 = 2;
					}
					else if(evento.mouse.x >= 458  && evento.mouse.y >= 138 && evento.mouse.x <= 597 && evento.mouse.y <= 342){
						bot2 = 3;
					}
					else if(evento.mouse.x >= 600 && evento.mouse.y >= 138 && evento.mouse.x <= 1000 && evento.mouse.y <= 442){
						bot2 = 4;
					}
					else if(evento.mouse.x >= 450 && evento.mouse.y >= 350 && evento.mouse.x <= 600 && evento.mouse.y <= 598){
						bot2 = 5;
					}
					else if(evento.mouse.x >= 750 && evento.mouse.y >= 425 && evento.mouse.x <= 1000 && evento.mouse.y <= 620){
						bot2 = 6;
					}
					printf("%d", bot2);

				}
			}
			else if (evento.type == ALLEGRO_EVENT_KEY_UP && bot1 != resposta){
				//verifica qual tecla foi pressionada
				switch(evento.keyboard.keycode){
				case ALLEGRO_KEY_DOWN:
					switch(tela){
					case 0:
						tela = 1;
						break;
					case 1:
						tela = 2;
						break;
					case 2:
						tela = 1;
						break;
					case 3:
						tela = 4;
						break;
					case 4:
						tela = 3;
						break;
					default:
						break;
					}
					break;
				case ALLEGRO_KEY_UP:
					switch(tela){
					case 0:
						tela = 2;
						break;
					case 1:
						tela = 2;
						break;
					case 2:
						tela = 1;
						break;
					case 3:
						tela = 4;
						break;
					case 4:
						tela = 3;
						break;
					default:
						break;
					}
					break;
				case ALLEGRO_KEY_LEFT:
					switch(tela){
					case 0:
						tela = 3;
						break;
					case 1:
						tela = 3;
						break;
					case 2:
						tela = 4;
						break;
					case 3:
						tela = 1;
						break;
					case 4:
						tela = 2;
						break;
					default:
						break;
					}
					break;
				case ALLEGRO_KEY_RIGHT:
					switch(tela){
					case 0:
						tela = 3;
						break;
					case 1:
						tela = 3;
						break;
					case 2:
						tela = 4;
						break;
					case 3:
						tela = 1;
						break;
					case 4:
						tela = 2;
						break;
					default:
						break;
					}
					break;
				case ALLEGRO_KEY_ENTER:
					switch(tela){
					case 1:
						bot1 = 1;
						break;
					case 2:
						bot1 = 2;
						break;
					case 3:
						bot1 = 3;
						break;
					case 4:
						bot1 = 4;
						break;
					default:
						break;
					}
					break;
				case ALLEGRO_KEY_PAD_ENTER:
					switch(tela){
					case 1:
						bot1 = 1;
						break;
					case 2:
						bot1 = 2;
						break;
					case 3:
						bot1 = 3;
						break;
					case 4:
						bot1 = 4;
						break;
					default:
						break;
					}
					break;
				case ALLEGRO_KEY_ESCAPE:
					for(j=0;j<2;j = j+1){
						al_destroy_bitmap(imagemr[j]);
					}
					return;
					break;
				default:
					break;
				}
			}
		}
		if(op2 == 1){
			al_draw_bitmap(imagem5[0], 0, 0, 0);
			al_draw_text(fonte2, al_map_rgb(255, 0, 0), LARGURATELA * 0.945 , 710, ALLEGRO_ALIGN_CENTRE, "Menu");
		}
		else if(op2 == 2){
			al_draw_bitmap(imagem5[1], 0, 0, 0);
			al_draw_text(fonte2, al_map_rgb(255, 0, 0), LARGURATELA * 0.945 , 710, ALLEGRO_ALIGN_CENTRE, "Menu");
		}
		else if(op2 == 3){
			al_draw_bitmap(imagem5[2], 0, 0, 0);
			al_draw_text(fonte2, al_map_rgb(255, 0, 0), LARGURATELA * 0.945 , 710, ALLEGRO_ALIGN_CENTRE, "Menu");
		}
		else if(op2 == 4){
			al_draw_bitmap(imagem5[3], 0, 0, 0);
			al_draw_text(fonte2, al_map_rgb(255, 0, 0), LARGURATELA * 0.945 , 710, ALLEGRO_ALIGN_CENTRE, "Menu");
		}
		else if(op2 == 5){
			al_draw_bitmap(imagem5[5], 0, 0, 0);
			al_draw_text(fonte2, al_map_rgb(255, 0, 0), LARGURATELA * 0.945 , 710, ALLEGRO_ALIGN_CENTRE, "Menu");
		}
		else if(op2 == 6){
			al_draw_bitmap(imagem5[4], 0, 0, 0);
			al_draw_text(fonte2, al_map_rgb(255, 0, 0), LARGURATELA * 0.945 , 710, ALLEGRO_ALIGN_CENTRE, "Menu");
		}
		else if (op2 == 0){
			al_draw_bitmap(imagem2, 0, 0, 0);
			if(op==0){
				//al_draw_filled_rectangle(458,138,597,342,al_map_rgb(255, 0, 0));
				al_draw_text(fonte2, al_map_rgb(255, 0, 0), LARGURATELA * 0.945 , 710, ALLEGRO_ALIGN_CENTRE, "Menu");
			}
			else{
				al_draw_bitmap(imagem[0], 865, 680, 0);
				al_draw_text(fonte2, al_map_rgb(0, 0, 0), LARGURATELA * 0.945 , 710, ALLEGRO_ALIGN_CENTRE, "Menu");
			}
		}
		if (timer == 14){
			timer = 0;
			c = c+1;
			if(c == 15){
				c = 0;
				l = l + 1;
			}
			j = rand()%5;
		}
		if(j == 0){
			al_draw_bitmap(imagem0[l], a+100, b-110, 0);
			if(resposta == bot1)
				al_draw_bitmap(imagemr[1], a+100, b-110, 0);
			al_draw_filled_triangle(a + 100,b-30,a+130,b-30,a+70,b,al_map_rgb(0, 0, 0));
			if(a + 400 < LARGURATELA){
				if(timer==0 || timer == 3 || timer == 6||timer == 9||timer == 12)
					al_draw_bitmap(imagem[4], a, b, 0);
				else if(timer == 1|| timer == 4|| timer == 7||timer == 10||timer == 13)
					al_draw_bitmap(imagem[3], a, b, 0);
				else
					al_draw_bitmap(imagem[5], a, b, 0);
				a = a+5;
				timer = timer + 1;
			}
			else{
				while(j==0){
					j = rand()%5;
					timer = 0;
				}
			}
		}
		else if(j == 1){
			al_draw_bitmap(imagem0[l], a+100, b-110, 0);
			if(resposta == bot1)
				al_draw_bitmap(imagemr[1], a+100, b-110, 0);
			al_draw_filled_triangle(a + 100,b-30,a+130,b-30,a+70,b,al_map_rgb(0, 0, 0));
			if(a - 85 > 0){
				if(timer==0 || timer == 3 || timer == 6||timer == 9||timer == 12)
					al_draw_bitmap(imagem[10], a, b, 0);
				else if(timer == 1|| timer == 4|| timer == 7||timer == 10||timer == 13)	
					al_draw_bitmap(imagem[9], a, b, 0);
				else
					al_draw_bitmap(imagem[11], a, b, 0);
				a = a-5;
				timer = timer + 1;
			}
			else{
				while(j==1){
					j = rand()%5;
					timer = 0;
				}
			}
		}
		else if(j == 2){
			al_draw_bitmap(imagem0[l], a+100, b-110, 0);
			if(resposta == bot1)
				al_draw_bitmap(imagemr[1], a+100, b-110, 0);
			al_draw_filled_triangle(a + 100,b-30,a+130,b-30,a+70,b,al_map_rgb(0, 0, 0));
			if(b + 85 < ALTURATELA){
				if(timer==0 || timer == 3 || timer == 6||timer == 9||timer == 12)
					al_draw_bitmap(imagem[1], a, b, 0);
				else if(timer == 1|| timer == 4|| timer == 7||timer == 10||timer == 13)
					al_draw_bitmap(imagem[0], a, b, 0);
				else
					al_draw_bitmap(imagem[2], a, b, 0);
				b = b+5;
				timer = timer + 1;
			}
			else{
				while(j==2){
					j = rand()%5;
					timer = 0;
				}
			}
		}
		else if(j == 3){
			al_draw_bitmap(imagem0[l], a+100, b-110, 0);
			if(resposta == bot1)
				al_draw_bitmap(imagemr[1], a+100, b-110, 0);
			al_draw_filled_triangle(a + 100,b-30,a+130,b-30,a+70,b,al_map_rgb(0, 0, 0));
			if(b - 150 > 0){ 
				if(timer==0 || timer == 3 || timer == 6||timer == 9||timer == 12)
					al_draw_bitmap(imagem[7], a, b, 0);
				else if(timer == 1|| timer == 4|| timer == 7||timer == 10||timer == 13)
					al_draw_bitmap(imagem[6], a, b, 0);
				else
					al_draw_bitmap(imagem[8], a, b, 0);
				b = b-5;
				timer = timer + 1;
			}
			else{
				while(j==3){
					j = rand()%5;
					timer = 0;
				}
			}
		}
		else{
			if(n == 0)
				al_draw_bitmap(imagem0[5], a+100, b-110, 0);
			else{
				al_draw_bitmap(imagem0[l], a+100, b-110, 0);
			}
			if(resposta == bot1)
				al_draw_bitmap(imagemr[1], a+100, b-110, 0);
			al_draw_filled_triangle(a + 100,b-30,a+130,b-30,a+70,b,al_map_rgb(0, 0, 0));
			if(timer==0)
				al_draw_bitmap(imagem[12], a, b, 0);
			else if(timer==1)
				al_draw_bitmap(imagem[13], a, b, 0);
			else if(timer==2)
				al_draw_bitmap(imagem[14], a, b, 0);
			else
				al_draw_bitmap(imagem[15], a, b, 0);
			if(timer < 3)
				timer = timer + 1;
			else if(timer == 3)
				m = m + 1;
			if(m == 10){
				m = 1;
				n = n + 1;
				timer = timer + 1;
			}
			if(timer >= 4)
				timer = timer + 1;
		}
		if(n == 1){
			al_draw_bitmap(imagemr[0], a+100, b-110, 0);
		}
		al_rest(0.07);
		al_draw_filled_circle(50, 675, 15,al_map_rgb(0,0,0));
		al_draw_filled_circle(300, 675, 15,al_map_rgb(0,0,0));
		al_draw_filled_circle(50, 720, 15,al_map_rgb(0,0,0));
		al_draw_filled_circle(300, 720, 15,al_map_rgb(0,0,0));
		al_draw_text(fonte2, al_map_rgb(0,100,255),73,653,ALLEGRO_ALIGN_LEFT, paisjogo[0]);
		al_draw_text(fonte2, al_map_rgb(0,100,255),73,698,ALLEGRO_ALIGN_LEFT, paisjogo[1]);
		al_draw_text(fonte2, al_map_rgb(0,100,255),323,653,ALLEGRO_ALIGN_LEFT, paisjogo[2]);
		al_draw_text(fonte2, al_map_rgb(0,100,255),323,698,ALLEGRO_ALIGN_LEFT, paisjogo[3]);
		if(resposta == bot1){
			al_draw_text(fonte, al_map_rgb(0,0,130),LARGURATELA/2,500,ALLEGRO_ALIGN_CENTER,"VOCE ACERTOU O PAIS!");
			if ((resp1 == 0 || resp1 == 4) && bot2 == 3){
				al_draw_bitmap(imagem2,0,0,0);
				al_draw_text(fonte, al_map_rgb(0,0,130),LARGURATELA/2,300,ALLEGRO_ALIGN_CENTER,"VOCE ACERTOU O");
				al_draw_text(fonte, al_map_rgb(0,0,130),LARGURATELA/2 ,400,ALLEGRO_ALIGN_CENTER,"CONTINENTE!");
				al_flip_display();
				al_rest(5.0);
				for(j=0;j<2;j = j+1){
					al_destroy_bitmap(imagemr[j]);
				}
				return;
			}
			else if ((resp1 == 5 || resp1 == 2) && bot2 == 1){
				al_draw_bitmap(imagem2,0,0,0);
				al_draw_text(fonte, al_map_rgb(0,0,130),LARGURATELA/2,300,ALLEGRO_ALIGN_CENTER,"VOCE ACERTOU O");
				al_draw_text(fonte, al_map_rgb(0,0,130),LARGURATELA/2 ,400,ALLEGRO_ALIGN_CENTER,"CONTINENTE!");
				al_flip_display();
				al_rest(5.0);
				for(j=0;j<2;j = j+1){
					al_destroy_bitmap(imagemr[j]);
				}
				return;
			}
			else if ((resp1 == 1) && bot2 == 2){
				al_draw_bitmap(imagem2,0,0,0);
				al_draw_text(fonte, al_map_rgb(0,0,130),LARGURATELA/2,300,ALLEGRO_ALIGN_CENTER,"VOCE ACERTOU O");
				al_draw_text(fonte, al_map_rgb(0,0,130),LARGURATELA/2 ,400,ALLEGRO_ALIGN_CENTER,"CONTINENTE!");
				al_flip_display();
				al_rest(5.0);
				for(j=0;j<2;j = j+1){
					al_destroy_bitmap(imagemr[j]);
				}
				return;
			}
			else if ((resp1 == 3) && bot2 == 4){
				al_draw_bitmap(imagem2,0,0,0);
				al_draw_text(fonte, al_map_rgb(0,0,130),LARGURATELA/2,300,ALLEGRO_ALIGN_CENTER,"VOCE ACERTOU O");
				al_draw_text(fonte, al_map_rgb(0,0,130),LARGURATELA/2 ,400,ALLEGRO_ALIGN_CENTER,"CONTINENTE!");
				al_flip_display();
				al_rest(5.0);
				for(j=0;j<2;j = j+1){
					al_destroy_bitmap(imagemr[j]);
				}
				return;
			}
			else if(bot2 != 0){
				al_draw_text(fonte, al_map_rgb(255,0,0),LARGURATELA/2 ,400,ALLEGRO_ALIGN_CENTER,"ERROU O CONTINENTE!");
				bot2 = 0;
			}
		}
		else{
			if(tela == 1){
				al_draw_filled_circle(50, 675, 15,al_map_rgb(255,0,0));
				al_draw_text(fonte2, al_map_rgb(255,0,0),73,653,ALLEGRO_ALIGN_LEFT, paisjogo[0]);
			}
			else if(tela == 3){
				al_draw_filled_circle(300, 675, 15,al_map_rgb(255,0,0));
				al_draw_text(fonte2, al_map_rgb(255,0,0),323,653,ALLEGRO_ALIGN_LEFT, paisjogo[2]);
			}
			else if(tela == 2){
				al_draw_filled_circle(50, 720, 15,al_map_rgb(255,0,0));
				al_draw_text(fonte2, al_map_rgb(255,0,0),73,698,ALLEGRO_ALIGN_LEFT, paisjogo[1]);
			}
			else if(tela == 4){
				al_draw_filled_circle(300, 720, 15,al_map_rgb(255,0,0));
				al_draw_text(fonte2, al_map_rgb(255,0,0),323,698,ALLEGRO_ALIGN_LEFT, paisjogo[3]);
			}
			if(bot1 != 0){
				al_draw_text(fonte, al_map_rgb(255,0,0),LARGURATELA/2 ,400,ALLEGRO_ALIGN_CENTER,"ERROU!");
				bot1 = 0;
			}
		}
		al_draw_text(fonte2, al_map_rgb(255,255,255),43,653,ALLEGRO_ALIGN_LEFT,"A");
		al_draw_text(fonte2, al_map_rgb(255,255,255),43,698,ALLEGRO_ALIGN_LEFT,"B");
		al_draw_text(fonte2, al_map_rgb(255,255,255),293,653,ALLEGRO_ALIGN_LEFT,"C");
		al_draw_text(fonte2, al_map_rgb(255,255,255),293,698,ALLEGRO_ALIGN_LEFT,"D");
		al_flip_display();
		if(l >= 4)
			l = 0;
	}
	for(j=0;j<2;j = j+1){
		al_destroy_bitmap(imagemr[j]);
	}
}

int carregar(ALLEGRO_BITMAP *imagem[],ALLEGRO_BITMAP *imagem0[]){
	int i, j;
	srand (time(NULL));
	i = rand() % 6;
	if(i==0){
		imagem[0] = al_load_bitmap("ale1.a.bmp");
		imagem[1] = al_load_bitmap("ale1.b.bmp");
		imagem[2] = al_load_bitmap("ale1.c.bmp");
		imagem[3] = al_load_bitmap("ale2.a.bmp");
		imagem[4] = al_load_bitmap("ale2.b.bmp");
		imagem[5] = al_load_bitmap("ale2.c.bmp");
		imagem[6] = al_load_bitmap("ale3.a.bmp");
		imagem[7] = al_load_bitmap("ale3.b.bmp");
		imagem[8] = al_load_bitmap("ale3.c.bmp");
		imagem[9] = al_load_bitmap("ale4.a.bmp");
		imagem[10] = al_load_bitmap("ale4.b.bmp");
		imagem[11] = al_load_bitmap("ale4.c.bmp");
		imagem[12] = al_load_bitmap("ale5.a.bmp");
		imagem[13] = al_load_bitmap("ale5.b.bmp");
		imagem[14] = al_load_bitmap("ale5.c.bmp");
		imagem[15] = al_load_bitmap("ale5.d.bmp");
		imagem[16] = al_load_bitmap("ale6.bmp");
		imagem0[0] = al_load_bitmap("alem1.bmp");
		imagem0[1] = al_load_bitmap("aelm2.bmp");
		imagem0[2] = al_load_bitmap("aelm3.bmp");
		imagem0[3] = al_load_bitmap("aelm4.bmp");
		imagem0[4] = al_load_bitmap("aelm5.bmp");
		imagem0[5] = al_load_bitmap("aelm.bmp");
	}
	else if(i==1){
		imagem[0] = al_load_bitmap("braa.1.bmp");
		imagem[1] = al_load_bitmap("braa.2.bmp");
		imagem[2] = al_load_bitmap("braa.3.bmp");
		imagem[3] = al_load_bitmap("brab.1.bmp");
		imagem[4] = al_load_bitmap("brab.2.bmp");
		imagem[5] = al_load_bitmap("brab.3.bmp");
		imagem[6] = al_load_bitmap("brac.1.bmp");
		imagem[7] = al_load_bitmap("brac.2.bmp");
		imagem[8] = al_load_bitmap("brac.3.bmp");
		imagem[9] = al_load_bitmap("brad.1.bmp");
		imagem[10] = al_load_bitmap("brad.2.bmp");
		imagem[11] = al_load_bitmap("brad.3.bmp");
		imagem[12] = al_load_bitmap("brae.1.bmp");
		imagem[13] = al_load_bitmap("brae.2.bmp");
		imagem[14] = al_load_bitmap("brae.3.bmp");
		imagem[15] = al_load_bitmap("brae.4.bmp");
		imagem[16] = al_load_bitmap("bra.bmp");
		imagem0[0] = al_load_bitmap("bram1.bmp");
		imagem0[1] = al_load_bitmap("bram2.bmp");
		imagem0[2] = al_load_bitmap("bram3.bmp");
		imagem0[3] = al_load_bitmap("bram4.bmp");
		imagem0[4] = al_load_bitmap("bram5.bmp");
		imagem0[5] = al_load_bitmap("bram.bmp");
	}
	else if(i==2){
		imagem[0] = al_load_bitmap("cana.1.bmp");
		imagem[1] = al_load_bitmap("cana.2.bmp");
		imagem[2] = al_load_bitmap("cana.3.bmp");
		imagem[3] = al_load_bitmap("canb.1.bmp");
		imagem[4] = al_load_bitmap("canb.2.bmp");
		imagem[5] = al_load_bitmap("canb.3.bmp");
		imagem[6] = al_load_bitmap("canc.1.bmp");
		imagem[7] = al_load_bitmap("canc.2.bmp");
		imagem[8] = al_load_bitmap("canc.3.bmp");
		imagem[9] = al_load_bitmap("cand.1.bmp");
		imagem[10] = al_load_bitmap("cand.2.bmp");
		imagem[11] = al_load_bitmap("cand.3.bmp");
		imagem[12] = al_load_bitmap("cane.1.bmp");
		imagem[13] = al_load_bitmap("cane.2.bmp");
		imagem[14] = al_load_bitmap("cane.3.bmp");
		imagem[15] = al_load_bitmap("cane.4.bmp");
		imagem[16] = al_load_bitmap("can.bmp");
		imagem0[0] = al_load_bitmap("canm1.bmp");
		imagem0[1] = al_load_bitmap("canm2.bmp");
		imagem0[2] = al_load_bitmap("canm3.bmp");
		imagem0[3] = al_load_bitmap("canm4.bmp");
		imagem0[4] = al_load_bitmap("usam5.bmp");
		imagem0[5] = al_load_bitmap("usam.bmp");
	}
	else if(i==3){
		imagem[0] = al_load_bitmap("chia.1.bmp");
		imagem[1] = al_load_bitmap("chia.2.bmp");
		imagem[2] = al_load_bitmap("chia.3.bmp");
		imagem[3] = al_load_bitmap("chib.1.bmp");
		imagem[4] = al_load_bitmap("chib.2.bmp");
		imagem[5] = al_load_bitmap("chib.3.bmp");
		imagem[6] = al_load_bitmap("chic.1.bmp");
		imagem[7] = al_load_bitmap("chic.2.bmp");
		imagem[8] = al_load_bitmap("chic.3.bmp");
		imagem[9] = al_load_bitmap("chid.1.bmp");
		imagem[10] = al_load_bitmap("chid.2.bmp");
		imagem[11] = al_load_bitmap("chid.3.bmp");
		imagem[12] = al_load_bitmap("chie.1.bmp");
		imagem[13] = al_load_bitmap("chie.2.bmp");
		imagem[14] = al_load_bitmap("chie.3.bmp");
		imagem[15] = al_load_bitmap("chie.4.bmp");
		imagem[16] = al_load_bitmap("chi.bmp");
		imagem0[0] = al_load_bitmap("chim1.bmp");
		imagem0[1] = al_load_bitmap("chim2.bmp");
		imagem0[2] = al_load_bitmap("chim3.bmp");
		imagem0[3] = al_load_bitmap("chim4.bmp");
		imagem0[4] = al_load_bitmap("chim5.bmp");
		imagem0[5] = al_load_bitmap("chim.bmp");
	}
	else if(i==4){
		imagem[0] = al_load_bitmap("espa.1.bmp");
		imagem[1] = al_load_bitmap("espa.2.bmp");
		imagem[2] = al_load_bitmap("espa.3.bmp");
		imagem[3] = al_load_bitmap("espb.1.bmp");
		imagem[4] = al_load_bitmap("espb.2.bmp");
		imagem[5] = al_load_bitmap("espb.3.bmp");
		imagem[6] = al_load_bitmap("espc.1.bmp");
		imagem[7] = al_load_bitmap("espc.2.bmp");
		imagem[8] = al_load_bitmap("espc.3.bmp");
		imagem[9] = al_load_bitmap("espd.1.bmp");
		imagem[10] = al_load_bitmap("espd.2.bmp");
		imagem[11] = al_load_bitmap("espd.3.bmp");
		imagem[12] = al_load_bitmap("espe.1.bmp");
		imagem[13] = al_load_bitmap("espe.2.bmp");
		imagem[14] = al_load_bitmap("espe.3.bmp");
		imagem[15] = al_load_bitmap("espe.4.bmp");
		imagem[16] = al_load_bitmap("esp.bmp");
		imagem0[0] = al_load_bitmap("espm1.bmp");
		imagem0[1] = al_load_bitmap("espm2.bmp");
		imagem0[2] = al_load_bitmap("espm3.bmp");
		imagem0[3] = al_load_bitmap("espm4.bmp");
		imagem0[4] = al_load_bitmap("espm5.bmp");
		imagem0[5] = al_load_bitmap("espm.bmp");
	}
	else if(i==5){
		imagem[0] = al_load_bitmap("usaa.1.bmp");
		imagem[1] = al_load_bitmap("usaa.2.bmp");
		imagem[2] = al_load_bitmap("usaa.3.bmp");
		imagem[3] = al_load_bitmap("usab.1.bmp");
		imagem[4] = al_load_bitmap("usab.2.bmp");
		imagem[5] = al_load_bitmap("usab.3.bmp");
		imagem[6] = al_load_bitmap("usac.1.bmp");
		imagem[7] = al_load_bitmap("usac.2.bmp");
		imagem[8] = al_load_bitmap("usac.3.bmp");
		imagem[9] = al_load_bitmap("usad.1.bmp");
		imagem[10] = al_load_bitmap("usad.2.bmp");
		imagem[11] = al_load_bitmap("usad.3.bmp");
		imagem[12] = al_load_bitmap("usae.1.bmp");
		imagem[13] = al_load_bitmap("usae.2.bmp");
		imagem[14] = al_load_bitmap("usae.3.bmp");
		imagem[15] = al_load_bitmap("usae.4.bmp");
		imagem[16] = al_load_bitmap("usa.bmp");
		imagem0[0] = al_load_bitmap("usam1.bmp");
		imagem0[1] = al_load_bitmap("usam2.bmp");
		imagem0[2] = al_load_bitmap("usam3.bmp");
		imagem0[3] = al_load_bitmap("usam4.bmp");
		imagem0[4] = al_load_bitmap("usam5.bmp");
		imagem0[5] = al_load_bitmap("usam.bmp");
	}
	for(j = 0; j<17; j = j+1){
		al_convert_mask_to_alpha(imagem[j],al_map_rgb(255,0,255));
	}
	return i;
}

void carregarm(ALLEGRO_BITMAP *imagem3[]){
	int j;
	imagem3[0] = al_load_bitmap("mundo14.bmp");
	imagem3[1] = al_load_bitmap("mundo13.bmp");	
	imagem3[2] = al_load_bitmap("mundo12.bmp");
	imagem3[3] = al_load_bitmap("mundo11.bmp");
	imagem3[4] = al_load_bitmap("mundo10.bmp");
	imagem3[5] = al_load_bitmap("mundo9.bmp");
	imagem3[6] = al_load_bitmap("mundo8.bmp");
	imagem3[7] = al_load_bitmap("mundo7.bmp");
	imagem3[8] = al_load_bitmap("mundo6.bmp");
	imagem3[9] = al_load_bitmap("mundo5.bmp");
	imagem3[10] = al_load_bitmap("mundo4.bmp");
	imagem3[11] = al_load_bitmap("mundo3.bmp");
	imagem3[12] = al_load_bitmap("mundo2.bmp");
	imagem3[13] = al_load_bitmap("mundo1.bmp");
	for(j = 0; j<14; j = j+1){
		al_convert_mask_to_alpha(imagem3[j],al_map_rgb(255,0,255));
	}
}

void carregarf(ALLEGRO_BITMAP *imagem5[]){
	imagem5[0] = al_load_bitmap("americaN.bmp");
	imagem5[1] = al_load_bitmap("americaS.bmp");
	imagem5[2] = al_load_bitmap("europa.bmp");
	imagem5[3] = al_load_bitmap("asia.bmp");
	imagem5[4] = al_load_bitmap("oceania.bmp");
	imagem5[5] = al_load_bitmap("africa.bmp");
}

