#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


#include <map>
#include <string>

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    
    int n;
    cin>>n;
    
    map<string,int> marks;
    
    
    std::vector<string> toPrint;
    for(int i=0;i<n;i++)
    {
        int type;
        cin>>type;
        if(type==1)
        {
            std::string x;
            int y;
            cin>>x;
            cin>>y;
            
            int &curMarks=marks[x];
            curMarks+=y;
        }
        else if(type==2 || type==3)
        {
            std::string x;
            cin>>x;
            if(type==2)
            {
                marks[x]=0;
            }
            else if(type==3)
            {
                string msg="0";
                auto it=marks.find(x);
                if(it!=marks.end())
                {
                    msg=std::to_string(it->second);
                }
                toPrint.emplace_back(msg);
            }
        }
    }
    
    for(const auto print:toPrint)
    {
        cout<<print<<"\n";
    }
    

    
    return 0;
}
