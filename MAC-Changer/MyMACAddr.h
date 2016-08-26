/*
*/

#pragma once
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <unordered_map>

#include <Windows.h>
#include <iphlpapi.h>
#include <tchar.h>


//this is important , becasue window.h defines MAX which conflicts 
#undef max
//-----------------------------------------------

#pragma comment(lib, "IPHLPAPI.lib")
using namespace std;

class MyMACAddr
{
public:
	MyMACAddr();
	~MyMACAddr();

	string GenRandMAC();

	void showAdapterList();
	unordered_map<string, string> getAdapters();

	void AssingRndMAC();


private:
	string MACAdd = "Unknown";


};

