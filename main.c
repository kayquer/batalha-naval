#include <stdio.h>
#include <stdlib.h> //proprocionou uso das fun��es rand, srand e atoi
#include <time.h> //biblioteca que fornece a fun��o time que foi utilizada de semente para a fun��o rand.
#include <string.h> //bibiloteca que fornece a fun��es para munipula��o de strings.
#include <ctype.h> //biblioteca em que usamos as fun��es isdigit, isalpha e isspace.
#include <locale.h> //biblioteca que usamos a fun��o setlocale para determinar a localiza��o da lingua portuguesa.


int x,xp,y,t,rx,ry,b,bp,c,ac=1,bc=1,barcos,contador,player[32][32],cpu[32][32],acertos_player,acertos_cpu,erros_player,erros_cpu,barcos_player=1,barcos_cpu=1,asc,printasc,ascp,printascp,ok;
char a,aa[2],bb[2],ap,app[1],bpp[1],escolher;


//Fun��o para criar a guia de letras do Tabuleiro

void criaguia(int t){
    player[0][0]='X';
  for(x=1;x<=t;x++)
    player[x][0]=64+x;
//Fun��o para criar a guia n�merica do tabuleiro
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


// Fun��o para o Jogador escolher as posi��es dos barcos
void criabarco_player(int t,char escolher){


  if(escolher == 's'){
    while(xp<t){
        desenhatabuleiro(t);
//fun��o fgets para ler as coordenadas do usu�rio
        printf("Digite as Posi��es do Barcos %d de %d:\n",xp+1,t);
        fgets(app,2,stdin);

        fgets(bpp,2,stdin);

        if(isalpha(app[0]) && isdigit(bpp[0])){
          ap = app[0];
          bp = atoi(bpp);
        }
//estrutura de repeti��o while para ignorar espa�os caso o usu�rio digite algo diferente do esperado
    while((app[0] = getchar()) != '\n' && app[0] != EOF);
    if(!(isalpha(ap) || isdigit(bp))){
      printf("Posi��es Incorretas! \n Digite Novamente Nas Posi��es Corretas\n");
    }
//Condicional para atualiza��o dos valores com base na tabela ASCII
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
          printf("Voc� j� escolheu Esta Posi��o ou Ela � Inv�lida\n");
        }

        if(ap-ascp>t || bp > t){
          printf("Posi��o Fora do Tabuleiro\n");
        }
        if(player[ap-ascp][bp] == '~'){
          printf("Voc� Escolheu [%c] [%d] \n",ap-printascp,bp);
          player[ap-ascp][bp] = 'o';
          xp+=1 ;
        }
      }
    }
  }

}
//Fun��o para caso o usu�rio deseje que as posi��es de seus barcos sejam determinadas aleatoriamente
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
//fun��o que calcula a quantidade de barcos
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
//fun��o para determinar as posi��es de ataque do jogador
void player_ataca(){
  do{
    printf("Digite as Coordenadas para Atacar:");

    fgets(aa,2,stdin);
    fgets(bb,2,stdin);
//fun��o if para determinar se as entradas do usu�rio foram corretas e atriburis os valores que ser�o usados para determinar a posi��o na matriz
    if(isalpha(aa[0]) && isdigit(bb[0])){
      a = aa[0];
      b = atoi(bb);
      c = 0;
    }
//fun��o respons�vel por detectar caracteres, n�meros e valores diferentes de 0, atribuindo o valor 1 a v�riavel flag "c" caso um dos valores seja falso.
    if(!( isalpha(a) && isdigit(bb[0]) && b!=0)){
      printf("Voc� digitou Incorretamente\n");
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
//condicionais que determinam a saida caso o usu�rio digite valores fora do tabuleiro ou caso atire novamente na mesma posi��o
      if(cpu[a-asc][b]=='x'){
        printf("Voc� j� Atirou Nesta Posi��o Ou ela � Inv�lida\n");
      }
      if(a-asc>t || b > t){
        printf("Posi��o Fora do Tabuleiro\n");
      }
      while((aa[0] = getchar()) != '\n' && aa[0] != EOF);
//estrutura de repeti��o respons�vel por determinar os acertos e erros caso todas as condi��es acima forem satisfeitas
  }while(cpu[a-asc][b]=='x' || (a-asc>t || b > t) || c== 1   );

        if(cpu[a-asc][b] == 'o'){
          printf("Voc� Atirou em [%c] [%d] e Acertou\n",a-printasc,b);
          cpu[a-asc][b] = 'x';
          acertos_player += 1 ;
          barcos_cpu-=1;

        }
        if(cpu[a-asc][b] == '~'){
          printf("Voc� Atirou em [%c] [%d] e Errou\n",a-printasc,b);
          cpu[a-asc][b] = 'x';
          erros_player += 1 ;
        }

  }


//fun��o que gera as posi��es de ataque do CPU, foi usando srand para gerar a semente e rand mod o valor do tamanho do tabuleiro.
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
//fun��o que exibe o placar da partida
void mostra_placar(){
  printf("Seu Placar=====Acertos: %d =====Erros: %d ======Barcos: %d\n",acertos_player,erros_player,barcos_player);
  printf("CPU Placar=====Acertos: %d =====Erros: %d ======Barcos: %d\n",acertos_cpu,erros_cpu,barcos_cpu);


}
//fun��o respons�vel por desenhar o tubuleiro do jogador
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
//fun��o que desenha o tabuleiro do CPU, ocultando suas posi��es.
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
//fun��o respons�vel por criar a ordena��o funcional do jogo, bem como suas condi��es de termino, terminando em vit�ria e derrota por cada parte.
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
    printf("Voc� Perdeu !");
  }
  if(barcos_cpu == 0){
    printf("Voc� Venceu !");
  }
}
main(){
//fun��o para habilitar caracteres especiais para a lingua portuguesa
    setlocale(LC_ALL, "Portuguese");
  do{
    if(escolher != 0){
      printf("Valor Invalido!");
    }
    //fun��o que questiona o usu�rio caso deseje escolher suas posi��es ou deixar aleatorias
    printf("\nVoc� Deseja Escolher Suas Posi��es s/n ?\n");
    escolher = getchar();
    while( getchar() != '\n' );
    if(escolher == 's' || escolher == 'n'){
      ok = 1;
    }
    }while(ok != 1);
  ok = 0;
  for(x =0;x<=1;x++){
    //fun��o que registra a escolha do usu�rio referente ao tamanho do tabuleiro
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




