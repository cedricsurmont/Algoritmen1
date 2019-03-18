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
	using std::cerr;
    using std::setw;
#include <algorithm>   // voor sort()-methode uit STL

/** class Sorteermethode
    \brief abstracte klasse van methodes die een vector sorteren
*/
template <class T>
ostream& operator<<(ostream& os, const vector<T>& v) {
	for (auto e : v) {
		os << e << " ";
	}
	return os;
}
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

/** \class SelectionSort
*/
template <typename T>
class SelectionSort : public Sorteermethode<T> {
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
	void TopDownSplitMerge(vector<T> &v, int begin, int end, vector<T> &help) const;
	void TopDownMerge(vector<T> &v, int begin, int middle, int end, vector<T> &help) const;
};
/** \class MergeSort
	Topdown, recursive version with only 1 additional auxiliary vector
*/
template <typename T>
class BUMergeSort : public Sorteermethode<T> {
public:
	void operator()(vector<T> & v) const;
private:
	void BottomUpMergeSort(vector<T> &v, int begin, int end, vector<T> &help) const;
	void BottomUpMerge(vector<T> &v, int begin, int middle, int end, vector<T> &help) const;
};

/** \class HeapSort
	
*/
template <typename T>
class HeapSort : public Sorteermethode<T> {
public:
	void operator()(vector<T> & v) const;
private:
	void heapify(vector<T> &v, int root, int end)const;
};

/** \class LeftPivotQuickSort

*/
template <typename T>
class LeftPivotQuickSort : public Sorteermethode<T> {
public:
	void operator()(vector<T> & v) const;
private:
	void LeftPivotQuickSortSplit(vector<T> &v, int begin, int end) const;
};

/** \class RightPivotQuickSort

*/
template <typename T>
class RightPivotQuickSort : public Sorteermethode<T> {
public:
	void operator()(vector<T> & v) const;
private:
	void RightPivotQuickSortSplit(vector<T> &v, int begin, int end) const;
};

/** \class DualPivotQuickSort

*/
template <typename T>
class DualPivotQuickSort : public Sorteermethode<T> {
public:
	void operator()(vector<T> & v) const;
private:
	void dualPivotQuickSort(vector<T> &v, int begin, int end);
	int partition(vector<T> &v, int begin, int end, int * lp) const;
};

