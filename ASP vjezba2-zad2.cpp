#include <iostream>
#include <chrono>
#include <stdexcept>
#include <cassert>

//kom
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
void test_dodavanje() {
    std::cout << "\n--- TEST 1: Dodavanje (dodaj_iza) ---\n";
    const int BROJ_ELEMENATA = 30000;
   
    {
        MiniNizLista lista;
        auto t1 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < BROJ_ELEMENATA; ++i) {
            lista.dodaj_iza(i); 
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> trajanje = t2 - t1;
        std::cout << "Najbolji slucaj (dodavanje na kraj): " << trajanje.count() << " ms\n";
    }

 
    {
        MiniNizLista lista;
        lista.dodaj_iza(0);
        auto t1 = std::chrono::high_resolution_clock::now();
        for (int i = 1; i < BROJ_ELEMENATA; ++i) {
            lista.pocetak();   
            lista.dodaj_iza(i);
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> trajanje = t2 - t1;
        std::cout << "Najgori slucaj (dodavanje pri pocetku): " << trajanje.count() << " ms\n";
    }
}

void test_brisanje() {
    std::cout << "\ntest 2: Brisanje\n";
    const int BROJ_ELEMENATA = 30000;

    {
        MiniNizLista lista;
        for (int i = 0; i < BROJ_ELEMENATA; ++i) lista.dodaj_iza(i);

        auto t1 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < BROJ_ELEMENATA; ++i) {
            lista.kraj();
            lista.obrisi(); 
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> trajanje = t2 - t1;
        std::cout << "Najbolji slucaj (brisanje s kraja): " << trajanje.count() << " ms\n";
    }

      {
        MiniNizLista lista;
        for (int i = 0; i < BROJ_ELEMENATA; ++i) lista.dodaj_iza(i);

        auto t1 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < BROJ_ELEMENATA; ++i) {
            lista.pocetak();
            lista.obrisi(); 
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> trajanje = t2 - t1;
        std::cout << "Najgori slucaj (brisanje s pocetka): " << trajanje.count() << " ms\n";
    }
}

void test_kretanje_i_pristup() {
    std::cout << "\ntest3: Metode kretanja i pristupa \n";
    MiniNizLista lista;

    
    lista.dodaj_iza(10);
    lista.dodaj_iza(20);
    lista.dodaj_iza(30);

    lista.pocetak();
    assert(lista.daj_trenutni() == 10);

    lista.sljedeci();
    assert(lista.daj_trenutni() == 20);

    lista.prethodni();
    assert(lista.daj_trenutni() == 10);

    lista.kraj();
    assert(lista.daj_trenutni() == 30);
    std::cout << "Najbolji slucaj (ispravno kretanje i pristup): PROSLAO\n";


    MiniNizLista prazna_lista;
    try {
        prazna_lista.daj_trenutni(); 
        std::cout << "GRESKA: Izuzetak nije bacen!\n";
    } catch (const std::logic_error& e) {
        std::cout << "Najgori slucaj (pristup praznoj listi - izuzetak): PROSLAO\n";
    }
}



// U sustini za unos na kraj niza najbolji slucaj je O(1) jer se pomjeri samo pokazivac (ne pomjera se nista od elemenata) cak i ako prosirujemo niz najgori slucaj je O(1)
// Ako unosimo na pocetku ili sredini liste najgori slucaj je O(n) za jedan element a ako unosimo vise elemanata npr N najgori slucaj je O(n^2)
// brisanje elemanata je ekvivalentno sa dodavanjem (s kraja ) isto je O(1)
// brisanje s pocetka/sredine je isti slucaj kao i sa dodavanjem tj O(n) u najgorem slucaju ako brisemo N elemanata onda je O(n^2)
// bilo kakvo potraznja trenutnog,prethodnog,sljedeceg,pocetak,kraj je uvijek O(1) jer mozemo postaviti indekse na tekuci element ili mozemo pristupi direktno elementu preko indeksa 


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
