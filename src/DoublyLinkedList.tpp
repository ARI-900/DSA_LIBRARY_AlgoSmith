
#pragma once

// Do NOT include this file directly.
// It is automatically included at the bottom of DoublyLinkedList.hpp.

namespace algosmith {

// ── Default Constructor ───────────────────────────────────────────────────────
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() noexcept
    : head_(nullptr), tail_(nullptr), size_(0) {}


// ── Destructor ────────────────────────────────────────────────────────────────
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}


// ── Copy Constructor ──────────────────────────────────────────────────────────
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& other)
    : head_(nullptr), tail_(nullptr), size_(0) {
    Node* cursor = other.head_;
    while (cursor != nullptr) {
        insertAtTail(cursor->data);
        cursor = cursor->next;
    }
}


// ── Move Constructor ──────────────────────────────────────────────────────────
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList&& other) noexcept
    : head_(std::exchange(other.head_, nullptr)),
      tail_(std::exchange(other.tail_, nullptr)),
      size_(std::exchange(other.size_, 0)) {}


// ── Copy Assignment ───────────────────────────────────────────────────────────
template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList& other) {
    if (this != &other) {
        DoublyLinkedList tmp(other);          // copy-and-swap idiom
        std::swap(head_, tmp.head_);
        std::swap(tail_, tmp.tail_);
        std::swap(size_, tmp.size_);
    }
    return *this;
}


// ── Move Assignment ───────────────────────────────────────────────────────────
template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList&& other) noexcept {
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
void DoublyLinkedList<T>::clear() noexcept {
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
void DoublyLinkedList<T>::insertAtHead(const T& value) {
    Node* newNode = new Node(value);
    if (head_ == nullptr) {
        head_ = newNode;
        tail_ = newNode;        // first node → both head_ and tail_ point here
    } else {
        newNode->next = head_;
        head_->prev   = newNode;
        head_         = newNode;
    }
    ++size_;
}


// ── insertAtTail ──────────────────────────────────────────────────────────────
// O(1) because of tail_ pointer
template <typename T>
void DoublyLinkedList<T>::insertAtTail(const T& value) {
    Node* newNode = new Node(value);
    if (head_ == nullptr) {
        head_ = newNode;
        tail_ = newNode;
    } else {
        newNode->prev = tail_;
        tail_->next   = newNode;
        tail_         = newNode;
    }
    ++size_;
}


// ── insertAtPosition ─────────────────────────────────────────────────────────
// pos = 0       → same as insertAtHead
// pos >= size_  → same as insertAtTail
template <typename T>
void DoublyLinkedList<T>::insertAtPosition(std::size_t pos, const T& value) {
    if (pos == 0 || isEmpty()) {
        insertAtHead(value);
        return;
    }
    if (pos >= size_) {
        insertAtTail(value);
        return;
    }
    // Walk to the node currently AT pos (we insert before it)
    Node* cursor = head_;
    for (std::size_t i = 0; i < pos; ++i) {
        cursor = cursor->next;
    }
    Node* newNode     = new Node(value);
    Node* prevNode    = cursor->prev;

    newNode->next  = cursor;
    newNode->prev  = prevNode;
    prevNode->next = newNode;
    cursor->prev   = newNode;

    ++size_;
}


// ── deleteAtHead ──────────────────────────────────────────────────────────────
template <typename T>
void DoublyLinkedList<T>::deleteAtHead() {
    if (isEmpty()) {
        throw std::out_of_range("deleteAtHead(): list is empty.");
    }
    Node* tmp = head_;
    head_     = head_->next;
    if (head_ != nullptr) {
        head_->prev = nullptr;  // new head has no predecessor
    } else {
        tail_ = nullptr;        // list is now empty; fix tail_ too
    }
    delete tmp;
    --size_;
}


// ── deleteAtTail ──────────────────────────────────────────────────────────────
// O(1) — doubly-linked list can step directly to prev node
template <typename T>
void DoublyLinkedList<T>::deleteAtTail() {
    if (isEmpty()) {
        throw std::out_of_range("deleteAtTail(): list is empty.");
    }
    if (size_ == 1) {
        // Only one node — reuse deleteAtHead to keep logic DRY
        deleteAtHead();
        return;
    }
    Node* tmp = tail_;
    tail_     = tail_->prev;
    tail_->next = nullptr;
    delete tmp;
    --size_;
}


// ── deleteByValue ─────────────────────────────────────────────────────────────
template <typename T>
void DoublyLinkedList<T>::deleteByValue(const T& value) {
    if (isEmpty()) {
        throw std::out_of_range("deleteByValue(): list is empty.");
    }
    // Walk forward to find the node
    Node* cursor = head_;
    while (cursor != nullptr && cursor->data != value) {
        cursor = cursor->next;
    }
    if (cursor == nullptr) {
        throw std::out_of_range("deleteByValue(): value not found in list.");
    }
    // Unlink cursor from its neighbours
    if (cursor->prev != nullptr) {
        cursor->prev->next = cursor->next;
    } else {
        head_ = cursor->next;   // deleted node was head_
    }
    if (cursor->next != nullptr) {
        cursor->next->prev = cursor->prev;
    } else {
        tail_ = cursor->prev;   // deleted node was tail_
    }
    delete cursor;
    --size_;
}


// ── isEmpty ───────────────────────────────────────────────────────────────────
template <typename T>
bool DoublyLinkedList<T>::isEmpty() const noexcept {
    return head_ == nullptr;
}


// ── getSize ───────────────────────────────────────────────────────────────────
template <typename T>
std::size_t DoublyLinkedList<T>::getSize() const noexcept {
    return size_;
}


// ── searchInList ──────────────────────────────────────────────────────────────
template <typename T>
bool DoublyLinkedList<T>::searchInList(const T& value) const noexcept {
    Node* cursor = head_;
    while (cursor != nullptr) {
        if (cursor->data == value) return true;
        cursor = cursor->next;
    }
    return false;
}


// ── print (forward) ──────────────────────────────────────────────────────────
template <typename T>
void DoublyLinkedList<T>::print(std::ostream& os) const {
    if (isEmpty()) {
        os << "[ EMPTY ]\n";
        return;
    }
    Node* cursor = head_;
    os << "[ ";
    while (cursor != nullptr) {
        os << cursor->data;
        if (cursor->next != nullptr) os << " <-> ";
        cursor = cursor->next;
    }
    os << " ]\n";
}


// ── printReverse (backward) ──────────────────────────────────────────────────
template <typename T>
void DoublyLinkedList<T>::printReverse(std::ostream& os) const {
    if (isEmpty()) {
        os << "[ EMPTY ]\n";
        return;
    }
    Node* cursor = tail_;
    os << "[ ";
    while (cursor != nullptr) {
        os << cursor->data;
        if (cursor->prev != nullptr) os << " <-> ";
        cursor = cursor->prev;
    }
    os << " ]\n";
}

} // namespace algosmith
