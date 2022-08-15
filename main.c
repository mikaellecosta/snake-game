#include<conio.h>
#include<time.h>
#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int c[300][2], pontos=1, tamanho=1, cx=60, cy=2;
int comida[2], comida2[2], comida3[3], speed=150;
int nivel = 0;

void gotoxy(int x, int y){
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}

void perguntaNivel() {
    printf("\n\n\n\n\n\n\n\n\n\n ESCOLHA O NIVEL DE DIFICULDADE: [1] FACIL  [2] MEDIO  [3] DIFICIL \n >>>>Escolha: ");
    scanf("%d", &nivel);
    switch(nivel){
        case 1: speed = 300;
        break;

        case 2: speed = 200;
        break;

        case 3: speed = 150;
        break;
    }
}

void desenha(){ // cria a cobrinha para começar a jogar
    int i;
    for(i=0; i<tamanho; i++){
        gotoxy(c[i][0],c[i][1]);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,
    9);
    printf("%c",220);

    }
}

void posicao(){ // atualiza a posição a medida que a cobrinha anda
    int i;
    gotoxy(c[tamanho][0],c[tamanho][1]);
    printf(" ");
    for(i=tamanho; i>=0; i--){
        c[i+1][0] = c[i][0];
        c[i+1][1] = c[i][1];
    }
}

int encostou(){ // verifica se a cobrinha encostou no próprio corpo
    int i, retorno=0;
    for(i=1; i<tamanho; i++){
        if(cx==c[i][0] && cy==c[i][1]){
            retorno=1;
        }
    }
    return retorno;
}

void geraComida() {
    int n;
    n = (rand() % 100);

    if(n >= 0 && n <=50){
        geraComidaVerde();
    }else if(n >= 51 && n <=80){
        geraComidaVermelha();
    } else{
        geraComidaAmarela();
    }

}

void geraComidaVermelha(){ // gera a comida vermelha em uma posição aleatória
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole,
    FOREGROUND_RED);

    gotoxy(comida[0],comida[1]);
    printf(" ");
    srand(time(NULL));
    comida[0] = (rand() % 28) +60;
    comida[1] = (rand() % 18) +1;
    gotoxy(comida[0],comida[1]);
    printf("%c",169);

    SetConsoleTextAttribute(hConsole,
    7);
}

void geraComidaVerde(){ // gera a comida verde em uma posição aleatória
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole,
    FOREGROUND_GREEN);

    gotoxy(comida2[0],comida2[1]);
    printf(" ");
    srand(time(NULL));
    comida2[0] = (rand() % 48) +60;
    comida2[1] = (rand() % 18) +1;
    gotoxy(comida2[0],comida2[1]);
    printf("%c",169);

    SetConsoleTextAttribute(hConsole,
    7);
}

void geraComidaAmarela(){ // gera a comida amarela em uma posição aleatória
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole,
    14);
    gotoxy(comida3[0],comida3[1]);
    printf(" ");
    srand(time(NULL));
    comida3[0] = (rand() % 48) +60;
    comida3[1] = (rand() % 18) +1;
    gotoxy(comida3[0],comida3[1]);
    printf("%c",169);

    SetConsoleTextAttribute(hConsole,
    7);
}



void addRank(char nome[]) { // adiciona um nome ao ranking assim como sua pontuação
  FILE *f;
  f = fopen("ranking.txt", "a");
  if (f == 0) {
    printf("Banco de dados do ranking não esta disponível\n\n");
    exit(1);
  }
  fprintf(f, "%d || Nome: %s \n", pontos, nome);

  fclose(f);
}


void escreverNome() {
  char nome[100];
  printf("Digite seu nome: ");
  scanf("%s", nome);
  addRank(nome);
}

void ordenar(){ // ordena a posição do ranking em ordem de menor pontuação

#define MAX_LEN 100

    char *strFileName = "C:\\Users\\mikah_dn9uzh0\\Desktop\\snakegame\\ranking.txt";
    char *strFileSummary = "C:\\Users\\mikah_dn9uzh0\\Desktop\\snakegame\\out.txt";
    char strTempData[MAX_LEN];
    char **strData = NULL; // String List
    int i, j;
    int noOfLines = 0;

    FILE * ptrFileLog = NULL;
    FILE * ptrSummary = NULL;

    if ( (ptrFileLog = fopen("ranking.txt", "r")) == NULL ) {
        fprintf(stderr,"Error: Could not open %s\n",strFileName);
        return 1;
    }
    if ( (ptrSummary = fopen("out.txt", "w")) == NULL ) {
        fprintf(stderr,"Error: Could not open %s\n",strFileSummary);
        return 1;
    }

    while(fgets(strTempData, MAX_LEN, ptrFileLog) != NULL) {
        if(strchr(strTempData,'\n'))
            strTempData[strlen(strTempData)-1] = '\0';
        strData = (char**)realloc(strData, sizeof(char**)*(noOfLines+1));
        strData[noOfLines] = (char*)calloc(MAX_LEN,sizeof(char));
        strcpy(strData[noOfLines], strTempData);
        noOfLines++;
    }
    // loop para reorganizar o ranking

    for(i= 0; i < (noOfLines - 1); ++i) {
        for(j = 0; j < ( noOfLines - i - 1); ++j) {
            if(strcmp(strData[j], strData[j+1]) > 0) {
                strcpy(strTempData, strData[j]);
                strcpy(strData[j], strData[j+1]);
                strcpy(strData[j+1], strTempData);
            }
        }
    }
    // escreve o ranking organizado no arquivo out

    for(i = 0; i < noOfLines; i++)
        fprintf(ptrSummary,"%s\n",strData[i]);
    for(i = 0; i < noOfLines; i++)
        free(strData[i]);
    free(strData);
    fclose(ptrFileLog);
    fclose(ptrSummary);
    return 0;
}


