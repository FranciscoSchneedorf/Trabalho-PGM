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

        // Laco para colocar o ponteiro na ultima linha util da imagem nova
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
    static tImagem aux;
    int lin_original = *lin;
    int col_original = *col;
    int *pOrigem = &img[0][0];
    int total = (*lin) * (*col);

    /*------ MONTANDO AUX ------*/
    for (int i = 0; i < lin_original; i++)
    {
        int *pDestino = &aux[0][0]; // Começa na primeira linha da imagem auxiliar

        // Laco para andar para a direita ate a coluna (lin_original - 1 - i)
        for (int k = 0; k < lin_original - 1 - i; k++)
        {
            pDestino++;
        }

        // Laco para percorrer as colunas da linha original
        for (int j = 0; j < col_original; j++)
        {
            *pDestino = *pOrigem; // Copiando o pixel da imagem original para o local onde o pDestino aponta

            pOrigem++; // Avanca para o proximo pixel da imagem original

            // Verificando se ainda ha pixels para copiar
            if (j < col_original - 1)
            {
                pDestino += lin_original; // Desce uma linha em aux
            }
        }
    }

    /*------ COPIANDO AUX PARA IMG ORIGINAL ------*/
    *lin = col_original;
    *col = lin_original;

    int *pAux = &aux[0][0];
    int *pImg = &img[0][0];

    for (int i = 0; i < total; i++)
    {
        *pImg = *pAux;
        pImg++;
        pAux++;
    }

    return 0;
}

int verticalPGM(tImagem img, int lin, int col)
{
    static tImagem aux;

    int *pOrigem = &img[0][0];                  // Aponta para o inicio da imagem original
    int *pDestino = &aux[0][0] + (lin - 1) * col; // Aponta para o inicio da ultima linha de aux

    // Laco para percorrer as linhas da imagem original
    for (int *fimLinhas = pOrigem + lin * col; pOrigem < fimLinhas; pDestino -= col)
    {
        // Laco para copiar uma linha inteira (col pixels)
        for (int *fimLinha = pOrigem + col; pOrigem < fimLinha; pOrigem++, pDestino++)
        {
            *pDestino = *pOrigem;
        }

        pDestino -= col; // Volta pDestino para o inicio da linha que acabou de copiar (compensa o avanco do laco interno)
    }

    // Laco para copiar aux de volta para img
    int *pAux = &aux[0][0];
    int *pImg = &img[0][0];
    int *fim = pImg + lin * col;

    for (; pImg < fim; pImg++, pAux++)
    {
        *pImg = *pAux;
    }

    return 0;
}

int horizontalPGM(tImagem img, int lin, int col)
{
    static tImagem aux;

    int *pOrigem = &img[0][0];                  // Aponta para o inicio da imagem original
    int *pDestino = &aux[0][0] + (lin - 1) * col; // Aponta para o inicio da ultima linha de aux

    // Laco para percorrer as linhas da imagem original
    for (int *fimLinhas = pOrigem + lin * col; pOrigem < fimLinhas; pDestino += 2 * col)
    {
        // Laco para copiar uma linha inteira (col pixels), de tras para frente
        for (int *fimLinha = pOrigem + col; pOrigem < fimLinha; pOrigem++, pDestino--)
        {
            *pDestino = *pOrigem;
        }
    }

    // Laco para copiar aux de volta para img
    int *pAux = &aux[0][0];
    int *pImg = &img[0][0];
    int *fim = pImg + lin * col;

    for (; pImg < fim; pImg++, pAux++)
    {
        *pImg = *pAux;
    }

    return 0;
}


int negativoPGM(tImagem img, int lin, int col, int tons)
{
    // Laco para passar por todos os pixel da matriz
    for (int *p = 0; p < &img[0][0] + col* lin; p++)
    {
            *p = tons - *p; // Subtrai-se de 255 o valor do pixel atual. Se for 0, 255 - 0 = 255. Logo, o pixel que era preto vira brnaco, e vice-versa
    }

    return 0;
}

int passabaixaPGM(tImagem img, int lin, int col)
{
    // Variaveis
    int soma = 0;
    static tImagem aux;

    // Laco para copiar a matriz original para aux, para nao altera-la durante os lacos
    int *origem = &img[0][0];
    int *destino = &aux[0][0];
    int *fim = origem + lin * col;

    for (; origem < fim; origem++, destino++)
    {
        *destino = *origem;
    }

    // Laco para passar por todos os pixels da imagem, comecando em 1 para linhas e colunas para nao contabilizar as bordas
    for (int *linha_central = &img[1][1]; linha_central < &img[lin - 1][1]; linha_central += col)
    {
        for (int *p = linha_central; p < linha_central+(col - 2); p++)
        {
            soma = 0; // Soma zerada a cada pixel

            for (int *linha_viz = p - col - 1; linha_viz <= p + col; linha_viz += col) // Laco para encontrar os vizinhos do pixel central
            {
                for (int *viz = linha_viz; viz <= linha_viz + 2; viz++)
                {
                    soma = soma + *viz;
                }
            }

            *(&aux[0][0] + (p - &img[0][0])) = soma / 9; // Alterando o pixel central
        }
    }

    // Laco para copiar a imagem filtrada para a original

    int *source = &aux[0][0];
    int *destino = &img[0][0];
    int *limite = destino + lin * col;

    for (; destino < limite; destino++, source++)
    {
        *destino = *source;
    }

    return 0;
}

int escurecerbordaPGM(tImagem img, int lin, int col, int fator, int decremento)
{
    // Variavies
    int camada = 0;
    int fator_atual = 0;

    // Laco para percorrer pixel a pixel, decrescendo de acordo com o fator e a camada em que se encontra
    for (int *p = &img[0][0]; p < &img[0][0] + (lin) * (col); p++){

    int offset = p - &img[0][0];   // posição linear do pixel
    int i = offset / col;          // linha
    int j = offset % col;          // coluna

            camada = min(min(i, lin - 1 - i), min(j, col - 1 - j)); // Calculando a menor distancia entre o pixel e as bordas; A menor distancia indica em que camada o pixel esta

            fator_atual = fator - (camada * decremento);

            // Se o fator ficar negativo, nao escurece mais
            if (fator_atual < 0)
            {
                fator_atual = 0;
            }

            img[i][j] = max(0, img[i][j] - fator_atual); // Escurece o pixel, sem deixar ficar abaixo de 0
    }

    return 0;
}
