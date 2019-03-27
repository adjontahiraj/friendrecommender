#include "bplustree.h"
using namespace std;
// A utility function to add an edge in an 
// undirected graph
class adjacencyList { 
	public:
		//this is the adjacency list
		vector<vector<int>> ajlist;

		//the map keeps track of the current user perms in the list
		//and the index of the users in the list
		unordered_map<int,int> hmap;

		//this adds a edge or freindship between two users
		void addEdge(int perm1, int perm2) { 
			//if perm1 is not in the system
			if(hmap.find(perm1) == hmap.end()){
				//making new vector for the user and pushing to the list
				vector<int> newUser1;
				ajlist.push_back(newUser1);

				//updating the map with the index of the user
				hmap.insert({perm1,ajlist.size()-1});
			}
			//if perm2 is not in the system follow same steps as above
			/*if (hmap.find(perm2)==hmap.end()){
				vector<int> newUser2;
				ajlist.push_back(newUser2);
				hmap.insert({perm2,ajlist.size()-1});
			}*/

			//p1 & p2 are the indexes of the users in the adjacency list
			int p1 = hmap.find(perm1)->second;
			/*int p2 = hmap.find(perm2)->second;

			//variables used to check if friendship edges already exists 
			bool p1Exist = false;
			bool p2Exist = false;

			//checking if perm2 is already a friend of perm1
			for(int p1Iter = 0; p1Iter < ajlist[p1].size(); p1Iter++) {
				if(ajlist[p1][p1Iter] == perm2) {
					p2Exist = true;
				}
			}

			//checking if perm1 is already a freind of perm2
			for(int p2Iter = 0; p2Iter< ajlist[p2].size(); p2Iter++){
				if(ajlist[p2][p2Iter] == perm1) {
					p1Exist = true;
				}
			}
			
			//adding perm1 to perm2's freind list if it doesnt exist
			if(!p1Exist){
   	 			ajlist[p2].push_back(perm1); 
			}*/
			
			//adding perm2 to perm1's freind list if it doesnt exist
			//if(!p2Exist){
  			ajlist[p1].push_back(perm2); 
			//}
		}

		bool isFriend(int perm, int recPerm) {
			int i = hmap.find(perm)->second;
			for(int x = 0; x<ajlist[i].size(); x++) {
				if(ajlist[i][x] == recPerm) {
					return false;
				}
			}
			return true;
		}
		//A utility function to print the friends of a user
		//with the given perm number
		void userRelation(int perm) {
			
			int pIndex = hmap.find(perm)->second;
			for(int x = 0; x < ajlist[pIndex].size(); x++) {
				cout<<ajlist[pIndex][x];

				if(x != ajlist[pIndex].size()-1) {
					cout<<", ";
				}
			}
		    cout<<endl;
		}	 
		
		void depthFSHelper(int permIndex, bool seen[], string g1, string g2, vector<userObject>* r, bplustree* b) {
			seen[permIndex] = true;
			
			vector<int>::iterator i;
			for(i = ajlist[permIndex].begin(); i!= ajlist[permIndex].end(); ++i) {
				if(!seen[hmap.find(*i)->second]) {
					userObject* user = b->Search(*i);
					if(user->getGenre1() == g1 || user->getGenre2() == g1) {
							r->push_back(*user);
					} 
					else if(user->getGenre1() == g2 || user->getGenre2() == g2) {
							r->push_back(*user);
					}
					depthFSHelper(hmap.find(*i)->second, seen, g1, g2, r, b);
				}
			}
		}
		//depth first search main algorithm
		void DFS(int perm, string g1, string g2, vector<userObject>* r, bplustree* b) {
			bool *seen = new bool[ajlist.size()];
			for(int i = 0; i< ajlist.size(); i++) {
				seen[i] = false;
			}
			depthFSHelper(hmap.find(perm)->second, seen, g1, g2, r, b);
		}

		/*void BFS(int perm, string genre1, string genre2, vector<userObject>* recommended, bplustree bpt){
			cout<<"inside bfs"<<endl;
			//an array to keep track of all the nodes
			//that have been visited
			bool* visited = new bool[ajlist.size()];

			//set all the nodes to false
			for(int y = 0; y <ajlist.size(); y++){
				visited[y] = false;
			}
			//setting the index of the node where we start from to true

			visited[hmap.find(perm)->second] = true;
			cout<<"index of perm "<<perm<<" "<<hmap.find(perm)->second<<endl;
			//queue to add nodes to and visit them
			list<userObject> queue;
			userObject* user = bpt.Search(perm);
			queue.push_back(*user);
			//used to get the front of the queue
			int currNode;
			//to keep track of the index of perms as we traverse 
			int index;
			int test = 1;
			//userObject* user = = bpt.Search(ajlist[hmap.find(currNode)->second][i]);
			//traversing through the graph
			cout<<"before while loop"<<endl;
			while(!queue.empty()){
				
				cout<<"\n\nTEST IS "<<test<<endl;
				*user = queue.front();
				queue.pop_front();
				cout<<"inside while"<<endl;
				cout<<"current perm "<<user->perm<<endl;
				cout<<"size of frined list: "<<ajlist[hmap.find(user->perm)->second].size()<<endl;
				for(int i = 0 ; i < ajlist[hmap.find(user->perm)->second].size(); i++) {
					//userObject pointing to the user we are visiting
					//cout<<currNode<<endl;
					cout<<"t0"<<endl;
					user = bpt.Search(ajlist[hmap.find(user->perm)->second][i]);
					
					//getting index of the user
					//perm = user->perm;
					//cout<<perm<<","<<endl;
					//cout<<"TEST1"<<endl;
					index = hmap.find(user->perm)->second;

					//if we have visited this node we do nothing, 
					//else we go into the loop below to check it
					//cout<<"TEST2"<<endl;
					if(!visited[index]){
						test++;
						//mark node visited
						visited[index] = true;
						cout<<"XXX"<<endl;
						//push node to queue
						queue.push_back(*user);
						
						//if the 
						/*if(user->getGenre1() == genre1 || user->getGenre2() == genre1){
							recommended->push_back(*user);
						}
						else if(user->getGenre1() == genre2 || user->getGenre2() == genre2){
							recommended->push_back(*user);
						}
					}
					cout<<"TEST 3"<<endl;
				}
			}


		}*/
};
	
	
	
	
	
	
