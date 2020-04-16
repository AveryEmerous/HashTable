#include "lib.hpp"
#include <cmath>
#include <iostream>
#include <exception>

Entry::Entry(int key, int value) : key(key), value(value) {}

//Constructor for a HashMap. Creates as many entries as
//the given absolute value of the first parameter.
HashMap::HashMap(unsigned size) : vSize(abs(size)){
    std::cout << "Calling constructor of HashMap. (vSize = " << vSize << ")\n";
    HashTable = new Entry*[vSize];
    for (unsigned i = 0; i < vSize; i++)
        HashTable[i] = nullptr;
}

//Destructor for a HashMap. 
//Frees up associated with the HashTable.
HashMap::~HashMap() {
    std::cout << "Calling destructor of HashMap.\n";
    for (unsigned i = 0; i < vSize; i++) {
        if (HashTable[i] != nullptr) {
            delete HashTable[i];
            HashTable[i] = nullptr;
        }
    }
    delete HashTable;
}

//Returns the modulo of the given key by the size of the HashTable.
unsigned HashMap::keyMod(int key) {
    return abs(key) % vSize;
}

//Insert a key with a value to an available
//absolute key position in the HashTable.
void HashMap::insert(int key, int value) {
    unsigned pos = keyMod(key);
    while (HashTable[pos] != nullptr && pos < vSize - 1) {
        pos = keyMod(pos + 1);
    }
    if (HashTable[pos] != nullptr && vSize - 1 == pos) {
        throw std::bad_alloc();
    }
    HashTable[pos] = new Entry(key, value);
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

//Prints current table in format:
//pos(in HashTable) : key : value
void HashMap::printTable() const {
    std::cout << "pos : key : value\n";
    for (unsigned pos = 0; pos < vSize; pos++) {
        if (HashTable[pos] != nullptr) std::cout << pos << " : " << HashTable[pos]->key << " : " << HashTable[pos]->value << '\n';
    }
}

//Prints the key and values of the
//given coordinates in the console.
void HashMap::printAt(int pos) const {
    if (nullptr != HashTable[pos] && 0 <= pos) std::cout << pos << " : " << HashTable[pos]->key << " : " << HashTable[pos]->value << '\n';
}