#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "questao.h"



using namespace std;


class Interface {
    private:
        int qtdeQuestoes;
        Questao** questoes;

        void listaQuestoes () {
            
        };
        void menuQuestao () {
            char OP[100];

            cout << "\t\t\t\tGerenciamento de Questões\n" << endl;
            cout << "Escolhas: " << endl;
            cout << "(1) Criar nova questão" << endl;
            cout << "(2) Excluir questão" << endl;
            cout << "(3) Atualizar questão" << endl;
            cout << "(4) Consultar questão" << endl;
            cout << "(5) Sair" << endl;
            cout << "Opção: ";
            
            scanf(" %s", OP);
            fflush(stdin);

            int operation = atoi(OP);
            
            if (operation <= 0 || operation > 5) {
                cout << "Opção inválida";
                menuQuestao();
            }
            opcoes (operation);
            menuQuestao();


        };
        void opcoes (int operation) {
            if (operation == 1) {
                criarQuestao();
            }
            else if (operation == 2) {
                excluirQuestao();
            }
            else if (operation == 3) {
                atualizarQuestao();
            }
            else if (operation == 4) {
                consultarQuestao();
            }
            else if (operation == 5) {
                cout << ":)" << endl;
                exit(0);
            }
        };
        void criarQuestao () {
            Questao** Aux = this->questoes;
            this->questoes = (Questao**) calloc (this->qtdeQuestoes + 1, sizeof(Questao*));
            int i = 0;
            while (i < this->qtdeQuestoes) {
                this->questoes[i] = Aux[i];
                ++i;
            }
            this->questoes[ this->qtdeQuestoes ] = new Questao();

        };
        void excluirQuestao() {
            if (this->qtdeQuestoes = 0) {
                cout << "Nenhuma questão cadastrada até o momento";
                return;
            }
            cout << "Não implementado" << endl;

        };
        void atualizarQuestao() {
            if (this->qtdeQuestoes = 0) {
                cout << "Nenhuma questão cadastrada até o momento";
                return;
            }
            cout << "Não implementado" << endl;

        };
        void consultarQuestao () {
            if (this->qtdeQuestoes = 0) {
                cout << "Nenhuma questão cadastrada até o momento";
                return;
            }
            questoes[0]->getResposta();
            // cout << "Não implementado" << endl;

        };
        

    public:
        Interface () { };
        virtual ~Interface () { };

        void init () {
            this->qtdeQuestoes = 0;
            menuQuestao();
        };
        


};








#endif