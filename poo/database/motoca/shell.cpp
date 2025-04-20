#include <iostream>
#include <memory> //shared_ptr
#include <sstream> //stringstream
#include <utility> //exchange
using namespace std;
class Pessoa{
    string nome;
    int idade;
    public:
    Pessoa(string nome, int idade): nome(nome), idade(idade){}
    string getNome() const{
        return this->nome;
    }
    int getIdade() {
        return this->idade;
    }
    string str() const{
        stringstream dd;
        dd << "(" << nome << ":" << idade << ")";
        return dd.str();
    }
};
ostream& operator << (ostream &os, const Pessoa& pessoa){
    return os << pessoa.str();
}
class Moto{
    int potencia{1};
    int tempo{0};
    shared_ptr<Pessoa> pessoa = nullptr;
    public:
    void inserir(shared_ptr<Pessoa> pessoa){
        if(this->pessoa == nullptr){
            this->pessoa = pessoa;
        }else{
            cout << "fail: busy motorcycle" << endl;
        }
    }
    shared_ptr<Pessoa> remover(){
        if (this->pessoa == nullptr){
            cout << "fail: empty motorcycle" << endl;
        }
            auto backup = this->pessoa;
            this->pessoa = nullptr;
            return backup;
        
    }
    void comprar(int tempo){
        this->tempo += tempo;
    }
    void dirigir(int tempo){
        if(this->tempo == 0){
            cout << "fail: buy time first" << endl;
            return;
        }
        if(this->pessoa == nullptr){
            cout << "fail: empty motorcycle" << endl;
            return;
        }
        if(this-> pessoa-> getIdade() > 10){
            cout << "fail: too old to drive" << endl;
            return;
        }
        if(this->tempo < tempo){
            cout << "fail: time finished after" << " " << this->tempo << " minutes" << endl;
            this->tempo = 0;
            return;
        }
        this->tempo -= tempo;
    }
    string buzinar() const{
        string saida = "P";
        for(int i = 0; i < (int) this->potencia; i++){
            saida += 'e';
        }
        return saida + "m";

    }
        Moto() = default;
        void criar(int potencia = 1, int tempo = 0){
            this->potencia = potencia;
            this->tempo = tempo;
        }
        string str() const{
        stringstream ss;
        ss << "power:" << potencia << ", time:" << tempo << ", person:";
        if (pessoa) {
            ss << pessoa->str();
        } else {
            ss << "(empty)";
        }
        return ss.str();

        }
};
ostream& operator << (ostream &os, const Moto& moto){
    return os << moto.str();
}
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
         else if (cmd == "init") {
        //     // INICIE A MOTO AQUI USANDO O CONSTRUTOR
             int power {}, time{};
             ss >> power >> time;
             moto.criar(power, time);
         } 
         else if (cmd == "show") {
        //     // MOSTRE A MOTO AQUI
            cout << moto.str() << endl;
        }
         else if (cmd == "leave") {
        //     // RETIRE A PESSOA DA MOTO
        //     // SE EXISTIR, MOSTRE A PESSOA
        auto person = moto.remover();
        if(person == nullptr){
        } else{
            cout << person->getNome() << ":" << person->getIdade() << endl;
        }
         }
         else if (cmd == "honk") {
            moto.buzinar();
            cout << moto.buzinar() << endl;
         }
         else if (cmd == "enter") {
        //     // CRIE UM PONTEIRO PARA PESSOA E INICIE-O AQUI
        //     // DEPOIS INSIRA A PERSON NA MOTO
        string nome;
        int idade;
        ss >> nome >> idade;
        if (ss.fail()) {
            cout << "fail: entrada inválida\n";
        } else {
            auto person = make_shared<Pessoa>(nome, idade);
            moto.inserir(person);
        }
         }
         else if (cmd == "buy") {
        //     // COMPRE TEMPO PARA DIRIGIR
             int tempo {};
             ss >> tempo;
             moto.comprar(tempo);
         }
         else if (cmd == "drive") {
             // DIRIJA A MOTO POR UM TEMPO
             int tempo {};
             ss >> tempo;
             moto.dirigir(tempo);
         }
        else {
            cout << "fail: invalid command\n";
        }
    }
}
