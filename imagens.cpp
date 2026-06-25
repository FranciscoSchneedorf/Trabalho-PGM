#include <iostream>
#include <fstream>
#include <algorithm>
#include "imagens.h"

using namespace std;

int carregaPGM(string nome, tImagem img, int *col, int *lin, int *tons)
{
    // Variaveis
    string tipo;

    ifstream arquivo(nome); // Abertura do arquivo

    // Verificacoes
    if (!arquivo.is_open())
    {
        return 1;
    }

    arquivo >> tipo;

    if (tipo != "P2")
    {
        cout << "ERRO: Arquivo nao tem formato P2." << endl;
        return 1;
    }

    // Leitura do arquivo
    arquivo >> *col >> *lin >> *tons;
    for (int *p = &img[0][0]; *p < &img[0][0] + (*lin) * (*col); p++)
    {
        arquivo >> *p;
    }

    arquivo.close();

    return 0;
}

int salvaPGM(string nome, tImagem img, int col, int lin, int tons)
{
    // Criando o arquivo
    ofstream arquivo(nome);

    // Verificacao
    if (!arquivo.is_open())
    {
        cout << "ERRO: Nao foi possivel salvar o arquivo. " << endl;
        return 1;
    }

    // Escrevendo o cabecalho
    arquivo << "P2" << endl
            << col << " " << lin << endl
            << tons << endl;

    // Salvando o arquivo
for (int *p = &img[0][0]; *p < &img[0][0] + (*lin) * (*col); p++)
    {
            arquivo << *P << " ";
        arquivo << endl;
    }

    arquivo.close();

    return 0;
}

int clarear_escurecerPGM(tImagem img, int col, int lin, int valor, int tons)
{
    // Clareando a imagem
    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++)
        {
            img[i][j] = max(0, min(img[i][j] + valor, tons)); // Compara os valores e min escolhe o menor, impedindo de ultrapassar. Max escolhe sempre 0 se o valor for menor que 0
        }
    }

    return 0;
}

int binPGM(tImagem img, int col, int lin, int tons, int limiar)
{
    // Laco para percorrer o arquivo-texto linha a linha pelos pixels
    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (img[i][j] > limiar) // Verificando se o tom em determinada posicao ij e maior do que o limiar dado pelo usuario.
            {
                img[i][j] = tons;
            }
            else // Se o tom naquela posicao for menor igual ao limiar, vira 0
            {
                img[i][j] = 0;
            }
        }
    }

    return 0;
}

int esquerdaPGM(tImagem img, int *lin, int *col)
{
    // Variaveis
    static tImagem aux; // Criando uma matriz auxiliar para fazer a copia e nao perder os pixels nas posicoes originais durante a rotacao
    int lin_original = *lin;
    int col_original = *col;

    // Laco para inverter pixel a pixel
    for (int i = 0; i < *lin; i++)
    {
        for (int j = 0; j < *col; j++)
        {
            aux[col_original - 1 - j][i] = img[i][j]; // Coluna 0 vira linha 0, porem invertida.
        }
    }

    // Atualizando o tamanho da imagem pos-rotacao
    *lin = col_original;
    *col = lin_original;

    // Laco para passar a matriz rotacionada para a imagem original
    for (int i = 0; i < *lin; i++)
    {
        for (int j = 0; j < *col; j++)
        {
            img[i][j] = aux[i][j];
        }
    }

    return 0;
}

int direitaPGM(tImagem img, int *lin, int *col)
{
    // Variaveis
    static tImagem aux; // Criando uma matriz auxiliar para fazer a copia e nao perder os pixels nas posicoes originais durante a rotacao
    int lin_original = *lin;
    int col_original = *col;

    // Laco para inverter pixel a pixel
    for (int i = 0; i < *lin; i++)
    {
        for (int j = 0; j < *col; j++) //
        {
            aux[j][lin_original - 1 - i] = img[i][j]; // Linha 0 vira a ultima coluna, porem invertida
        }
    }

    // Atualizando o tamanho da imagem pos-rotacao
    *lin = col_original;
    *col = lin_original;

    // Laco para passar a matriz rotacionada para a imagem original
    for (int i = 0; i < *lin; i++)
    {
        for (int j = 0; j < *col; j++)
        {
            img[i][j] = aux[i][j];
        }
    }

    return 0;
}

