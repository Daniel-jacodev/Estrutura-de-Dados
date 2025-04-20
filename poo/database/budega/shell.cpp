#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <sstream>
#include <utility>
using namespace std;
// Função auxiliar para mapear e juntar elementos de um container
template <typename CONTAINER, typename FUNC>
auto map_join(const CONTAINER& c, FUNC f, const string& sep = ", ") {
    stringstream ss;
    for (auto it = c.begin(); it != c.end(); ++it) {
        ss << (it != c.begin() ? sep : "") << f(*it);
    }
    return ss.str();
}

class Pessoa{
    string nome;
    public:
    Pessoa(string nome) : nome(nome){}
    string getNome() const{
        return this->nome;
    }
    string str(){
        stringstream ss;
        ss << nome;
        return ss.str();
    }
};

class Market {
    int caixas{};
    list <shared_ptr <Pessoa>> espera;
    shared_ptr<Pessoa> lista {nullptr};
    vector<shared_ptr<Pessoa>> caixasAtendimento;
    
public:
    // Construtor
    Market(int caixas) : caixas(caixas), caixasAtendimento(caixas, nullptr) {}

   
    void inserir(shared_ptr<Pessoa> pessoa) {
        espera.push_back(pessoa);
    }
    
    void finalizar(int indice){
        if(indice >= caixas){
            cout << "fail: caixa inexistente" << endl;
            return;
        }
        if(caixasAtendimento[indice] == nullptr){
            cout << "fail: caixa vazio" << endl;
            return;
        }
        caixasAtendimento[indice] = nullptr;
    }

    void chamar(int indice) {
        if (espera.empty()) {
            cout << "fail: sem clientes" << endl;
            return;
        }
        if (caixasAtendimento[indice] != nullptr) {
            cout << "fail: caixa ocupado" << endl;
            return;
        }
        shared_ptr<Pessoa> pessoa = espera.front();
        espera.pop_front();
        caixasAtendimento[indice] = pessoa; 
    }

    string str() {
        stringstream ss;
        ss << "Caixas: [";
        for (int i = 0; i < caixas; i++) {
            if (i > 0) ss << ", ";
            if(caixasAtendimento[i] != nullptr){
                ss << caixasAtendimento[i]->getNome();
            }else{
                ss << (lista != nullptr ? lista->getNome() : "-----");
            }
        }
        ss << "]" << endl << "Espera: [";
        if (espera.empty()) {
            ss << "]";
        } else {
            for (auto it = espera.begin(); it != espera.end(); ++it) {
                ss << (*it)->getNome();
                if (next(it) != espera.end()) {
                    ss << ", ";
                }
            }
            ss << "]";
        }
        return ss.str();
    }
};


int main() {
    Market market(0);
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "show") { 
            cout << market.str() << endl;
        } else if (cmd == "init") { 
             int caixas;
             ss >> caixas;
             market = Market(caixas);
        } else if (cmd == "arrive") { 
             string nome;
             ss >> nome;
             market.inserir(make_shared<Pessoa>(nome));
        } else if (cmd == "call") { 
             int indice;
             ss >> indice;
             market.chamar(indice);
        } else if (cmd == "finish") { 
             int indice;
             ss >> indice;
             market.finalizar(indice);
        } else {
            cout << "fail: comando invalido\n";
        }
    }
}
