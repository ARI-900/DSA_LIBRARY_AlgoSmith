#pragma once

#include <algorithm> // for std::max

// Do NOT include this file directly.
// It is automatically included at the bottom of BinarySearchTree.hpp.

namespace algosmith {

// ── Default Constructor ───────────────────────────────────────────────────────
template <typename T>
BinarySearchTree<T>::BinarySearchTree() noexcept : root_(nullptr), size_(0) {}


// ── Destructor ────────────────────────────────────────────────────────────────
template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
    clear(root_);
}


// ── Copy Constructor ──────────────────────────────────────────────────────────
template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree& other) : root_(nullptr), size_(other.size_) {
    root_ = clone(other.root_);
}


// ── Move Constructor ──────────────────────────────────────────────────────────
template <typename T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree&& other) noexcept
    : root_(std::exchange(other.root_, nullptr)), size_(std::exchange(other.size_, 0)) {}


// ── Copy Assignment ───────────────────────────────────────────────────────────
template <typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree& other) {
    if (this != &other) {
        BinarySearchTree tmp(other); // copy-and-swap idiom
        std::swap(root_, tmp.root_);
        std::swap(size_, tmp.size_);
    }
    return *this;
}


// ── Move Assignment ───────────────────────────────────────────────────────────
template <typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(BinarySearchTree&& other) noexcept {
    if (this != &other) {
        clear(root_);
        root_ = std::exchange(other.root_, nullptr);
        size_ = std::exchange(other.size_, 0);
    }
    return *this;
}


// ── deleteTree ────────────────────────────────────────────────────────────────
template <typename T>
void BinarySearchTree<T>::deleteTree() {
    clear(root_);
    root_ = nullptr;
    size_ = 0;
}


