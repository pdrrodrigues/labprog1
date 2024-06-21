#include <iostream>
#include <random>
#include <array>

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

    // int getMovimentos() const {
    //     return movimentos;
    // }

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
        if (tabuleiro[0][mi] != '.') {
            return false;
        }

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

    bool jogadaVencedora(char jogador) {
        int sequenciaVencedora = 0;
        for (int c = 0; c < m - 3; c++) {
            for (int r = 0; r < n; r++) {
                for (int i = 0; i < 4; i++) {
                    if (tabuleiro[r][c + i] == jogador) {
                        sequenciaVencedora++;
                    }
                    if (sequenciaVencedora == 4) { return true; }
                }
                sequenciaVencedora = 0;
            }
        }

        for (int c = 0; c < m; c++) {
            for (int r = 0; r < n - 3; r++) {
                for (int i = 0; i < 4; i++) {
                    if (tabuleiro[r + i][c] == jogador) {
                        sequenciaVencedora++;
                    }
                    if (sequenciaVencedora == 4) { return true; }
                }
                sequenciaVencedora = 0;
            }
        }

        for (int c = 0; c < m - 3; c++) {
            for (int r = 3; r < n; r++) {
                for (int i = 0; i < 4; i++) {
                    if (tabuleiro[r - i][c + i] == jogador) {
                        sequenciaVencedora++;
                    }
                    if (sequenciaVencedora == 4) { return true; }
                }
                sequenciaVencedora = 0;
            }
        }

        for (int c = 0; c < m - 3; c++) {
            for (int r = 0; r < n - 3; r++) {
                for (int i = 0; i < 4; i++) {
                    if (tabuleiro[r + i][c + i] == jogador) {
                        sequenciaVencedora++;
                    }
                    if (sequenciaVencedora == 4) { return true; }
                }
                sequenciaVencedora = 0;
            }
        }
        return false;
    }

    Lig4(const Lig4 &cp) {
        m = cp.m;
        n = cp.n;
        vez = cp.vez;
        // movimentos = cp.movimentos;
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
    // int movimentos = 0;
};

class Lig4Tradicional: public Lig4 {
public:
    Lig4Tradicional(int dificuldade, default_random_engine engine): Lig4(6, 7) {
        this->dificuldade = dificuldade;
        this->engine = engine;
    }

    Lig4Tradicional(Lig4Tradicional &cp): Lig4(cp) {
        dificuldade = cp.dificuldade;
        engine = cp.engine;
    }

    int jogadorAleatorio(default_random_engine &engine) {
        uniform_int_distribution chance{0, 6};
        return chance(engine);
    }

    int jogadorIA() {
        return minimax(dificuldade)[1];
    }

    array<int, 2> minimax(int profundidade, int alfa, int beta, int turnos) {
       if (profundidade == 0 || profundidade >= (7 * 6) - turnos) {
            return array<int, 2>{tabScore(b, COMPUTER), -1};
        }
        if (p == COMPUTER) {
            array<int, 2> moveSoFar = {INT_MIN, -1};
            if (winningMove(b, PLAYER)) {
                return moveSoFar;
            } 
            for (int c = 0; c < 7; c++) {
                if (b[NUM_ROW - 1][c] == 0) {
                    vector<vector<int> > newBoard = copyBoard(b);
                    makeMove(newBoard, c, p);
                    int score = miniMax(newBoard, d - 1, alf, bet, PLAYER)[0];
                    if (score > moveSoFar[0]) {
                        moveSoFar = {score, (int)c};
                    }
                    alf = max(alf, moveSoFar[0]);
                    if (alf >= bet) { break; }
                }
            }
            return moveSoFar;
        }
        else {
            array<int, 2> moveSoFar = {INT_MAX, -1};
            if (winningMove(b, COMPUTER)) {
                return moveSoFar;
            }
            for (unsigned int c = 0; c < NUM_COL; c++) {
                if (b[NUM_ROW - 1][c] == 0) {
                    vector<vector<int> > newBoard = copyBoard(b);
                    makeMove(newBoard, c, p);
                    int score = miniMax(newBoard, d - 1, alf, bet, COMPUTER)[0];
                    if (score < moveSoFar[0]) {
                        moveSoFar = {score, (int)c};
                    }
                    bet = min(bet, moveSoFar[0]);
                    if (alf >= bet) { break; }
                }
            }
            return moveSoFar;
        } 
    }

