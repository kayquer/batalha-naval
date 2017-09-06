#include <stdio.h>
#include <stdlib.h> //proprocionou uso das funções rand, srand e atoi
#include <time.h> //biblioteca que fornece a função time que foi utilizada de semente para a função rand.
#include <string.h> //bibiloteca que fornece a funções para munipulação de strings.
#include <ctype.h> //biblioteca em que usamos as funções isdigit, isalpha e isspace.
#include <locale.h> //biblioteca que usamos a função setlocale para determinar a localização da lingua portuguesa.


int x,xp,y,t,rx,ry,b,bp,c,ac=1,bc=1,barcos,contador,player[32][32],cpu[32][32],acertos_player,acertos_cpu,erros_player,erros_cpu,barcos_player=1,barcos_cpu=1,asc,printasc,ascp,printascp,ok;
char a,aa[2],bb[2],ap,app[1],bpp[1],escolher;


//Função para criar a guia de letras do Tabuleiro

void criaguia(int t){
    player[0][0]='X';
  for(x=1;x<=t;x++)
    player[x][0]=64+x;
//Função para criar a guia númerica do tabuleiro
  for(y=1;y<=t;y++)
    player[0][y]=y;

    cpu[0][0]='X';
  for(x=1;x<=t;x++)
    cpu[x][0]=64+x;
  for(y=1;y<=t;y++)
    cpu[0][y]=y;

}



void criatabuleiro(int t){
  for(x=1;x<=t;x++)
    for(y=1;y<=t;y++){
      player[x][y]='~';
      player[x][y]='~';
      cpu[x][y]='~';
      cpu[x][y]='~';
    }

}


// Função para o Jogador escolher as posições dos barcos
void criabarco_player(int t,char escolher){


  if(escolher == 's'){
    while(xp<t){
        desenhatabuleiro(t);
//função fgets para ler as coordenadas do usuário
        printf("Digite as Posições do Barcos %d de %d:\n",xp+1,t);
        fgets(app,2,stdin);

        fgets(bpp,2,stdin);

        if(isalpha(app[0]) && isdigit(bpp[0])){
          ap = app[0];
          bp = atoi(bpp);
        }
//estrutura de repetição while para ignorar espaços caso o usuário digite algo diferente do esperado
    while((app[0] = getchar()) != '\n' && app[0] != EOF);
    if(!(isalpha(ap) || isdigit(bp))){
      printf("Posições Incorretas! \n Digite Novamente Nas Posições Corretas\n");
    }
//Condicional para atualização dos valores com base na tabela ASCII
      if(isalpha(ap) || isdigit(bp)){

        if(ap >= 'a' && ap <= 'z'){
          ascp = 96;
          printascp = 32;
        }
        if(ap >= 'A' && ap <= 'Z'){
          asc = 64;
          printascp = 0;
        }
        if(player[ap-ascp][bp]=='o'){
          printf("Você já escolheu Esta Posição ou Ela é Inválida\n");
        }

        if(ap-ascp>t || bp > t){
          printf("Posição Fora do Tabuleiro\n");
        }
        if(player[ap-ascp][bp] == '~'){
          printf("Você Escolheu [%c] [%d] \n",ap-printascp,bp);
          player[ap-ascp][bp] = 'o';
          xp+=1 ;
        }
      }
    }
  }

}
//Função para caso o usuário deseje que as posições de seus barcos sejam determinadas aleatoriamente
void criabarcoaleat(int t){
  if(escolher=='n'){
      srand(time(NULL));
      do{
        rx = rand()%t;
        ry = rand()%t;
        if (rx != 0 && ry !=0 && player[rx][ry] !='o'){
          player[rx][ry]='o';
          contador ++;
        }
      }while(contador < t);
        contador = 0;
      }
      do{
          rx = rand()%t;
          ry = rand()%t;
          if (rx != 0 && ry !=0 && cpu[rx][ry] !='o'){
            cpu[rx][ry]='o';
            contador ++;
          }
      }while(contador < t);
}
//função que calcula a quantidade de barcos
void conta_barcos(int t){
  barcos_player = t;
  barcos_cpu = t;
  for(x=0;x<=t;x++)
    for(y=0;y<=t;y++){

      if(player[x][y] == 'o'){
        barcos = barcos+ 1;
      }

    }
}
//função para determinar as posições de ataque do jogador
void player_ataca(){
  do{
    printf("Digite as Coordenadas para Atacar:");

    fgets(aa,2,stdin);
    fgets(bb,2,stdin);
//função if para determinar se as entradas do usuário foram corretas e atriburis os valores que serão usados para determinar a posição na matriz
    if(isalpha(aa[0]) && isdigit(bb[0])){
      a = aa[0];
      b = atoi(bb);
      c = 0;
    }
//função responsável por detectar caracteres, números e valores diferentes de 0, atribuindo o valor 1 a váriavel flag "c" caso um dos valores seja falso.
    if(!( isalpha(a) && isdigit(bb[0]) && b!=0)){
      printf("Você digitou Incorretamente\n");
      c = 1;
    }


      if(a >= 'a' && a <= 'z'){
        asc = 96;
        printasc = 32;
      }
      if(a >= 'A' && a <= 'Z'){
        asc = 64;
        printasc = 0;
      }
//condicionais que determinam a saida caso o usuário digite valores fora do tabuleiro ou caso atire novamente na mesma posição
      if(cpu[a-asc][b]=='x'){
        printf("Você já Atirou Nesta Posição Ou ela é Inválida\n");
      }
      if(a-asc>t || b > t){
        printf("Posição Fora do Tabuleiro\n");
      }
      while((aa[0] = getchar()) != '\n' && aa[0] != EOF);
//estrutura de repetição responsável por determinar os acertos e erros caso todas as condições acima forem satisfeitas
  }while(cpu[a-asc][b]=='x' || (a-asc>t || b > t) || c== 1   );

        if(cpu[a-asc][b] == 'o'){
          printf("Você Atirou em [%c] [%d] e Acertou\n",a-printasc,b);
          cpu[a-asc][b] = 'x';
          acertos_player += 1 ;
          barcos_cpu-=1;

        }
        if(cpu[a-asc][b] == '~'){
          printf("Você Atirou em [%c] [%d] e Errou\n",a-printasc,b);
          cpu[a-asc][b] = 'x';
          erros_player += 1 ;
        }

  }


