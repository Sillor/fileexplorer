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

filesystem::path getPath();

// --------------------------------------------------------------------



// classes
// --------------------------------------------------------------------

// The generic parent class of everything: will be pure virtual at some point, though currently it isnt...
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

	// setter
	virtual void setIcon() {};		// UNDEFINED FOR NOW, will be used to determine which visual to use to represent the file/folder/sym link/whatever
	
	// getter
	filesystem::path getPath() const;		// returns a filesystem::path object for the thing
	string Item::getPathStr() const;		// returns a string containing the full path on the filesystem of the thing

	protected:
		filesystem::path location;			// filesystem::path object for the item
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

		// setter
		void populate();	// collects the things stored in the directory and saves them in the vector variable "location"

		// getter
		void printContents() const;		// print the names and paths of the things in the directory

		

	protected:
		vector<Item*> contents;			// contains a list of Item pointers for every item in the directory.
};

// the generic parent of all actual files, derives from Item..
class File : public Item
{	
	public:

		File()
		{
		}

		File(filesystem::path initPath) : Item(initPath)
		{
			// intentionally blank, can maybe just delete this constructor?
		}

		// setter
		void getFileType();
	
	protected:
		string fileType;

	
};
// --------------------------------------------------------------------



int main()
{
	cout << endl << endl << "------------------" << endl << endl;
	filesystem::path currentDir = "/home/r/Desktop";	// Set this directory to be something on your computer		
	Directory testDir(currentDir);

	testDir.populate();
	testDir.printContents();

	//string temp = getPathStr();

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
	for (const filesystem::directory_entry & file : filesystem::directory_iterator(getPath()))																												
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

filesystem::path Item::getPath() const
{
	return location;
}

string Item::getPathStr() const
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

void Directory::printContents() const
{
	for (int index = 0; index < contents.size(); index++)		
	{	
		string holder = contents[index]->getPathStr();
		cout << holder << endl;
	}
}

void getFileType()
{
	//string pathStr = getPath
	//system(file )

}
