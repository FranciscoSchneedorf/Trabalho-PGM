# Processamento de Imagens PGM com Ponteiros

## Disciplina

AEDS I — Algoritmos e Estruturas de Dados I
Turma: 2026/1

## Integrantes

* Maick Carvalho
* Francisco Schneedorf
* Kauã Carvalho

## Descrição do projeto

Este projeto implementa um programa em C++ para processamento de imagens no formato PGM texto, tipo `P2`.

O programa permite carregar uma imagem PGM, aplicar operações de processamento e salvar uma nova imagem resultante. As operações sobre os pixels são realizadas utilizando ponteiros, conforme a restrição da atividade.

## Arquivos do projeto

O projeto é composto pelos seguintes arquivos:

* `main.cpp`: contém a função principal, o menu de opções e as chamadas das funções de processamento.
* `imagens.cpp`: contém a implementação das funções de leitura, escrita e processamento das imagens.
* `imagens.h`: contém as constantes, o tipo da imagem e os protótipos das funções.
* `README.txt`: contém as informações do projeto, instruções de compilação e uso.

## Como compilar

Para compilar o programa, execute no terminal, dentro da pasta do projeto:

```bash
g++ main.cpp imagens.cpp -o programa
```

No Windows, também é possível gerar o executável com extensão `.exe`:

```bash
g++ main.cpp imagens.cpp -o programa.exe
```

## Como executar

Após compilar, execute:

```bash
./programa
```

No Windows PowerShell, execute:

```bash
./programa.exe
```

## Formato da imagem

O programa trabalha com imagens PGM texto no formato `P2`.

A imagem deve conter:

1. o identificador `P2`;
2. a largura e a altura da imagem;
3. o valor máximo de cinza;
4. os valores dos pixels.

## Opções do menu

O programa apresenta um menu interativo com as seguintes opções:

* `[1]` Leitura do arquivo-texto PGM
* `[2]` Clarear ou escurecer
* `[3]` Binarizar por um limiar
* `[4]` Rotacionar
* `[5]` Imagem negativa
* `[6]` Filtro passa-baixa
* `[7]` Escurecer borda
* `[8]` Iconização
* `[9]` Filtro passa-baixa iterativo
* `[10]` Espelhamento diagonal
* `[11]` Redimensionamento por fator inteiro
* `[12]` Recorte de região
* `[0]` Sair

## Descrição das principais operações

### Clarear ou escurecer

Solicita um valor inteiro ao usuário.
Valores positivos clareiam a imagem, e valores negativos escurecem.
Os pixels são limitados ao intervalo entre `0` e o valor máximo de cinza.

### Binarizar por limiar

Solicita um limiar ao usuário.
Pixels acima do limiar tornam-se brancos, e os demais tornam-se pretos.

### Rotacionar

Abre um submenu com opções de rotação:

* esquerda;
* direita;
* vertical;
* horizontal.

As rotações para esquerda e direita alteram as dimensões da imagem, trocando linhas por colunas.

### Imagem negativa

Inverte os valores de cinza da imagem.

### Filtro passa-baixa

Aplica um filtro de suavização 3 × 3 por média aritmética dos vizinhos.
Os pixels de borda são mantidos com seus valores originais.

### Escurecer borda

Escurece progressivamente as camadas da borda da imagem, usando um fator inicial e um decremento informados pelo usuário.

### Iconização

Gera uma versão reduzida da imagem com 32 × 32 pixels.

### Filtro passa-baixa iterativo

Aplica o filtro passa-baixa 3 × 3 repetidas vezes, conforme o número de iterações informado pelo usuário.

### Espelhamento diagonal

Gera uma nova imagem transposta, trocando linhas por colunas.

### Redimensionamento por fator inteiro

Permite ampliar ou reduzir a imagem por um fator inteiro.

Na ampliação, cada pixel é replicado em um bloco `N × N`.

Na redução, é amostrado 1 pixel a cada `N` pixels nas linhas e nas colunas.

### Recorte de região

Solicita ao usuário:

* linha inicial;
* coluna inicial;
* altura;
* largura.

A função extrai a subimagem correspondente à região informada, desde que ela esteja dentro dos limites da imagem original.

## Observações

As operações devem ser executadas somente após uma imagem ter sido carregada.

Cada operação de processamento gera uma nova imagem PGM de saída.

O projeto não deve ser entregue com arquivos executáveis, arquivos compactados ou imagens de saída geradas durante os testes.
