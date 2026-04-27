
#include <algosmith/AlgoSmith.hpp>
#include <iostream>

int main() {

    // ── Basic usage ───────────────────────────────────────────────────────
    algosmith::DoublyLinkedList<int> list;

    list.insertAtHead(10);
    list.insertAtHead(5);
    list.insertAtTail(20);
    list.insertAtTail(30);
    list.insertAtPosition(2, 99);   // Insert 99 at index 2

    std::cout << "After insertions (forward):  ";
    list.print();

    std::cout << "After insertions (reverse):  ";
    list.printReverse();

    std::cout << "Size: " << list.getSize() << "\n";

    // ── Search ────────────────────────────────────────────────────────────
    std::cout << "Search 99:  " << (list.searchInList(99)  ? "found" : "not found") << "\n";
    std::cout << "Search 999: " << (list.searchInList(999) ? "found" : "not found") << "\n";

    // ── Delete ────────────────────────────────────────────────────────────
    list.deleteAtHead();
    std::cout << "After deleteAtHead():        ";
    list.print();

    list.deleteAtTail();            // O(1) — doubly-linked!
    std::cout << "After deleteAtTail() [O(1)]: ";
    list.print();

    list.deleteByValue(99);
    std::cout << "After deleteByValue(99):     ";
    list.print();

    // ── Exception handling demo ───────────────────────────────────────────
    algosmith::DoublyLinkedList<int> emptyList;
    try {
        emptyList.deleteAtHead();
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << "\n";
    }

    // ── Rule of Five demo ─────────────────────────────────────────────────
    algosmith::DoublyLinkedList<int> original;
    original.insertAtTail(1);
    original.insertAtTail(2);
    original.insertAtTail(3);

    algosmith::DoublyLinkedList<int> copied  = original;            // copy constructor
    algosmith::DoublyLinkedList<int> moved   = std::move(original); // move constructor

    std::cout << "Copied list:             ";  copied.print();
    std::cout << "Moved list:              ";  moved.print();
    std::cout << "Original after move:     ";  original.print(); // should be EMPTY

    return 0;
}
