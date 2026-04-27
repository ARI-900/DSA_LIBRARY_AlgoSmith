
#pragma once

#include <cstddef>      // std::size_t
#include <stdexcept>    // std::out_of_range
#include <ostream>      // std::ostream
#include <iostream>     // std::cout (default arg in print)
#include <utility>      // std::move, std::exchange

namespace algosmith {

// ============================================================================
//  DoublyLinkedList<T>
//
//  Doubly-linked list with head_ AND tail_ pointers.
//  Every node carries both a next and a prev pointer, enabling O(1)
//  deletion at the tail and bidirectional traversal.
//
//  Complexity:
//      insertAtHead()      — O(1)
//      insertAtTail()      — O(1)
//      insertAtPosition()  — O(n)
//      deleteAtHead()      — O(1)
//      deleteAtTail()      — O(1)   ← prev pointer makes this possible
//      deleteByValue()     — O(n)
//      searchInList()      — O(n)
//      getSize()           — O(1)
// ============================================================================

template <typename T>
class DoublyLinkedList {

public:
    // ── Constructors / Destructor (Rule of Five) ──────────────────────────
    DoublyLinkedList() noexcept;                                     // Default
    DoublyLinkedList(const DoublyLinkedList& other);                 // Copy constructor
    DoublyLinkedList(DoublyLinkedList&& other) noexcept;             // Move constructor
    DoublyLinkedList& operator=(const DoublyLinkedList& other);      // Copy assignment
    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept;  // Move assignment
    ~DoublyLinkedList();                                             // Destructor (RAII)

    // ── Modifiers ─────────────────────────────────────────────────────────
    void insertAtHead(const T& value);
    void insertAtTail(const T& value);
    void insertAtPosition(std::size_t pos, const T& value);

    void deleteAtHead();                    // throws std::out_of_range if empty
    void deleteAtTail();                    // throws std::out_of_range if empty
    void deleteByValue(const T& value);     // throws std::out_of_range if not found

    // ── Accessors ─────────────────────────────────────────────────────────
    [[nodiscard]] bool        isEmpty()            const noexcept;
    [[nodiscard]] std::size_t getSize()            const noexcept;
    [[nodiscard]] bool        searchInList(const T& value) const noexcept;

    // ── Display ───────────────────────────────────────────────────────────
    void print(std::ostream& os = std::cout)         const; // forward: head → tail
    void printReverse(std::ostream& os = std::cout)  const; // reverse: tail → head

private:
    struct Node {
        T     data;
        Node* next;
        Node* prev;
        explicit Node(const T& val) : data(val), next(nullptr), prev(nullptr) {}
    };

    Node*       head_;
    Node*       tail_;
    std::size_t size_;

    void clear() noexcept; // Frees all nodes; used by destructor & assignments
};

} // namespace algosmith

// Template definitions must be visible at compile time
#include "../../src/DoublyLinkedList.tpp"
