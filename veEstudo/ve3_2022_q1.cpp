#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

using namespace std;

class Forca {
public:
    Forca(vector<string> listaPalavras): listaPalavras(listaPalavras) {}

    bool iniciar() {
        if(listaPalavras.empty()) {
            cout << "Sem palavras armazenadas!" << endl;
            cout << "Ate outra vez!!!" << endl;
            return false;
        }

        chances = 0;
        if(!letrasUsadas.empty()) letrasUsadas.clear();

        random_device rd{};
        default_random_engine engine{rd()};
        shuffle(listaPalavras.begin(), listaPalavras.end(), engine);
        palavraEscolhida = listaPalavras.back();
        listaPalavras.pop_back();
        palavraAtual = string(palavraEscolhida.size(), '_');

        return true;
    }

    void mostrar() {
        cout << "_______" << endl;
        cout << "|      |" << endl;
        cout << "|      " << (chances > 0 ? "O" : " ") << endl;
        cout << "|     " << (chances > 2 ? "/" : " ") << (chances > 1 ? "|" : " ") << (chances > 3 ? "\\" : " ") << endl;
        cout << "|     " << (chances > 5 ? "/" : " ") << (chances > 4 ? " \\" : "  ") << endl;
        cout << "|" << endl;
        cout << "\n" << palavraAtual << endl;

        return;
    }

    void jogar() {
        char input;
        bool inputValid = false;

        do {
            cout << "Insira um caracter: ";
            cin >> input;

            if(!letrasUsadas.empty()) {
                inputValid = (letrasUsadas.find(input) == letrasUsadas.npos) ? true : false;
            } else {
                inputValid = true;
            }
            

            if(inputValid) {
                cout << "Caracter valido" << endl;
                letrasUsadas.push_back(input);
            } else {
                cout << "Caracter invalido, tente novamente" << endl;
            }
        } while(!inputValid);

        auto itr1 = palavraEscolhida.begin();
        auto itr2 = palavraAtual.begin();
        bool hasInput = false;

        for(;itr1 != palavraEscolhida.end(); ++itr1, ++itr2){
            if(*itr1 == input) {
                *itr2 = input;
                hasInput = true;
            }
        }

        if(!hasInput) ++chances;

        return;
    }

    bool testeFimdeJogo() {
        if(chances < maxChances && palavraAtual == palavraEscolhida) {
            cout << "Parabens voce ganhou o jogo!!!" << endl;
            return true;
        } else if(chances < maxChances) {
            return false;
        } else {
            cout << "Voce morreu!" << endl;
            return true;
        }
    }

private:
    vector<string> listaPalavras;
    string palavraEscolhida;
    string palavraAtual;
    string letrasUsadas;
    int chances;
    static const int maxChances{6};
};

int main() {
    vector<string> palavras{"pipoca", "arara", "teste"};
    Forca forca(palavras);
    bool jogar = forca.iniciar();

    while(jogar) {
        bool fim = false;
        forca.mostrar();

        while(!fim) {
            forca.jogar();
            fim = forca.testeFimdeJogo();
            forca.mostrar();
        }

        jogar = forca.iniciar();
    }

    return 0;
}