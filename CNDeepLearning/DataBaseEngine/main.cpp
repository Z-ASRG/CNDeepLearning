#include <iostream>
#include <string>
#include "leveldb/db.h"  
#include "Tensor.h"
#include <fstream>
#include <sstream>
#include <boost/filesystem.hpp>  
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>

#include<SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

using namespace std;

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
int get_labels(const std::string& dir, std::vector<std::string>& filenames)
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

		if (fs::is_directory(iter->status()))
		{
			std::string label = iter->path().string();
			label = label.substr(label.rfind("\\") + 1, label.size());

			filenames.push_back(label);
		}
	}

	return filenames.size();
}
void saveFilesIntoDatabase(std::string filespath, leveldb::DB* db)
{
	vector<std::string> files;
	get_filenames(filespath, files);

	std::stringstream ss;
	boost::archive::text_oarchive osa(ss);
	std::vector<Tensor<double>> tensorset;
	for (int i=0 ;i<files.size();i++)
	{
		sf::Image image;
		if (!image.loadFromFile(files[i].c_str()))
		{
			printf("Loading file failed!");
			return;
		}
		Tensor<double> tensor;
		tensor._shape.row=image.getSize().y;
		tensor._shape.column=image.getSize().x;
		for (int h = 0; h < image.getSize().y; h++)
			for (int w = 0; w < image.getSize().x; w++)
			{
				sf::Color color = image.getPixel(w, h);
				int r = (int)color.r;
				int g = (int)color.g;
				int b = (int)color.b;
				double ivalue = 0.0;
				if (r > 150 || g > 150 || b > 150)
				{
					r = g = b = 255;
					ivalue = 1.0;
				}
				else
				{
					r = g = b = 0;
					ivalue = 0.0;
				}
				tensor._data.push_back(ivalue);
			}
		tensorset.push_back(tensor);
		//std::cout << "Percent: " << (float)i / (float)files.size() * 100 << endl;
	}
	osa << tensorset;
	leveldb::Status s = db->Put(leveldb::WriteOptions(), filespath, ss.str());

	std::cout << "Finished!" << endl;
}
bool readDataBase(const std::string& dbname,const std::string& picfolder)
{
	leveldb::DB* db;
	leveldb::Options options;
	options.create_if_missing = true;
	leveldb::Status s = leveldb::DB::Open(options, dbname, &db);

	if (!s.ok())
	{
		cout << "create database failed" << endl;
		return false;
	}
	std::string pics = picfolder + dbname + "\\";
	
	std::stringstream ss;
	std::string str;
	leveldb::Status status = db->Get(leveldb::ReadOptions(), pics, &str);
	ss << str;

	boost::archive::text_iarchive osa(ss);
	std::vector<Tensor<double>> tensorset;

	osa >> tensorset;

	delete db;
	return true;
}
int main()
{
	std::string picfolder = "G:\\train_image\\";
	vector<std::string> dbname;
	get_labels(picfolder,dbname);

	for (int i = 0; i < dbname.size(); i++)
	{
		leveldb::DB* db;
		leveldb::Options options;
		options.create_if_missing = true;
		leveldb::Status s = leveldb::DB::Open(options, dbname[i], &db);

		if (!s.ok())
		{
			cout << "create database failed" << endl;
			return -1;
		}
		std::string pics = picfolder + dbname[i] + "\\";
		saveFilesIntoDatabase(pics, db);

		delete db;
	}

	readDataBase("0",picfolder);


	//double arr[] = { 2.9,34.7 };
	//Tensor<double> t(arr, 1, 2), t2;



	//std::string value;
	//s = db->Get(leveldb::ReadOptions(), "a", &value);
	//std::stringstream oss;
	//oss << value;
	//boost::archive::text_iarchive isa(oss);
	//isa >> t2;
	//cout << value << endl;

	



	//std::ofstream ofs("myfile.txt");
	//boost::archive::text_oarchive oa(ofs);
	//oa << t;
	//ofs.close();
	/////read

	//std::ifstream ifs("myfile.txt");
	//boost::archive::text_iarchive ia(ifs);
	//ia >> t2;
	//ifs.close();



	return 0;
}