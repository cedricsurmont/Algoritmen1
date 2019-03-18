#include "sorteermethode_deel2_quick.h"
#include <queue>

class TernaireRadixQsort : Sorteermethode<std::string> {
public:
	void operator()(vector<std::string> & v) const {
		quicksortXX(v, 0, v.size() - 1, 0);
	}
private:

	const char get_key(std::string s, int pos) const {
		if (pos > s.length()) return ' ';
		return s[pos];
	}
	void partition(vector<std::string> & v, int start, int einde, int index, int * lo, int * hi) const{
		
	}

	void ternaire_radix_qsort(vector<std::string> & v, int start, int einde, int index) const {
		
	}

	void quicksortXX(vector<std::string> &a, int lo, int hi, int d) const { 
		/*
		deze implementatie houdt geen rekening met gelijke sleutels
		vb { "aa","aa", "ba" } geeft error
		*/
		if (hi <= lo) return;
		int lt = lo, gt = hi;
		int v = a[lo][d];  //char at pos d in string a[lo]=> to asci int
		int i = lo + 1;
		while (i <= gt) {
			int t = a[i][d];
			if (t < v) swap(a[lt++], a[i++]);
			else if (t > v) {
				while (a[gt][d] > v && gt > i) gt--;
				if(gt> i) swap(a[gt--], a[i++]);
			}
			else i++;
		}
		quicksortXX(a, lo, lt - 1, d);
		quicksortXX(a, lt, gt, d + 1);
		quicksortXX(a, gt + 1, hi, d);
	}



};

class KeyIndexedCountSort : Sorteermethode<std::string> {
public: 
	
	void operator()(vector<std::string> & v) const {
		key_indexed_counting(v,0);
	}

private:
	char get_key(std::string s, int pos) const {
		if (pos > s.length()) return ' ';
		return s[pos];
	}

	void key_indexed_counting(vector<std::string> &v, int key_index) const{
		int n = v.size();
		int R = 256;
		vector<int> count(R + 1, 0);
		//freq tabel invullen
		//freq tabel cumulatief maken (specify destination)
		//overloop origineel, copieer naar aux
		//kopieer naar v;
		vector<std::string> aux(v.size());
		for (int i = 0; i < v.size(); i++)
		{
			count[get_key(v[i],key_index) + 1]++;
		}
		for (int r = 0; r < R; r++)
		{
			count[r + 1] += count[r];
		}
		for (int i = 0; i < v.size(); i++)
		{
			int dest = count[get_key(v[i], key_index)]++;
			aux[dest] = v[i];
		}
		for (int i = 0; i < v.size(); i++)
		{
			v[i] = aux[i];
		}
	}
};

class MSDRadixSort : Sorteermethode<std::string> {
public:
	void operator()(vector<std::string> & v) const {
		key_indexed_counting(v, 0,0,v.size()-1);
	}
private:
	char get_key(std::string s, int pos) const {
		if (pos > s.length()) return ' ';
		return s[pos];
	}


	void key_indexed_counting(vector<std::string> &v, int key_index,int start, int einde) const {
		
		if (start >= einde) return;
		int R = 256;
		vector<int> count(R + 1, 0);
		//freq tabel invullen
		//freq tabel cumulatief maken (specify destination)
		//overloop origineel, copieer naar aux
		//kopieer naar v;
		vector<std::string> aux(einde -start+1);
		for (int i = start; i <= einde; i++)
		{
			count[get_key(v[i], key_index) + 1]++;
		}
		for (int r = 0; r < R; r++)
		{
			count[r + 1] += count[r];
		}
		for (int i = start; i <= einde; i++)
		{
			int dest = count[get_key(v[i], key_index)]++;
			aux[dest] = v[i];
		}
		for (int i = 0; i < einde - start +1; i++)
		{
			v[start+ i] = aux[i];
		}

		for (int i = 0; i < R; i++)
		{
			key_indexed_counting(v, key_index + 1, start + count[i], start + count[i + 1] - 1);
		}
	}
	
	
};

//OPMERKING: we werken enkel met strings met vaste lengte W
class LSDRadixSort : Sorteermethode<std::string> {
public:

	void operator()(vector<std::string> & v) const {
		lsd_radix_sort(v, v[0].length());
	}

private:
	void lsd_radix_sort(vector<std::string> & v, int W) const {
		int R = 256;
		vector<int>count(R + 1, 0);
		vector<std::string>  aux;
		for (int d = W - 1; d >= 0; d--)
		{
			//tel freq
			for (int i = 0; i < v.size(); i++)
			{
				count[v[i][d]]++;
			}
			for (int r = 0; r < R; r++)
			{
				count[r + 1] = count[r];
			}
			for (int i = 0; i < v.size(); i++)
			{
				int dest = count[v[i][d]]++;
				aux[dest] = v[i];
			}
			for (int i = 0; i < v.size(); i++)
			{
				v[i] = aux[i];
			}
			//maak cumulatief, bevat doeladress
			//kopieer naar aux
			// kopieer naar origineel

		}
	}
};