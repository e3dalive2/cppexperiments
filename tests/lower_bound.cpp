#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    cin>>n;
    std::vector<int> ints;
    ints.resize(n);
    for(auto &i:ints)
    {
        cin>>i;
    }
    
    int qr;
    cin>>qr;
    std::vector<int> ys;
    ys.resize(qr);
    for(auto &y:ys)
    {
        cin>>y;
    }
    
    
    for(const auto &y:ys)
    {
        auto it=std::lower_bound(ints.begin(),ints.end(),y);
        if(it==ints.end())
        {
            cout<<"Error "<<y;
        }
        else
        {
            int val=*it;
            int ix=it-ints.begin()+1;
            if(val==y)
            {
                cout<<"Yes ";             
            }
            else
            {
                cout<<"No ";
            }
            cout<<ix;

        }
        
        cout<<"\n";
    }
    
    return 0;
}
