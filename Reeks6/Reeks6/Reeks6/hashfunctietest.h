#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <iostream>
//hashindex neemt een T-sleutel en geeft een hashwaarde tussen 0 en n terug.

using std::string;
using std::getline;
using std::ifstream;
using std::list;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

template<class T,int(* hashindex)(const T&,int n)>
class Hashtabel:public vector<list<T> >{
public:
	Hashtabel(int grootteTabel) {
		this->sizeTabel = grootteTabel;
		this->resize(this->sizeTabel);
	}

	void createHash(string file)
	{
		ifstream input(file);
		string line;
		int count = 0;
		while (getline(input, line) && count < this->sizeTabel) {
			T& sleutel = line;

			int hash = hashindex(sleutel, sizeTabel);
			if (hash < sizeTabel && hash >= 0) {
				this->at(hash).push_back(sleutel);
			}
			count++;
		}
    }
	void printTabel() {
		for (int i = 0; i < sizeTabel; i++) {
			cout << "List " << i << " met size " << this->at(i).size() << ":" << endl;
			for (auto v : this->at(i)) {
				cout << v << "-";
			}
			cout << endl;
		}
	}

private: 
	int sizeTabel;

};


