#include <iostream>
#include <random>
#include <array>
#include <vector>
#include <climits>

using namespace std;

class Lig4 {
public:
    Lig4(int n, int m): m(m), n(n) {
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

    Lig4(const Lig4 &cp) {
        m = cp.m;
        n = cp.n;
        vez = cp.vez;
        tabuleiro = new char*[n];
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                tabuleiro[i] = new char[m];
            }
        }

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                tabuleiro[i][j] = cp.tabuleiro[i][j];
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

    char getJogador() const {
        return vez;
    }

    char** getTabuleiro() const {
        return tabuleiro;
    }

    void alternarJogador() {
        vez = (vez == 'O') ? 'X' : 'O';
        return;
    }

    bool jogadaValida(int mi) {
        return tabuleiro[0][mi] == '.';
    }

    void jogada(int mi) {
        for(int i=n-1; i>=0; --i) {
            if(tabuleiro[i][mi] == '.') {
                tabuleiro[i][mi] = vez;
                break;
            }
        }

        alternarJogador();
        return;
    }

    void desfazerJogada(int mi) {
        for (int i = 0; i < n; ++i) {
            if (tabuleiro[i][mi] != '.') {
                tabuleiro[i][mi] = '.';
                alternarJogador();
                break;
            }
        }
        
    }

    void resetar() {
        vez = 'X';
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                tabuleiro[i][j] = '.';
            }
        }

        return;
    }

    bool jogadaVencedora(char jogador) const {       
        for(int r = 0; r < n; r++) {
            for(int c = 0; c < m - 3; c++) {
                if(tabuleiro[r][c] == jogador && tabuleiro[r][c+1] == jogador && tabuleiro[r][c+2] == jogador && tabuleiro[r][c+3] == jogador) {
                    return true;
                }
            }
        }
        
        for(int c = 0; c < m; c++) {
            for(int r = 0; r < n - 3; r++) {
                if(tabuleiro[r][c] == jogador && tabuleiro[r+1][c] == jogador && tabuleiro[r+2][c] == jogador && tabuleiro[r+3][c] == jogador) {
                    return true;
                }
            }
        }
        
        for(int r = 0; r < n - 3; r++) {
            for(int c = 0; c < m - 3; c++) {
                if(tabuleiro[r][c] == jogador && tabuleiro[r+1][c+1] == jogador && tabuleiro[r+2][c+2] == jogador && tabuleiro[r+3][c+3] == jogador) {
                    return true;
                }
            }
        }
        
        for(int r = 3; r < n; r++) {
            for(int c = 0; c < m - 3; c++) {
                if(tabuleiro[r][c] == jogador && tabuleiro[r-1][c+1] == jogador && tabuleiro[r-2][c+2] == jogador && tabuleiro[r-3][c+3] == jogador) {
                    return true;
                }
            }
        }

        return false;
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
    char vez = 'X';
    char **tabuleiro;
};

class Lig4Tradicional: public Lig4 {
public:
    Lig4Tradicional(int dificuldade): Lig4(NUM_LIN, NUM_COL), dificuldade(dificuldade) {
        for(int i = 0; i<NUM_COL; ++i) {
            this->ordemColunas.push_back(NUM_COL/2 + (1-2*(i%2))*(i+1)/2);
        }
    }

    Lig4Tradicional(Lig4Tradicional &cp): Lig4(cp), dificuldade(cp.dificuldade) {}

