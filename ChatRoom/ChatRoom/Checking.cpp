#include "Checking.h"

bool database::look_up(string username){
	if (data_store.find(username) == data_store.end())
		return false;
	else
		return true;
}

void database::insert(string username, string password){
	data_store[username] = password;
}