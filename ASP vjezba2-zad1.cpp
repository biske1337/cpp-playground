    #include <iostream>
#include <chrono>
#include <stdexcept>

class MiniNizLista {
    int* elementi;
    int kapacitet;
    int broj_elemenata;
    int tekuci;

public:
      MiniNizLista() : kapacitet(100), broj_elemenata(0), tekuci(-1) {
        elementi = new int[kapacitet];
      }

    ~MiniNizLista() {
        delete[] elementi;
    }

    MiniNizLista(const MiniNizLista& druga) 
        : kapacitet(druga.kapacitet), broj_elemenata(druga.broj_elemenata), tekuci(druga.tekuci) {
        elementi = new int[kapacitet];
        for (int i =0;i<broj_elemenata;i++) {
            elementi[i]=druga.elementi[i];
        }
    }

    MiniNizLista& operator=(const MiniNizLista& druga) {
        if (this==&druga) return *this;
        delete[] elementi;
        kapacitet = druga.kapacitet;
        broj_elemenata = druga.broj_elemenata;
        tekuci = druga.tekuci;
        elementi = new int[kapacitet];
        for (int i=0;i<broj_elemenata;i++) {
            elementi[i] = druga.elementi[i];
        }
        return *this;
    }

    bool pocetak() {
        if (broj_elemenata==0) return false;
        tekuci=0;
        return true;
    }

    bool kraj() {
        if (broj_elemenata==0) return false;
        tekuci=broj_elemenata - 1;
        return true;
    }

    bool prethodni() {
        if (tekuci > 0) {
            tekuci--;
            return true;
        }
        return false;
    }

    bool sljedeci() {
        if (tekuci < broj_elemenata - 1) {
            tekuci++;
            return true;
        }
        return false;
    }

    int daj_trenutni() const {
        if (broj_elemenata == 0 || tekuci < 0) {
            throw std::logic_error("Lista je prazna");
        }
        return elementi[tekuci];
    }

    int daj_broj_elemenata() const {
        return broj_elemenata;
    }

    int daj_kapacitet() const {
        return kapacitet;
    }

    void dodaj_iza(int x) {
        if (broj_elemenata == kapacitet) {
            int novi_kapacitet = kapacitet * 2;
            int* novi_elementi = new int[novi_kapacitet];
            
            for (int i=0; i < broj_elemenata; i++) {
                novi_elementi[i] = elementi[i];
            }
            
            delete[] elementi;
            elementi = novi_elementi;
            kapacitet = novi_kapacitet;
        }

        if (broj_elemenata == 0) {
            elementi[0] = x;
            tekuci = 0;
        } else {
            for (int i = broj_elemenata; i>tekuci+1; i--) {
                elementi[i] = elementi[i-1];
            }   
            elementi[tekuci+1] = x;
            tekuci++;
        }
        broj_elemenata++;
    }

    void obrisi() {
        if (broj_elemenata == 0 || tekuci < 0) {
            throw std::logic_error("Nema elementa za brisanje!");
        }

        for (int i=tekuci; i<broj_elemenata-1;i++) {
            elementi[i] = elementi[i + 1];
        }
        broj_elemenata--;

        if (broj_elemenata == 0) {
            tekuci = -1;
        } else if (tekuci >= broj_elemenata) {
            tekuci = broj_elemenata - 1;
        }
    }
};

int main() {
    MiniNizLista lista;
    auto pocetak = std::chrono::high_resolution_clock::now();
    for (int i=0; i<100000;i++) {
        lista.dodaj_iza(i);
    }
    auto kraj = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> trajanje = kraj - pocetak;

    std::cout << "Uspjesno dodano 100.000 elemenata!\n";
    std::cout << "Konacan broj elemenata: " << lista.daj_broj_elemenata() << "\n";
    std::cout << "Konacan kapacitet niza: " << lista.daj_kapacitet() << "\n";
    std::cout << "Vrijeme izvrsavanja: " << trajanje.count() << " ms\n";

    return 0;
}