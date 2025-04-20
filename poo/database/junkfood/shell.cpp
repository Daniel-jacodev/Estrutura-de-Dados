#include <iostream>
#include <vector>
#include <sstream>
#include <utility>
#include <iomanip>  //setw(tamanho), setfill('0'), left, right
using namespace std;

template<typename CONTAINER, typename FUNC>
string map_join(const CONTAINER& cont, FUNC func, string delim) {
    stringstream ss;
    for (auto it = cont.begin(); it != cont.end(); it++) {
        ss << (it == cont.begin() ? "" : delim);
        ss << func(*it);
    }
    return ss.str();
}
class Espiral{
    private:
        string nome;
        int qtd;
        double preco;
    public:
        Espiral(string nome, int qtd, double preco) : 
            nome(nome), qtd(qtd), preco(preco){}
        string getNome(){
            return nome;
        }
        int getQtd(){
            return qtd;
        }
        double getPreco(){
            return preco;
        }
        void setNome(string nome){
            this->nome = nome;
        }
        void setQtd(int qtd){
            this->qtd = qtd;
        }
        void setPreco(double preco){
            this->preco = preco;
        }

        string str(){
            stringstream ss;

            ss << "[" << setw(8) << setfill(' ') << nome 
            << " : " << qtd << " U : " << fixed
            << setprecision(2) << preco << " RS]";
            return ss.str();
        }
};
class Maquina{
    private:
        double saldo;
        double lucro;
        vector <Espiral> espirais;
    public:
        Maquina(int n_espirais){
            espirais = vector <Espiral> (n_espirais, Espiral("empty", 0, 0));
            saldo = 0;
            lucro = 0;
        }
        void setEspiral(size_t indice, string nome, double preco, int qtd){
            if(indice > espirais.size()){
                cout << "fail: indice nao existe" << endl;
                return;
            }
            else{
                espirais[indice] = Espiral(nome, qtd, preco);
            }
        }
        void limpar(int indice){
            espirais[indice] = Espiral("empty", 0, 0);

        }
        void butarDenhero(int value){
            saldo += value;
        }
        void troco(){
            cout << "voce recebeu "  << fixed << setprecision(2) << saldo << " RS" << endl;
            saldo = 0;
        }
        void comprar(int indice){
            if(indice > (int) espirais.size()){
                cout << "fail: indice nao existe" << endl;
                return;
            }
            else if(saldo < espirais[indice].getPreco()){
                cout << "fail: saldo insuficiente" << endl;
                return;
            }
            else if(espirais[indice].getQtd() == 0){
                cout << "fail: espiral sem produtos" << endl;
                return;
            }
            else{
                cout << "voce comprou um " << espirais[indice].getNome() << endl;
                saldo -= espirais[indice].getPreco();
                espirais[indice].setQtd(espirais[indice].getQtd() - 1);
            }

        }

        string str(){
            stringstream ss;
            ss << "saldo: " << fixed << setprecision(2) << saldo << endl;
            for(size_t i = 0 ; i < espirais.size(); i++){
                ss << i << " " << espirais[i].str() << endl;
            }
            string saida = ss.str();
            saida.pop_back();
            return saida;
        }
};

int main() {
    Maquina maquina(4);
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        try {
            if (cmd == "show") {
                // IMPRIMIR
                cout << maquina.str() << endl;
            } else if (cmd == "init") {
                 int n_espirais {};
                 ss >> n_espirais;
                 maquina = Maquina(n_espirais);
            } else if (cmd == "limpar") {
                 int indice {};
                 ss >> indice;
                 maquina.limpar(indice);
            } else if (cmd == "dinheiro") {
                 int value {};
                 ss >> value;
                 maquina.butarDenhero(value);
            } else if (cmd == "comprar") {
                 int index {};
                 ss >> index;
                 maquina.comprar(index);
            } else if (cmd == "set") {
                 int index {};
                 string name;
                 int qtd {};
                 double price {};
                 ss >> index >> name >> qtd >> price;
                 maquina.setEspiral(index, name, price, qtd);
            } else if (cmd == "troco") {
                maquina.troco();
            } else if (cmd == "end") {
                break;
            } else {
                cout << "comando invalido" << endl;
            }
        } catch (const char* e) {
            cout << e << endl;
        }
    }
    return 0;
}
