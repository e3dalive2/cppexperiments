#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    
    int q;
    cin>>q;
    
    set<int> s;
    
    std::vector<std::pair<int,int>> todo;
    for(int i=0;i<q;i++)
    {
        int x,y;
        cin>>x;
        cin>>y;
        
        todo.emplace_back(std::make_pair(x,y));
    }
    
    for(const auto &to:todo)
    {
        int oper=to.first;
        int val=to.second;
        
        if(oper==1)
        {
            s.insert(val);
        }
        else if(oper==2)
        {
            s.erase(val);
        }
        else if(oper==3)
        {
            auto it=s.find(val);
            if(it!=s.end())
            {
                cout<<"Yes\n";
            }
            else
            {
                cout<<"No\n";
            }
        }
    }
    
    return 0;
}



