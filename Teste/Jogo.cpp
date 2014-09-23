#include <iostream>
#include <ctime>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Textura.h"
#include "Bola_Verde.h"
#include "Bola_Vermelha.h"
#include "Bola_Jogador.h"
#include "Bola_Roxa.h"
#include "Circulo.h"
#include "Jogo.h"


Texture Plano_Fundo;
int  Conta_Tempo ;
int x_mouse , y_mouse;

int Numeros_Bolas_Verdes = 0;
int Numeros_Bolas_Vermelhas = 0;
int Numeros_Bolas_Roxas = 0;
int Numeros_Bolas_Verdes_Grudadas = 0;
int Pontos_Total = 0;

std::vector< Bola_Verde > Lista_Bola_Verde;          // Cria um vetor vazio
std::vector< Bola_Verde >::iterator Bolaverde_it;  // Cria um iterador para

std::vector< Bola_Verde > Lista_Bola_Verde_Grudadas;          // Cria um vetor vazio
std::vector< Bola_Verde >::iterator Bolagrudada_it;  // Cria um iterador para

std::vector< Bola_Vermelha > Lista_Bola_Vermelha;          // Cria um vetor vazio
std::vector< Bola_Vermelha >::iterator Bolavermelha_it;  // Cria um iterador para

std::vector< Bola_Roxa > Lista_Bola_Roxa;          // Cria um vetor vazio
std::vector< Bola_Roxa >::iterator Bolaroxa_it;  // Cria um iterador para



Mix_Music *Musica = NULL;

enum POSSIVEL_BOLA
{
    BOLA_VERDE,
    BOLA_ROXA,
    BOLA_VERMELHA

};

void Escolher_Bola(SDL_Renderer *Janelarenderizada);
void Criar_Bola_Verde(SDL_Renderer *Janelarenderizada);
void Criar_Bola_Vermelha(SDL_Renderer *Janelarenderizada);
void Criar_Bola_Roxa(SDL_Renderer *Janelarenderizada);
void Atualizar_Objetos_Tela(SDL_Renderer *Janelarenderizada,Bola_Jogador *Play_Copia);
void Remove_Bolas_Fora();
void Checar_Colisao(Bola_Jogador *Play_Copia,SDL_Renderer *Janelarenderizada);
void Calcular_Pontos();
void Libera_lista_Grudada();
void Play_Music();

void Jogo::Iniciar_Jogo(SDL_Window *Janela , SDL_Renderer *Janelarenderizada )
{
            Conta_Tempo = 0;
            srand (time (NULL));
            Play_Music();
            Bola_Jogador Play(Janelarenderizada);

            bool exit_jogo = false;
            Plano_Fundo.loadFromFile("imagens/imagem de fundo sem logo.jpg",Janelarenderizada);

            //Event handler
			SDL_Event e;
			//While application is running
			while( !exit_jogo)
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						exit_jogo= true;
					}
				}

				//Clear screen

            Conta_Tempo ++ ;
            SDL_SetRenderDrawColor( Janelarenderizada, 0xFF, 0xFF, 0, 0xFF );
            SDL_RenderClear( Janelarenderizada );
            Plano_Fundo.render(0,0,Janelarenderizada);
            Atualizar_Objetos_Tela(Janelarenderizada, &Play);
            SDL_RenderPresent( Janelarenderizada );

			}






}



void Escolher_Bola(SDL_Renderer *Janelarenderizada)
{


    POSSIVEL_BOLA ESCOLHIDA;
    int Numero = rand() % 3 ;
switch(Numero)
{
case 0:
    ESCOLHIDA = BOLA_VERDE;
    break;
case 1:
    ESCOLHIDA = BOLA_VERMELHA;
    break;
case 2:
    ESCOLHIDA = BOLA_ROXA;
    break;
}

switch(ESCOLHIDA)
                {

                    case BOLA_VERDE:
                    //if(Numeros_Bolas_Verdes<1){
                        Criar_Bola_Verde(Janelarenderizada);
                      // }
                        break;

                    case BOLA_VERMELHA:

                        Criar_Bola_Vermelha(Janelarenderizada);

                        break;

                    case BOLA_ROXA:
                        Criar_Bola_Roxa(Janelarenderizada);
                        break;

                    default:
                        break;

                }


}

void Criar_Bola_Verde(SDL_Renderer *Janelarenderizada)
{

Bola_Verde *Nova_Bola = new Bola_Verde(Janelarenderizada);
Lista_Bola_Verde.push_back(*Nova_Bola);
Numeros_Bolas_Verdes++;

}

