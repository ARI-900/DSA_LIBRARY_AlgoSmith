
#pragma once

// Do NOT include this file directly.
// It is automatically included at the bottom of LinkedList.hpp.

namespace algosmith {

// ── Default Constructor ───────────────────────────────────────────────────────
template <typename T>
LinkedList<T>::LinkedList() noexcept
    : head_(nullptr), tail_(nullptr), size_(0) {}


// ── Destructor ────────────────────────────────────────────────────────────────
template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}


// ── Copy Constructor ──────────────────────────────────────────────────────────
template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other)
    : head_(nullptr), tail_(nullptr), size_(0) {
    Node* cursor = other.head_;
    while (cursor != nullptr) {
        insertAtTail(cursor->data);
        cursor = cursor->next;
    }
}


// ── Move Constructor ──────────────────────────────────────────────────────────
template <typename T>
LinkedList<T>::LinkedList(LinkedList&& other) noexcept
    : head_(std::exchange(other.head_, nullptr)),
      tail_(std::exchange(other.tail_, nullptr)),
      size_(std::exchange(other.size_, 0)) {}


// ── Copy Assignment ───────────────────────────────────────────────────────────
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
    if (this != &other) {
        LinkedList tmp(other);          // copy-and-swap idiom
        std::swap(head_, tmp.head_);
        std::swap(tail_, tmp.tail_);
        std::swap(size_, tmp.size_);
    }
    return *this;
}


// ── Move Assignment ───────────────────────────────────────────────────────────
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& other) noexcept {
    if (this != &other) {
        clear();
        head_ = std::exchange(other.head_, nullptr);
        tail_ = std::exchange(other.tail_, nullptr);
        size_ = std::exchange(other.size_, 0);
    }
    return *this;
}


// ── Private: clear() ──────────────────────────────────────────────────────────
template <typename T>
void LinkedList<T>::clear() noexcept {
    while (head_ != nullptr) {
        Node* tmp = head_;
        head_     = head_->next;
        delete tmp;
    }
    tail_ = nullptr;
    size_ = 0;
}


// ── insertAtHead ──────────────────────────────────────────────────────────────
template <typename T>
void LinkedList<T>::insertAtHead(const T& value) {
    Node* newNode = new Node(value);
    if (head_ == nullptr) {
        head_ = newNode;
        tail_ = newNode;        // first node → both head_ and tail_ point here
    } else {
        newNode->next = head_;
        head_         = newNode;
    }
    ++size_;
}


// ── insertAtTail ──────────────────────────────────────────────────────────────
// O(1) because of tail_ pointer
template <typename T>
void LinkedList<T>::insertAtTail(const T& value) {
    Node* newNode = new Node(value);
    if (head_ == nullptr) {
        head_ = newNode;
        tail_ = newNode;
    } else {
        tail_->next = newNode;
        tail_       = newNode;
    }
    ++size_;
}


// ── insertAtPosition ─────────────────────────────────────────────────────────
// pos = 0 → same as insertAtHead
// pos >= size_ → same as insertAtTail
template <typename T>
void LinkedList<T>::insertAtPosition(std::size_t pos, const T& value) {
    if (pos == 0 || isEmpty()) {
        insertAtHead(value);
        return;
    }
    if (pos >= size_) {
        insertAtTail(value);
        return;
    }
    Node* cursor = head_;
    for (std::size_t i = 0; i < pos - 1; ++i) {
        cursor = cursor->next;
    }
    Node* newNode   = new Node(value);
    newNode->next   = cursor->next;
    cursor->next    = newNode;
    ++size_;
}


// ── deleteAtHead ──────────────────────────────────────────────────────────────
template <typename T>
void LinkedList<T>::deleteAtHead() {
    if (isEmpty()) {
        throw std::out_of_range("deleteAtHead(): list is empty.");
    }
    Node* tmp = head_;
    head_     = head_->next;
    if (head_ == nullptr) {
        tail_ = nullptr;        // list is now empty; fix tail_ too
    }
    delete tmp;
    --size_;
}


// ── deleteAtTail ──────────────────────────────────────────────────────────────
// O(n) — singly-linked list must walk to second-last node
template <typename T>
void LinkedList<T>::deleteAtTail() {
    if (isEmpty()) {
        throw std::out_of_range("deleteAtTail(): list is empty.");
    }
    if (size_ == 1) {
        // Only one node — reuse deleteAtHead to keep logic DRY
        deleteAtHead();
        return;
    }
    // Walk to the second-last node
    Node* cursor = head_;
    while (cursor->next != tail_) {
        cursor = cursor->next;
    }
    delete tail_;
    cursor->next = nullptr;
    tail_        = cursor;
    --size_;
}


// ── deleteByValue ─────────────────────────────────────────────────────────────
template <typename T>
void LinkedList<T>::deleteByValue(const T& value) {
    if (isEmpty()) {
        throw std::out_of_range("deleteByValue(): list is empty.");
    }
    // Check head first
    if (head_->data == value) {
        deleteAtHead();
        return;
    }
    Node* cursor = head_;
    while (cursor->next != nullptr && cursor->next->data != value) {
        cursor = cursor->next;
    }
    if (cursor->next == nullptr) {
        throw std::out_of_range("deleteByValue(): value not found in list.");
    }
    Node* tmp    = cursor->next;
    cursor->next = tmp->next;
    if (tmp == tail_) {
        tail_ = cursor;         // deleted node was tail_; update tail_
    }
    delete tmp;
    --size_;
}


// ── isEmpty ───────────────────────────────────────────────────────────────────
template <typename T>
bool LinkedList<T>::isEmpty() const noexcept {
    return head_ == nullptr;
}


// ── getSize ───────────────────────────────────────────────────────────────────
template <typename T>
std::size_t LinkedList<T>::getSize() const noexcept {
    return size_;
}


// ── searchInList ──────────────────────────────────────────────────────────────
template <typename T>
bool LinkedList<T>::searchInList(const T& value) const noexcept {
    Node* cursor = head_;
    while (cursor != nullptr) {
        if (cursor->data == value) return true;
        cursor = cursor->next;
    }
    return false;
}


// ── print ─────────────────────────────────────────────────────────────────────
template <typename T>
void LinkedList<T>::print(std::ostream& os) const {
    if (isEmpty()) {
        os << "[ EMPTY ]\n";
        return;
    }
    Node* cursor = head_;
    os << "[ ";
    while (cursor != nullptr) {
        os << cursor->data;
        if (cursor->next != nullptr) os << " -> ";
        cursor = cursor->next;
    }
    os << " ]\n";
}

} // namespace algosmith

