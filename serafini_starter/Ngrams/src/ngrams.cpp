#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "hashmap.h"
#include "simpio.h"
#include "vector.h"
#include "filelib.h"

using namespace std;

static void welcome();
static void makemap();
static string getfilename();
static Vector<string> fillmapkeys(ifstream &infile, int n);
static void makecriculation(Vector<string> firstWords);
static void PrintText();

HashMap<Vector<string>, Vector<string>> mymap;
Vector<string> window;

int main()
{
    welcome();
    makemap();
    PrintText();

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
    string infilename = getfilename();
    infile.open(infilename);
    int n = getInteger("Value of N? ");
    cout << endl;
    Vector<string> firstWords = fillmapkeys(infile, n);

}

static string getfilename(){
    int s;
    string name;
    do{
        s = 1;
        cout << "Input file? ";
        getline(cin, name);
        fstream _file;
        _file.open(name, ios :: in);
        if(!_file){
            cout << "Unable to open that file.  Try again." << endl;
            s = 0;
        }
    }while(s == 0);

    return name;
}

static Vector<string> fillmapkeys(ifstream &infile, int n){
    string word;
    while (window.size() < n -1){
        infile >> word;
        window.add(word);
    }
    Vector<string> firstWords = window;
    infile >> word;
    while(!infile.fail()){
        mymap[window].add(word);
        window.remove(0);
        window.add(word);
        infile >> word;
    }
    return firstWords;
}

static void makecirculation(Vector<string> firstWords){
    for(int i =  0; i < firstWords.size(); i++){
        mymap[window].add(firstWords[i]);
        window.remove(0);
        window.add(firstWords[i]);
    }
}

static void PrintText(){
    while (true) {
        int randword = getInteger("# of random words to generate (0 to quit)? ");
        if(randword == 0){
            return;
        }
        cout << "... ";
        window = mymap.keys()[randomInteger(0, mymap.size() - 1)];
        for(int i = 0; i < randword; i++){
            cout << window[0] << " ";
            window.add(mymap[window][randomInteger(0, mymap[window].size() - 1)]);
            window.remove(0);
        }
        cout << "..." << endl << endl;
    }
}
