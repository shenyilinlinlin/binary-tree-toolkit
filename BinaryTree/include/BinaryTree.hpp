#ifndef BinaryTree__HPP
#define BinaryTree__HPP

#include <random>
#include <string>
#include <sstream>
#include <queue>
#include <iostream>
#include <vector>

class BinaryTree {
public:
    static constexpr int RAND_INT_BOUND = 300; // Upper bound for random integers

    enum class TreeType {
        BST,
        HEAP,
    };

    BinaryTree() = default;
    explicit BinaryTree(TreeType type) : treeType_(type) {} 
    ~BinaryTree();
    
    TreeType getTreeType() const { return treeType_; }

    // Tree operations on the whole tree
    int getSize() const;
    int getHeight() const;
    void insert(int item);
    std::string visualizeTree() const;

    class Node {
    public:
        int item;
        Node* left;
        Node* right;

        explicit Node(int v) : item(v), left(nullptr), right(nullptr) {}
        std::string toString() const { return std::to_string(item); }
    };

    Node* findNode(int item) const;

    // Heap-specific operations
    int deleteMax(); // Returns the maximum element and removes it from heap
    int peekMax() const; // Returns the maximum element without removing it
    std::vector<int> heapSort(); // Performs heap sort and returns sorted values in ascending order

    // BST-specific operations
    std::vector<int> bstSort() const; // Returns BST values in sorted (ascending) order

    // Static utility methods for creating and analyzing trees
    static BinaryTree createRandomTree(int nodes);
    static void analyzeRandomTreeHeights(int nodes, int trees);

    // Static utility methods for generating orders
    static std::vector<int> generateSortedOrder(int n);
    static void generateBalancedOrder(const std::vector<int>& nodes, int start, int end, std::vector<int>& result);

private:
    Node* root_ { nullptr };
    TreeType treeType_ { TreeType::BST }; // Default to BST
    
    // Array representation for heap (1-indexed, position 0 unused)
    std::vector<int> heapArray_;

    static std::mt19937& rng();

    int calculateSize(Node* x) const; 
    int calculateHeight(Node* x) const; 
    void destroyTree(Node* x); 

    Node* insertBST(Node* x, int item); 
    Node* findBST(Node* x, int item) const; 

    // Heap operations using array representation
    void insertHeapArray(int item);
    int deleteMaxArray();
    void swimArray(int index);  // Move element up in array heap
    void sinkArray(int index);  // Move element down in array heap
    
    // Conversion functions between array and tree representations
    void arrayToTree();  // Convert heap array to tree representation
    
    // Helper functions for array-tree conversion
    Node* arrayToTreeHelper(int index);

    Node* findHeap(Node* x, int item) const; 

    void bstSortHelper(Node* node, std::vector<int>& sortedValues) const;
    };

#endif // BinaryTree__HPP