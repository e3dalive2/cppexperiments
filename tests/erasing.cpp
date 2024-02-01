#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int N;
    cin>>N;
    std::vector<int> data;
    data.resize(N);
    for(auto &v:data)
    {
        cin>>v;
    }
    
    int query;
    cin>>query;
    
    int a,b;
    cin>>a;
    cin>>b;
    
    query--;
    a--;
    b--;
    data.erase(data.begin()+query);
    
    data.erase(data.begin()+a,data.begin()+b);
    
    
    cout<<data.size()<<"\n";
    for(auto v:data){cout<<v<<" ";}
    
    return 0;
}
