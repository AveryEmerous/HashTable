#ifndef H_LIB
#define H_LIB

#include <iostream>

struct Entry {
    int key;
    int value;
    Entry(int key, int value);
};

class HashMap {
private:
    Entry ** HashTable;
    unsigned vSize;

public:
    HashMap(unsigned size);
    ~HashMap();

    unsigned keyMod(int key);
    void insert(int key, int value);
    void removeKey(int key);
    void removeValue(int value);
    long long searchKey(int key);
    long long searchValue(int value) const;
    
    unsigned size() const;

    void printTable() const;
    void printAt(int pos) const;
};

#endif