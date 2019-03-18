#include "sortvector.h";
#include "sorteermethode.h";
#include "chrono.h";
#include "csv.h";
#include "intstring.h";

using std::cout;

using std::endl;
using std::cin;
using std::string;

template <class T>
void testAlgorithm(Sorteermethode<T> &s, int size) {
//	cout << s.getClass() << endl;
	Sortvector<int> v(size);
	v.vul_random_zonder_dubbels();
	cout << "Vector voor sorteren: " << v << endl;
	s(v);
	if (v.is_gesorteerd()) {
		cout << "Vector na sorteren: " << v << endl;
	}
	else {
		cout << "Sorteren is mislukt :( ..." << endl << v << endl;
	}
	
}

void testVector(int size) {
	Sortvector<int> s(size);
	cout << "Initiële vector:" << endl << s << endl << endl;
	if (s.is_gesorteerd()) {
		cout << "Bovenstaande vector is range!" << endl;
	}
	else {
		cout << "Bovenstaande vector is NIET range!" << endl;
	}
	s.vul_range();
	cout << "Na vul_range:" << endl << s << endl << endl;
	if (s.is_gesorteerd()) {
		cout << "Bovenstaande vector is range!" << endl;
	}
	else {
		cout << "Bovenstaande vector is NIET range!" << endl;
	}
	s.vul_omgekeerd();
	cout << "Na vul_omgekeerd:" << endl << s << endl << endl;
	if (s.is_gesorteerd()) {
		cout << "Bovenstaande vector is gesorteerd!" << endl;
	}
	else {
		cout << "Bovenstaande vector is NIET gesorteerd!" << endl;
	}
	s.draai_om();
	cout << "Na draai_om:" << endl << s << endl << endl;
	if (s.is_gesorteerd()) {
		cout << "Bovenstaande vector is gesorteerd!" << endl;
	}
	else {
		cout << "Bovenstaande vector is NIET gesorteerd!" << endl;
	}
	s.vul_random_zonder_dubbels();
	cout << "Na vul_random_zonder_dubbels:" << endl << s << endl << endl;
	
}

int main(int argc, char** argv) {
	//pushen vanaf school //negeer dit
	//Sortvector<int> s(2000);
	//s.vul_random_zonder_dubbels();
	//cout << "Voor sorteren: " << s << endl; 
	//LeftPivotQuickSort<int> sorter;
	//sorter(s);
	//cout << "Na sorteren: " << s << endl;
	//sorter.meet(10, 100000, std::cout);
	//vector<string> s2 = { "een", "twee", "drie", "vier", "vijf", "zes", "zeven", "acht", "negen", "aaa", "aba", "abb", "abba" };
	//LSDRadixSort sorter;
	////testAlgorithm(sorter, 19);
	//sorter(s2);
	//int found = one_sided_binary_search(590, s);
	//cout << "Index of 590 with one_sided_binary_search: " << found << endl;
	//for (int i = 0; i < s2.size(); i++) {
	//	cout << s2.at(i) << "-";
	//}
	vector<double> s3 = { 0.23, 0.22, 0.35, 0.44, 0.55, 0.56, 0.98, 0.87 };
	BucketSort sorter2;
	for (int i = 0; i < s3.size(); i++) {
		cout << s3.at(i) << "-";
	}
	sorter2(s3);
	cout << "Na BucketSort: " << endl;
	for (int i = 0; i < s3.size(); i++) {
		cout << s3.at(i) << "-";
	}
	cin.get();
	return 0;
}