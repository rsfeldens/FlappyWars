/*========================================== FLAPPY WARS - main =================================================*/
//bibliotecas
#include "raylib.h"
#include <stdio.h>
#include <string.h>


//definição das funções max e min, que dados valores a e b, devolvem o maior e o menor valor.
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))

/*================================================================ DEFINIÇÃO DE ENUMERAÇÃO E ESTRUTURAS GLOBAIS ===================================================================*/

//enumeração das telas de jogo a serem utilizadas no switch case
typedef enum GameScreen { MENU, PLAY, GAMEPLAY, GAMEOVER, LEVELS, RANKING} GameScreen;


//estrutura do jogador da gameplay, com sua posição(x,y), largura, altura e velocidade
typedef struct{
        Vector2 position;
        int width;
        int height;
        float velocidade;
        
}PLAYER;

//estrutura dos tubos, com sua posição(x,y), largura e altura e booleana indicando se o tubo está ativo
typedef struct{
     Vector2 position;
     int width;
     int height;
     bool active;
        
}TUBE;

//estrutura da dificuldade, contendo as variáveis fornecidas no arquivo texto
typedef struct{
      int score_threshold;
      int gap;
      int inc_gap;
      int dif_max_altura;
      int inc_dif_max_altura;
      int vel_obstaculos;
      int inc_vel_obstaculos;
}DIFFICULTY;

//estrutura do jogador a ser alocado no ranking
typedef struct{
    char nome[16];
    int score;
}PLAYER_RANKING;  

/*================================================================== FUNÇÕES PARA DESENHO NA TELA ============================================================================*/

//função que desenha a introdução e menu principal do jogo
void draw_menu(Texture2D fundo_menu, Texture2D logo_menu, int y_abertura, int levelselectedheight, Texture2D menulevelselected, Texture2D volume){
    
    //desenha fundo do menu
    DrawTexture(fundo_menu,0,0,RAYWHITE);
    
    //desenha abertura do jogo
    DrawTexture(logo_menu, 600 - 228, 800 - y_abertura, RAYWHITE);
    DrawText("Há muito tempo, em uma galáxia muito, muito distante... Os\n\n\n\nalunos do INF-UFRGS, Gabriel e Rodrigo, receberam a missão \n\n\n\nde criar uma versão do jogo Flappy Bird em C. Sendo assim,\n\n\n\ndecidiram implementar a temática do universo de Star Wars.\n\n\n\nAo pressionar a tecla espaço, você será enviado ao menu\n\n\n\nprincipal do jogo. Que a força esteja com você, sempre.",160, 1000 - y_abertura, 30, YELLOW);

    //desenha menu principal e suas opções
    if(y_abertura >= 1400)
    {       
        
        DrawTexture(logo_menu, 600 - 228, 20, RAYWHITE);
        
        DrawRectangle(450, 215, 300, 100, YELLOW);
        DrawText("PLAY", 470, 235, 40, BLACK);

        DrawRectangle(450, 365, 300, 100, YELLOW);
        DrawText("LEVELS", 470, 385, 40, BLACK);

        DrawRectangle(450, 515, 300, 100, YELLOW);
        DrawText("RANKING", 470, 535, 40, BLACK);

        DrawRectangle(450, 665, 300, 100, YELLOW);
        DrawText("EXIT", 470, 685, 40, BLACK);
        DrawTexture(menulevelselected, 1000, levelselectedheight,RAYWHITE);

        DrawTexture(volume,50,50,RAYWHITE);
        
            
    }
}

//função que desenha as opções de levels para o jogador
void draw_levels(Texture2D fundo_menu, Texture2D smalltatooine, Texture2D smallendor, Texture2D smalldeathstar){
  
        DrawTexture(fundo_menu,0,0,RAYWHITE);
        DrawTexture(smalltatooine,50,200,RAYWHITE);
        DrawTexture(smallendor,450,200,RAYWHITE);
        DrawTexture(smalldeathstar, 850,150,RAYWHITE);
        DrawText("TATOOINE", 100, 600, 30, GRAY);
        DrawText("EASY", 100, 650, 20, YELLOW);
        DrawText("ENDOR", 500, 600, 30, GRAY);
        DrawText("NORMAL", 500, 650, 20, YELLOW);
        DrawText("DEATH STAR", 900, 600, 30, GRAY);
        DrawText("HARD", 900, 650, 20, YELLOW);
}