//função que gera as posições de ataque do CPU, foi usando srand para gerar a semente e rand mod o valor do tamanho do tabuleiro.
void cpu_ataca(int t){
  srand(time(NULL));
    do{
        ac = rand()%t+1;
        bc = rand()%t+1;
        printf("%d %d",ac,bc);
    }

    while(player[ac][bc]=='x');
      if(player[ac][bc] == 'o'){
        printf("CPU Atirou em [%c] [%d] e Acertou\n",ac+64,bc);
        player[ac][bc] = 'x';
        acertos_cpu += 1 ;
        barcos_player-=1;

      }
      if(player[ac][bc] == '~'){
        printf("CPU Atirou em [%c] [%d] e Errou\n",ac+64,bc);
        player[ac][bc] = 'x';
        erros_cpu += 1 ;
      }


}
//função que exibe o placar da partida
void mostra_placar(){
  printf("Seu Placar=====Acertos: %d =====Erros: %d ======Barcos: %d\n",acertos_player,erros_player,barcos_player);
  printf("CPU Placar=====Acertos: %d =====Erros: %d ======Barcos: %d\n",acertos_cpu,erros_cpu,barcos_cpu);


}
//função responsável por desenhar o tubuleiro do jogador
void desenhatab_player(int t){
  printf("\n====PLAYER====\n");
  for(x=0;x<=t;x++)
    for(y=0;y<=t;y++){
      if(player[x][y]<=t){
        printf("%3.d",player[x][y]);
      }else{printf("%3.c",player[x][y]);
      }
      if(y==t){
        printf("\n");
      }

    }
}
void desenhatabuleiro(int t){
  for(x=0;x<=t;x++)
    for(y=0;y<=t;y++){
      if(player[x][y]<=t){
        printf("%3.d",player[x][y]);
      }else{printf("%3.c",player[x][y]);
      }
      if(y==t){
        printf("\n");
      }

    }
}
//função que desenha o tabuleiro do CPU, ocultando suas posições.
void desenhatab_cpu(int t){
  printf("\n====CPU====\n");
  for(x=0;x<=t;x++)
    for(y=0;y<=t;y++){
      if(cpu[x][y] == 'o'){
        printf("%3.c",'~');
      }
      if(cpu[x][y]<=t){
        printf("%3.d",cpu[x][y]);
      }
      if(cpu[x][y] == '~'){
        printf("%3.c",cpu[x][y]);
      }
      if (y==0){
        printf("%3.c",cpu[x][0]);
      }
      if(cpu[x][y] == 'x'){
        printf("%3.c",cpu[x][y]);
      }
      if(y==t){
        printf("\n");
      }

    }
}
//função responsável por criar a ordenação funcional do jogo, bem como suas condições de termino, terminando em vitória e derrota por cada parte.
void gameplay(t){

  criaguia(t);
  criatabuleiro(t);
  criabarco_player(t,escolher);
  criabarcoaleat(t);
  conta_barcos(t);
  desenhatab_player(t);
  desenhatab_cpu(t);
  mostra_placar();
  do{
    player_ataca(t);
    cpu_ataca(t);
    mostra_placar();
    desenhatab_cpu(t);
    desenhatab_player(t);
    }while(barcos_player>0 && barcos_cpu>0);

  if(barcos_player == 0){
    printf("Você Perdeu !");
  }
  if(barcos_cpu == 0){
    printf("Você Venceu !");
  }
}
main(){
//função para habilitar caracteres especiais para a lingua portuguesa
    setlocale(LC_ALL, "Portuguese");
  do{
    if(escolher != 0){
      printf("Valor Invalido!");
    }
    //função que questiona o usuário caso deseje escolher suas posições ou deixar aleatorias
    printf("\nVocê Deseja Escolher Suas Posições s/n ?\n");
    escolher = getchar();
    while( getchar() != '\n' );
    if(escolher == 's' || escolher == 'n'){
      ok = 1;
    }
    }while(ok != 1);
  ok = 0;
  for(x =0;x<=1;x++){
    //função que registra a escolha do usuário referente ao tamanho do tabuleiro
      printf("Digite o Tamanho do Tabuleiro 5, 10, 15 ou 20 :\n");
      scanf("%d",&t);
      while( getchar() != '\n' );
      switch(t){
        case 5:
        t = 5;
        gameplay(t);
        break;

        case 10:
        t = 10;
        gameplay(t);
        break;

        case 15:
        t = 15;
        gameplay(t);
        break;

        case 20:
        t = 20;
        gameplay(t);
        break;

        default :
        x-=1;
       printf ("Valor invalido!\n");
      }

    }
}




