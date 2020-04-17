#include "lib.hpp"
#include <cmath>
#include <iostream>
#include <exception>

//Constructor for an Entry. Takes a key and a value
//and stores it publicly.
Entry::Entry(int key, int value) : key(key), value(value) {}

//Inserts itself into ostream to be compatible with that library.
std::ostream & Entry::ins (std::ostream & os) const {
    return os << key << " : " << value;
}

//Assigning a new value for a specific key.
Entry & Entry::operator= (int value) {
    this->value = value;
    return *this;
}

//Uses the inserter to return the the calling stream and insert itself there.
std::ostream & operator<< (std::ostream & os, const Entry & ob) {
    return ob.ins(os);
} 

//Constructor for a HashMap. Creates as many entries as
//the given absolute value of the first parameter.
//Positions are assigned nullptr by default.
HashMap::HashMap(unsigned size) : vSize(abs(size)){
    std::cout << "Calling constructor of HashMap. (vSize = " << vSize << ")\n";
    HashTable = new Entry*[vSize];
    for (unsigned i = 0; i < vSize; i++)
        HashTable[i] = nullptr;
}

//Copy constructor for HashMap. Copies all of the
//entries in the right side HashMap to the same positions.
HashMap::HashMap(const HashMap & r) : vSize(r.vSize) {
    std::cout << "Calling copy constructor of HashMap. (r.vSize = " << vSize << ")\n";
    HashTable = new Entry*[vSize];
    for (unsigned i = 0; i < vSize; i++)
        if (HashTable[i] != nullptr) 
            HashTable[i] = r.HashTable[i];
}

//Calls class desctructor, copies thr right's HashMap size
//and copies all of the entries to the same positions.
HashMap & HashMap::operator= (const HashMap & r) {
    std::cout << "Calling equal redefinition and destructor. ";
    if (HashTable != nullptr) {
        for (unsigned i = 0; i < vSize; i++) {
            if (HashTable[i] != nullptr) {
                delete HashTable[i];
                HashTable[i] = nullptr;
            }
        }
        delete HashTable;
        HashTable = nullptr;
    }

    vSize = r.vSize;

    std::cout << "New vSize = " << vSize << '\n';

    HashTable = new Entry*[vSize];
    for (unsigned i = 0; i < vSize; i++)
        if (HashTable[i] != nullptr) 
            HashTable[i] = r.HashTable[i];
    
    return *this;
}

//Destructor for a HashMap. 
//Frees up space associated with the HashTable.
HashMap::~HashMap() {
    std::cout << "Calling destructor of HashMap.\n";
    for (unsigned i = 0; i < vSize; i++) {
        if (HashTable[i] != nullptr) {
            delete HashTable[i];
            HashTable[i] = nullptr;
        }
    }
    delete HashTable;
    HashTable = nullptr;
}   

//Returns the modulo of the given key by the size of the HashTable.
unsigned HashMap::keyMod(int key) {
    return abs(key) % vSize;
}

//Removes the given key from the HashTable
//and replaces it with a nullptr.
void HashMap::removeKey(int key) {
    long long pos = searchKey(key);
    if (-1 != pos) {
        delete HashTable[pos];
        HashTable[pos] = nullptr;
    }
}

//Removes the given value from the HashTable
//and replaces it with a nullptr.
//This method only removes one instance of
//an entry with the given value with which
//ever is closer to the start of the HashTable.
void HashMap::removeValue(int value) {
    long long pos = searchValue(value);
    if (-1 != pos) {
        delete HashTable[pos];
        HashTable[pos] = nullptr; 
    }
}

//Returns the position at which a key has
//been found in HashTable. If a key is not
//found, function returns -1.
long long HashMap::searchKey(int key) {
    for (unsigned pos = keyMod(key); pos < vSize; pos++) {
        if (HashTable[pos] != nullptr)
            if (key == HashTable[pos]->key) 
                return pos;
    }
    return -1;
}

//Returns the position at which a value has
//been found in HashTable. If a value is not
//found, function returns -1.
long long HashMap::searchValue(int value) const {
    for (unsigned pos = 0; pos < vSize; pos++) {
        if (HashTable[pos] != nullptr)
            if (value == HashTable[pos]->value) 
                return pos;
    }
    return -1;
}

//Returns the number of maximum entries in HashTable.
unsigned HashMap::size() const {
    return vSize;
}

//Returns a pointer to the value associated with the given key.
//If no such key is found, it is created with a default value of 0.
Entry & HashMap::operator[](int key) {
    if (HashTable[keyMod(key)] == nullptr) {
        unsigned pos = keyMod(key);
        while (HashTable[pos] != nullptr && pos < vSize - 1) {
            pos = keyMod(pos + 1);
        }
        if (HashTable[pos] != nullptr && vSize - 1 == pos) {
            throw std::bad_alloc();
        }
        HashTable[pos] = new Entry(key, 0);
    }
    return *HashTable[searchKey(key)];
}

//Inserts itself into ostream to be compatible with that library.
std::ostream & HashMap::ins (std::ostream & os) const {
    std::cout << "pos : key : value\n";
    for (unsigned pos = 0; pos < vSize; pos++)
         if (HashTable[pos] != nullptr) std::cout << pos << " : " << HashTable[pos]->key << " : " << HashTable[pos]->value << '\n';
    return os;
}

//Uses the inserter to return the the calling stream and insert itself there.
std::ostream & operator<< (std::ostream & os, const HashMap & ob) {
    return ob.ins(os);
}