int verticalPGM(tImagem img, int lin, int col)
{
    // Variaveis
    static tImagem aux; // Criando uma matriz auxiliar para fazer a copia e nao perder os pixels nas posicoes originais durante a rotacao
    int lin_original = lin;
    int col_original = col;

    // Laco para inverter pixel a pixel
    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++) //
        {
            aux[lin_original - 1 - i][j] = img[i][j]; // Linha inverte, coluna permanece igual
        }
    }

    // Atualizando o tamanho da imagem pos-rotacao
    lin = lin_original;
    col = col_original;

    // Laco para passar a matriz rotacionada para a imagem original
    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++)
        {
            img[i][j] = aux[i][j];
        }
    }

    return 0;
}

int horizontalPGM(tImagem img, int lin, int col)
{
    // Variaveis
    static tImagem aux; // Criando uma matriz auxiliar para fazer a copia e nao perder os pixels nas posicoes originais durante a rotacao
    int lin_original = lin;
    int col_original = col;

    // Laco para inverter pixel a pixel
    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++) //
        {
            aux[i][col_original - 1 - j] = img[i][j]; // Coluna inverte, linha permanece igual
        }
    }

    // Atualizando o tamanho da imagem pos-rotacao
    lin = lin_original;
    col = col_original;

    // Laco para passar a matriz rotacionada para a imagem original
    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++)
        {
            img[i][j] = aux[i][j];
        }
    }

    return 0;
}

int negativoPGM(tImagem img, int lin, int col, int tons)
{
    // Laco para passar por todos os pixel da matriz
    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++)
        {
            img[i][j] = tons - img[i][j]; // Subtrai-se de 255 o valor do pixel atual. Se for 0, 255 - 0 = 255. Logo, o pixel que era preto vira brnaco, e vice-versa
        }
    }

    return 0;
}

int passabaixaPGM(tImagem img, int lin, int col)
{
    // Variaveis
    int soma = 0;
    static tImagem aux;

    // Laco para copiar a matriz original para aux, para nao altera-la durante os lacos
    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++)
        {
            aux[i][j] = img[i][j];
        }
    }

    // Laco para passar por todos os pixels da imagem, comecando em 1 para linhas e colunas para nao contabilizar as bordas
    for (int i = 1; i < lin - 1; i++)
    {
        for (int j = 1; j < col - 1; j++)
        {
            soma = 0; // Soma zerada a cada pixel

            for (int a = -1; a <= 1; a++) // Laco para encontrar os vizinhos do pixel central
            {
                for (int b = -1; b <= 1; b++)
                {
                    soma = soma + img[i + a][j + b]; // a e b variam de -1 a 1 para acessar os vizinhos
                }
            }

            aux[i][j] = soma / 9; // Alterando o pixel central
        }
    }

    // Laco para copiar a imagem filtrada para a original
    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++)
        {
            img[i][j] = aux[i][j];
        }
    }

    return 0;
}

int escurecerbordaPGM(tImagem img, int lin, int col, int fator, int decremento)
{
    // Variavies
    int camada = 0;
    int fator_atual = 0;

    // Laco para percorrer pixel a pixel, decrescendo de acordo com o fator e a camada em que se encontra
    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++)
        {
            camada = min(min(i, j), min(lin - 1 - i, col - 1 - j)); // Calculando a menor distancia entre o pixel e as bordas; A menor distancia indica em que camada o pixel esta

            fator_atual = fator - (camada * decremento);

            // Se o fator ficar negativo, nao escurece mais
            if (fator_atual < 0)
            {
                fator_atual = 0;
            }

            img[i][j] = max(0, img[i][j] - fator_atual); // Escurece o pixel, sem deixar ficar abaixo de 0
        }
    }

    return 0;
}
