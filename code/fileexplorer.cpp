#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <vector>

using namespace sf;
using namespace std;

// prototypes
// --------------------------------------------------------------------
string getNameFromFullPath(string pathParam);

//void populateDirectory(Directory& directoryParam);

filesystem::path getDirectoryPath();

// --------------------------------------------------------------------



// classes
// --------------------------------------------------------------------

// will be virtual
class Item
{
	public:

	// Note, the new keyword relies on there being a default constructor
	Item()
	{
	}
	
	Item(filesystem::path initPath)
	{
		location = initPath;
	}

	filesystem::path getDirectoryPath();

	string Item::getDirectoryPathStr();

	void printContents();
	

	protected:
		vector<Item*> contents;
		filesystem::path location;

};

class Directory : public Item
{
	public:
		Directory()
		{
		}
	
		Directory(filesystem::path initPath) : Item(initPath)
		{
			//location = initPath;
		}

		void populate();

	protected:
};
// --------------------------------------------------------------------

int main()
{
	filesystem::path currentDir = "/home/r/Desktop";
	//cout << currentDir;
	

	//Directory testDir("/home/r/Desktop");
	Directory testDir(currentDir);

	//filesystem::path testPathObj = testDir.getDirectoryPath();

	//cout << endl << testPathObj << endl;

	//Item testItem(currentDir);
	//testPathObj = testItem.getDirectoryPath();
	//cout << endl << testPathObj << endl;





	
	testDir.populate();
	testDir.printContents();

	







	
	VideoMode vm(1200, 675);

	RenderWindow window(vm, "File Explorer", Style::Close);

	// MAIN LOOP
	// ##########################################################################################
	/*
	while (window.isOpen())
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		window.clear();
		window.display();
	}
	*/
	// ##########################################################################################

	return 0;
}


// function defs
// --------------------------------------------------------------------

void Directory::populate()
{
	
	for (const filesystem::directory_entry & file : filesystem::directory_iterator(getDirectoryPath()))
	//for (auto & file : filesystem::directory_iterator(location))		// passing member var 'location' to a <filesystem> iterator which
																									// generates a filesystem::directory_entry object 
																									// (its identifier is "file", in the loop condition) for each thing
																									// in the location as the for loop goes through everything.

																									// The rest of the loop body is adding each thing to the member list
																									// named "contents".
	{
		//cout << getNameFromFullPath(file.path()) << endl;
		//if (filesystem::is_directory(getNameFromFullPath(file.path())))			// translation: is it a folder itself?
		if (filesystem::is_directory(file.path()))
		{
			Item* tempPtr = nullptr;
			tempPtr = new Directory(location);								
			contents.push_back(tempPtr);
			//cout << getNameFromFullPath(file.path()) << right << "\t\t\t" << "DIRECTORY ADDED" << endl;
		}

		else if (filesystem::is_symlink(file.path()))
		{
			Item* tempPtr = nullptr;
			tempPtr = new Directory(location);
			contents.push_back(tempPtr);
			//cout << "SYM LINK ADDED" << endl;
		}

		else	// if its anything other than a directory...
		{
			Item* tempPtr2 = new Item(location);
			contents.push_back(tempPtr2);
			//cout << getNameFromFullPath(file.path()) << right << "\t\t\t" << "MISCELLANEOUS THING ADDED" << endl;
		}
	}

}

filesystem::path Item::getDirectoryPath()
{
	return location;
}

string Item::getDirectoryPathStr()
{
	string holder = location.string();
	return holder;
}




string getNameFromFullPath(string pathParam)
{
    string returnVal = "";          // returnVal can be renamed maybe

    // Getting the name in reverse
    for (int index = pathParam.length(); index != 0; index--)
    {

        if (pathParam[index] != '/')
        {
            returnVal = returnVal + pathParam[index];

        }
        else
        {
            break;
        }
    }

    string returnVal2 = "";
    // Putting the name in the correct order
    for (int index = 0; index < returnVal.length(); index++)
    {
        returnVal2 = returnVal2 + returnVal[returnVal.length() - index];
    }

	// TEST OUTPUT
    //cout << returnVal2 << endl;

    return returnVal2;
}

void Item::printContents()
{
	cout << "test" << endl;
	for (int index = 0; index < contents.size(); index++)		// not working because loop condition referring to the wrong contents var
	{
		cout << "test2";	
		string holder = contents[index]->getDirectoryPathStr();
		cout << holder << endl;
		//cout << contents[index]->getDirectoryPathStr() << endl;
		//cout << contents[index]->getDirectoryPath() << endl;


		//string* temp = nullptr;
		//temp = &contents[index]->getDirectoryPath().string();
		//cout << *temp;
	}

	//cout << contents[0]->

}
