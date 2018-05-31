#include<iostream>
using namespace std;
#define N 5

int maze[N][N] = {
    {1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1},
    {0, 1, 0, 0, 1},
    {1, 0, 0, 1, 1},
    {0, 1, 1, 1, 1}
};

int pace[N][N] = {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
};

bool Maze(int x, int y);
void print();
bool isSafe(int x, int y);

int main()
{
    Maze(0, 0);
    return 0;
}

bool Maze(int x, int y){
    if(x == N -1 && y == N - 1){
        pace[x][y] = 1;
        print();
        return true;
    }
    if(isSafe(x, y) == true){
        pace[x][y] = 1;
        if(Maze(x + 1, y) == true){
            return true;
        }
        if(Maze(x, y + 1) == true){
            return true;
        }
    }
    pace[x][y] = 0;

    return false;
}

void print(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%-3d", pace[i][j]);
        }
        printf("\n");
    }
}

bool isSafe(int x, int y)
{
    if(x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1){
        return true;
    }
    return false;
}