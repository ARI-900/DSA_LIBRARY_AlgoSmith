
#include <algosmith/AlgoSmith.hpp>
#include <iostream>

int main() {

    // ── Basic insertions ──────────────────────────────────────────────────
    //  Inserting: 50, 30, 70, 20, 40, 60, 80
    //  Tree shape:
    //            50
    //           /  \
    //          30   70
    //         / \  / \
    //        20 40 60 80

    algosmith::BinarySearchTree<int> bst;

    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    // Duplicate — should be silently ignored
    bst.insert(50);

    std::cout << "Size (expected 7):          " << bst.getSize()   << "\n";
    std::cout << "Height (expected 3):         " << bst.getHeight() << "\n";

    // ── Traversals ────────────────────────────────────────────────────────
    std::cout << "In-Order    (sorted):        ";  bst.printInOrder();
    std::cout << "Pre-Order   (root first):    ";  bst.printPreOrder();
    std::cout << "Post-Order  (root last):     ";  bst.printPostOrder();
    std::cout << "Level-Order (BFS):           ";  bst.printLevelOrder();

    // ── Min / Max ─────────────────────────────────────────────────────────
    std::cout << "Min (expected 20):           " << bst.findMin() << "\n";
    std::cout << "Max (expected 80):           " << bst.findMax() << "\n";

    // ── Search ────────────────────────────────────────────────────────────
    std::cout << "Search 40  (found):          " << (bst.search(40)  ? "found" : "not found") << "\n";
    std::cout << "Search 999 (not found):      " << (bst.search(999) ? "found" : "not found") << "\n";

    // ── Remove: leaf node (80) ────────────────────────────────────────────
    bst.remove(80);
    std::cout << "\nAfter remove(80) [leaf]:     ";  bst.printInOrder();

    // ── Remove: one-child node (30 now only has 40 after 20 gone) ─────────
    bst.remove(20);                             // now 30 has single child 40
    bst.remove(30);                             // one-child case
    std::cout << "After remove(20) & (30):     ";  bst.printInOrder();

    // ── Remove: two-children node (50 = root) ────────────────────────────
    bst.remove(50);                             // two-child root → successor is 60
    std::cout << "After remove(50) [2 child]:  ";  bst.printInOrder();

    // ── Exception handling ────────────────────────────────────────────────
    try {
        bst.remove(999);
    } catch (const std::out_of_range& e) {
        std::cout << "\nCaught: " << e.what() << "\n";
    }

    algosmith::BinarySearchTree<int> emptyBst;
    try {
        (void)emptyBst.findMin();
    } catch (const std::out_of_range& e) {
        std::cout << "Caught: " << e.what() << "\n";
    }

    // ── deleteTree ────────────────────────────────────────────────────────
    bst.deleteTree();
    std::cout << "\nAfter deleteTree():          ";  bst.printInOrder();
    std::cout << "Size (expected 0):           " << bst.getSize() << "\n";

    // ── Rule of Five demo ─────────────────────────────────────────────────
    algosmith::BinarySearchTree<int> original;
    original.insert(10);
    original.insert(5);
    original.insert(15);

    algosmith::BinarySearchTree<int> copied = original;             // copy constructor
    algosmith::BinarySearchTree<int> moved  = std::move(original);  // move constructor

    std::cout << "\nCopied BST In-Order:         ";  copied.printInOrder();
    std::cout << "Moved BST In-Order:          ";  moved.printInOrder();
    std::cout << "Original after move:         ";  original.printInOrder(); // EMPTY

    return 0;
}