//função para desenhar a tela de play(pre-gameplay)
void draw_play(Texture2D levelbackground, Texture2D grogu){
    
    DrawTexture(levelbackground,0,0,RAYWHITE);
    DrawRectangle(115,215, MeasureText("PRESS SPACE AND MAY THE FORCE BE WITH YOU", 30) + 10,35, BLACK);
    DrawText("PRESS SPACE AND MAY THE FORCE BE WITH YOU", 120, 220, 30, YELLOW);
    DrawTexture(grogu, 155, 250, RAYWHITE);
}

//função para desenhar a tela de gampeplay
void draw_gameplay(Texture2D levelbackground, Texture2D tube_tatooine, Texture2D tube_endor, Texture2D tube_deathstar, char textoscore[], TUBE *tubes, DIFFICULTY difficulty, int select_level){
    
            //desenha o fundo do level escolhido
            DrawTexture(levelbackground,0,0,RAYWHITE);


            for(int i=0; i<4; i++)
            {
                if(select_level == 1){
                    //tubes de baixo
                    DrawTexture(tube_tatooine,tubes[i].position.x, tubes[i].position.y, RAYWHITE);
                    //tubes de cima
                    DrawTexture(tube_tatooine,tubes[i].position.x, tubes[i].position.y - 800 - difficulty.gap, RAYWHITE); 
                }
                
                if(select_level == 2){
                    //tubes de baixo
                    DrawTexture(tube_endor,tubes[i].position.x, tubes[i].position.y, RAYWHITE);
                    //tubes de cima
                    DrawTexture(tube_endor,tubes[i].position.x, tubes[i].position.y - 800 - difficulty.gap, RAYWHITE);
                }
                
                if(select_level == 3){
                    //tubes de baixo
                    DrawTexture(tube_deathstar,tubes[i].position.x, tubes[i].position.y, RAYWHITE);
                    //tubes de cima
                    DrawTexture(tube_deathstar,tubes[i].position.x, tubes[i].position.y - 800 - difficulty.gap, RAYWHITE);
                }
            }

            //desenha pontuação do jogador em tempo real
            DrawRectangle(880,95,MeasureText("Score:0000", 45) + 10, 55, Fade(BLACK, 0.5f));
            DrawText(textoscore, 900, 100, 45, YELLOW);

            
}

//função que desenha o player do level selecionado
void draw_player_level(Texture2D boba_textura, Texture2D luke_textura, Texture2D vader_textura, int select_level, PLAYER player){
  
        // auxiliar para troca de level
        // 0 = nenhum level selecionado
        // 1 = tatooine
        // 2 = endor
        // 3 = deathstar
    
        if(select_level == 1)
        {
            DrawTexture(boba_textura, player.position.x, player.position.y, RAYWHITE);
        }

        if(select_level == 2)
        {
            DrawTexture(luke_textura, player.position.x, player.position.y, RAYWHITE);
        }

        if(select_level == 3)
        {
            DrawTexture(vader_textura, player.position.x, player.position.y, RAYWHITE);
        }
    
}

//função para desenhar o aviso de game over e suas opções (jogar novamente ou menu)
void draw_gameover(Texture2D gameover){
    DrawTexture(gameover,450,100,RAYWHITE);            
    DrawRectangle(450, 365, 300, 100, YELLOW);
    DrawText("PLAY AGAIN", 470, 385, 40, BLACK);
    DrawRectangle(450, 515, 300, 100, YELLOW);
    DrawText("MENU", 470, 535, 40, BLACK);
}

//função para desenhar a tela de ranking
void draw_ranking(Texture2D fundo_menu, Texture2D obiwan, int screenwidth, PLAYER_RANKING *player_ranking){    
    
    DrawTexture(fundo_menu,0,0,RAYWHITE); 
    DrawText("RANKING", (screenwidth/2) - (MeasureText("RANKING",60)/2), 100, 60, YELLOW);
    DrawTexture(obiwan, 600, 300, RAYWHITE);
    
    //desenha nome e pontuação dos jogadores que estão no ranking           
    for(int i = 0; i<5; i++){ 
    DrawText(TextFormat("%dº - %s - %d", i + 1, player_ranking[i].nome, player_ranking[i].score),200 , 200 + (80*(i+1)), 30, YELLOW);
    }
}

//função para desenhar opção de voltar para o menu, utilizada em praticamente todas telas do jogo
void draw_op_menu(){
    
    DrawRectangle(980,0,120,62, YELLOW);
    DrawText("MENU",1000,20,30, BLACK);
}

/*======================================================= FUNÇÕES AUXILIARES PARA RODAR O JOGO =================================================================================*/

