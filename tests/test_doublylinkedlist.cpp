
#include <algosmith/DoublyLinkedList.hpp>
#include <gtest/gtest.h>

using algosmith::DoublyLinkedList;

// ── State ─────────────────────────────────────────────────────────────────────

TEST(DoublyLinkedListTest, DefaultConstructorIsEmpty) {
    DoublyLinkedList<int> list;
    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(list.getSize(), 0u);
}

// ── insertAtHead ──────────────────────────────────────────────────────────────

TEST(DoublyLinkedListTest, InsertAtHeadSingleElement) {
    DoublyLinkedList<int> list;
    list.insertAtHead(5);
    EXPECT_EQ(list.getSize(), 1u);
    EXPECT_TRUE(list.searchInList(5));
}

TEST(DoublyLinkedListTest, InsertAtHeadMultiple) {
    DoublyLinkedList<int> list;
    list.insertAtHead(1);
    list.insertAtHead(2);
    list.insertAtHead(3);
    EXPECT_EQ(list.getSize(), 3u);
    EXPECT_TRUE(list.searchInList(1));
    EXPECT_TRUE(list.searchInList(2));
    EXPECT_TRUE(list.searchInList(3));
}

// ── insertAtTail ──────────────────────────────────────────────────────────────

TEST(DoublyLinkedListTest, InsertAtTailSingleElement) {
    DoublyLinkedList<int> list;
    list.insertAtTail(10);
    EXPECT_EQ(list.getSize(), 1u);
    EXPECT_TRUE(list.searchInList(10));
}

TEST(DoublyLinkedListTest, InsertAtTailMultiple) {
    DoublyLinkedList<int> list;
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.insertAtTail(3);
    EXPECT_EQ(list.getSize(), 3u);
}

// ── insertAtPosition ──────────────────────────────────────────────────────────

TEST(DoublyLinkedListTest, InsertAtPositionMiddle) {
    DoublyLinkedList<int> list;
    list.insertAtTail(1);
    list.insertAtTail(3);
    list.insertAtPosition(1, 2);    // [ 1 <-> 2 <-> 3 ]
    EXPECT_EQ(list.getSize(), 3u);
    EXPECT_TRUE(list.searchInList(2));
}

TEST(DoublyLinkedListTest, InsertAtPositionZeroActsAsHead) {
    DoublyLinkedList<int> list;
    list.insertAtTail(10);
    list.insertAtPosition(0, 99);   // [ 99 <-> 10 ]
    EXPECT_EQ(list.getSize(), 2u);
    EXPECT_TRUE(list.searchInList(99));
}

TEST(DoublyLinkedListTest, InsertAtPositionBeyondSizeActsAsTail) {
    DoublyLinkedList<int> list;
    list.insertAtTail(1);
    list.insertAtPosition(999, 42); // [ 1 <-> 42 ]
    EXPECT_EQ(list.getSize(), 2u);
    EXPECT_TRUE(list.searchInList(42));
}

// ── deleteAtHead ──────────────────────────────────────────────────────────────

TEST(DoublyLinkedListTest, DeleteAtHeadReducesSize) {
    DoublyLinkedList<int> list;
    list.insertAtHead(1);
    list.insertAtHead(2);
    list.deleteAtHead();
    EXPECT_EQ(list.getSize(), 1u);
}

TEST(DoublyLinkedListTest, DeleteAtHeadOnEmptyThrows) {
    DoublyLinkedList<int> list;
    EXPECT_THROW(list.deleteAtHead(), std::out_of_range);
}

TEST(DoublyLinkedListTest, DeleteAtHeadSingleElementLeavesEmpty) {
    DoublyLinkedList<int> list;
    list.insertAtHead(42);
    list.deleteAtHead();
    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(list.getSize(), 0u);
}

TEST(DoublyLinkedListTest, DeleteAtHeadFixesPrevPointer) {
    DoublyLinkedList<int> list;
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.insertAtTail(3);
    list.deleteAtHead();            // new head should have prev == nullptr
    // If prev is not null this would cause issues in printReverse; test via size
    EXPECT_EQ(list.getSize(), 2u);
    EXPECT_FALSE(list.searchInList(1));
}

// ── deleteAtTail ──────────────────────────────────────────────────────────────

TEST(DoublyLinkedListTest, DeleteAtTailReducesSize) {
    DoublyLinkedList<int> list;
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.insertAtTail(3);
    list.deleteAtTail();
    EXPECT_EQ(list.getSize(), 2u);
    EXPECT_FALSE(list.searchInList(3));
}

TEST(DoublyLinkedListTest, DeleteAtTailOnEmptyThrows) {
    DoublyLinkedList<int> list;
    EXPECT_THROW(list.deleteAtTail(), std::out_of_range);
}

TEST(DoublyLinkedListTest, DeleteAtTailSingleElementLeavesEmpty) {
    DoublyLinkedList<int> list;
    list.insertAtTail(7);
    list.deleteAtTail();
    EXPECT_TRUE(list.isEmpty());
}

