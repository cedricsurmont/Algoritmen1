#include "sortvector.h";
#include "sorteermethode.h";
#include "chrono.h";
#include "csv.h";
#include "intstring.h";

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
	//pushen vanaf school //negeer dit
	Sortvector<Intstring> s(30);
	s.vul_random_zonder_dubbels();
	cout << "Voor sorteren: " << s << endl; 
	InsertionSort<Intstring> sorter;
	sorter(s);
	cout << "Na sorteren: " << s << endl;
	
	
	cin.get();
	return 0;
}