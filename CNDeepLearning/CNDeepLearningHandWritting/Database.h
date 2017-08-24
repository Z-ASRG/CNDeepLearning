#pragma once

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

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

using namespace std;

bool readDataBase(const std::string& dbname, const std::string& picfolder, std::vector<Tensor<double>>& tensorset)
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

	osa >> tensorset;

	delete db;
	return true;
}

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