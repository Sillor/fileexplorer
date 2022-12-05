#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <unistd.h>  
#include "fun.h"

void Directory::displayContents(RenderWindow& windowParam, RectangleShape& background, View& mainView) 
{
	// adjusting the view to be same as window size
	Vector2f size = static_cast<Vector2f>(windowParam.getSize());
	mainView = View(FloatRect(0.f, 0.f, size.x, size.y));  // what does the .f do??
	windowParam.setView(mainView);

	windowParam.draw(background);
	Vector2f itemCoords(0.0, 0.0);

	// -------

	int horizontalWidth = size.x;
	int verticalWidth = size.y;
	vector<Vector2f> gridCoords;

	int yPos = 0;
	int xPos = 0;
	for (int index = 0; index < verticalWidth; index = index + 120)
	{
		for (int subIndex = 0; subIndex < (horizontalWidth - 120); subIndex = subIndex + 120)
		{
			xPos = subIndex;
			gridCoords.push_back(Vector2f(xPos, yPos));

			//cout << "subIndex:  " << (subIndex) << endl;
			//cout << "horizontalWidth: " << horizontalWidth << endl;
			//cout << endl << endl;
		}

		xPos = 0;
		yPos = index + 120;
		gridCoords.push_back(Vector2f(xPos, yPos));
	}

	 for (auto thing : gridCoords)
	{
		//cout << thing.x << "and " << thing.y;
		//cout << thing.y << endl;
		//cout << "\t";
	} 

	for (int index = 0; index < contents.size() - 1; index++)
	{
		contents.at(index)->setIcon();
		Sprite tempSprite;
		tempSprite.setTexture(*contents.at(index)->getInfo().iconPtr);
		
		tempSprite = contents.at(index)->resizeSprite(tempSprite);
		//cout << "OUT" << endl;

		try 
		{
			
			tempSprite.setPosition(gridCoords.at(index));
			windowParam.draw(tempSprite);
			contents.at(index)->cleanTexture();		// fixes memory leak
			//cout << "IN HERE" << endl;
		}
		catch (out_of_range& outOfRangeException) { cout << "ERROR" << endl; }
		
	}

}

void Directory::setIcon()
{
	info.iconPtr = new Texture;
	info.iconPtr->loadFromFile("/home/r/Pictures/Captures d’écran/Capture d’écran du 2022-12-04 00-41-38.png");	// generic directory image
	//textureIcons.push_back(info.iconPtr);

}

void File::setIcon()
{
	info.iconPtr = new Texture;		
	//info.iconPtr->loadFromFile("/home/r/Pictures/Captures d’écran/Capture d’écran du 2022-12-04 00-41-38.png");
	info.iconPtr->loadFromFile(getInfo().location);

	//textureIcons.push_back(info.iconPtr);
}

