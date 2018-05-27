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
            if(MineField[i][j] < 9 && MineField[i][j] > 0 )
                printf("%d ",MineField[i][j]);
            else{
                if(MineField[i][j] == PUZZLE)
                    printf("- ");
                else if(MineField[i][j] == 0 )
                    printf("  ");
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
    //array2d_init(Height, Width, MineField, NOTMINE);
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

int minefield_countflag(int Height, int Width, int MineField[][Width], int x, int y)
{
    int counter = 0;
    for(int i = x-1; i <= x+1; i++){
        for(int j = y-1; j <= y+1; j++){
            if( i >= 0 && i < Height && j >= 0 && j < Width ){
                if(MineField[i][j] == FLAG)
                    counter ++;
            }
        }
    }
    return counter;
}

int minefield_countpuzzle(int Height, int Width, int MineField[][Width], int x, int y)
{
    int counter = 0;
    for(int i = x-1; i <= x+1; i++){
        for(int j = y-1; j <= y+1; j++){
            if( i >= 0 && i < Height && j >= 0 && j < Width ){
                if(MineField[i][j] == PUZZLE)
                    counter ++;
            }
        }
    }
    return counter;
}

Status minefield_neighbor(int Height, int Width, int MineField[][Width], int MineNum, int MinePos[][2],int x, int y, Status PlayerStatus)
{
    int minecount = minefield_countmine(Height, Width, MineField, MineNum, MinePos, x, y);
    if(MineField[x][y] == PUZZLE)
        PlayerStatus.puzzleleft--;
    MineField[x][y] = minecount;
    return PlayerStatus;
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

Status minefield_helper(int Height, int Width, int MineField[][Width], int MineNum, int MinePos[][2],int x, int y, Status PlayerStatus)
{
    int minecount1 = minefield_countmine(Height, Width, MineField, MineNum, MinePos, x, y);
    if(MineField[x][y] == PUZZLE)
        PlayerStatus.puzzleleft--;
    MineField[x][y] = minecount1;

    if(MineField[x][y] == 0 && minefield_countflag(Height, Width, MineField, x, y) == 0 ){
        for(int i = x-1; i <= x+1; i++){
            for(int j = y-1; j <= y+1; j++){
                if( i >= 0 && i < Height && j >= 0 && j < Width ){
                    if(MineField[i][j] == PUZZLE)
                        PlayerStatus.puzzleleft --;
                    int minecount2 = minefield_countmine(Height, Width, MineField, MineNum, MinePos, i, j);
                    MineField[i][j] = minecount2;
                }
            }
        }    
    }
    return PlayerStatus;
}

Status minefield_auto(int Height, int Width, int MineField[][Width], int MineNum, int MinePos[][2],int x, int y, Status PlayerStatus)
{
    if(MineField[x][y] == PUZZLE)
        PlayerStatus.puzzleleft--;
    else{
        return PlayerStatus;
    }
    int minecount1 = minefield_countmine(Height, Width, MineField, MineNum, MinePos, x, y);
    MineField[x][y] = minecount1;

    int fcnt = minefield_countflag(Height, Width, MineField, x, y);
    int pcnt = minefield_countpuzzle(Height, Width, MineField, x, y);
    //printf("(%d,%d) Pc:%d Fc:%d\n",x,y,pcnt,fcnt);

    if(MineField[x][y] == 0 && fcnt == 0 && pcnt != 0){
        for(int i = x-1; i <= x+1; i++){
            for(int j = y-1; j <= y+1; j++){
                if( i >= 0 && i < Height && j >= 0 && j < Width && (i != x || j != y)){
                    PlayerStatus = minefield_auto(Height, Width, MineField, MineNum, MinePos, i, j, PlayerStatus);
                }
            }
        }    
    }
    return PlayerStatus;
}

Status minefield_solver(int Height, int Width, int MineField[][Width], int MineNum, int MinePos[][2],int x, int y, Status PlayerStatus)
{
    if(MineField[x][y] == PUZZLE)
        PlayerStatus.puzzleleft--;
    else{
        return PlayerStatus;
    }
    int minecount1 = minefield_countmine(Height, Width, MineField, MineNum, MinePos, x, y);
    MineField[x][y] = minecount1;

    int fcnt = minefield_countflag(Height, Width, MineField, x, y);
    int pcnt = minefield_countpuzzle(Height, Width, MineField, x, y);
    //printf("(%d,%d) Pc:%d Fc:%d\n",x,y,pcnt,fcnt);

    if(MineField[x][y] == 0 && fcnt == 0 && pcnt != 0){
        for(int i = x-1; i <= x+1; i++){
            for(int j = y-1; j <= y+1; j++){
                if( i >= 0 && i < Height && j >= 0 && j < Width && (i != x || j != y)){
                    PlayerStatus = minefield_solver(Height, Width, MineField, MineNum, MinePos, i, j, PlayerStatus);
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
    char Ctrlz;
    while( game_status != GAME_END){
        minefield_print(Height, Width, MineField, PlayerStatus);
        // read command
        printf("give the axies x,y,U to open, x,y,F to flag or unflag, x,y,Q to quit\n");
        scanf("%d,%d,%c", &Ctrlx, &Ctrly, &Ctrlz);
        if (Ctrlz == 'Q'){
            // quit
            return -1;
        }
        else{
            if(Ctrlx < Height && Ctrlx >= 0 && Ctrly < Width && Ctrly >=0 ){
                // test what happened
                if(Ctrlz == 'U'){
                    if(MineField[Ctrlx][Ctrly] != FLAG){
                        int issafe = checkMinPos(MineNum, MinePos, Ctrlx, Ctrly);
                        if(issafe == 1){
                            // MineField[Ctrlx][Ctrly] = NOTMINE;
                            // PlayerStatus.puzzleleft --;
                            if(GameSettings.automode == 1)
                                PlayerStatus = minefield_neighbor(Height, Width, MineField, MineNum, MinePos, Ctrlx, Ctrly, PlayerStatus);
                            else if(GameSettings.automode == 2)
                                PlayerStatus = minefield_helper(Height, Width, MineField, MineNum, MinePos, Ctrlx, Ctrly, PlayerStatus);
                            else if(GameSettings.automode == 3)
                                PlayerStatus = minefield_auto(Height, Width, MineField, MineNum, MinePos, Ctrlx, Ctrly, PlayerStatus);
                            else{
                                PlayerStatus = minefield_solver(Height, Width, MineField, MineNum, MinePos, Ctrlx, Ctrly, PlayerStatus);
                            }
                        }
                        else{
                            printf("You hit the mine, game over!\n");
                            minefield_display(Height, Width, MineField, MineNum, MinePos, PlayerStatus);
                            return -1;
                        }
                    }
                    else{
                        printf("Flag here, remove it first\n");
                    }
                }
                else if(Ctrlz == 'F'){
                    if(MineField[Ctrlx][Ctrly] == PUZZLE){
                        PlayerStatus.MineNumleft --;
                        PlayerStatus.puzzleleft --;
                        MineField[Ctrlx][Ctrly] = FLAG;
                    }
                    else if(MineField[Ctrlx][Ctrly] == FLAG){
                        PlayerStatus.MineNumleft ++;
                        PlayerStatus.puzzleleft ++;
                        MineField[Ctrlx][Ctrly] = PUZZLE;
                    }
                    else{
                        printf("no flag operation.\n");
                    }
                }
                else{
                    printf("no other choices yet.\n");
                }
            }
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
    GameSettings.automode = 3; // automode
    
    printf("Settings: Width: %d, Height: %d, Mine: %d, automode: %d\n", Width, Height, MineNum, GameSettings.automode);
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
                    printf("automode settings:\n1.no auto.\n2.helper expand\n3.auto expand.\n4.solver\n");
                    scanf("%d", &Ctl3);
                    if(Ctl3 < 5 && Ctl3 > 0)
                        GameSettings.automode = Ctl3;
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
        printf("Settings: Width: %d, Height: %d, Mine: %d, automode: %d\n", Width, Height, MineNum, GameSettings.automode);
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