    int jogadorAleatorio() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(0, NUM_COL - 1);
        return dist(gen);
    }

    int jogadorIA(int turnos) {
        return miniMax(dificuldade, INT_MIN, INT_MAX, turnos)[1];
    }

    array<int, 2> miniMax(int profundidade, int alfa, int beta, int turnos) {
        if (profundidade == 0 || profundidade >= (NUM_COL * NUM_LIN) - turnos) {
            return array<int, 2>{this->valorTabuleiro(this->getTabuleiro(), 'X'), -1};
        }
        if (this->getJogador() == 'X') {
            array<int, 2> valorAtual = {INT_MIN, -1};
            if (this->jogadaVencedora('O')) {
                return valorAtual;
            } 
            for (int c = 0; c < NUM_COL; c++) {
                if (this->jogadaValida(ordemColunas[c])) {
                    this->jogada(ordemColunas[c]);
                    int valor = this->miniMax(profundidade - 1, alfa, beta, turnos)[0];
                    this->desfazerJogada(ordemColunas[c]);
                    if (valor > valorAtual[0]) {
                        valorAtual = {valor, ordemColunas[c]};
                    }
                    alfa = max(alfa, valorAtual[0]);
                    if (alfa >= beta) { break; }
                }
            }
            return valorAtual;
        }
        else {
            array<int, 2> valorAtual = {INT_MAX, -1};
            if (this->jogadaVencedora('X')) {
                return valorAtual;
            }
            for (int c = 0; c < NUM_COL; c++) {
                if (this->jogadaValida(ordemColunas[c])) {
                    this->jogada(ordemColunas[c]);
                    int valor = this->miniMax(profundidade - 1, alfa, beta, turnos)[0];
                    this->desfazerJogada(ordemColunas[c]);
                    if (valor < valorAtual[0]) {  
                        valorAtual = {valor, ordemColunas[c]};
                    }
                    beta = min(beta, valorAtual[0]);
                    if (alfa >= beta) { break; }
                }
            }
            return valorAtual;
        } 
    }

    static int valorTabuleiro(char** tabuleiro, char p) {
        int score = 0;
        vector<char> vl(NUM_COL);
        vector<char> vc(NUM_LIN);
        vector<char> conjunto(4);
        
        for (int r = 0; r < NUM_LIN; r++) {
            for (int c = 0; c < NUM_COL; c++) {
                vl[c] = tabuleiro[r][c];
            }
            for (int c = 0; c < NUM_COL - 3; c++) {
                for (int i = 0; i < 4; i++) {
                    conjunto[i] = vl[c + i];
                }
                score += valorConjunto(conjunto, p);
            }
        }
        
        for (int c = 0; c < NUM_COL; c++) {
            for (int r = 0; r < NUM_LIN; r++) {
                vc[r] = tabuleiro[r][c];
            }
            for (int r = 0; r < NUM_LIN - 3; r++) {
                for (int i = 0; i < 4; i++) {
                    conjunto[i] = vc[r + i];
                }
                score += valorConjunto(conjunto, p);
            }
        }
        
        for (int r = 0; r < NUM_LIN - 3; r++) {
            for (int c = 0; c < NUM_COL; c++) {
                vl[c] = tabuleiro[r][c];
            }
            for (int c = 0; c < NUM_COL - 3; c++) {
                for (int i = 0; i < 4; i++) {
                    conjunto[i] = tabuleiro[r + i][c + i];
                }
                score += valorConjunto(conjunto, p);
            }
        }

        for (int r = 0; r < NUM_LIN - 3; r++) {
            for (int c = 0; c < NUM_COL; c++) {
                vl[c] = tabuleiro[r][c];
            }
            for (int c = 0; c < NUM_COL - 3; c++) {
                for (int i = 0; i < 4; i++) {
                    conjunto[i] = tabuleiro[r + 3 - i][c + i];
                }
                score += valorConjunto(conjunto, p);
            }
        }
        return score;
    }

    static int valorConjunto(vector<char> v, char p) {
        int bom = 0;
        int ruim = 0;
        int vazio = 0;
        for (char ch : v) {
            if (ch == p) bom++;
            if (ch == 'O' || ch == 'X') ruim++;
            if (ch == '.') vazio++;
        }
        ruim -= bom;
        return heuristica(bom, ruim, vazio);
    }

    static int heuristica(int b, int r, int v) {
        int valor = 0;
        if (b == 4) { valor += 500001; }
        else if (b == 3 && v == 1) { valor += 5000; }
        else if (b == 2 && v == 2) { valor += 500; }
        else if (r == 2 && v == 2) { valor -= 501; }
        else if (r == 3 && v == 1) { valor -= 5001; }
        else if (r == 4) { valor -= 500000; }
        return valor;
    }

    char jogar() {
        bool fim = false;
        int turnos = 0;
        while(!fim) {
            if(this->getJogador() == 'X') {
                this->jogada(this->jogadorIA(turnos));
            } else if (this->getJogador() == 'O') {
                bool valido;
                int jogada;
                do{
                    jogada = this->jogadorAleatorio();
                    valido = this->jogadaValida(jogada);
                } while(!valido);

                this->jogada(jogada);
            }

            if (turnos == NUM_COL * NUM_LIN) {
                return 'E';
            }
            fim = this->jogadaVencedora(this->getJogador() == 'X' ? 'O' : 'X');
            ++turnos;
        }
        return ((this->getJogador() == 'X') ? 'O' : 'X');
    }

    ~Lig4Tradicional() {}
private:
    int dificuldade;
    static const int NUM_COL = 7;
    static const int NUM_LIN = 6;
    vector<int> ordemColunas;
};

int main() {
    const int total = 10000;
    int count = 0;
    char ganhador;
    Lig4Tradicional l = Lig4Tradicional(5);

    for(int i = 0; i < total; ++i){
        ganhador = l.jogar();
        l.exibe();
        l.resetar();

        if(ganhador == 'X') {
            ++count;
        }
    }

    cout <<  "Vitorias: " << count << endl;
    return 0;
}