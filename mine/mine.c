#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define PUZZLE 11
#define MINE 13
#define NOTMINE 12
#define FLAG 10

#define GAME_END 0
#define GAME_START 1

// data structure
//int mine[rows][cols];
typedef struct player_status{
    int MineNumleft;
    int puzzleleft;
}Status;

typedef struct game_settings{
    int automode;

}Settings;

int array2d_init(int Height, int Width, int MineField[][Width], int initnum)
{
    for(int i = 0; i < Height; i++){
        for(int j = 0; j < Width; j++){
            MineField[i][j] = initnum;
        }
    }
    return 0;
}

int minefield_print(int Height, int Width, int MineField[][Width], Status PlayerStatus)
{
    for(int i = 0; i < Width; i++)
        printf("*");
    printf(" mine ");
    for(int i = 0; i < Width/4; i++)
        printf("*");
    printf(" P:%2d M:%2d ",PlayerStatus.puzzleleft, PlayerStatus.MineNumleft );
    for(int i = 0; i < Width/4; i++)
        printf("*");
    printf("\n   ");
    for(int ax = 0; ax < Width; ax ++)
        printf("%2d",ax);
    printf("\n");
    for(int i = 0; i < Height; i++){
        printf("%2d| ",i);
        for(int j = 0; j < Width; j++){
            if(MineField[i][j] < 9 )
                printf("%d ",MineField[i][j]);
            else{
                if(MineField[i][j] == PUZZLE)
                    printf("Q ");
                else if(MineField[i][j] == NOTMINE)
                    printf("S ");
                else if(MineField[i][j] == MINE)
                    printf("M ");
                else if(MineField[i][j] == FLAG)
                    printf("F ");
            }
        }
        printf("|\n");
    }
    for(int i = 0; i < Width; i++)
        printf("*");
    printf(" mine ");
    for(int i = 0; i < Width; i++)
        printf("*");
    printf("\n");
    return 0;
}

int array2d_print(int Height, int Width, int Array[][Width])
{
    printf("print array2d:\n");
    for(int i = 0; i < Height; i++){
        for(int j = 0; j < Width; j++){
            printf("%d ",Array[i][j]);
        }
        printf("\n ");
    }
    return 0;
}

int array_rand(int MinePos[][2], int MineNum, int Height, int Width)
{
    unsigned seed = time(NULL);
    srand(seed);
    for(int i = 0; i < MineNum; i++){
        int temp1 = rand() % Height;
        int temp2 = rand() % Width; 
        int j;
        for(j = 0; j < i; j++){
            if (MinePos[i][0] == temp1 && MinePos[i][1] == temp2)
                break;
        }
        if( j < i)
            i--;
        else{
            MinePos[i][0] = temp1;
            MinePos[j][1] = temp2;
        }
    }
    return 0;
}

int game_int(int Height, int Width, int MineField[][Width], int MinePos[][2], int MineNum, Status PlayerStatus)
{
    // init game field
    array2d_init(Height, Width, MineField, PUZZLE);
    //minefield_print(Height, Width, MineField, PlayerStatus);
    // init mine position
    array_rand(MinePos, MineNum, Height, Width);
    //array2d_print(MineNum,2,MinePos);
    return 0;
}

int checkMinPos(int MineNum, int MinePos[][2], int x, int y)
{
    for(int i = 0; i < MineNum; i++){
        if(MinePos[i][0] == x && MinePos[i][1] == y)
            return 0;
    }
    return 1;
}

void minefield_display(int Height, int Width, int MineField[][Width], int MineNum, int MinePos[][2], Status PlayerStatus)
{
    array2d_init(Height, Width, MineField, NOTMINE);
    for( int i = 0; i < MineNum; i++){
        MineField[MinePos[i][0]][MinePos[i][1]] = MINE;
    }
    minefield_print(Height, Width, MineField, PlayerStatus);
}

int minefield_countmine(int Height, int Width, int MineField[][Width], int MineNum, int MinePos[][2],int x, int y)
{
    int counter = 0;
    for(int i = x-1; i <= x+1; i++){
        for(int j = y-1; j <= y+1; j++){
            if( i >= 0 && i < Height && j >= 0 && j < Width ){
                if(checkMinPos(MineNum, MinePos, i, j) == 0)
                    counter ++;
            }
        }
    }
    return counter;
}

void minefield_neighbor(int Height, int Width, int MineField[][Width], int MineNum, int MinePos[][2],int x, int y)
{
    if(MineField[x][y] == NOTMINE){
        int minecount = minefield_countmine(Height, Width, MineField, MineNum, MinePos, x, y);
        MineField[x][y] = minecount;
    }

    /*
    for(int i = x-1; i <= x+1; i++){
        for(int j = y-1; j <= y+1; j++){
            if( i >= 0 && i < Height && j >= 0 && j < Width ){
                if(MineField[i][j] <= PUZZLE){
                    int minecount = minefield_countmine(Height, Width, MineField, MineNum, MinePos, i, j);
                    MineField[i][j] = minecount;
                }
            }
        }
    }*/
}

Status minefield_auto(int Height, int Width, int MineField[][Width], int MineNum, int MinePos[][2],int x, int y, Status PlayerStatus)
{
    if(MineField[x][y] == NOTMINE){
        int minecount = minefield_countmine(Height, Width, MineField, MineNum, MinePos, x, y);
        MineField[x][y] = minecount;
    }
    if(MineField[x][y] == 0){
        for(int i = x-1; i <= x+1; i++){
            for(int j = y-1; j <= y+1; j++){
                if( i >= 0 && i < Height && j >= 0 && j < Width ){
                    if(MineField[i][j] == PUZZLE || MineField[i][j] == FLAG ){
                        PlayerStatus.puzzleleft --;
                        int minecount = minefield_countmine(Height, Width, MineField, MineNum, MinePos, i, j);
                        MineField[i][j] = minecount;
                    }
                }
            }
        }    
    }
    return PlayerStatus;
}

