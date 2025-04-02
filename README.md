# FlappyWars
Instruções de jogo
========================================================================================================

Objetivo do trabalho: 
A meta consiste em criar uma versão simplificada do famoso jogo Flappy Bird, na linguagem de programação C, fazendo uso da biblioteca gráfica Raylib.
No caso, será implementada a temática do renomado universo de Star Wars, por isso tem o título FlappyWars.

Dificuldades: as variáveis de dificuldade(score_threshold, gap, inc_gap, dif_max_altura, inc_dif_max_altura, vel_obstaculos, inc_vel_obstaculos) de cada level podem ser alteradas ao modificar cada arquivo texto presente na pasta do jogo.
Com essas variáveis é possível modificar o tamanho do espaço entre os tubos, a velocidade dos tubos, a diferença de altura máxima entre dois tubos consecutivos e de quantos em quantos pontos será feito o incremento delas.Esses incrementos
também podem ser alterados.
	* "dificuldade1.txt"
	* "dificuldade2.txt"
	* "dificuldade3.txt"

Ranking: Toda vez que o jogo inicia, é carregado um arquivo binário que contem o ranking com os cinco melhores jogadores e suas respectivas pontuações.
Caso o arquivo não existe, o arquivo é criado com cinco jogadores genéricos e pontuações zeradas.
	* "ranking.bin"

Jogo:
- Ao abrir o jogo, inicia-se a tela de abertura, que pode ser pulada com a tecla SPACE.

- Todas as opções do menu são acessadas pelo click com o botão esquerdo do mouse.

- Após a abertura, é iniciado o menu principal. Nele, são apresentadas as opções de PLAY (jogar), LEVELS (selecionar dificuldade), RANKING (exibe ranking), EXIT (sai do jogo).

- IMPORTANTE: o botão de PLAY só é liberado para acesso após algum level ser selecionado.

- Botão LEVELS: tela de seleção de dificuldade com três planetas, cada um representando uma dificuldade a ser selecionada; Tatooine(fácil), Endor(médio) e Deathstar(Difícil).

- Botão PLAY: leva para uma tela anterior a gameplay de fato, que só tem a opção de voltar para o menu no canto superior direito, ou a de jogar pressionando a tecla SPACE.

- Ao apertar SPACE e iniciar a gameplay, o jogador é controlado apenas com a tecla SPACE, que ao ser pressionada, resulta em um pulo do personagem. O desafio é passar por dentro de obstáculos (tubos) sem colidir com os mesmos,
somando um ponto a cada vez que o jogador passar por um tubo. Caso ele colida com os tubos ou saia da tela, entra na tela de GAMEOVER, onde pode acontecer duas coisas:

	-> se o jogador tiver pontuação suficiente para entrar no ranking de top 5 melhores pontuações, abre uma tela o parabenizando e permitindo que o mesmo insira seu nome (max 15 caracteres) para visualizá-lo no ranking.
	-> se o jogador não tiver pontuação suficiente para entrar no ranking, abre uma tela com opções de jogar novamente ou ir para o menu.

- Botão RANKING: tela para visualizar o ranking de top5 pontuações do jogo.

- Botão EXIT: sai do jogo.
