#include <stdlib.h>
#include <iostream>
#include <climits>
#include <cmath>

using namespace std;

#define player_pc 'x'
#define player_h 'o'

int terminou = 0;

char board[6][7] =
{
    {'-', '-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-', '-'}
};

void jogada_h();
void jogadapc();
void print(char mat[][7]);
int pontos(char mat[][7], char key);
int posso_jogar(char mat[][7], int c);
char move(char mat1[][7], char mat2[][7], char player, int c);
int min_v(char mat[][7], char player, int prof);
int max_v(char mat[][7], char player, int prof);
bool terminal(char mat[][7]);
void primeiro_h();
void primeiro_pc();
void inicia_minmax();

void jogada_h()
{
    int coluna;

    cout << "1| 2| 3| 4| 5| 6| 7" << endl;
    print(board);
    cout << "Joga (1-7): ";
    cin >> coluna;
    cout << endl;
    if (!((coluna - 1 >= 0) && (coluna - 1 <= 6)))
    {
        cout << "Posicao Invalida" << endl;
        jogada_h();
    }
    else if (posso_jogar(board, coluna - 1) != -1)
    {
        int linha = posso_jogar(board, coluna - 1);
        board[linha][coluna - 1] = player_h;
    }
    else
    {
        cout << "Posicao Invalida" << endl;
        jogada_h();
    }
}

void jogada_pc(int col)
{
    if (posso_jogar(board, col) != -1)
    {
        int linha = posso_jogar(board, col);
        board[linha][col] = player_pc;
    }
}

void print(char mat[][7])
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            cout << mat[i][j] << "| ";
        }
        cout << endl;
    }
}

int pontos(char mat[][7], char key)
{
    char opnt;
    if (key == player_pc)
        opnt = player_h;
    else
        opnt = player_pc;

    int pontos = 0;

    if (key == player_pc)
    {
        pontos = 16;
    }
    else
    {
        pontos = -16;
    }


    //pontos para as colunas
    for (int j = 0; j < 7; j++)
    {
        for (int i = 5; i > 2; i--)
        {
            if (mat[i][j] != opnt)
            {
                int count = 0;
                int k = i;
                while (k >= i - 4)
                {
                    if (mat[k][j] == key)
                    {
                        count++;
                    }
                    else if (mat[k][j] == opnt)
                    {
                        count = 0;
                        break;
                    }
                    k--;
                }
                if (key == player_pc)
                {
                    if (count == 1)
                    {
                        pontos += 1;
                    }
                    else if (count == 2)
                    {
                        pontos += 10;
                    }
                    else if (count == 3)
                    {
                        pontos += 50;
                    }
                    else if (count == 4)
                    {
                        return 512;
                    }
                }
                else
                {
                    if (count == 1)
                    {
                        pontos -= 1;
                    }
                    else if (count == 2)
                    {
                        pontos -= 10;
                    }
                    else if (count == 3)
                    {
                        pontos -= 50;
                    }
                    else if (count == 4)
                    {
                        return -512;
                    }

                }
            }

        }
    }

    //pontos para as linhas
    for (int i = 5; i >= 0; i--)
    {
        for (int j = 0; j < 4; j++)
        {
            if (mat[i][j] != opnt)
            {
                int count = 0;
                int k = j;

                while (k < j + 4)
                {
                    if (mat[i][k] == key)
                    {
                        count++;
                    }
                    else if (mat[i][k] == opnt)
                    {
                        count = 0;
                        break;
                    }
                    k++;
                }
                if (key == player_pc)
                {
                    if (count == 1)
                    {
                        pontos += 1;
                    }
                    else if (count == 2)
                    {
                        pontos += 10;
                    }
                    else if (count == 3)
                    {
                        pontos += 50;
                    }
                    else if (count == 4)
                    {
                        return 512;
                    }
                }
                else
                {
                    if (count == 1)
                    {
                        pontos -= 1;
                    }
                    else if (count == 2)
                    {
                        pontos -= 10;
                    }
                    else if (count == 3)
                    {
                        pontos -= 50;
                    }
                    else if (count == 4)
                    {
                        return -512;
                    }
                }
            }
        }
    }

    //verificar diagonal y=x
    for (int i = 5; i > 2; i--)
    {
        for (int j = 0; j < 4; j++)
        {
            if (mat[i][j] != opnt)
            {
                int count = 0;
                int k = 0;
                while (k < 4)
                {
                    if (mat[i - k][j + k] == key)
                    {
                        count++;
                    }
                    else if (mat[i - k][j + k] == opnt)
                    {
                        count = 0;
                        break;
                    }
                    k++;
                }
                if (key == player_pc)
                {
                    if (count == 1)
                    {
                        pontos += 1;
                    }
                    else if (count == 2)
                    {
                        pontos += 10;
                    }
                    else if (count == 3)
                    {
                        pontos += 50;
                    }
                    else if (count == 4)
                    {
                        return 512;
                    }
                }
                else
                {
                    if (count == 1)
                    {
                        pontos -= 1;
                    }
                    else if (count == 2)
                    {
                        pontos -= 10;
                    }
                    else if (count == 3)
                    {
                        pontos -= 50;
                    }
                    else if (count == 4)
                    {
                        return -512;
                    }
                }
            }
        }
    }


    //verificar diagonal y=-x
    for (int i = 5; i > 2; i--)
    {
        for (int j = 3; j < 7; j++)
        {
            if (mat[i][j] != opnt)
            {
                int count = 0;
                int k = 0;
                while (k < 4)
                {
                    if (mat[i - k][j - k] == key)
                    {
                        count++;
                    }
                    else if (mat[i - k][j - k] == opnt)
                    {
                        count = 0;
                        break;
                    }
                    k++;
                }
                if (key == player_pc)
                {
                    if (count == 1)
                    {
                        pontos += 1;
                    }
                    else if (count == 2)
                    {
                        pontos += 10;
                    }
                    else if (count == 3)
                    {
                        pontos += 50;
                    }
                    else if (count == 4)
                    {
                        return 512;
                    }
                }
                else
                {
                    if (count == 1)
                    {
                        pontos -= 1;
                    }
                    else if (count == 2)
                    {
                        pontos -= 10;
                    }
                    else if (count == 3)
                    {
                        pontos -= 50;
                    }
                    else if (count == 4)
                    {
                        return -512;
                    }
                }
            }
        }
    }

    return pontos;
}

