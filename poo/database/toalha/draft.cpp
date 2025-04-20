#include <iostream>
using namespace std;
class Toalha{
    string size;
    int umidade;
    string cor;
    public:
    Toalha(){
        size = nullptr;
        umidade = 0;
        cor = nullptr;
    }
    void enxugar(int valor){
        umidade += valor;
    }
    void torcer(){
        umidade = 0;
    }
    int getUmidadeMax(string size) {
        if (size == "P") {
            return 10;
        }
        else if (size == "M") {
            return 20;
        }
        else if (size == "G") {
            return 30;
        }
        return 0; // valor padrão caso não seja P, M ou G
    }
    bool conferir() const {
        return umidade == 0;
    }
};
int main() {
    Toalha toalha;

    std::cout << "qxcode\n";
}

