#include "bplustree.h"


using namespace std;

void bplustree::Insert(int perm, userObject* data) {
	// check if tree is empty
	if (root == NULL) {
		// Regardless of M root is always a leaf node for
		// the first insertion. So, create a new leaf node.
		root = new leafnode;
		root->Insert(perm, data);
		//cout<<"inserted"<<perm<<endl;
	}

	// if it is not the root
	else {
		//to check if we split the root due to insert
		bool removeRoot = false;

		genericNode* l = NULL;
		genericNode* r = NULL;
		//keep track of parentPerm key
		int* parentpermKey = new int;
		

		// obtain the search path from the root to leaf node and push it on to a stack
		stack<genericNode*>* s = new stack<genericNode*>;
		findPath(root, perm, s);

		// insert the key perm with the data value it holds
		s->top()->Insert(perm, data);


		// Split the current node and insert the middle key & children in to the parent.
		// we do this at 3 because out tree has l = 2;
		while (s->top()->getpermKeys().size() == 3) {
			// current node becomes left half, and middle perm key is what we give to the parent
			l = s->top();
			r = l->Split(parentpermKey);

			// check if currently split node is not the root node
			s->pop();
			if (!s->empty())
			{
				// Insert the middle key and the right half in to
				// the parent. The parent will be an inner node.
				s->top()->Insert(*parentpermKey, r);
			}
			// if currently split node is the root node
			else
			{
				// we need to remove the root
				removeRoot = true;
				break;
			}
		}


		// we need new nodes l and r to connect to the root
		if (removeRoot)
		{
			// create a new inner node
			innernode* tRoot = new innernode;

			// insert the left and the right halves as the children of this new inner node
			tRoot->Insert(*parentpermKey, l, r);

			// mark this new inner node as the root of the tree
			root = tRoot;
		}
		delete(parentpermKey);
		delete(s);
	}
}

void bplustree :: print(genericNode* n) {
		if(n == NULL) {
			cerr<<"Empty Tree"<<endl;
		}

		//for key perm numbers that set the tree equality
		vector<int> perms = n->getpermKeys();

		//printing out correct node names
		if(n->isLeaf()) {
			cout<<"\nLeafNode Data: ";
		}else{
			cout<<"\nInnerNode keys: ";
		}

		//
		vector<int>::iterator index;
		for(index = perms.begin(); index != perms.end(); index++) {
			cout<<*index<<" ";
		}
		cout<<"\n";
		//if this is an inner node
		if (!n->isLeaf()) {
			vector<genericNode*> childNodes = n->get_Children();
			//printing the child nodes
			cout<<"Child Nodes: ";
			vector<genericNode*>::iterator c;
			for(c = childNodes.begin(); c!= childNodes.end(); c++) {
				vector<int> childPerms = (*c)->getpermKeys();
				vector<int>::iterator cp;
				for(cp = childPerms.begin(); cp!= childPerms.end(); cp++) {
					cout<<*cp<<" ";
				}
				cout<<"\n";
			}

			vector<genericNode*>::iterator i;
			for(i = childNodes.begin(); i!= childNodes.end(); i++) {
				print(*i);
			}
		}

}

void bplustree::printTree(){
	print(root);
}
	

void bplustree::findPath(genericNode* n, int perm, stack<genericNode*>* s) {

	// push node to stack
	s->push(n);

	// check if the node pushed to stack is an inner node
	if (!n->isLeaf()) {
		// search for the given key in the current node
		vector<int> keys = n->getpermKeys();
		vector<genericNode*> children = n->get_Children();
		vector<int>::iterator index = lower_bound(keys.begin(), keys.end(), perm);

		// check if key is found
		if (perm == keys[index - keys.begin()])
		{
			// recursively repeat by searching the path through the corresponding right child index
			findPath(children[(index - keys.begin()) + 1], perm, s);
		}

		// if key is not found
		else
		{
			// recursively repeat by searching the path through the corresponding left child index
			findPath(children[index - keys.begin()], perm, s);
		}
	}

}

bplustree :: bplustree() {
	root = NULL;
	m = 4;
}



userObject* bplustree::Search(int perm){
	userObject* nullObj = new userObject(-1,"Null","Null","Null");
	int c = 0;

	// getting search path from root to leafe Node
	stack<genericNode*>* s = new stack<genericNode*>;
	//getting the path to the correct data or a null
	findPath(root, perm, s);

	// search for the key in the leaf node, which is at the top of the stack
	vector<int> permKeys = s->top()->getpermKeys();
	vector<vector<userObject*>> values = s->top()->getData();
	vector<int>::iterator index = lower_bound(permKeys.begin(), permKeys.end(), perm);

	// check if key is found
	if (perm == permKeys[index - permKeys.begin()]){
		delete nullObj;
		nullObj = values[index - permKeys.begin()][c];

	}
	delete(s);

	//return bad userObject
	return nullObj;
}