/** \class CountingSort

*/
template <typename T>
class CountingSort : public Sorteermethode<T> {
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
	for (int i = kortste; i <= langste; i *= 10) {
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

template <typename T>
void InsertionSort<T>::operator()(vector<T> & v) const {
	for (int i = 1; i < v.size(); i++) {
		T h = move(v.at(i));
		int j = i - 1;
		while (j >= 0 && h < v.at(j)) {
			v.at(j+1) = move(v.at(j));
			j--;
		}
		v.at(j+1) = move(h);
	}
}

template<typename T>
inline void ShellSort<T>::operator()(vector<T>& v) const
{
	cerr << "SHELLSORT" << endl;
	int sedgewick[5] = { 1, 5, 19, 41, 109 };
	for (int l = 4; l >= 0; l--) {
		int k = sedgewick[l];
		for (int i = k; i < v.size(); i++) {
			T h = move(v.at(i));
			int j = i - k;
			while (j >= 0 && h < v.at(j)) {
				v.at(j + k) = move(v.at(j));
				j -= k;
			}
			v.at(j + k) = move(h);
		}
	}
	
}



template<typename T>
inline void MergeSort<T>::operator()(vector<T>& v) const
{
	int n = v.size();
	vector<T> help((n+1)/2);

	TopDownSplitMerge(v, 0, n, help);

}


template<typename T>
inline void MergeSort<T>::TopDownSplitMerge(vector<T> &v, int begin, int end, vector<T> &help) const
{
	//de size van de overgebleven vector is 1? => niet meer splitten
	//int runsize = end - begin;
	if (end - begin < 2) {
		//cerr << "Run size: " << runsize << endl << v << endl;
		return;
	}
	//cerr << "v: " << v << endl;
	//cerr << "h: " << v << endl << endl;
	//cerr << "Run size: " << runsize << endl << v << endl;
	int middle =  begin + (end - begin) / 2;
	//recursief beide helften van V sorteren in B
	TopDownSplitMerge(v, begin, middle, help);	//links
	TopDownSplitMerge(v, middle, end, help);	//rechts
	//resultaten van b mergen in v
	TopDownMerge(v, begin, middle, end, help);

}

template<typename T>
inline void MergeSort<T>::TopDownMerge(vector<T> &v, int begin, int middle, int end, vector<T> &help) const
{
	//copy first half in to help vector, with vector initialization by using another vector's iterators
	help = { v.begin() + begin, v.begin() + middle };
	int j = begin;		//index for element in result matrix
	int ri = middle;	//to check boundaries
	middle -= begin;	//to check boundaries, middle is now the number of elements in the left half
	int li = 0;			//to check boundaries
	//zolang er elementen over zijn in de linker- en rechterhelft...
	while (li < middle && ri < end) {
		if (help.at(li) <= v.at(ri)) {
			v.at(j) = move(help.at(li));
			j++; li++;
		}
		else {
			v.at(j) = move(v.at(ri));
			j++; ri++;
		}
	}
	//Add the rest of the other half
	while (li < middle) {
		v.at(j) = help.at(li);
		j++; li++;
	}
	while (ri < end) {
		v.at(j) = v.at(ri);
		j++; ri++;
	}
}

//template<typename T>
//inline void SelectionSort<T>::operator()(vector<T>& v) const
//{
//	//searching largest element
//	for (int i = v.size() - 1; i > 0; i--) {
//		int imax = i;
//		for (int j = 0; j < i; j++) {
//			if (v.at(j) > v.at(imax)) {
//				imax = j;
//			}
//		}
//		swap(v.at(imax), v.at(i));
//	}
//}
template<typename T>
inline void SelectionSort<T>::operator()(vector<T>& v) const 
{
	//searching smallest element
	cerr << "SelectionSort selecting the smallest element" << endl;
	for (int i = 0; i < v.size(); i++) {
		int ismall = i;
		for (int j = v.size() - 1; j > i; j--) {
			if (v.at(ismall) > v.at(j))
				ismall = j;
		}
		swap(v.at(ismall), v.at(i));
	}
}

template<typename T>
inline void HeapSort<T>::operator()(vector<T>& v) const
{
	cerr << "HEAPSORT" << endl;
	for (int i = v.size()/2 -1; i>=0; i--) {
		//build a maxheap
		heapify(v, i, v.size());
	}
	for (int i = v.size() - 1; i > 0; i--) {
		//place biggest number at the back of the vector
		swap(v.at(0), v.at(i));
		//heapify the rest of the vector
		heapify(v, 0, i);
	}
}

template<typename T>
inline void HeapSort<T>::heapify(vector<T>& v, int root, int end) const
{
	int largest = root;
	int left = 2 * root + 1;
	int right = 2 * root + 2;

	if (left < end && v.at(left) > v.at(largest)) {
		largest = left;
	}
	if (right < end && v.at(right) > v.at(largest)) {
		largest = right;
	}
	if (largest != root) {
		swap(v.at(root), v.at(largest));
		heapify(v, largest, end);		//heapify the subtree that has changed
	}
}

template<typename T>
inline void LeftPivotQuickSort<T>::operator()(vector<T>& v) const
{
	LeftPivotQuickSortSplit(v, 0, v.size() - 1);
}

template<typename T>
inline void LeftPivotQuickSort<T>::LeftPivotQuickSortSplit(vector<T>& v, int begin, int end) const
{
	if (begin < end - 1) {
		T pivot = v.at(begin);		//copy
		int i = begin;
		int j = end;
		while (v.at(j) > pivot)
			j--;
		while (i < j) {
			swap(v.at(i), v.at(j));
			i++;
			while (v.at(i) < pivot)
				i++;
			j--;
			while (v.at(j) > pivot)
				j--;
		}
		LeftPivotQuickSortSplit(v, begin, j + 1);
		LeftPivotQuickSortSplit(v, j + 1, end);
	}
}

template<typename T>
inline void RightPivotQuickSort<T>::operator()(vector<T>& v) const
{
	cerr << "RightPivotQuickSort: " << endl;
	RightPivotQuickSortSplit(v, 0, v.size() - 1);
}

template<typename T>
inline void RightPivotQuickSort<T>::RightPivotQuickSortSplit(vector<T>& v, int begin, int end) const
{
	if (end - begin > 1) {
		T pivot = v.at(end);
		int i = begin;
		int j = end;
		while (v.at(i) < pivot)
			i++;
		while (i < j) {
			swap(v.at(i), v.at(j));
			j--;
			while (v.at(j) > pivot)
				j--;
			i++;
			while (v.at(i) < pivot)
				i++;
		}
		RightPivotQuickSortSplit(v, begin, i-1 );
		RightPivotQuickSortSplit(v, i-1 , end);
	}
}

template<typename T>
inline void DualPivotQuickSort<T>::operator()(vector<T>& v) const
{
	dualPivotQuickSort(v, 0, v.size() - 1);
}

template<typename T>
inline void DualPivotQuickSort<T>::dualPivotQuickSort(vector<T>& v, int begin, int end)
{
	if (begin < end) {
		int lp, rp;			//left and right pivot
		rp = partition(v, begin, end, &lp);
		dualPivotQuickSort(v, begin, lp - 1);
		dualPivotQuickSort(v, lp + 1, rp - 1);
		dualPivotQuickSort(v, rp + 1, end);
	}
	
}

template<typename T>
inline int DualPivotQuickSort<T>::partition(vector<T>& v, int begin, int end, int * lp) const
{
	if (v.at(begin) > v.at(end))		//in case left pivot would be smaller than right pivot
		swap(v.at(begin), v.at(end));
	int k = begin + 1;
	int g = end - 1;
	int m = begin + 1;
	T leftPivot = v.at(begin);	
	T rightPivot = v.at(end);		
	while (m <= g) {
		//Check the m element and place it in the correct subarray
		if (v.at(m) < leftPivot) {		
			swap(v.at(m), v.at(k));
			k++;
		}
		else if (v.at(m) >= rightPivot) {	//maybe > inst of >=
			while (v.at(g) > rightPivot && m < g)
				g--;
			swap(v.at(m), v.at(g));
			g--;
			if (v.at(m) < leftPivot) {
				swap(v.at(m), v.at(k));
				k++;
			}
		}
		m++;	//next element
	}
	//to set pivots to correct positions
	k--;
	g++;
	swap(v.at(begin), v.at(k));	//v[begin] is leftpivot
	swap(v.at(end), v.at(g));   //v[end] is rightpivot

	//return values
	*lp = k;
	return g;
}

template<typename T>
inline void CountingSort<T>::operator()(vector<T>& v) const
{
	int RANGE = 20;	//hardcoded, bad practice
	vector<T> output(v.size()-1);
	vector<int> count(RANGE);
	//frequency table
	for (int i = 0; i < v.size()-1; i++) {
		count[v.at(i)]++;
	}
	//Modify frequency table
	for (int i = 1; i < RANGE; i++)
		count[i] += count[i - 1];
	//Arrange output vector
	for (int i = 0; i < v.size(); i++) {
		output[count[v.at(i)]-1] = v.at(i);
		count[v.at(i)]--;
	}
	v = output;
}

template<typename T>
inline void BUMergeSort<T>::operator()(vector<T>& v) const
{
	vector<T> help((v.size() + 1) / 2);
	BottomUpMergeSort(v, 0, v.size() - 1, help);
}

template<typename T>
inline void BUMergeSort<T>::BottomUpMergeSort(vector<T>& v, int begin, int end, vector<T>& help) const
{
	cerr << "Bottom Up Mergesort: " << endl;
	for (int width = 1; width < v.size(); width *= 2) {
		for (int i = 0; i < v.size(); i += 2 * width) {	//Iterates every two subarrays
			BottomUpMerge(v, i, std::min(i + width, (int)v.size()), std::min((i + 2 * width), (int)v.size()), help);
		}
	}
}

template<typename T>
inline void BUMergeSort<T>::BottomUpMerge(vector<T>& v, int begin, int middle, int end, vector<T>& help) const
{
	//copy first half in to help vector, with vector initialization by using another vector's iterators
	help = { v.begin() + begin, v.begin() + middle };
	int j = begin;		//index for element in result matrix
	int ri = middle;	//to check boundaries
	middle -= begin;	//to check boundaries, middle is now the number of elements in the left half
	int li = 0;			//to check boundaries
	//zolang er elementen over zijn in de linker- en rechterhelft...
	while (li < middle && ri < end) {
		if (help.at(li) <= v.at(ri)) {
			v.at(j) = move(help.at(li));
			j++; li++;
		}
		else {
			v.at(j) = move(v.at(ri));
			j++; ri++;
		}
	}
	//Add the rest of the other half
	while (li < middle) {
		v.at(j) = help.at(li);
		j++; li++;
	}
	while (ri < end) {
		v.at(j) = v.at(ri);
		j++; ri++;
	}
}

template <class T>
int binary_search(const T &s, const vector<T> &v) {
	int l = 0, r = v.size();
	while (l < r - 1) {
		int m = l + (r - l) / 2;
		if (s < v.at(m))
			r = m;
		else
			l = m;
	}
	return v.at(l) == s ? l : -1;
}

template <class T>
int one_sided_binary_search(const T &s, const vector<T> &v) {
	//can't use the size!
	if (v.at(0) != s) {
		int i = 1;
		while (v.at(i) < s) {
			i *= 2;
			cout << "Index : " << i << endl;
		}
		//binary search between index i and i/2
		vector<T> help = { v.begin() + i / 2, v.begin() + i };	//Make better binary_search function with begin & end index instead!
		return i / 2 + binary_search(s, help);
			
	}
	else {
		return 0;
	}

}
