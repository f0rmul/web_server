#include <iostream>
#include <drogon/drogon.h>
#include "InterfaceLayer/Controllers/UserHttpController.hpp"
#include "DomainLayer/Services/UserManagmentService.hpp"

using namespace std;

int main()
{
	try
	{	
		system("chcp 1251");
		cout << drogon::banner << endl;
		drogon::app().loadConfigFile("config.json").run();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	return 0;
}
