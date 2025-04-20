#include <iostream>
using namespace std;
class Chinela{
    int tamanho = 0;
    public:
    Chinela(){
        this->tamanho = tamanho;
    }
    int getTamanho(){
        return tamanho;
    }
        void setTamanho(int valor) {
       
        if (valor >= 20 && valor <= 50 && valor % 2 == 0) {
            tamanho = valor;
        } else {
            cout << "Valor invalido! Tamanho deve ser um numero par entre 20 e 50." << endl;
        }
    }
};
int main() {
    Chinela chinela;

    while (chinela.getTamanho() == 0) {
        cout << "Digite o tamanho da chinela (um numero par entre 20 e 50): ";
        int tamanho;
        cin >> tamanho;
        chinela.setTamanho(tamanho);
    }

    cout << "Parabens, voce comprou uma chinela tamanho " << chinela.getTamanho() << "." << endl;

    std::cout << "qxcode\n";
}

