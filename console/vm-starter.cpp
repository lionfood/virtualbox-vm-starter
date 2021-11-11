#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "tiny-process-library/process.hpp"
#include "vm.cpp"

using namespace std;
using namespace TinyProcessLib;

/// <summary>
/// Splits a string based on a given delimiter.
/// </summary>
/// <param name="value">the string to split</param>
/// <param name="delimiter">the delimiter to use</param>
/// <returns>A pointer to an std::vector&lt;std::string&gt;, each entry containing one part of the splitted string</returns>
vector<string>* split(string const &value, string delimiter)
{
	vector<string> *words = new vector<string>();
	size_t pos;
	string working_val = value;
	while ((pos = working_val.find(delimiter)) != string::npos)
	{
		words->push_back(working_val.substr(0, pos));
		working_val.erase(0, pos + delimiter.length());
	}
	if (working_val != "") { words->push_back(working_val); }
	return words;
}

/// <summary>
/// insert numberOfChars times the '0'-character in front of origin
/// </summary>
/// <param name="origin">the string to pad</param>
/// <param name="numberOfChars">how many characters should be used for padding</param>
void padNull(string *origin, size_t numberOfChars)
{
	origin->insert(0, numberOfChars, '0');
}

/// <summary>
/// the entrypoint of the application
/// 
/// Controles the console logic.
/// </summary>
/// <returns>0 if the processing was successfull</returns>
int main()
{

#ifdef _WIN32
	string VBOX_MANAGE_COMMAND = "\"C:\\Program Files\\Oracle\\VirtualBox\\VBoxManage.exe\""" list vms -s";
	string delimiter = "\r\n";
#else
	string VBOX_MANAGE_COMMAND = "VBoxManage list vms -s";
	string delimiter = "\n";
#endif

	string *output = new string("");

	auto stdout_handler = [output](const char *bytes, size_t n) { *output = string(bytes, n); };

	// start VBoxManage to list all known VMs
	Process process(VBOX_MANAGE_COMMAND, "", stdout_handler);
	int exit_status;
	while (!process.try_get_exit_status(exit_status))
	{
		// do nothing while process has not finished
	}


	// split the output by the linebreaks
	vector<string> *vm_strings = split(*output, delimiter);

	delete output;

	// display all vms
	int i = 0;
	vector<VM> vms{};
	string questionString = "[";

	/*
	 * initialize and fill our vms vector
	 * display all possibilities
	 */
	for (string val : *vm_strings)
	{
		vector<string> *vm = split(val.erase(0, 1), "\" ");
		vms.push_back(VM((*vm)[0], (*vm)[1]));
		cout << ++i << ".\t" << (*vm)[0] << endl;	//display number and name of VM
		questionString += to_string(i);
		questionString += ",";
	}
	questionString += "0]?";

	// display aborting possibility
	cout << "0" << ".\t" << "Exit Application" << endl;

	delete vm_strings;

	// let the user choose one vm
	cout << endl << "Please insert the number of an VM and press return to select and start it." << endl;
	cout << questionString << " ";

	// read the selected entry
	size_t selected = 0;
	cin >> selected;

	// if the user gives a value in the range of vms
	if (selected >= 1 && selected <= vms.size())
	{
#ifdef _WIN32
		string virtualBoxVM_Command = "start \"\" \"C:\\Program Files\\Oracle\\VirtualBox\\VirtualBoxVM.exe\"";
#else
		string virtualBoxVM_Command = "VirtualBoxVM";
#endif

		// start the vm without binding it to the current process
		string arguments = " --comment \"" + vms[selected - 1].name + "\" --startvm \"" + vms[selected - 1].UID + "\"";
		string command = virtualBoxVM_Command + arguments;
		std::system(command.c_str());
	}
	// show abort message
	else
	{
		cout << "Abort." << endl;
	}
	return 0;
}
