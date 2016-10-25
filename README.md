# CAMPO MINADO

Jogo campo minado implementado na linguagem C usando a biblioteca grafica Allegro 5

* Para executar o jogo, apenas é necessario abrir o arquivo executavel  (Campo-Minado.exe no Windows e Campo_Minado.o no Linux).
* Para compila-lo é necessario a instalação da biblioteca allegro, [clique aqui](https://sites.google.com/a/liesenberg.biz/cjogos/home/software/ambiente-code-blocks-allegro-5 "Allegro com Code:Blocks") para um tutorial de instalação do allegro com code blocks.
* Caso opte por compilar: 
 1. No Linux use o seguinte comando (depois faça o passo anterior):
   * ``gcc Campo_Minado.c -o Campo_Minado -lallegro -lallegro_dialog -lallegro_ttf -lallegro_font -lallegro_primitives -lallegro_image -lallegro_audio -lallegro_acodec``
 2. No Windowns adicione os seguintes parâmetros para compilação (depois faça o passo anterior):
   * ``-lallegro -lallegro_dialog -lallegro_ttf -lallegro_font -lallegro_primitives -lallegro_image -lallegro_audio -lallegro_acodec``
* [Veja o video da Gameplay] (https://youtu.be/6lzJ9R5j8Xw "Gameplay video")
* Caso o jogo nao esteja igual ao do video, provavelmente é um problema de incompatibilidade com o S.O., se possivel executar o jogo no windows.



## Universidade Federal De Alagoas

### Projeto de Programação 1

#### Professor: Baldoino Neto

##### Grupo:

* Cicero Rafael
* Lucas Ribeiro
* Nelson Gomes
* Thiago Torres


## Sobre o jogo

Primeiramente o menu principal, feito dinamicamente com fila de eventos e varios bitmaps para quando o usuario passar o mouse por cima ele mudar a cor, a transparencia e a cor da fonte. São apresentadas cinco opçoes (**JOGAR**, **INFORMAÇOES**, **VER RANKING**, **CREDITOS**, **SAIR DO JOGO**)

### JOGAR

Em **JOGAR** voce escolhera a dificuldade, o tamanho do tabuleiro e quantas bombas tem em cada dificuldade esta na seção de **INFORMAÇÃO** ao escolher a dificuldade desejada, o tabuleiro começara a carregar com uma animação e ao ficar pronto ele apresentara uma seção a esquerda com **reiniciar** para recomeçar ao jogo e **sair** para voltar ao menu, ao fazer o primeiro clique o cronometro começara e a quantidade de bombas sera mostrada, voce pode clicar com o botao direito ou esquerdo, o *botao esquerdo* voce revelara o que tem aonde foi clicado, o *botão direito* colocara ou tirara uma bandeira, bandeiras servem para sinalizar onde voce acha que tem uma *bomba*, toda vez que uma bandeira for colocada a quantidade de bombas restantes diminuira, os clique sao processados por um calculo especifico que transforma as *coordenadas em pixels* do clique na *linha e na coluna da matriz* o clique so sera processado se respeitar as limitaçoes do tabuleiro, o jogo so irá gerar o tabuleiro *após o primeiro clique* para evitar que o jogador perca no primeiro clique, a geração do campo é feita de forma que ele cria uma matriz com o tamanho desejado dependendo da dificuldade e vai acessando **lugares aleatorios** e caso ja nao tenha uma bomba ou nao seja o lugar que o usuario fez o primeiro clique, ele colocara uma bomba ate a quantidade de bombas serem satisfeitas, apos as bombas serem postas outra funçao passara pela matriz, em toda area que ela passar ela vai *verifiar seus arredores*, respeitando os limites do tabuleiro para nao verificar uma seção fora e dar **segmentation error**, e para cada bomba em volta, aumentara em um o seu valor, com o tabuleiro pronto e salvo, faremos outro tabuleiro que sera o tabuleiro visivel pelo usuario, que começara inteiramente com "#" pois no inicio do jogo nenhuma parte do campo foi revelada, a medida que o usuario vai jogando o tabuleiro se atualiza e carrega a parte grafica junto.

Caso o usuario clique em uma area descoberta, *tudo que esta a sua volta sera descoberto, com exceção das __casas com bandeiras__*; Por isso, se quiser melhorar seu tempo, considere traçar *estrategias que minimizem os cliques*, utilizando essa feature de contorno.

Caso o usuario clique em uma area que o valor seja de **1 a 8**, a area simplesmente **será revelada**, caso seja um **0**, ou seja, **não tenha nenhuma bomba nos quadrados adjacentes** ele iniciara a funçao chamada ``floodfill``, que é feita com *backtracking*, ele primeiramente analisara os quadrados adajcentes e montara todos os candidatos validos, caso a casa analisada seja 0, ele é um candidato valido, pois ele pode se expandir para ele, reiniciando o processo *recursivamente* e sempre marcando por onde ele passou para ele nao passar denovo. Para todos os canditados validos, a condiçao de parada é quando a casa e difirente de 0, no final mostrando todos os zeros que estao adjacentes uns aos outros, depois chamando outra função para completar o floodfill mostrando todos os quadrados adjacentes aos zeros que nao são zeros, igual o campo minado classico.

## VENCER OU PERDER

O jogador perde se **clicar** em **qualquer bomba**, e ganha se **descobrir todas as casas menos as que tiverem bombas**. Para isso, ele sempre *checa quantas casas faltam e se você não já tocou em alguma bomba*; Caso algo aconteça, ele então chama a função de ``ganhar`` e solicita que você digite seu nome com até 3 digitos para ser salvo no **ranking** (E salva a pontuação em um **arquivo de texto**) ou ``perder``.

## ENTRADAS DE TEXTO

Utilizadas ao **ganhar** e ao **pesquisar** o nome no ranking. Para isso, foi necessária um evento que capturasse cada tecla, o Allegro tem um mapeamento de caractere diferente de C. Começa na posição 0, cada tecla, adiciona algo na posição que deve ser preenchida e passa para próxima; se for detectado um backspace, ele volta um casa.

## VER RANKING

Em **VER RANKING** apresentara as **opções de dificuldade** para mostrar o *ranking* de acordo com cada uma, é mostrado apenas o **TOP 5** do *ranking*, mas caso o usuário queira saber sua colocação **não estando no _ranking_** dos 5 melhores, apenas é necessario **digitar no topo** o seu nome (*até 3 digitos*) e o jogo apresentara em cima em uma **box vermelha**, sua colocação seu tempo e seu nome, caso você ocupe mais de uma colocação, o jogo apresentara a com **melhor tempo**, usando *busca binaria* para achar o usuario em uma lista e *bubble sort* para mostrar o melhor tempo e colocação do usuario, lembrando que cada dificuldade tem seu próprio ranking.
