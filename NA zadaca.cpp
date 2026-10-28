#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <algorithm>
#include <functional>
#include <typeinfo>




class Vector{

    std::vector<double> a;

    public:

   explicit Vector(int n){
    if(n<=0) throw std::range_error("Bad dimension");
    a.resize(n);
   }

   Vector(std::initializer_list<double> l) : a(l) {
      if(l.size()==0) throw std::range_error("Bad dimension");
   }
   int NElems() const {
      return a.size();
   }
   double &operator[](int i){
     return a[i];
   } 


   double operator[](int i) const{
     return a[i];
   }; 
   double &operator()(int i){
    if(i<1 || i>a.size()) throw std::range_error("Invalid index");
    return a[i-1];
   } 
   double operator()(int i) const{
    if(i<1 || i>a.size()) throw std::range_error("Invalid index");
    return a[i-1];
   } 
   double Norm() const {
    double suma=0;
    for(int i=0;i<a.size();i++){
        suma+=(a[i]*a[i]);
    }
    suma=sqrt(suma);
    return suma;
   }

   friend double VectorNorm(const Vector &v){
     double suma=0;
     for(int i=0;i<v.NElems();i++){
        suma+=(v[i]*v[i]);
     }
     suma=sqrt(suma);
     return suma;
   }

   double GetEpsilon() const{
       return 10*Norm()*std::numeric_limits<double>::epsilon();
   }

   void Print(char separator = '\n', double eps = -1){
    bool poziva=false;
    if(eps>0) poziva=true;

    if(separator=='\n'){
        for(int i=0;i<a.size();i++){
            if(!poziva){
            if(std::abs(a[i])<GetEpsilon()){
                a[i]=0;
                std::cout << a[i] << separator;
            }
            else std::cout<< a[i] << separator;
           }else{
            if(std::abs(a[i])<eps){
                a[i]=0;
                std::cout << a[i] << separator;
            }
            else std::cout<< a[i] << separator;
           }   
       }
    }else {
        for(int i=0;i<a.size();i++){
            if(!poziva){
            if(std::abs(a[i])<GetEpsilon()) a[i]=0;
            if(!(i==a.size()-1)){
                std::cout<< a[i] << separator;
            }else{
                std::cout<< a[i];
            }
          }else{
            if(std::abs(a[i])<eps){
                a[i]=0;
            }
            if(!(i==a.size()-1)){
                std::cout<< a[i] << separator;
            }else {
                std::cout<< a[i];
            }
          }
        }
    }

   }
   friend void PrintVector(const Vector &v, char separator = '\n', double eps = -1) {
    bool poziva=false;
    if(eps>0) poziva=true;

    for(int i=0;i<v.NElems();i++) {
        double vrijednost=v[i];

        if(!poziva) {
            if(std::abs(vrijednost)<v.GetEpsilon())
                vrijednost=0;
        } else {
            if(std::abs(vrijednost)<eps)
                vrijednost=0;
        }

        if(separator!='\n' && i > 0) std::cout << separator; // prvi element
        std::cout << vrijednost;

        if(separator == '\n') std::cout << separator; // funkcionise za zadnji
    }


   }
   friend Vector operator +(const Vector &v1, const Vector &v2){
    if(v1.NElems()!=v2.NElems()) throw std::domain_error("Incompatible formats");
    Vector pomocni(v1.NElems());
    for(int i=0;i<v1.NElems();i++){
        pomocni[i]=v1[i]+v2[i];
   }
   return pomocni;

  }
   Vector &operator +=(const Vector &v){
    if(NElems()!=v.NElems()) throw std::domain_error("Incompatible formats");
    for(int i=0;i<a.size();i++){
        a[i]+=v[i];
    }
    return *this;
   }
   friend Vector operator -(const Vector &v1, const Vector &v2){
    if(v1.NElems()!=v2.NElems()) throw std::domain_error("Incompatible formats");
    Vector pomocni(v1.NElems());
    for(int i=0;i<v1.NElems();i++){
        pomocni[i]=v1[i]-v2[i];
    }
    return pomocni;
   }
   Vector &operator -=(const Vector &v){
    if(NElems()!=v.NElems()) throw std::domain_error("Incompatible formats");
    for(int i=0;i<a.size();i++){
        a[i]-=v[i];
    }

    return *this;
   }


