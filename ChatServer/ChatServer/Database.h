	#include<map>
#include<string>
#include<iostream>
using namespace std;
class Database{
public:
	Database();
	map<string, string> data;
	map<int, string> name_map;
	map<int, bool> con_map;
	bool look_up(string user);
	void set_data(int);
	bool get_data(int);
	void insert(int,string);
	string retrieve(int);
	string retrieve(int,int);
	void data_erase(int);
	bool login_check(int,string);
	string extract_name(string);
	void insert_name(int id, string name);
	string retrieve_pass(string user);
};

static Database* data_ptr;