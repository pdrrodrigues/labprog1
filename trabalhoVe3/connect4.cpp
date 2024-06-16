#include <iostream>

using namespace std;

class Lig4 {
public:
    Lig4(int m, int n, unsigned int movimentos): m(m), n(n), movimentos{movimentos} {
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

    unsigned int getMovimentos() const {
        return movimentos;
    }

    void alternarJogador() {
        vez = movimentos % 2 ? 'X' : 'O';
        return;
    }

    bool jogadaValida(int mi) {
        if (tabuleiro[0][mi] != '.') {
            return false;
        }

        movimentos++;
        return true;
    }

    void jogada(int mi) {
        for(int i=n-1; i>=0; i++) {
            if(tabuleiro[i][mi] == '.') {
                tabuleiro[i][mi] = vez;
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
    // void gerencia() {
    //     bool fim = false;
    //     while(!fim) {
    //         exibe();
    //         jogada();
    //         if(isFull()) {
    //             fim = resultadoFinal();
    //         }
    //     }

    //     return;
    // }

    ~Lig4() {
        for(int i=0; i<n; i++) {
            delete[] tabuleiro[i];
        }

        delete[] tabuleiro;
    }

private:
    int m;
    int n;
    static const int FILEIRA = 4;
    char vez = 'X';
    char **tabuleiro;
    unsigned int movimentos;

    bool isFull() {
        bool isFull = true;
        for(int j=0; j<m; j++) {
            if(tabuleiro[0][j] == '.'){
                isFull = false;
                break;
            }
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