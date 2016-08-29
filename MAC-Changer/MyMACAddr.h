/*
* Copyright (C) 2016 SaEeD
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*
*
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
#include <netcon.h>
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
	//disable and enable the Adapter to effect new Changes 
	HRESULT DisableEnableConnections(BOOL bEnable, const wchar_t * AdapterName);



};