   friend Vector operator *(double s, const Vector &v){
    Vector pomocni(v.NElems());
    for(int i=0;i<v.NElems();i++){
        pomocni[i]=v[i]*s;
    }
    return pomocni;
   }
   friend Vector operator *(const Vector &v, double s){
    Vector pomocni(v.NElems());
    for(int i=0;i<v.NElems();i++){
        pomocni[i]=v[i]*s;
    }
    return pomocni;
   } 
   Vector &operator *=(double s){
    for(int i=0;i<a.size();i++){
        a[i]*=s;
    }
    return *this;
   }
   friend double operator *(const Vector &v1, const Vector &v2){
    if(v1.NElems()!=v2.NElems()) throw std::domain_error("Incompatible formats");
    double suma=0;
    for(int i=0;i<v1.NElems();i++){
      suma+=(v1[i]*v2[i]);
    }
    return suma;
   }
   friend Vector operator /(const Vector &v, double s){
    if(s==0) throw std::domain_error("Division by zero");
    Vector pomocni(v.NElems());
    for(int i=0;i<v.NElems();i++){
        pomocni[i]=v[i]/s;
    }

    return pomocni;
   } 
   Vector &operator /=(double s){
    if(s==0) throw std::domain_error("Division by zero");
    for(int i=0;i<NElems();i++){
        a[i]/=s;
    }
    return *this;
   }

  
 
};







