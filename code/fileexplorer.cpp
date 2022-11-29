#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>

using namespace sf;
using namespace std;

// prototypes
// --------------------------------------------------------------------
string getNameFromFullPath(string pathParam);

//void populateDirectory(Directory& directoryParam);

filesystem::path getPath();

string parseFileData(fstream& fileInfoParam);

// --------------------------------------------------------------------



// classes
// --------------------------------------------------------------------

// The generic parent class of everything: will be pure virtual at some point, though currently it isnt...
class Item
{
	public:

	// Dont think default constructor needed?
	//Item()
	//{
	//}
	
	Item(filesystem::path initPath)
	{
		location = initPath;
	}

	~Item() {};

	// setter
	virtual void setIcon() {};		// UNDEFINED FOR NOW, will be used to determine which visual to use to represent the file/folder/sym link/whatever
	
	// getter
	filesystem::path getPath() const;		// returns a filesystem::path object for the thing
	virtual string getPathStr() const;		// returns a string containing the full path on the filesystem of the thing

	protected:
		filesystem::path location;			// filesystem::path object for the item
		vector<Item*> contents;
};

class Directory : public Item
{
	public:
		//Directory()
		//{
		//}
	
		Directory(filesystem::path initPath) : Item(initPath)
		{	
		}

		~Directory() {};

		// void
		virtual void printContents() const;		// print the names and paths of the things in the directory

		// setter
		void populate();	// collects the things stored in the directory and saves them in the vector variable "location"

		// getter
		virtual string getPathStr() const;

		

	protected:
		//vector<Item*> contents;			// contains a list of Item pointers for every item in the directory.
};

// the generic parent of all actual files, derives from Item
class File : public Item
{	
	public:

		//File()
		//{
		//}

		File(filesystem::path initPath) : Item(initPath)
		{
			string pathStr = getPathStr();
			string command = "";				// command to pass to system() to get the file type info
			string quotes = "\"";	
			command = "file " + quotes + pathStr + quotes + " > \"system call output.txt\"";
			system(command.c_str());

			fstream fileInfo("system call output.txt");
			if (fileInfo.fail()) { cout << "FILE OPEN FAILURE << endl"; }

			fileType = parseFileData(fileInfo);
		}

		~File() {};

		// void
		void getFileType();
		//virtual void printContents() const;		// note to self: generates weird linker error, but dont need this anyway.
													// reason explained here: 
													// https://www.daniweb.com/programming/software-development/threads/114299/undefined-reference-to-vtable-for

		// getter
		virtual string getPathStr() const;
		
	
	protected:
		string fileType;

	
};
// --------------------------------------------------------------------



int main()
{
	cout << endl << endl << "------------------" << endl << endl;
	filesystem::path currentDir = "/home/r/Desktop/testDir";	// Set this directory to be something on your computer		
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
			Item* tempPtr2 = new File(file.path());
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

string Directory::getPathStr() const
{
	string holder = location.string();
	return holder;

}


string File::getPathStr() const
{
	string holder = location.string();
	return holder;

}


// Returns just the name of a file or a thing instead of its entire path
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
		//string holder = contents[index]->getPathStr();		
		//cout << holder << endl;
		
		cout << contents[index]->getPathStr() << endl;
	}
}



void File::getFileType()
{
	// just return the thing

}

// Analyses the file generated by the File class constructor and returns a string with the correct file type
string parseFileData(fstream& fileInfoParam)
{
	string fileDataStr = "";
	getline(fileInfoParam, fileDataStr);

	if (fileDataStr.find("PNG image data", 0) != string::npos)
	{
		//cout << "test1" << endl;
		fileDataStr = "png";
	}

	else if (fileDataStr.find("JPEG image data", 0) != string::npos)
	{
		//cout << "test2" << endl;
		fileDataStr = "jpeg";
	}

	else if (fileDataStr.find("ASCII text", 0) != string::npos)
	{
		//cout << "test3" << endl;
		fileDataStr = "txt";
	}

	else if (fileDataStr.find("Audio file with ID3", 0) != string::npos)
	{
		//cout << "test4" << endl;
		fileDataStr = "mp3";
	}

	else if (fileDataStr.find("ISO Media, MP4", 0) != string::npos)
	{
		//cout << "test5" << endl;
		fileDataStr = "mp4";
	}

	else 
	{
		cout << "undetected" << endl;
	}

	return fileDataStr;
}
