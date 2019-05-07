#include "hashfunctietest.h"
#include <iostream>
using std::cin;

int slechtehash(const string& s, int n) {
	return s.size() % n;
};

int hornerhash(const string& woord, int n) {
	unsigned int horner = 0;
	for (int i = 0; i < woord.size(); i++)
		horner = (horner * 256 + woord[i]);
	return horner % n;
};

int main() {
	Hashtabel<string, hornerhash> tabel(574427);
	tabel.createHash("woordenlijst.txt");
	tabel.printTabel();
	cin.get();
}