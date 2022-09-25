#include "../src/main.cpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
/*
	To check output (At the Project1 directory):
		g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
*/

TEST_CASE("AVL Insertion Test Height", "[flag]")
{
	MyAVLTree *tree = nullptr;
	// Seeing if height stays consistent at large ordered values (testing balancing)
	for (int i = 0; i < 1000; i++)
		tree = tree->insert(Student("John Doe", to_string(10000000 + i)), tree);
	int expectedOutput = 10;
	int actualOutput = tree->getTreeHeight(tree);
	REQUIRE(actualOutput == expectedOutput);

	MyAVLTree *tree2 = nullptr;
	// Testing 50 randomly generated values
	vector<int> treeInput = {29763044, 11406719, 12750908, 23465203, 44533346, 43721282, 36338810, 46203822, 21095224, 12657334, 44479390, 32331876, 33042067, 35036064, 28303171, 17146038, 32667299, 32608767, 14778325, 15889664, 11752253, 10510539, 17072558, 34567884, 17392816, 14479701, 43242916, 35191572, 45775379, 24346701, 11025015, 33804662, 35573427, 49153162, 35072617, 42555913, 47934038, 31900538, 38525469, 10111166, 26122962, 41781020, 39069724, 16344420, 10773996, 42056004, 42353930, 25986104, 25248052, 45578394};
	for (int i = 0; i < treeInput.size(); i++)
		tree2 = tree2->insert(Student("Jane Doe", to_string(treeInput[i])), tree2);
	int expectedOutput2 = 7;
	int actualOutput2 = tree2->getTreeHeight(tree2);
	REQUIRE(actualOutput2 == expectedOutput2);

	MyAVLTree *tree3 = nullptr;
	// Testing empty tree
	int expectedOutput3 = 0;
	int actualOutput3 = tree3->getTreeHeight(tree3);
	REQUIRE(actualOutput3 == expectedOutput3);

	MyAVLTree *tree4 = nullptr;
	tree4 = tree4->insert(Student("Loner", "31415926"), tree4);
	// Testing single root
	int expectedOutput4 = 1;
	int actualOutput4 = tree3->getTreeHeight(tree4);
	REQUIRE(actualOutput4 == expectedOutput4);
}
TEST_CASE("AVL Removal Test", "[flag]")
{
	MyAVLTree *tree = nullptr;
	// Testing 50 randomly generated values (same values from test 1)
	vector<int> treeInput = {29763044, 11406719, 12750908, 23465203, 44533346, 43721282, 36338810, 46203822, 21095224, 12657334, 44479390, 32331876, 33042067, 35036064, 28303171, 17146038, 32667299, 32608767, 14778325, 15889664, 11752253, 10510539, 17072558, 34567884, 17392816, 14479701, 43242916, 35191572, 45775379, 24346701, 11025015, 33804662, 35573427, 49153162, 35072617, 42555913, 47934038, 31900538, 38525469, 10111166, 26122962, 41781020, 39069724, 16344420, 10773996, 42056004, 42353930, 25986104, 25248052, 45578394};
	for (int i = 0; i < treeInput.size(); i++)
		tree = tree->insert(Student("Jane Doe", to_string(treeInput[i])), tree);
	tree = tree->remove("14778325", tree);
	tree = tree->remove("41781020", tree);
	tree = tree->remove("34567884", tree);

	vector<Student> inOrderStudents;
	tree->setInOrder(inOrderStudents, tree);
	vector<int> expectedOutput = {10111166, 10510539, 10773996, 11025015, 11406719, 11752253, 12657334, 12750908, 14479701, 15889664, 16344420, 17072558, 17146038, 17392816, 21095224, 23465203, 24346701, 25248052, 25986104, 26122962, 28303171, 29763044, 31900538, 32331876, 32608767, 32667299, 33042067, 33804662, 35036064, 35072617, 35191572, 35573427, 36338810, 38525469, 39069724, 42056004, 42353930, 42555913, 43242916, 43721282, 44479390, 44533346, 45578394, 45775379, 46203822, 47934038, 49153162};
	vector<int> actualOutput;
	for (int i = 0; i < inOrderStudents.size(); i++)
		actualOutput.push_back(stoi(inOrderStudents[i].id));
	REQUIRE(expectedOutput.size() == actualOutput.size());
	REQUIRE(expectedOutput == actualOutput);

	// Testing when all nodes get removed
	MyAVLTree *tree2 = nullptr;
	tree2 = tree2->insert(Student("Jerry", "00000001"), tree2);
	tree2 = tree2->insert(Student("Gerry", "00000003"), tree2);
	tree2 = tree2->insert(Student("Goerry", "00000002"), tree2);
	tree2 = tree2->remove("00000002", tree2);
	tree2 = tree2->remove("00000003", tree2);
	tree2 = tree2->remove("00000001", tree2);

	int expectedOutput2 = 0;
	int actualOutput2 = tree2->getTreeHeight(tree2);
	REQUIRE(expectedOutput2 == actualOutput2);
}
TEST_CASE("AVL Removal in Order Test", "[flag]")
{
	MyAVLTree *tree = nullptr;
	// Testing if multiple remove in orders give accurate results
	vector<int> treeInput = {20000001, 10000001, 00000006, 00000003, 00200001, 00000031, 00000040};
	for (int i = 0; i < treeInput.size(); i++)
		tree = tree->insert(Student("George", to_string(treeInput[i])), tree);
	tree = tree->removeInOrder(6, tree);
	tree = tree->removeInOrder(3, tree);
	tree = tree->removeInOrder(0, tree);
	tree = tree->removeInOrder(2, tree);
	vector<int> expectedOutput = {00000006, 00000031, 10000001};
	vector<Student> inOrderStudents;
	vector<int> actualOutput;
	tree->setInOrder(inOrderStudents, tree);
	for (int i = 0; i < inOrderStudents.size(); i++)
		actualOutput.push_back(stoi(inOrderStudents[i].id));
	REQUIRE(expectedOutput.size() == actualOutput.size());
	REQUIRE(expectedOutput == actualOutput);
}

