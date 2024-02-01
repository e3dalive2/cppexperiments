#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


class Person
{
public:    
    virtual void getdata()
    {
        cin>>name;
        cin>>age;      
    }
    virtual void putdata()
    {
        cout<<name<<" "<<age;
    }
    
    std::string name;
    int age;
    
};

class Student:public Person
{
public:
vector<int> marks;
  
static int instanceCount;  
int id;  
    Student()
    {
        marks.resize(6);
        id=++instanceCount;
    }  

    virtual void getdata() override
    {
        Person::getdata();
        for(auto &m:marks)
        {
            cin>>m;
        }
    }
    virtual void putdata() override
    {
        Person::putdata();
        cout<<" ";
        int sum=0;
        for(auto m:marks)
        {
            sum+=m;
        }
        cout<<sum<<" "<<id<<"\n";
    }
};

int Student::instanceCount=0;

class Professor:public Person
{
    int publications;
public:

static int instanceCount;  
int id;  
Professor()
{
    id=++instanceCount;
}

    virtual void getdata() override
    {
        Person::getdata();
        cin>>publications;
    }
    virtual void putdata() override
    {
        Person::putdata();
        cout<<" "<<publications<<" "<<id<<"\n";
    }
};

int Professor::instanceCount=0;

int main(){

    int n, val;
    cin>>n; //The number of objects that is going to be created.
    Person *per[n];

    for(int i = 0;i < n;i++){

        cin>>val;
        if(val == 1){
            // If val is 1 current object is of type Professor
            per[i] = new Professor;

        }
        else per[i] = new Student; // Else the current object is of type Student

        per[i]->getdata(); // Get the data from the user.

    }

    for(int i=0;i<n;i++)
        per[i]->putdata(); // Print the required output for each object.

    return 0;

}
