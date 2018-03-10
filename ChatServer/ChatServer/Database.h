#include<map>
#include<string>
using namespace std;
class Database{
public:
	Database();
	map<string, string> data;
	map<int, string> name_map;
	bool look_up(string user);
	void insert(int,string);
	string retrieve(int);
	string retrieve(int,int);
	void data_erase(int);
	bool login_check(string);
	string extract_name(string);
	void insert_name(int id, string name);
};

static Database* data_ptr;