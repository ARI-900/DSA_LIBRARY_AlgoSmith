
#include <algosmith/LinkedList.hpp>
#include <gtest/gtest.h>

using algosmith::LinkedList;

// ── State ─────────────────────────────────────────────────────────────────────

TEST(LinkedListTest, DefaultConstructorIsEmpty) {
    LinkedList<int> list;
    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(list.getSize(), 0u);
}

// ── insertAtHead ──────────────────────────────────────────────────────────────

TEST(LinkedListTest, InsertAtHeadSingleElement) {
    LinkedList<int> list;
    list.insertAtHead(5);
    EXPECT_EQ(list.getSize(), 1u);
    EXPECT_TRUE(list.searchInList(5));
}

TEST(LinkedListTest, InsertAtHeadMultiple) {
    LinkedList<int> list;
    list.insertAtHead(1);
    list.insertAtHead(2);
    list.insertAtHead(3);
    EXPECT_EQ(list.getSize(), 3u);
    EXPECT_TRUE(list.searchInList(1));
    EXPECT_TRUE(list.searchInList(2));
    EXPECT_TRUE(list.searchInList(3));
}

// ── insertAtTail ──────────────────────────────────────────────────────────────

TEST(LinkedListTest, InsertAtTailSingleElement) {
    LinkedList<int> list;
    list.insertAtTail(10);
    EXPECT_EQ(list.getSize(), 1u);
    EXPECT_TRUE(list.searchInList(10));
}

TEST(LinkedListTest, InsertAtTailMultiple) {
    LinkedList<int> list;
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.insertAtTail(3);
    EXPECT_EQ(list.getSize(), 3u);
}

// ── insertAtPosition ──────────────────────────────────────────────────────────

TEST(LinkedListTest, InsertAtPositionMiddle) {
    LinkedList<int> list;
    list.insertAtTail(1);
    list.insertAtTail(3);
    list.insertAtPosition(1, 2);    // [ 1 -> 2 -> 3 ]
    EXPECT_EQ(list.getSize(), 3u);
    EXPECT_TRUE(list.searchInList(2));
}

TEST(LinkedListTest, InsertAtPositionZeroActsAsHead) {
    LinkedList<int> list;
    list.insertAtTail(10);
    list.insertAtPosition(0, 99);   // [ 99 -> 10 ]
    EXPECT_EQ(list.getSize(), 2u);
    EXPECT_TRUE(list.searchInList(99));
}

TEST(LinkedListTest, InsertAtPositionBeyondSizeActsAsTail) {
    LinkedList<int> list;
    list.insertAtTail(1);
    list.insertAtPosition(999, 42); // [ 1 -> 42 ]
    EXPECT_EQ(list.getSize(), 2u);
    EXPECT_TRUE(list.searchInList(42));
}

// ── deleteAtHead ──────────────────────────────────────────────────────────────

TEST(LinkedListTest, DeleteAtHeadReducesSize) {
    LinkedList<int> list;
    list.insertAtHead(1);
    list.insertAtHead(2);
    list.deleteAtHead();
    EXPECT_EQ(list.getSize(), 1u);
}

TEST(LinkedListTest, DeleteAtHeadOnEmptyThrows) {
    LinkedList<int> list;
    EXPECT_THROW(list.deleteAtHead(), std::out_of_range);
}

TEST(LinkedListTest, DeleteAtHeadSingleElementLeavesEmpty) {
    LinkedList<int> list;
    list.insertAtHead(42);
    list.deleteAtHead();
    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(list.getSize(), 0u);
}

// ── deleteAtTail ──────────────────────────────────────────────────────────────

TEST(LinkedListTest, DeleteAtTailReducesSize) {
    LinkedList<int> list;
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.insertAtTail(3);
    list.deleteAtTail();
    EXPECT_EQ(list.getSize(), 2u);
    EXPECT_FALSE(list.searchInList(3));
}

TEST(LinkedListTest, DeleteAtTailOnEmptyThrows) {
    LinkedList<int> list;
    EXPECT_THROW(list.deleteAtTail(), std::out_of_range);
}

