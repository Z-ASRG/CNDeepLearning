#include <iostream>
#include <string>
#include "leveldb/db.h"  
#include "Tensor.h"
#include <fstream>
#include <sstream>
#include <boost/filesystem.hpp>  

int get_filenames(const std::string& dir, std::vector<std::string>& filenames)
{
	namespace fs = boost::filesystem;
	fs::path path(dir);
	if (!fs::exists(path))
	{
		return -1;
	}

	fs::directory_iterator end_iter;
	for (fs::directory_iterator iter(path); iter != end_iter; ++iter)
	{
		if (fs::is_regular_file(iter->status()))
		{
			filenames.push_back(iter->path().string());
		}

		if (fs::is_directory(iter->status()))
		{
			get_filenames(iter->path().string(), filenames);
		}
	}

	return filenames.size();
}
using namespace std;
int main()
{
	vector<std::string> files;
	get_filenames("E:\\train_image\\0\\", files);

	leveldb::DB* db;
	leveldb::Options options;
	options.create_if_missing = true;
	leveldb::Status s = leveldb::DB::Open(options, "database", &db);

	if (!s.ok())
	{
		return -1;
	}
	double arr[] = { 2.9,34.7 };
	Tensor<double> t(arr, 1, 2), t2;

	std::stringstream ss;
	boost::archive::text_oarchive osa(ss);
	osa << t;

	s = db->Put(leveldb::WriteOptions(), "a", ss.str());

	std::string value;
	s = db->Get(leveldb::ReadOptions(), "a", &value);
	std::stringstream oss;
	oss << value;
	boost::archive::text_iarchive isa(oss);
	isa >> t2;
	cout << value << endl;

	delete db;



	std::ofstream ofs("myfile.txt");
	boost::archive::text_oarchive oa(ofs);
	oa << t;
	ofs.close();
	///read

	std::ifstream ifs("myfile.txt");
	boost::archive::text_iarchive ia(ifs);
	ia >> t2;
	ifs.close();



	return 0;
}