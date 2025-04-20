#include <iostream>
#include <vector>
#include <sstream>
using namespace std;
class Camisa {
    string tamanho;
public:

    Camisa() {
        this->tamanho = "";  
    }

 
    string getTamanho() {
        return tamanho;
    }


    void setTamanho(string tamain) {
       
        if (tamain == "PP" || tamain == "P" || tamain == "M" || tamain == "G" || tamain == "GG" || tamain == "XG") {
            tamanho = tamain;
        } else {
            cout << "fail: Valor inválido, tente PP, P, M, G, GG ou XG" << endl;
        }
    }
    string str() const {
    std::stringstream ss;
    ss << "size: (" << this->tamanho << ")";
    return ss.str();
    } 
};
int main() {
    Camisa camisa;
    string tamnho;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "size") { // TENTE ATRIBUIR UM TAMANHO
            string tamanho;
            ss >> tamanho;
            camisa.setTamanho(tamanho);
        } else if (cmd == "show") { // MOSTRE AS INFORMAÇÕES DO OBJETO
         cout << camisa.str() << endl;
        } else if (cmd == "end") {
            break;
        } else {
            cout << "fail: Comando inválido" << endl;
        }
    }
}