// ── Privates: clear & clone ───────────────────────────────────────────────────
template <typename T>
void BinarySearchTree<T>::clear(Node* node) noexcept {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::clone(Node* node) const {
    if (node == nullptr) return nullptr;
    Node* newNode = new Node(node->data);
    newNode->left = clone(node->left);
    newNode->right = clone(node->right);
    return newNode;
}


// ── insert ────────────────────────────────────────────────────────────────────
template <typename T>
void BinarySearchTree<T>::insert(const T& value) {
    bool inserted = false;
    root_ = insert(root_, value, inserted);
    if (inserted) {
        ++size_;
    }
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::insert(Node* node, const T& value, bool& inserted) {
    if (node == nullptr) {
        inserted = true;
        return new Node(value);
    }
    if (value < node->data) {
        node->left = insert(node->left, value, inserted);
    } else if (value > node->data) {
        node->right = insert(node->right, value, inserted);
    }
    // If value == node->data, inserted remains false (duplicate ignored)
    return node;
}


// ── remove ────────────────────────────────────────────────────────────────────
template <typename T>
void BinarySearchTree<T>::remove(const T& value) {
    bool removed = false;
    root_ = remove(root_, value, removed);
    if (removed) {
        --size_;
    } else {
        throw std::out_of_range("BinarySearchTree::remove: value not found.");
    }
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::remove(Node* node, const T& value, bool& removed) {
    if (node == nullptr) {
        return nullptr;
    }
    if (value < node->data) {
        node->left = remove(node->left, value, removed);
    } else if (value > node->data) {
        node->right = remove(node->right, value, removed);
    } else {
        // Match found!
        removed = true;
        
        // Case 1 & 2: 0 or 1 child
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        
        // Case 3: 2 children
        // Find min in right subtree (In-order successor)
        Node* minRight = findMin(node->right);
        node->data = minRight->data;
        // Delete the successor
        bool dummy = false;
        node->right = remove(node->right, minRight->data, dummy);
    }
    return node;
}


// ── search ────────────────────────────────────────────────────────────────────
template <typename T>
bool BinarySearchTree<T>::search(const T& value) const noexcept {
    return search(root_, value);
}

template <typename T>
bool BinarySearchTree<T>::search(Node* node, const T& value) const noexcept {
    if (node == nullptr) return false;
    if (value < node->data) return search(node->left, value);
    if (value > node->data) return search(node->right, value);
    return true; // Match found (value == node->data)
}


// ── findMin ───────────────────────────────────────────────────────────────────
template <typename T>
T BinarySearchTree<T>::findMin() const {
    if (isEmpty()) throw std::out_of_range("BinarySearchTree::findMin: tree is empty.");
    return findMin(root_)->data;
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::findMin(Node* node) const noexcept {
    if (node->left == nullptr) return node;
    return findMin(node->left);
}


// ── findMax ───────────────────────────────────────────────────────────────────
template <typename T>
T BinarySearchTree<T>::findMax() const {
    if (isEmpty()) throw std::out_of_range("BinarySearchTree::findMax: tree is empty.");
    return findMax(root_)->data;
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::findMax(Node* node) const noexcept {
    if (node->right == nullptr) return node;
    return findMax(node->right);
}


// ── isEmpty ───────────────────────────────────────────────────────────────────
template <typename T>
bool BinarySearchTree<T>::isEmpty() const noexcept {
    return root_ == nullptr;
}


// ── getSize ───────────────────────────────────────────────────────────────────
template <typename T>
std::size_t BinarySearchTree<T>::getSize() const noexcept {
    return size_;
}


// ── getHeight ─────────────────────────────────────────────────────────────────
template <typename T>
std::size_t BinarySearchTree<T>::getHeight() const noexcept {
    return height(root_);
}

template <typename T>
std::size_t BinarySearchTree<T>::height(Node* node) const noexcept {
    if (node == nullptr) return 0;
    return 1 + std::max(height(node->left), height(node->right));
}


// ── Traversals ────────────────────────────────────────────────────────────────

// In-Order Traversals
template <typename T>
void BinarySearchTree<T>::printInOrder(std::ostream& os) const {
    if (isEmpty()) {
        os << "[ EMPTY ]\n";
        return;
    }
    os << "[ ";
    inOrder(root_, os);
    os << "]\n";
}

template <typename T>
void BinarySearchTree<T>::inOrder(Node* node, std::ostream& os) const {
    if (node != nullptr) {
        inOrder(node->left, os);
        os << node->data << " ";
        inOrder(node->right, os);
    }
}


// Pre-Order
template <typename T>
void BinarySearchTree<T>::printPreOrder(std::ostream& os) const {
    if (isEmpty()) {
        os << "[ EMPTY ]\n";
        return;
    }
    os << "[ ";
    preOrder(root_, os);
    os << "]\n";
}

template <typename T>
void BinarySearchTree<T>::preOrder(Node* node, std::ostream& os) const {
    if (node != nullptr) {
        os << node->data << " ";
        preOrder(node->left, os);
        preOrder(node->right, os);
    }
}


// Post-Order
template <typename T>
void BinarySearchTree<T>::printPostOrder(std::ostream& os) const {
    if (isEmpty()) {
        os << "[ EMPTY ]\n";
        return;
    }
    os << "[ ";
    postOrder(root_, os);
    os << "]\n";
}

template <typename T>
void BinarySearchTree<T>::postOrder(Node* node, std::ostream& os) const {
    if (node != nullptr) {
        postOrder(node->left, os);
        postOrder(node->right, os);
        os << node->data << " ";
    }
}


// Level-Order
template <typename T>
void BinarySearchTree<T>::printLevelOrder(std::ostream& os) const {
    if (isEmpty()) {
        os << "[ EMPTY ]\n";
        return;
    }
    
    os << "[ ";
    std::queue<Node*> q;
    q.push(root_);
    
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        
        os << current->data << " ";
        
        if (current->left != nullptr)  q.push(current->left);
        if (current->right != nullptr) q.push(current->right);
    }
    os << "]\n";
}

} // namespace algosmith
