#ifndef SCAPEGOAT_CPP
#define SCAPEGOAT_CPP

#include <iostream>
using namespace std;

template<typename T>
class ScapeNode {
public:
    T value;
    ScapeNode<T> *parent, *left, *right;

    ScapeNode(const T& val, ScapeNode<T>* par=nullptr) : value(val), parent(par), left(nullptr), right(nullptr) { }
    ScapeNode(const ScapeNode*& pOther) : value(pOther->value), parent(pOther->parent) {
        if(pOther->left != nullptr)
            left = new ScapeNode<T>(pOther->left);
        if(pOther->right != nullptr)
            right = new ScapeNode<T>(pOther->right);
    }
};

template<typename T>
class Scapegoat {
private:
    int _size;
    ScapeNode<T>* _root;

    void _erase(const T&, ScapeNode<T>*&);

    ScapeNode<T>* _insert(const T&, ScapeNode<T>*&);
    ScapeNode<T>* _find(const T&, ScapeNode<T>*) const;

public:
    Scapegoat();
    Scapegoat(const Scapegoat&);

    void insert(const T&);
    void erase(const T&);

    ScapeNode<T>* root();
    ScapeNode<T>* find(const T&) const;
    
};

template<typename T>
void Scapegoat<T>::_erase(const T& value, ScapeNode<T>*& root) {
    
}

template<typename T>
ScapeNode<T>* Scapegoat<T>::_insert(const T& value, ScapeNode<T>*& root) {
    if(root == nullptr)
        return new ScapeNode<T>(value, root);
    else if(value < root->value)
        return root->left = _insert(value, root->left);
    else if(value > root->value)
        return root->right = _insert(value, root->right);
    else
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
Scapegoat<T>::Scapegoat() : _size(0), _root(nullptr) { }

template<typename T>
Scapegoat<T>::Scapegoat(const Scapegoat& other) : _size(other.size()) {
    _root = new ScapeNode<T>(other.root());
}

template<typename T>
void Scapegoat<T>::insert(const T& value) {
    if(_root == nullptr)
        _root = new ScapeNode<T>(value);
    else
        _insert(value, _root);
}

template<typename T>
void Scapegoat<T>::erase(const T& value) {
    auto& toDelete = find(value);
    if(toDelete != nullptr) {
        if(toDelete->left==nullptr and toDelete->right==nullptr) {
            delete toDelete;
        }else if(toDelete->left==nullptr and toDelete->right!=nullptr) { // Solo figlio destro

        }else if(toDelete->left!=nullptr and toDelete->right==nullptr) { // Solo figlio sinistro

        }else { // Entrambi i figli

        }
    }
}

template<typename T>
ScapeNode<T>* Scapegoat<T>::root() {
    return _root;
}

template<typename T>
ScapeNode<T>* Scapegoat<T>::find(const T& value) const {
    return _find(value, _root);
}


int main()
{
    Scapegoat<int> scapegoat;

    int q;
    cin >> q;

    for(int i=0; i<q; ++i) {
        int type, value;
        cin >> type >> value;

        if(type == 0) {
            scapegoat.insert(value);
        }else {
            auto p = scapegoat.find(value);
            if(p == nullptr) {
                cout << "Niente " << value << " nello scapegoat!\n";
            }else {
                cout << value << " e' presente nello scapegoat!\n";
            }
        }
    }

    return 0;
}

#endif