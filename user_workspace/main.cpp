#include <iostream>
#include<vector>
#include<map>
#include<algorithm>


#include <algosmith/AlgoSmith.hpp>
using namespace std;

// Uncomment the line below to use the AlgoSmith library
// #include <algosmith/AlgoSmith.hpp>

int main() {
    cout << "========================================\n";
    cout << "        Welcome to User Workspace!      \n";
    cout << "========================================\n\n";

    cout << "Write your code here.\n";
    cout << "To use the AlgoSmith library, uncomment the include statement above,\n";
    cout << "and also uncomment the 'target_link_libraries' line in the CMakeLists.txt file.\n" << endl;


    map<int,int> mp;
    vector<int> arr = {3,2,1,5,4};


    cout << "Before sort: ";
    for(int it : arr) {
        cout << it << "   " ;
    }cout <<endl;


    sort(arr.begin(), arr.end());


    cout << "After sort: ";
    for(int it : arr) {
        cout << it << "   " ;
    }cout <<endl;



    vector<int> arr2 = {3,5,4,33,3,2,2,4,1,4};

    for(int it : arr2) {
        mp[it]++;
    }

    cout << "Map Value: " << endl;
    for(auto it : mp) {
        cout << "KEY: " << it.first << " || VALUE: " << it.second << endl;
    }



    // using my library:
    algosmith::LinkedList<int> myList;
    algosmith::DoublyLinkedList<int> myDll;


    myList.insertAtHead(10);
    myList.insertAtHead(5);
    myList.insertAtTail(20); 
    // 5 -> 10  -> 20 -> X

    myList.print();



    return 0;
}
