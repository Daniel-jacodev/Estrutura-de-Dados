#include <iostream>
#include <sstream>
using namespace std;

class Toalha {
    string size;
    int umidade;
    string cor;

public:
    Toalha() {
        size = "";
        umidade = 0;
        cor = "";
    }


    void criar(string cor, string tamanho) {
        this->cor = cor;
        this->size = tamanho;
        this->umidade = 0;  
    }

  
    void enxugar(int valor) {
        umidade += valor;
        if (umidade >= getUmidadeMax()) {
            umidade = getUmidadeMax(); 
            cout << "toalha encharcada" << endl;
        }
    }


    void torcer() {
        umidade = 0;
    }


    int getUmidadeMax() {
        if (size == "P") {
            return 10;
        }
        else if (size == "M") {
            return 20;
        }
        else if (size == "G") {
            return 30;
        }
        return 0;
    }

   
    bool conferir() const {
        return umidade == 0;
    }

  
    string str() {
        stringstream ss;
        ss << "Cor: " << this->cor << ", Tamanho: " << this->size << ", Umidade: " << this->umidade;
        return ss.str();
    }
};

int main() {
    Toalha toalha;

    while (true) {
        string line, cmd;
        getline(cin, line);  
        cout << "$" << line << endl; 

        stringstream par(line); 
        par >> cmd;  

        if (cmd == "mostrar") {  
            cout << toalha.str() << endl;
        } 
        else if (cmd == "criar") { 
            string cor, tamanho;
            par >> cor >> tamanho;  
            toalha.criar(cor, tamanho); 
        } 
        else if (cmd == "enxugar") { 
            int valor;
            par >> valor;
            toalha.enxugar(valor); 
        } 
        else if (cmd == "torcer") { 
            toalha.torcer(); 
        } 
        else if (cmd == "seca") { 
            cout << (toalha.conferir() ? "sim" : "nao") << endl; 
        } 
        else if (cmd == "end") {
            break; 
        } 
        else {
            cout << "fail: comando invalido" << endl; 
        }
    }

    return 0;
}
