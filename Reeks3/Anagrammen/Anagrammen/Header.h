#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <utility>
#include <fstream>
#include <string>

using std::string;
using std::pair;
using std::vector;
using std::ifstream;

void LeftPivotQuickSortSplit(vector<pair<string, string>> &, int , int );
void LeftPivotQuickSort(vector<pair<string, string>> &);

void initializePairVector(vector<pair<string, string>> &v, string file) {
	ifstream input(file);
	if (input.is_open()) {
		string word;
		int testindex = 0;
		while (getline(input, word) && testindex <= 50) {
			string original = word;
			std::sort(word.begin(), word.end());
			pair<string, string> myPair = std::make_pair(original, word);
			v.push_back(myPair);

			testindex++;
		}
	}
	/*pair<string, string> p = std::make_pair("laa", "aal");
	v.push_back(p);*/
}

void LeftPivotQuickSort(vector<pair<string, string>> &v)
{
	LeftPivotQuickSortSplit(v, 0, v.size());
}

void LeftPivotQuickSortSplit(vector<pair<string, string>> &v, int begin, int end) 
{
	if (begin < end - 1) {
		int pivotsize = v.at(begin).second.size();		
		int i = begin;
		int j = end-1;
		while (v.at(j).second.size() > pivotsize)
			j--;
		while (i < j) {
			swap(v.at(i), v.at(j));
			i++;
			while (v.at(i).second.size() < pivotsize)
				i++;
			j--;
			while (v.at(j).second.size() > pivotsize)
				j--;
		}
		LeftPivotQuickSortSplit(v, begin, j + 1);
		LeftPivotQuickSortSplit(v, j + 1, end);
	}
}