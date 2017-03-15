#include <stdlib.h>
#include <iostream>

using namespace std;

#define player_pc 'x'
#define player_h 'o'

char board[6][7] =
{
    { 'x', 'o', 'x', 'o', 'o', 'x', 'o'},
    { 'x', 'o', 'x', 'o', 'x', 'o', 'x'},
    { 'o', 'x', 'o', 'x', 'o', 'o', 'x'},
    { 'x', 'x', 'o', 'x', 'o', 'x', 'o'},
    { 'x', 'o', 'o', 'x', 'o', 'x', 'o'},
    { 'x', 'o', 'x', 'o', 'x', 'o', 'x'}
};

void jogada_possivel(int coluna, char player)
{
    int linha =5;
    while( (board[linha][coluna] == 'x' || board[linha][coluna] == 'o') && linha >=0 )
    {
        linha--;
    }
    board[linha][coluna] = player;
}

void jogadax2()
{
    int coluna = 0;
    cout << " dá posição coluna entre 0-6 (inclusive) onde jogar " << endl;
    cin >> coluna;
    if(coluna < 0 || coluna >7)
    {
        cout << " posição invalida " << endl;
        return ;
    }
    jogada_possivel(coluna, player_pc);
}

void print()
{
    for (int i=0; i<6; i++)
    {
        for (int j=0; j<7; j++)
        {
            cout << board[i][j];
        }
        cout << endl;
    }
}
int is_Solution(char mat[][7], char key){
    
    int count = 0;
    
    //linha
    for (int i=0; i<4; i++) {
        for (int j = 5; j>=0; j--) {
            if(mat[j][i] == mat[j][i+1] && mat[j][i] == key){
                count = 0;
                for (int k = i; k<7; k++) {
                    if(mat[j][k] == mat[j][k+1] && mat[j][k] == key)
                    {
                        count++;
                    }
                    if(count == 3 )
                    {
                        return 1;
                    }
                }
            }
            
        }
    }
    
    //coluna
    for (int i= 5; i>2; i--) {
        
        for (int j = 0; j<7; j++) {
            if(mat[i][j] == mat[i-1][j] && mat[i][j] == key){
                count = 0;
                for (int k = i; k>=0; k--) {
                    if(mat[k][j] == mat[k-1][j] && mat[k][j] == key)
                    {
                        count++;
                    }
                    if(count == 3 )
                    {
                        return 1;
                    }
                }
            }
        }
    }
    
    //diagonais y=x
    for (int i=5; i>3; i--) {
        for (int j=3; j>=0; j--) {
            if(mat[i][j]== mat[i-1][j+1] && mat[i][j] == key)
            {
                int z = i;
                count = 0;
                for (int k=j; k<5; k++) {
                    if(mat[z][k]== mat[z-1][k+1] && mat[z][k] == key && z>=0){
                        count ++;
                        z--;
                    }
                    if(count == 3){
                        return 1;
                    }
                }
            }
        }
    }
    
    // diagonais y=-x
    for (int i=5; i>2; i--) {
        for (int j=6; j>=0; j--) {
            if(mat[i][j]== mat[i-1][j-1] && mat[i][j] == key)
            {
                int z = i;
                count = 0;
                for (int k=j; k>=0; k--) {
                    if(mat[z][k]== mat[z-1][k-1] && mat[z][k] == key && z>=0){
                        count ++;
                        z--;
                    }
                    if(count == 3){
                        return 1;
                    }
                }
            }
        }
    }
    
    //ver se existe empate
    count =0;
    for (int i=0; i<6; i++)
    {
        for(int j=0;j<7; j++)
        {
            if(mat[i][j] == 'x' || mat[i][j] == 'o')
            {
                count++;
            }
        }
    }
    if(count == (7*6))
    {
        return 0;
    }
    
    //senao retorna derrota
    return -1;
}

int Min_Max(char mat[][7])
{
    if(is_Solution(mat,'x') != 0){
        
    }
}

int main(){
        jogadax2();
        print();
}