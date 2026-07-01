#include "BinaryTree.hpp"

#include <algorithm>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>

// Destructor: Cleans up the tree
BinaryTree::~BinaryTree() { destroyTree(root_); }

// Shared random number generator
std::mt19937& BinaryTree::rng() {
    static std::mt19937 eng{std::random_device{}()};
    return eng;
}

// Recursively deletes all nodes in the tree
void BinaryTree::destroyTree(Node* x) {
    // TODO: Implement this method to clean up the tree

}

// Returns the number of nodes in the tree
int BinaryTree::getSize() const { 
    if (treeType_ == TreeType::HEAP) {
        return static_cast<int>(heapArray_.size()) - 1;
    }
    return calculateSize(root_); 
}

// Helper: Recursively calculates the size of the tree
int BinaryTree::calculateSize(Node* x) const {
    // TODO: Implement this method to calculate the size of the tree

}

// Returns the height of the tree
int BinaryTree::getHeight() const { return calculateHeight(root_); }

int BinaryTree::calculateHeight(Node* x) const {
    // TODO: Implement this method to calculate the height of the tree

}

// Inserts an item into the tree
void BinaryTree::insert(int item) {
    switch (treeType_) {
        case TreeType::BST:
            {
                Node* newNode = insertBST(root_, item);
                if (!root_) root_ = newNode;
            }
            break;
        case TreeType::HEAP:
            {
                insertHeapArray(item);
                arrayToTree(); // Update tree representation
            }
            break;
        default:
            {
                Node* newNode = insertBST(root_, item);
                if (!root_) root_ = newNode;
            }
            break;
    }
}

// Heap insertion using array representation
void BinaryTree::insertHeapArray(int item) {
    // TODO: Implement this method to insert into the heap array


}

// Swim up operation for array-based heap
void BinaryTree::swimArray(int index) {
    // TODO: Implement this method to maintain heap property after insertion

}

// Delete maximum element from heap
int BinaryTree::deleteMax() {

    if (treeType_ != TreeType::HEAP) {
        throw std::runtime_error("deleteMax() can only be called on HEAP trees");
    }
    
    int maxValue = deleteMaxArray();
    arrayToTree(); // Update tree representation
    return maxValue;
}

// Classical heap deleteMax using array representation
int BinaryTree::deleteMaxArray() {
    // TODO: Implement this method to delete the maximum element from the heap array
    
}

// Sink down operation for array-based heap
void BinaryTree::sinkArray(int index) {
    // TODO: Implement this method to maintain heap property after deletion

}

// Peek at maximum element without removing it
int BinaryTree::peekMax() const {
    if (treeType_ != TreeType::HEAP) {
        throw std::runtime_error("peekMax() can only be called on HEAP trees");
    }
    
    if (static_cast<int>(heapArray_.size()) <= 1) {
        throw std::runtime_error("Heap is empty");
    }
    
    return heapArray_[1];
}

// Performs heap sort and returns sorted values in ascending order
std::vector<int> BinaryTree::heapSort() {
    // TODO: Implement this method to perform heap sort and return sorted values
    
}

// Convert heap array to tree representation
void BinaryTree::arrayToTree() {
    if (treeType_ != TreeType::HEAP) return;
    
    // Clear existing tree
    destroyTree(root_);
    root_ = nullptr;
    
    // Build tree from array (starting from index 1)
    if (static_cast<int>(heapArray_.size()) > 1) {
        root_ = arrayToTreeHelper(1);
    }
}

// Helper: Recursively build tree from array
BinaryTree::Node* BinaryTree::arrayToTreeHelper(int index) {
    // TODO: Implement this method to build tree from heap array

}

// Helper: Recursively inserts a node into BST
BinaryTree::Node* BinaryTree::insertBST(Node* x, int item) {
    // TODO: Implement this method to insert into the BST

}

// Finds a node with the given item in BST
BinaryTree::Node* BinaryTree::findBST(Node* x, int item) const {
    // TODO: Implement this method to find a node in the BST

}

// Helper: Recursively finds a node in a heap
BinaryTree::Node* BinaryTree::findHeap(Node* node, int item) const {
    // TODO: Implement this method to find a node in the heap tree

}

// Finds a node with the given item
BinaryTree::Node* BinaryTree::findNode(int item) const {
    switch (treeType_) {
        case TreeType::BST:
            return findBST(root_, item);
        case TreeType::HEAP:
            return findHeap(root_, item);
        default:
            return nullptr;
    }
}

// Visualizes the tree level by level
std::string BinaryTree::visualizeTree() const {
    std::ostringstream oss;

    if (!root_) return "Tree is empty.\n";

    oss << "Tree Visualization (Level Order):\n";
    
    // For heap, also show array representation
    if (treeType_ == TreeType::HEAP && static_cast<int>(heapArray_.size()) > 1) {
        oss << "Heap Array: [";
        for (int i = 1; i < static_cast<int>(heapArray_.size()); i++) {
            oss << heapArray_[i];
            if (i < static_cast<int>(heapArray_.size()) - 1) oss << ", ";
        }
        oss << "]\n";
    }
    
    std::queue<Node*> q;
    q.push(root_);

    while (!q.empty()) {
        int levelSize = static_cast<int>(q.size());

        for (int i = 0; i < levelSize; ++i) {
            Node* current = q.front();
            q.pop();

            if (current) {
                oss << current->item << " ";
                q.push(current->left);
                q.push(current->right);
            } else {
                oss << "null ";
            }
        }

        oss << "\n";
    }

    return oss.str();
}


// Creates a tree with random integers
BinaryTree BinaryTree::createRandomTree(int nodes) {
    BinaryTree tree;
    std::uniform_int_distribution<int> dist(0, RAND_INT_BOUND - 1);
    auto& eng = rng();
    for (int i = 0; i < nodes; ++i) tree.insert(dist(eng));
    return tree;
}

// Analyzes tree heights for random trees
void BinaryTree::analyzeRandomTreeHeights(int nodes, int trees) {
    int minHeight = RAND_INT_BOUND + 1;
    int maxHeight = 0;
    long long sum = 0;

    for (int i = 0; i < trees; ++i) {
        int height = createRandomTree(nodes).getHeight();
        minHeight = std::min(minHeight, height);
        maxHeight = std::max(maxHeight, height);
        sum += height;
    }

    int avgHeight = trees ? static_cast<int>(sum / trees) : 0;
    std::cout << trees << " " << nodes << "-node trees: "
              << "min_height=" << minHeight
              << ", max_height=" << maxHeight
              << ", avg_height=" << avgHeight << "\n";
}

// Returns BST values in sorted ascending order
std::vector<int> BinaryTree::bstSort() const {
    if (treeType_ != TreeType::BST) {
        throw std::runtime_error("bstSort() can only be called on BST trees");
    }
    
    std::vector<int> sortedValues;
    bstSortHelper(root_, sortedValues);
    return sortedValues;
}

// Helper: Recursively traverse BST to get sorted values
void BinaryTree::bstSortHelper(Node* node, std::vector<int>& sortedValues) const {
    // TODO: Implement this method to get sorted values from BST nodes

}
