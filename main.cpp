//#include "bplustree.h"
#include "graph.cpp"
#include <sstream>
#include <fstream>
// main function
class solution{
	adjacencyList aL;
	bplustree* bpt = new bplustree();
	
	public:
		solution(){
		}

		void InputFile(string filename){
			ifstream inputFile;
			char splitter =';';
			string arguments;
			inputFile.open(filename);
			while(getline(inputFile,arguments)){
				int inputCount = 0;
				istringstream split(arguments);
				vector<string>tokens;
				vector<int> relations;
				vector<int> tempfix;
				string userInput;
				while(getline(split,userInput,splitter)){
					//0 means this is the perm number, so
					//we a
					if(inputCount == 0){
						tempfix.push_back(stoi(userInput));
					}
					else if(inputCount < 4){
						tokens.push_back(userInput);	
					}
					else{
						relations.push_back(stoi(userInput));
					}
					inputCount++;
				}
				for(int x = 0 ; x < relations.size();x++){
					aL.addEdge(tempfix[0],relations[x]);
				}

				userObject* user = new userObject(tempfix[0],tokens[0],tokens[1],tokens[2]);
				bpt->Insert(tempfix[0],user);
			}
			inputFile.close();

			//print the B-tree
			//bpt->printTree();
		}

		void addUser(int perm, string name, string genre1,string genre2,vector<int> relations){
			
				for(int x = 0 ; x < relations.size(); x++){
					aL.addEdge(perm,relations[x]);
					aL.addEdge(relations[x],perm);
				}
				
				userObject* inserted = new userObject(perm,name,genre1,genre2);
				bpt->Insert(perm,inserted);
			
		}
			
		void findUser(int perm){
			userObject* userInTree = bpt->Search(perm);
			if(userInTree->perm == -1){
				cout<<"User is not found"<<endl;
			}
			else{
				cout<<"Success!"<<endl;
		
			}
		}
		void findUserDetails(int perm){
			userObject* userInTree = bpt->Search(perm);
			if(userInTree->perm == -1){
				cout<<"User is not found"<<endl;
			}
			else{
				cout<<"Perm Number : " << userInTree->perm<<endl;
				cout<<"Name : "<< userInTree->name<<endl;
				cout<<"Genre 1 : "<< userInTree->genre1<<endl;
				cout<<"Genre 2 : "<< userInTree->genre2<<endl;
				cout<<"Perm Numbers of Friends : ";
				aL.userRelation(perm);
			}
		}
		
		void recommendedFriends(int perm){
			vector<userObject>* recommended = new vector<userObject>;
			userObject* user  = bpt->Search(perm);
			string genre1 = user->genre1;
			string genre2 = user->genre2;
			aL.DFS(perm, genre1,genre2,recommended,bpt);
			cout<<"Recommended Friends:"<<endl;
			for(int x = 0 ; x < recommended[0].size();x++){
				userObject s = recommended[0][x];
				if( aL.isFriend(perm, s.getPerm())){
					cout<<"<"<<s.getPerm()<<", "<<s.getName()<<", "<<s.getGenre1()<<", "<<s.getGenre2()<<">"<<endl;
				}
			}
		}

};

int main(int argc, char* argv[])
{
	solution* sol =new solution();
	vector<int>push;
	sol->addUser(-4,"Test","test","test",push);
	sol->addUser(-12,"Test","Test","test",push);
	sol->addUser(-6,"Test","test","test",push);
	//sol.InputFile("friends.txt");
	cout<<"Welcome To The Friendship Recommender Application"<<endl;
        cout<<"What actions would you like to perform?"<<endl;
        cout<<"1) Insert TextFile"<<endl;
        cout<<"2) Insert User"<<endl;
        cout<<"3) Find User "<<endl;
        cout<<"4) Find User Details"<<endl;
	cout<<"5) Recommend Friends"<<endl;
        cout<<"6) Exit "<<endl;
        int action;
        while(true){
                 cin.clear();
                 cin>>action;
                        if(cin.fail()){
                                cin.clear();
                                cin.ignore();
                                cout<<"Invalid Command, Try Again"<<endl;
                                continue;
                        }
                        string word;
                        switch(action){
                                case 1:{
					cin.clear();
					cout<<"Type the file name"<<endl;
					cin>>word;
                                        sol->InputFile(word);
                                        cout<<"Done\n\n"<<endl;
                                        break;
                                       }
                                case 2:
                                        {
					int perm;
					string name;
					string genre1;
					string genre2;
					string relations;
					string splitter;
					vector<int> push;
					cout<<"Type perm of new user:"<<endl;
            				cin>>perm;
        				cout<<"Type name of new user:"<<endl;
            				cin>>name;
            				cout<<"Type new user's 1st favorite genre:"<<endl;
            				cin>>genre1;
            				cout<<"Type new user's 2st favorite genre:"<<endl;
            				cin>>genre2;
     				        cout<<"Enter perms of friends of new user ex: 1;2;3;4: "<<endl;
            				cin>>relations;
                                        stringstream ss(relations);
					while(getline(ss,splitter,';')){
						push.push_back(atoi(splitter.c_str()));
					}
					sol->addUser(perm,name,genre1,genre2,push);
                                        cout<<"Success"<<endl;
                                        break;
                                        }
                                case 3:
                                        {
                                        int perm;
					cout<<"Type perm of user:"<<endl;
                                        cin>>perm;
					sol->findUser(perm);
                                        break;
                                        }
                                case 4:
                                        {
                                        int perm;
                                        cout<<"Type perm of user:"<<endl;
                                        cin>>perm;
					sol->findUserDetails(perm);
					cout<<"Success"<<endl;
					break;
                                        }
                                case 5:{
                                        int perm;
                                        cout<<"Type perm of user:"<<endl;
                                        cin>>perm;
					sol->recommendedFriends(perm);
					cout<<"Success"<<endl;
					break;
				       }
				case 6:{
					cout<<"Exiting"<<endl;
					return 0;
				       }
                                default:
                                        cout<<"Invalid Command, Try Again"<<endl;
                        }
        		cout<<"What actions would you like to perform?"<<endl;
      			cout<<"1) Insert TextFile"<<endl;
        		cout<<"2) Insert User"<<endl;
        		cout<<"3) Find User "<<endl;
       			cout<<"4) Find User Details"<<endl;
      			cout<<"5) Recommend Friends"<<endl;
        		cout<<"6) Exit "<<endl;                
	
	}

	/*vector<int> push = {16,32,35,3};
	solution* friendrec = new solution();
	string test = "users_friendship.txt";
	friendrec->InputFile(test);
	friendrec->recommendedFriends(22);*/
//	BPlusTree x;
//	x.Initialize(4);
//	adjacencyList 
};

