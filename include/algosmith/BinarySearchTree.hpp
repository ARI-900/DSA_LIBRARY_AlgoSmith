
#pragma once

#include <cstddef>      // std::size_t
#include <stdexcept>    // std::out_of_range
#include <ostream>      // std::ostream
#include <iostream>     // std::cout (default arg in print)
#include <queue>        // std::queue (for level-order traversal)
#include <utility>      // std::move, std::exchange

namespace algosmith {

// ============================================================================
//  BinarySearchTree<T>
//
//  Classic BST where:
//      left child  < parent
//      right child > parent
//  Duplicate values are ignored on insert.
//
//  Complexity (average / worst-case):
//      insert()        — O(log n) / O(n)
//      remove()        — O(log n) / O(n)
//      search()        — O(log n) / O(n)
//      findMin()       — O(log n) / O(n)
//      findMax()       — O(log n) / O(n)
//      getHeight()     — O(n)
//      getSize()       — O(1)
//      printInOrder()  — O(n)   ← produces sorted output
//      printLevelOrder()— O(n)  ← BFS
// ============================================================================

template <typename T>
class BinarySearchTree {

public:
    // ── Constructors / Destructor (Rule of Five) ──────────────────────────
    BinarySearchTree() noexcept;                                          // Default
    BinarySearchTree(const BinarySearchTree& other);                      // Copy constructor
    BinarySearchTree(BinarySearchTree&& other) noexcept;                  // Move constructor
    BinarySearchTree& operator=(const BinarySearchTree& other);           // Copy assignment
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept;       // Move assignment
    ~BinarySearchTree();                                                   // Destructor (RAII)

    // ── Modifiers ─────────────────────────────────────────────────────────
    void insert(const T& value);            // Ignores duplicates
    void remove(const T& value);            // throws std::out_of_range if not found
    void deleteTree();                      // Removes all nodes; tree is empty after this

    // ── Accessors ─────────────────────────────────────────────────────────
    [[nodiscard]] bool        search(const T& value)  const noexcept;
    [[nodiscard]] T           findMin()                const;             // throws if empty
    [[nodiscard]] T           findMax()                const;             // throws if empty
    [[nodiscard]] bool        isEmpty()                const noexcept;
    [[nodiscard]] std::size_t getSize()                const noexcept;
    [[nodiscard]] std::size_t getHeight()              const noexcept;

    // ── Traversals ────────────────────────────────────────────────────────
    void printInOrder   (std::ostream& os = std::cout) const; // Left → Root → Right (sorted)
    void printPreOrder  (std::ostream& os = std::cout) const; // Root → Left → Right
    void printPostOrder (std::ostream& os = std::cout) const; // Left → Right → Root
    void printLevelOrder(std::ostream& os = std::cout) const; // BFS level by level

private:
    struct Node {
        T     data;
        Node* left;
        Node* right;
        explicit Node(const T& val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node*       root_;
    std::size_t size_;

    // ── Private Recursive Helpers ──────────────────────────────────────────
    void        clear      (Node* node)                          noexcept;
    Node*       clone      (Node* node)                          const;
    Node*       insert     (Node* node, const T& value, bool& inserted);
    Node*       remove     (Node* node, const T& value, bool& removed);
    bool        search     (Node* node, const T& value)          const noexcept;
    Node*       findMin    (Node* node)                          const noexcept;
    Node*       findMax    (Node* node)                          const noexcept;
    std::size_t height     (Node* node)                          const noexcept;
    void        inOrder    (Node* node, std::ostream& os)        const;
    void        preOrder   (Node* node, std::ostream& os)        const;
    void        postOrder  (Node* node, std::ostream& os)        const;
};

} // namespace algosmith

// Template definitions must be visible at compile time
#include "../../src/BinarySearchTree.tpp"
