#include"Database.h"
void Database::set_data(int ID){
	data_ptr->con_map[ID] = false;
}
bool Database::get_data(int ID){
	return data_ptr->con_map[ID];
}
Database::Database(){
	data_ptr = this;
}
string Database::extract_name(string user)
{
	int i;
	for (i = 0; i < user.length(); i++){
		if (user[i] == '!'){
			break;
		}
	}
	string name = user.substr(0, i);
	return name;
}

void Database::insert_name(int id, string user)
{
int i;
for (i = 0; i < user.length(); i++){
if (user[i] == '!'){
break;
}
}
string name = user.substr(0, i);
string  pass = user.substr(i + 2, user.length());
data_ptr->name_map[id] = name;
}

bool Database::look_up(string user){
	int i;
	for (i = 0; i < user.length(); i++){
		if (user[i] == '!'){
			break;
		}
	}
	string name = user.substr(0, i);
	string  pass = user.substr(i + 2, user.length());
	if (data_ptr->data.find(name) == data_ptr->data.end()){
		return false;
	}
	return true;
}

string Database::retrieve(int ID){
	return data_ptr->name_map[ID];
}

void Database::data_erase(int ID){
	data_ptr->name_map.erase(ID);
}
string Database::retrieve(int ID,int a){
	string temp="";
	map<int, string>::iterator it;
	for (it = data_ptr->name_map.begin(); it != data_ptr->name_map.end(); ++it){
		if (it->first!=ID && (!data_ptr->con_map[it->first]))
			temp = temp + "#" + to_string(it->first) + " " + it->second + " !";
	}
	if (temp != "")
		temp[temp.length() - 1] = '\0';
	return temp;
}

string Database::retrieve_pass(string user){
	return data_ptr->data[user];
}

void Database::insert(int id,string user){
	int i;
	for (i = 0; i < user.length(); i++){
		if (user[i] == '!'){
			break;
		}
	}
	string name = user.substr(0, i);
	string  pass = user.substr(i + 2, user.length());
	data_ptr->data[name] = pass;
	data_ptr->name_map[id] = name;
}


bool Database::login_check(int ID,string user){
	int i;
	//cout << user << "     fa";
	if (user[user.length()-1] == '/'){
		data_ptr->con_map[ID] = true;
		user = user.substr(0, user.length() - 1);
	}
	
	for (i = 0; i < user.length(); i++){
		if (user[i] == '!'){
			break;
		}
	}
	string name = user.substr(0, i);
	string  pass = user.substr(i + 2, user.length());
	if (data_ptr->data.find(name) == data_ptr->data.end()){
		return false;
	}
	if (data_ptr->data[name] != pass){
		return false;
	}
	return true;
}