int main(){
    int i, gameover=0;
    int tecla;

    perguntaNivel();
    system("cls");
if(nivel != 0){ // cria o campo inicial do jogo que a cobrinha irá percorrer
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,13);

    for(i=55; i<110; i++){ // linha superior
        gotoxy(i,0);
        printf("%c",219);
        Sleep(5);
    }
    for(i=0; i<30; i++){ // coluna da direita
        gotoxy(110,i);
        printf("%c",219);
        Sleep(5);
    }
    for(i=110; i>=55; i--){ // linha inferior
        gotoxy(i,30);
        printf("%c",219);
        Sleep(5);
    }
    for(i=30; i>0; i--){ // coluna da esquerda
        gotoxy(55,i);
        printf("%c",219);
        Sleep(5);
    }


    geraComida(); // gera a comida pelo sort entre os 3 tipos

    desenha(); // cria a cobrinha
    tecla='d'; // direção para a direita
    while(gameover==0){ // enquanto o usuário não perder
        gotoxy(112,2); // informações de pontos, tamanho e velocidade em x= 112 e y= 2,4,6
        printf("Pontos: %d\t",pontos);
        gotoxy(112,4);
        printf("Tamanho: %d\t",tamanho);
        gotoxy(112,6);
        printf("Velocidade: %d caracteres/s",speed);
        c[0][0]=cx;
        c[0][1]=cy;
        if(kbhit()) // se alguma tecla for apertada, o valor
            tecla=getch(); // vai para a variável 'tecla'

        if(tecla=='w' || tecla=='W' || tecla==72){
            cy--;
            if(cy==0) break; // se a cabeça da cobra estiver na parede superior,
        }                    // o usuario perdeu o jogo
        if(tecla=='a' || tecla=='A' || tecla==75){
            cx--;
            if(cx==55) break; // se a cabeça da cobra estiver na parede da esquerda,
        }                    // o usuario perdeu o jogo
        if(tecla=='s' || tecla=='S' || tecla==80){
            cy++;
            if(cy==30) break; // se a cabeça da cobra estiver na parede de baixo,
        }                     // o usuario perdeu o jogo
        if(tecla=='d' || tecla=='D' || tecla==77){
            cx++;
            if(cx>=110) break; // se a a cabeça da cobra estiver na parede da direita,
        }                     // o usuario perdeu o jogo

        if(cx==comida[0] && cy==comida[1]){ // se a cobra comer a comida vermelha
            pontos+=2;
            geraComida();
            Beep(5000,100);
        }
        if(cx==comida2[0] && cy==comida2[1]){ // se a cobra comer a comida verde
            pontos++;
            tamanho++;
            geraComida();
            Beep(1000,100);
        }
        if(cx==comida3[0] && cy==comida3[1]){ // se a cobra comer a comida amarela
            pontos+=3;
            tamanho+=3;
            geraComida();
            Beep(3000,100);
        }
        gameover=encostou();
        posicao(); // Atualiza a cobra
        desenha(); // Desenha a cobra
        gotoxy(70,30);
        Sleep(speed);
    }
    system("cls"); // caso o usuario perca, a tela é limpa e exibe uma mensagem final:


    printf("-----> VOCE PERDEU! PONTOS: %d <----- \n",pontos);

    SetConsoleTextAttribute(hConsole,
    10);


printf("                          __                         \n");  // cobrinha morta em asc art
printf("           ---_ ...... _/_ -\\                 \n");
printf("          / xx .      ./ xx\\ \\                \n");
printf("          : '         /__-'   \\.             \n");
printf("         /                      )            \n");
printf("       _/                  >   .'            \n");
printf("     /   '   .       _.-'' /  .'             \n");
printf("     \\           __/''     /.'               \n");
printf("       \\ '--  .-'' /     //'                 \n");
printf("        \\|  \\ | /     //                     \n");
printf("             \\:     //                    \n");
printf("          `\\/     //                         \n");
printf("           \\___\\//                          \n");
printf("               |                           \n");
printf("               |  \\/                     \n");
printf("               |__/                    ");

escreverNome(); // pede o nome do jogador e usa a funçao addRank(nome) que já está atrelada a funçao indicada na linha
ordenar(); // utiliza a funçao para ordernar o ranking
system("pause");




}
}
