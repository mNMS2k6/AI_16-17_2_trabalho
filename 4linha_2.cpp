#include <stdlib.h>
#include <iostream>
#include <climits>

using namespace std;

#define player_pc 'x'
#define player_h 'o'

char board[6][7] =
{
    {'x', 'x', 'x', 'o', 'o', 'x', 'o'},
    {'x', 'o', 'x', 'o', 'x', 'o', 'x'},
    {'o', 'o', 'o', 'x', 'o', 'o', 'x'},
    {'x', 'x', 'o', 'x', 'o', 'x', 'o'},
    {'x', 'o', 'o', 'x', 'o', 'x', 'o'},
    {'x', 'o', 'x', 'o', 'x', 'o', 'x'}
};

int posso_jogar(char mat[][7], int c);

void jogada_h()
{
    int coluna;
    cout << "Qual é a coluna onde quer jogar? (1-7)" << endl;
    cin >> coluna;
    if(!((coluna-1>=0) && (coluna-1<=6)))
    {
        cout << "Posicao Invalida" << endl;
        jogada_h();
    }
    else if (posso_jogar(board, coluna-1) != -1)
    {
        int linha = posso_jogar(board, coluna-1);
        board[linha][coluna-1] = player_h;
    }
    else
    {
        cout << "Posicao Invalida" << endl;
        jogada_h();   
    }
}

void print(char mat[][7])
{
    for (int i=0; i<6; i++)
    {
        for (int j=0; j<7; j++)
        {
            cout << mat[i][j] << "| ";
        }
        cout << endl;
    }
}

int is_Solution(char mat[][7], char key)
{
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
    char turn;
    if(key == player_pc)
        turn = player_h;
    else
        turn = player_pc;

    if(is_Solution(mat,turn) == 1)
        return -1;
    else
        return -2;
}

int posso_jogar(char mat[][7], int c)
{
    int linha = 5;
    while( (mat[linha][c] == 'x' || mat[linha][c] == 'o') && linha >=0)
    {
        linha--;
    }

    if(linha <0)
        return -1;
    else
        return linha;
}


void move(char mat2[][7], char player, int c)
{
    if(posso_jogar(mat2, c) != -1)
    {
        int k = posso_jogar(mat2, c);
        mat2[k][c] = player;
    }
}

int max_v(char mat[][7], char player);
int min_v(char mat[][7], char player);

int min_max(char mat[][7])
{
    int tmp=INT_MAX, v, save_i;

    for (int i=0; i<7; i++)
    {
        if(posso_jogar(mat, i) != -1)
        {
            if (v < tmp)
            {
                tmp = v;
                save_i = i;
            }
            v = min_v(mat, player_h);
        }
    }
    return save_i;
}

int max_v(char mat[][7], char player)
{
    int v;
    if ( (v = is_Solution(mat, player)) != -2)
    {
        return v;
    }
    else
    {
        v = INT_MIN;
        for (int i=0; i<7; i++)
        {
            char mat2[6][7];
            move(mat, player, i);

            char turn;
            if(player == player_pc)
                turn = player_h;
            else
                turn = player_pc;

            v = max(v,min_v(mat2, turn));
        }
    }    
}

int min_v(char mat[][7], char player)
{
    int v;
    if ( (v = is_Solution(mat, player)) != -2)
    {
        return v;
    }
    else
    {
        v = INT_MAX;
        for (int i=0; i<7; i++)
        {
            char mat2[6][7];
            move(mat, player, i);

            char turn;
            if(player == player_pc)
                turn = player_h;
            else
                turn = player_pc;

            v = min(v,max_v(mat2, turn));
        }
    }
}



int main(){
     //jogada_h();
       cout << "onde o pc joga: " << min_max(board) << endl;
    print(board);
}