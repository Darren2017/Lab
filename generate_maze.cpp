#include<iostream>
using namespace std;

short D[200][200] = {0}, Z[200][200] = {0};
int nx[] = {1, 0, -1, 0};
int ny[] = {0, 1, 0, -1};
int M, N;         //M-------高度       N --------------长度  

void generate_maze(int x, int y);
void generate_wall();
void print();
void read();

int main()
{
    read();
    generate_wall();
    generate_maze(rand() % N, rand() % M);
    print();

    return 0;
}

void generate_maze(int x, int y){
    D[x][y] = 1;
    srand(time(0));
    int n = 4, a[6];
    for(int i = 1; i <= 4; i++){
        a[i] = i;
    }
    random_shuffle(a+1,a+n+1);
    for(int i = 0; i < 4; i++){
        int xi = x + nx[a[i + 1] - 1];
        int yi = y + ny[a[i + 1] - 1];
        if(D[xi][yi] == 0 && xi < N && xi >= 0 && yi >= 0 && yi < M){
            int mx = 2 * x + 1, my = 2 * y + 1;
            if(i == 0){
                Z[mx + 1][my] = 0;
            }else if(i == 1){
                Z[mx][my + 1] = 0;
            }else if(i == 2){
                Z[mx - 1][my] = 0;
            }else{
                Z[mx][my - 1] = 0;
            }
            generate_maze(xi, yi);
        }
    }
}

void generate_wall(){
    for(int i = 0; i < 2 * N + 1; i++){
        if(i % 2 == 0){
            for(int j = 0; j < 2 * M + 1; j++){
                Z[i][j] = 1;
            }
        }
    }
    for(int i = 0; i < 2 * M + 1; i++){
        if(i % 2 == 0){
            for(int j = 0; j < 2 * N + 1; j++){
                Z[j][i] = 1;
            }
        }
    }
}

void print(){
    for(int i = 0; i < 2 * N + 1; i++){
        for(int j = 0; j < 2 * M + 1; j++){
            if(Z[i][j]){
                printf("# ");
            }else{
                printf("  ");
            }
        }
        printf("\n");
    }
}

void read(){
    printf("please enter height of maze ");
    scanf("%d", &M);
    printf("please enter longth of maze ");
    scanf("%d", &N);
}