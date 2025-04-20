
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
using namespace std;

template<typename CONTAINER, typename FUNC>
string join(const CONTAINER& cont, FUNC func, const string& delim) {
    stringstream ss;
    for (auto it = cont.begin(); it != cont.end(); it++) {
        ss << (it == cont.begin() ? "" : delim) << func(*it);
    }
    return ss.str();
}
enum class Label{DEPOSIT, FEE, OPENING, REVERSE, WITHDRAW, ERROR};
string labelToString(Label label){
    switch (label){
        case Label :: DEPOSIT: return "deposit";
        case Label :: FEE: return "fee";
        case Label :: OPENING: return "opening";
        case Label :: REVERSE: return "reverse";
        case Label :: WITHDRAW: return "withdraw";
        case Label :: ERROR: return "ERROR";
        default: throw runtime_error("Label inválido");
    }
}
Label stringToLabel(const string& str){
    if(str == "DEPOSIT") return Label::DEPOSIT;
    if(str == "FEE") return Label::FEE;
    if(str == "OPENING") return Label::OPENING;
    if(str == "REVERSE") return Label::REVERSE;
    if(str == "WITHDRAW") return Label::WITHDRAW;
    if(str == "ERRO") return Label::ERROR;
    throw runtime_error("Label inválido");
}

class Operation{
    int index;
    Label label;
    int value;
    int balance;
    public:
        Operation(int index, Label label, int value, int balance) :
        index(index), label(label), value(value), balance(balance){}
        
        int getBalance() const {
            return balance;
        }
        int getIndex() const {
            return index;
        }
        Label getLabel(){
            return label;
        }
        int getValue() const {
            return value;
        }

        string str() const {
            stringstream ss;
            ss << setfill(' ') << setw(2) <<  getIndex() << ":"  << setfill(' ') << setw(9)  << labelToString(label) << ":";
            if(label == Label::WITHDRAW || label == Label::FEE){
                int newValue = value * -1;
                ss << setfill(' ') << setw(5) << newValue;
            }else{
                ss << setfill(' ') << setw(5) << value;
            }
            return ss.str();
        }

};

class BalanceManager{
    int balance;
    vector <Operation> extrato;
    int nextId;
    public:
        BalanceManager(int balance, int nextId) : balance(balance), nextId(nextId){}
       void addOperation(Label label, int value){
        if(label == Label::DEPOSIT){
            balance += value;
        }
        if(label == Label::WITHDRAW){
            balance -= value;
        }
        if(label == Label::FEE){
            balance -= value;
        }
        Operation op(nextId++, label, value, balance);
        extrato.push_back(op);
       }
       int getBalance(){
        return balance;
       }
       void getOperation(int index){
        for(auto& op : extrato){
            if(op.getIndex() == index){
                cout << op.str() << endl;
                return;
            }
        }
        cout << "fail: indice invalido" << endl;
    }
    void printExtrato(int qtd) const{
        int size = extrato.size();
        int start = (qtd == 0) ? 0 : max(0, size - qtd);
        for (int i = start; i < size; i++){
            cout << extrato[i].str() << ":" << setfill(' ') << setw(5)
            << extrato[i].getBalance() << endl;
        }
    }
    void reverse(const vector<int>& indices) {
        for (int index : indices) {
            bool found = false;
            for (auto& op : extrato) {
                if (op.getIndex() == index) {
                    if (op.getLabel() == Label::FEE) {
                        balance += op.getValue();
                        addOperation(Label::REVERSE, op.getValue());
                    } else {
                        cout << "fail: index " << index << " is not a fee" << endl;
                    }
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "fail: index " << index << " invalid" << endl;
            }
        }
    }

    
    string str() const{
        stringstream ss;
        ss << "balance:" << balance << endl;
        return ss.str();
    }
};
class Account{
    int id;
    BalanceManager balanceManager;
    public:
    Account(int id, int initialBalance = 0) 
    : id(id), balanceManager(initialBalance, 0) {
        balanceManager.addOperation(Label::OPENING, 0);
    }
    void deposit(int value){
        if (value < 0){
            cout << "fail: invalid value" << endl;
            return;
        }
        balanceManager.addOperation(Label::DEPOSIT, value);
    }
    void retirar(int value){
         if(value > balanceManager.getBalance()){
             cout << "fail: insufficient balance" << endl;
             return;
         }
        balanceManager.addOperation(Label::WITHDRAW, value);
    }
    void fee(int value){
        balanceManager.addOperation(Label::FEE, value);

    }
    void printExtrato(int qtd) const{
       balanceManager.printExtrato(qtd);
    }
    
    void reverseCommand(const vector<int>& indices) {
        balanceManager.reverse(indices);
    }
    string str() const{
        stringstream ss;
        ss << "account:" << id << " " << balanceManager.str();
        return ss.str();

    }
};


int main() {
    Account account (0);
    while(true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        
        if (cmd == "end") {
            break;
        }
        else if (cmd == "init") {
             int number{};
            ss >> number;
            account = Account(number, 0);
        }
        else if (cmd == "show") {
            // TODO
            cout << account.str();
        }
        else if (cmd == "deposit") {
             float value{};
             ss >> value;
             account.deposit(value);
        }
        else if (cmd == "withdraw") {
             float value{};
             ss >> value;
             account.retirar(value);
        }
        else if (cmd == "fee") {
             float value{};
             ss >> value;
             account.fee(value);
        }
        else if (cmd == "extract") {
             int qtd{};
             ss >> qtd;
             account.printExtrato(qtd);
        }
        else if (cmd == "reverse") {
            vector<int> indices;
             int index{};
             while(ss >> index) {
                indices.push_back(index);
             }
             account.reverseCommand(indices);
        }
        else {
            cout << "fail: invalid command\n";
        }
    }
    return 0;
}
