#include <iostream>
#include <string>

using namespace std;

class Empregado {
public:
    Empregado(string nome, double salario, int ramal): nome(nome), salario(salario), ramal(ramal) {
        contagem++;
        warn();
    }

    const string getNome() {
        return nome;
    }

    const double getSalario() {
        return salario;
    }

    void setSalario(double newSalario) {
        salario = newSalario;
        return;
    }

    const int getRamal() {
        return ramal;
    }

    void setRamal(int newRamal) {
        ramal = newRamal;
        return;
    }
private:
    static inline int contagem = 0;
    const string nome;
    double salario;
    int ramal;

    void warn() {
        if(contagem < 10) {
            cout << "Numero de funcionarios abaixo do necessario(10)!!!" << endl;
        } else if(contagem > 50) {
            cout << "Numero de funcionarios acima do necessario(50)!!!" << endl;
        }

        return;
    }
};