int posso_jogar(char mat[][7], int c)
{
    int linha = 5;
    while ( (mat[linha][c] == 'x' || mat[linha][c] == 'o') && linha >= 0)
    {
        linha--;
    }

    if (linha < 0)
        return -1;
    else
        return linha;
}


char move(char mat1[][7], char mat2[][7], char player, int c)
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            mat2[i][j] = mat1[i][j];
        }
    }

    if (posso_jogar(mat2, c) != -1)
    {
        int k = posso_jogar(mat2, c);
        mat2[k][c] = player;
    }
}


int min_v(char mat[][7], char player, int prof)
{
    int v;
    if (terminal(mat) || prof == 0)
    {
        return pontos(mat, player);
    }
    else
    {
        v= INT_MAX;
        for(int j=0; j<7; j++)
        {
            char newmat[6][7];
            move(mat, newmat, player_pc, j);
            v = min(v, max_v(newmat, player_pc, prof-1));
        }
    }
    return v;
}

int max_v(char mat[][7], char player, int prof)
{
    int v;
    if (terminal(mat) || prof == 0)
    {
        return pontos(mat, player);
    }
    else
    {
        v= INT_MIN;
        for(int j=0; j<7; j++)
        {
            char newmat[6][7];
            move(mat, newmat, player_h, j);
            v = max(v, min_v(newmat, player_h, prof-1));
        }
    }
    return v;
}

int minmax(char mat[][7], char player)
{

    int val = INT_MIN, val_tmp, col;

    for (int j=0; j<7; j++)
    {
        if(posso_jogar(board, j) != -1)
        {
            char newmat[6][7];
            move(board, newmat, player_pc, j);

            val_tmp = max_v(newmat, player_pc, 5);
            if (val_tmp > val)
            {
                col = j;
                val = val_tmp;

            }
        }
    }
    return col;
}

bool terminal(char mat[][7])
{

    if (pontos(mat, player_pc) == 512 || pontos(mat, player_h) == -512)
    {
        return true;
    }
    //ver se existe empate
    int count = 0;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (mat[i][j] == 'x' || mat[i][j] == 'o')
            {
                count++;
            }
        }
    }
    if (count == (7 * 6))
    {
        return true;
    }
    else
        return false;
}

void primeiro_h()
{
    while (1)
    {
        if (!terminal(board))
        {

            jogada_h();
            if (pontos(board, player_h) == -512)
            {
                cout << "Ganhou" << endl;
                print(board);
                break;
            }


            cout << "##### PC A JOGAR #####" << endl;  
            int col = minmax(board, player_pc);
            jogada_pc(col);

            if (pontos(board, player_pc) == 512)
            {
                cout << "Perdeu" << endl;
                print(board);
                break;
            }
            cout << "PC jogou na: " << col+1 << endl << endl;

        }
        else
        {
            cout << "Empatou" << endl;
            break;
        }
    }
}

void primeiro_pc()
{
    while (1)
    {
        if (!terminal(board))
        {


            cout << "##### PC A JOGAR #####" << endl;  
            int col = minmax(board, player_pc);
            jogada_pc(col);

            if (pontos(board, player_pc) == 512)
            {
                cout << "Perdeu" << endl;
                print(board);
                break;
            }
            cout << "PC jogou na: " << col+1 << endl << endl;

            jogada_h();
            if (pontos(board, player_h) == -512)
            {
                cout << "Ganhou" << endl;
                print(board);
                break;
            }

        }
        else
        {
            cout << "Empatou" << endl;
            break;
        }
    }
}

void inicia_minmax()
{
    int player;

    cout << "Quem começa?" << endl << "1-EU" << endl << "2-PC" << endl << "Res:";
    cin >> player;
    cout << endl;
    
    if (player == 1)
        primeiro_h();
    else if(player == 2)
        primeiro_pc();
    else
    {
        cout << "Jogador inválido" << endl; 
        inicia_minmax();
        return;
    }
}

int main()
{
    inicia_minmax();
}