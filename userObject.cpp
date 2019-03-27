#include "bplustree.h"

using namespace std;
userObject::userObject(int perm, string name, std::string genre1, std::string genre2) {

	this->perm = perm;
	this->name = name;
	this->genre1 = genre1;
	this->genre2 = genre2;

}

int userObject::getPerm() {
	return perm;
}


string userObject::getName() {
	return name;
}

string userObject::getGenre1() {
	return genre1;
}

string userObject::getGenre2() {
	return genre2;
}
