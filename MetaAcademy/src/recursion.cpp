/* 
 * TODO: put your own comments here. Also you should leave comments on
 * each of your methods.
 */

#include <math.h>
#include <cmath>
#include "recursion.h"
#include <map>
#include "vector.h"
#include "set.h"
#include "gwindow.h"
#include "gobjects.h"
#include "tokenscanner.h"
#include "stack.h"
#include "queue.h"
using namespace std;
void personalCurriculum1(Map<string, Vector<string>> & prereqMap, string goal, Map<string, string> & mymap, Stack<string> & mystack);

Map<string, string> mymap;
Stack<string> mystack;

int gcd(int a, int b) {
    if(b == 0){
        cout << "gcd(" << a << ", " << b << ") = " << b << endl;
        return a;
    }else {
        cout << "gcd(" << a << ", " << b << ") = gcd(" << b << ", " << a % b << ")" << endl;
        return gcd(b, a % b);
    }
    cout << "[recursion gcd called]" << endl;
    return 0;
}

void serpinskii(GWindow &w, int leftX, int leftY, int size, int order) {
    if (order == 1){
        w.drawLine(leftX, leftY,  leftX + size, leftY);
        w.drawLine(leftX + size, leftY, leftX + size / 2, leftY + size * sqrt(3.0) / 2);
        w.drawLine(leftX + size / 2, leftY + size * sqrt(3.0) / 2, leftX, leftY);
    }else {
        serpinskii(w, leftX, leftY, size / 2, order - 1);
        serpinskii(w, leftX + size / 2, leftY, size / 2, order - 1);
        serpinskii(w, leftX + size / 4, leftY + size * sqrt(3.0) / 4, size / 2, order - 1);
    }
    cout << "[recursion serpinskii called]" << endl;
}

int floodFill(GBufferedImage& image, int x, int y, int newColor) {
    int localcloor = image.getRGB(x, y);
    int cnt = 0;
    if(localcloor == newColor || !image.inBounds(x,y)){
        return 0;
    }else {
        image.setRGB(x, y, newColor);
        cnt++;
        if(image.getRGB(x , y - 1) == localcloor){
            cnt += floodFill(image, x, y - 1, newColor);
        }if(image.getRGB(x - 1, y) == localcloor){
            cnt += floodFill(image, x - 1, y, newColor);
        }if((image.getRGB(x, y + 1) == localcloor)){
            cnt += floodFill(image, x, y + 1, newColor);
        }if(image.getRGB(x + 1, y) == localcloor){
            cnt += floodFill(image, x + 1, y, newColor);
        }
    }

//    if(image.getRGB(x + 1, y) == localcloor){
//        image.setRGB(x + 1, y, newColor);
//        count++;
//        return floodFill(image, x + 1, y, newColor);
//    }else if (image.getRGB(x - 1, y) == localcloor){
//        image.setRGB(x - 1, y, newColor);
//        count++;
//        return floodFill(image, x - 1, y, newColor);
//    }else if(image.getRGB(x, y + 1) == localcloor){
//        image.setRGB(x, y + 1, newColor);
//        count++;
//        return floodFill(image, x , y + 1, newColor);
//    }

    cout << "[recursion flood fill called]" << endl;
    return cnt;
}

void personalCurriculum(Map<string, Vector<string>> & prereqMap, string goal) {
    Map<string, string> mymap;
    Stack<string> mystack;
    mystack.push(goal);
    personalCurriculum1(prereqMap, goal, mymap, mystack);
    while (!mystack.isEmpty()){
        cout << mystack.top() << endl;
        mystack.pop();
    }
    cout << "[recursion personal curriculum called]" << endl;
}

void personalCurriculum1(Map<string, Vector<string>> & prereqMap, string goal, Map<string, string> & mymap, Stack<string> & mystack){
    if (prereqMap.containsKey(goal)){
        for(int i = prereqMap[goal].size() - 1; i >= 0; i--){
            if(mymap.containsKey(prereqMap[goal][i])){
                continue;
            }else{
                mystack.push(prereqMap[goal][i]);
                //cout << prereqMap[goal][i] << endl;
                mymap.put(prereqMap[goal][i], "1");
            }
        }
        for(int i = prereqMap[goal].size() - 1; i >= 0; i--){
            personalCurriculum1(prereqMap, prereqMap[goal][i], mymap, mystack);
        }
    }
}

string generate(Map<string, Vector<string> > & grammar, string symbol) {
    srand(time(0));
    string str;
    Vector <string> array;
    if(!grammar.containsKey(symbol)){
        str=' '+symbol;
        return str;
    }
    else{
        string token;
        array=grammar.get(symbol);
        token=array[rand()%array.size()];
        TokenScanner s(token);
        while(s.hasMoreTokens()){
            string t=s.nextToken();
            str=str+' '+generate(grammar, t);
        }
    }
//    cout << "[recursion generate called]" << endl;
    return str;
}
