#include "Header.h"

using std::cout;
using std::endl;
using std::cin;

void printPairVector(vector<pair<string, string>> &);

int main() {
	vector<pair<string, string>> v;
	initializePairVector(v, "woordenlijst.txt");
	/*printPairVector(v);*/

	LeftPivotQuickSort(v);
	printPairVector(v);
	cin.get();
}

void printPairVector(vector<pair<string, string>> &v) {
	for (int i = 0; i < v.size(); i++) {
		cout << v.at(i).first << "-" << v.at(i).second << endl;
	}
}