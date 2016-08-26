#include "MyMACAddr.h"

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))


MyMACAddr::MyMACAddr()
{
	srand((unsigned)time(0));
}


MyMACAddr::~MyMACAddr()
{
}

string MyMACAddr::GenRandMAC()
{
	stringstream temp;
	int number = 0;
	string result;

	for (int i = 0; i < 6; i++)
	{
		number = rand() % 254;
		temp << setfill('0') << setw(2) << hex << number;
		if (i != 5)
		{
			temp << "-";
		}
	}
	result = temp.str();
	
	for (auto &c : result)
	{
		c = toupper(c);
	}

	return result;
}

//-----------------------------------------------
// https://msdn.microsoft.com/en-us/library/windows/desktop/aa366062(v=vs.85).aspx
//-----------------------------------------------

void MyMACAddr::showAdapterList()
{
	PIP_ADAPTER_INFO pAdapterInfo;
	PIP_ADAPTER_INFO pAdapter = NULL;
	DWORD dwRetVal = 0;
	UINT i;

	ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
	pAdapterInfo = (IP_ADAPTER_INFO *)MALLOC(sizeof(IP_ADAPTER_INFO));
	if (pAdapterInfo == NULL) {
		cerr << "Error allocating memory needed to call GetAdaptersinfo." << endl;
	}
	// Make an initial call to GetAdaptersInfo to get
	// the necessary size into the ulOutBufLen variable
	if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
		FREE(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO *)MALLOC(ulOutBufLen);
		if (pAdapterInfo == NULL) {
			cerr << "Error allocating memory needed to call GetAdaptersinfo" << endl;
		}
	}

	if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR) {
		pAdapter = pAdapterInfo;
		while (pAdapter) {
			cout<<"\n\tComboIndex: \t" << pAdapter->ComboIndex << endl;
			cout << "\tAdapter Name: \t" << pAdapter->AdapterName << endl;
			cout << "\tAdapter Desc: \t" << pAdapter->Description <<endl;
			cout << "\tAdapter Addr: \t";
			for (i = 0; i < pAdapter->AddressLength; i++) {
				if (i == (pAdapter->AddressLength - 1))
					printf("%.2X\n", (int)pAdapter->Address[i]);
				else
					printf("%.2X-", (int)pAdapter->Address[i]);
			}
			cout << "\tIP Address: \t" << pAdapter->IpAddressList.IpAddress.String << endl;
			cout << "\tIP Mask: \t" << pAdapter->IpAddressList.IpMask.String << endl;
			cout << "\tGateway: \t" <<pAdapter->GatewayList.IpAddress.String << endl;
			pAdapter = pAdapter->Next;
			
		}
	}
	else {
		cerr << "GetAdaptersInfo failed with error: " <<  dwRetVal<< endl;

	}
	if (pAdapterInfo)
		FREE(pAdapterInfo);

}

//-----------------------------------------------
//
//-----------------------------------------------
unordered_map<string, string> MyMACAddr::getAdapters()
{
	PIP_ADAPTER_INFO pAdapterInfo;
	PIP_ADAPTER_INFO pAdapter = NULL;
	DWORD dwRetVal = 0;

	unordered_map<string, string> result;
	stringstream temp;
	string str_mac;

	ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
	pAdapterInfo = (IP_ADAPTER_INFO *)MALLOC(sizeof(IP_ADAPTER_INFO));
	if (pAdapterInfo == NULL) {
		cerr << "Error allocating memory needed to call GetAdaptersinfo" << endl;
	}
	// Make an initial call to GetAdaptersInfo to get
	// the necessary size into the ulOutBufLen variable
	if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
		FREE(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO *)MALLOC(ulOutBufLen);
		if (pAdapterInfo == NULL) {
			cerr << "Error allocating memory needed to call GetAdaptersinfo\n" << endl;
		}
	}

	if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR) {
			pAdapter = pAdapterInfo;
			while (pAdapter) {
					for (UINT i = 0; i < pAdapter->AddressLength; i++) {
						temp << setfill('0') << setw(2) << hex << (int)pAdapter->Address[i];
						if (i != pAdapter->AddressLength - 1)
						{
							temp << "-";
						}
				
					}
			
					str_mac = temp.str();
					temp.str("");
					temp.rdbuf();
					for (auto&c : str_mac)
					{
						c = toupper(c);
					}
			
					result.insert({ pAdapter->Description, str_mac });

					pAdapter = pAdapter->Next;
			}
	}
	else {
		cerr << "GetAdaptersInfo failed with error: " << dwRetVal << endl;

	}
	if (pAdapterInfo)
		FREE(pAdapterInfo);
	
	
	return result;
}

//-----------------------------------------------
//
//-----------------------------------------------
void MyMACAddr::AssingRndMAC()
{
	//Copy Network interfaces to Vector
	vector <string> list;
	for (auto &itm : getAdapters())
	{
		list.push_back(itm.first);
	}

	cout << "\n[+]List of Available Adapters: " << endl;
	int range = 0;
	for (auto itm = list.begin(); itm != list.end(); itm++)
	{
		cout << '\t' << range + 1 << ")" << *itm << endl;
		range++;
	}

	cout << "[*]Selection: ";
	// Input validation
	int selection = 0;
	cin >> selection;
	if ( cin.fail() || (selection < 1) || (selection > range) )
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cerr << "[!]Invalid Selection Input!" << endl;
		return;
	}
	//-----------------------------------------------
	cout << "[-]Selected Adapter is: " << list.at(selection - 1) << '\n' << endl;


}
