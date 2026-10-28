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
            return std::sqrt(suma);
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
            if(eps>=0) poziva=true;

            for(int i=0;i<NElems();i++) {
                double vrijednost=a[i];

                if(!poziva) {
                    if(std::abs(vrijednost)<GetEpsilon())
                        vrijednost=0;
                } else {
                    if(std::abs(vrijednost)<eps)
                        vrijednost=0;
                }

                if(separator!='\n' && i>0) std::cout << separator; // prvi element
                std::cout << vrijednost;

                if(separator == '\n') std::cout << separator; // funkcionise za zadnji
            }
           
        }
        friend void PrintVector(const Vector &v, char separator = '\n', double eps = -1) {
            bool poziva=false;
            if(eps>=0) poziva=true;

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

        class Matrix{

            std::vector<std::vector<double>> b;

            public:
            Matrix(int m, int n){
                if(m<=0 || n<=0) throw std::range_error("Bad dimension");
                b.resize(m,std::vector<double>(n,0));
            }
            Matrix(const Vector &v){
                b.resize(v.NElems(),std::vector<double>(1));
                for(int i=0;i<b.size();i++){
                b[i][0]=v[i];
                }
            }

            Matrix(std::initializer_list<std::vector<double>> l) :b(l){
                if(l.size()==0 || l.begin()->size()==0) throw std::range_error("Bad dimension");
                int x=l.begin()->size();
                for(const auto &v :l){
                    if(v.size()!=x) throw std::logic_error("Bad matrix"); 
                }

            }
            int NRows() const{
                return b.size();
            }
            int NCols() const{
            return b[0].size();
            }
            double *operator[](int i){
                return b[i].data();
            }
            const double *operator[](int i) const{
                return b[i].data();
            }
            double &operator()(int i, int j){
                if(i<1 || i>NRows() || j<1 || j>NCols()) throw std::range_error("Invalid index");
                return b[i-1][j-1]; 
            }
            double operator()(int i, int j) const{
                if(i<1 || i>NRows() || j<1 || j>NCols()) throw std::range_error("Invalid index");
                return b[i-1][j-1]; 
            }
            double Norm() const{
                double suma=0;
                for(int i=0;i<NRows();i++){
                    for(int j=0;j<NCols();j++){
                        suma+=(b[i][j]*b[i][j]);
                    }
                }
                return std::sqrt(suma);
            }
            friend double MatrixNorm(const Matrix &m){
                double suma=0;
                for(int i=0;i<m.NRows();i++){
                    for(int j=0;j<m.NCols();j++){
                        suma+=(m[i][j]*m[i][j]);
                    }
                }
                return std::sqrt(suma);
            }
            double GetEpsilon() const{
                return 10*Norm()*std::numeric_limits<double>::epsilon();
            }
            void Print(int width = 10, double eps = -1) const{

            double prag=0;
            if(eps<0) prag=GetEpsilon();
            else prag=eps;
            for(int i=0;i<NRows();i++){
                for(int j=0;j<NCols();j++){
                    double vrijednost=b[i][j];
                    if(std::abs(vrijednost)<prag) vrijednost=0;
                    std::cout<< std::setw(width) << vrijednost;
                }
                std::cout<< std::endl;
            }

            }
            friend void PrintMatrix(const Matrix &m, int width = 10, double eps = -1){
            double prag=0;
            if(eps<0) prag=m.GetEpsilon();
            else prag=eps;
            for(int i=0;i<m.NRows();i++){
                for(int j=0;j<m.NCols();j++){
                    double vrijednost=m[i][j];
                    if(std::abs(vrijednost)<prag) vrijednost=0;
                    std::cout<< std::setw(width) << vrijednost;
                }
                std::cout<< std::endl;
            }
            }
            friend Matrix operator +(const Matrix &m1, const Matrix &m2){
                if(m1.NRows()!=m2.NRows() || m1.NCols()!=m2.NCols()) throw std::domain_error("Incompatible formats");
                Matrix pomocna(m1.NRows(),m2.NCols());
                for(int i=0;i<m1.NRows();i++){
                    for(int j=0;j<m1.NCols();j++){
                    pomocna[i][j]=m1[i][j]+m2[i][j];
                    }
                }
                return pomocna;
            }
            Matrix &operator +=(const Matrix &m){
                if(NRows()!=m.NRows() || NCols()!=m.NCols()) throw std::domain_error("Incompatible formats");

                for(int i=0;i<NRows();i++){
                    for(int j=0;j<NCols();j++){
                        b[i][j]+=m[i][j];
                    }
                }
                return *this;
            }
            friend Matrix operator -(const Matrix &m1, const Matrix &m2){
                if(m1.NRows()!=m2.NRows() || m1.NCols()!=m2.NCols()) throw std::domain_error("Incompatible formats");
                Matrix pomocna(m1.NRows(),m2.NCols());
                for(int i=0;i<m1.NRows();i++){
                    for(int j=0;j<m2.NCols();j++){
                        pomocna[i][j]=(m1[i][j]-m2[i][j]);
                    }
                }
            return pomocna;
            }
            Matrix &operator -=(const Matrix &m){
                if(NRows()!=m.NRows() || NCols()!=m.NCols()) throw std::domain_error("Incompatible formats");
                for(int i=0;i<NRows();i++){
                    for(int j=0;j<NCols();j++){
                        b[i][j]-=m[i][j];
                    }
                }
                return *this;
            }
            friend Matrix operator *(double s, const Matrix &m){
                Matrix pomocna(m.NRows(),m.NCols());
                for(int i=0;i<m.NRows();i++){
                    for(int j=0;j<m.NCols();j++){
                        pomocna[i][j]=m[i][j]*s;
                    }
                }
                return pomocna;
            }
            friend Matrix operator *(const Matrix &m, double s){
                Matrix pomocna(m.NRows(),m.NCols());
                for(int i=0;i<m.NRows();i++){
                    for(int j=0;j<m.NCols();j++){
                        pomocna[i][j]=m[i][j]*s;
                    }
                }
                return pomocna;
            }
            Matrix &operator *=(double s){
                for(int i=0;i<NRows();i++){
                    for(int j=0;j<NCols();j++){
                        b[i][j]*=s;
                    }
                }
                return *this;
            }
            friend Matrix operator *(const Matrix &m1, const Matrix &m2){
                if(m1.NCols()!=m2.NRows()) throw std::domain_error("Incompatible formats");
                Matrix pomocna(m1.NRows(),m2.NCols());
                for(int i=0;i<m1.NRows();i++){
                    for(int j=0;j<m2.NCols();j++){
                        for(int k=0;k<m1.NCols();k++){
                            pomocna[i][j]+=m1[i][k]*m2[k][j];
                        }
                    }
                }
            return pomocna;
            }
            Matrix &operator *=(const Matrix &m){
                if(NCols()!=m.NRows()) throw std::domain_error("Incompatible formats");
                Matrix pomocna(NRows(),m.NCols());
                for(int i=0;i<NRows();i++){
                    for(int j=0;j<m.NCols();j++){
                        for(int k=0;k<NCols();k++){
                            pomocna[i][j]+=b[i][k]*m[k][j];
                        }
                    }
                }
            b=pomocna.b; 
            return *this;

            }
            friend Vector operator *(const Matrix &m, const Vector &v){
            if(m.NCols()!=v.NElems()) throw std::domain_error("Incompatible formats");
            Vector pomocni(m.NRows());
            for(int i=0;i<m.NRows();i++){
                double suma=0;
                for(int j=0;j<m.NCols();j++){
                    suma+=m[i][j]*v[j];
                }
                pomocni[i]=suma;
            }
            return pomocni;
            }

            friend Matrix Transpose(const Matrix &m){
                Matrix pomocna(m.NCols(),m.NRows());
                for(int i=0;i<m.NRows();i++){
                    for(int j=0;j<m.NCols();j++){
                        pomocna[j][i]=m[i][j];
                    }
                }
                return pomocna;
            }
            void Transpose(){
                bool kvadratna=false;
                if(NRows()==NCols()) kvadratna=true;
                if(kvadratna){
                    for(int i=0;i<NRows();i++){
                        for(int j=i+1;j<NCols();j++){
                            std::swap(b[i][j],b[j][i]);
                        }
                    }
                }else{
                Matrix pomocna(NCols(),NRows());
                for(int i=0;i<NRows();i++){
                    for(int j=0;j<NCols();j++){
                        pomocna[j][i]=b[i][j];
                    }
                }
                b=pomocna.b;
            
            }
            }

        };




namespace ZadacaTest {
int ukupno=0, proslo=0;
void Check(const std::string &ime, bool ok) {
    ++ukupno;
    if(ok) ++proslo;
    std::cout << (ok ? "[PASS] " : "[FAIL] ") << ime << '\n';
}
void Sekcija(const std::string &ime) { std::cout << "\n========== " << ime << " ==========\n"; }
bool Blizu(double a, double b, double rel=1e-12) {
    if(a==b) return true;
    if(!std::isfinite(a) || !std::isfinite(b)) return false;
    return std::abs(a-b) <= rel*std::max({1.0, std::abs(a), std::abs(b)});
}
bool V(const Vector &v, std::initializer_list<double> o) {
    if(v.NElems()!=int(o.size())) return false;
    int i=0;
    for(double x:o) if(!Blizu(v[i++],x)) return false;
    return true;
}
bool M(const Matrix &m, std::initializer_list<std::initializer_list<double>> o) {
    if(m.NRows()!=int(o.size())) return false;
    int i=0;
    for(auto red:o) {
        if(m.NCols()!=int(red.size())) return false;
        int j=0;
        for(double x:red) if(!Blizu(m[i][j++],x)) return false;
        ++i;
    }
    return true;
}
template<class E, class F>
bool Baca(F f, const std::string &poruka) {
    try { f(); }
    catch(const E &e) { return typeid(e)==typeid(E) && std::string(e.what())==poruka; }
    catch(...) { return false; }
    return false;
}
template<class F>
std::string Snimi(F f) {
    std::ostringstream s;
    std::streambuf *stari=std::cout.rdbuf(s.rdbuf());
    try { f(); }
    catch(...) { std::cout.rdbuf(stari); throw; }
    std::cout.rdbuf(stari);
    return s.str();
}
std::string Polje(double x, int width) {
    std::ostringstream s; s << std::setw(width) << x; return s.str();
}
}

int main() {
    using namespace ZadacaTest;
    const double eps=std::numeric_limits<double>::epsilon();
    std::cout << std::boolalpha;
    Sekcija("VECTOR: konstrukcija i pristup");
    Check("V dim 1, inicijalne nule", V(Vector(1),{0}));
    Check("V dim 6, inicijalne nule", V(Vector(6),{0,0,0,0,0,0}));
    Check("V lista pozitivnih", V(Vector{1,2,3},{1,2,3}));
    Check("V lista mjesovitih", V(Vector{-2,0,3.5},{-2,0,3.5}));
    Check("V dim 0", Baca<std::range_error>([]{Vector v(0);},"Bad dimension"));
    Check("V negativna dim", Baca<std::range_error>([]{Vector v(-4);},"Bad dimension"));
    Check("V prazna lista", Baca<std::range_error>([]{Vector v{};},"Bad dimension"));
    Vector v{10,20,30}; const Vector cv{4,5,6};
    Check("V NElems",v.NElems()==3);
    Check("V [] citanje",v[0]==10 && v[2]==30);
    Check("V () citanje",v(1)==10 && v(3)==30);
    Check("V const []",cv[0]==4 && cv[2]==6);
    Check("V const ()",cv(1)==4 && cv(3)==6);
    v[1]=77; Check("V [] pisanje",V(v,{10,77,30}));
    v(3)=-8; Check("V () pisanje",V(v,{10,77,-8}));
    Check("V () nula",Baca<std::range_error>([&]{(void)v(0);},"Invalid index"));
    Check("V () negativan",Baca<std::range_error>([&]{(void)v(-3);},"Invalid index"));
    Check("V () iznad",Baca<std::range_error>([&]{(void)v(4);},"Invalid index"));
    Check("V const () nula",Baca<std::range_error>([&]{(void)cv(0);},"Invalid index"));
    Check("V const () iznad",Baca<std::range_error>([&]{(void)cv(4);},"Invalid index"));
    Check("V [] povratni tip",(std::is_same<decltype(std::declval<Vector&>()[0]),double&>::value));
    Check("V const [] povratni tip",(std::is_same<decltype(std::declval<const Vector&>()[0]),double>::value));
    Check("V () povratni tip",(std::is_same<decltype(std::declval<Vector&>()(1)),double&>::value));
    Check("V const () povratni tip",(std::is_same<decltype(std::declval<const Vector&>()(1)),double>::value));
    Sekcija("VECTOR: norme, epsilon i ispis");
    Vector a{3,4}, zero{0,0,0};
    Check("V norma 3-4-5",Blizu(a.Norm(),5));
    Check("V prijateljska norma",Blizu(VectorNorm(a),5));
    Check("V norma 1D",Blizu(Vector{-7}.Norm(),7));
    Check("V norma 3D",Blizu(Vector{1,2,2}.Norm(),3));
    Check("V norma nula",zero.Norm()==0 && VectorNorm(zero)==0);
    Check("V epsilon 3-4-5",Blizu(a.GetEpsilon(),50*eps));
    Check("V epsilon nula",zero.GetEpsilon()==0);
    Check("V epsilon 1D",Blizu(Vector{2}.GetEpsilon(),20*eps));
    Check("V Print default",Snimi([&]{a.Print();})=="3\n4\n");
    Check("V Print razmak",Snimi([&]{a.Print(' ');})=="3 4");
    Check("V Print zarez",Snimi([&]{a.Print(',');})=="3,4");
    Check("V PrintVector default",Snimi([&]{PrintVector(a);})=="3\n4\n");
    Check("V PrintVector separator",Snimi([&]{PrintVector(a,';');})=="3;4");
    Check("V Print jedna komponenta",Snimi([]{Vector{9}.Print(',');})=="9");
    Check("V Print jedna komponenta newline",Snimi([]{Vector{9}.Print();})=="9\n");
    Vector tiny{1e-12,-1e-12,2};
    Check("V Print eksplicitni prag",Snimi([&]{tiny.Print(' ',1e-9);})=="0 0 2");
    Check("V Print eps=0",Snimi([&]{tiny.Print(' ',0);})=="1e-12 -1e-12 2");
    Check("V Print podrazumijevani prag",Snimi([]{Vector{1e-16,1}.Print(',');})=="0,1");
    Check("V PrintVector prag",Snimi([&]{PrintVector(tiny,',',1e-9);})=="0,0,2");
    Check("V Print ne mijenja vrijednosti",V(tiny,{1e-12,-1e-12,2}));
    Check("V Print negativni",Snimi([]{Vector{-2,-3}.Print(';');})=="-2;-3");
    Sekcija("VECTOR: racunski operatori");
    Vector x{1,2,3}, y{4,5,6};
    Check("V +",V(x+y,{5,7,9}));
    Check("V -",V(x-y,{-3,-3,-3}));
    Check("V + nula",V(x+Vector{0,0,0},{1,2,3}));
    Check("V - sam od sebe",V(x-x,{0,0,0}));
    Check("V skalar lijevo",V(3*x,{3,6,9}));
    Check("V skalar desno",V(x*3,{3,6,9}));
    Check("V negativan skalar",V(-2*x,{-2,-4,-6}));
    Check("V skalar nula",V(x*0,{0,0,0}));
    Check("V skalar decimalan",V(x*0.5,{0.5,1,1.5}));
    Check("V dot",Blizu(x*y,32));
    Check("V dot sam",Blizu(x*x,14));
    Check("V dot ortogonalni",Blizu(Vector{1,0}*Vector{0,1},0));
    Check("V dot negativni",Blizu(Vector{1,2}*Vector{-3,-4},-11));
    Check("V /2",V(x/2,{0.5,1,1.5}));
    Check("V /-2",V(x/-2,{-0.5,-1,-1.5}));
    Check("V /0.5",V(x/0.5,{2,4,6}));
    Check("V originali nepromijenjeni",V(x,{1,2,3})&&V(y,{4,5,6}));
    Vector d{1,2,3};
    d+=y; Check("V +=",V(d,{5,7,9}));
    d-=y; Check("V -=",V(d,{1,2,3}));
    d*=3; Check("V *=",V(d,{3,6,9}));
    d/=3; Check("V /=",V(d,{1,2,3}));
    d+=d; Check("V += sam",V(d,{2,4,6}));
    d-=d; Check("V -= sam",V(d,{0,0,0}));
    Vector q{1,2}; (q*=2)*=3; Check("V ulanac *=",V(q,{6,12}));
    (q/=2)/=3; Check("V ulanac /=",V(q,{1,2}));
    (q+=Vector{1,1})+=Vector{2,2}; Check("V ulanac +=",V(q,{4,5}));
    (q-=Vector{1,1})-=Vector{1,1}; Check("V ulanac -=",V(q,{2,3}));
    Check("V + dimenzije",Baca<std::domain_error>([&]{(void)(x+Vector{1});},"Incompatible formats"));
    Check("V - dimenzije",Baca<std::domain_error>([&]{(void)(x-Vector{1});},"Incompatible formats"));
    Check("V dot dimenzije",Baca<std::domain_error>([&]{(void)(x*Vector{1});},"Incompatible formats"));
    Check("V += dimenzije",Baca<std::domain_error>([]{Vector t{1,2};t+=Vector{1};},"Incompatible formats"));
    Check("V -= dimenzije",Baca<std::domain_error>([]{Vector t{1,2};t-=Vector{1};},"Incompatible formats"));
    Check("V /0",Baca<std::domain_error>([&]{(void)(x/0.0);},"Division by zero"));
    Check("V /=0",Baca<std::domain_error>([]{Vector t{1};t/=0.0;},"Division by zero"));
    Vector original{2,3}; Vector copy(original);copy[0]=99;
    Check("V duboka kopija",V(original,{2,3})&&V(copy,{99,3}));
    Vector assigned{1};assigned=original;assigned[1]=77;
    Check("V duboka dodjela",V(original,{2,3})&&V(assigned,{2,77}));
    assigned=assigned; Check("V samododjela",V(assigned,{2,77}));

    Sekcija("MATRIX: konstrukcija i indeksiranje");
    Check("M 1x1 nula",M(Matrix(1,1),{{0}}));
    Check("M 2x3 nule",M(Matrix(2,3),{{0,0,0},{0,0,0}}));
    Check("M lista 2x3",M(Matrix{{1,2,3},{4,5,6}},{{1,2,3},{4,5,6}}));
    Check("M lista 1x3",M(Matrix{{-1,0,2}},{{-1,0,2}}));
    Check("M iz Vector",M(Matrix(Vector{2,4,6}),{{2},{4},{6}}));
    Check("M iz Vector 1D",M(Matrix(Vector{8}),{{8}}));
    Check("M dimenzija redovi 0",Baca<std::range_error>([]{Matrix m(0,2);},"Bad dimension"));
    Check("M dimenzija kolone 0",Baca<std::range_error>([]{Matrix m(2,0);},"Bad dimension"));
    Check("M dimenzija negativna",Baca<std::range_error>([]{Matrix m(-1,2);},"Bad dimension"));
    Check("M obje negativne",Baca<std::range_error>([]{Matrix m(-1,-1);},"Bad dimension"));
    Check("M prazna lista",Baca<std::range_error>([]{Matrix m{};},"Bad dimension"));
    Check("M prazan red",Baca<std::range_error>([]{Matrix m{{}};},"Bad dimension"));
    Check("M vise praznih redova",Baca<std::range_error>([]{Matrix m{{},{}};},"Bad dimension"));
    Check("M grbava 2 i 1",Baca<std::logic_error>([]{Matrix m{{1,2},{3}};},"Bad matrix"));
    Check("M grbava 1 i 2",Baca<std::logic_error>([]{Matrix m{{1},{2,3}};},"Bad matrix"));
    Matrix A{{1,2,3},{4,5,6}}; const Matrix CA{{7,8},{9,10}};
    Check("M NRows NCols",A.NRows()==2&&A.NCols()==3);
    Check("M [] citanje",A[0][0]==1&&A[1][2]==6);
    Check("M () citanje",A(1,1)==1&&A(2,3)==6);
    Check("M const []",CA[1][1]==10);
    Check("M const ()",CA(2,1)==9);
    A[0][1]=20; Check("M [] pisanje",M(A,{{1,20,3},{4,5,6}}));
    A(2,3)=60; Check("M () pisanje",M(A,{{1,20,3},{4,5,60}}));
    Check("M [] povratni tip",(std::is_same<decltype(std::declval<Matrix&>()[0]),double*>::value));
    Check("M const [] povratni tip",(std::is_same<decltype(std::declval<const Matrix&>()[0]),const double*>::value));
    Check("M () povratni tip",(std::is_same<decltype(std::declval<Matrix&>()(1,1)),double&>::value));
    Check("M const () povratni tip",(std::is_same<decltype(std::declval<const Matrix&>()(1,1)),double>::value));
    Check("M () red 0",Baca<std::range_error>([&]{(void)A(0,1);},"Invalid index"));
    Check("M () kolona 0",Baca<std::range_error>([&]{(void)A(1,0);},"Invalid index"));
    Check("M () red -1",Baca<std::range_error>([&]{(void)A(-1,1);},"Invalid index"));
    Check("M () kolona -1",Baca<std::range_error>([&]{(void)A(1,-1);},"Invalid index"));
    Check("M () red previsok",Baca<std::range_error>([&]{(void)A(3,1);},"Invalid index"));
    Check("M () kolona previsoka",Baca<std::range_error>([&]{(void)A(1,4);},"Invalid index"));
    Check("M const () red 0",Baca<std::range_error>([&]{(void)CA(0,1);},"Invalid index"));
    Check("M const () kolona previsoka",Baca<std::range_error>([&]{(void)CA(1,3);},"Invalid index"));

    Sekcija("MATRIX: norma, epsilon, ispis");
    Matrix N{{1,2},{3,4}};
    Check("M Frobenius norma",Blizu(N.Norm(),std::sqrt(30.0)));
    Check("M MatrixNorm",Blizu(MatrixNorm(N),std::sqrt(30.0)));
    Check("M norma 1x1 negativan",Blizu(Matrix{{-7}}.Norm(),7));
    Check("M norma nula",Matrix(3,2).Norm()==0);
    Check("M epsilon",Blizu(N.GetEpsilon(),10*std::sqrt(30.0)*eps));
    Check("M epsilon nula",Matrix(2,2).GetEpsilon()==0);
    Check("M Print width 3",Snimi([&]{N.Print(3);})=="  1  2\n  3  4\n");
    Check("M Print width 5",Snimi([&]{N.Print(5);})=="    1    2\n    3    4\n");
    Check("M Print default",Snimi([&]{N.Print();})=="         1         2\n         3         4\n");
    Check("M PrintMatrix width",Snimi([&]{PrintMatrix(N,3);})=="  1  2\n  3  4\n");
    Check("M PrintMatrix default",Snimi([&]{PrintMatrix(N);})=="         1         2\n         3         4\n");
    Matrix small{{1e-12,-1e-12},{2,0}};
    Check("M Print eps 1e-9",Snimi([&]{small.Print(3,1e-9);})=="  0  0\n  2  0\n");
    Check("M PrintMatrix eps 1e-9",Snimi([&]{PrintMatrix(small,3,1e-9);})=="  0  0\n  2  0\n");
    Check("M Print eps 0",Snimi([&]{small.Print(0,0);})=="1e-12-1e-12\n20\n");
    Check("M Print ne mijenja matricu",M(small,{{1e-12,-1e-12},{2,0}}));
    Check("M Print 1x1",Snimi([]{Matrix{{7}}.Print(2);})==" 7\n");
    Check("M Print veci od width",Snimi([]{Matrix{{12345}}.Print(2);})=="12345\n");
    Check("M Print negativni",Snimi([]{Matrix{{-1,-20}}.Print(4);})=="  -1 -20\n");

    Sekcija("MATRIX: +, -, skalar i dodjele");
    Matrix P{{1,2},{3,4}}, Q{{5,6},{7,8}};
    Check("M +",M(P+Q,{{6,8},{10,12}}));
    Check("M -",M(P-Q,{{-4,-4},{-4,-4}}));
    Check("M + nula",M(P+Matrix(2,2),{{1,2},{3,4}}));
    Check("M - sam",M(P-P,{{0,0},{0,0}}));
    Check("M skalar lijevo",M(2*P,{{2,4},{6,8}}));
    Check("M skalar desno",M(P*2,{{2,4},{6,8}}));
    Check("M skalar negativan",M(-2*P,{{-2,-4},{-6,-8}}));
    Check("M skalar decimalan",M(P*0.5,{{0.5,1},{1.5,2}}));
    Check("M skalar nula",M(P*0,{{0,0},{0,0}}));
    Check("M originali nepromijenjeni",M(P,{{1,2},{3,4}})&&M(Q,{{5,6},{7,8}}));
    Matrix D=P; D+=Q; Check("M +=",M(D,{{6,8},{10,12}}));
    D-=Q; Check("M -=",M(D,{{1,2},{3,4}}));
    D*=3; Check("M *= skalar",M(D,{{3,6},{9,12}}));
    D+=D; Check("M += sam",M(D,{{6,12},{18,24}}));
    D-=D; Check("M -= sam",M(D,{{0,0},{0,0}}));
    Matrix chain{{1,2}}; (chain*=2)*=3;
    Check("M ulanac *= skalar",M(chain,{{6,12}}));
    (chain+=Matrix{{1,1}})+=Matrix{{2,2}};
    Check("M ulanac +=",M(chain,{{9,15}}));
    (chain-=Matrix{{1,1}})-=Matrix{{2,2}};
    Check("M ulanac -=",M(chain,{{6,12}}));
    Check("M + razlicit broj redova",Baca<std::domain_error>([&]{(void)(P+Matrix(3,2));},"Incompatible formats"));
    Check("M + razlicit broj kolona",Baca<std::domain_error>([&]{(void)(P+Matrix(2,3));},"Incompatible formats"));
    Check("M - razlicit broj redova",Baca<std::domain_error>([&]{(void)(P-Matrix(3,2));},"Incompatible formats"));
    Check("M - razlicit broj kolona",Baca<std::domain_error>([&]{(void)(P-Matrix(2,3));},"Incompatible formats"));
    Check("M += razlicite dimenzije",Baca<std::domain_error>([]{Matrix a(2,2);a+=Matrix(2,3);},"Incompatible formats"));
    Check("M -= razlicite dimenzije",Baca<std::domain_error>([]{Matrix a(2,2);a-=Matrix(3,2);},"Incompatible formats"));

    Sekcija("MATRIX: mat-mat i mat-vektor");
    Matrix L{{1,2,3},{4,5,6}}, R{{7,8},{9,10},{11,12}};
    Check("M 2x3 * 3x2",M(L*R,{{58,64},{139,154}}));
    Check("M 3x2 * 2x3",M(R*L,{{39,54,69},{49,68,87},{59,82,105}}));
    Check("M 2x2 * 2x2",M(P*Q,{{19,22},{43,50}}));
    Check("M 1x3 * 3x1",M(Matrix{{1,2,3}}*Matrix{{4},{5},{6}},{{32}}));
    Check("M 3x1 * 1x2",M(Matrix{{1},{2},{3}}*Matrix{{4,5}},{{4,5},{8,10},{12,15}}));
    Check("M identitet desno",M(P*Matrix{{1,0},{0,1}},{{1,2},{3,4}}));
    Check("M identitet lijevo",M(Matrix{{1,0},{0,1}}*P,{{1,2},{3,4}}));
    Check("M proizvod s nulom",M(P*Matrix(2,2),{{0,0},{0,0}}));
    Check("M originali nakon proizvoda",M(L,{{1,2,3},{4,5,6}})&&M(R,{{7,8},{9,10},{11,12}}));
    Check("M * nekompatibilne dimenzije",Baca<std::domain_error>([&]{(void)(L*Matrix(2,2));},"Incompatible formats"));
    Matrix mul=P;mul*=Q;Check("M *= matrica",M(mul,{{19,22},{43,50}}));
    Matrix nonSquare=L;nonSquare*=R;
    Check("M *= mijenja dimenzije",M(nonSquare,{{58,64},{139,154}})&&nonSquare.NCols()==2);
    Matrix self{{1,2},{3,4}};self*=self;
    Check("M *= sama sobom",M(self,{{7,10},{15,22}}));
    Check("M *= nekompatibilno",Baca<std::domain_error>([]{Matrix a(2,3);a*=Matrix(2,2);},"Incompatible formats"));
    Check("M * V 2x3",V(L*Vector{1,2,3},{14,32}));
    Check("M * V 3x2",V(R*Vector{2,3},{38,48,58}));
    Check("M * V nula",V(L*Vector{0,0,0},{0,0}));
    Check("M * V 1x1",V(Matrix{{7}}*Vector{3},{21}));
    Check("M * V nekompatibilno",Baca<std::domain_error>([&]{(void)(L*Vector{1,2});},"Incompatible formats"));

    Sekcija("MATRIX: transponovanje");
    Check("Transpose slobodna 2x3",M(Transpose(L),{{1,4},{2,5},{3,6}}));
    Check("Transpose slobodna 3x2",M(Transpose(R),{{7,9,11},{8,10,12}}));
    Check("Transpose slobodna kvadratna",M(Transpose(P),{{1,3},{2,4}}));
    Check("Transpose slobodna 1x3",M(Transpose(Matrix{{1,2,3}}),{{1},{2},{3}}));
    Check("Transpose slobodna 3x1",M(Transpose(Matrix{{1},{2},{3}}),{{1,2,3}}));
    Check("Transpose slobodna 1x1",M(Transpose(Matrix{{7}}),{{7}}));
    Check("Transpose ne mijenja original",M(L,{{1,2,3},{4,5,6}}));
    Matrix T1=L;T1.Transpose();Check("Transpose metoda 2x3",M(T1,{{1,4},{2,5},{3,6}}));
    T1.Transpose();Check("Transpose metoda dvaput",M(T1,{{1,2,3},{4,5,6}}));
    Matrix T2{{1,2,3},{4,5,6},{7,8,9}};T2.Transpose();
    Check("Transpose metoda 3x3",M(T2,{{1,4,7},{2,5,8},{3,6,9}}));
    Matrix T3{{8}};T3.Transpose();Check("Transpose metoda 1x1",M(T3,{{8}}));
    Matrix T4{{1,2,3}};T4.Transpose();Check("Transpose metoda 1x3",M(T4,{{1},{2},{3}}));
    T4.Transpose();Check("Transpose metoda 3x1",M(T4,{{1,2,3}}));
    Check("Transpose dvaput slobodna",M(Transpose(Transpose(L)),{{1,2,3},{4,5,6}}));

    Sekcija("MATRIX: kopiranje, dodjela, identiteti");
    Matrix source{{1,2},{3,4}};Matrix copied(source);copied[0][0]=99;
    Check("M duboka kopija",M(source,{{1,2},{3,4}})&&M(copied,{{99,2},{3,4}}));
    Matrix target(1,1);target=source;target[1][1]=88;
    Check("M duboka dodjela i promjena dimenzija",M(source,{{1,2},{3,4}})&&M(target,{{1,2},{3,88}}));
    target=target;Check("M samododjela",M(target,{{1,2},{3,88}}));
    Check("M distributivnost",M(P*(Q+P),{{26,32},{58,72}}));
    Check("M transpose proizvoda",M(Transpose(P*Q),{{19,43},{22,50}}));
    Check("M norma transponovane",Blizu(Transpose(L).Norm(),L.Norm()));
    Check("V norma i dot identitet",Blizu(Vector{2,-3,6}.Norm()*Vector{2,-3,6}.Norm(),49));

    Sekcija("ZAVRSNI IZVJESTAJ");
    std::cout << "UKUPNO: " << ukupno << "\nPROSLO: " << proslo
              << "\nPALO: " << ukupno-proslo << '\n';
    return ukupno==proslo ? 0 : 1;
}