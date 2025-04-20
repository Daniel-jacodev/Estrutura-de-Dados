#include <iostream>
#include <memory>
#include <sstream>
using namespace std;

class Grafite {
    string dureza;
    int tamanho;
    float espessura;

public:
    Grafite(string dureza, int tamanho, float espessura)
        : dureza(dureza), tamanho(tamanho), espessura(espessura) {}

    string getDureza() const {
        return this->dureza;
    }
    int getTamanho() const {
        return this->tamanho;
    }
    void setTamanho(int tamanho) {
        this->tamanho = tamanho;
    }
    float getCalibre() const {
        return this->espessura;
    }

    string str() const {
        stringstream ss;
        ss << "[" << espessura << ":" << dureza << ":" << tamanho << "]";
        return ss.str();
    }
};

class Lapiseira {
    float calibre = 0;
    shared_ptr<Grafite> grafite = nullptr;

public:
    void criar(float calibre) {
        this->calibre = calibre;
    }

    void inserir(shared_ptr<Grafite> grafite) {
        if (this->grafite != nullptr) {
            cout << "fail: ja existe grafite" << endl;
            return;
        }
        if (grafite->getCalibre() != this->calibre) {
            cout << "fail: calibre incompativel" << endl;
            return;
        }
        this->grafite = grafite;
    }

    void remover() {
        //cout << "vai se fuder" << endl;
        if(grafite != nullptr){
            grafite = nullptr;  // Remover o grafite
            return;
        }
        if(grafite == nullptr){
            cout << "fail: nao tem nada no tambor" << endl;
            return;
        }
    }
    void escrever(){
        if(grafite == nullptr){
            cout << "fail: nao existe grafite" << endl;
            return;
        }
        else if(grafite->getTamanho() <= 10){
            cout << "fail: tamanho insuficiente" << endl;
            return;
        }
        else if (grafite->getTamanho() > 10){
            if(grafite->getDureza() == "HB"){
                grafite->setTamanho(grafite->getTamanho() - 1);
            }
            if(grafite->getDureza() == "2B"){
                grafite->setTamanho(grafite->getTamanho() - 2);
                if(grafite->getTamanho() < 10){
                    cout << "fail: folha incompleta" << endl;
                   grafite->setTamanho(10);
                }
            }
            if(grafite->getDureza() == "4B"){
                grafite->setTamanho(grafite->getTamanho() - 4);
                if(grafite->getTamanho() < 10){
                    cout << "fail: folha incompleta" << endl;
                   grafite->setTamanho(10);
                }
            }
            if(grafite->getDureza() == "6B"){
                grafite->setTamanho(grafite->getTamanho() - 6);
            }
        }
    }
    string str() const {
        stringstream ss;
        ss << "calibre: " << calibre << ", grafite: ";
        if (grafite) {
            ss << grafite->str();
        } else {
            ss << "null";
        }
        return ss.str();
    }
};

int main() {
    Lapiseira lapiseira;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "show") {
            cout << lapiseira.str() << endl;
        } else if (cmd == "init") {
            float thickness;
            ss >> thickness;
            lapiseira.criar(thickness);
        } else if (cmd == "insert") {
            float thickness;
            string hardness;
            int size;
            ss >> thickness >> hardness >> size;
            auto grafite = make_shared<Grafite>(hardness, size, thickness);
            lapiseira.inserir(grafite);
        } else if (cmd == "remove") {
            lapiseira.remover();  // Apenas chama o método para remover
        } 
        else if (cmd == "write") { 
            lapiseira.escrever();
        }
    
        else {
            cout << "fail: comando invalido" << endl;
        }
    }
}
