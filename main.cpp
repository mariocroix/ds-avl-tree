#include "avl.hpp"

// Function to print data in the AVL tree nodes
template <typename T>
void printData(const T& data)
{
    std::cout << data << " ";
}

int main()
{
    AVL<int> avlTree;

    avlTree.insert(50);
    avlTree.insert(30);
    avlTree.insert(70);
    avlTree.insert(20);
    avlTree.insert(40);
    avlTree.insert(60);
    avlTree.insert(80);

    std::cout << "AVL Tree Structure:" << std::endl;
    avlTree.printTree(avlTree.getRoot());


    int searchElement = 40;
    std::cout << "\nSearching for element " << searchElement << ": ";
    if (avlTree.search(searchElement)) {
        std::cout << "Found" << std::endl;
    } else {
        std::cout << "Not Found" << std::endl;
    }

    int predecessorElement = 50;
    int pred = avlTree.getPredecessor(predecessorElement)->getData();
    std::cout << "\nPredecessor of " << predecessorElement << " is " << pred << std::endl;

    int successorElement = 40;
    int suc = avlTree.getSuccessor(successorElement)->getData();
    std::cout << "\nSuccessor of " << successorElement << " is " << suc << std::endl;

    int removeElement = 30;
    avlTree.remove(removeElement);
    std::cout << "\nAVL Tree after removing " << removeElement << ":" << std::endl;
    avlTree.printTree(avlTree.getRoot());

    std::cout << "\nIn-order Traversal: ";
    avlTree.traverse(printData);

    return 0;
}
