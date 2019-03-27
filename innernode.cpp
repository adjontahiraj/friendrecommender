#include "bplustree.h"

innernode::innernode() {
	
	leaf = false;
}



// function for insertion in a new inner root node
void innernode::Insert(int perm, genericNode* leftChild, genericNode* rightChild)
{
	// insert key, left child and right child
	permKeys.push_back(perm);
	children.push_back(leftChild);
	children.push_back(rightChild);
}


void innernode::Insert(int perm, genericNode* rightChild)
{
	// insert key in to suitable position in the given inner node
	std::vector<int>::iterator index = lower_bound(permKeys.begin(), permKeys.end(), perm);
	permKeys.insert(index, perm);

	// insert right child in the immediately next index in the children vector
	index = lower_bound(permKeys.begin(), permKeys.end(), perm);
	children.insert(children.begin() + (index - permKeys.begin() + 1), rightChild);
}

genericNode* innernode::Split(int* parentpermKey)
{
	int length = permKeys.size();

	// create a new right inner node
	innernode *rightNode = new innernode;

	// key to be moved up to the parent is the middle element in the current inner node
	*parentpermKey = permKeys[length / 2];

	// Copy the second half of the current inner node excluding the middle element to the
	// new right inner node. Erase the second half of the current inner node including
	// the middle element, and thus current inner node becomes the left inner node.
	rightNode->permKeys.assign(permKeys.begin() + (length / 2 + 1), permKeys.end());
	rightNode->children.assign(children.begin() + (length / 2 + 1), children.end());
	permKeys.erase(permKeys.begin() + length / 2, permKeys.end());
	children.erase(children.begin() + (length / 2 + 1), children.end());

	// return the new right inner node
	return rightNode;
}

std::vector<genericNode*>innernode::get_Children()
{
	// return the children vector
	return children;
}