TEST(LinkedListTest, DeleteAtTailSingleElementLeavesEmpty) {
    LinkedList<int> list;
    list.insertAtTail(7);
    list.deleteAtTail();
    EXPECT_TRUE(list.isEmpty());
}

// ── deleteByValue ─────────────────────────────────────────────────────────────

TEST(LinkedListTest, DeleteByValueRemovesMiddleElement) {
    LinkedList<int> list;
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.insertAtTail(3);
    list.deleteByValue(2);
    EXPECT_FALSE(list.searchInList(2));
    EXPECT_EQ(list.getSize(), 2u);
}

TEST(LinkedListTest, DeleteByValueRemovesHead) {
    LinkedList<int> list;
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.deleteByValue(1);
    EXPECT_FALSE(list.searchInList(1));
    EXPECT_EQ(list.getSize(), 1u);
}

TEST(LinkedListTest, DeleteByValueRemovesTail) {
    LinkedList<int> list;
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.deleteByValue(2);
    EXPECT_FALSE(list.searchInList(2));
    EXPECT_EQ(list.getSize(), 1u);
}

TEST(LinkedListTest, DeleteByValueNotFoundThrows) {
    LinkedList<int> list;
    list.insertAtHead(1);
    EXPECT_THROW(list.deleteByValue(99), std::out_of_range);
}

TEST(LinkedListTest, DeleteByValueOnEmptyThrows) {
    LinkedList<int> list;
    EXPECT_THROW(list.deleteByValue(1), std::out_of_range);
}

// ── Search ────────────────────────────────────────────────────────────────────

TEST(LinkedListTest, SearchFindsExistingElement) {
    LinkedList<int> list;
    list.insertAtTail(7);
    EXPECT_TRUE(list.searchInList(7));
}

TEST(LinkedListTest, SearchMissesAbsentElement) {
    LinkedList<int> list;
    list.insertAtTail(7);
    EXPECT_FALSE(list.searchInList(99));
}

TEST(LinkedListTest, SearchOnEmptyListReturnsFalse) {
    LinkedList<int> list;
    EXPECT_FALSE(list.searchInList(1));
}

// ── Rule of Five ─────────────────────────────────────────────────────────────

TEST(LinkedListTest, CopyConstructorDeepCopies) {
    LinkedList<int> a;
    a.insertAtTail(1);
    a.insertAtTail(2);
    LinkedList<int> b(a);
    b.deleteAtHead();
    EXPECT_EQ(a.getSize(), 2u);     // original untouched
    EXPECT_EQ(b.getSize(), 1u);
}

TEST(LinkedListTest, CopyAssignmentDeepCopies) {
    LinkedList<int> a;
    a.insertAtTail(1);
    a.insertAtTail(2);
    LinkedList<int> b;
    b = a;
    b.deleteAtHead();
    EXPECT_EQ(a.getSize(), 2u);     // original untouched
    EXPECT_EQ(b.getSize(), 1u);
}

TEST(LinkedListTest, MoveConstructorTransfersOwnership) {
    LinkedList<int> a;
    a.insertAtTail(1);
    a.insertAtTail(2);
    LinkedList<int> b(std::move(a));
    EXPECT_TRUE(a.isEmpty());       // source is now empty
    EXPECT_EQ(b.getSize(), 2u);
}

TEST(LinkedListTest, MoveAssignmentTransfersOwnership) {
    LinkedList<int> a;
    a.insertAtTail(1);
    a.insertAtTail(2);
    LinkedList<int> b;
    b = std::move(a);
    EXPECT_TRUE(a.isEmpty());
    EXPECT_EQ(b.getSize(), 2u);
}

// ── Template Flexibility ──────────────────────────────────────────────────────

TEST(LinkedListTest, WorksWithDoubleType) {
    LinkedList<double> list;
    list.insertAtTail(3.14);
    list.insertAtTail(2.71);
    EXPECT_TRUE(list.searchInList(3.14));
    EXPECT_EQ(list.getSize(), 2u);
}

TEST(LinkedListTest, WorksWithStringType) {
    LinkedList<std::string> list;
    list.insertAtTail("hello");
    list.insertAtTail("world");
    EXPECT_TRUE(list.searchInList("hello"));
    EXPECT_FALSE(list.searchInList("missing"));
}