    static int tabScore(char** tabuleiro, unsigned int p) {
        int score = 0;
        vector<unsigned int> rs(NUM_COL);
        vector<unsigned int> cs(NUM_ROW);
        vector<unsigned int> set(4);
        
        for (unsigned int r = 0; r < NUM_ROW; r++) {
            for (unsigned int c = 0; c < NUM_COL; c++) {
                rs[c] = b[r][c];
            }
            for (unsigned int c = 0; c < NUM_COL - 3; c++) {
                for (int i = 0; i < 4; i++) {
                    set[i] = rs[c + i];
                }
                score += scoreSet(set, p);
            }
        }
        
        for (unsigned int c = 0; c < NUM_COL; c++) {
            for (unsigned int r = 0; r < NUM_ROW; r++) {
                cs[r] = b[r][c];
            }
            for (unsigned int r = 0; r < NUM_ROW - 3; r++) {
                for (int i = 0; i < 4; i++) {
                    set[i] = cs[r + i];
                }
                score += scoreSet(set, p);
            }
        }
        
        for (unsigned int r = 0; r < NUM_ROW - 3; r++) {
            for (unsigned int c = 0; c < NUM_COL; c++) {
                rs[c] = b[r][c];
            }
            for (unsigned int c = 0; c < NUM_COL - 3; c++) {
                for (int i = 0; i < 4; i++) {
                    set[i] = b[r + i][c + i];
                }
                score += scoreSet(set, p);
            }
        }

        for (unsigned int r = 0; r < NUM_ROW - 3; r++) {
            for (unsigned int c = 0; c < NUM_COL; c++) {
                rs[c] = b[r][c];
            }
            for (unsigned int c = 0; c < NUM_COL - 3; c++) {
                for (int i = 0; i < 4; i++) {
                    set[i] = b[r + 3 - i][c + i];
                }
                score += scoreSet(set, p);
            }
        }
        return score;
    }

    int scoreSet(vector<unsigned int> v, unsigned int p) {
        unsigned int good = 0;
        unsigned int bad = 0;
        unsigned int empty = 0;
        for (unsigned int i = 0; i < v.size(); i++) {
            good += (v[i] == p) ? 1 : 0;
            bad += (v[i] == PLAYER || v[i] == COMPUTER) ? 1 : 0;
            empty += (v[i] == 0) ? 1 : 0;
        }
        bad -= good;
        return heuristica(good, bad, empty);
    }

    static int heuristica(int b, int r, int v) {
        int score = 0;
        if (b == 4) { score += 500001; }
        else if (b == 3 && v == 1) { score += 5000; }
        else if (b == 2 && v == 2) { score += 500; }
        else if (r == 2 && v == 2) { score -= 501; }
        else if (r == 3 && v == 1) { score -= 5001; }
        else if (r == 4) { score -= 500000; }
        return score;
    }

    char jogar() {}

    ~Lig4Tradicional() {}
private:
    int dificuldade;
    default_random_engine engine;
    static const int NUM_COL = 7;
    static const int NUM_LIN = 6;
};

int main() {
    const int total = 100;
    int count = 0;
    random_device rd{};
    default_random_engine engine{rd()};

    for(int i = 0; i < total; ++i){
        char ganhador;
        Lig4Tradicional l = Lig4Tradicional(5, engine);
        ganhador = l.jogar();

        if(ganhador == 'x') {
            ++count;
        }
    }

    cout << (count/total)*100 << endl;
    return 0;
}