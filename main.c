#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int x,y,t,rx,ry,b,ac=1,bc=1,barcos,contador,player[32][32],cpu[32][32],acertos_player,acertos_cpu,erros_player,erros_cpu,barcos_player=1,barcos_cpu=1;
char a;




void criaguia(int t){
    player[0][0]='X';
  for(x=1;x<=t;x++)
    player[x][0]=64+x;
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

void criabarcoaleat(int t){
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

  do{
        rx = rand()%t;
        ry = rand()%t;
        if (rx != 0 && ry !=0 && cpu[rx][ry] !='o'){
        cpu[rx][ry]='o';
        contador ++;
        }
  }while(contador < t);
}

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

void player_ataca(){
  printf("\n[%c][%d]\n",a,b);
  printf("Digite as Coordenadas para Atacar:");
  scanf(" %c%d",&a,&b);

  printf("\n[%d][%d]\n",a,b);


      if(cpu[a-96][b] == 'o'){
        printf("Você Atirou em [%c] [%d] e Acertou\n",a-32,b);
        cpu[a-96][b] = 'x';
        acertos_player += 1 ;
        barcos_cpu-=1;

      }
      if(cpu[a-96][b] == '~'){
        printf("Você Atirou em [%c] [%d] e Errou\n",a-32,b);
        cpu[a-96][b] = 'x';
        erros_player += 1 ;
      }

}

void cpu_ataca(int t){
  srand(time(NULL));

    ac = rand()%t+1;
    bc = rand()%t+1;
    printf("%d %d",ac,bc);

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

void mostra_placar(){
  printf("Seu Placar=====Acertos: %d =====Erros: %d ======Barcos: %d\n",acertos_player,erros_player,barcos_player);
  printf("CPU Placar=====Acertos: %d =====Erros: %d ======Barcos: %d\n",acertos_cpu,erros_cpu,barcos_cpu);


}

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
void gameplay(t){

  criaguia(t);
  criatabuleiro(t);
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
    printf("Voce Perdeu !");
  }
  if(barcos_cpu == 0){
    printf("Voce Venceu !");
  }
}
main(){

printf("Digite o Tamanho do Tabuleiro com no maximo 24 Posicoes:\n");
scanf("%d",&t);
while(t<2 && t>24){
  printf("Digite um valor maior ou igual a 3 e menor igual a 24:\n");
  scanf("%d",&t);
}
  if(t>2 && t<25){
    gameplay(t);
  }
}
