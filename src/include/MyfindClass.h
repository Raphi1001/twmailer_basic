#include <vector>

#ifndef MYFINDCLASS_H
#define MYFINDCLASS_H
#pragma once

class MyfindClass
{
private:
	bool caseSensitve = true;
	bool recursive = false;
	char *program_name = NULL;
	std::string searchpath = "";
	std::string pathToFile = "Not Found";
	std::vector<std::string> filenames;
	std::vector<pid_t> children;

	//func
	void Print_usage();
	void ForkFiles();
	void WaitChild();
	void FindFile(int i);
	void SingleSearch(std::string path, std::string fileToSearch); 
	std::string StringToLower(std::string str);

public:
	MyfindClass(){};  		//ctor
	~MyfindClass(){};   	//dtor

	//func
	bool ReadInput(int argc, char *argv[]);
	bool StartSearch();
	void KillZombies();
};
#endif