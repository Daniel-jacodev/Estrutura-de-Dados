#include <sstream>
#include <iostream>
#include <list>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

template <typename CONTAINER, typename FN>
string map_join(const CONTAINER& container, FN fn, string sep = ", ") {
    stringstream ss;
    for (auto it = container.begin(); it != container.end(); ++it) {
        ss << (it != container.begin() ? sep : "") << fn(*it);
    }
    return ss.str();
}

enum class Label {GIVE, TAKE, PLUS};
string labelToString(Label label) {
    switch (label) {
        case Label::GIVE: return "give";
        case Label::TAKE: return "take";
        case Label::PLUS: return "plus";
        default: return "???";
    }
}
Label stringToLabel(const string& str){
    if (str == "give"){return Label::GIVE;}
    if (str == "take"){return Label::TAKE;}
    if (str == "plus"){return Label::PLUS;}
    throw runtime_error("Label inválido");
}

class Operacao{
    int id;
    string nome;
    Label label;
    int valor;

public:
    Operacao(int id, string nome, Label label, int valor): id(id), nome(nome), label(label), valor(valor){}

    int getId() const {
        return id;
    }

    string getNome() const {
        return nome;
    }

    Label getLabel() const {
        return label;
    }

    int getValor() const {
        return valor;
    }

    string str() const {
        stringstream ss;
        ss << labelToString(label) << ":" << nome << " " << valor;
        return ss.str();
    }
};

class Cliente{
    string nome;
    int limite;
    list<Operacao> operacoes;

public:
    Cliente(string nome, int limite) : nome(nome), limite(limite){}

    string getNome() const {
        return nome;
    }

    int getLimite() const {
        return limite;
    }

    const list<Operacao>& getOperacoes() const {
        return operacoes;
    }

    void addOperacao(Operacao op) {
        operacoes.push_back(op);
    }

    int getSaldo() const {
        int saldo = 0;
        for (const auto& op : operacoes) {
            if (op.getLabel() == Label::GIVE) {
                saldo += op.getValor();
            } else if (op.getLabel() == Label::TAKE) {
                saldo -= op.getValor();
            } else if(op.getLabel() == Label::PLUS){
                saldo += op.getValor();
            }
        }
        return saldo;
    }

    string str() const {
        stringstream ss;
        ss << nome << " " << getSaldo() << "/" << limite;
        return ss.str();
    }
};

class Agiota {
    list<Cliente> Vivos;
    list<Cliente> Mortos;
    list<Operacao> opVivo; // Lista global de operações
    int nextId;

public:
    Agiota() : nextId(0) {}

    void addCli(string nome, int limite) {
        for (const auto& cliente : Vivos) {
            if (cliente.getNome() == nome) {
                cout << "fail: cliente ja existe" << endl;
                return;
            }
        }
         Vivos.push_back(Cliente(nome, limite));
    }

    void give(string nome, int value) {
        for (auto& cliente : Vivos) {
            if (cliente.getNome() == nome) {
                if (cliente.getSaldo() + value > cliente.getLimite()) {
                    cout << "fail: limite excedido" << endl; // Corrigido para "limite"
                    return;
                }
                Operacao op(nextId, nome, Label::GIVE, value);
                cliente.addOperacao(op); // Adiciona ao cliente
                opVivo.push_back(op);     // Adiciona à lista global
                nextId++;
                return;
            }
        }
        cout << "fail: cliente nao existe" << endl; // Corrigido para "fail"
    }

    void take(string nome, int value){
        for(auto& cliente: Vivos){
                if(cliente.getNome() == nome){
                Operacao op(nextId, nome, Label::TAKE, value);
                cliente.addOperacao(op);
                opVivo.push_back(op);
                nextId++;
                return;
                }
        }
        cout << "fail: cliente nao existe" << endl;
    }
    void showCli(string nome){
        for(auto& cliente: Vivos){
            if(cliente.getNome() == nome){
                cout << cliente.str() << endl;
                for(auto& op: cliente.getOperacoes()){
                    cout << "id:" << op.getId() << " " << op.str() << endl;
                }
                return;
            }
        }
        cout << "fail: cliente nao existe" << endl;
    }
    void kill(string nome){
        for(auto it = Vivos.begin(); it != Vivos.end(); it++){
            if(it->getNome() == nome){
                Mortos.push_back(*it);
            opVivo.remove_if([&](const Operacao& op) {
                return op.getNome() == nome;
            });
            Vivos.erase(it); // Remove o cliente da lista de Vivos
            return;
            }
        }
}
    void plus() {
        vector<Cliente> clientesOrdenados(Vivos.begin(), Vivos.end());
        
        // Ordena os clientes vivos em ordem alfabética pelo nome
        sort(clientesOrdenados.begin(), clientesOrdenados.end(), [](const Cliente& a, const Cliente& b) {
            return a.getNome() < b.getNome();
        });
        for (auto& cliente : clientesOrdenados) {
            int valor = cliente.getSaldo() * 0.1; // 10% do saldo atual
            Operacao op(nextId, cliente.getNome(), Label::PLUS, valor);
            
            // Atualiza o cliente real em Vivos
            for (auto& realCliente : Vivos) {
                if (realCliente.getNome() == cliente.getNome()) {
                    realCliente.addOperacao(op);
                    break;
                }
            }
            opVivo.push_back(op);
            nextId++;
        }
}
    string str() const {
        stringstream ss;
        vector <Cliente> clientesOrdenados(Vivos.begin(), Vivos.end());
        sort(clientesOrdenados.begin(), clientesOrdenados.end(), [](auto a, auto b) {
            return a.getNome() < b.getNome();
        });
        // Exibe clientes vivos
        for (const auto& cliente : clientesOrdenados) {
            ss << ":) " << cliente.str() << endl;
        }

        // Exibe operações na ordem global
        for (const auto& op : opVivo) {
            ss << "+ id:" << op.getId() << " " << op.str() << endl;
        }
        vector <Cliente> clientesOrdenadosMortos(Mortos.begin(), Mortos.end());
        sort(clientesOrdenadosMortos.begin(), clientesOrdenadosMortos.end(), [](auto a, auto b) {
            return a.getNome() < b.getNome();
        });
        for(const auto& cliente: clientesOrdenadosMortos){
            ss << ":( " << cliente.str() << endl;
        }
        for(const auto& cliente: Mortos){
            for(const auto& op: cliente.getOperacoes()){
                ss << "- id:" << op.getId() << " " << op.str() << endl;
            }
        }

        return ss.str();
    }
};


int main() {
    Agiota agiota;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        }
        else if (cmd == "addCli") {
            string name;
            int limite {};
            ss >> name >> limite;
            agiota.addCli(name, limite);
        }
        else if (cmd == "show") {
            cout << agiota.str();
        }
        else if (cmd == "showCli") {
             string name;
             ss >> name;
             agiota.showCli(name);
        }
        else if (cmd == "kill") {
             string name;
             ss >> name;
             agiota.kill(name);
        }
        else if (cmd == "give") {
            string name;
            int value;
            ss >> name >> value;
            agiota.give(name, value);
        }
        else if (cmd == "take") {
             string name;
             int value;
             ss >> name >> value;
             agiota.take(name, value);
        }
        else if (cmd == "plus") {
             agiota.plus();
        }
        else {
            cout << "fail: comando invalido\n";
        }
    }
}