#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

// Student Struct and Tree class
struct Student
{
	string name;
	string id;
	Student(string x, string y) : name(x), id(y) {}
};
class MyAVLTree
{
	Student student;
	MyAVLTree *left;
	MyAVLTree *right;

public:
	MyAVLTree(Student x) : student(x), left(nullptr), right(nullptr) {}
	~MyAVLTree();
	// Height functions
	int getTreeHeight(MyAVLTree *root);
	void printLevelCount(MyAVLTree *root);

	// Rotations and balance functions
	void leftLeftRotation(MyAVLTree *root);
	void rightRightRotation(MyAVLTree *root);
	void rightLeftRotation(MyAVLTree *root);
	void leftRightRotation(MyAVLTree *root);
	void balanceTree(MyAVLTree *root);

	// Insertion and removal functions
	MyAVLTree *insert(Student student, MyAVLTree *root);
	MyAVLTree *remove(string id, MyAVLTree *root, MyAVLTree *prevNode);
	MyAVLTree *removeInOrder(int n, MyAVLTree *root);

	// Search functions
	bool searchId(string id, MyAVLTree *root, bool doPrint);
	void searchName(string name, MyAVLTree *root);

	// Transversal functions
	void setInOrder(vector<Student> &inOrderNumbers, MyAVLTree *root);
	void setPreOrder(vector<Student> &preOrderNumbers, MyAVLTree *root);
	void setPostOrder(vector<Student> &postOrderNumbers, MyAVLTree *root);
	void setPostOrderNodes(vector<MyAVLTree *> &postOrderNumbers, MyAVLTree *root);
	void printInOrder(MyAVLTree *root);
	void printPreOrder(MyAVLTree *root);
	void printPostOrder(MyAVLTree *root);
};
// Destructor
MyAVLTree::~MyAVLTree()
{
	vector<MyAVLTree *> postOrderTransversal;
	setPostOrderNodes(postOrderTransversal, this);
	for (int i = 0; i < postOrderTransversal.size(); i++)
	{
		delete postOrderTransversal[i];
	}
}
// Tree Functions
// Gets height of tree (and any subtree within a tree given this)
int MyAVLTree::getTreeHeight(MyAVLTree *root)
{
	if (root == nullptr)
		return 0;
	int leftSubTree = getTreeHeight(root->left);
	int rightSubTree = getTreeHeight(root->right);
	int height = 1 + max(leftSubTree, rightSubTree);
	return height;
}
// LeftLeft Rotation Function
void MyAVLTree::leftLeftRotation(MyAVLTree *root)
{
	Student tempRoot = root->student;	 // saves root value
	root->student = root->left->student; // switches "root" (where it detected imbalance) to new root
	// determines if a node needs to "switch" to satisfy bst during rebalancing
	if (root->right == nullptr)
	{
		root->right = root->left;
		root->left = root->left->left;
		root->right->left = nullptr;
		root->right->student = tempRoot;
	}
	else
	{
		MyAVLTree *tempPtr = root->left->right;
		root->left->right = nullptr;
		root->left->right = root->left->left;
		root->left->student = tempRoot;
		root->left->right = root->right;
		root->right = root->left;
		root->left = root->left->left;
		root->right->left = tempPtr;
	}
}
void MyAVLTree::rightRightRotation(MyAVLTree *root)
{
	Student tempRoot = root->student;	  // saves root value
	root->student = root->right->student; // switches "root" (where it detected imbalance) to new root
	// determines if a node needs to "switch" to satisfy bst during rebalancing
	if (root->left == nullptr)
	{
		root->left = root->right;
		root->right = root->right->right;
		root->left->right = nullptr;
		root->left->student = tempRoot;
	}
	else
	{
		MyAVLTree *tempPtr = root->right->left;
		root->right->left = nullptr;
		root->right->left = root->right->right;
		root->right->student = tempRoot;
		root->right->left = root->left;
		root->left = root->right;
		root->right = root->right->right;
		root->left->right = tempPtr;
	}
}
void MyAVLTree::rightLeftRotation(MyAVLTree *root)
{
	// Modifies right left into right right form
	MyAVLTree *tempPtr = root->right->left;
	root->right->left = nullptr;
	tempPtr->right = root->right;
	root->right = tempPtr;

	root->rightRightRotation(root);
}
void MyAVLTree::leftRightRotation(MyAVLTree *root)
{
	// Modifies left right into left left form
	MyAVLTree *tempPtr = root->left->right;
	root->left->right = nullptr;
	tempPtr->left = root->left;
	root->left = tempPtr;
	root->leftLeftRotation(root);
}