void Criar_Bola_Vermelha(SDL_Renderer *Janelarenderizada)
{

Bola_Vermelha *Nova_Bola = new Bola_Vermelha(Janelarenderizada);
Lista_Bola_Vermelha.push_back(*Nova_Bola);
Numeros_Bolas_Vermelhas++;

}

void Criar_Bola_Roxa(SDL_Renderer *Janelarenderizada)
{

Bola_Roxa *Nova_Bola = new Bola_Roxa(Janelarenderizada);
Lista_Bola_Roxa.push_back(*Nova_Bola);
Numeros_Bolas_Roxas++;

}

void Atualizar_Objetos_Tela(SDL_Renderer *Janelarenderizada,Bola_Jogador *Play_Copia)
{


    Play_Copia->Render_Imagem(Janelarenderizada);
    Play_Copia->Get_Position(&x_mouse,&y_mouse);
    if (Conta_Tempo % 200 == 0)
    {
      Escolher_Bola(Janelarenderizada);
      Conta_Tempo = 0;
    std::cout<<Pontos_Total<<"   "<<Numeros_Bolas_Verdes_Grudadas<<std::endl;
    }


Bolaverde_it = Lista_Bola_Verde.begin();
for(int Contador = 0 ; Contador < Numeros_Bolas_Verdes ; Contador++,Bolaverde_it++)
{

   Bolaverde_it->Set_Caminho();
   Bolaverde_it->Render_Imagem(Janelarenderizada);


}


Bolavermelha_it = Lista_Bola_Vermelha.begin();
for(int Contador = 0 ; Contador < Numeros_Bolas_Vermelhas ; Contador++,Bolavermelha_it++)
{

   Bolavermelha_it->Set_Caminho();
   Bolavermelha_it->Render_Imagem(Janelarenderizada);

}

Bolaroxa_it = Lista_Bola_Roxa.begin();
for(int Contador = 0 ; Contador < Numeros_Bolas_Roxas ; Contador++,Bolaroxa_it++)
{

   Bolaroxa_it->Set_Caminho();
   Bolaroxa_it->Render_Imagem(Janelarenderizada);


}

Bolagrudada_it = Lista_Bola_Verde_Grudadas.begin();
for(int Contador = 0 ; Contador < Numeros_Bolas_Verdes_Grudadas ; Contador++,Bolagrudada_it++)
{
    int x_atual,y_atual;
    int x_ ,y_;
    int x_0 , y_0;
    Bolagrudada_it->Get_Position(&x_atual,&y_atual);
    x_ = x_atual;
    y_ = y_atual;
    Bolagrudada_it->Get_Colisao(&x_0,&y_0);
    x_ -= x_0 - x_mouse ;
    y_ -= y_0 - y_mouse ;


    Bolagrudada_it->Set_Position(x_,y_);
    Bolagrudada_it->Set_Colisao(x_mouse,y_mouse);
    Bolagrudada_it->Render_Imagem_Manual(Janelarenderizada,x_ ,y_);





}

Checar_Colisao(Play_Copia,Janelarenderizada);
Remove_Bolas_Fora();

SDL_RenderPresent( Janelarenderizada );


}





void Play_Music()
{
    if( !Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    std::cout<< "Failed to load beat music! SDL_mixer Error: %s\n"<< Mix_GetError();

                }
            Musica = Mix_LoadMUS( "musica/The Exorcist Theme.mp3" );
            if( Musica == NULL )
            {
            std::cout<< "Failed to load beat music! SDL_mixer Error: %s\n"<< Mix_GetError();

            }
            Mix_PlayMusic( Musica, -1 );
}

