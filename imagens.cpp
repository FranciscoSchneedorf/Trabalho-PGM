#include <iostream>
#include <fstream>
#include <algorithm>
#include "imagens.h"

using namespace std;


int lerInteiro(string mensagem)
{
    int valor = 0;
    cout << mensagem;
    cin >> valor;

    while (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "ERRO: Entrada invalida. Digite um numero: " << endl;
        cin >> valor;
    }

    return valor;
}


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
    for (int *p = &img[0][0]; p < &img[0][0] + (*lin) * (*col); p++)
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
    for (int *p = &img[0][0]; p < &img[0][0] + lin * col; p++)
    {
        arquivo << *p << " ";
    }

    arquivo.close();

    return 0;
}

int clarear_escurecerPGM(tImagem img, int col, int lin, int valor, int tons)
{
    // Clareando a imagem
    for (int *p = &img[0][0]; p < &img[0][0] + lin * col; p++)
    {
        *p = max(0, min(*p + valor, tons)); // Compara os valores e min escolhe o menor, impedindo de ultrapassar. Max escolhe sempre 0 se o valor for menor que 0
    }

    return 0;
}

int binPGM(tImagem img, int col, int lin, int tons, int limiar)
{
    // Laco para percorrer o arquivo-texto linha a linha pelos pixels
    for (int *p = &img[0][0]; p < &img[0][0] + lin * col; p++)
    {
        if (*p > limiar) // Verificando se o tom em determinada posicao ij e maior do que o limiar dado pelo usuario.
        {
            *p = tons;
        }
        else // Se o tom naquela posicao for menor igual ao limiar, vira 0
        {
            *p = 0;
        }
    }

    return 0;
}

int esquerdaPGM(tImagem img, int *lin, int *col)
{
    // Variaveis
    static tImagem aux;      // Criando uma matriz auxiliar para fazer a copia e nao perder os pixels nas posicoes originais durante a rotacao
    int lin_original = *lin; // Guardando os valores originais
    int col_original = *col;
    int *pOrigem = &img[0][0]; // Ponteiro que aponta para o primeiro pixel da imagem
    int total = (*lin) * (*col);

    /*------ MONTANDO AUX ------*/
    // Laco para percorrer as linhas
    for (int i = 0; i < lin_original; i++)
    {
        int *pDestino = &aux[0][0]; // Criando ponteiro para a imagem auxiliar

        // Laco para colocar o ponteiro na ultima linha da imagem nova
        for (int k = 0; k < col_original - 1; k++)
        {
            pDestino += lin_original; // Desce uma linha na imagem auxiliar compactada
        }

        // Laco para andar para a direita ate a coluna i da imagem nova
        for (int k = 0; k < i; k++)
        {
            pDestino++;
        }

        // Laco para percorrer as colunas da linha original
        for (int j = 0; j < col_original; j++)
        {
            *pDestino = *pOrigem; // Copiando o pixel da imagem original para o local onde o pDestino aponta

            pOrigem++; // Depois de copiar o pixel atual, o ponteiro original passa para o proximo pixel

            // Verificando se ainda ha pixels para copiar
            if (j < col_original - 1)
            {
                pDestino -= lin_original; // Sobe uma linha em aux
            }
        }
    }

    /*------ COPIANDO AUX PARA IMG ORIGINAL ------*/
    // Atualizando dimensoes
    *lin = col_original;
    *col = lin_original;

    // Preparando para copiar aux de volta para img
    int *pAux = &aux[0][0]; // Aponta para o começo de aux
    int *pImg = &img[0][0]; // Aponta para o começo de img

    for (int i = 0; i < total; i++)
    {
        *pImg = *pAux; // Copiando o pixel de aux para img

        // Avançando os ponteiros
        pImg++;
        pAux++;
    }

    return 0;
}

int direitaPGM(tImagem img, int *lin, int *col)
{
    // Variaveis
    static tImagem aux; // Criando uma matriz auxiliar para fazer a copia e nao perder os pixels nas posicoes originais durante a rotacao
    int lin_original = *lin;
    int col_original = *col;
    int *pOrigem = &img[0][0];
    int total = (*lin) * (*col);

    /*------ MONTANDO AUX ------*/
    // Laco para percores as linhas da imagem original
    for (int i = 0; i < lin_original; i++)
    {
        int *pDestino = &aux[0][0]; // Ponteiro que aponta para o primeiro pixel da imagem auxiliar

        // Laco para colocar o ponteiro na posição correta (coluna da direita)
        for (int k = 0; k < lin_original - 1 - i; k++)
        {
            pDestino++;
        }

        // laco para percorrer as colunas da imagem original
        for (int j = 0; j < col_original; j++)
        {
            *pDestino = *pOrigem; // Realocando os pixels

            pOrigem++; // Avançando os pixels na matriz aux

            // Se ainda houver pixels para copiar, desce uma linha em aux
            if (j < col_original - 1)
            {
                pDestino += lin_original;
            }
        }
    }

    /*------ COPIANDO AUX PARA IMG ORIGINAL ------*/
    // Atualizando dimensoes
    *lin = col_original;
    *col = lin_original;

    // Preparando para copiar aux de volta para img

    int *pAux = &aux[0][0]; // Aponta para o começo de aux
    int *pImg = &img[0][0]; // Aponta para o começo de img

    for (int i = 0; i < total; i++)
    {
        *pImg = *pAux; // Copiando o pixel de aux para img

        // Avançando os ponteiros
        pImg++;
        pAux++;
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

int redimensionamentoPGM(tImagem img, int *lin, int *col)
{
    // Variaveis
    static tImagem aux; // Criando uma matriz auxiliar para fazer a copia e nao perder os pixels nas posicoes originais durante a rotacao
    int lin_original = *lin;
    int col_original = *col;
    int fator, modo;    

    // Entrada de dados
    cout << "Informe o fator de redimensionamento: " << endl;
    cin >> fator;
    cout << "Informe o modo desejado" << endl;
    cout << "[1] Ampliacao" << endl;
    cout << "[2] Reducao" << endl;
    
}