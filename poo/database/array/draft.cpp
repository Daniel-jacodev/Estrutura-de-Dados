#include <iostream>
#include <vector>
using namespace std;

struct Vector
{
  int _size;
  int _capacity;
  int *_data;

    Vector(int capacity){
        _size = 0;
        this->_capacity = capacity;
        this->_data = new int[capacity];
    }
    ~Vector(){
        delete [] this->_data;
    }
    void show(){
        cout << "[";
        for(int i = 0; i < this->_size; i++){
            cout << this->_data[i] << " ";
        }
        cout << "]" << this->_size << "/" << this->_capacity << endl;
    }
    void push_back (int value){
    if(this->_size == this->_capacity){
        this->reserve(this->_capacity * 2);
    }
    this->_data[this->_size] = value;
    this->_size += 1;
    }
    void pop_back(){
        if(this->_size > 0){
            this->_size -= 1;
        }
    }
    int& front(){
        return this->_data[0];
    }

    int& back(){
        return this->_data[this->_size - 1];
    }
   // int& get(int index){
     //  return this->data[this->size - 1]; 
//    }
    int size(){
        return _size;
    }
    int capacity(){
        return _capacity;
    }
    int * begin(){
        return &this->_data[0];
    }
    int * end(){
        return &this->_data[this->_size];
    }
    void reserve(int capacity){
        int * novo = new int[capacity];
        if(capacity < this->_size){
            for(int i = 0; i < capacity; i++){
                novo[i] = this->_data[i];
            }
        }
        else{
            for(int i = 0; i < this->_size; i++){
                novo[i] = this->_data[i];
            }
        }
        delete[] this->_data;
        this->_data = novo;
    }
};

int main() {
    Vector vet(3);
    vet.show();
    vet.push_back(2);
    vet.push_back(3);
    vet.push_back(4);
    vet.push_back(5);
    vet.show();
    vet.pop_back();
    vet.show();
    vet.front() = 200;
    vet.show();
    vet.back() = 0;
    vet.show();
    for (auto it= vet.begin(); it != vet.end(); it++){
        cout << *it << " ";
    }
    cout << endl;
    vet.show();
    std::cout << "qxcode\n";
}

