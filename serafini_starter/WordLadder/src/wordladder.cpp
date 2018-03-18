#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <ctype.h>
#include "console.h"
#include "lexicon.h"

using namespace std;

int main() {
    cout << "Welcome to CS 106B Word Ladder." << endl;
    cout << "Please give me two English words, and I will change the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    int s;

    string name;
    do{
        s = 1;
        cout << "Dictionary file name?";
        cin >> name;
        fstream _file;
        _file.open(name, ios :: in);
        if(!_file){
            cout << "Unable to open that file.  Try again." << endl;
            s = 0;
        }
    }while(s == 0);

    string world1;
    string world2;
    do{
        s = 0;
        cout << "Word #1 (or Enter to quit):";
        cin >> world1;
        if (cin.get() == '\n'){
            cout << "Have a nice day." << endl;
            return 0;
        }
        while (world1[s]) {
            world1[s] = tolower(world1[s]);
            s++;
        }
        cout << "Word #2 (or Enter to quit):";
        cin >> world2;
        if(cin.get() == 'n'){
            cout << "Have a nice day." << endl;
            return 0;
        }
        s = 0;
        while (world2[s]) {
            world2[s] = tolower(world2[s]);
            s++;
        }

        if(world1 == world2){
            cout << "The two words must be different" << endl;
            continue;
        }
        if(sizeof(world1) != sizeof(world2)){
            cout << "The two words must be the same length." << endl;
            continue;
        }

        Lexicon lex(name);

        if((!lex.contains(world1)) || (!lex.contains(world2))){
            cout << "The two words must be found in the dictionary." << endl;
        }


    }while(world1 == world2 || sizeof(world1) != sizeof(world2) || (!lex.contains(world1)) || (!lex.contains(world2)));

    int flag[20] = {0};
    while (world1 != world2) {
        for(int i = 0; i < int(sizeof(world1)); i++){
            if(!flag[i]){
                string tem;
                tem = world2;
                tem[i] = world1[i];
                if(lex.contains(tem)){
                    world2 = tem;
                    flag[i] = 1;
                    cout << world2;
                }
            }
        }

    }



    return 0;
}
