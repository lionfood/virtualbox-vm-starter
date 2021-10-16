#include <string>

using namespace std;

struct VM
{
	string name;
	string UID;

	VM(string name, string UID)
	{
		this->name = name;
		this->UID = UID;
	}
};
