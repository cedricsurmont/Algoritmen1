#include "sortvector.h";
#include "sorteermethode.h";
#include "chrono.h";
#include "csv.h";


using std::cout;

using std::endl;
using std::cin;
using std::string;



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
	Sortvector<int> s(30);
	s.vul_random_zonder_dubbels();
	cout << "Beginvector: " << s << endl;
	STLSort<int> sorter;
	sorter(s);
	cout << "Na STLSort: " << s << endl;
	InsertionSort<int> sorter2;
	s.vul_random_zonder_dubbels();
	sorter2(s);
	cout << "Na InsertionSort: " << s << endl;

	cout << "STLSort" << endl;
	sorter.meet(10, 1000000, std::cout);
	cout << "InsertionSort" << endl;
	sorter2.meet(10, 1000000, std::cout);
	cin.get();
	return 0;
}