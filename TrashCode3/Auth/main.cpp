#include <iostream>
#include "AutherLibrary.h"

int main()
{
	AutherLibrary::Initialize("key1", "key2");

	std::string key; std::cout << "Enter key: "; std::cin >> key;

	if (AutherLibrary::Auth(key.c_str(), AutherLibrary::GetHwid()))
	{
		std::cout << "Loggined" << std::endl;
		std::cout << "Time left: " << AutherLibrary::ExpireDateHumanReadable() << std::endl;
		AutherLibrary::CreateLog(key, "Successful authorization!", "Login");
	}
}