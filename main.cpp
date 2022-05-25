#include <iostream>
#include <vector>
#include <random>
#include <ctime>
using namespace std;

class Estrategia {
public:
    Estrategia() = default;
    virtual ~Estrategia() = default;
    virtual bool execute(vector<int> &numeros) = 0;
};

class CincoPares : public Estrategia {
public:
    CincoPares() = default;
    bool execute(vector<int> &numeros) override {
        int count = 0;
        for (auto val: numeros) {
            if (val % 2 == 0) count++;
        }
        if (count == 5) return true;
        return false;
    };
};

class CincoImpares : public Estrategia {
public:
    CincoImpares() = default;
    bool execute(vector<int> &numeros) override {
        int count = 0;
        for (auto val: numeros) {
            if (val % 2) count++;
        }
        if (count == 5) return true;
        return false;
    };
};

class Primo : public Estrategia {
public:
    Primo() = default;
    const bool isPrime(int val) {
        if (val == 0 || val == 1) return false;
        for (int i = 2 ; i < val/2 ; i++) {
            if (val % i == 0) return false;
        }
        return true;
    }
    bool execute(vector<int> &numeros) override {
        for (auto val: numeros) {
            if (isPrime(val)) return true;
        }
        return false;
    };
};

class TresDiez : public Estrategia {
public: 
    TresDiez() = default;
    bool execute(vector<int> &numeros) override {
        int count = 0;
        for (auto val: numeros) {
            if (val % 10 == 0) count++;
        }
        if (count == 3) return true;
        return false;
    };
};

class DosVenticinco : public Estrategia {
public:
    DosVenticinco() = default;
    bool execute(vector<int> &numeros) override{
        int count = 0;
        for (auto val: numeros) {
            if (val % 25 == 0) count++;
        }
        if (count == 2) return true;
        return false;
    };
};

class Observer {
public:
    Observer() = default;
    virtual ~Observer() = default;
    virtual void update() = 0;
};

class Jugador: public Observer {
private:
    Estrategia estrategia;
    bool gano;
public:
    explicit Jugador(Estrategia &strategy): estrategia{strategy} {};
    const void update(vector<int> &numeros) {
        gano = estrategia.execute(numeros);
    }
    const bool acabado() {return gano;}
};


class SubjectInterface {
private:
    virtual void registerObsever() = 0;
    virtual void removeObserver() = 0;
    virtual void notifyObserver() = 0;
};

class GeneradorNumeros: public SubjectInterface {
private:
    vector<int> generados;
    vector<shared_ptr<Jugador>> jugadores;
public:
    void start(vector<shared_ptr<Jugador>> nuevos_jugadores) {
        while (getState() == 0) {
            srand(time(nullptr));
            int nuevo = (rand() % 100) + 1;
            generados.push_back(nuevo);
            notifyObserver();
        }
    }
    void notifyObserver() override {
        for (auto jugador: jugadores) {
            jugador->update(generados);
        }
    }

    bool getState() {
        for (auto jugador: jugadores) {
            if (jugador->acabado()) return true;
        }
        return false;
    }
};


class ComienzaJuego: public Observer {
private:
    shared_ptr<GeneradorNumeros> generador;
public:
    const void update(vector<shared_ptr<Jugador>> &jugadores) {
        if (jugadores.size() == 5)
            generador->start(jugadores);
    }
};

class Juego {
private:
    static shared_ptr<Juego> juego;
    vector<shared_ptr<Jugador>> jugadores;
    shared_ptr<ComienzaJuego> comenzar;
public:
    static shared_ptr<Juego> getInstance() {
        if (juego == nullptr) {
            juego = make_shared<Juego>();
        }
        return juego;
    }

    void nuevoJugador(shared_ptr<Jugador> jugador) {
        jugadores.push_back(jugador);
        comenzar->update(jugadores);
    }


};

shared_ptr<Juego> Juego::juego = nullptr;

int main() {
    return 0;
}