void Checar_Colisao(Bola_Jogador *Play_Copia,SDL_Renderer *Janelarenderizada)
{
    Bolaverde_it = Lista_Bola_Verde.begin();
    Bolavermelha_it = Lista_Bola_Vermelha.begin();
    Bolaroxa_it = Lista_Bola_Roxa.begin();


    int x ,y ;

    Circulo *Jogador = new Circulo;
    Play_Copia->Get_Position(&x,&y);
    Jogador->Set_Raio(19);
    Jogador->Set_X_Y(x,y);

    for(int Contador = 0 , Contador2 = Numeros_Bolas_Vermelhas ; Contador < Contador2 ; Contador++,Bolavermelha_it++)
    {
        int x_objeto,y_objeto;
        Bolavermelha_it->Get_Position(&x_objeto,&y_objeto);
        Circulo *Objeto = new Circulo;
        Objeto->Set_Raio(19);
        Objeto->Set_X_Y(x_objeto,y_objeto);

        if ( Jogador->Checar_Colisao(*Jogador,*Objeto) )
        {
            Bolavermelha_it->Set_Flag('F');
            Libera_lista_Grudada();
        }

    delete Objeto;
    Objeto=NULL;

    }

    for(int Contador = 0 , Contador2 = Numeros_Bolas_Verdes ; Contador < Contador2 ; Contador++,Bolaverde_it++)
    {
        int x_objeto,y_objeto;
        Bolaverde_it->Get_Position(&x_objeto,&y_objeto);
        Circulo *Objeto = new Circulo;
        Objeto->Set_Raio(19);
        Objeto->Set_X_Y(x_objeto,y_objeto);

        if ( Jogador->Checar_Colisao(*Jogador,*Objeto) )
        {
            int x , y ;
            Bolaverde_it->Get_Position(&x,&y);

            Bola_Verde *Nova_Bola = new Bola_Verde(Janelarenderizada);
            Nova_Bola->Set_Position(x,y);
            Nova_Bola->Set_Colisao(x_mouse,y_mouse);

            Lista_Bola_Verde_Grudadas.push_back(*Nova_Bola);
            Numeros_Bolas_Verdes_Grudadas++;
            Bolaverde_it->Set_Flag('F');



        }

    delete Objeto;
    Objeto=NULL;
    }


    for(int Contador = 0 , Contador2 = Numeros_Bolas_Roxas ; Contador < Contador2 ; Contador++,Bolaroxa_it++)
    {
        int x_objeto,y_objeto;
        Bolaroxa_it->Get_Position(&x_objeto,&y_objeto);
        Circulo *Objeto = new Circulo;
        Objeto->Set_Raio(19);
        Objeto->Set_X_Y(x_objeto,y_objeto);

        if ( Jogador->Checar_Colisao(*Jogador,*Objeto) )
        {
            Bolaroxa_it->Set_Flag('F');
            Calcular_Pontos();
        }

    delete Objeto;
    Objeto=NULL;
    }

    Remove_Bolas_Fora();

        Bolagrudada_it =Lista_Bola_Verde_Grudadas.begin();
        for    (int Contador =0 , Contador2 = Numeros_Bolas_Verdes_Grudadas ; Contador < Contador2 ; Contador++,Bolagrudada_it++)
        {
            int x , y;

            Circulo *Objeto_Grudado = new Circulo;
            Bolagrudada_it->Get_Position(&x,&y);
            Objeto_Grudado->Set_Raio(19);
            Objeto_Grudado->Set_X_Y(x,y);

            Bolavermelha_it = Lista_Bola_Vermelha.begin();
            for(int Contador = 0 , Contador2 = Numeros_Bolas_Vermelhas ; Contador < Contador2 ; Contador++,Bolavermelha_it++)
            {

            int x_objeto,y_objeto;
            Bolavermelha_it->Get_Position(&x_objeto,&y_objeto);
            Circulo *Objeto = new Circulo;
            Objeto->Set_Raio(19);
            Objeto->Set_X_Y(x_objeto,y_objeto);

                if ( Objeto_Grudado->Checar_Colisao(*Objeto_Grudado,*Objeto) )
                {
                Bolavermelha_it->Set_Flag('F');
                Libera_lista_Grudada();
                }

            delete Objeto;
            Objeto=NULL;

            }

            Bolaroxa_it = Lista_Bola_Roxa.begin();
            for(int Contador = 0 , Contador2 = Numeros_Bolas_Roxas ; Contador < Contador2 ; Contador++,Bolaroxa_it++)
            {
            int x_objeto,y_objeto;
            Bolaroxa_it->Get_Position(&x_objeto,&y_objeto);
            Circulo *Objeto = new Circulo;
            Objeto->Set_Raio(19);
            Objeto->Set_X_Y(x_objeto,y_objeto);

            if ( Objeto_Grudado->Checar_Colisao(*Objeto_Grudado,*Objeto) )
            {
            Bolaroxa_it->Set_Flag('F');
            Calcular_Pontos();
            }

            delete Objeto;
            Objeto=NULL;
            }

            Bolaverde_it = Lista_Bola_Verde.begin();
            for(int Contador = 0 , Contador2 = Numeros_Bolas_Verdes ; Contador < Contador2 ; Contador++,Bolaverde_it++)
            {
            int x_objeto,y_objeto;
            Bolaverde_it->Get_Position(&x_objeto,&y_objeto);
            Circulo *Objeto = new Circulo;
            Objeto->Set_Raio(19);
            Objeto->Set_X_Y(x_objeto,y_objeto);

            if ( Objeto_Grudado->Checar_Colisao(*Objeto_Grudado,*Objeto) )
            {
            int x , y ;
            Bolaverde_it->Get_Position(&x,&y);

            Bola_Verde *Nova_Bola = new Bola_Verde(Janelarenderizada);
            Nova_Bola->Set_Position(x,y);
            Nova_Bola->Set_Colisao(x_mouse,y_mouse);
            Lista_Bola_Verde_Grudadas.push_back(*Nova_Bola);
            Numeros_Bolas_Verdes_Grudadas++;
            Bolaverde_it->Set_Flag('F');



            }

            delete Objeto;
            Objeto=NULL;
            }


        }





}