//função para gerar os tubos inicias a cada vez que a gameplay inicia
void make_initial_tubes(TUBE *tubes, int screenheight, DIFFICULTY difficulty){
    int i;
    
    for(i=0; i < 4; i++){
            //ative o tubo para contar a pontuação posteriormente
            tubes[i].active = true;
            //O primeiro é posicionado no limite da largura da tela e os outros a sua direita com tubos com 400 de distância entre si. 
            tubes[i].position.x = 1200 + (i * 400);            
            if(i>0){
                //se i > 0, posicione o tubo atual com base na posição y do tubo anterior, com uma variação determinada pela dificuldade.
              tubes[i].position.y = GetRandomValue(tubes[i-1].position.y - difficulty.dif_max_altura, tubes[i-1].position.y + difficulty.dif_max_altura);
            }else{
                //se i == 0, posicione o primeiro tubo aleatoriamente entre 50 e 750.
              tubes[i].position.y = GetRandomValue(50, 750);  
            }
            //valor mínimo de posição y (750) para os tubos de baixo aparecerem na tela
            tubes[i].position.y = min(tubes[i].position.y, (screenheight - 50));
            //valor mínimo de posição y (50) para os tubos de cima aparecerem na tela
            tubes[i].position.y = max(tubes[i].position.y, (difficulty.gap + 50));
            
        }
}


//função que carrega o ranking, utilizada uma vez no começo da main
void loadranking(PLAYER_RANKING *player_ranking){
    FILE *rankarq;
    rankarq = fopen("ranking.bin", "rb");
        
        if (rankarq != NULL) {
            //lê conteúdo do arquivo binário para a array do tipo PLAYER_RANKING
            fread(player_ranking, sizeof(PLAYER_RANKING), 5, rankarq);
            fclose(rankarq);

        }else{
            //se o arquivo não existir, cria e preenche o ranking com jogadores genéricos e pontuações zeradas
            for(int i=0;i<5;i++){
            strcpy(player_ranking[i].nome, "Player");
            player_ranking[i].score = 0;
            }
            rankarq = fopen("ranking.bin", "wb");
            fwrite(player_ranking,sizeof(PLAYER_RANKING), 5, rankarq);
            fclose(rankarq);
        }
    
    
}

 
//função para salvar o ranking toda vez que o mesmo for alterado    
void saveranking(PLAYER_RANKING currentPlayer, PLAYER_RANKING *player_ranking){
    
    
    for (int i = 0; i < 5; i++) {
        //se a pontuação do jogador for maior que a pontuação do jogador em questão do ranking
        if (currentPlayer.score > player_ranking[i].score) {
            // Deslocar os jogadores abaixo para abrir espaço para o novo
            for (int j = 4; j > i; j--) {
                player_ranking[j] = player_ranking[j-1];
                
            }

            // Atualizar a posição do novo jogador
            player_ranking[i] = currentPlayer;
            
            //escreve no arquivo o ranking atualizado
            FILE *rankarq = fopen("ranking.bin", "wb");
            if (rankarq != NULL) {
            fwrite(player_ranking, sizeof(PLAYER_RANKING), 5, rankarq);
            fclose(rankarq);
            }
            break;  // Sair do loop depois de atualizar o ranking
        }
    }
        
  
}    

//função para escolher opção menu
void op_menu(GameScreen *currentScreen){
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionRecs((Rectangle){980,0,120,60}, (Rectangle){GetMousePosition().x, GetMousePosition().y, 1, 1}))
        {
            *currentScreen = MENU;
        }
}

//função que lê os arquivos texto das dificuldades
void le_dificuldade(DIFFICULTY *difficulty, char diff_select[]){ 
    FILE *diffarq;
    diffarq = fopen(diff_select, "r");
        
        if (diffarq != NULL) {
            //lê o conteudo da dificuldade para a estrutura difficulty a ser utilizada no jogo
            fscanf(diffarq, "%d %d %d %d %d %d %d", &difficulty->score_threshold, &difficulty->gap, &difficulty->inc_gap,
                   &difficulty->dif_max_altura, &difficulty->inc_dif_max_altura, &difficulty->vel_obstaculos, &difficulty->inc_vel_obstaculos);

            fclose(diffarq);
        }
}

