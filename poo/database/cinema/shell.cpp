#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
using namespace std;

template<class CONTAINER, class FUNC>
string map_join(const CONTAINER& c, FUNC f, string sep) {
    stringstream ss;
    for (auto it = c.begin(); it != c.end(); it++) {
        ss << (it == c.begin() ? "" : sep);
        ss << f(*it);
    }
    return ss.str();
}

class Cliente{
    string id;
    int phone;
    public:
        Cliente(string id, int phone) : id(id), phone(phone) {}
        int getPhone(){
            return phone;
        }
        void setPhone(int phone){
            this->phone = phone;
        }
        string getId(){
            return id;
        }
        void setId(string id){
            this->id = id;
        }
        string str(){
            stringstream ss;
            ss << id << ":" << phone;
            return ss.str();
        }
};

class Sala{
    vector <Cliente> clientes;
    bool confere = false;
    int qtd;
    public:
        Sala(int qtd) : qtd(qtd) {
            clientes = vector <Cliente> (qtd, Cliente("-", 0));
        }

    void reservar(string id, int phone, int index){
        if(index < 0 || index >= qtd){
            cout << "fail: cadeira nao existe" << endl;
            return;
        }
        else if(clientes[index].getId() != "-"){
            cout << "fail: cadeira ja esta ocupada" << endl;
            return;
        }
        for(size_t i = 0; i < clientes.size(); i++){
            if(clientes[i].getId() == id){
                cout << "fail: cliente ja esta no cinema" << endl;
                return;
            }
        }
        clientes[index] = Cliente(id, phone);
        clientes[index].setId(clientes[index].getId() = id);
    }
    void cancelar(string id){
        for(size_t i = 0; i < clientes.size(); i++){
            if(clientes[i].getId() == id){
                clientes[i].setId(clientes[i].getId() = "-");
                clientes[i].setPhone(0);
                confere = true;
            }
    }
            if(confere == false){
            cout << "fail: cliente nao esta no cinema" << endl;
            return;
        }
        confere = false;
    }


        string str(){
            stringstream ss;
            ss << "[";
            if(clientes.size() > 0){
                for (size_t i = 0; i < clientes.size(); i++) {
                    if(i == clientes.size() - 1 && clientes[i].getId() != "-"){
                        ss << clientes[i].str();
                        break;
                    }
                    if(i == clientes.size() - 1 && clientes[i].getId() == "-"){
                        ss << "-";
                        break;
                    }
                    if (clientes[i].getId() == "-") {
                        ss << "- ";
                    } else {
                        ss  << clientes[i].str() << " ";
                    }
                }
       //     if (clientes.back().getId() == "-") {
         //               ss << "-";
               // } else {
                 //       ss << clientes.back().str();
             //   }
        }
            ss << "]";
            return ss.str();
        }
};


int main() {
    Sala sala(0);
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;    
        } else if (cmd == "show") {
            cout << sala.str() << endl;
        } else if (cmd == "init") {
            int qtd;
            ss >> qtd;
            sala = Sala(qtd);
        } else if (cmd == "reserve") {
             string id, phone;
             int index;
             ss >> id >> phone >> index;
             sala.reservar(id, stoi(phone), index);
        } else if (cmd == "cancel") {
            string id;
             ss >> id;
                sala.cancelar(id);
        } else {
            cout << "fail: comando invalido" << endl;
        }
    }
}
