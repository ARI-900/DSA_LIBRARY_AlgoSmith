
#include <algosmith/BinarySearchTree.hpp>
#include <gtest/gtest.h>
#include <sstream>

using algosmith::BinarySearchTree;

// ── State ─────────────────────────────────────────────────────────────────────

TEST(BSTTest, DefaultConstructorIsEmpty) {
    BinarySearchTree<int> bst;
    EXPECT_TRUE(bst.isEmpty());
    EXPECT_EQ(bst.getSize(), 0u);
    EXPECT_EQ(bst.getHeight(), 0u);
}

// ── insert ────────────────────────────────────────────────────────────────────

TEST(BSTTest, InsertSingleElement) {
    BinarySearchTree<int> bst;
    bst.insert(10);
    EXPECT_EQ(bst.getSize(), 1u);
    EXPECT_TRUE(bst.search(10));
}

TEST(BSTTest, InsertMultipleElements) {
    BinarySearchTree<int> bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    EXPECT_EQ(bst.getSize(), 3u);
    EXPECT_TRUE(bst.search(50));
    EXPECT_TRUE(bst.search(30));
    EXPECT_TRUE(bst.search(70));
}

TEST(BSTTest, InsertDuplicateIsIgnored) {
    BinarySearchTree<int> bst;
    bst.insert(10);
    bst.insert(10);
    bst.insert(10);
    EXPECT_EQ(bst.getSize(), 1u);
}

// ── remove ────────────────────────────────────────────────────────────────────

TEST(BSTTest, RemoveLeafNode) {
    BinarySearchTree<int> bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.remove(30);     // leaf
    EXPECT_FALSE(bst.search(30));
    EXPECT_EQ(bst.getSize(), 2u);
}

TEST(BSTTest, RemoveNodeWithOneChild) {
    BinarySearchTree<int> bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(20);     // 30 has one left child (20)
    bst.remove(30);
    EXPECT_FALSE(bst.search(30));
    EXPECT_TRUE(bst.search(20));
    EXPECT_EQ(bst.getSize(), 2u);
}

TEST(BSTTest, RemoveNodeWithTwoChildren) {
    BinarySearchTree<int> bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(60);
    bst.insert(80);
    bst.remove(70);     // 70 has two children (60, 80)
    EXPECT_FALSE(bst.search(70));
    EXPECT_TRUE(bst.search(60));
    EXPECT_TRUE(bst.search(80));
    EXPECT_EQ(bst.getSize(), 4u);
}

TEST(BSTTest, RemoveRoot) {
    BinarySearchTree<int> bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.remove(50);     // root with two children
    EXPECT_FALSE(bst.search(50));
    EXPECT_TRUE(bst.search(30));
    EXPECT_TRUE(bst.search(70));
    EXPECT_EQ(bst.getSize(), 2u);
}

TEST(BSTTest, RemoveOnlyElement) {
    BinarySearchTree<int> bst;
    bst.insert(99);
    bst.remove(99);
    EXPECT_TRUE(bst.isEmpty());
    EXPECT_EQ(bst.getSize(), 0u);
}

TEST(BSTTest, RemoveNotFoundThrows) {
    BinarySearchTree<int> bst;
    bst.insert(10);
    EXPECT_THROW(bst.remove(999), std::out_of_range);
}

TEST(BSTTest, RemoveFromEmptyThrows) {
    BinarySearchTree<int> bst;
    EXPECT_THROW(bst.remove(1), std::out_of_range);
}

// ── search ────────────────────────────────────────────────────────────────────

TEST(BSTTest, SearchFindsExistingElement) {
    BinarySearchTree<int> bst;
    bst.insert(50);
    bst.insert(30);
    EXPECT_TRUE(bst.search(30));
}

TEST(BSTTest, SearchMissesAbsentElement) {
    BinarySearchTree<int> bst;
    bst.insert(50);
    EXPECT_FALSE(bst.search(999));
}

TEST(BSTTest, SearchOnEmptyReturnsFalse) {
    BinarySearchTree<int> bst;
    EXPECT_FALSE(bst.search(1));
}

// ── findMin / findMax ─────────────────────────────────────────────────────────

TEST(BSTTest, FindMinReturnsSmallest) {
    BinarySearchTree<int> bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    EXPECT_EQ(bst.findMin(), 20);
}

TEST(BSTTest, FindMaxReturnsLargest) {
    BinarySearchTree<int> bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(80);
    EXPECT_EQ(bst.findMax(), 80);
}

TEST(BSTTest, FindMinOnEmptyThrows) {
    BinarySearchTree<int> bst;
    EXPECT_THROW(bst.findMin(), std::out_of_range);
}

TEST(BSTTest, FindMaxOnEmptyThrows) {
    BinarySearchTree<int> bst;
    EXPECT_THROW(bst.findMax(), std::out_of_range);
}

TEST(BSTTest, FindMinMaxSingleElement) {
    BinarySearchTree<int> bst;
    bst.insert(42);
    EXPECT_EQ(bst.findMin(), 42);
    EXPECT_EQ(bst.findMax(), 42);
}

