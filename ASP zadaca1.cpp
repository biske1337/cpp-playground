#include <iostream>
#include <stdexcept>


template <typename Tip>

class Lista{
    
    public:
    virtual ~Lista() = default;

    virtual int brojElemenata() const = 0;

    virtual Tip& trenutni() = 0;
    virtual const Tip& trenutni() const = 0;

    virtual bool prethodni() = 0;
    virtual bool sljedeci() = 0;

    virtual void pocetak() = 0;
    virtual void kraj() = 0;

    virtual void obrisi() = 0;

    virtual void dodajIspred(const Tip& el) = 0;
    virtual void dodajIza(const Tip& el) = 0;

    virtual Tip& operator[](int i) = 0;
    virtual const Tip& operator[](int i) const = 0;
};

template<typename Tip>

class NizLista : public Lista<Tip>
{
    Tip *elementi;
    int kapacitet;
    int broj_elemanata;
    int trenutni;

    public:
    NizLista() : kapacitet(100), broj_elemanata(0),trenutni(-1){
        elementi= new Tip[kapacitet];
    }
    ~NizLista(){
        delete []elementi;
    }
    NizLista(const NizLista& l) : kapacitet(l.kapacitet), broj_elemanata(l.broj_elemanata), trenutni(l.trenutni){
        elementi= new Tip[kapacitet];
        for(int i=0;i<l.broj_elemanata++){
            elementi[i]=l.elementi[i];
        }
    }

    int brojElemenata() const override {
        return broj_elemanata;
    }
    Tip& trenutni() override {
        if(broj_elemanata==0 || trenutni<0){
            throw std::logic_error("Lista je prazna");
        }
        return elementi[trenutni];
    }
    const Tip& trenutni() const override {
        if(broj_elemanata==0 || trenutni<0){
            throw std::logic_error("Lista je prazna");
        }
        return elementi[trenutni];
    }
    bool prethodni() override{
       if(broj_elemanata==0 || trenutni<0) throw std::logic_error("Lista je prazna");
       if(trenutni>0){
        trenutni--;
        return true;
       }
       return false;
    }
    bool sljedeci() override {
        if(broj_elemanata==0 || trenutni<0) throw std::logic_error("Lista je prazna");
        if(trenutni < broj_elemanata-1){
            trenutni++;
            return true;
        } // logika
        return false;
    }
    void pocetak() override {
        if(broj_elemanata==0 || trenutni<0) throw std::logic_error("Lista je prazna");
        trenutni=0;
    }
    void kraj() override {
        if(broj_elemanata==0 || trenutni<0) throw std::logic_error("Lista je prazna");
        trenutni=broj_elemanata-1;
    }
    void obrisi() override {
        if(broj_elemanata==0 || trenutni<0){
            throw std::logic_error("Lista prazna");
        }
        for(int i=trenutni;i<broj_elemanata-1;i++){
            elementi[i]=elementi[i+1];
        }
        broj_elemanata--;
        if(broj_elemanata==0) trenutni=-1;
        else if(trenutni>=broj_elemanata) trenutni=broj_elemanata-1;
    }
    void dodajIza(const Tip& el) override {
        if(broj_elemanata==kapacitet){
            int novi_kapacitet=kapacitet*2;
            Tip *novi_elementi= new Tip[novi_kapacitet];
            for(int i=0;i<broj_elemanata;i++){
                novi_elementi[i]=elementi[i];
            }
            delete[] elementi;
            elementi= novi_elementi;
            kapacitet=novi_kapacitet;
        }
        if(broj_elemanata==0){
            elementi[0]=el;
            trenutni=0;
        }else{
            for(int i=broj_elemanata;i>trenutni+1;i--){
                elementi[i]=elementi[i-1];
            }
            elementi[trenutni+1]=el;
        }
        broj_elemanata++;
    }
    void dodajIspred(const Tip& el) override {
        if(broj_elemanata==kapacitet){
            int novi_kapacitet=kapacitet*2;
            Tip *novi_elementi= new Tip[novi_kapacitet];
            for(int i=0;i<broj_elemanata;i++){
                novi_elementi[i]=elementi[i];
            }
            delete[] elementi;
            elementi= novi_elementi;
            kapacitet=novi_kapacitet;
        }
        if(broj_elemanata==0){
            elementi[0]=el;
            trenutni=0;
        }else{
            for(int i=broj_elemanata;i>trenutni+1;i++){
                elementi[i]=elementi[i-1];
            }
            elementi[trenutni]=el;
            trenutni++;
        }
        broj_elemanata++;

    }
    Tip& operator[](int i) override{
      if(i<0 || i>=broj_elemanata) throw std::logic_error("Nevalidan indeks");
      return elementi[i];
    }
    const Tip& operator[](int i) const override {
        if(i<0 || i>=broj_elemanata) throw std::logic_error("Nevalidan indeks");
        return elementi[i];
    }
    NizLista& operator=(const NizLista &l){
        if(this==&l) return *this;
        Tip *novi_elementi= new Tip[l.kapacitet];
        try{
            for(int i=0;i<l.broj_elemanata;i++){
                novi_elementi[i]=l.elementi[i];
            }
        }catch(...){
            delete[] novi_elementi;
            throw;
        }
        delete[] elementi;
        elementi=novi_elementi;
        kapacitet=l.kapacitet;
        broj_elemanata=l.broj_elemanata;
        trenutni=l.trenutni;
        return *this;
    }

};

/**/







int main(){





    return 0;
}