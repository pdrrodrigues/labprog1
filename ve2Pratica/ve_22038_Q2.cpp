#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class FuncionarioBase {
public:
    FuncionarioBase(int id, string name, double salary, string tipo): id(id), name(name), salary(salary), tipo(tipo) {}

    double getSalary() {
        return salary;
    }

    string getName() {
        return name;
    }

    void exibirDetalhes() {
        cout << "Indentificador do Funcionario: " << id << endl;
        cout << "Nome do Funcionario: " << name << endl;
        cout << "Salario do Funcionario: " << this->getSalary() << endl;
        cout << "Funcao dom Funcionario: " << tipo << endl;

        return;
    }

    virtual void fun() {}

private:
    int id;
    string name;
    double salary;
    string tipo;
};

class Funcionario: public FuncionarioBase {
public: 
    Funcionario(int id, string name, double salary, string tipo): FuncionarioBase(id, name, salary, tipo) {}
};

class Gerente: public FuncionarioBase {
public:
    Gerente(int id, string name, double salary): FuncionarioBase(id, name, salary, "Gerente") {}

    void adicionarFuncionario(FuncionarioBase& fun) {
        if(time.size() >= maxTime) {
            cout << "Time cheio!" << endl;
        } else {
            if(dynamic_cast<Gerente*> (&fun) != nullptr) {
                cout << "Nao pode adicionar outro gerente no time!" << endl;
            } else {
                auto found = find(time.begin(), time.end(), &fun);
                if(found == time.end()) {
                    cout << "Adicionado o funcionario " << fun.getName() << " no time" << endl;
                    time.push_back(&fun);
                } else {
                    cout << "Funcionario ja presente no time" << endl;
                }
            }
        }

        return;
    }

    void mostrarTime() {
        cout << "Time do Gerente " << FuncionarioBase::getName() << endl;

        auto itr = time.begin();
        for(; itr != time.end(); ++itr) {
            (*itr)->exibirDetalhes();
            cout << "\n";
        }

        return;
    }

    double salarioTotal() {
        int salarioTotal = FuncionarioBase::getSalary();
        auto itr = time.begin();
        for(; itr != time.end(); ++itr) {
            salarioTotal += (*itr)->getSalary();
        }

        return salarioTotal;
    }
private:
    vector<FuncionarioBase*> time;
    static const int maxTime = 10;
};

int main() {
    Funcionario f1 = Funcionario(1, "Func1", 5000, "analista");
    Funcionario f2 = Funcionario(2, "Func2", 5000, "analista");
    Funcionario f3 = Funcionario(3, "Func3", 5000, "analista");
    Funcionario f4 = Funcionario(4, "Func4", 5000, "analista");
    Funcionario f5 = Funcionario(5, "Func5", 5000, "analista");
    Funcionario f6 = Funcionario(6, "Func6", 5000, "analista");
    Funcionario f7 = Funcionario(7, "Func7", 5000, "analista");
    Funcionario f8 = Funcionario(8, "Func8", 5000, "analista");
    Funcionario f9 = Funcionario(9, "Func9", 5000, "analista");
    Funcionario f10 = Funcionario(10, "Func10", 5000, "analista");
    Funcionario f11 = Funcionario(11, "Func11", 5000, "analista");
    Gerente g1 = Gerente(12, "Ger1", 12000);
    Gerente g2 = Gerente(13, "Ger2", 12000);

    f1.exibirDetalhes();
    g1.adicionarFuncionario(f1);
    g1.adicionarFuncionario(g2);
    g1.adicionarFuncionario(f2);
    g1.adicionarFuncionario(f3);
    g1.adicionarFuncionario(f4);
    g1.adicionarFuncionario(f5);
    g1.adicionarFuncionario(f6);
    g1.adicionarFuncionario(f7);
    g1.adicionarFuncionario(f8);
    g1.adicionarFuncionario(f9);
    g1.adicionarFuncionario(f10);
    g1.adicionarFuncionario(f11);
    g1.mostrarTime();
    cout << "O salario total do time do gerente " << g1.getName() << " e " << g1.salarioTotal() << endl;

    return 0;
}