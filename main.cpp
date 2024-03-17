#include <iostream>
#include <cmath>
#include <cassert>
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

template <typename tmp, typename = typename enable_if<is_arithmetic<tmp>::value>::type>
Vector<tmp> CinElements(Vector<tmp> myvector){
    cout<<"Input elements: "<<endl;
    for(int i = 0; i < myvector.GetD(); ++i){
        double value;
        cout<<"V["<<i+1<<"] = "; cin>>value;
        myvector.SetElement(i, value);
    }
    return myvector;
}

template <typename tmp, typename = typename enable_if<is_arithmetic<tmp>::value>::type>
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
    try{
        if(addend1.GetD() != addend2.GetD()){
            throw(invalid_argument("Different dimensions!"));
        }
        Vector<tmp> sum(addend1.GetD());
        for(int i = 0; i < addend1.GetD(); ++i){
            sum.GetV()[i] = addend1.GetV()[i] + addend2.GetV()[i];
        }
        return sum;
    }

    catch(invalid_argument& myexception){
        cout<<myexception.what();
        throw;
    }
}

template <typename tmp, typename = typename enable_if<is_arithmetic<tmp>::value>::type>
Vector<tmp> Sub(Vector<tmp> saklebi, Vector<tmp> maklebi){
    try{
        if(saklebi.GetD() != maklebi.GetD()){
            throw(invalid_argument("Different dimensions!"));
        }
        Vector<tmp> sub(saklebi.GetD());
        for(int i = 0; i < saklebi.GetD(); ++i){
            sub.GetV()[i] = saklebi.GetV()[i] - maklebi.GetV()[i];
        }
        return sub;
    }

    catch(invalid_argument& myexception){
        cout<<myexception.what();
        throw;
    }
}

template <typename tmp, typename = typename enable_if<is_arithmetic<tmp>::value>::type>
tmp ScalarProduct(Vector<tmp> v1, Vector<tmp> v2){
    try{
        if(v1.GetD() != v2.GetD()){
            throw(invalid_argument("Different dimensions!"));
        }
        tmp scalarproduct = 0;
        for(int i = 0; i < v1.GetD(); ++i){
            scalarproduct += v1.GetV()[i] * v1.GetV()[i];
        }
        return scalarproduct;
    }
    catch(invalid_argument& myexception){
        cout<<myexception.what();
        throw;
    }
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
unsigned int BiggestElement(Vector<tmp> myvector){
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

template <typename tmp, typename = typename enable_if<is_arithmetic<tmp>::value>::type>
ostream& operator<<(ostream& os, Vector<tmp> myvector){
    for(unsigned int i = 0; i < myvector.GetD(); ++i){
        os<<myvector.GetV()[i]<<endl;
    }
    return os;
}

int main(int argc, char* argv[]){

    Vector<double> vector1 = CinDimension<double>();
    Vector<double> vector2 = CinDimension<double>();

    CinElements(vector1);
    CinElements(vector2);

    cout<<Sum(vector1, vector2);
    cout<<Sub(vector1, vector2);

    return 0;
}
