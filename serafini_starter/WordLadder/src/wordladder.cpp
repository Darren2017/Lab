#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <ctype.h>
#include "console.h"
#include "lexicon.h"
#include "vector.h"
#include "queue.h"

using namespace std;

static void welcome();
static string getfilename();
static bool getword(const Lexicon& dictionary, string& word, string prompt);
static bool checkword(const Lexicon& dictionary, string& word1, string& word2);
static Vector<string> getwordladder(const Lexicon& dictionary, const string& word1, const string& word2);
static Lexicon onehoaway(const Lexicon& dictionary, Lexicon& new_words, const string& firword);
static void printwordladder(const Vector<string>& wordladder, const string& word1, const string& word2);

int main(){
    welcome();
    string file = getfilename();
    Lexicon dictionary(file);

    while (true) {
        string word1;
        string word2;
        Vector<string> wordladder;

        if(getword(dictionary, word1, "Word #1 (or Enter to quit):"))   break;
        if(getword(dictionary, word2, "Word #1 (or Enter to quit):"))   break;
        if(checkword(dictionary, word1, word2))     break;

        wordladder = getwordladder(dictionary, word1, word2);
        printwordladder(wordladder, word1, word2);

    }

    cout << "Have a nice day." << endl;

    return 0;
}

static void welcome(){
    cout << "Welcome to CS 106B Word Ladder." << endl;
    cout << "Please give me two English words, and I will change the" << endl << "first into the second by changing one letter at a time." << endl;

}

static string getfilename(){
    int s;
    string name;
    do{
        s = 1;
        cout << "Dictionary file name?";
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

static bool getword(const Lexicon& dictionary, string& word, string prompt){
    while (true) {
        cout << prompt;
        getline(cin, word);
        if(word.empty()){
            return true;
        }else if(dictionary.contains(word)){
            return false;
        }
        cout << "The two words must be found in the dictionary." << endl;
    }
}

static bool checkword(const Lexicon& dictionary, string& word1, string& word2){
    if(word1.length() != word2.length()){
        cout << "The two words must be the same length.";
        return getword(dictionary, word1, word2);
    }
    return false;
}

static Vector<string> getwordladder(const Lexicon& dictionary, const string& word1, const string& word2){
    Queue< Vector<string> > qu;
    Vector<string> wordladder;
    Lexicon new_words;

    wordladder.add(word1);
    new_words.add(word1);
    qu.enqueue(wordladder);
    while (!qu.isEmpty()) {
        wordladder = qu.dequeue();
        string firword = wordladder[wordladder.size() - 1];
        if(firword == word2){
            break;
        }else{
            for(string word: onehoaway(dictionary, new_words, firword)){
                Vector<string> wordladderclone = wordladder;
                wordladderclone.add(word);
                qu.enqueue(wordladderclone);
            }
        }
    }
    return wordladder;

}

static Lexicon onehoaway(const Lexicon& dictionary, Lexicon& new_words, const string& firword){
    Lexicon onehoaway;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for(int i = 0; i < firword.length(); i++){
        for(int j = 0; j < alphabet.length(); j++){
            string testword = firword;
            testword[i] = alphabet[j];
            if(dictionary.contains(testword) && !new_words.contains(testword)){
                onehoaway.add(testword);
                new_words.add(testword);
            }
        }
    }
    return onehoaway;
}

static void printwordladder(const Vector<string>& wordladder, const string& word1, const string& word2){
    if(word1 == word2){
        cout << "Found ladder" << wordladder[0];
    }else if(wordladder.size() == 1){
        cout << "No word ladder between \"" << word1 << "\" and \"" << word2 << "\" could be found.";
    }else {
        cout << "change process:";
        for(string word: wordladder){
            cout << "  " << word;
        }
    }
    cout << endl << endl;
}
