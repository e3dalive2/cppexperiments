#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

#include <list>
#include <unordered_map>

class LRUCache:public Cache
{
    public:
    
    std::list<std::pair<int, int>> itemList; // List to store the cache items as (key, value) pairs
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> cacheMap; // Map to hold keys and pointers to the items in itemList
    
    size_t maxSize=0;    
    int id_invalid=-1;
    
    LRUCache(int amt):maxSize(amt)
    {

    }
    
    void set(int key,int value) override
    {
        auto it = cacheMap.find(key);
        if (it != cacheMap.end()) {
            // Key found, update the value and move to the front
            it->second->second = value;
            itemList.splice(itemList.begin(), itemList, it->second);
        } else {
            // Key not found, check if the cache is full
            if (itemList.size() == maxSize) {
                // Remove the least recently used item
                auto last = itemList.back();
                cacheMap.erase(last.first);
                itemList.pop_back();
            }
            // Add the new item to the front
            itemList.emplace_front(key, value);
            cacheMap[key] = itemList.begin();
        }
    }
    int get(int key) override
    {
        auto it = cacheMap.find(key);
        if (it == cacheMap.end()) {
            // Key not found
            return -1;
        } else {
            // Move the accessed item to the front of the list
            itemList.splice(itemList.begin(), itemList, it->second);
            return it->second->second;
        }
    }
};

int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}
