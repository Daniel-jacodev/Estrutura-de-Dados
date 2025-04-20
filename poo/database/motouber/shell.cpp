#include <iostream>
#include <sstream>
#include <memory>
using namespace std;
    class Pessoa{
        int dinheiro;
        string nome;
        public:
        string getNome () const{
            return this->nome;
        }
        int getDinheiro(){
            return this->dinheiro;
        }
        void setNome(string nome){
            this->nome = nome;
        }
        void setDinheiro(int dinheiro){
            this->dinheiro = dinheiro;
        }
    };
    class Moto{
        //declarar variaveis
        string name;
        int money;
        int custo;
        shared_ptr <Pessoa> pessoa = nullptr;
        public:
            //construtor
            Moto(){
                name = "";
                money = 0;
                custo = 0;
            }
            //função de definir motorista
            void setMoto(string name, int money){
                if(!this->name.empty()){
                    cout << "fail: ja tem motorista" << endl;
                }else{
                        this->name = name;
                        this->money = money;
                }
            }
            //função de definir passageiro
            void setPass(string nome, int dinheiro){
                if(pessoa == nullptr){
                    pessoa = make_shared<Pessoa>();
                    pessoa->setNome(nome);
                    pessoa->setDinheiro(dinheiro);
                }else{
                    cout << "fail: ja tem passageiro" << endl;
                }
            }
            //função de dirigir
            void dirigir(int custo){
            if (pessoa == nullptr) {
                cout << "fail: no passenger" << endl;
            return;
        }
                this->custo += custo;

            }
        
        void leavePass() {
            if (pessoa == nullptr) {
                cout << "fail: no passenger" << endl;
                return;
            }
            if(custo > pessoa->getDinheiro()){
                cout << "fail: Passenger does not have enough money" << endl;;
            }
    
            int dinheiroPassageiro = pessoa->getDinheiro();
            int valorPago = min(dinheiroPassageiro, custo);

            pessoa->setDinheiro(dinheiroPassageiro - valorPago);
            money += valorPago;

            cout << pessoa->getNome() << ":" << valorPago << " left" << endl;

            pessoa = nullptr;
            custo = 0;
        }
                
            // pegar a função str dos dados
            string str() const {
                stringstream ss;
                ss << "Cost: " << custo << ", Driver: ";
                    if (name.empty()) {
                        ss << "None" << ", Passenger: ";
                        if(pessoa == nullptr) {
                            ss << "None";
                        }
                        else{
                            ss << pessoa->getNome();
                        }
                    }else{
                        ss << name << ":" << money << ", Passenger: " ;
                        if (pessoa == nullptr) {
                            ss << "None";
                        }
                        else{
                            ss << pessoa->getNome() << ":" << pessoa->getDinheiro();
                        }
                    }
            return ss.str();
            }
        };

int main() {
    Moto moto;
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
            cout << moto.str() << endl;
         }
         else if (cmd == "setDriver") { 
             string name;
             int money;
             ss >> name >> money;
             moto.setMoto(name, money);
         }
         else if (cmd == "setPass") { 
             string name;
             int money;
             ss >> name >> money;
             moto.setPass(name, money);
         }
         else if (cmd == "drive") { 
             int distance;
             ss >> distance;
             moto.dirigir(distance);
         }
         else if (cmd == "leavePass") {
            moto.leavePass();
         }
        else {
            cout << "fail: command not found\n";
        }
    }
}
