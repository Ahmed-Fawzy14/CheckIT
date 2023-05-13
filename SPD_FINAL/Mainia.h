#ifndef MAINIA_H
#define MAINIA_H
#include <string>
#include <vector>
#include<unordered_map>
#include<unordered_set>
#include <list>


using namespace std;

#pragma once

//Function that include all program function calls
//Called by main function to execute program
void runProgram();


float jaccardSimilarity(const unordered_set<string>& set1, const unordered_set<string>& set2);
vector<string> generateNGrams(const string& str, int n);
void similarityPercent(string main, string c1, string c2, string c3);
list<pair<string, string>> printPoly(unordered_map<string, string> foundPolySentences, unordered_map<string, string> foundPoly4Phrases, unordered_map<string, string> foundPoly3Phrases, unordered_map<string, string> foundPoly2Phrases, int document);


#endif // MAINIA_H