void MyAVLTree::balanceTree(MyAVLTree *root)
{
	if (root != nullptr)
	{
		int balanceFactor = root->left->getTreeHeight(root->left) - root->right->getTreeHeight(root->right);
		if (abs(balanceFactor) > 1)
		{
			// Left
			if (balanceFactor > 0)
			{
				// Left Right
				if (root->left->right != nullptr && root->left->left == nullptr)
					root->leftRightRotation(root);
				// Left Left
				else
					root->leftLeftRotation(root);
			}
			// Right
			else
			{
				// Right Left
				if (root->right->left != nullptr && root->right->right == nullptr)
					root->rightLeftRotation(root);
				// Right Right
				else
					root->rightRightRotation(root);
			}
		}
	}
}
MyAVLTree *MyAVLTree::insert(Student student, MyAVLTree *root)
{
	if (root == nullptr)
	{
		cout << "successful" << endl;
		return new MyAVLTree(student);
	}
	// Recursive insertion
	if (stoi(root->student.id) < stoi(student.id))
		root->right = root->right->insert(student, root->right);
	else if (stoi(root->student.id) > stoi(student.id))
		root->left = root->left->insert(student, root->left);
	else
		cout << "unsuccessful" << endl;
	root->balanceTree(root);
	return root;
}
MyAVLTree *MyAVLTree::remove(string gatorId, MyAVLTree *root, MyAVLTree *prevNode = nullptr)
{
	if (root == nullptr)
	{
		cout << "unsuccessful" << endl;
		return root;
	}
	// Recursive removal
	if (stoi(root->student.id) > stoi(gatorId))
		root->left = root->left->remove(gatorId, root->left);
	else if (stoi(root->student.id) < stoi(gatorId))
		root->right = root->right->remove(gatorId, root->right);
	else
	{
		// Accounts for all the removal cases
		cout << "successful" << endl;
		if (root->right == nullptr && root->left == nullptr)
			if (prevNode == nullptr)
				root = nullptr;
			else if (prevNode->right == root)
				prevNode->right = nullptr;
			else
				prevNode->left = nullptr;
		else if (root->right != nullptr)
			if (prevNode == nullptr)
			{
				MyAVLTree *tempPtr = root->left;
				root = root->right;
				root->left = tempPtr;
			}
			else
			{
				MyAVLTree *tempPtr = root->right;
				root->right = nullptr;
				if (prevNode->right == root)
					prevNode->right = tempPtr;
				else
					prevNode->left = tempPtr;
			}
		else if (prevNode == nullptr)
		{
			MyAVLTree *tempPtr = root->right;
			root = root->left;
			root->right = tempPtr;
		}
		else
		{
			MyAVLTree *tempPtr = root->left;
			root->left = nullptr;
			if (prevNode->right == root)
				prevNode->right = tempPtr;
			else
				prevNode->left = tempPtr;
		}
	}
	return root;
}
bool MyAVLTree::searchId(string gatorId, MyAVLTree *root, bool doPrint)
{
	if (root == nullptr)
	{
		if (doPrint)
			cout << "unsuccessful" << endl;
		return false;
	}
	// Search by recursion
	else
	{
		if (root->student.id == gatorId)
		{
			if (doPrint)
				cout << root->student.name << endl;
			return true;
		}
		else if (stoi(root->student.id) > stoi(gatorId))
			return root->searchId(gatorId, root->left, doPrint);
		else
			return root->searchId(gatorId, root->right, doPrint);
	}
}

void MyAVLTree::searchName(string name, MyAVLTree *root)
{
	vector<Student> preOrderStudents;
	root->setPreOrder(preOrderStudents, root);
	// Get pre order values
	bool foundName = false;
	// Search through pre order vector
	for (int i = 0; i < preOrderStudents.size(); i++)
	{
		if (preOrderStudents[i].name == name)
		{
			cout << preOrderStudents[i].id << endl;
			foundName = true;
		}
	}
	if (!foundName)
		cout << "unsuccessful" << endl;
}

void MyAVLTree::setInOrder(vector<Student> &inOrderNumbers, MyAVLTree *root)
{
	if (root != nullptr)
	{
		root->setInOrder(inOrderNumbers, root->left);
		inOrderNumbers.push_back(root->student);
		root->setInOrder(inOrderNumbers, root->right);
	};
}
void MyAVLTree::setPreOrder(vector<Student> &preOrderNumbers, MyAVLTree *root)
{

	if (root != nullptr)
	{
		preOrderNumbers.push_back(root->student);
		root->left->setPreOrder(preOrderNumbers, root->left);
		root->right->setPreOrder(preOrderNumbers, root->right);
	};
}

void MyAVLTree::setPostOrder(vector<Student> &postOrderNumbers, MyAVLTree *root)
{

	if (root != nullptr)
	{
		root->left->setPostOrder(postOrderNumbers, root->left);
		root->right->setPostOrder(postOrderNumbers, root->right);
		postOrderNumbers.push_back(root->student);
	};
}
void MyAVLTree::setPostOrderNodes(vector<MyAVLTree *> &postOrderNodes, MyAVLTree *root)
{

	if (root != nullptr)
	{
		root->left->setPostOrderNodes(postOrderNodes, root->left);
		root->right->setPostOrderNodes(postOrderNodes, root->right);
		postOrderNodes.push_back(root);
	};
}

