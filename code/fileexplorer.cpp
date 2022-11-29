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
			// intentionally blank, can maybe just delete this constructor?
		}

		void populate();	// collects the things stored in the directory and saves them in the vector variable "location"

	protected:
};
// --------------------------------------------------------------------

int main()
{
	cout << endl << endl << "------------------" << endl << endl;
	filesystem::path currentDir = "/home/r/Desktop";	// Set this directory to be something on your computer		
	Directory testDir(currentDir);

	testDir.populate();
	testDir.printContents();

	// The stuff you did is below, im just commenting it out temporarily
	// -------------------------------
	/*


	VideoMode vm(1200, 675);

	RenderWindow window(vm, "File Explorer", Style::Close);

	// MAIN LOOP
	// ##########################################################################################
	
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


// FUNCTION DEFS
// --------------------------------------------------------------------

// collects the things stored in the directory and saves them in the vector member with identifier "location"
void Directory::populate()
{
	
	// passing member var 'location' to a <filesystem> iterator which
	// generates a filesystem::directory_entry object 
	// (its identifier is "file", in the loop condition) for each thing
	// in the location as the for loop goes through everything.
	//
	// The rest of the loop body is adding each thing to the member list
	// named "contents".
	for (const filesystem::directory_entry & file : filesystem::directory_iterator(getDirectoryPath()))																												
	{			
		if (filesystem::is_directory(file.path()))		// translation: is it a folder itself?
		{
			Item* tempPtr = nullptr;								
			tempPtr = new Directory(file.path());	
			contents.push_back(tempPtr);
			//cout << getNameFromFullPath(file.path()) << right << "\t\t\t" << "DIRECTORY ADDED" << endl;
		}

		else if (filesystem::is_symlink(file.path()))
		{
			Item* tempPtr = nullptr;
			tempPtr = new Directory(file.path());
			contents.push_back(tempPtr);
			//cout << "SYM LINK ADDED" << endl;
		}

		else	// if its anything other than a directory...
		{
			Item* tempPtr2 = new Item(file.path());
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
    string reversedString = "";          

    // Getting the name in reverse
    for (int index = pathParam.length(); index != 0; index--)
    {

        if (pathParam[index] != '/')
        {
            reversedString = reversedString + pathParam[index];

        }
        else
        {
            break;
        }
    }

    string returnVal = "";
    // Putting the name in the correct order
    for (int index = 0; index < reversedString.length(); index++)
    {
        returnVal = returnVal + reversedString[reversedString.length() - index];
    }

	// TEST OUTPUT
    //cout << returnVal << endl;

    return returnVal;
}

void Item::printContents()
{
	for (int index = 0; index < contents.size(); index++)		
	{	
		string holder = contents[index]->getDirectoryPathStr();
		cout << holder << endl;
	}
}
