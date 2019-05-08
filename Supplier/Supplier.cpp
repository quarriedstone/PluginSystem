// Supplier.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <windows.h>
#include <string> 
#include <string.h> 
#include <list>
#define SERVICE
#include "../api.h"
#include "../plugin_id.h"

typedef struct _DllListElement
{
	GUID pluginId;
	const wchar_t* DllName;
	pfn_GetCopyright GetCopyright;
} DllListElement;

std::list<DllListElement> g_DllList = {
	{ plugin1_id, L"Plugin1_2.dll", nullptr },
	{ plugin2_id, L"Pugin2.dll", nullptr }
};


int main()
{
	DWORD i = 0;
	HKEY hKey = NULL;
	LPCTSTR strKeyName = TEXT("SOFTWARE\\PluginSystem");

	// Writing
	for (DllListElement element : g_DllList) {
		// Make string from GUID
		wchar_t register_value[256] = L"\0";
		wchar_t* string;
		IID guid;

		StringFromIID(element.pluginId, &string);
		printf("GUID is %S \n", string);

		// Make GUID from string
		const auto res2 = IIDFromString(string, &guid);
		if (res2 != S_OK) {
			printf("Enable to convert %S to GUID \n", string);
			return NULL;
		}

		wcscat_s(register_value, 256, element.DllName);

		//////////////////////////////////////////////////////////////////////////////////
		LPCTSTR value = (LPCTSTR) string;

		//Open the key
		long sts = RegOpenKeyEx(HKEY_CURRENT_USER, strKeyName, 0, KEY_ALL_ACCESS, &hKey);

		//If failed, create the key
		if (ERROR_NO_MATCH == sts || ERROR_FILE_NOT_FOUND == sts)
		{
			std::wcout << "Creating registry key " << strKeyName << std::endl;

			LONG j = RegCreateKeyEx(HKEY_CURRENT_USER, strKeyName, NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);

			if (ERROR_SUCCESS != j)
				std::wcout << "Error: Could not create registry key " << strKeyName << std::endl << "\tERROR: " << j << std::endl;
			else
				std::wcout << "Success: Key created" << std::endl;

		}
		else if (ERROR_SUCCESS != sts)
		{
			std::wcout << "Cannot open registry key " << strKeyName << std::endl << "\tERROR: " << sts << std::endl;

		}

		// Setting value 
		LONG st = RegSetValueEx(hKey, value, 0, REG_SZ, (LPBYTE)register_value, wcslen(register_value) * sizeof(wchar_t));

		if (ERROR_SUCCESS != st)
			std::wcout << "Error: Could not write to registry key " << strKeyName << std::endl << "\tERROR: " << st << std::endl;
		else
			std::wcout << "Success: value: " << register_value << " was written" << std::endl;

		i++;
	}

	RegCloseKey(hKey);
}

//// Splitting values from string
//wchar_t *guid_str, *plugin_nam;
//wchar_t* buffer;
//guid_str = wcstok_s(register_value, L":", &buffer);
//plugin_nam = wcstok_s(NULL, L":", &buffer);
//
//printf("%S\n", guid_str);
//printf("%S\n", plugin_nam);


//// Checking 
	//std::cout << std::endl;
	//for (DllListElement element : g_DllList)
	//{
	//	std::wcout << element.DllName << std::endl;
	//}

	//for (auto i = begin(g_DllList); i != end(g_DllList); i++)
	//{
	//	auto element = *i;
	//	if (IsEqualGUID(element.pluginId, guid))
	//	{
	//		*i = DllListElement({ guid, L"sosat", nullptr });
	//	}
	//}

	//for (DllListElement element : g_DllList)
	//{
	//	std::wcout << element.DllName << std::endl;
	//}

// Reading
//wchar_t data[256];
//DWORD size = sizeof(data);
//DWORD type = REG_SZ;
//
//LONG nError = RegQueryValueEx(hKey, value, NULL, &type, (LPBYTE)data, &size);
//
//if (nError != ERROR_SUCCESS)
//std::wcout << "Cannot read registry key " << strKeyName << std::endl << "\tERROR: " << sts << std::endl;
//else
//std::wcout << "Success: value: " << data << " was read" << std::endl;
//If it already existed, get the value from the key.


//// Reading
	//HKEY hKey = NULL;
	//LPCTSTR strKeyName = TEXT("SOFTWARE\\OtherTestSoftware");
	//DWORD type = REG_SZ;
	////Open the key
	//long sts = RegOpenKeyEx(HKEY_CURRENT_USER, strKeyName, 0, KEY_ALL_ACCESS, &hKey);
	//
	//DWORD cValues;              // number of values for key 
	//DWORD cbMaxValueData;       // longest value data 
	//DWORD retCode;
	//DWORD cchValue = 16383;
	//wchar_t guid_string[256];
	//wchar_t buffer[256];

	//retCode = RegQueryInfoKey(
	//	hKey,                    // key handle 
	//	NULL,                // buffer for class name 
	//	NULL,           // size of class string 
	//	NULL,                    // reserved 
	//	NULL,               // number of subkeys 
	//	NULL,            // longest subkey size 
	//	NULL,            // longest class string 
	//	&cValues,                // number of values for this key 
	//	NULL,            // longest value name 
	//	&cbMaxValueData,         // longest value data 
	//	NULL,   // security descriptor 
	//	NULL);

	//for (DWORD i = 0, retCode = ERROR_SUCCESS; i < cValues; i++) {
	//	cchValue = 16383;
	//	guid_string[0] = '\0';

	//	DWORD lpData = cbMaxValueData;
	//	buffer[0] = '\0';

	//	retCode = RegEnumValueA(hKey, i,
	//		(LPSTR)guid_string,
	//		&cchValue,
	//		NULL,
	//		NULL,
	//		(LPBYTE)buffer,
	//		&lpData);
	//	
	//	if (retCode == ERROR_SUCCESS) {
	//		wprintf(L"Success: %S %S was read\n", guid_string, buffer);
	//	}
	//}

	/*LONG nError = RegQueryValueEx(hKey, value, NULL, &type, (LPBYTE)data, &size);

	if (nError != ERROR_SUCCESS)
	std::wcout << "Cannot read registry key " << strKeyName << std::endl << "\tERROR: " << sts << std::endl;
	else
	std::wcout << "Success: value: " << data << " was read" << std::endl;
	If it already existed, get the value from the key.
*/
