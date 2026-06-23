#include <iostream>
#include <string>
#include "imagens.h"


using namespace std;

// Funcoes secundarias

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

int menu()
{
    // Variaveis
    int escolha = 10;

    cout << "----------- M E N U -----------" << endl;
    cout << "[1] Leitura do arquivo-texto PGM " << endl;
    cout << "[2] Clarear ou escurecer" << endl;
    cout << "[3] Binarizar por um limiar" << endl;
    cout << "[4] Rotacionar" << endl;
    cout << "[5] Imagem negativa" << endl;
    cout << "[6] Filtro passa-baixa" << endl;
    cout << "[7] Escurecer borda" << endl;
    cout << "[0] Sair" << endl;

    escolha = lerInteiro(": "); // Verificando se um numero foi digitado

    return escolha;
}


// Funcao principal

int main()
{
    // Variaveis
    static tImagem img_entrada;
    string nome_user;
    int escolha_user = 10;
    int colunas = 0, linhas = 0, tons = 0, return_carregaPGM = 0;

    while ((escolha_user = menu()) != 0)
    {
        // Opcoes
        switch (escolha_user)
        {
        case 1:
        {
            // Entrada de dados
            cout << "Escreva o nome do arquivo a ser lido: " << endl;
            cin >> nome_user;
            nome_user = nome_user + ".pgm";

            return_carregaPGM = carregaPGM(nome_user, img_entrada, &colunas, &linhas, &tons);

            // Verificacao da função
            if (return_carregaPGM == 0)
            {
                cout << "Arquivo lido com sucesso! " << endl;
            }
            else
            {
                cout << "ERRO: Arquivo nao encontrado. ";

                return 1;
            }

            break;
        }

        case 2:
        {
            // Variaveis
            int sucesso = 0;

            // Verificacao se a imagem foi inicializada
            if (linhas == 0)
            {
                cout << "Nenhuma imagem foi inicializda. Tente novamente. " << endl;
                break;
            }

            // Variaveis
            int valor_user = 0, cl_escPGM;

            // Entrada de dados
            cout << "Informe o valor para a alteracao.\nExemplo:\n-50 para subtrair 50 em cada pixel.\n50 para acrescer 50 em cada pixel." << endl;
            valor_user = lerInteiro(": "); // Verificando se um numero foi digitado

            // Chamando a funcao e salvando seu return
            cl_escPGM = clarear_escurecerPGM(img_entrada, colunas, linhas, valor_user, tons);

            if (cl_escPGM != 0)
            {
                cout << "ERRO: Nao foi possivel clarear a imagem." << endl;
            }

            cout << "Imagem clarada/escurecida com sucesso!\nEscreva o nome da imagem a ser salva:\n";
            cin >> nome_user;

            sucesso = salvaPGM(nome_user + "_2" + ".pgm", img_entrada, colunas, linhas, tons); // Salvando o arquivo

            // Verificando se a imagem foi salva corretamente
            if (sucesso != 0)
            {
                cout << "ERRO: Nao foi possivel salvar o arquivo. " << endl;
                break;
            }

            cout << "Arquivo salvo corretamente. " << endl;

            break;
        }

        case 3:
        {
            // Verificacao se a imagem foi inicializada
            if (linhas == 0)
            {
                cout << "Nenhuma imagem foi inicializda. Tente novamente. " << endl;
                break;
            }

            // Variaveis
            int limiar_user = 0;
            int sucesso = 0;
            string nome_user;

            // Entrada de dados
            cout << "Informe o limiar para binarizar a imagem-texto: " << endl;
            limiar_user = lerInteiro(": "); // Verificando se um numero foi digitado

            // Verificando se o numero digitado esta no intervalo esperado
            while ((tons < limiar_user) || (limiar_user < 0))
            {
                cout << "ERRO: Digite um numero entre 0 e " << tons << "." << endl;
                limiar_user = lerInteiro(": "); // Verificando se um numero foi digitado
            }

            binPGM(img_entrada, colunas, linhas, tons, limiar_user);

            cout << "Imagem binarizada com sucesso!\nEscreva o nome da imagem a ser salva:" << endl;
            cin >> nome_user;

            sucesso = salvaPGM(nome_user + "_3" + ".pgm", img_entrada, colunas, linhas, tons);

            // Verificando se a imagem foi salva corretamente
            if (sucesso != 0)
            {
                cout << "ERRO: Nao foi possivel salvar o arquivo. " << endl;
                break;
            }

            cout << "Arquivo salvo corretamente. " << endl;

            break;
        }
        case 4:
        {
            // Variaveis
            int sucesso = 0;

            // Verificacao se a imagem foi inicializada
            if (linhas == 0)
            {
                cout << "Nenhuma imagem foi inicializda. Tente novamente. " << endl;
                break;
            }

            // Variaveis
            int resp_user = 0;

            cout << "-------- ROTACIONAR ---------" << endl;
            cout << "[1] Esquerda" << endl;
            cout << "[2] Direita" << endl;
            cout << "[3] Vertical" << endl;
            cout << "[4] Horizontal" << endl;
            cout << "[0] Sair" << endl;
            resp_user = lerInteiro(": "); // Verificando se um numero foi digitado

            switch (resp_user)
            {
            case 1:
            {
                // Variaveis
                int esquerda = esquerdaPGM(img_entrada, &linhas, &colunas);
                string nome_user;

                // Verificacao da execucao da funcao
                if (esquerda != 0)
                {
                    cout << "ERRO: Nao foi possivel rotacionar. " << endl;

                    break;
                }

                cout << "Imagem rotacionada com sucesso!\nEscreva o nome da imagem a ser salva: " << endl;
                cin >> nome_user;

                sucesso = salvaPGM(nome_user + "_4.1" + ".pgm", img_entrada, colunas, linhas, tons);

                // Verificando se a imagem foi salva corretamente
                if (sucesso != 0)
                {
                    cout << "ERRO: Nao foi possivel salvar o arquivo. " << endl;
                    break;
                }

                cout << "Arquivo salvo corretamente. " << endl;

                break;
            }
            case 2:
            {
                // Variaveis
                int direita = direitaPGM(img_entrada, &linhas, &colunas);
                int sucesso = 0;
                string nome_user;

                // Verificacao da execucao da funcao
                if (direita != 0)
                {
                    cout << "ERRO: Nao foi possivel rotacionar. " << endl;

                    break;
                }

                cout << "Imagem rotacionada com sucesso!\nEscreva o nome da imagem a ser salva: " << endl;
                cin >> nome_user;

                sucesso = salvaPGM(nome_user + "_4.2" + ".pgm", img_entrada, colunas, linhas, tons);

                // Verificando se a imagem foi salva corretamente
                if (sucesso != 0)
                {
                    cout << "ERRO: Nao foi possivel salvar o arquivo. " << endl;
                    break;
                }

                cout << "Arquivo salvo corretamente. " << endl;

                break;
            }
            case 3:
            {
                // Variaveis
                int vertical = verticalPGM(img_entrada, linhas, colunas);
                int sucesso = 0;
                string nome_user;

                // Verificacao da execucao da funcao
                if (vertical != 0)
                {
                    cout << "ERRO: Nao foi possivel rotacionar. " << endl;

                    break;
                }

                cout << "Imagem rotacionada com sucesso!\nEscreva o nome da imagem a ser salva: " << endl;
                cin >> nome_user;

                sucesso = salvaPGM(nome_user + "_4.3" + ".pgm", img_entrada, colunas, linhas, tons);

                // Verificando se a imagem foi salva corretamente
                if (sucesso != 0)
                {
                    cout << "ERRO: Nao foi possivel salvar o arquivo. " << endl;
                    break;
                }

                cout << "Arquivo salvo corretamente. " << endl;

                break;
            }
            case 4:
            {
                // Variaveis
                int horizontal = horizontalPGM(img_entrada, linhas, colunas);
                int sucesso = 0;
                string nome_user;

                // Verificacao da execucao da funcao
                if (horizontal != 0)
                {
                    cout << "ERRO: Nao foi possivel rotacionar. " << endl;

                    break;
                }

                cout << "Imagem rotacionada com sucesso!\nEscreva o nome da imagem a ser salva: " << endl;
                cin >> nome_user;

                sucesso = salvaPGM(nome_user + "_4.4" + ".pgm", img_entrada, colunas, linhas, tons);

                // Verificando se a imagem foi salva corretamente
                if (sucesso != 0)
                {
                    cout << "ERRO: Nao foi possivel salvar o arquivo. " << endl;
                    break;
                }

                cout << "Arquivo salvo corretamente. " << endl;

                break;
            }
            case 0:
            {
                cout << "Saindo... " << endl;
                break;
            }

            default:
            {
                cout << "ERRO: Opcao invalida" << endl;
                break;
            }
            }

            break;
        }

        case 5:
        {
            // Variaveis
            int negativo = 0, sucesso = 0;

            // Verificacao se a imagem foi inicializada
            if (linhas == 0)
            {
                cout << "Nenhuma imagem foi inicializda. Tente novamente. " << endl;
                break;
            }

            negativo = negativoPGM(img_entrada, linhas, colunas, tons);

            // Verificando se a funcao foi executada corretamente
            if (negativo != 0)
            {
                cout << "ERRO: Nao foi possivel gerar a imagem negativa. Tente novamente. " << endl;
                break;
            }

            cout << "Imagem negativa foi realizada com sucesso!\nEscreva o nome da imagem a ser salva: " << endl;
            cin >> nome_user;

            sucesso = salvaPGM(nome_user + "_5" + ".pgm", img_entrada, colunas, linhas, tons);

            // Verificando se a imagem foi salva corretamente
            if (sucesso != 0)
            {
                cout << "ERRO: Nao foi possivel salvar o arquivo. " << endl;
                break;
            }

            cout << "Arquivo salvo corretamente. " << endl;

            break;
        }

        case 6:
        {
            // Variaveis
            int passabaixa = 0, sucesso = 0;
            string nome_user;

            // Verificacao se a imagem foi inicializada
            if (linhas == 0)
            {
                cout << "Nenhuma imagem foi inicializda. Tente novamente. " << endl;
                break;
            }

            passabaixa = passabaixaPGM(img_entrada, linhas, colunas);

            // Verificando se a funcao foi executada corretamente
            if (passabaixa != 0)
            {
                cout << "ERRO: Nao foi possivel aplicar o filtro passa-baixa. Tente novamente. " << endl;
                break;
            }

            cout << "Filtro passa baixa aplicado com sucesso!\nEscreva o nome da imagem a ser salva: " << endl;
            cin >> nome_user;

            sucesso = salvaPGM(nome_user + "_6" + ".pgm", img_entrada, colunas, linhas, tons);

            // Verificando se a imagem foi salva corretamente
            if (sucesso != 0)
            {
                cout << "ERRO: Nao foi possivel salvar o arquivo. " << endl;
                break;
            }

            cout << "Arquivo salvo corretamente. " << endl;

            break;
        }

        case 7:
        {
            // Variaveis
            int fator_inicial = 0;
            int decremento = 0;
            int escurecerborda = 0;
            int sucesso = 0;
            string nome_user;

            // Verificando se a imagem foi inicializada
            if (linhas == 0)
            {
                cout << "Nenhuma imagem foi inicializada. Tente novamente." << endl;
                break;
            }

            // Entrada de dados
            cout << "Informe o fator inicial de escurecimento: " << endl;
            fator_inicial = lerInteiro(": ");

            // Verificando se o numero digitado esta no intervalo esperado
            while (fator_inicial < 0 || fator_inicial > tons)
            {
                cout << "ERRO: Digite um fator entre 0 e " << tons << "." << endl;
                fator_inicial = lerInteiro(": ");
            }

            cout << "Informe o decremento por camada: " << endl;
            decremento = lerInteiro(": ");

            // Verificando se o numero digitado esta no intervalo esperado
            while (decremento < 0 || decremento > tons)
            {
                cout << "ERRO: Digite um decremento entre 0 e " << tons << "." << endl;
                decremento = lerInteiro(": ");
            }

            escurecerborda = escurecerbordaPGM(img_entrada, linhas, colunas, fator_inicial, decremento);

            if (escurecerborda != 0)
            {
                cout << "ERRO: Nao foi possivel escurecer a borda. " << endl;
                break;
            }

            cout << "Borda escurecida com sucesso! " << endl;
            cout << "Escreva o nome do arquivo a ser salvo: " << endl;
            cin >> nome_user;

            sucesso = salvaPGM(nome_user + "_7" + ".pgm", img_entrada, colunas, linhas, tons);

            if (sucesso != 0)
            {
                cout << "ERRO: Nao foi possivel salvar o arquivo." << endl;
                break;
            }

            cout << "O arquivo foi salvo corretamente. " << endl;

            break;
        }

        default:
        {
            cout << "ERRO: Opcao invalida" << endl;
            break;
        }
        }
    }

    cout << "Encerrando..." << endl;
}
