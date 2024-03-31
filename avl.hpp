#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>

template <typename T>
class AVL
{
private:
    struct Node;
public:
    AVL();
    ~AVL();
    Node* getRoot() const;
    void insert(const T&);
    void remove(const T&);
    bool search(const T&) const;
    Node* getSuccessor(const T&) const;
    Node* getPredecessor(const T&) const;
    void traverse(void (*)(const T&)) const;
    Node* rotateLeft(Node*);
    Node* rotateRight(Node*);
    Node* getMax(Node*) const;
    Node* getMin(Node*) const;
    int getHeight(Node*) const;
    int getBF(Node*) const;
    void printTree(Node*, int depth = 0) const;

private:
    struct Node
    {
        Node* _left;
        Node* _right;
        T _data;

        explicit Node(const T&);
        T getData() const;
    };

    Node* _root;

    Node* insert(Node*, const T&);
    Node* remove(Node*, const T&);
    Node* search(Node*, const T&) const;
    void traverse(Node*, void (*)(const T&)) const;
    void destroyTree(Node*);
};

#include "avl.tpp"

#endif // AVL_HPP