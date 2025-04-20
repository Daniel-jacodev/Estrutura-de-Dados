#include <iostream>
using namespace std;

class Camisa {
    string tamanho;
public:

    Camisa() {
        this->tamanho = "";  
    }

 
    string getTamanho() {
        return tamanho;
    }


    void setTamanho(string tamain) {
       
        if (tamain == "P" || tamain == "M" || tamain == "G" || tamain == "GG" || tamain == "XG") {
            tamanho = tamain;
        } else {
            cout << "Tamanho inválido, tente novamente." << endl;
        }
    }
};

int main() {
    Camisa camisa; 
    string tamanho;

    while (camisa.getTamanho() == "") {
        cout << "Digite o tamanho da camisa (P, M, G, GG, XG): ";
        cin >> tamanho;
        camisa.setTamanho(tamanho);
    }

    cout << "Camisa tamanho " << camisa.getTamanho() << " selecionada." << endl;
    std::cout << "qxcode\n";
}
