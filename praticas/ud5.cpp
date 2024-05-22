#include <iostream>

using namespace std;

class Contador {
public:
    Contador() {
        contagem++;
    }

    static void contagemAtual() {
        cout << "A contagem atual e " << contagem << endl;
        return;
    }

    ~Contador() {
        contagem--;
    }
private:
    static int contagem;
};

int Contador::contagem = 0;

int main() {
    Contador::contagemAtual();
    Contador *c1 = new Contador();
    Contador::contagemAtual();
    Contador *c2 = new Contador();
    Contador::contagemAtual();
    Contador *c3 = new Contador();
    Contador::contagemAtual();
    delete c1;
    Contador::contagemAtual();
    delete c2;
    Contador::contagemAtual();
    delete c3;
    Contador::contagemAtual();

    return 0;
};