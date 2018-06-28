#ifndef QUESTAO_H
#define QUESTAO_H

#include <time.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "resposta.h"

using namespace std;

class Questao {
    private:
        float nota;
        char enunciado[1000];
        int tipoResposta;
        Resposta* resposta;

    public:
        Questao () {
            char enunciado[200];
            float nota;
            fflush(stdin);


            cout << "\t\tCriar nova questão" << endl;
            cout << "Enunciado: ";
            scanf(" %s", enunciado);
            cout << "Nota: ";
            scanf("%f", &nota);
            fflush(stdin);

            setEnunciado(enunciado);
            setNota(nota);

            int op;
            do {
                cout << "\n\t\tSelecione o tipo de resposta:" << endl;
                cout << "(1) Multipla Escolha" << endl;
                cout << "(2) Verdadeiro ou Falso" << endl;
                cout << "(3) Questão dissertativa\n" << endl;

                char OP[100];
                scanf(" %s", OP);
                fflush(stdin);

                op = atoi(OP);
                if (op <= 0 || op > 3)
                    cout << "\nOpção inválida\n\n" << endl;
            } while (op <= 0 || op > 3);
            setTipoResposta(op);


         };
        virtual ~Questao () { };

        void setNota (float nota) {
            this->nota = nota;
        };

        float getNota () {
            return this->nota;
        };
        void setEnunciado (char enun[]) {
            if (strlen(enunciado) > 999) 
                strcpy(this->enunciado, enunciado);
            else
                cout << "Enunciado muito gigantão" << endl;
        };
        char* getEnunciado () {
            return this->enunciado;
        };
        void setTipoResposta (int OP) {
            if (OP == 1) {
                this->resposta = new Multiplaescolha();
                this->tipoResposta = OP;
            }
            else if (OP == 2) {
                this->resposta = new TrueFalse();
                this->tipoResposta = OP;
            }
            else if (OP == 3) {
                this->resposta = new QuestaoAberta();
                this->tipoResposta = OP;
            }
            else 
                cout << "Eroooooooooooo" << endl;
        };
        void removeResposta () {
            this->resposta->~Resposta();
        }
        void getResposta() {
            char** res = this->resposta->getResposta();
            cout << res[0] << endl;
        }


        void compartilhar () { /* "gera" um link só para amostra */
            srand(time(NULL));

            char validchars[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
            char* novaString = (char* ) calloc(10, sizeof(char));

            for (int i = 0; i < 10; ++i) {
                novaString[i] = validchars[ rand() % strlen(validchars)];
                novaString[i + 1] = 0x0;
            }

            cout << "Link para questão: " << novaString << ".quest" << endl;
        }


};



#endif