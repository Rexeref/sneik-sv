
///
///  DICHIARAZIONI GLOBALI
///

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>

#define VERT 15
#define ORIZ 40
#define BASELENGHT 5

//Per Escape Sequence printf("\x1b[%d;%dHX", y, x);
#include <windows.h>
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004

//Per Funzione  sleep_ms();
void sleep_ms(int milliseconds);

void howSnak(int len, int posHX, int posHY, int timeMatrix[ORIZ][VERT]);

int printAll(int timeMatrix[ORIZ][VERT], int len, int points);

void rstrFillChar(char raster[VERT][ORIZ], char character);

void genApple(int timeMatrix[ORIZ][VERT]);

//Funzione Copia Inclollata da internet StackOverflow <3 smack smack
void ShowConsoleCursor(int showFlag);

FILE *fp;
char nomefile[] = ".sneik-scoreboard";

int main()
{
    system("cls");
    srand(time(NULL));
    ///
    ///  DICHIARAZIONI LOCALI
    ///

    //Per Escape Sequence printf("\x1b[%d;%dHX", y, x);
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD consoleMode;
    GetConsoleMode(console, &consoleMode);
    consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(console, consoleMode);

    ///
    ///  CODICE SNAKE
    ///
    int hx=6, hy=42, last=3, len=BASELENGHT, time[ORIZ][VERT], deathQ=0, start=1, moves=0;

    ShowConsoleCursor(0);

    for(int i=0; i<10000; i++){
        printf("Loading... %d/100\x1b[%d;%dH", i/100, 1, 1);
    }


    for(int i=0; i<VERT; i++){
        for(int j=0; j<ORIZ; j++){
            time[j][i]=0;
        }
    }

    while( 1 ){
        moves++;
        printf("\x1b[%d;%dH\033[36;1mScore: %07d", 3, 45, (len-BASELENGHT-1)*100+moves );
        _cputs( "" );
        if(_kbhit()){
            switch(_getch()){
                case 'w':
                case 'W':
                    last=0;
                    hy--;
                    break;
                case 'a':
                case 'A':
                    last=1;
                    hx--;
                    break;
                case 's':
                case 'S':
                    last=2;
                    hy++;
                    break;
                case 'd':
                case 'D':
                    last=3;
                    hx++;
                    break;
                default:
                    break;
            }

        }
        else{
            switch(last){
                case 0:
                    hy--;
                    break;
                case 1:
                    hx--;
                    break;
                case 2:
                    hy++;
                    break;
                case 3:
                    hx++;
                    break;
                default:
                    break;
            }
        }
        sleep_ms(100);
        time[hx][hy]+=len;
        if(time[hx][hy]==time[hx-1][hy]||time[hx][hy]==time[hx+1][hy]||time[hx][hy]==time[hx][hy-1]||time[hx][hy]==time[hx][hy+1]||start==1){
            start=0;
            len++;
            genApple(time);
            
        }
        howSnak(len, hy, hx, time);
        deathQ = printAll(time, len, 10);
        for(int i; i<VERT; i++){
            if(time[ORIZ][i]==len){
                time[1][i]=len;
                last=0;

            }
            else if(time[0][i]==len){
                time[ORIZ][i]=len;
                last=2;
            }
        }
        for(int i; i<ORIZ; i++){
            if(time[i][VERT]==len){
                time[i][1]=len;
                last=1;

            }
            else if(time[i][0]==len){
                time[i][VERT]=len;
                last=3;
            }
        }
        if(deathQ==1){
            int bestlocalscore=0;char choo;
            if(fopen(nomefile, "r")==NULL){
                fp = fopen(nomefile, "w");
                fclose(fp);
            }
            fp = fopen(nomefile, "r");
            fscanf(fp, "%d", &bestlocalscore);
            fclose(fp);
            if(bestlocalscore<(len-BASELENGHT-1)*100+moves){
                bestlocalscore=(len-BASELENGHT-1)*100+moves;
                fp = fopen(nomefile, "w");
                fprintf(fp, "%d", bestlocalscore);
                fclose(fp);
            }
            printf("\x1b[%d;%dHPunteggio finale => %d\nVuoi tentare a battere il record? (Si' = y, Y, s, S) \n    RECORD = %d\n\n: ", 16, 1, (len-BASELENGHT-1)*100+moves, bestlocalscore);
            scanf("%c", &choo);
            if(choo=='y' || choo=='Y' || choo=='s'||choo=='S'){
                system("sneik");
            }
            return 0;
        }
    }
}


///
/// FUNZIONI
///

void sleep_ms(int milliseconds){ // cross-platform sleep function
#ifdef WIN32
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);if(j!=VERT){
        rstrSquareCharXY('X', VERT/2, ORIZ/2, j, i, VERT, ORIZ, patata);
#else
    if (milliseconds >= 1000)
      sleep(milliseconds / 1000);
    usleep((milliseconds % 1000) * 1000);
#endif
}

void howSnak(int len, int posHX, int posHY, int timeMatrix[ORIZ][VERT]){
    for(int i=0; i<VERT; i++){
        for(int j=0; j<ORIZ; j++){
            if(timeMatrix[j][i]>=1){
                    timeMatrix[j][i]--;
            }
        }
    }
}

void genApple(int timeMatrix[ORIZ][VERT]){
    int patata=rand()%(ORIZ*VERT + 1 - 0) -0;
    for(int i=0; i<VERT; i++){
        for(int j=0; j<ORIZ; j++){
            patata--;
            if(patata==0){
                timeMatrix[j][i]=-1;
            }
        }
    }
}

int printAll(int timeMatrix[ORIZ][VERT], int len, int points){
    int deathQ=0;
    printf("\x1b[%d;%dH", 1, 1);
    for(int i=0; i<VERT; i++){
        for(int j=0; j<ORIZ; j++){
            if(timeMatrix[j][i]>len){deathQ=1;}
            switch(timeMatrix[j][i]){
                case -1: ///frutto
                    printf("\033[31;42m%c\033[0m", 149);
                    break;
                case 0:  ///terreno
                    printf("\033[32;42m \033[0m");
                    break;
                default: ///serpente
                    printf("\033[35;42m%c\033[0m", 178);
                    break;
            }
            printf("\033[93;40m");
        }
        printf("\n");
    }
    return deathQ;
}

void ShowConsoleCursor(int showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
