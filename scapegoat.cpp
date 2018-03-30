#ifndef _SCAPEGOAT_TREE_
#define _SCAPEGOAT_TREE_

#include <limits>
#include <string>
#include <vector>

/* 
 * Definition of ScapeNode<T>
 */

template<typename T>
class ScapeNode {
public: // Public stuff
    size_t size;
    T value;
    scapeNode<T> *parent, *left, *right;

    ScapeNode(const T&);
};

template<typename T>
ScapeNode<T>::ScapeNode(const T & value) : value(value), parent(nullptr), left(nullptr), right(nullptr) {

}

/*
 * Definition of Scapegoat<T>
 */

template<typename T>
class Scapegoat {
private: // Private attributes
    size_t _size;
    float _alpha;
    ScapeNode<T>* _root;

private: // Private Methods
    void _buildFromOrdered(ScapeNode<T>*, typename std::vector<T>::iterator, typename std::vector<T>::iterator);

public: // Public Methods
    Scapegoat(float);
    Scapegoat(const Scapegoat&);
    ~Scapegoat();

    void insert(const T&); // @TODO
    void erase(const T&); // @TODO

    ScapeNode<T>* find(const T&); // @TODO
    ScapeNode<T>* predecessor(const T&); // @TODO

    Scapegoat& operator=(const Scapegoat&); // @TODO

    std::vector<T> getOrderedItems(); // @TODO
};

/*
 * Public Methods implementation
 */

template<typename T>
Scapegoat<T>::Scapegoat(float _alpha)
: _size(1),
  _alpha(_alpha),
  _root(new ScapeNode<T>(std::numeric_limits<T>::max())) {

}

template<typename T>
Scapegoat<T>::Scapegoat(const Scapegoat & other)
: _size(other._size),
  _alpha(other._alpha) {
    auto orderedItems = other.getOrderedItems();
    _buildFromOrdered(_root, orderedItems.begin(), orderedItems.end());

    return *this;
}

template<typename T>
Scapegoat<T>::~Scapegoat() {
    _recRemove(_root);

}




template<typename T>
void Scapegoat<T>::insert(const T & value) {

}

template<typename T>
void Scapegoat<T>::erase(const T & value) {

}





template<typename T>
ScapeNode<T>* Scapegoat<T>::find(const T & value) {

}

template<typename T>
ScapeNode<T>* scapegoat<T>::predecessor(const T & value) {

}


#endif