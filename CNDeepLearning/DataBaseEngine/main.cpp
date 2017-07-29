#include <iostream>
#include <string>
#include "leveldb/db.h"  

using namespace std;
int main()
{
	leveldb::DB* db;
	leveldb::Options options;
	options.create_if_missing = true;
	leveldb::Status s = leveldb::DB::Open(options, "database", &db);

	if (!s.ok())
	{
		return -1;
	}
	s = db->Put(leveldb::WriteOptions(), "a", "102");
	string value;
	s = db->Get(leveldb::ReadOptions(), "a", &value);
	cout << value << endl;

	delete db;
	return 0;
}