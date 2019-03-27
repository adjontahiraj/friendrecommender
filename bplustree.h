#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <stdio.h>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <stack>
#include <string>
#include <iostream>
#include <list>
using namespace std;

class userObject {
    public:
        userObject(int perm, string name, string genre1, string genre2);
        int perm;
        string name;
        string genre1;
        string genre2;
        int getPerm();
        string getName();
        string getGenre1();
        string getGenre2();

};

class genericNode{
    protected:
        
        bool leaf;
        vector<int> permKeys;
    public:
        virtual genericNode* getNext() {
            genericNode* x = NULL;
            return x;
        }
        //to hold the user objects
        virtual vector<vector<userObject*>> getData() {
            vector<vector<userObject*>> x;
            return x;
        }
        vector<int> getpermKeys();
        
        bool isLeaf();
        virtual void Insert(int perm, userObject* userObject){}
        virtual void Insert(int perm, genericNode* rightChild){}
        virtual void Insert(int perm, genericNode* leftChild, genericNode* rightChild){}
        virtual genericNode* Split(int* parentpermKey) {
            genericNode* x = NULL;
            return x;
            }
        virtual vector<genericNode*> get_Children(){
            vector<genericNode*> x;
            return x;
        }
        virtual void Search(int perm){}
};

class leafnode : public genericNode{
    public:
    
        leafnode();
        vector<vector<userObject*>> getData();
        genericNode* getNext();
        void Insert(int perm, userObject* data);

        //function to split nodes
        genericNode* Split(int* parentpermkey);
        

    private:
        leafnode* prev;
        leafnode* next;
        vector<vector<userObject*>> data;

};



class innernode: public genericNode{
    public:

        innernode();
        genericNode* Split(int* parentpermKey);
        vector<genericNode*> get_Children();
        void Insert(int perm, genericNode* rightChild);
        void Insert(int perm, genericNode* leftChild, genericNode* rightChild);
        

    private:
    //the children of the node
        vector<genericNode*> children;

};

class bplustree{
    public:
        bplustree();
        void Insert(int perm, userObject* data);
        void Reveal_Tree(genericNode* node);
        userObject* Search(int perm);
        genericNode* root;
        void printTree();
        //vector<userObject> f;


    private:
        int m;
        void findPath(genericNode* n, int perm, stack<genericNode*>* s);
        void print(genericNode* n);



};

#endif