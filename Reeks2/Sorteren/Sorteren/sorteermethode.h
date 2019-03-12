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


/** \class InsertionSort
*/
template <typename T>
class InsertionSort : public Sorteermethode<T>{
    public:
        void operator()(vector<T> & v) const;   
};

/** \class Shellsort
*/
 
template <typename T>
class ShellSort : public Sorteermethode<T>{
    public:
        void operator()(vector<T> & v) const;
};

/** \class MergeSort
	Topdown, recursive version with only 1 additional auxiliary vector
*/

template <typename T>
class MergeSort : public Sorteermethode<T> {
public:
	void operator()(vector<T> & v) const;
private:
	void TopDownSplitMerge(vector<T> &b, int begin, int end, vector<T> &v) const;
	void TopDownMerge(vector<T> &v, int begin, int middle, int end, vector<T> &b) const;
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

template <typename T>
void STLSort<T>::operator()(vector<T> & v) const {
	sort(v.begin(), v.end());
}

template<typename T>
inline void ShellSort<T>::operator()(vector<T>& v) const
{
	int sedgewick[5] = { 1, 5, 19, 41, 109 };
	for (int j = 4; j >= 0; j--) {
		int k = sedgewick[j];
		for (int i = k; i < v.size(); i++) {
			T h = move(v.at(i));
			int l = i - k;
			while (l >= 0 && h < v.at(l)) {
				v.at(l + k) = move(v.at(l));
				l -= k;
			}
			v.at(l + k) = move(h);
		}
	}
	
}

template <typename T>
void InsertionSort<T>::operator()(vector<T> & v) const {
	for (int i = 1; i < v.size(); i++) {
		T h;
		h = move(v[i]);
		int j = i - 1;
		while (j >= 0 && h < v[j]) {
			v[j + 1] = move(v[j]);
			j--;
		}
		v[j + 1] = move(h);
	}
}

template<typename T>
inline void MergeSort<T>::operator()(vector<T>& v) const
{
	int n = v.size();
	vector<T> help(n);
	//duplicate v in b;
	//efficient???
	for (int i = 0; i < n; i++) {
		help.at(i) = v.at(i);
	}
	TopDownSplitMerge(help, 0, n, v);

}


template<typename T>
inline void MergeSort<T>::TopDownSplitMerge(vector<T> &help, int begin, int end, vector<T> &v) const
{
	//de size van de overgbleven vector is 1? => niet meer splitten
	if (end - begin < 2)
		return;
	int middle = (end + begin) / 2;
	//recursief beide helften van V sorteren in B
	TopDownSplitMerge(v, begin, middle, help);	//links
	TopDownSplitMerge(v, middle, end, help);	//rechts
	//resultaten van b mergen in v
	TopDownMerge(help, begin, middle, end, v);

}

template<typename T>
inline void MergeSort<T>::TopDownMerge(vector<T> &v, int begin, int middle, int end, vector<T> &help) const
{
	int i = begin;
	int j = middle;
	//zolang er elementen over zijn in de linker- of rechterhelften...
	for (int k = begin; k < end; k++) {
		//?
		if (i < middle && (j >= end || v.at(i) <= v.at(j))) {
			help.at(k) = v.at(i);	//efficient???
			i++;
		}
		else {
			help.at(k) = v.at(j);	//efficient???
			j++;
		}
	}
}