int main(){

    int proslo = 0, palo = 0;

    auto Test = [&](const std::string &naziv, bool uslov) {
        std::cout << (uslov ? "[PASS] " : "[FAIL] ")
                  << naziv << "\n";
        if(uslov) proslo++;
        else palo++;
    };

    auto Jednako = [](double a, double b) {
        return std::abs(a - b) <=
            1e-12 * std::max({1.0, std::abs(a), std::abs(b)});
    };

    auto Isti = [&](const Vector &v,
                    std::initializer_list<double> ocekivano) {
        if(v.NElems() != int(ocekivano.size())) return false;
        int i = 0;
        for(double x : ocekivano)
            if(!Jednako(v[i++], x)) return false;
        return true;
    };

    auto Izuzetak = [&](auto funkcija,
                        const std::string &poruka,
                        bool domain) {
        try {
            funkcija();
        } catch(const std::domain_error &e) {
            return domain && e.what() == poruka;
        } catch(const std::range_error &e) {
            return !domain && e.what() == poruka;
        } catch(...) {
            return false;
        }
        return false;
    };

    auto Ispis = [](auto funkcija) {
        std::ostringstream izlaz;
        auto *stari = std::cout.rdbuf(izlaz.rdbuf());
        try {
            funkcija();
        } catch(...) {
            std::cout.rdbuf(stari);
            throw;
        }
        std::cout.rdbuf(stari);
        return izlaz.str();
    };

    std::cout << "\n=== 1. KONSTRUKTORI ===\n";

    Test("Dimenzija 1", Isti(Vector(1), {0}));
    Test("Dimenzija 5", Isti(Vector(5), {0,0,0,0,0}));
    Test("Lista sa jednim elementom", Isti(Vector{7}, {7}));
    Test("Lista sa negativnim elementima",
         Isti(Vector{-1,-2,-3}, {-1,-2,-3}));
    Test("Lista sa decimalnim elementima",
         Isti(Vector{1.5,-2.25,3.75}, {1.5,-2.25,3.75}));

    Test("Dimenzija 0 - izuzetak",
         Izuzetak([] { Vector v(0); },
                  "Bad dimension", false));
    Test("Negativna dimenzija - izuzetak",
         Izuzetak([] { Vector v(-5); },
                  "Bad dimension", false));
    Test("Prazna lista - izuzetak",
         Izuzetak([] { Vector v{}; },
                  "Bad dimension", false));

    std::cout << "\n=== 2. INDEKSIRANJE ===\n";

    Vector a{10,20,30,40};
    const Vector ca{5,6,7};

    Test("NElems", a.NElems() == 4);
    Test("[] prvi element", a[0] == 10);
    Test("[] zadnji element", a[3] == 40);
    Test("() prvi element", a(1) == 10);
    Test("() zadnji element", a(4) == 40);
    Test("const []", ca[1] == 6);
    Test("const ()", ca(3) == 7);

    a[0] = 100;
    Test("Izmjena preko []", a[0] == 100);
    a(4) = 400;
    Test("Izmjena preko ()", a[3] == 400);

    Test("Indeks 0 - izuzetak",
         Izuzetak([&] { (void)a(0); },
                  "Invalid index", false));
    Test("Negativan indeks - izuzetak",
         Izuzetak([&] { (void)a(-1); },
                  "Invalid index", false));
    Test("Prevelik indeks - izuzetak",
         Izuzetak([&] { (void)a(5); },
                  "Invalid index", false));
    Test("const indeks 0 - izuzetak",
         Izuzetak([&] { (void)ca(0); },
                  "Invalid index", false));
    Test("const prevelik indeks - izuzetak",
         Izuzetak([&] { (void)ca(4); },
                  "Invalid index", false));

    std::cout << "\n=== 3. NORME I EPSILON ===\n";

    Vector n1{3,4};
    Vector n2{0,0,0};
    Vector n3{-3,-4};
    Vector n4{1,2,2};
    Vector n5{1e-10,0};

    Test("Norm 3-4-5", Jednako(n1.Norm(), 5));
    Test("VectorNorm 3-4-5", Jednako(VectorNorm(n1), 5));
    Test("Norm nultog vektora", n2.Norm() == 0);
    Test("Norm negativnih elemenata", Jednako(n3.Norm(), 5));
    Test("Norm 3D vektora", Jednako(n4.Norm(), 3));
    Test("Norm malih brojeva",
         std::abs(n5.Norm()-1e-10) < 1e-24);

    double eps = std::numeric_limits<double>::epsilon();

    Test("GetEpsilon za (3,4)",
         Jednako(n1.GetEpsilon(), 50*eps));
    Test("GetEpsilon nultog vektora",
         n2.GetEpsilon() == 0);
    Test("GetEpsilon za (1,2,2)",
         Jednako(n4.GetEpsilon(), 30*eps));

    std::cout << "\n=== 4. SABIRANJE I ODUZIMANJE ===\n";

    Vector x{1,2,3};
    Vector y{4,5,6};
    Vector z{0,0,0};

    Test("Sabiranje", Isti(x+y, {5,7,9}));
    Test("Oduzimanje", Isti(x-y, {-3,-3,-3}));
    Test("Sabiranje sa nulom", Isti(x+z, {1,2,3}));
    Test("Oduzimanje samog sebe", Isti(x-x, {0,0,0}));
    Test("Original x nepromijenjen", Isti(x, {1,2,3}));
    Test("Original y nepromijenjen", Isti(y, {4,5,6}));

    Test("Sabiranje razlicitih dimenzija",
         Izuzetak([&] {
             Vector r = x + Vector{1,2};
         }, "Incompatible formats", true));

    Test("Oduzimanje razlicitih dimenzija",
         Izuzetak([&] {
             Vector r = x - Vector{1,2};
         }, "Incompatible formats", true));

    std::cout << "\n=== 5. MNOZENJE ===\n";

    Test("Skalar lijevo", Isti(3*x, {3,6,9}));
    Test("Skalar desno", Isti(x*3, {3,6,9}));
    Test("Negativni skalar", Isti(x*(-2), {-2,-4,-6}));
    Test("Mnozenje nulom", Isti(x*0, {0,0,0}));
    Test("Mnozenje jedinicom", Isti(x*1, {1,2,3}));
    Test("Decimalni skalar", Isti(x*0.5, {0.5,1,1.5}));

    Test("Skalarni proizvod", Jednako(x*y, 32));
    Test("Skalarni proizvod sa nulom", x*z == 0);
    Test("Skalarni proizvod samog sebe", x*x == 14);
    Test("Ortogonalni vektori",
         Vector{1,0} * Vector{0,1} == 0);
    Test("Negativni skalarni proizvod",
         Vector{1,2} * Vector{-3,-4} == -11);

    Test("Skalarni proizvod razlicitih dimenzija",
         Izuzetak([&] {
             double r = x * Vector{1,2};
             (void)r;
         }, "Incompatible formats", true));

    std::cout << "\n=== 6. DIJELJENJE ===\n";

    Test("Dijeljenje sa 2", Isti(x/2, {0.5,1,1.5}));
    Test("Dijeljenje negativnim skalarom",
         Isti(x/(-2), {-0.5,-1,-1.5}));
    Test("Dijeljenje jedinicom", Isti(x/1, {1,2,3}));
    Test("Dijeljenje velikim brojem",
         Isti(Vector{100,200}/100, {1,2}));

    Test("Dijeljenje nulom",
         Izuzetak([&] {
             Vector r = x/0.0;
         }, "Division by zero", true));

    std::cout << "\n=== 7. OPERATORI DODJELE ===\n";

    Vector d{1,2,3};
    d += Vector{4,5,6};
    Test("operator +=", Isti(d, {5,7,9}));

    d -= Vector{4,5,6};
    Test("operator -=", Isti(d, {1,2,3}));

    d *= 3;
    Test("operator *=", Isti(d, {3,6,9}));

    d /= 3;
    Test("operator /=", Isti(d, {1,2,3}));

    d += d;
    Test("Samododavanje d+=d", Isti(d, {2,4,6}));

    d -= d;
    Test("Samooduzimanje d-=d", Isti(d, {0,0,0}));

    Vector e{2,4};
    (e *= 2) *= 3;
    Test("U lancu *= ", Isti(e, {12,24}));

    (e /= 2) /= 3;
    Test("U lancu /= ", Isti(e, {2,4}));

    Vector f{1,2};
    (f += Vector{3,4}) += Vector{5,6};
    Test("U lancu +=", Isti(f, {9,12}));

    Test("+= razlicite dimenzije",
         Izuzetak([&] {
             Vector q{1,2};
             q += Vector{1,2,3};
         }, "Incompatible formats", true));

    Test("-= razlicite dimenzije",
         Izuzetak([&] {
             Vector q{1,2};
             q -= Vector{1,2,3};
         }, "Incompatible formats", true));

    Test("/= nulom",
         Izuzetak([&] {
             Vector q{1,2};
             q /= 0;
         }, "Division by zero", true));

    std::cout << "\n=== 8. PRINT ===\n";

    Vector p{1,2,3};

    Test("Print default",
         Ispis([&] { p.Print(); }) == "1\n2\n3\n");

    Test("Print razmak",
         Ispis([&] { p.Print(' '); }) == "1 2 3");

    Test("Print zarez",
         Ispis([&] { p.Print(','); }) == "1,2,3");

    Test("PrintVector",
         Ispis([&] { PrintVector(p, ';'); }) == "1;2;3");

    Test("Print jedan element",
         Ispis([] { Vector{7}.Print(','); }) == "7");

    Test("Print jedan element default",
         Ispis([] { Vector{7}.Print(); }) == "7\n");

    Vector sitni{1e-10, -1e-10, 1, 0};

    Test("Print eksplicitni epsilon",
         Ispis([&] {
             sitni.Print(' ', 1e-9);
         }) == "0 0 1 0");

    Test("Print epsilon nula",
         Ispis([&] {
             Vector{0,1}.Print(' ', 0);
         }) == "0 1");

    Test("Print negativni brojevi",
         Ispis([] {
             Vector{-2,-3,4}.Print(',');
         }) == "-2,-3,4");

    std::cout << "\n=== 9. KOPIRANJE ===\n";

    Vector original{1,2,3};
    Vector kopija(original);
    kopija[0] = 99;

    Test("Kopirni konstruktor",
         Isti(kopija, {99,2,3}));
    Test("Original nakon kopiranja",
         Isti(original, {1,2,3}));

    Vector dodjela{0};
    dodjela = original;
    dodjela[1] = 77;

    Test("Operator dodjele",
         Isti(dodjela, {1,77,3}));
    Test("Original nakon dodjele",
         Isti(original, {1,2,3}));

std::cout << "\n=== 10. RUBNI SLUCAJEVI ===\n";

Vector u{1e-15, 1};
Test("Default epsilon uklanja sitni broj",
     Ispis([&] { u.Print(' '); }) == "0 1");

Vector v{0.5, -0.5, 0};
Test("Dijeljenje decimalnim brojem",
     Isti(v/0.5, {1,-1,0}));

Vector w{1,2,3};
Test("Kombinacija operacija",
     Isti(2*w - w/2, {1.5,3,4.5}));

Test("Skalarni proizvod komutativan",
     Jednako(Vector{2,3} * Vector{4,5},
             Vector{4,5} * Vector{2,3}));

Vector r{1,2,3};
r *= 0;
Test("Mnozenje sa nulom preko *=",
     Isti(r, {0,0,0}));

Vector s{1,2,3};
s /= -1;
Test("Promjena predznaka preko /=",
     Isti(s, {-1,-2,-3}));

Vector h{1,2,3};
Test("Negativna tolerancija koristi GetEpsilon",
     Ispis([&] { h.Print(',', -5); }) == "1,2,3");


    std::cout << "\n============================\n";
    std::cout << "UKUPNO: " << proslo+palo << "\n";
    std::cout << "PROSLO: " << proslo << "\n";
    std::cout << "PALO: " << palo << "\n";
    std::cout << "============================\n";

    return palo == 0 ? 0 : 1;
   
    return 0;
}