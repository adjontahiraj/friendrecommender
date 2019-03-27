#include "bplustree.h"
#include <tuple>


leafnode::leafnode() {

	leaf = true;

}

// getter functions
std::vector<vector<userObject*>> leafnode::getData()
{
	// return the vector of the data
	return data;
}

genericNode* leafnode :: getNext() {
	return next;
}

void leafnode::Insert(int perm, userObject* user) {

	// search for the key in the given leaf node
	std::vector<int>::iterator index = lower_bound(permKeys.begin(), permKeys.end(), perm);
	if((0 != permKeys.size()) && (perm == permKeys[index - permKeys.begin()])) {
		data[index - permKeys.begin()].push_back(user);
	} else {
		permKeys.insert(index, perm);
		vector<userObject*> newData;
		newData.push_back(user);

	//insert the corresponding value

		index = lower_bound(permKeys.begin(), permKeys.end(), perm);
	//auto obj = std::t (user, indx);
		data.insert(data.begin() + (index - permKeys.begin()), newData);
	}

}
genericNode* leafnode::Split(int* keyToParent)
{
	// create a new right leaf node
	leafnode* rightNode = new leafnode;

	// key to be moved up to the parent is the middle element in the current leaf node
	*keyToParent = permKeys[permKeys.size() / 2];

	//copy second half to new leafnode and erase it so current leaf is good
	rightNode->permKeys.assign(permKeys.begin() + permKeys.size() / 2, permKeys.end());
	rightNode->data.assign(data.begin() + data.size() / 2, data.end());
	permKeys.erase(permKeys.begin() + permKeys.size() / 2, permKeys.end());
	data.erase(data.begin() + data.size() / 2, data.end());


	// return the right leaf node
	return rightNode;
}