void MyAVLTree::printInOrder(MyAVLTree *root)
{
	vector<Student> inOrderNumbers;
	setInOrder(inOrderNumbers, root);
	for (int i = 0; i < inOrderNumbers.size(); i++)
	{
		if (i == inOrderNumbers.size() - 1)
		{
			cout << inOrderNumbers[i].name << endl;
			// Ensures last print has no ending comma
			break;
		}
		cout << inOrderNumbers[i].name << ", ";
	}
}

void MyAVLTree::printPreOrder(MyAVLTree *root)
{
	vector<Student> preOrderNumbers;
	setPreOrder(preOrderNumbers, root);
	for (int i = 0; i < preOrderNumbers.size(); i++)
	{
		if (i == preOrderNumbers.size() - 1)
		{
			cout << preOrderNumbers[i].name << endl;
			// Ensures last print has no ending comma
			break;
		}
		cout << preOrderNumbers[i].name << ", ";
	}
}

void MyAVLTree::printPostOrder(MyAVLTree *root)
{
	vector<Student> postOrderNumbers;
	setPostOrder(postOrderNumbers, root);
	for (int i = 0; i < postOrderNumbers.size(); i++)
	{
		if (i == postOrderNumbers.size() - 1)
		{
			cout << postOrderNumbers[i].name << endl;
			// Ensures last print has no ending comma
			break;
		}
		cout << postOrderNumbers[i].name << ", ";
	}
}

void MyAVLTree::printLevelCount(MyAVLTree *root)
{
	cout << getTreeHeight(root) << endl;
}

MyAVLTree *MyAVLTree::removeInOrder(int n, MyAVLTree *root)
{
	vector<Student> inOrderList;
	setInOrder(inOrderList, root);
	if (n >= inOrderList.size())
		cout << "unsuccessful" << endl;
	else
		// Calls remove on specified in order node
		root = root->remove(inOrderList[n].id, root);
	return root;
}

int main()
{
	int numOfCmds;
	cin >> numOfCmds;
	cin.ignore(256, '\n'); // allows swtich from cin -> getline(cin, s)
	MyAVLTree *tree = nullptr;
	for (int i = 0; i < numOfCmds; i++)
	{
		string input;
		getline(cin, input);
		bool validInput = true;
		if (input.find("insert ") != string::npos)
		{
			int j = 8;
			string name = "";
			// Ensure name is spaces and letters
			while (input[j] != '"')
			{
				if (isalpha(input[j]) || input[j] == ' ')
					name += input[j];
				else
				{
					cout << "unsuccessful" << endl;
					validInput = false;
					break;
				}
				j++;
			}
			string gatorId = input.substr(j + 2);
			// Ensure gatorId is only numbers
			for (int k = 0; k < gatorId.size(); k++)
			{
				if (!isdigit(gatorId[k]))
				{
					validInput = false;
					break;
				}
			}
			// Ensure gatorId is strictly 8 digits
			if (gatorId.size() != 8)
			{
				cout << "unsuccessful" << endl;
				validInput = false;
			}
			// ensures no duplicates
			if (tree->searchId(gatorId, tree, false))
			{
				cout << "unsuccessful" << endl;
				validInput = false;
			}
			if (validInput)
				tree = tree->insert(Student(name, gatorId), tree);
		}
		if (input.find("remove ") != string::npos)
		{
			string gatorId = input.substr(7);
			// Ensure gatorId is strictly 8 digits
			if (gatorId.size() != 8)
			{
				cout << "unsuccessful" << endl;
				validInput = false;
			}
			if (validInput)
				tree = tree->remove(gatorId, tree);
		}
		if (input.find("search ") != string::npos)
		{
			bool isNum = false;
			bool isAlph = false;
			string searchTerm = input.substr(7);
			for (int k = 0; k < searchTerm.size(); k++)
			{
				if (isdigit(searchTerm[k]))
					isNum = true;
				if (isalpha(searchTerm[k]))
					isAlph = true;
			}
			// Ensures no mix of letters and numbers passes
			if (isNum && isAlph)
				cout << "unsuccessful" << endl;
			else if (isNum)
				tree->searchId(searchTerm, tree, true);
			else if (isAlph)
				tree->searchName(searchTerm.substr(1, searchTerm.size() - 2), tree);
			else
				cout << "unsuccessful" << endl;
		}
		if (input.find("removeInorder ") != string::npos)
			tree->removeInOrder(stoi(input.substr(14)), tree);
		// Print order function calls
		if (input == "printInorder")
			tree->printInOrder(tree);
		if (input == "printPreorder")
			tree->printPreOrder(tree);
		if (input == "printPostorder")
			tree->printPostOrder(tree);
		if (input == "printLevelCount")
			tree->printLevelCount(tree);
	}
	return 0;
}