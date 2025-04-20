#pragma once
#include "fn.hpp"
using namespace std;

struct Animal {
    string especie;
    string barulho;
    int estagio;

    Animal(string especie = "", string barulho = ""):
        especie(especie), barulho(barulho), estagio(0) {
    }

    string fazerBarulho() const {
        if (estagio == 0) {
            return "---";
        }
        else if (estagio == 4) {
            return "RIP";
        }
        return this->barulho;
    }

    void envelhecer(int nivel) {
        estagio += nivel;
        if (estagio >= 4) {
            cout << "warning: " << especie << " morreu" << endl;
            estagio = 4;
        }
    }

    string str() const {
        return fn::format("{}:{}:{}", especie, estagio, barulho);
    }
};

//inline ostream& operator<<(std::ostream& os, const Animal& animal) {
  //  return os << animal.str();
// }

struct Student {
    Animal animal;
    Student(string especie = "", std::string barulho = "") {
        (void) especie;
        (void) barulho;
        animal = Animal(especie, barulho);
    }

    void grow(int nivel) {
        (void) nivel;
        animal.envelhecer(nivel);
    }

    void noise() {
        cout << animal.fazerBarulho() << std::endl;
    }

    void show() {
        cout << animal.str() << std::endl;
    }
};

struct Debug {
    static const bool debug = false;
    static void run() {
        cout << "Debug ativado" << std::endl;
    }
};
