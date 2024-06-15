#include <iostream>

using namespace std;

class Lig4 {
public:
    Lig4(int m, int n): m(m), n(n) {
        tabuleiro = new char*[this->n];
        for(int i=0; i<this->n; i++) {
            tabuleiro[i] = new char[this->m];
        }

        for(int i=0; i<this->n; i++) {
            for(int j=0; j<this->m; j++) {
                tabuleiro[i][j] = '.';
            }
        }
    }

    void exibe() {
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                cout << " " << tabuleiro[i][j];
            }
            cout << "\n";
        }

        for(int k=0; k<m; k++) {
            cout << " " << k+1;
        }

        cout << "\n";

        return;
    }

    // Mudar
    void alternarJogador() {
        vez = (vez == 'X') ? 'O' : 'X';
        return;
    }

    // Mudar
    bool jogadaValida(int mi) {
        if(mi <= 0 || mi > m) {
            cout << "Jogada invalida, tente novamente!" << endl;
            return false;
        } else if(tabuleiro[0][mi-1] != '.') {
            cout << "Coluna cheia, tente novamente!" << endl;
            return false;
        } else {
            cout << "Jogada valida" << endl;
            return true;
        }
    }

    // Mudar
    void jogada() {
        int mi;
        do {
            cout << "Insira a coluna que deseja jogar: ";
            cin >> mi;
        } while(!jogadaValida(mi));

        for(int i=n-1; i>=0; i--) {
            if(tabuleiro[i][mi-1] == '.') {
                tabuleiro[i][mi-1] = vez;
                break;
            }
        }
        alternarJogador();
        return;
    }

    // Mudar
    bool resultadoFinal() {
        pair<int, int> pontos;
        int xpontos = 0, opontos = 0;

        pontos = horPoints();
        xpontos += pontos.first;
        opontos += pontos.second;
        pontos = verPoints();
        xpontos += pontos.first;
        opontos += pontos.second;

        cout << xpontos << endl;
        cout << opontos << endl;
        exibe();
        if(xpontos == opontos) {
            cout << "O resultado final e um empate!" << endl;
        } else if(xpontos > opontos) {
            cout << "O jogador 'X' ganhou!" << endl;
        } else {
            cout << "O jogador 'O' ganhou!" << endl;
        }

        return true;
    }

    // Mudar
    void gerencia() {
        bool fim = false;
        while(!fim) {
            exibe();
            jogada();
            if(isFull()) {
                fim = resultadoFinal();
            }
        }

        return;
    }

    ~Lig4() {
        for(int i=0; i<n; i++) {
            delete[] tabuleiro[i];
        }

        delete[] tabuleiro;
    }

private:
    int m;
    int n;
    static const int k = 4;
    char vez = 'X';
    char **tabuleiro;

    bool isFull() {
        bool isFull = true;
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if(tabuleiro[i][j] == '.'){
                    isFull = false;
                    break;
                }
            }
            if(!isFull) break;
        }

        return isFull;
    }

    // Mudar
    pair<int, int> horPoints() {
        pair<int, int> horPoints;
        horPoints.first = 0;
        horPoints.second = 0;

        for(int i=0; i<n; i++) {
            int xtiles = 0;
            for(int j=0; j<m; j++) {
                if(tabuleiro[i][j] == 'O') {
                    xtiles = 0;
                } else {
                    xtiles++;
                    if(xtiles == 4){
                        horPoints.first += 1;
                        xtiles = 0;
                    }
                }
            }
        }

        for(int i=0; i<n; i++) {
            int otiles = 0;
            for(int j=0; j<m; j++) {
                if(tabuleiro[i][j] == 'X') {
                    otiles = 0;
                } else {
                    otiles++;
                    if(otiles == 4){
                        horPoints.second += 1;
                        otiles = 0;
                    }
                }
            }
        }

        return horPoints;
    }   

    // Mudar
    pair<int, int> verPoints() {
        pair<int, int> verPoints;
        verPoints.first = 0;
        verPoints.second = 0;
        
        for(int j=0; j<m; j++) {
            int xtiles = 0;
            for(int i=0; i<n; i++) {
                if(tabuleiro[i][j] == 'O') {
                    xtiles = 0;
                } else {
                    xtiles++;
                    if(xtiles == 4){
                        verPoints.first += 1;
                        xtiles = 0;
                    }
                }
            }
        }

        for(int j=0; j<m; j++) {
            int otiles = 0;
            for(int i=0; i<n; i++) {
                if(tabuleiro[i][j] == 'X') {
                    otiles = 0;
                } else {
                    otiles++;
                    if(otiles == 4){
                        verPoints.second += 1;
                        otiles = 0;
                    }
                }
            }
        }

        return verPoints;
    }

    // Criar avaliar diagonal
};

int main() {
    Lig4 lig4 = Lig4(4, 4);
    lig4.gerencia();
}