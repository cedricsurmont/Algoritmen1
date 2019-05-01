#ifndef __BACKTRACKFLEX_H
#define __BACKTRACKFLEX_H
#include <iostream>
#include <fstream>
#include <stdio.h>
using std::ostream;
using std::cerr;
using std::cout;
using std::endl;
#include <vector>
using std::vector;
//De klasse Backtrackflex zoekt een vector van knopen die een oplossing biedt voor een gegeven
//probleem. Wat er met deze oplossing moet gedaan worden staat in de functie verwerk.
//Backtrackflex kan ingesteld worden zodat hij juist 1 oplossing zoekt, of zodat
//hij alle oplossingen zoekt.
//
//Backtrackflex is flexibel omdat het toevoegen/wegnemen van elementen
//aan/van deeloplossing kan overschreven worden.

template <class knoop>
class Backtrackflex{
public:

    //als opgeroepen met zoekalle=true worden alle oplossingen gezocht
    void losOp(bool zoekalle);                                                                 
protected:
    void losOp(bool& gedaan,bool zoekalle);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         

    //de volgende functies moeten misschien aangepast voor specifieke problemen.
    virtual void voegToeAanDeeloplossing(const knoop& element);
    virtual void verwijderUitDeeloplossing();                                              
    
/**********************************************************************

De onderstaande functies moeten ingevuld worden voor specifieke problemen.

   
***************************************************************************/
//controle geeft true terug als de vector deeloplossing een oplossing bevat.
    virtual bool controle()=0;
//verwerk: afhandeling van een oplossing die opgeslagen is in deeloplossing.
    virtual void verwerk()=0;
//geefVerdere: geef verzameling verderzettingen van de deeloplossing.
    virtual vector<knoop> geefVerdere()=0;
//Opgelet: deeloplossing is een vector van *pointers* naar knopen; de knopen zelf zitten
// in de vector mogelijkheid die lokaal gedeclareerd wordt in losOp
    vector<const knoop*> deeloplossing;

	void printDeeloplossing();
	void printSom();
};



template <class knoop>
void Backtrackflex<knoop>::losOp(bool zoekalle){
    deeloplossing.clear();
    bool gedaan=false;
    losOp(gedaan,zoekalle);
}

template <class knoop>
void Backtrackflex<knoop>::losOp(bool& gedaan,bool zoekalle){
    if (controle()){//oplossing gevonden
        verwerk();
        if (!zoekalle)
            gedaan=true;
    }
//bij sommige problemen kan een oplossing nog verlengd worden tot een langere oplossing
//daarom moet het volgend stuk code ook worden uitgevoerd als we een oplossing hebben.
   if (!gedaan){
//noot: het werken met referenties naar elementen van een vector is alleen veilig als de
//vector onveranderlijk is.
        const vector<knoop> mogelijkheid(geefVerdere());
        int i=0;
        while (i<mogelijkheid.size() && !gedaan){
            voegToeAanDeeloplossing(mogelijkheid[i]);
			//printDeeloplossing();
            losOp(gedaan,zoekalle);
            verwijderUitDeeloplossing();
            i++;
        }
    }
}

template <class knoop>
void Backtrackflex<knoop>::voegToeAanDeeloplossing(const knoop& element){
    deeloplossing.push_back(&element);
}

template <class knoop>
void Backtrackflex<knoop>::verwijderUitDeeloplossing(){
	cout << endl << "Voor verwijdering: " << endl;
	printDeeloplossing();
    deeloplossing.resize(deeloplossing.size()-1);
	cout << "Na verwijdering: " << endl;
	printDeeloplossing();
}

template<class knoop>
inline void Backtrackflex<knoop>::printDeeloplossing()
{
	cout << "DeelOplossing: ";
	for (int i = 0; i < deeloplossing.size(); i++) {
		cout << *(deeloplossing.at(i)) << " ";
	}
	cout << endl;
}

template<class knoop>
inline void Backtrackflex<knoop>::printSom()
{
	int som = 0;
	for (int i = 0; i < deeloplossing.size(); i++) {
		som += *(deeloplossing.at(i));
	}
	cout << "Som van oplossing met grootte " << deeloplossing.size() << ": " << som << endl;
}


#endif