//função que faz os incrementos na dificuldade de acordo com o score_threshold
void ajust_diff(DIFFICULTY *difficulty, int score, PLAYER player){
    
    //se a pontuação atual for divisível pela variável score_threshold, sinalização de que variáveis devem ser incrementadas
    if(score % difficulty->score_threshold == 0){
        
        //estabelece gap mínimo(dobro da altura do jogador)
        if(difficulty->gap - difficulty->inc_gap > (player.height * 2)){
            difficulty->gap -= difficulty->inc_gap;
        }
        
        //incrementa velocidade dos tubos
        difficulty->vel_obstaculos += difficulty->inc_vel_obstaculos;
        
        //incrementa diferença máxima de altura
        difficulty->dif_max_altura += difficulty->inc_dif_max_altura;
    }
}

/*===================================================== COMEÇO DA FUNÇÃO MAIN - DECLARAÇÃO DE VARIÁVEIS E CONSTANTES =======================================================*/    

int main(void)
{ 
  
    //define dimensões da tela e inicia a janela do jogo
    const int screenwidth = 1200;
    const int screenheight = 800;
    InitWindow(screenwidth, screenheight, "FlappyWars");
    
    //jogo roda a 60 quadros por segundo
    SetTargetFPS(60);
    
    //variáveis para ranking
    int key;
    int letterCount = 0;
    PLAYER_RANKING player_ranking[5];
    PLAYER_RANKING currentPlayer;
    currentPlayer.score = 0;
    currentPlayer.nome[0] = '\0' ;
    int auxiliar_ranking = 0;
    
    //load do ranking
    loadranking(player_ranking);
    
    //definição da estrutra para as dificuldades
    DIFFICULTY difficulty;
    
    //variáveis para menu e pontuação
    float y_abertura = 0;
    int close = 0;
    int auxiliar_music = 1;
    int i, j;
    int levelselectedheight = 670;
    int select_level = 0;
    
    //variáveis da pontuação
    int score = 0;
    char textoscore[32];
    
    //cria os tubos que serão utilizados no jogo
    TUBE tubes[4];
    const int tubewidth = 150;
    const int tubeheight = 800;
    tubes[i].active = true;   
    
    //cria e pre define o jogador
    const playerwidth = 56;
    const playerheight = 80;
    PLAYER player = {{200, 100},playerwidth, playerheight, 0};
    
    //carrega texturas do menu
    Texture2D fundo_menu = LoadTexture("./images/fundo_menu.png");
    Texture2D logo_menu = LoadTexture("./images/logo_menu.png");
    Texture2D levelbackground = fundo_menu;
    Texture2D blank = LoadTexture("./images/blank.png");
    Texture2D menulevelselected = blank;
    
    //carregas as texturas dos fundos de cada level
    Texture2D tatooine = LoadTexture("./images/tatooine.png");
    Texture2D endor = LoadTexture("./images/endor.png");
    Texture2D deathstar = LoadTexture("./images/deathstar.png");
    Texture2D gameover = LoadTexture("./images/gameover.png");
    Texture2D obiwan = LoadTexture("./images/obiwan.png");
    GameScreen currentScreen = MENU;
    
    //carrega textura do personagem da tela de "Play"
    Texture2D grogu = LoadTexture("./images/grogu.png");
    
    //carrega as texturas dos levels
    Texture2D smalltatooine = LoadTexture("./images/smalltatooine.png");
    Texture2D smallendor = LoadTexture("./images/smallendor.png");
    Texture2D smalldeathstar = LoadTexture("./images/smalldeathstar.png");
    
    //carrega as texturas dos personagens e redefine suas dimensões:
    
    //boba (level 1)
    Image boba_img = LoadImage("./images/boba.png");
    ImageResize(&boba_img, 56, 80);
    Texture2D boba_textura = LoadTextureFromImage(boba_img);
    //luke (level 2)
    Image luke_img = LoadImage("./images/luke.png");
    ImageResize(&luke_img, 56, 80);
    Texture2D luke_textura = LoadTextureFromImage(luke_img);
    //vader (level 3)
    Image vader_img = LoadImage("./images/vader.png");
    ImageResize(&vader_img, 56, 80);
    Texture2D vader_textura = LoadTextureFromImage(vader_img);
    
    //carrega as texturas dos tubos
    Texture2D tube_tatooine = LoadTexture("./images/tube_tatooine.png");
    Texture2D tube_endor = LoadTexture("./images/tube_endor.png");
    Texture2D tube_deathstar = LoadTexture("./images/tube_deathstar.png");
    
    //carrega as texturas dos planetas do menu
    Texture2D vstatooine = LoadTexture("./images/vstatooine.png");
    Texture2D vsdeathstar = LoadTexture("./images/vsdeathstar.png");
    Texture2D vsendor = LoadTexture("./images/vsendor.png");
    
    //carrega as texturas volume
    Texture2D volumeon = LoadTexture("./images/volumeon.png");
    Texture2D volumeoff = LoadTexture("./images/volumeoff.png");
    Texture2D volume = volumeon;  
    
    //inicia audio e carrega músicas do jogo
    InitAudioDevice();
    Music music_menu = LoadMusicStream("./audio/music_menu.mp3");
    Music music_game = LoadMusicStream("./audio/music_game.mp3");
    PlayMusicStream(music_menu);
    PlayMusicStream(music_game);
    SetMasterVolume(0.2f);  
    
/*======================================================================== LOOP PRINCIPAL DO JOGO ================================================================================*/   
    //equanto a janela nao sinalizar com fechar, continuar rodando
    while(!WindowShouldClose() && !close)
    {
        
        
/*============================================================= SWITCH CASE PARA TELAS DIFERENTES (RODA JOGO) ================================================================*/
        switch(currentScreen)
        {
        //TELA DE MENU    
        case MENU:
        {
            
            //roda música no menu
            UpdateMusicStream(music_menu);
            
            //se for apertado espaço, pula a abertura, colocando o y da abertura fora da tela, permitindo a abertura do menu principal.
            if(IsKeyDown(KEY_SPACE))
        {
            y_abertura = 1400;
        }
        
        //incrementa o y da abertura enquanto ele não sair da tela
        if(y_abertura <= 1400)
        {

            y_abertura += 0.8f;

        }
        //se o y da abertura tiver saído da tela, mostra o menu principal 
        if(y_abertura >= 1400){
            
                //se o mouse clicar no botao "PLAY" e algum level tiver sido selecionado, ir para o jogo
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionRecs((Rectangle){450, 215, 300, 100},
                                                                                  (Rectangle){GetMousePosition().x, GetMousePosition().y, 1, 1}) && select_level != 0)
                {
                    currentScreen = PLAY;
                }
                
                //se o mouse clicar no botao "LEVELS", abre a tela com as opções de levels
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionRecs((Rectangle){450, 365, 300, 100},
                                                                                  (Rectangle){GetMousePosition().x, GetMousePosition().y, 1, 1}))
                {
                    currentScreen = LEVELS;
                }
                
                //se o mouse clicar no botao "RANKING", abre o ranking com as melhores pontuações
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionRecs((Rectangle){450, 515, 300, 100},
                                                                                  (Rectangle){GetMousePosition().x, GetMousePosition().y, 1, 1}))

                {
                    currentScreen = RANKING;
                }
                
                //se o mouse clicar no botao "EXIT", fecha o jogo
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionRecs((Rectangle){450, 665, 300, 100},
                                                                                  (Rectangle){GetMousePosition().x, GetMousePosition().y, 1, 1}))
                {
                    close = 1;
                }
                
                //se o mouse clicar no indicador de volume, desliga o volume(caso o mesmo esteja ligado)
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionRecs((Rectangle){45,45,100, 100},
                                                                                  (Rectangle){GetMousePosition().x, GetMousePosition().y, 1, 1}) && auxiliar_music == 1)
                {   
                    SetMasterVolume(0);
                    volume = volumeoff;
                    auxiliar_music = 0;
                    
                 //se o mouse clicar no indicador de volume, liga o volume(caso o mesmo esteja desligado)   
                }else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionRecs((Rectangle){45,45,100, 100},
                                                                                  (Rectangle){GetMousePosition().x, GetMousePosition().y, 1, 1}))
                {   
                   
                    SetMasterVolume(0.2f);
                    volume = volumeon;
                    auxiliar_music = 1;
                       
                }
        }     


            break;
        }

        //TELA DE PLAY
        case PLAY:
        {   
            //roda a musica do jogo
            SeekMusicStream(music_game, 3);
            UpdateMusicStream(music_game);
        
            //zera a velocidade do personagem
            player.velocidade =0;
            
            //se for apertado a tecla espaço, começa a gameplay
            if (IsKeyPressed(KEY_SPACE))
            {
                currentScreen = GAMEPLAY;
            }
            
            //adiciona colisão com o botão voltar para o menu do canto superior direito da tela
            op_menu(&currentScreen);


            break;
        }
        
        //TELA DA GAMEPLAY
        case GAMEPLAY:
        {
            //roda musica do jogo
            UpdateMusicStream(music_game);
            
            //Checagem da colisão entre o personagem, os tubos e as bordas da tela, feita por meio de um for loop para os 4 tubos. Se colidirem, reinicializa as variáveis que foram alteradas ao longo do jogo, lê a dificuldade do level que estiver selecionado e vai para a tela de GAMEOVER
            
            for(i=0; i<4; i++){
                    //colisão tubos de cima
               if((CheckCollisionRecs((Rectangle){player.position.x,player.position.y, player.width, player.height},
                                      (Rectangle){tubes[i].position.x, tubes[i].position.y - 800 - difficulty.gap,tubewidth, 800})))
                   {
                    player.velocidade =0;
                    currentScreen = GAMEOVER;
                    if(select_level == 1){
                        le_dificuldade(&difficulty, "dificuldade1.txt");
                    }
                    if(select_level == 2){
                        le_dificuldade(&difficulty, "dificuldade2.txt");
                    }
                    if(select_level == 3){
                        le_dificuldade(&difficulty, "dificuldade3.txt");
                    }
                    player.position.y = 200;
                    
                    //reinicializa os tubos
                    make_initial_tubes(tubes,screenheight, difficulty);

                }   //colisão tubos de cima
                else if((CheckCollisionRecs((Rectangle){player.position.x,player.position.y, player.width, player.height},
                (Rectangle){tubes[i].position.x, tubes[i].position.y, tubewidth, 800})))
                {   
                    player.velocidade =0;
                    currentScreen = GAMEOVER;
                    if(select_level == 1){
                        le_dificuldade(&difficulty, "dificuldade1.txt");
                    }
                    if(select_level == 2){
                        le_dificuldade(&difficulty, "dificuldade2.txt");
                    }
                    if(select_level == 3){
                        le_dificuldade(&difficulty, "dificuldade3.txt");
                    }
                    
                    player.position.y = 200;
                    
                    //reinicializa os tubos
                    make_initial_tubes(tubes, screenheight, difficulty);

                }

            }
            
            //colisão com os limites inferiores da tela
            if((CheckCollisionRecs((Rectangle){player.position.x,player.position.y, player.width, player.height},
                                   (Rectangle){0, screenheight + (2 * player.height) , screenwidth, player.height})))
            {   
                player.velocidade =0;
                currentScreen = GAMEOVER;
                    if(select_level == 1){
                        le_dificuldade(&difficulty, "dificuldade1.txt");
                    }
                    if(select_level == 2){
                        le_dificuldade(&difficulty, "dificuldade2.txt");
                    }
                    if(select_level == 3){
                        le_dificuldade(&difficulty, "dificuldade3.txt");
                    }
                player.position.y = 200;
                
                
                //reinicializa os tubos
                make_initial_tubes(tubes,screenheight, difficulty);
            }
            //colisão com os limites superiores da tela
            if((CheckCollisionRecs((Rectangle){player.position.x,player.position.y, player.width, player.height},
                                   (Rectangle){0, - (2 * player.height) , screenwidth, player.height})))
            {
                player.velocidade =0;
                currentScreen = GAMEOVER;
                    if(select_level == 1){
                        le_dificuldade(&difficulty, "dificuldade1.txt");
                    }
                    if(select_level == 2){
                        le_dificuldade(&difficulty, "dificuldade2.txt");
                    }
                    if(select_level == 3){
                        le_dificuldade(&difficulty, "dificuldade3.txt");
                    }
                player.position.y = 200;
                
                
                //reinicializa os tubos
                make_initial_tubes(tubes,screenheight, difficulty);
            }

            //se for apertado espaço(pulo), velocidade do jogar recebe -8 (sobe na tela)
            if(IsKeyPressed(KEY_SPACE))
            {
                player.velocidade = -8;
            }

            //percorre os tubos
            for(i=0; i<4; i++)
            {   
                //se o tubo estiver com a sua booleana ativada e o jogador tiver passado por ele, conta ponto e desativa a booleana desse tubo
                if(tubes[i].active && player.position.x > tubes[i].position.x){
                    score++;
                    //ajusta a dificuldade de acordo com o numero de pontos
                    ajust_diff(&difficulty, score, player);
                    tubes[i].active = false;
                    currentPlayer.score = score;
                    
                    //se a pontuação do jogador atual for maior que o último colocado do ranking, aciona a auxiliar do ranking indicando que o ranking deve ser atualizado
                    if(currentPlayer.score > player_ranking[4].score){
                        auxiliar_ranking = 1;
                    }
                }
                    //se o tubo tiver passado pela tela
                if(tubes[i].position.x <= -tubewidth)
                {   
                    //teleporta o tubo de volta para o início, do lado direito da tela
                    tubes[i].position.x = 1600 - tubewidth;
                    tubes[i].active = true;
                    if(i>0){
                      //se não for o primeiro tubo, ajusta a posição y em relação ao tubo anterior
                      tubes[i].position.y = GetRandomValue(tubes[i-1].position.y - difficulty.dif_max_altura, tubes[i-1].position.y + difficulty.dif_max_altura);
                    }else{
                      //se for o primeiro tubo, ajusta a posição y em relação ao terceiro tubo
                      tubes[i].position.y = GetRandomValue(tubes[3].position.y - difficulty.dif_max_altura, tubes[3].position.y + difficulty.dif_max_altura);  
                    }
                    //valor mínimo de posição y (750) para os tubos de baixo aparecerem na tela
                    tubes[i].position.y = min(tubes[i].position.y, (screenheight - 50));
                    //valor mínimo de posição y (50) para os tubos de cima aparecerem na tela
                    tubes[i].position.y = max(tubes[i].position.y, (difficulty.gap + 50));
                 
                }
                
            }
            


            //movimentação dos tubos a partir da velocidade dada na dificuldade
            for(i=0; i<4; i++)
            {
                tubes[i].position.x -= difficulty.vel_obstaculos;

            }
            
            //velocidade e aceleração do jogador
            player.velocidade += .4f;
            player.position.y += player.velocidade;
            
            //atualiza a pontuação em tempo real para desenha-la na tela
            sprintf(textoscore, "score: %d", score);
            
            break;


        }
        //TELA DE GAMEOVER
        case GAMEOVER:
        {
            //se o jogador não tiver pontuação para entrar no ranking, fornece os botões de jogar novamente ou ir pro menu
            if(auxiliar_ranking==0){
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionRecs((Rectangle){450, 365, 300, 100},
                                                                                 (Rectangle){GetMousePosition().x, GetMousePosition().y, 1, 1}))
                {   
                    score = 0;
                    currentScreen = PLAY;
                }
                
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionRecs((Rectangle){450, 515, 300, 100},
                                                                                 (Rectangle){GetMousePosition().x, GetMousePosition().y, 1, 1}))
                {   
                    score = 0;
                    currentScreen = MENU;
                }
            }
          
            
            break;
        }
        
        //TELA DE LEVELS
        case LEVELS:
        {   
            //roda musica no menu
            UpdateMusicStream(music_menu);
            
            //menu com 3 botões que correspondem cada um a um level(dificuldade). Uma vez selecionado, muda a variável select_level, que vai indicar para outras partes do programa qual o level que o jogador selecionou
            
            //botão dificuldade1 fácil(planeta tatooine)
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionRecs((Rectangle){120,220,260,260},(Rectangle){GetMousePosition().x, GetMousePosition().y, 1, 1}))
            {
                levelbackground = tatooine;
                select_level = 1;
                le_dificuldade(&difficulty, "dificuldade1.txt");
                make_initial_tubes(tubes,screenheight, difficulty);
                currentScreen = MENU;
                menulevelselected = vstatooine;
                levelselectedheight = 670;
                
            }
            
            //botão dificuldade2 média(planeta endor)
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionRecs((Rectangle){520,220,260,260},(Rectangle){GetMousePosition().x, GetMousePosition().y, 1, 1}))
            {
                levelbackground = endor;
                select_level = 2;
                le_dificuldade(&difficulty, "dificuldade2.txt");
                make_initial_tubes(tubes,screenheight, difficulty);
                currentScreen = MENU;
                menulevelselected = vsendor;
                levelselectedheight = 670;
                
                
            }
            
            //botão dificuldade3 difícil(estrela da morte)
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionRecs((Rectangle){920,220,260,260},(Rectangle){GetMousePosition().x, GetMousePosition().y, 1, 1}))
            {
                levelbackground = deathstar;
                select_level = 3;
                le_dificuldade(&difficulty, "dificuldade3.txt");
                make_initial_tubes(tubes,screenheight, difficulty);
                currentScreen = MENU;
                menulevelselected = vsdeathstar;
                levelselectedheight = 650;

                

            }
            //adiciona colisão com o botão voltar para o menu do canto superior direito da tela
            op_menu(&currentScreen);
            break;
        }
        
        //TELA DO RANKING
        case RANKING:
        {   
           //roda musica no menu
           UpdateMusicStream(music_menu);
           //adiciona colisão com o botão voltar para o menu do canto superior direito da tela
           op_menu(&currentScreen); 
        }
        
        
        
        }
        
        
        
        
        
        

    
