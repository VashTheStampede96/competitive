#ifndef SCAPEGOAT_CPP
#define SCAPEGOAT_CPP

#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class ScapeNode {
public:
    int size;
    T value;
    ScapeNode<T> *parent, *left, *right;

    ScapeNode(const T& val, ScapeNode<T>* par=nullptr) : size(1), value(val), parent(par), left(nullptr), right(nullptr) { }
    ScapeNode(const ScapeNode*& pOther) : size(pOther->size), value(pOther->value), parent(pOther->parent) {
        if(pOther->left != nullptr)
            left = new ScapeNode<T>(pOther->left);
        if(pOther->right != nullptr)
            right = new ScapeNode<T>(pOther->right);
    }

    ~ScapeNode() {
        if(left != nullptr)
            delete left;
        if(right != nullptr)
            delete right;
    }
};

template<typename T>
class Scapegoat {
private:
    size_t _size;
    float _alpha;
    ScapeNode<T>* _root;

    void _erase(const T&, ScapeNode<T>*&);
    void _getOrdered(ScapeNode<T>*, std::vector<T>&);

    ScapeNode<T>* _insert(const T&, ScapeNode<T>*&, ScapeNode<T>*&);
    ScapeNode<T>* _find(const T&, ScapeNode<T>*) const;
    ScapeNode<T>* _predecessor(const ScapeNode<T>*) const;
    ScapeNode<T>* _reBuild(ScapeNode<T>*);
    ScapeNode<T>* _recReBuild(typename std::vector<T>::iterator, typename std::vector<T>::iterator);

public:
    Scapegoat(float=0.5f);
    Scapegoat(const Scapegoat&);
    ~Scapegoat();

    void insert(const T&);
    void erase(const T&);

    size_t size() const;

    ScapeNode<T>* root();
    ScapeNode<T>* find(const T&) const;
    ScapeNode<T>* end() const;
    
};

// PRIVATE METHODS --------------------------------------------------------------------

template<typename T>
void Scapegoat<T>::_erase(const T& value, ScapeNode<T>*& root) {
    
}

template<typename T>
void Scapegoat<T>::_getOrdered(ScapeNode<T>* root, std::vector<T>& orderedValues) {
    if(root->left != nullptr)
        _getOrdered(root->left, orderedValues);
    orderedValues.push_back(root->value);
    if(root->right != nullptr)
        _getOrdered(root->right, orderedValues);
}

template<typename T>
ScapeNode<T>* Scapegoat<T>::_insert(const T& value, ScapeNode<T>*& root, ScapeNode<T>*& parent) {
    int x = 0;
    if(root == nullptr)
        return new ScapeNode<T>(value, parent);
    else if(value < root->value) {
        root->left = _insert(value, root->left, root);
        x = root->left->size;
    }else if(value > root->value) {
        root->right = _insert(value, root->right, root);
        x = root->right->size;
    }
    
    ++(root->size);

    if((float)x > _alpha*root->size) {
        root = _reBuild(root);
        root->parent = parent;
    }

    
    return root;
}

template<typename T>
ScapeNode<T>* Scapegoat<T>::_find(const T& value, ScapeNode<T>* root) const {
    if(root == nullptr or root->value == value)
        return root;
    else if(value < root->value)
        return _find(value, root->left);
    else
        return _find(value, root->right);
}

template<typename T>
ScapeNode<T>* Scapegoat<T>::_predecessor(const ScapeNode<T>* root) const {
    auto current = root->left;
    while(current->right != nullptr)
        current = current->right;
    
    return current;
}

template<typename T>
ScapeNode<T>* Scapegoat<T>::_reBuild(ScapeNode<T>* root) {
    std::vector<T> orderedValues;
    orderedValues.reserve(root->size);

    _getOrdered(root, orderedValues);
    auto tmp = root->parent;

    return _recReBuild(orderedValues.begin(), orderedValues.end());
}

template<typename T>
ScapeNode<T>* Scapegoat<T>::_recReBuild(typename std::vector<T>::iterator beg, typename std::vector<T>::iterator end) {
    if(beg != end) {
        auto mid = beg + std::distance(beg, end)/2;
        auto root = new ScapeNode<T>(*mid);
        root->left = _recReBuild(beg, mid);
        root->right = _recReBuild(++mid, end);

        return root;
    }
}

// PUBLIC METHODS ----------------------------------------------------------------------------

template<typename T>
Scapegoat<T>::Scapegoat(float alpha) : _size(0), _alpha(alpha), _root(nullptr) {
}

template<typename T>
Scapegoat<T>::Scapegoat(const Scapegoat& other) : _size(other.size()), _alpha(other->_alpha) {
    _root = new ScapeNode<T>(other.root());
}

template<typename T>
Scapegoat<T>::~Scapegoat() {
    delete _root;
}

template<typename T>
void Scapegoat<T>::insert(const T& value) {
    if(_root == nullptr) {
        _root = new ScapeNode<T>(value);
        _root->parent = _root;
    }else
        _insert(value, _root, _root->parent);
}

template<typename T>
void Scapegoat<T>::erase(const T& value) {
    auto toDelete = find(value);
    if(toDelete != nullptr) {
        if(toDelete->left!=nullptr and toDelete->right!=nullptr) {
            auto pred = _predecessor(toDelete);
            std::swap(pred->value, toDelete->value);
            toDelete = pred;
        }

        if(toDelete->left==nullptr and toDelete->right==nullptr) {
            delete toDelete;
        }else if(toDelete->left==nullptr and toDelete->right!=nullptr) { // Solo figlio destro
            toDelete->right->parent = toDelete->parent;
            if(toDelete == toDelete->parent->left)
                toDelete->parent->left = toDelete->right;
            else
                toDelete->parent->right = toDelete->right;
        }else if(toDelete->left!=nullptr and toDelete->right==nullptr) { // Solo figlio sinistro
            toDelete->left->parent = toDelete->parent;
            if(toDelete == toDelete->parent->left)
                toDelete->parent->left = toDelete->left;
            else
                toDelete->parent->right = toDelete->left;
        }
    }
}

template<typename T>
size_t Scapegoat<T>::size() const {
    return _size;
}

template<typename T>
ScapeNode<T>* Scapegoat<T>::root() {
    return _root;
}

template<typename T>
ScapeNode<T>* Scapegoat<T>::find(const T& value) const {
    return _find(value, _root);
}

template<typename T>
ScapeNode<T>* Scapegoat<T>::end() const {
    return _root->parent;
}


enum qType {insert, find, erase};

int main()
{
    Scapegoat<int> scapegoat(0.66);

    int q;
    cin >> q;

    for(int i=0; i<q; ++i) {
        int type, value;
        cin >> type >> value;

        switch(type) {
            case qType::insert: cerr << "Inserting...\n"; scapegoat.insert(value); break;
            case qType::find: cout << (scapegoat.find(value)!=nullptr ? "Trovato!\n" : "Non trovato!\n"); break;
            case qType::erase: cerr << "Erasing...\n"; scapegoat.erase(value); break;
            default: break;
        }
    }

    return 0;
}

#endif