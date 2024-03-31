#ifndef AVL_TPP
#define AVL_TPP

#include "avl.hpp"

template <typename T>
AVL<T>::AVL()
    : _root {nullptr} {}

template <typename T>
AVL<T>::~AVL()
{
    destroyTree(_root);
}

template <typename T>
void AVL<T>::destroyTree(AVL<T>::Node* node)
{
    if (node)
    {
        destroyTree(node->_left);
        destroyTree(node->_right);
        delete node;
    }
}

template <typename T>
typename AVL<T>::Node* AVL<T>::getRoot() const
{
    return _root;
}

template <typename T>
void AVL<T>::insert(const T& data)
{
    _root = insert(_root, data);
}

template <typename T>
typename AVL<T>::Node* AVL<T>::insert(AVL<T>::Node* node, const T& data)
{
    if (node == nullptr)
    {
        return new Node(data);
    }

    if (node->_data > data)
    {
        node->_left = insert(node->_left, data);
    }
    else
    {
        node->_right = insert(node->_right, data);
    }

    int bf = getBF(node);

    if (bf < -1 && data < node->_right->_data) // RL
    {
        node->_right = rotateRight(node->_right);
        return rotateLeft(node);
    }
    if (bf < -1 && data > node->_right->_data) // RR
    {
        return rotateLeft(node);
    }
    if (bf > 1 && data > node->_left->_data) // LR
    {
        node->_left = rotateLeft(node->_left);
        return rotateRight(node);
    }
    if (bf > 1 && data < node->_left->_data) // LL
    {
        return rotateRight(node);
    }

    return node;
}

template <typename T>
void AVL<T>::remove(const T& data)
{
    _root = remove(_root, data);
}

template <typename T>
typename AVL<T>::Node* AVL<T>::remove(AVL<T>::Node* node, const T& data)
{
    if (node == nullptr)
    {
        return node;
    }
    if (node->_data > data)
    {
        node->_left = remove(node->_left, data);
    }
    else if (node->_data < data)
    {
        node->_right = remove(node->_right, data);
    }
    else
    {
        if (node->_left == nullptr)
        {
            Node* tmp = node->_right;
            delete node;
            return tmp;
        }
        else if (node->_right == nullptr)
        {
            Node* tmp = node->_left;
            delete node;
            return tmp;
        }
        else
        {
            Node* tmp = getMax(node->_left);
            node->_data = tmp->_data;
            node->_left = remove(node->_left, tmp->_data);
        }
    }

    int bf = getBF(node);

    if (bf < -1 && getBF(node->_right) > 0) // RL
    {
        node->_right = rotateRight(node->_right);
        return rotateLeft(node);
    }
    if (bf < -1 && getBF(node->_right) <= 0) // RR
    {
        return rotateLeft(node);
    }
    if (bf > 1 && getBF(node->_left) < 0) // LR
    {
        node->_left = rotateLeft(node->_left);
        return rotateRight(node);
    }
    if (bf > 1 && getBF(node->_left) >= 0) // LL
    {
        return rotateRight(node);
    }

    return node;
}

template <typename T>
bool AVL<T>::search(const T& data) const
{
    return search(_root, data) != nullptr;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::search(AVL<T>::Node* node, const T& data) const
{
    if (node == nullptr || node->_data == data)
    {
        return node;
    }

    if (data < node->_data)
    {
        return search(node->_left, data);
    }
    else
    {
        return search(node->_right, data);
    }
}

template <typename T>
typename AVL<T>::Node* AVL<T>::getPredecessor(const T& data) const
{
    Node* pred = nullptr;
    Node* curr = _root;

    while (curr && curr->_data != data)
    {
        if (curr->_data < data)
        {
            pred = curr;
            curr = curr->_right;
        }
        else
        {
            curr = curr->_left;
        }
    }

    if (!curr || !curr->_left)
    {
        return pred;
    }

    return getMax(curr->_left);
}

template <typename T>
typename AVL<T>::Node* AVL<T>::getSuccessor(const T& data) const
{
    Node* suc = nullptr;
    Node* curr = _root;

    while (curr && curr->_data != data)
    {
        if (curr->_data > data)
        {
            suc = curr;
            curr = curr->_left;
        }
        else
        {
            curr = curr->_right;
        }
    }

    if (!curr || !curr->_right)
    {
        return suc;
    }

    return getMax(curr->_right);
}

template <typename T>
void AVL<T>::traverse(void (*func)(const T&)) const
{
    traverse(_root, func);
}

template <typename T>
void AVL<T>::traverse(AVL<T>::Node* node, void (*func)(const T&)) const
{
    if (node != nullptr)
    {
        // preorder
        // func(node->_data);
        traverse(node->_left, func);
        // inorder
        func(node->_data);
        traverse(node->_right, func);
        // postorder
        // func(node->_data);
    }
}

template <typename T>
typename AVL<T>::Node* AVL<T>::rotateLeft(AVL::Node* node)
{
    Node* y = node->_right;
    node->_right = y->_left;
    y->_left = node;

    return y;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::rotateRight(AVL<T>::Node *node)
{
    Node* y = node->_left;
    node->_left = y->_right;
    y->_right = node;

    return y;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::getMax(AVL<T>::Node* node) const
{
    Node* curr = node;
    while (curr->_right != nullptr)
    {
        curr = curr->_right;
    }

    return curr;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::getMin(AVL<T>::Node* node) const {
    Node* curr = node;
    while (curr->_left != nullptr)
    {
        curr = curr->_left;
    }

    return curr;
}

template <typename T>
int AVL<T>::getHeight(AVL<T>::Node* node) const {
    if (node == nullptr)
    {
        return -1;
    }

    return std::max(getHeight(node->_left), getHeight(node->_right)) + 1;
}

template <typename T>
int AVL<T>::getBF(AVL<T>::Node* node) const
{
    return getHeight(node->_left) - getHeight(node->_right);
}

template <typename T>
void AVL<T>::printTree(AVL<T>::Node* node, int depth) const
{
    if (node != nullptr)
    {
        printTree(node->_right, depth + 1);
        std::cout << std::string(depth * 4, ' ') << node->_data << std::endl;
        printTree(node->_left, depth + 1);
    }
}

template <typename T>
AVL<T>::Node::Node(const T& data)
    : _left {nullptr}
    , _right {nullptr}
    , _data {data} {}

template <typename T>
T AVL<T>::Node::getData() const
{
    return _data;
}

#endif // AVL_TPP