#include <iostream> // fixed, cout, endl, string
#include <sstream> // stringstream
#include <iomanip> // setprecision
using namespace std;

class Calculadora{
    int bateria;
    int batteryMax;
    float display;
    public:
    //Construtor para inicializar os valores
    Calculadora(int batteryMax)
    {
        this->bateria = 0;
        this->batteryMax = batteryMax;
        this->display = 0.00;
    }
    //função para carregar a calculadora
        void charge(int carga)
    {
        bateria += carga;
        if(bateria > batteryMax){
            bateria = batteryMax;
        }
    }
    //agr vou fazer a função para somar 
    void sum(int a, int b){
        if(bateria == 0){
           cout << "fail: bateria insuficiente" << endl;
        }
        else{
            display = a + b;
            bateria -= 1;
        }
    }
    void div(float num, float den){
        if(bateria == 0){
           cout << "fail: bateria insuficiente" << endl;
           bateria = 0;
        }
        if (den <= 0){
            cout << "fail: divisao por zero" << endl;
            bateria -= 1;
        }
        else{
            if(bateria > 0){
            display = num / den;
            bateria -= 1;
            }
            if(bateria < 0){
                bateria = 0;
            }
        }
    }

  
    string str() const {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << "display = " << this->display << ", battery = " << this->bateria;
    return ss.str();
    } 

};

int main() {
    Calculadora calculadora(100); // Inicializa com bateria máxima igual a 0


    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << '\n';

        stringstream par(line);
        par >> cmd;

        if (cmd == "end") {
            break;
        } 
        else if (cmd == "init") {
            int batteryMax {};
            par >> batteryMax;
            calculadora = Calculadora(batteryMax);
        } 
        else if (cmd == "show") {
            cout << calculadora.str() << endl;
        } 
        else if (cmd == "charge") {
            int carga {};
            par >> carga;
            calculadora.charge(carga);
        } 
        else if (cmd == "sum") {
            // SOMAR
            int a {}, b {};
            par >> a >> b;
            calculadora.sum(a, b);
        } 
        else if (cmd == "div") {
            // DIVIDIR
            float num {}, den {};
            par >> num >> den;
            calculadora.div(num, den);
        } 
        else {
            cout << "fail: comando invalido" << endl;
        }
    }


}