TEST(DoublyLinkedListTest, DeleteAtTailIsO1ViaPrevPointer) {
    // Verify the tail_ pointer moves to the correct prev node
    DoublyLinkedList<int> list;
    list.insertAtTail(10);
    list.insertAtTail(20);
    list.insertAtTail(30);
    list.deleteAtTail();            // removes 30; tail_ should now hold 20
    EXPECT_TRUE(list.searchInList(20));
    EXPECT_FALSE(list.searchInList(30));
}

// ── deleteByValue ─────────────────────────────────────────────────────────────

TEST(DoublyLinkedListTest, DeleteByValueRemovesMiddleElement) {
    DoublyLinkedList<int> list;
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.insertAtTail(3);
    list.deleteByValue(2);
    EXPECT_FALSE(list.searchInList(2));
    EXPECT_EQ(list.getSize(), 2u);
}

TEST(DoublyLinkedListTest, DeleteByValueRemovesHead) {
    DoublyLinkedList<int> list;
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.deleteByValue(1);
    EXPECT_FALSE(list.searchInList(1));
    EXPECT_EQ(list.getSize(), 1u);
}

TEST(DoublyLinkedListTest, DeleteByValueRemovesTail) {
    DoublyLinkedList<int> list;
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.deleteByValue(2);
    EXPECT_FALSE(list.searchInList(2));
    EXPECT_EQ(list.getSize(), 1u);
}

TEST(DoublyLinkedListTest, DeleteByValueNotFoundThrows) {
    DoublyLinkedList<int> list;
    list.insertAtHead(1);
    EXPECT_THROW(list.deleteByValue(99), std::out_of_range);
}

TEST(DoublyLinkedListTest, DeleteByValueOnEmptyThrows) {
    DoublyLinkedList<int> list;
    EXPECT_THROW(list.deleteByValue(1), std::out_of_range);
}

// ── Search ────────────────────────────────────────────────────────────────────

TEST(DoublyLinkedListTest, SearchFindsExistingElement) {
    DoublyLinkedList<int> list;
    list.insertAtTail(7);
    EXPECT_TRUE(list.searchInList(7));
}

TEST(DoublyLinkedListTest, SearchMissesAbsentElement) {
    DoublyLinkedList<int> list;
    list.insertAtTail(7);
    EXPECT_FALSE(list.searchInList(99));
}

TEST(DoublyLinkedListTest, SearchOnEmptyListReturnsFalse) {
    DoublyLinkedList<int> list;
    EXPECT_FALSE(list.searchInList(1));
}

// ── Rule of Five ──────────────────────────────────────────────────────────────

TEST(DoublyLinkedListTest, CopyConstructorDeepCopies) {
    DoublyLinkedList<int> a;
    a.insertAtTail(1);
    a.insertAtTail(2);
    DoublyLinkedList<int> b(a);
    b.deleteAtHead();
    EXPECT_EQ(a.getSize(), 2u);     // original untouched
    EXPECT_EQ(b.getSize(), 1u);
}

TEST(DoublyLinkedListTest, CopyAssignmentDeepCopies) {
    DoublyLinkedList<int> a;
    a.insertAtTail(1);
    a.insertAtTail(2);
    DoublyLinkedList<int> b;
    b = a;
    b.deleteAtHead();
    EXPECT_EQ(a.getSize(), 2u);     // original untouched
    EXPECT_EQ(b.getSize(), 1u);
}

TEST(DoublyLinkedListTest, MoveConstructorTransfersOwnership) {
    DoublyLinkedList<int> a;
    a.insertAtTail(1);
    a.insertAtTail(2);
    DoublyLinkedList<int> b(std::move(a));
    EXPECT_TRUE(a.isEmpty());       // source is now empty
    EXPECT_EQ(b.getSize(), 2u);
}

TEST(DoublyLinkedListTest, MoveAssignmentTransfersOwnership) {
    DoublyLinkedList<int> a;
    a.insertAtTail(1);
    a.insertAtTail(2);
    DoublyLinkedList<int> b;
    b = std::move(a);
    EXPECT_TRUE(a.isEmpty());
    EXPECT_EQ(b.getSize(), 2u);
}

// ── Template Flexibility ──────────────────────────────────────────────────────

TEST(DoublyLinkedListTest, WorksWithDoubleType) {
    DoublyLinkedList<double> list;
    list.insertAtTail(3.14);
    list.insertAtTail(2.71);
    EXPECT_TRUE(list.searchInList(3.14));
    EXPECT_EQ(list.getSize(), 2u);
}

TEST(DoublyLinkedListTest, WorksWithStringType) {
    DoublyLinkedList<std::string> list;
    list.insertAtTail("hello");
    list.insertAtTail("world");
    EXPECT_TRUE(list.searchInList("hello"));
    EXPECT_FALSE(list.searchInList("missing"));
}