void Remove_Bolas_Fora()
{
    Bolaverde_it = Lista_Bola_Verde.begin();
    Bolavermelha_it = Lista_Bola_Vermelha.begin();
    Bolaroxa_it = Lista_Bola_Roxa.begin();
    for(int Contador = 0 , Contador2 = Numeros_Bolas_Verdes ; Contador < Contador2 ; Contador++,Bolaverde_it++)
    {
        if (   Bolaverde_it->Get_Flag()=='F' )
        {

            Bolaverde_it->Free();
            Lista_Bola_Verde.erase(Lista_Bola_Verde.begin() + Contador);
            --Numeros_Bolas_Verdes;
        }

    }


    for(int Contador = 0 , Contador2 = Numeros_Bolas_Vermelhas ; Contador < Contador2 ; Contador++,Bolavermelha_it++)
    {
        if (   Bolavermelha_it->Get_Flag()=='F')
        {
            Bolavermelha_it->Free();
            Lista_Bola_Vermelha.erase(Lista_Bola_Vermelha.begin() + Contador);
            --Numeros_Bolas_Vermelhas;
        }

    }

    for(int Contador = 0 , Contador2 = Numeros_Bolas_Roxas ; Contador < Contador2 ; Contador++,Bolaroxa_it++)
    {
        if (   Bolaroxa_it->Get_Flag()=='F' )
        {
            Bolaroxa_it->Free();
            Lista_Bola_Roxa.erase(Lista_Bola_Roxa.begin() + Contador);
            --Numeros_Bolas_Roxas;
        }

    }



}

void Calcular_Pontos()
{   if(Numeros_Bolas_Verdes_Grudadas >= 3)
  {

    switch (Numeros_Bolas_Verdes_Grudadas)
    {
        case 3 :
         Pontos_Total = Pontos_Total + 1;
         Libera_lista_Grudada();
         break;

        case 4 :
         Pontos_Total = Pontos_Total + (4 * 5);
         Libera_lista_Grudada();
         break;

        case 5 :
         Pontos_Total = Pontos_Total + (5 * 11);
         Libera_lista_Grudada();
         break;

        case 6 :
         Pontos_Total = Pontos_Total + (6 * 17);
         Libera_lista_Grudada();
         break;

        case 7 :
         Pontos_Total = Pontos_Total + (7 * 25);
         Libera_lista_Grudada();
         break;

        case 8 :
         Pontos_Total = Pontos_Total + (8 * 33);
         Libera_lista_Grudada();
         break;

        case 9 :
         Pontos_Total = Pontos_Total + (9 * 41);
         Libera_lista_Grudada();
         break;

        case 10 :
         Pontos_Total = Pontos_Total + (10 * 51);
         Libera_lista_Grudada();
         break;

        default:
            Pontos_Total = Pontos_Total + (Numeros_Bolas_Verdes_Grudadas * 100);
            Libera_lista_Grudada();
            break;
    }
  }
  else
  {
      Libera_lista_Grudada();
  }

}


void Libera_lista_Grudada()
{
     while( !Lista_Bola_Verde_Grudadas.empty())
    {

           Lista_Bola_Verde_Grudadas.erase(Lista_Bola_Verde_Grudadas.begin());
           Numeros_Bolas_Verdes_Grudadas --;

    }
}