int game_loop(int Height, int Width, int MineField[][Width], int MineNum, int MinePos[][2], Status PlayerStatus, Settings GameSettings)
{
    int game_status = GAME_START;
    int Ctrlx,Ctrly;
    while( game_status != GAME_END){
        minefield_print(Height, Width, MineField, PlayerStatus);
        // read command
        printf("give the axies x,y to test, -1,-1 to quit\n");
        scanf("%d,%d", &Ctrlx, &Ctrly);
        if(Ctrlx < Height && Ctrlx >= 0 && Ctrly < Width && Ctrly >=0 ){
            // test what happened
            if(MineField[Ctrlx][Ctrly] == PUZZLE || MineField[Ctrlx][Ctrly] == FLAG){
                int issafe = checkMinPos(MineNum, MinePos, Ctrlx, Ctrly);
                if(issafe == 1){
                    MineField[Ctrlx][Ctrly] = NOTMINE;
                    PlayerStatus.puzzleleft --;
                    if(GameSettings.automode == 0)
                        minefield_neighbor(Height, Width, MineField, MineNum, MinePos, Ctrlx, Ctrly);
                    else
                        PlayerStatus = minefield_auto(Height, Width, MineField, MineNum, MinePos, Ctrlx, Ctrly, PlayerStatus);
                }
                else{
                    printf("You hit the mine, game over!\n");
                    minefield_display(Height, Width, MineField, MineNum, MinePos, PlayerStatus);
                    return -1;
                }
            }
        }
        else if (Ctrlx == -1 && Ctrly == -1){
            // quit()
            return -1;
        }
        if(PlayerStatus.MineNumleft == PlayerStatus.puzzleleft)
        {
            printf("you win!");
            break;
        }
    }
    return 0;
}

int game(int Height, int Width, int MineNum, Settings GameSettings)
{
    int MineField[Height][Width];
    int MinePos[MineNum][2];
    Status PlayerStatus;
    PlayerStatus.MineNumleft = MineNum;
    PlayerStatus.puzzleleft = Height * Width;
    game_int(Height, Width, MineField, MinePos, MineNum, PlayerStatus);
    game_loop(Height, Width, MineField, MineNum, MinePos, PlayerStatus, GameSettings);
    return 0;
}


int mine(int Level)
{
    int Width, Height, MineNum;
    if (Level == 1){
        Width = 10;
        Height = 10;
        MineNum = 10;
    }
    else if (Level == 2){
        Width = 20;
        Height = 15;
        MineNum = 30;
    }
    else if (Level == 3){
        Width = 30;
        Height = 20;
        MineNum = 50;
    }
    
    int Ctl1;
    Settings GameSettings;
    GameSettings.automode = 0; // close automode
    
    printf("Settings: Width: %d, Height: %d, Mine: %d, automode: %s\n", Width, Height, MineNum, GameSettings.automode == 1?"on":"off");
    printf("Menu:\n1.Start.\n2.Settings.\n3.Main Menu.\n");
    scanf("%d",&Ctl1);
    while(Ctl1 != 3){
        if (Ctl1 == 1){
            game(Height, Width, MineNum, GameSettings);
        }
        else if (Ctl1 == 2){
            // settings
            printf("Choose the settings you want to change:\n1.automode.\n2.back\n");
            int Ctl2 = 2;
            scanf("%d", &Ctl2);
            while (Ctl2 != 2){
                if (Ctl2 == 1){
                    int Ctl3;
                    printf("automode settings:\n1.on.\n2.off\n");
                    scanf("%d", &Ctl3);
                    if(Ctl3 == 1)
                        GameSettings.automode = 1;
                    else if (Ctl3 == 2)
                        GameSettings.automode = 0;
                    else{
                        printf("invalid input\n");
                    }
                }
                printf("Choose the settings you want to change:\n1.automode.\n2.back\n");
                scanf("%d", &Ctl2);
            }
        }
        else if (Ctl1 == 3){
            break;
        }
        else{
            printf("invalid input");
        }
        printf("Settings: Width: %d, Height: %d, Mine: %d, automode: %s\n", Width, Height, MineNum, GameSettings.automode == 1?"on":"off");
        printf("Menu:\n1.Start.\n2.Settings.\n3.Main Menu.\n");
        scanf("%d",&Ctl1);
    }
    // return to last menu
    return 0;
}

int main (int argc, char** argv)
{
    int Level=1;
    printf("(Wellcome to game mine, please select a mode:\nMenu:\n1.small[%d].\n2.medium[%d].\n3.large[%d].\n4.quit[%d]\n", Level == 1?1:0, Level == 2?1:0, Level == 3?1:0, Level == 4?1:0 );
    scanf("%d",&Level);
    while ( Level == 1 || Level == 2 || Level == 3){
        printf("Loading game %d\n",Level);
        mine(Level);
        printf("(Wellcome to game mine, please select a mode:\nMenu:\n1.small[%d].\n2.medium[%d].\n3.large[%d].\n4.quit[%d]\n", Level == 1?1:0, Level == 2?1:0, Level == 3?1:0, Level == 4?1:0 );
        scanf("%d",&Level);
        if(Level == 4 )
            break;
    }

    printf("don't get required Level, Bye!\n");
    return 0;
}
