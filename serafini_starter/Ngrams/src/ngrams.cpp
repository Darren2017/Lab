// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "Map"
#include "simpio.h"
#include "vector.h"
#include "hashmap.h".h"
#include "filelib.h"

using namespace std;

static void welcome();
static void makemap();
static void generatewords();
static Vector<string> fillmapkeys(ifstream &infile, int n);
static void accountfrowraround(Vector<string> firstwords);

HashMap<Vector<string>,Vector<string>> nmap;
Vector<string> window;

int main() {
    welcome();
    makemap();
    generatewords();

    cout << "Exiting." << endl;
    return 0;
}

static void welcome(){
cout << "Welcome to CS 106B Random Writer (N-Grams)."
     << endl << "This program makes random text based on a document."
     << endl << "Give me an input file and an 'N' value for groups of words, and I'll creat random text for you."
     << endl << endl;

}


static void makemap(){
    ifstream infile;
    promptUserForFile(infile, "Input file? ");
    int n = getInteger("Value of N? ");
    cout << endl;
    Vector<string> firstWords = fillmapkeys(infile, n);
    accountfrowraround(firstWords);
}

static void generatewords(){
    while (true) {
        int randwords = getInteger("# of random words to generate (0 to quit)? ");
        if(randwords == 0){
            return;
        }
        cout << "... ";
        window = nmap.keys()[randomInteger(0, nmap.size() - 1)];
        for(int i = 0; i < randwords; i++){
            cout << window[0] << " ";
            window.add(nmap[window][randomInteger(0, nmap[window].size() - 1)]);
            window.remove(0);
        }
        cout << "..." << endl << endl;
    }
}

static Vector<string> fillmapkeys(ifstream &infile, int n){
    string word;
    while (window.size() < n - 1) {
        infile >> word;
        window.add(word);
    }
    Vector<string> firstWords = window;
    infile >> word;
    while(!infile.fail()){
        nmap[window].add(word);
        window.remove(0);
        window.add(word);
        infile >> word;
    }
    return firstWords;
}

static void accountfrowraround(Vector<string> firstwords){
    for(int i = 0; i < firstwords.size(); i++){
        nmap[window].add(firstwords[i]);
        window.remove(0);
        window.add(firstwords[i]);
    }
}