TEST_CASE("AVL Pre Order Test", "[flag]")
{
	MyAVLTree *tree = nullptr;
	// Testing if preorder holds with multiple removals
	tree = tree->insert(Student("Jerry", "00000014"), tree);
	tree = tree->insert(Student("Gerry", "00000027"), tree);
	tree = tree->insert(Student("Harry", "00000032"), tree);
	tree = tree->insert(Student("Barry", "00000012"), tree);
	tree = tree->insert(Student("Larry", "00000002"), tree);
	tree = tree->insert(Student("Kerry", "00000007"), tree);
	tree = tree->remove("00000032", tree);
	tree = tree->removeInOrder(0, tree);

	vector<int> expectedOutput = {12, 7, 27, 14};
	vector<int> actualOutput;
	vector<Student> preOrderedStudents;
	tree->setPreOrder(preOrderedStudents, tree);
	for (int i = 0; i < preOrderedStudents.size(); i++)
		actualOutput.push_back(stoi(preOrderedStudents[i].id));
	REQUIRE(expectedOutput.size() == actualOutput.size());
	REQUIRE(expectedOutput == actualOutput);
}

TEST_CASE("AVL Post Order Test", "[flag]")
{
	MyAVLTree *tree = nullptr;
	// Testing if preorder holds with multiple removals
	tree = tree->insert(Student("Apple", "00001014"), tree);
	tree = tree->insert(Student("Pear", "00000227"), tree);
	tree = tree->insert(Student("Banana", "00000062"), tree);
	tree = tree->insert(Student("Grape", "00000105"), tree);
	tree = tree->insert(Student("Orange", "00000002"), tree);
	tree = tree->insert(Student("Lemon", "00000001"), tree);
	tree = tree->insert(Student("Melon", "00000007"), tree);
	tree = tree->insert(Student("Pineapple", "00000005"), tree);
	tree = tree->removeInOrder(0, tree);
	tree = tree->removeInOrder(2, tree);

	vector<int> expectedOutput = {5, 2, 105, 1014, 227, 62};
	vector<int> actualOutput;
	vector<Student> postOrderedStudents;
	tree->setPostOrder(postOrderedStudents, tree);
	for (int i = 0; i < postOrderedStudents.size(); i++)
		actualOutput.push_back(stoi(postOrderedStudents[i].id));
	REQUIRE(expectedOutput.size() == actualOutput.size());
	REQUIRE(expectedOutput == actualOutput);
}