/*================================================================= SWITCH CASE PARA DESENHOS NAS TELAS ===========================================================================*/
        //inicia desenhos
        BeginDrawing();
        
        switch(currentScreen)
        {

        case MENU:
        {   
            //desenha a abertura e o menu principal do jogo
            draw_menu(fundo_menu, logo_menu, y_abertura,  levelselectedheight,  menulevelselected, volume);
            break;
        }
    
        case PLAY:
        {
            //desenha a tela de PLAY (anterior a gameplay)
            draw_play(levelbackground, grogu);
            //desenha a opção de voltar para o menu no canto superior direito da tela
            draw_op_menu();


            break;
        }

        case GAMEPLAY:
        {   
            //desenha a gameplay, com tubos e fundos diferentes dependendo da escolha do level
            draw_gameplay(levelbackground, tube_tatooine, tube_endor, tube_deathstar, textoscore, tubes, difficulty, select_level);
            
            //desenha pontuação na tela
            DrawText(textoscore, 900, 100, 45, YELLOW);

            //desenha o jogador dependendo da escolha de level
            draw_player_level(boba_textura, luke_textura, vader_textura, select_level, player);

        break;
        }
        
        case GAMEOVER:
        {
            //desenha fundo do level atual
            
            DrawTexture(levelbackground,0,0,RAYWHITE);
            
            if(auxiliar_ranking==0){
            draw_gameover(gameover);
            }else{
                        DrawRectangle(200, 100, 800, 300,BLACK);
                        DrawText("PARABENS!", 600 - (MeasureText("PARABENS!", 65) / 2), 120, 65, PURPLE );
                        DrawText("Você fez uma excelente pontuação e", 600 - (MeasureText("Voce fez uma excelente pontuação e", 30) / 2), 200, 30, WHITE);
                        DrawText("entrou para o ranking dos mestres jedis!", 600 - (MeasureText("entrou para o ranking dos mestres jedis!", 30) / 2), 250, 30, WHITE);
                        DrawText("Digite seu nome: (máximo 15 caracteres)", 315, 350, 30, YELLOW);
                        
                        //key é a tecla digitada pelo teclado
                        key = GetCharPressed();
                        
                        //intervalo de chars que são aceitas (32 - 125 em ASCII)
                        if ((key >= 32) && (key <= 125) && (letterCount < 15))
                        {
                            currentPlayer.nome[letterCount] = (char)key;
                            currentPlayer.nome[letterCount+1] = '\0';
                            letterCount++; //contador de letras
                        }
                        
                        //se for apertada a tecla backspace, diminui o contador de letras e acrescenta o '\0' no começo da string para zerar seus caracteres
                        if (IsKeyPressed(KEY_BACKSPACE))
                        {
                            letterCount--;
                            if (letterCount < 0) letterCount = 0;
                            currentPlayer.nome[letterCount] = '\0';
                        }
                        
                    //desenha na tela fundo preto para as letras enquanto escreve nome
                    DrawRectangle((screenwidth/2) - (MeasureText(currentPlayer.nome,50)/2)-10, 390, MeasureText(currentPlayer.nome,50)+20, 70, BLACK);
                    DrawText(currentPlayer.nome, (screenwidth/2) - (MeasureText(currentPlayer.nome,50)/2), 400, 50, YELLOW);
                
                //se a tecla enter for apertada, salva o nome no ranking e zera as variaveis para futuras inserções de nomes no ranking
                if(IsKeyPressed(KEY_ENTER)){
                auxiliar_ranking = 0;
                saveranking(currentPlayer, player_ranking);
                currentPlayer.nome[0] = '\0';
                letterCount = 0;
                score = 0;  
                currentScreen = PLAY;
                }
            }
         
            break;
        }    
        
        case LEVELS:
        {
            draw_levels(fundo_menu, smalltatooine, smallendor, smalldeathstar);
            //desenha a opção de voltar para o menu no canto superior direito da tela
            draw_op_menu();
            break;
        }
        
        case RANKING:
        {   
           draw_ranking(fundo_menu, obiwan, screenwidth, player_ranking);
           //desenha a opção de voltar para o menu no canto superior direito da tela
           draw_op_menu();
           break;
        }
        
        default:
            break;
        }

        //finaliza desenhos
        EndDrawing();
    }
/*================================================================================ FINALIZA O JOGO ================================================================================*/
    //encerra os audios e musicas do programa
    UnloadMusicStream(music_menu);
    UnloadMusicStream(music_game);
    CloseAudioDevice();

    CloseWindow();



    return 0;

}