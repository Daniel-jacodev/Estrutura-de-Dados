#include <iostream>
#include <list>
#include <sstream>
#include <memory>
using namespace std;



// Função auxiliar para mapear e juntar elementos de um container
template <typename CONTAINER, typename FUNC>
auto map_join(const CONTAINER& c, FUNC f, const string& sep = ", ") {
    stringstream ss;
    for (auto it = c.begin(); it != c.end(); ++it) {
        ss << (it != c.begin() ? sep : "");
        ss << f(*it);
    }
    return ss.str();
}
class Grafite{
    float calibre{};
    int tamanho{};
    string dureza{};
    public:
    Grafite(float calibre, int tamanho, string dureza)
        : calibre(calibre), tamanho(tamanho), dureza(dureza){}
    
    float getCalibre(){
        return calibre;
    }
    int getTamanho(){
        return tamanho;
    }
    void setTamanho(int tamanho) {
        this->tamanho = tamanho;
    }
    string getDureza(){
        return dureza;
    }
    string str(){
        stringstream ss;
        ss <<"[" << calibre << ":" << dureza << ":" << tamanho << "]";
        return ss.str();
    }
};

class Lapiseira{
    float calibre{};
    shared_ptr <Grafite> ponta {nullptr};
    list<shared_ptr<Grafite>> tambor;
    public:
    Lapiseira(float calibre): calibre(calibre){}
    string str(){
        stringstream ss;
        auto LSTR = [](auto x){return x->str();};
        ss << "calibre: " << calibre << ", " 
            << "bico: " << (ponta != nullptr  ? ponta->str() :
                "[]") << ", tambor: <" << map_join(tambor, LSTR, "") 
        << ">";
        return ss.str();
    }  

    void inserir(shared_ptr<Grafite> grafite){
        if(this->calibre != grafite->getCalibre()){
            cout << "fail: calibre incompatível" << endl;
            return;
        }else{
        tambor.push_back(grafite);
        }
    }

    void puxar(){
        if(this->ponta == nullptr){
            this->ponta = tambor.front();
            tambor.pop_front();
        }else if(tambor.empty()){
            cout << "fail: tambor vazio" << endl;
        }else{
            cout << "fail: ja existe grafite no bico" << endl;
        }
    }

    void tirar(){
        if(this->ponta != nullptr){
            this->ponta = nullptr;
        }
        else{
            cout << "fail: nao existe grafite no bico" << endl;
        }
    }

    void escrever(){
        if(this->ponta == nullptr){
            cout << "fail: nao existe grafite no bico" << endl;
            return;
        }else if(ponta->getTamanho() <= 10){
            cout << "fail: tamanho insuficiente" << endl;
            return;
        }else{
            if(ponta->getDureza() == "HB"){
                ponta->setTamanho(ponta->getTamanho() - 1);
                return;
            }
            if(ponta->getDureza() == "2B"){
                if(ponta->getTamanho() == 11){
                    cout << "fail: folha incompleta" << endl;
                    ponta->setTamanho(ponta->getTamanho() - 1);
                    return;
                }else{
                    ponta->setTamanho(ponta->getTamanho() - 2);
                }
            }
            if (ponta->getDureza() == "4B"){
                if(ponta->getTamanho() < 14){
                    while(ponta->getTamanho() > 10){
                        ponta->setTamanho(ponta->getTamanho() - 1);
                    }
                    cout << "fail: folha incompleta" << endl;
                    return;
                }else{
               ponta->setTamanho(ponta->getTamanho() - 4);
                }
            }
        }
    }


};

int main() {
    Lapiseira lapiseira(0.5);
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;  
        }
        else if (cmd == "show") {
            cout << lapiseira.str() << endl;
        } 
        else if (cmd == "init") { 
             float calibre;
             ss >> calibre;
             lapiseira = Lapiseira(calibre);
        } 
        else if (cmd == "insert") { 
             float calibre;
             string dureza;
             int tamanho;
             ss >> calibre >> dureza >> tamanho;
             lapiseira.inserir(make_shared<Grafite>
                (calibre, tamanho, dureza));
        } 
        else if (cmd == "remove") { 
            lapiseira.tirar();
        } 
        else if (cmd == "pull") {
            lapiseira.puxar();
        } 
        else if (cmd == "write") {
            lapiseira.escrever();
        } 
        else {
            cout << "fail: comando invalido\n";
        }
    }
}
