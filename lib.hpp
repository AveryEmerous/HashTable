#ifndef H_LIB
#define H_LIB

#include <iostream>

struct Entry {
    int key;
    int value;
    
    Entry(int key, int value);
    Entry & operator= (int value);

    virtual std::ostream & ins (std::ostream & os) const;
};

std::ostream & operator<< (std::ostream & os, const Entry & ob);

class HashMap {
private:
    Entry ** HashTable;
    unsigned vSize;

public:
    HashMap(unsigned size = 0);
    HashMap(const HashMap & r);
    HashMap & operator= (const HashMap & r);
    ~HashMap();

    unsigned keyMod(int key);
    void removeKey(int key);
    void removeValue(int value);
    long long searchKey(int key);
    long long searchValue(int value) const;
    
    unsigned size() const;

    Entry & operator[](int key);

    virtual std::ostream & ins (std::ostream & os) const;
};

std::ostream & operator<< (std::ostream & os, const HashMap & ob);

#endif