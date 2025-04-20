#include <iostream>
#include <sstream>
#include <memory>
#include <algorithm>

class Bateria {
private:
    int capacidade{0};
    int carga{0};

public:
    Bateria(int capacidade, int carga = 0) : capacidade(capacidade) {
        if (carga == 0) {
            carga = capacidade;
        }
        this->carga = carga;
    }

    int getCapacidade() const {
        return capacidade;
    }

    int getCarga() const {
        return carga;
    }

    void usarCarga(int minutos) {
        if (carga >= minutos) {
            carga -= minutos;
        } else {
            carga = 0;
        }
    }

    bool estaVazia() const {
        return carga <= 0;
    }

    void carregarBateria(int minutos) {
        carga = std::min(capacidade, carga + minutos);
    }

    std::string str() const {
        std::stringstream ss;
        ss << "(" << carga << "/" << capacidade << ")";
        return ss.str();
    }

    void mostrar() const {
        std::cout << str() << std::endl;
    }
};

class Carregador {
private:
    int potencia{0};

public:
    Carregador(int potencia = 0) : potencia(potencia) {}

    int getPotencia() const {
        return potencia;
    }

    void carregarBateria(std::shared_ptr<Bateria> bateria, int minutos) {
        if (bateria) {
            bateria->carregarBateria(minutos);
        }
    }

    std::string str() const {
        std::stringstream ss;
        ss << potencia;
        return ss.str();
    }

    void mostrar() const {
        std::cout << "(Potência " << str() << ")" << std::endl;
    }
};

class Notebook {
private:
    bool ligado = false;
    std::shared_ptr<Bateria> bateria;
    std::shared_ptr<Carregador> carregador;

public:
    Notebook() : ligado{false}, bateria(nullptr), carregador(nullptr) {}

    void setBateria(std::shared_ptr<Bateria> bat) {
        bateria = bat;
    }

    void setCarregador(std::shared_ptr<Carregador> ch) {
        carregador = ch;
    }

    void ligar() {
        if (ligado) {
            std::cout << "Notebook já está ligado.\n";
        } else if (!bateria || bateria->estaVazia()) {
            std::cout << "Não foi possível ligar\n";
        } else {
            ligado = true;
            std::cout << "Notebook ligado.\n";
        }
    }

    void desligar() {
        if (ligado) {
            std::cout << "Notebook desligado.\n";
            ligado = false;
        } else {
            std::cout << "Notebook já está desligado.\n";
        }
    }

    void usar(int tempo) {
        if (!ligado) {
            std::cout << "Notebook desligado.\n";
            return;
        }

        if (!bateria || bateria->estaVazia()) {
            std::cout << "Notebook descarregou e foi desligado.\n";
            desligar();
            return;
        }

        int usoReal = std::min(tempo, bateria->getCarga());
        bateria->usarCarga(usoReal);
        std::cout << "Usando por " << usoReal << " minutos.\n";

        if (bateria->estaVazia()) {
            std::cout << "Notebook descarregou e foi desligado.\n";
            desligar();
        }
    }

    std::shared_ptr<Bateria> rmBateria() {
        if (!bateria) {
            std::cout << "Nenhuma bateria para remover.\n";
            return nullptr;
        }

        auto removedBattery = bateria;
        bateria = nullptr;
        if (ligado) {
            desligar();
        }
        std::cout << "Bateria removida.\n";
        return removedBattery;
    }

    void mostrar() const {
        std::cout << "Status: " << (ligado ? "Ligado" : "Desligado");
        if (bateria) {
            std::cout << ", Bateria: " << bateria->str();
        } else {
            std::cout << ", Bateria: Nenhuma";
        }
        if (carregador) {
            std::cout << ", Carregador: (Potência " << carregador->str() << ")" << std::endl;
        } else {
            std::cout << ", Carregador: Desconectado\n";
        }
    }
};

int main() {
    Notebook notebook;
    notebook.mostrar();
    notebook.ligar();
    notebook.usar(10);

    auto bateria = std::make_shared<Bateria>(50); 
    bateria->mostrar();
    
    notebook.setBateria(bateria);
    notebook.mostrar();
    notebook.ligar();
    notebook.mostrar();
    notebook.usar(30);
    notebook.mostrar();
    notebook.usar(30);
    notebook.mostrar();
    
    auto removedBattery = notebook.rmBateria();
    removedBattery->mostrar();
    notebook.mostrar();

    auto carregador = std::make_shared<Carregador>(2);
    carregador->mostrar();

    notebook.setCarregador(carregador);
    notebook.mostrar();
    notebook.ligar();
    notebook.mostrar();
    notebook.setBateria(bateria);
    notebook.mostrar();
    notebook.usar(10);
    notebook.mostrar();

    return 0;
}

