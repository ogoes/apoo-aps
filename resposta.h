#ifndef RESPOSTA_H
#define RESPOSTA_H

#include <iostream>
#include <string.h>
#include "escolha.h"

using namespace std;

typedef struct dict {
    char texto[100];
    char resposta;
}Dict;

class Resposta {
    private:
        int qtdeRespostas;

    public:
        Resposta () {

        };

        /* 
            Métodos Abstratos
         */
        virtual char** getResposta () { }; 
        virtual int getQtde () { };
        virtual void setQtde () { };
        virtual void consultaResposta () { };


        /* 
            Métodos virtuais de Multescolha
        */

        virtual void addEscolha (char escolha[]) { };
        virtual void setResposta (int respostaIndex) { };
        virtual void removeEscolha(int respostaIndex) { };

        /* 
            Métodos virtuais de TrueFalse
        */
        virtual void addResposta (char texto[], char TF) { };
        virtual void removeResposta (int index) { };
        virtual void updateResposta (int index, char texto[], char TF) { };

        /* 
            Métodos virtuais de QuestãoAberta
        */
        virtual void setResposta (char resposta[]) { };

};

class Multiplaescolha: public Resposta {
    private:
        int qtdeOpcoes;
        Escolha** textosEscolhas;
        int respostaIndex;
        


    public:
        Multiplaescolha () {
            // Contructor
        };
        virtual ~Multiplaescolha () {
            // Desconstructor
        };

        virtual void setQtde (int qtde) {
            this->qtdeOpcoes = qtde;
        };
        virtual char** getResposta () {
            char** novo = (char**) malloc (sizeof(char*));
            novo[0] = this->textosEscolhas[this->respostaIndex]->getText();
            return novo;
        };
        virtual void setResposta (int respostaIndex) {
            this->respostaIndex = respostaIndex;
        };
        virtual void addEscolha (char escolha[]) {
            Escolha** Aux = this->textosEscolhas; // Faz copia dos valores de escolhas que já possui
            
            this->textosEscolhas = (Escolha**) calloc(this->qtdeOpcoes+1, sizeof(Escolha*));
            
            int i = 0;
            
            while (i < this->qtdeOpcoes) { // Faz a cópia para o vetor que foi alocado em um espaço menor
                this->textosEscolhas[i] = Aux[i];
                ++i;
            }
            Escolha* novaEscolha = new Escolha(); // Cria um novo objeto com valor de Escolha
            novaEscolha->setTexto(escolha);

            this->textosEscolhas[this->qtdeOpcoes] = novaEscolha; // atribue à ultima posição
            free(Aux);

            setQtde(this->qtdeOpcoes + 1);

        };
        virtual void removeEscolha (int respostaIndex) {
            Escolha** Aux = (Escolha**) calloc (this->qtdeOpcoes-1, sizeof(Escolha*));

            int i = 0;
            int j = 0;

            while (i < this->qtdeOpcoes) {
                if (i != respostaIndex) {
                    Aux[j] = this->textosEscolhas[i];
                    ++j;
                }
                ++i;
            }
            
            this->textosEscolhas[respostaIndex]->~Escolha();
            this->textosEscolhas = Aux;

            setQtde(this->qtdeOpcoes - 1);            
        };
        virtual void consultaResposta () {
            cout << this->textosEscolhas[this->respostaIndex]->getText << endl;
        };

};

class TrueFalse: public Resposta {
    private:
        int qtdeOpcoes;
        Dict** dicionario;

    public:
        
        TrueFalse () {
            // Contructor
        };
        virtual ~TrueFalse () {
            // descontructor
        };


        virtual void setQtde (int qtde) {
            this->qtdeOpcoes = qtde;
        };
        virtual char** getResposta () {
            if (this->qtdeOpcoes > 0) {
                Dict** dict = this->dicionario;
                char** back = (char**) calloc(this->qtdeOpcoes, sizeof(char*));
                int  i = 0;

                while (i < this->qtdeOpcoes) {
                    back[i] = (char*) calloc (strlen(dict[i]->texto) + 5, sizeof(char));

                    strcat(back[i], "( ");

                    char res[] = {dict[i]->resposta};
                    strcat(back[0], res);

                    strcat(back[i], ") ");

                    strcat(back[i], dict[i]->texto);
                    
                    ++i;
                }

                return back;
            }
            else {
                return NULL;
            }

        };
        virtual void addResposta (char texto[], char TF) { // TF = trueFalse
            Dict** Aux = this->dicionario;
            this->dicionario = (Dict**) calloc(this->qtdeOpcoes + 1, sizeof(Dict*));
            
            int i = 0;
            while (i < this->qtdeOpcoes) {
                this->dicionario[i] = Aux[i];
                ++i;
            }
            
            this->dicionario[ this->qtdeOpcoes ]->resposta = TF;
            strcpy (this->dicionario[ this->qtdeOpcoes ]->texto, texto);

            free(Aux);
            setQtde(this->qtdeOpcoes + 1);
        };
        virtual int getQtde() {
            return this->qtdeOpcoes;
        };
        virtual void removeResposta(int index) {
            Dict** Aux = (Dict**) calloc(this->getQtde() - 1, sizeof(Dict*));
            int i = 0;
            int j = 0;

            while (i < this->qtdeOpcoes) {
                if (i != index) {
                    Aux[j] = this->dicionario[i];
                    ++j;
                }

                ++i;
            }
            free(this->dicionario[index]);
            
            this->dicionario = Aux;
            setQtde(this->qtdeOpcoes - 1);
        };
        virtual void updateResposta(int index, char texto[], char TF) {
            strcpy(this->dicionario[index]->texto, texto);
            this->dicionario[index]->resposta = TF;
        };
        virtual void consultaResposta() {
            int i = 0;
            while (i < this->qtdeOpcoes) {
                cout << " (" << this->dicionario[i]->resposta << ") " << this->dicionario[i]->texto << endl;
                ++i;
            }
        };
};

class QuestaoAberta: public Resposta {
    private:
        char resposta[500];

    public:


        QuestaoAberta () {
            cout << "hello" << endl;
        };

        virtual void setQtde (int qtde) {
            // qtde é constante = 1
        };

        virtual char** getResposta () {
            char** novo = (char**) malloc(sizeof(char*));
            strcpy(novo[0], this->resposta);
            return novo;
        };
        virtual void setResposta (char resposta[]) {
            strcpy( this->resposta, resposta);
        };
        virtual int  getQtde () {
            return 1;
        };

        virtual void consultaResposta () {
            cout << this->resposta << endl;
        }

        
};


#endif