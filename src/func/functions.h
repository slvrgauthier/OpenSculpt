#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <stdlib.h>

using namespace std;

template<typename T>
bool contains(vector<T*> v, T* ptr) {
    for(unsigned int i = 0 ; i < v.size() ; ++i) {
        if(v[i] == ptr) {
            return true;
        }
    }
    return false;
}

#endif // FUNCTIONS_H
