#pragma once
#include "backtrackflex.h";

using std::cout;
using std::endl;

class Backtrack : public Backtrackflex<int> {
public:
	Backtrack(int aantal) {
		n = aantal;
	}
/**************************************************************************
De onderstaande functies moeten ingevuld worden voor specifieke problemen.
***************************************************************************/
//controle geeft true terug als de vector deeloplossing een oplossing bevat.
	bool controle();
	//verwerk: afhandeling van een oplossing die opgeslagen is in deeloplossing.
	void verwerk();
	//geefVerdere: geef verzameling verderzettingen van de deeloplossing.
	vector<int> geefVerdere();
	int n;

//private: 
	////////////////////VECTOREN ALS ARGUMENT ENKEL FOR TESTING
	bool controleerSomVierOpeenvolgende(int i);
	bool controleerDrieOpeenvolgende(int i);
	bool controleerVerschillendVanVierde(int i);
	bool checkVoorwaardes(int i);
};


bool Backtrack::controle() {
	return deeloplossing.size() == n;
}

inline void Backtrack::verwerk()
{
	cout << "Mogelijke oplossing: " << endl;
	printDeeloplossing();
	printSom();
}

inline vector<int> Backtrack::geefVerdere()
{
	vector<int> mogelijkheden;
	for (int i = 1; i <= 9; i++) {
		if (checkVoorwaardes(i)) {
			mogelijkheden.push_back(i);
		}
	}
	return mogelijkheden;
}

inline bool Backtrack::controleerSomVierOpeenvolgende(int g)
{
	int indexVanToevoegen = deeloplossing.size();
	int sum = 0;
	if (indexVanToevoegen < 3) {
		for (int i = 0; i < deeloplossing.size(); i++) {
			sum += *(deeloplossing[i]);
		}
	}
	else {
		for (int i = indexVanToevoegen - 3; i < indexVanToevoegen; i++) {
			sum += *(deeloplossing[i]);
		}
	}
	sum += g;
	return sum < 13;
}

inline bool Backtrack::controleerDrieOpeenvolgende(int g)
{
	int indexVanToevoegen = deeloplossing.size();
	if (indexVanToevoegen == 0) {
		return true;
	}
	else if (indexVanToevoegen == 1) {
		return g != *(deeloplossing[indexVanToevoegen - 1]);
	}
	else {
		return g != *(deeloplossing[indexVanToevoegen - 1]) && g != *(deeloplossing[indexVanToevoegen - 2]);
	}
}

inline bool Backtrack::controleerVerschillendVanVierde(int g)
{
	int indexVanToevoegen = deeloplossing.size();
	if (indexVanToevoegen < 4) {
		return true;
	}
	else {
		return g != *(deeloplossing[indexVanToevoegen - 4]);
	}
}

inline bool Backtrack::checkVoorwaardes(int i)
{
	//printDeeloplossing();
	return controleerSomVierOpeenvolgende(i) && controleerDrieOpeenvolgende(i) && controleerVerschillendVanVierde(i);
}

