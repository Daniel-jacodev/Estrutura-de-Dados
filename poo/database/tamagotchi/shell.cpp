#include <iostream>
#include <sstream>
#include <string>
#include <memory>
using namespace std;
    class Pet{
        int energyMax;
        int cleanMax;
        int energy;
        int clean;
        int age;
        bool vivo;
        public:
        Pet(int energyMax, int cleanMax){
            this->energyMax = energyMax;
            this->cleanMax = cleanMax;
            energy = energyMax;
            clean = cleanMax;
            age = 0;
            vivo = true;
        }
        int getEnergyMax () const{
            return this->energyMax;
        }
        int getEnergy() const {
            return this->energy;
        }
        int getCleanMax() const{
            return this->cleanMax;
        }
        int getClean () const{
            return this->clean;
        }
        int getAge() const {
            return this->age;
        }
        void setEnergy(int energy){
            this->energy = energy;
        }
        void setClean(int clean){
            this->clean = clean;
        }
        void setAge(int age){
            this->age = age;
        }
    };
    class Game{
        shared_ptr <Pet> pet = nullptr;
        public:
        void init (int energyMax, int cleanMax) {
            pet = make_shared<Pet>(energyMax, cleanMax);
        }
        void play(){
            //grafite->setTamanho(grafite->getTamanho() - 1);
            if(pet->getClean() > 0 && pet->getEnergy() > 0)
            {
                pet->setEnergy(pet->getEnergy() - 2);
                pet->setClean(pet->getClean() - 3);
                pet->setAge(pet->getAge() + 1);
                if(pet->getClean() <= 0){
                    cout << "fail: pet morreu de sujeira" << endl;
                }
                if(pet->getEnergy() <= 0){
                    cout << "fail: pet morreu de fraqueza" << endl;
                    pet->setEnergy(pet->getEnergy() + 1);
                }
            }
            else{
                cout << "fail: pet esta morto" << endl;
            }
        }
        void banhar(){
            if(pet->getClean() > 0 && pet->getEnergy() > 0)
            {
                pet->setEnergy(pet->getEnergy() - 3);
                pet->setAge(pet->getAge() + 2);
                while (pet->getClean() < pet->getCleanMax())
                    {
                        pet->setClean(pet->getClean() + 1);
                    }
                if(pet->getClean() <= 0){
                    cout << "fail: pet morreu de sujeira" << endl;
                }
            }else{
                cout << "fail: pet esta morto" << endl;
            }
        }
        void mimir(){
            if(pet->getClean() > 0 && pet->getEnergy() > 0){
                int newEnergyMax = pet->getEnergyMax() - 5;
                if(pet->getEnergy() > newEnergyMax){
                    cout <<"fail: nao esta com sono" << endl;
                }else{
                    while (pet->getEnergy() < pet->getEnergyMax())
                    {
                        pet->setEnergy(pet->getEnergy() + 1);
                        pet->setAge(pet->getAge() + 1);
                    }
                }
            }else{
                cout << "fail: pet esta morto" << endl;
            }
            
        }
        string str() const{
            stringstream ss;
            ss << "E:" << pet->getEnergy() << "/" << pet->getEnergyMax() << ", L:" <<
            pet->getClean() << "/" << pet->getCleanMax() << ", I:" << pet->getAge();
            return ss.str();
        }

    };


int main() {
    Game game;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;
        if (cmd == "end") {
            break;
        } 
         else if (cmd == "init") {
         // CRIE UM NOVO JOGO COM UM NOVO PET
             int energy, clean;
             ss >> energy >> clean;
             game.init(energy, clean);
         }
         else if (cmd == "show") {
            cout << game.str() << endl;
        } 
         else if (cmd == "play") { 
            game.play();
         } 
         else if (cmd == "shower") { 
            game.banhar();
         } 
        // else if (cmd == "eat") { 
        // } 
         else if (cmd == "sleep") { 
            game.mimir();
         } 
        else {
            cout << "fail: comando invalido" << endl;
        }
    }
    return 0;
}
