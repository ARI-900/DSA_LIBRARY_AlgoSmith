
#pragma once

#include <cstddef>      // std::size_t
#include <stdexcept>    // std::out_of_range
#include <ostream>      // std::ostream
#include <iostream>     // std::cout (default arg in print)
#include <utility>      // std::move, std::exchange

namespace algosmith {

// ============================================================================
//  LinkedList<T>
//
//  Singly-linked list with head_ AND tail_ pointers.
//
//  Complexity:
//      insertAtHead()      — O(1)
//      insertAtTail()      — O(1)   ← tail_ pointer makes this possible
//      insertAtPosition()  — O(n)
//      deleteAtHead()      — O(1)
//      deleteAtTail()      — O(n)   (singly-linked; must walk to second-last)
//      deleteByValue()     — O(n)
//      searchInList()      — O(n)
//      getSize()           — O(1)
// ============================================================================

template <typename T>
class LinkedList {

public:
    // ── Constructors / Destructor (Rule of Five) ──────────────────────────
    LinkedList() noexcept;                               // Default
    LinkedList(const LinkedList& other);                 // Copy constructor
    LinkedList(LinkedList&& other) noexcept;             // Move constructor
    LinkedList& operator=(const LinkedList& other);      // Copy assignment
    LinkedList& operator=(LinkedList&& other) noexcept;  // Move assignment
    ~LinkedList();                                       // Destructor (RAII)

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
    void print(std::ostream& os = std::cout) const;

private:
    struct Node {
        T     data;
        Node* next;
        explicit Node(const T& val) : data(val), next(nullptr) {}
    };

    Node*       head_;
    Node*       tail_;   // O(1) insertAtTail
    std::size_t size_;

    void clear() noexcept; // Frees all nodes; used by destructor & assignments
};

} // namespace algosmith

// Template definitions must be visible at compile time
#include "../../src/LinkedList.tpp"

