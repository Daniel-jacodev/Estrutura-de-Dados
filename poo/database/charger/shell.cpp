#include <iostream>
#include <sstream>
#include <memory>
#include <utility>
using namespace std;
    class Carregador{
        bool carregador = false;
        int potencia = 0;
        public:
        bool getCarregador() const{
            return this->carregador;
        }
        int getPotencia() const{
            return this->potencia;
        }
        void setPotencia(int potencia){
            this->potencia = potencia;
        }

        string str() const {
        stringstream ss;
        ss << potencia;
        return ss.str();
    }
    };

    class Bateria{
        bool bateria = false;
        int charge;
        int chargeMax;
        public:
        bool getBateria() const{
            return this->bateria;
        }
        void setBateria(bool bateria){
            this->bateria = bateria;
        }
        int getCharge() const{
            return this->charge;
        }
        void setCharge(int charge) {
            this->charge = charge;
        }
        int getChargeMax() const{
            return this->chargeMax;
        }
        void setChargeMax(int chargeMax){
            this->chargeMax = chargeMax;
        }

        string str() const {
        stringstream ss;
        ss << charge << "/" << chargeMax;
        return ss.str();
        }
    };

    class Notebook{
        bool ligado = false;
        int minutos = 0;
        shared_ptr <Bateria> bateria;
        shared_ptr <Carregador> carregador;
        public:
    Notebook() : bateria(make_shared<Bateria>()), carregador(make_shared<Carregador>()) {}

        void ligar () {
            if ((bateria && bateria->getCharge() != 0) || (carregador && carregador->getPotencia())) {
            ligado = true;
            } else {
                cout << "fail: não foi possível ligar" << endl;
            }
        }

        void desligar(){
            if(ligado == true){
                ligado = false;
            }
            else{
                cout << "fail: ja esta desligado" << endl;
            }
        }

        void usar(int minutos){
            if(ligado){
                this->minutos += minutos;
                if(carregador->getPotencia() == 0){
                    bateria->setCharge(bateria->getCharge() - minutos);
                    if(bateria->getCharge() <= 0){
                        cout << "fail: descarregou" << endl;
                        ligado = false;
                        while(bateria->getCharge() < 0){
                        bateria->setCharge(bateria->getCharge() + 1);
                        }
                    }
                }else{
                    bateria->setCharge(bateria->getCharge() + minutos*carregador->getPotencia());
                    if(bateria->getCharge() > bateria->getChargeMax()){
                        bateria->setCharge(bateria->getCharge() - 5);
                    }
                }
            }else{
                cout << "fail: desligado" << endl;
            }
        }
       void adicionarCarregador(int potencia){
            if(carregador && carregador->getPotencia() != 0){
                cout << "fail: carregador já conectado" << endl;
            }else{
                carregador->setPotencia(potencia);
            }
        }
        void retirarCarregador(){
            if(carregador && carregador->getPotencia() != 0){
                cout << "Removido " << carregador->getPotencia() << "W" << endl;;
               // carregador = nullptr;
                while(carregador->getPotencia() > 0){
                    carregador->setPotencia(carregador->getPotencia() - 1);
                }
                ligado = false;
                minutos = 0;
            }else{
                cout << "fail: Sem carregador" << endl;
            }
        }
        void adicionarBateria(int charge){
            if(bateria && bateria->getCharge() != 0){
                cout << "fail: bateria ja conectada" << endl;
            }else{
                bateria->setCharge(charge);
                bateria->setChargeMax(charge);
               // bateria->getChargeMax(charge);
            }
        }
        void retirarBateria(){
            if (bateria && bateria->getChargeMax() != 0){
                cout << "Removido " << bateria->getCharge() << "/" << bateria->getChargeMax() << endl;
                while(bateria->getCharge() > 0){
                    bateria->setCharge(bateria->getCharge() - 1);
                }
                while(bateria->getChargeMax() > 0){
                    bateria->setChargeMax(bateria->getChargeMax() - 1);
                }
                if(carregador->getPotencia() == 0){
                    ligado = false;
                    minutos = 0;
                }
            }else{
                cout << "fail: Sem bateria" << endl;
            }
        }
        string str() const{
            stringstream ss;
            ss << "Notebook: ";
            if(!ligado){
                ss << "desligado";
            }else{
                ss << "ligado" << " por " << minutos << " min";
            }
            if(carregador && carregador->getPotencia() != 0){
                ss << ", Carregador " << carregador->getPotencia() << "W";
            }
            if(bateria->getChargeMax() != 0){
                ss << ", Bateria " << bateria->getCharge() << "/" << bateria->getChargeMax();
            }
            return ss.str();
        }
    };
int main() {
    Notebook notebook;
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
            cout << notebook.str() << endl;
        } 
        else if (cmd == "turn_on") {
            notebook.ligar();
         }
         else if (cmd == "turn_off") { 
            notebook.desligar();
         } 
         else if (cmd == "use") { 
             int minutes;
             ss >> minutes;
             notebook.usar(minutes);
         } 
         else if (cmd == "set_charger") {
             // CRIE UM OBJETO Charger E ATRIBUA AO NOTEBOOK
             int power;
             ss >> power;
             notebook.adicionarCarregador(power);
         } 
         else if (cmd == "rm_charger") {
        //      REMOVA O CARREGADOR DO NOTEBOOK E IMPRIMA SE ELE EXISTIR
                notebook.retirarCarregador();
         } 
         else if (cmd == "set_battery") {
        //     // CRIE UM OBJETO Bateria E ATRIBUA AO NOTEBOOK
             int capacity;
             ss >> capacity;
             notebook.adicionarBateria(capacity);
         } 
         else if (cmd == "rm_battery") {
        //     // REMOVA A BATERIA DO NOTEBOOK E IMPRIMA SE ELA EXISTIR
         notebook.retirarBateria();
         } 
        else {
            cout << "fail: comando inválido\n";
        }
    }    
}
