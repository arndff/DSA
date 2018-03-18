#include "Parser.h"

Parser::Parser(const char* file)
{
	if (!file)
	{
		throw std::runtime_error("An invalid file has been passed.\n");
	}
	else
	{
		std::ifstream in;
		in.open(file);
		if (!in) 
		{ 
			throw std::runtime_error("Problem with opening the file for reading.\n"); 
		}
		extractData(in); //read data from a binary file
		in.close();

		m_tree.balance();
		//assert(m_tree.isPerfectlyBalanced()); //works OK

		menu(); //a simple while loop for the task's menu
	}
}

void Parser::extractData(std::ifstream& in)
{
	int key;
	size_t len;
	char* data;

	size_t pos = 0;

	//the binary file should be structured this way:
	//{ key, len, string }

	while(true)
	{
		in.read((char*)&key, sizeof(key));
		if (in.eof()) { break; } //the while should break here after the last successfully read entry
		in.read((char*)&len, sizeof(len));
		data = new char[len + 1];
		in.read(data, len);
		data[len] = '\0';
	
		m_tree.insert(key, data);
		
		delete[] data;
	}
}

void Parser::menu()
{
	int key;

	const size_t MAX_DATA_LEN = 100;
	char data[MAX_DATA_LEN + 1];

	while (std::cin)
	{
		std::cout << "1. add <key> <data>\n";
		std::cout << "2. remove <key> <data>\n";
		std::cout << "3. removeall <key>\n";
		std::cout << "4. search <key> <data>\n\n";

		int option;
		do
		{
			std::cout << "enter an option: ";
			std::cin >> option;
			
			std::cout << "enter key: ";
			std::cin >> key;

			std::cin.ignore();

			if (option == 3)
			{
				size_t removed = m_tree.removeAll(key);
				
				if (removed == 1)
					std::cout << removed << " element has just been removed\n";
				else
					std::cout << removed << " elements have just been removed\n";
			}

			else
			{
				std::cout << "enter data: ";
				std::cin >> data;

				switch (option)
				{
					case 1: 
						m_tree.insert(key, data); 
						break;
					
					case 2: 
						(m_tree.remove(key, data)) ? std::cout << "true\n"
							                   : std::cout << "false\n";
						break;
					
					case 4: 
						(m_tree.find(key, data)) ? std::cout << "true\n"
							                 : std::cout << "false\n";
						break;
				}
			}
		}
		
		while (option < 1 || option > 4);

		std::cout << "\n";
	}
}
