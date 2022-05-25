#include <iostream>
#include <vector>
#include <random>
#include <ctime>
using namespace std;

class Estrategia {
public:
    virtual bool execute(vector<int>);
};

class CincoPares : public Estrategia {
public:
    bool execute(vector<int> numeros) {
        int count = 0;
        for (auto val: numeros) {
            if (val % 2 == 0) count++;
        }
        if (count == 5) return true;
        return false;
    }
};

class CincoImpares : public Estrategia {
public:
    bool execute(vector<int> numeros) {
        int count = 0;
        for (auto val: numeros) {
            if (val % 2) count++;
        }
        if (count == 5) return true;
        return false;
    }
};

class Primo : public Estrategia {
public:
    bool isPrime(int val) {
        if (val == 0 || val == 1) return false;
        for (int i = 0 ; i < val/2 ; i++) {
            if (val % i == 0) return false;
        }
        return true;
    }
    bool execute(vector<int> numeros) {
        for (auto val: numeros) {
            if (isPrime(val)) return true;
        }
        return false;
    }
};

class TresDiez : public Estrategia {
public: 
    bool execute(vector<int> numeros) {
        int count = 0;
        for (auto val: numeros) {
            if (val % 10 == 0) count++;
        }
        if (count == 3) return true;
        return false;
    }
};

class DosVenticinco : public Estrategia {
public:
    bool execute(vector<int> numeros) {
        int count = 0;
        for (auto val: numeros) {
            if (val % 25 == 0) count++;
        }
        if (count == 2) return true;
        return false;
    }
};

class Jugador: public Observer {
private:
    Estrategia estrategia;
    bool gano;
public:
    Jugador(Estrategia strategy): estrategia{strategy} {};
    void update(vector<int> numeros) {
        gano = estrategia.execute(numeros);
    }
    bool acabado() {return gano;}
};

class Observer {
public:
    virtual void update();
};



class ComienzaJuego: public Observer {
private:
    shared_ptr<GeneradorNumeros> generador;
public:
    void update(vector<shared_ptr<Jugador>> jugadores) {
        if (jugadores.size() == 5)
            generador->start(jugadores);
    }
};

class SubjectInterface {
private:
    virtual void registerObsever();
    virtual void removeObserver();
    virtual void notifyObserver();
};

class GeneradorNumeros: public SubjectInterface {
private:
    vector<int> generados;
    vector<shared_ptr<Jugador>> jugadores;
public:
    void start(vector<shared_ptr<Jugador>> nuevos_jugadores) {
        while (getState() == 0) {
            srand(time(NULL));
            int nuevo = (rand() % 100) + 1;
            generados.push_back(nuevo);
            notifyObserver();
        }
    }
    void notifyObserver() {
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

class Juego {
private:
    static shared_ptr<Juego> juego;
    vector<shared_ptr<Jugador>> jugadores;
    shared_ptr<ComienzaJuego> comenzar;
    Juego() {}
public:
    Juego() {
        comenzar = make_shared<ComienzaJuego>();
    }
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


int main() {
    Juego juego;
}