// ── getHeight ─────────────────────────────────────────────────────────────────

TEST(BSTTest, HeightOfEmptyTreeIsZero) {
    BinarySearchTree<int> bst;
    EXPECT_EQ(bst.getHeight(), 0u);
}

TEST(BSTTest, HeightOfSingleNodeIsOne) {
    BinarySearchTree<int> bst;
    bst.insert(10);
    EXPECT_EQ(bst.getHeight(), 1u);
}

TEST(BSTTest, HeightOfBalancedTree) {
    BinarySearchTree<int> bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);
    EXPECT_EQ(bst.getHeight(), 3u);
}

// ── deleteTree ────────────────────────────────────────────────────────────────

TEST(BSTTest, DeleteTreeMakesEmpty) {
    BinarySearchTree<int> bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.deleteTree();
    EXPECT_TRUE(bst.isEmpty());
    EXPECT_EQ(bst.getSize(), 0u);
    EXPECT_EQ(bst.getHeight(), 0u);
}

TEST(BSTTest, DeleteTreeThenReinsert) {
    BinarySearchTree<int> bst;
    bst.insert(10);
    bst.insert(20);
    bst.deleteTree();
    bst.insert(99);
    EXPECT_EQ(bst.getSize(), 1u);
    EXPECT_TRUE(bst.search(99));
}

// ── Traversals (output verification) ──────────────────────────────────────────

TEST(BSTTest, InOrderProducesSortedOutput) {
    BinarySearchTree<int> bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    std::ostringstream oss;
    bst.printInOrder(oss);
    EXPECT_EQ(oss.str(), "[ 20 30 40 50 70 ]\n");
}

TEST(BSTTest, PreOrderOutput) {
    BinarySearchTree<int> bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    std::ostringstream oss;
    bst.printPreOrder(oss);
    EXPECT_EQ(oss.str(), "[ 50 30 70 ]\n");
}

TEST(BSTTest, PostOrderOutput) {
    BinarySearchTree<int> bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    std::ostringstream oss;
    bst.printPostOrder(oss);
    EXPECT_EQ(oss.str(), "[ 30 70 50 ]\n");
}

TEST(BSTTest, LevelOrderOutput) {
    BinarySearchTree<int> bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    std::ostringstream oss;
    bst.printLevelOrder(oss);
    EXPECT_EQ(oss.str(), "[ 50 30 70 20 40 ]\n");
}

TEST(BSTTest, TraversalOnEmptyTree) {
    BinarySearchTree<int> bst;
    std::ostringstream oss;
    bst.printInOrder(oss);
    EXPECT_EQ(oss.str(), "[ EMPTY ]\n");
}

// ── Rule of Five ──────────────────────────────────────────────────────────────

TEST(BSTTest, CopyConstructorDeepCopies) {
    BinarySearchTree<int> a;
    a.insert(10);
    a.insert(5);
    a.insert(15);
    BinarySearchTree<int> b(a);
    b.remove(10);
    EXPECT_EQ(a.getSize(), 3u);     // original untouched
    EXPECT_EQ(b.getSize(), 2u);
}

TEST(BSTTest, CopyAssignmentDeepCopies) {
    BinarySearchTree<int> a;
    a.insert(10);
    a.insert(5);
    BinarySearchTree<int> b;
    b = a;
    b.remove(5);
    EXPECT_EQ(a.getSize(), 2u);     // original untouched
    EXPECT_EQ(b.getSize(), 1u);
}

TEST(BSTTest, MoveConstructorTransfersOwnership) {
    BinarySearchTree<int> a;
    a.insert(10);
    a.insert(5);
    BinarySearchTree<int> b(std::move(a));
    EXPECT_TRUE(a.isEmpty());       // source is now empty
    EXPECT_EQ(b.getSize(), 2u);
}

TEST(BSTTest, MoveAssignmentTransfersOwnership) {
    BinarySearchTree<int> a;
    a.insert(10);
    a.insert(5);
    BinarySearchTree<int> b;
    b = std::move(a);
    EXPECT_TRUE(a.isEmpty());
    EXPECT_EQ(b.getSize(), 2u);
}

// ── Template Flexibility ──────────────────────────────────────────────────────

TEST(BSTTest, WorksWithDoubleType) {
    BinarySearchTree<double> bst;
    bst.insert(3.14);
    bst.insert(2.71);
    bst.insert(1.41);
    EXPECT_TRUE(bst.search(3.14));
    EXPECT_EQ(bst.getSize(), 3u);
    EXPECT_EQ(bst.findMin(), 1.41);
}

TEST(BSTTest, WorksWithStringType) {
    BinarySearchTree<std::string> bst;
    bst.insert("banana");
    bst.insert("apple");
    bst.insert("cherry");
    EXPECT_TRUE(bst.search("banana"));
    EXPECT_FALSE(bst.search("missing"));
    EXPECT_EQ(bst.findMin(), "apple");
    EXPECT_EQ(bst.findMax(), "cherry");
}