Sprite File::resizeSprite(Sprite& spriteParam)
{
	
	
	
	//Vector2f nativeScale = spriteParam.getScale();
	FloatRect w_h = spriteParam.getLocalBounds();		// this actually gets the resolution of the image
	int width = w_h.width;
	int height = w_h.height;
	//cout << info.location << ":\t" << "x: " << w_h.width << ", y: " << w_h.height << endl << endl;	


	float index = 0.95;

	// getting folder name from file name by deleting last part of the path -------------------
	int index2 = getInfo().location.length() - 1;
	string pathStr = getInfo().location;
	char character = pathStr[index2];
	while (character != '/')
	{
		pathStr = pathStr.substr(0, index2);
		index2--;
		character = pathStr[index2];
	}
	// -----------------------------------------------------------------------------------------

	// determining if a directory named ".file_explorer_thumbs" is present , making it if not --
	bool thumbsFolderPresent = false;
	for (auto & thing : filesystem::directory_iterator(pathStr))
	{
		cout << thing << endl;
		string stringToSearch = thing.path();
		if (stringToSearch.find(".file_explorer_thumbs", 0) != string::npos  )
		{
			thumbsFolderPresent = true;
			break;
		}
	}
	cout << "DONE" << endl;

	// creating the directory if it does not already exist
	if (thumbsFolderPresent == false)
	{
		string command = "mkdir ";
		command = command + pathStr;
		command = command + ".file_explorer_thumbs";
		cout << "COMMAND: " << command << endl;
		system(command.c_str());
	}
	// -----------------------------------------------------------------------------------------
	//thumbsFolderPresent = checkForThumbsFolder();

	// getting just the file name without the path
	
	
	for (auto & thing : filesystem::directory_iterator(pathStr))
	{
		/*
		string command2 = "cp ";
		command2 += thing.path();
		command2 += " /home/r/Desktop/testDir/.file_explorer_thumbs";
		*/

		// WORKS
		string commandX = "cd /home/r/Desktop/testDir/ && ";
		commandX += "convert \"4.jpg\" -resize 18% .file_explorer_thumb_4.jpg";

		// ALMOST WORKS
		
		string command2 = "cd ";
		command2 += pathStr;
		command2 += " && ";
		command2 += "convert ";
		//command2 += "\"";
		string name = getNameFromFullPath(thing.path());
		command2 += thing.path().c_str();
		//command2 += name;
		//command2 += "\"";
		command2 += " -resize 18% ";
		//command2 += "\"";
		command2 += ".file_explorer_thumb_";
		command2 += thing.path().filename().c_str();		// IT WORKS OMG OMG OMG 
		//command2 += name;
		//command2 += "\"";
		

		/*
		string command2 = "cd ";
		command2 += pathStr;
		command2 += " && ";
		command2 += "convert ";
		//command2 += "\"";
		//command2 += thing.path().c_str();		// this line not working
		command2 += getNameFromFullPath_CStr(thing.path());
		//command2 += "\"";
		command2 += " -resize 18% ";
		//command2 += "\"";
		command2 += ".file_explorer_thumb_";
		command2 += getNameFromFullPath_CStr(thing.path());;		// this line not working
		//command2 += "\"";
		*/

		if (commandX == command2)
			cout << "THEYRE TGHE SQME " << endl;
		

		/*
		string command2 = "convert ";
		//command2 += pathStr;
		command2 += thing.path();
		//command2 += "\"";
		command2 += " -resize 18% ";
		//command2 += "\"";
		command2 += pathStr;
		//command2 += ".file_explorer_thumbs/";
		string nameWithoutPath = getNameFromFullPath(getInfo().location);
		command2 += nameWithoutPath;
		//command2 += "\"";
		*/
		
		cout << "COMMAND X: " << commandX.c_str() << endl << endl;
		cout << "COMMAND 2 C String: " << command2.c_str() << endl << endl;
		cout << "COMMAND 2: " << command2 << endl << endl;
		system(command2.c_str());
		

		//string command3 = "convert ";
		//command3 += 
	}
	

	
	// while...
	
	
	
	
	 /* while (spriteParam.getGlobalBounds().width > 110)
	{
		spriteParam.setScale(index, index);
		width = width * 0.95;
		index = index - 0.02;


		FloatRect testRect = spriteParam.getGlobalBounds();
		float testWidth = testRect.width;
		float testHeight = testRect.height;

		//cout << testWidth << "  " << testHeight << endl;
	} */

	
	/* while (spriteParam.getGlobalBounds().height > 110)
	{
		spriteParam.setScale(index, index);
		width = width * 0.95;
		index = index - 0.02;


		FloatRect testRect = spriteParam.getGlobalBounds();
		float testWidth = testRect.width;
		float testHeight = testRect.height;

		//cout << testWidth << "  " << testHeight << endl;
	} */
	
	return spriteParam;
}

//bool checkForThumbsFolder()
//{
//	for (auto & thing : filesystem::directory_iterator(getInfo().info.))
//}


Sprite Directory::resizeSprite(Sprite& spriteParam)
{
	return spriteParam;
}






File::File(filesystem::path initPath) : Item(initPath)
		{
			string pathStr = getInfo().location;
			string command = "";				// command to pass to system() to get the file type info
			string quotes = "\"";	
			command = "file " + quotes + pathStr + quotes + " > \"system call output.txt\"";
			system(command.c_str());

			fstream fileInfo("system call output.txt");
			if (fileInfo.fail()) { cout << "FILE OPEN FAILURE << endl"; }

			fileType = parseFileData(fileInfo);
		}



void Directory::openItem() const
{

}

void File::openItem() const
{

}

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
			// will need to call functions to detect file type in here as well
			// so you arent creating a generic File object for each thing every time.
			// only do that if the file type cannot be determined.
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

/*
itemInfo Item::getInfo() const
{
	itemInfo holder;
	holder.location = location.string();
	holder.fileType = "";
	return holder;
}
*/

itemInfo Directory::getInfo() const
{
	itemInfo holder = info;
	holder.location = location.string();			// this line. 
	holder.fileType = "directory";
	holder.icon = info.icon;
	return holder;
}


itemInfo File::getInfo() const
{
	itemInfo holder = info;
	holder.location = location.string();		// this line
	holder.fileType = fileType;
	return holder;
}

void Directory::printContents() const
{
	for (int index = 0; index < contents.size(); index++)		
	{	
		//string holder = contents[index]->getPathStr();		
		//cout << holder << endl;
		
		//cout << contents[index]->getPathStr().location << "\t\t" << contents[index]->getPathStr().fileType << endl;
		cout << contents[index]->getInfo().fileType << ": " << endl;
		cout << contents[index]->getInfo().location << endl << endl;
	}
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

char* getNameFromFullPath_CStr(string pathParam)
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

    return returnVal.c_str();
}


string File::getFileType()
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
