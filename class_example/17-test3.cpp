#pragma once
#include <iostream>
#include <memory>
using namespace std;

// A Sample class with prints in constructor and destructor, so that we can track when the memory
// is allocated and deallocated

class Sample {
public:
	Sample() { cout << "Sample Constructor" << endl; }
	~Sample() { cout << "Sample Destructor" << endl; }
	void publicFn() { cout << "This is public function of class" << endl; }
};

// Test to confirm that unique pointers do release memory without explicitely calling
// the delete
void  TestUniquePtr_ReleaseMemory() {
	unique_ptr<Sample> up(new Sample{});
	up->publicFn();
	return;
}

// Test to confirm that unique pointers doesn't transfer the ownership
void TestUniquePtr_NoOwnershipTrasfer() {
	unique_ptr<Sample> up(new Sample);
	// The line below will generate compiler error
	//unique_ptr<Sample> upTrans = up;
	return;
}

// Test to confirm that unique pointers ownership can be transferred using std::move
void TestUniquePtr_MoveOwnershipTrasfer() {
	unique_ptr<Sample> up(new Sample);
	unique_ptr<Sample> upTrans = std::move(up);
	return;
}

// A helper function which returns a unique pointer
unique_ptr<Sample> AFunc() {
	cout << "Enter AFunc" << endl;
	unique_ptr<Sample> up(new Sample{});
	cout << "Exit AFunc" << endl;
	return up;
}

// Test to confirm that unique pointers can be returened from a function without
// sharing the ownership
void TestUniquePtr_ReturnFunction() {
	cout << "Enter TestUniquePtr_ReturnFunction" << endl;
	unique_ptr<Sample> retSp = AFunc();
	cout << "Exit TestUniquePtr_ReturnFunction" << endl;
	return;
}
// Test to confirm that unique pointers does free up the memory if no one is willing to take
// the ownership
void TestUniquePtr_ReturnNoOwnership() {
	cout << "Enter TestUniquePtr_ReturnNoOwnership" << endl;
	AFunc();
	cout << "Exit TestUniquePtr_ReturnNoOwnership" << endl;
	return;
}

// Test for using inbuilt Make_Unique to create a unique pointer
// Available only in C++14 onwards
void TestUniquePtr_MakeUnique() {
	unique_ptr<Sample> sp = make_unique<Sample>();
	return;
}

int main() {
	TestUniquePtr_ReleaseMemory();
	cout << "------------------------------------------------" << endl;
	TestUniquePtr_MoveOwnershipTrasfer();
	cout << "------------------------------------------------" << endl;
	TestUniquePtr_ReturnFunction();
	cout << "------------------------------------------------" << endl;
	TestUniquePtr_ReturnNoOwnership();
	cout << "------------------------------------------------" << endl;
	TestUniquePtr_MakeUnique();
	return 0;
}