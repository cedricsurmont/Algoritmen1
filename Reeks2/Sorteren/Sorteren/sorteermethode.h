#ifndef __SORTEERMETHODE
#define __SORTEERMETHODE
#include "sortvector.h"
#include "chrono.h"
#include <iostream>
#include <iomanip>
    using std::move;
    using std::swap;
    using std::endl;
    using std::cout;
    using std::setw;
#include <algorithm>   // voor sort()-methode uit STL

/** class Sorteermethode
    \brief abstracte klasse van methodes die een vector sorteren
*/
template <typename T>
class Sorteermethode{
    public:
/// \fn operator() sorteert de vector gegeven door het argument
        virtual void operator()(vector<T> & v) const = 0;

/// \fn meet(int kortste, int langste, ostream& os) schrijft naar os een overzicht (met de nodige ornamenten)
/// met de snelheid van de opgegeven sorteermethode *this. Er wordt 1 lijn uitgedrukt voor elke mogelijke
/// grootte. Deze groottes zijn kleinste, 10*kleinste, 100*kleinste,
/// enzovoorts, tot aan grootste.
/// Op een lijn staat de snelheid van de methode toegepast op
/// (1) een random tabel
/// (2) een al gesorteerde tabel.
/// (3) een omgekeerd gesorteerde tabel.

/// Deze functie werkt alleen als T een toekenning van een int toelaat,
/// zodat bv.
///    T a=5;
/// geldig is.
void meet(int kortste, int langste, ostream& os);



};

/** \class STLSort
   \brief STANDARD TEMPLATE LIBRARY SORT
*/
template <typename T>
class STLSort : public Sorteermethode<T>{
    public:
        void operator()(vector<T> & v) const;
};

template <typename T>
void STLSort<T>::operator()(vector<T> & v) const{
    sort(v.begin(),v.end());
}

/** \class InsertionSort
*/
template <typename T>
class InsertionSort : public Sorteermethode<T>{
    public:
        void operator()(vector<T> & v) const;   
};

template <typename T>
void InsertionSort<T>::operator()(vector<T> & v) const{
    for(int i=1; i<v.size(); i++){
        T h;
        h=move(v[i]);
        int j=i-1;
        while(j>=0 && h<v[j]){
            v[j+1] = move(v[j]);
            j--;
        }
        v[j+1] = move(h);
    }
}

/** \class Shellsort
*/
 
template <typename T>
class ShellSort : public Sorteermethode<T>{
    public:
        void operator()(vector<T> & v) const;
};

#endif 

template<typename T>
inline void Sorteermethode<T>::meet(int kortste, int langste, ostream & os)
{
	cout << "lengte\t\trandom\t\tgesorteerd\tomgekeerd" << endl;
	Chrono timer;
	Chrono timer2;
	Chrono timer3;
	for (int i = kortste; i < langste; i *= 10) {
		Sortvector<T> vector(i);
		vector.vul_random_zonder_dubbels();
		timer.start();
		this->operator()(vector);
		timer.stop();
		
		vector.vul_range();
		timer2.start();
		this->operator()(vector);
		timer2.stop();

		vector.vul_omgekeerd();
		timer3.start();
		this->operator()(vector);
		timer3.stop();

		os << i << "\t\t" << timer.tijd() << "\t\t" << timer2.tijd() << "\t\t" << timer3.tijd() << endl;

	}
}

template<typename T>
inline void ShellSort<T>::operator()(vector<T>& v) const
{
}
