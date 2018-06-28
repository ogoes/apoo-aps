#ifndef ESCOLHA_H
#define ESCOLHA_H

#include <string.h>


class Escolha {
    private:
        char Texto[200];

    public:
        Escolha () {

        }
        virtual ~Escolha() {

        };
        void setTexto (char texto[]) {
            strcpy(this->Texto, texto);
        }
        char* getText() {
            return Texto;
        }

};




#endif 