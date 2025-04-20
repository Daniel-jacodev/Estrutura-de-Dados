

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <memory>
#include <algorithm>
using namespace std;

// Classe base que o sena explicou
struct Veiculo {
    string id;
    string tipo;
    int horaEntrada;

    Veiculo(string id = "", string tipo = "", int horaEntrada = 0)
        : id(id), tipo(tipo), horaEntrada(horaEntrada) {}

    virtual ~Veiculo() {}

    string getId() const {
        return id;
    }

    string getTipo() const {
        string tipoFormatado = tipo;
        if (!tipoFormatado.empty()) {
            tipoFormatado[0] = toupper(tipoFormatado[0]);
        }
   return tipoFormatado;
    }

    int getHoraEntrada() const {
        return horaEntrada;
    }

    void setEntrada(int horaEntrada) {
        this->horaEntrada = horaEntrada;
    }

    virtual double calcularValor(int horaSaida) const = 0;

    string toString() const {
        stringstream ss;
        string tipoFormatado = tipo;
        if (!tipoFormatado.empty()) {
            tipoFormatado[0] = toupper(tipoFormatado[0]);
        }
        ss << setw(10) << setfill('_') << tipoFormatado << " : " << setw(10) << setfill('_') << id << " : " << horaEntrada;
        return ss.str();
    }
};

// Classe Bike
struct Bike : Veiculo {
    Bike(string id = "") : Veiculo(id, "bike", 0) {}

    double calcularValor(int horaSaida) const override {
        (void)horaSaida; 
        return 3.00; 
    }
};

// Classe Moto
struct Moto : Veiculo {
    Moto(string id = "") : Veiculo(id, "moto", 0) {}

    double calcularValor(int horaSaida) const override {
        int tempoPermanencia = horaSaida - getHoraEntrada();
        return static_cast<double>(tempoPermanencia) / 20.0;
    }
};

// Classe Carro
struct Carro : Veiculo {
    Carro(string id = "") : Veiculo(id, "carro", 0) {}

    double calcularValor(int horaSaida) const override {
        int tempoPermanencia = horaSaida - getHoraEntrada();
        double valor = static_cast<double>(tempoPermanencia) / 10.0;
        return max(valor, 5.00); 
    }
};

// Classe Estacionamento
struct Estacionamento {
    vector<shared_ptr<Veiculo>> veiculos;
    int horaAtual;

    Estacionamento(int horaAtual = 0) : horaAtual(horaAtual) {}

    int procurarVeiculo(string id) {
        for (size_t i = 0; i < veiculos.size(); i++) {
            if (veiculos[i]->getId() == id) {
                return i;
            }
        }
        return -1;
    }

    void estacionar(shared_ptr<Veiculo> veiculo) {
        if (procurarVeiculo(veiculo->getId()) == -1) {
            veiculo->setEntrada(horaAtual);
            veiculos.push_back(veiculo);
        } else {
            cout << "fail: veiculo ja esta no estacionamento" << endl;
        }
    }

    void pagar(string id) {
        int index = procurarVeiculo(id);
        if (index != -1) {
            auto veiculo = veiculos[index];
            double valor = veiculo->calcularValor(horaAtual);
            cout << veiculo->getTipo() << " chegou " << veiculo->getHoraEntrada() << " saiu " << horaAtual
                 << ". Pagar R$ " << fixed << setprecision(2) << valor << endl;
            veiculos.erase(veiculos.begin() + index);
        } else {
            cout << "fail: veiculo nao encontrado" << endl;
        }
    }
    void show() const{
        for (const auto& veiculo : veiculos) {
            cout << veiculo->toString() << endl;
        }
        cout << "Hora atual: " << horaAtual << endl;
    }
};

int main() {
    Estacionamento estacionamento;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "show") {
            estacionamento.show();
        } else if (cmd == "estacionar") {
            string tipo, id;
            ss >> tipo >> id;
            shared_ptr<Veiculo> veiculo;
            if (tipo == "bike") {
                veiculo = make_shared<Bike>(id);
            } else if (tipo == "moto") {
                veiculo = make_shared<Moto>(id);
            } else if (tipo == "carro") {
                veiculo = make_shared<Carro>(id);
            } else {
                cout << "fail: tipo de veiculo invalido" << endl;
                continue;
            }
            estacionamento.estacionar(veiculo);
        } else if (cmd == "tempo") {
            int tempo;
            ss >> tempo;
            estacionamento.horaAtual += tempo;
        } else if (cmd == "pagar") {
            string id;
            ss >> id;
            estacionamento.pagar(id);
        } else {
            cout << "fail: comando invalido" << endl;
        }
    }
}