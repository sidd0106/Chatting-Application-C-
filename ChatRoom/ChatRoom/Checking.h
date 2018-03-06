#include<string>
#include<map>
using namespace std;

class database{
public:
	map<string, string> data_store;

	//database(string username, string password);

	bool look_up(string username);

	void insert(string username, string password);
	
};

static database db;
