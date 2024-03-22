#include <iostream>
#include <cmath>
#include <cassert>
#include <type_traits>

using namespace std;

template <typename tmp>
class Vector{
    private:
        unsigned int Dimension;
        tmp* myvector;

    public:
        // CONSTRUCTOR:

        Vector(unsigned int Dimension = 1){
            SetD(Dimension);
            myvector = new tmp[Dimension];
        }

        // SETTERS:

        void SetD(unsigned int Dimension = 1){
            assert(Dimension != 0);
            this->Dimension = Dimension;
        }

        void SetElement(unsigned int i, tmp value){
            myvector[i] = value;
        }

        // GETTERS:

        unsigned int GetD(){return Dimension;}
        tmp* GetV(){return myvector;}
};

// VECTOR FUNCTIONS:

template <typename tmp>
Vector<tmp> CinDimension(){
    unsigned int i = 0;
    cout<<"Input dimension of your vector: "; cin>>i;
    return Vector<tmp>(i);
}

template <typename tmp>
Vector<tmp> CinElements(Vector<tmp> myvector){
    cout<<"Input elements: "<<endl;
    for(int i = 0; i < myvector.GetD(); ++i){
        tmp value;
        cout<<"V["<<i+1<<"] = "; cin>>value;
        myvector.SetElement(i, value);
    }
    return myvector;
}

template <typename tmp>
void CoutElements(Vector<tmp> myvector){
    cout<<"["<<myvector.GetD()<<"] = { ";
    for(int i = 0; i < myvector.GetD(); ++i){
        cout<<myvector.GetV()[i]<<"; ";
    }
    cout<<"}"<<endl;
}

// VECTOR ALGEBRA:

template <typename tmp, typename = typename enable_if<is_arithmetic<tmp>::value>::type>
Vector<tmp> Sum(Vector<tmp> addend1, Vector<tmp> addend2){
    if(addend1.GetD() != addend2.GetD()){
        throw(invalid_argument("Different dimensions!"));
    }
    Vector<tmp> sum(addend1.GetD());
    for(int i = 0; i < addend1.GetD(); ++i){
        sum.GetV()[i] = addend1.GetV()[i] + addend2.GetV()[i];
    }
    return sum;
}

template <typename tmp, typename = typename enable_if<is_arithmetic<tmp>::value>::type>
Vector<tmp> Sub(Vector<tmp> saklebi, Vector<tmp> maklebi){
    if(saklebi.GetD() != maklebi.GetD()){
        throw(invalid_argument("Different dimensions!"));
    }
    Vector<tmp> sub(saklebi.GetD());
    for(int i = 0; i < saklebi.GetD(); ++i){
        sub.GetV()[i] = saklebi.GetV()[i] - maklebi.GetV()[i];
    }
    return sub;
}

template <typename tmp, typename = typename enable_if<is_arithmetic<tmp>::value>::type>
tmp ScalarProduct(Vector<tmp> v1, Vector<tmp> v2){
    if(v1.GetD() != v2.GetD()){
        throw(invalid_argument("Different dimensions!"));
    }
    tmp scalarproduct = 0;
    for(int i = 0; i < v1.GetD(); ++i){
        scalarproduct += v1.GetV()[i] * v1.GetV()[i];
    }
    return scalarproduct;
}

template <typename tmp, typename = typename enable_if<is_arithmetic<tmp>::value>::type>
tmp DecLength(Vector<tmp> myvector){
    tmp declength = 0;
    for(int i = 0; i < myvector.GetD(); ++i){
        declength += myvector.GetV()[i] * myvector.GetV()[i];
    }
    return sqrt(declength);
}

// BIGGEST AND SMALLEST:

template <typename tmp, typename = typename enable_if<is_arithmetic<tmp>::value>::type>
unsigned BiggestElement(Vector<tmp> myvector){
    unsigned int I = 0;
    for(int i = 1; i < myvector.GetD(); ++i){
        if(myvector.GetV()[I] < myvector.GetV()[i]){
            I = i;
        }
    }
    return I;
}

template <typename tmp, typename = typename enable_if<is_arithmetic<tmp>::value>::type>
unsigned int SmallestElement(Vector<tmp> myvector){
    unsigned int I = 0;
    for(int i = 1; i < myvector.GetD(); ++i){
        if(myvector.GetV()[I] > myvector.GetV()[i]){
            I = i;
        }
    }
    return I;
}

// OPERATORS OVERLOADING:

template <typename tmp>
ostream& operator<<(ostream& os, Vector<tmp> myvector){
    for(unsigned int i = 0; i < myvector.GetD(); ++i){
        os<<myvector.GetV()[i]<<endl;
    }
    return os;
}

int main(int argc, char* argv[]){
    Vector vector1 = CinDimension<char>();
    Vector vector2 = CinDimension<char>();

    CinElements(vector1);
    CinElements(vector2);

    try{
        cout<<Sum<char>(vector1, vector2);
    }
    catch(exception& myexception){
        cout<<"Error: "<<myexception.what();
    }

    return 0;
}
