#include <iostream>
#include <stdexcept>
#include <utility>


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

        try{ 
          for(int i=0;i<l.broj_elemanata;i++){
            elementi[i]=l.elementi[i];
          }
       }catch(...){
        delete[] elementi;
        throw;
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
        if(broj_elemanata==0 ) throw std::logic_error("Lista je prazna");
        trenutni=0;
    }
    void kraj() override {
        if(broj_elemanata==0) throw std::logic_error("Lista je prazna");
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
            for(int i=broj_elemanata;i>trenutni;i--){
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

// trenutni const bez const
// prethodni sljedeci bool
// pocetak kraj void
// obrisi dodajIspred dodajIza operator[] operator []


template <typename Tip>

class JednostrukaLista : public Lista<Tip>{
    struct Cvor{
        Tip informacija;
        Cvor* sljedeci;
        Cvor(const Tip& informacija,Cvor *sljedeci=nullptr) : informacija(informacija), sljedeci(sljedeci) {}
    };
    int broj_el;
    Cvor *prvi;  // morao preimenovati zbog imena metoda
    Cvor *trenutni;
    Cvor *zadnji;
    
  public: 
  JednostrukaLista() : broj_el(0), prvi(nullptr),trenutni(nullptr),zadnji(nullptr) {}
  ~JednostrukaLista(){
    while(prvi!=nullptr){
        Cvor *pomocni=prvi;
        prvi=prvi->sljedeci;
        delete pomocni;
    }
  }
  JednostrukaLista(const JednostrukaLista& l) : broj_el(0), prvi(nullptr), trenutni(nullptr), zadnji(nullptr) {
    Cvor* pomocni = l.prvi;
    try {
        while(pomocni != nullptr) {
            Cvor* novi = new Cvor(pomocni->informacija);
            if(prvi==nullptr) {
                prvi = novi;
                trenutni = novi;
                zadnji = novi;
            } else {
                zadnji->sljedeci = novi;
                zadnji = novi;
            }
            if(pomocni==l.trenutni) trenutni = novi;

            broj_el++;
            pomocni = pomocni->sljedeci;
        }
    }
    catch(...) {
        while(prvi != nullptr) {
            Cvor* brise = prvi;
            prvi = prvi->sljedeci;
            delete brise;
        }
        throw;
    }
  }

  int brojElemenata() const override{
    return broj_el;
  }
  Tip& trenutni() override{
    if(trenutni==nullptr) throw std::logic_error("Lista je prazna");
    return trenutni->informacija;
  }
  const Tip& trenutni() const override {
    if(trenutni==nullptr) throw std::logic_error("Lista je prazna");
    return trenutni->informacija;
  }
  bool prethodni() override {
    if(broj_el==0) throw std::logic_error("Lista je prazna");
    // ideja je da preusmjerim trenutni na prethodni tako sto cu napravit pomocni cvor
    if(prvi==trenutni) return false;
    Cvor *pomocni=prvi;
    while(pomocni->sljedeci!=trenutni){
        pomocni=pomocni->sljedeci;
    }
    trenutni=pomocni;
    return true;
  }
  bool sljedeci() override{
    if(broj_el==0) throw std::logic_error("Lista je prazna");
    if(zadnji==trenutni) return false;
    trenutni=trenutni->sljedeci;
    return true;
  }
  void kraj() override{
    if(broj_el==0) throw std::logic_error("Lista je prazna");
    trenutni=zadnji;
  }
  void pocetak() override{
    if(broj_el==0) throw std::logic_error("Lista je prazna");
    trenutni=prvi;
  }
  void obrisi() override{
    if(trenutni==nullptr) throw std::logic_error("Lista je prazna");
    Cvor *pomocni=trenutni;
    if(trenutni==prvi){
        prvi=prvi->sljedeci;
        trenutni=prvi;
        if(prvi==nullptr) zadnji=nullptr;
    }else{
        Cvor *prethodni=prvi;
        while(prethodni->sljedeci!=trenutni){
            prethodni=prethodni->sljedeci;
        }
        
        if(trenutni==zadnji){
            zadnji=prethodni;
            trenutni=prethodni;
        }else{
            trenutni=trenutni->sljedeci;
        }
        prethodni->sljedeci=pomocni->sljedeci;

    }
    delete pomocni;
    broj_el--;
  }
  void dodajIza(const Tip &vrijednost) override{
    if(trenutni==nullptr){ // ako je sve prazno
        trenutni=new Cvor(vrijednost);
        zadnji=trenutni;
        prvi=zadnji;
        broj_el++;
        return;
    }
    Cvor *novi= new Cvor(vrijednost,trenutni->sljedeci);
    
    trenutni->sljedeci=novi;
    if(trenutni==zadnji) zadnji=novi;
    broj_el++;
  }
  void dodajIspred(const Tip &vrijednost) override{

    if(trenutni==nullptr){ // ako je sve prazno
        trenutni=new Cvor(vrijednost);
        prvi=trenutni;
        zadnji=trenutni;
        broj_el++;
        return;
    }
    Cvor *novi=new Cvor(vrijednost,trenutni);
    if(trenutni==prvi) prvi=novi;
    else{
        Cvor *prethodni=prvi;
        while(prethodni->sljedeci != trenutni){
            prethodni=prethodni->sljedeci;
        }
        prethodni->sljedeci=novi;
    }
    broj_el++;
  }
  Tip& operator[](int i) override {
    if(i<0 || i>=broj_el) throw std::logic_error("Nevalidan indeks");

    Cvor* pomocni = prvi;

    for(int j=0;j<i;j++){
        pomocni=pomocni->sljedeci;
    }
    return pomocni->informacija;
  }
  const Tip& operator[](int i) const override {
    if(i<0 || i>=broj_el) throw std::logic_error("Nevalidan indeks");

    const Cvor* pomocni = prvi;

    for(int j=0;j<i;j++){
        pomocni=pomocni->sljedeci;
    }
    return pomocni->informacija;
  }
  
  JednostrukaLista& operator=(const JednostrukaLista& l) {
    if(this == &l) return *this;

    JednostrukaLista kopija(l);

    std::swap(prvi, kopija.prvi);
    std::swap(trenutni, kopija.trenutni);
    std::swap(zadnji, kopija.zadnji);
    std::swap(broj_el, kopija.broj_el);

    return *this;
}






  





};






int main(){





    return 0;
}