#include <map>  
  
#include <string>  
  
#include <iostream>  
  
using namespace std;  
  
int main()  
  
{  
  
    map<int, string> mapStudent;  
  
    mapStudent[0] = "student_one";  
  
    mapStudent[1] = "student_two";  
  
    mapStudent[2] = "student_three";  

    mapStudent[3] = "student_four";
  
    map<int, string>::iterator iter;  
  
    for(iter = mapStudent.begin(); iter != mapStudent.end(); iter++)  
  
       cout<<iter->first<<' '<<iter->second<<endl;  
}  