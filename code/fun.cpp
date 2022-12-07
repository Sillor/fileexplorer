#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <unistd.h>
#include "fun.h"

// FUNCTION DEFS
// --------------------------------------------------------------------

void Directory::displayContents(RenderWindow &windowParam, RectangleShape &background, View &mainView)
{
	// adjusting the view to be same as window size
	Vector2f size = static_cast<Vector2f>(windowParam.getSize());
	mainView = View(FloatRect(0.f, 0.f, size.x, size.y));
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
		for (int subIndex = 0; subIndex < (horizontalWidth - 120 - 300); subIndex = subIndex + 120)
		{
			xPos = subIndex + 300;
			gridCoords.push_back(Vector2f(xPos, yPos + 45));

			// cout << "subIndex:  " << (subIndex) << endl;
			// cout << "horizontalWidth: " << horizontalWidth << endl;
			// cout << endl << endl;
		}

		xPos = 0;
		yPos = index + 120;
		//yPos += 300;
		gridCoords.push_back(Vector2f(xPos, yPos));
	}

	for (auto thing : gridCoords)
	{
		//cout << thing.x << "and " << thing.y;
		// cout << thing.y << endl;
		//cout << "\t";
	}

	for (int index = 0; index < contents.size(); index++)
	{
		contents.at(index)->setIcon();
		Sprite tempSprite;
		tempSprite.setTexture(*contents.at(index)->getInfo().iconPtr);

		try
		{
			//gridCoords.at(index).x += 300;
			tempSprite.setPosition(gridCoords.at(index));
			// and then save the coords permanently
			//iconScreenCoords.x += 300;
			iconScreenCoords = gridCoords.at(index);
			windowParam.draw(tempSprite);
			
			// text box
			Text text;
			string title = getTitle(contents.at(index)->getInfo().location);
			text.setString(title);
			Font font;
			text.setFillColor(Color(0, 0, 0));
			font.loadFromFile("fonts/Ubuntu-Light.ttf"); // light font for buttons
			text.setFont(font);
			Vector2f textScreenCoords(0.0, 0.0);
			textScreenCoords = iconScreenCoords;
			textScreenCoords.x += 20; textScreenCoords.y -= 20;
			float differential = 91.0;
			textScreenCoords.y = (iconScreenCoords.y + differential);
			text.setPosition(textScreenCoords);
			windowParam.draw(text);

			contents.at(index)->cleanTexture();
		}
		catch (out_of_range &outOfRangeException)
		{
		}
	}

	// delete info.iconPtr;
	// info.iconPtr = nullptr;
}

string getTitle(string titleParam)
{
	titleParam = getNameFromFullPath(titleParam);
	//cout << "TITLE: " << titleParam << endl;
	titleParam = titleParam.substr(0, 5);
	titleParam += "...";
	return titleParam;
}

void Directory::setIcon()
{
	info.iconPtr = new Texture;
	info.iconPtr->loadFromFile("images/folder.png"); // generic directory image
																								 // textureIcons.push_back(info.iconPtr);
}

void File::setIcon()
{
	info.iconPtr = new Texture; // This causes a memory leak if you run it long enough?
	info.iconPtr->loadFromFile("images/folder.png");
	// textureIcons.push_back(info.iconPtr);
}

void ImageFile::setIcon()
{
	info.iconPtr = new Texture; // This causes a memory leak if you run it long enough?
	//info.iconPtr->loadFromFile("/home/admin/Desktop/Capture_decran_du_2022-12-04_00-41-38.png");
	info.iconPtr->loadFromFile("images/image.png");

}

void TextFile::setIcon() 
{
	info.iconPtr = new Texture; // This causes a memory leak if you run it long enough?
	info.iconPtr->loadFromFile("images/txt.png");
}

void AudioFile::setIcon()
{
	info.iconPtr = new Texture; // This causes a memory leak if you run it long enough?
	info.iconPtr->loadFromFile("/images/audio.png");
}

void VideoFile::setIcon()
{
	info.iconPtr = new Texture; // This causes a memory leak if you run it long enough?
	info.iconPtr->loadFromFile("images/vid.png");
}

File::File(filesystem::path initPath) : Item(initPath)
{
	string pathStr = getInfo().location;
	string command = ""; // command to pass to system() to get the file type info
	string quotes = "\"";
	command = "file " + quotes + pathStr + quotes + " > \"system call output.txt\"";
	system(command.c_str());

	fstream fileInfo("system call output.txt");
	if (fileInfo.fail())
	{
		cout << "FILE OPEN FAILURE << endl";
	}

	fileType = parseFileData(fileInfo);
}

ImageFile::ImageFile(filesystem::path initPath) : File(initPath)
{
	/*
	string pathStr = getInfo().location;
	string command = ""; // command to pass to system() to get the file type info
	string quotes = "\"";
	command = "file " + quotes + pathStr + quotes + " > \"system call output.txt\"";
	system(command.c_str());

	fstream fileInfo("system call output.txt");
	if (fileInfo.fail())
	{
		cout << "FILE OPEN FAILURE << endl";
	}

	fileType = parseFileData(fileInfo);
	*/
}

AudioFile::AudioFile(filesystem::path initPath) : File(initPath)
{
	string pathStr = getInfo().location;
	string command = ""; // command to pass to system() to get the file type info
	string quotes = "\"";
	command = "file " + quotes + pathStr + quotes + " > \"system call output.txt\"";
	system(command.c_str());

	fstream fileInfo("system call output.txt");
	if (fileInfo.fail())
	{
		cout << "FILE OPEN FAILURE << endl";
	}

	fileType = parseFileData(fileInfo);
}

TextFile::TextFile(filesystem::path initPath) : File(initPath)
{
	string pathStr = getInfo().location;
	string command = ""; // command to pass to system() to get the file type info
	string quotes = "\"";
	command = "file " + quotes + pathStr + quotes + " > \"system call output.txt\"";
	system(command.c_str());

	fstream fileInfo("system call output.txt");
	if (fileInfo.fail())
	{
		cout << "FILE OPEN FAILURE << endl";
	}

	fileType = parseFileData(fileInfo);
}


VideoFile::VideoFile(filesystem::path initPath) : File(initPath)
{
	string pathStr = getInfo().location;
	string command = ""; // command to pass to system() to get the file type info
	string quotes = "\"";
	command = "file " + quotes + pathStr + quotes + " > \"system call output.txt\"";
	system(command.c_str());

	fstream fileInfo("system call output.txt");
	if (fileInfo.fail())
	{
		cout << "FILE OPEN FAILURE << endl";
	}

	fileType = parseFileData(fileInfo);
}


void Directory::openItem() const
{
}

void File::openItem() const
{
}

void ImageFile::openItem() const
{}

void AudioFile::openItem() const 
{}

void VideoFile::openItem() const
{}

void TextFile::openItem() const
{}

void Directory::populate()
{

	// passing member var 'location' to a <filesystem> iterator which
	// generates a filesystem::directory_entry object
	// (its identifier is "file", in the loop condition) for each thing
	// in the location as the for loop goes through everything.
	//
	// The rest of the loop body is adding each thing to the member list
	// named "contents".
	for (const filesystem::directory_entry &file : filesystem::directory_iterator(getPath()))
	{
		//string something = getNameFromFullPath(file.path());

		if (filesystem::is_directory(file.path())) // translation: is it a folder itself?
		{
			Item *tempPtr = nullptr;
			tempPtr = new Directory(file.path());
			contents.push_back(tempPtr);
			// cout << getNameFromFullPath(file.path()) << right << "\t\t\t" << "DIRECTORY ADDED" << endl;
		}

		else if (filesystem::is_symlink(file.path()))
		{
			Item *tempPtr = nullptr;
			tempPtr = new Directory(file.path());
			contents.push_back(tempPtr);
			// cout << "SYM LINK ADDED" << endl;
		}
		/*
		else if (fileType == "jpg")
		{
			Item* tempPtr = nullptr;
			tempPtr = new Image(file.path());
			contents.push_back(tempPtr);
		}
		*/

		else // if its anything other than a directory...
		{
			// will need to call functions to detect file type in here as well
			// so you arent creating a generic File object for each thing every time.
			// only do that if the file type cannot be determined.
			Item *tempPtr2 = new File(file.path());

			

			string fileType = tempPtr2->getInfo().fileType;
			cout << "fileType: " << fileType << endl;
			
			if (fileType == "jpeg" || fileType == "png")
			{
				Item* tempPtr3 = new ImageFile(file.path());
				contents.push_back(tempPtr3);			// seg error here
				delete tempPtr2;
			}
			
			else if (fileType == "mp3")
			{
				Item* tempPtr3 = new AudioFile(file.path());
				contents.push_back(tempPtr3);
				delete tempPtr2;
			}

			else if (fileType == "txt")
			{
				Item* tempPtr3 = new TextFile(file.path());
				contents.push_back(tempPtr3);
				delete tempPtr2;
			}

			else if (fileType == "mp4")
			{
				Item* tempPtr3 = new VideoFile(file.path());
				contents.push_back(tempPtr3);
				delete tempPtr2;
			}

			else if (fileType == "undetected")
			{
				contents.push_back(tempPtr2);
			}
			
			else 
			{
				contents.push_back(tempPtr2);
			}
		

			

			//contents.push_back(tempPtr2);

			// cout << getNameFromFullPath(file.path()) << right << "\t\t\t" << "MISCELLANEOUS THING ADDED" << endl;
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

//itemInfo File::Item::getInfo() const
itemInfo ImageFile::getInfo() const
{
	itemInfo holder = info;
	holder.location = location.string(); // this line.
	holder.fileType = "directory";
	holder.icon = info.icon;
	return holder;
}

itemInfo AudioFile::getInfo() const
{
	itemInfo holder = info;
	holder.location = location.string(); // this line.
	holder.fileType = "directory";
	holder.icon = info.icon;
	return holder;
}

itemInfo VideoFile::getInfo() const
{
	itemInfo holder = info;
	holder.location = location.string(); // this line.
	holder.fileType = "directory";
	holder.icon = info.icon;
	return holder;
}

itemInfo TextFile::getInfo() const
{
	itemInfo holder = info;
	holder.location = location.string(); // this line.
	holder.fileType = "directory";
	holder.icon = info.icon;
	return holder;
}

itemInfo Directory::getInfo() const
{
	itemInfo holder = info;
	holder.location = location.string(); // this line.
	holder.fileType = "directory";
	holder.icon = info.icon;
	return holder;
}



itemInfo File::getInfo() const
{
	itemInfo holder = info;
	holder.location = location.string(); // this line
	holder.fileType = fileType;
	return holder;
}

void Directory::printContents() const
{
	for (int index = 0; index < contents.size(); index++)
	{
		// string holder = contents[index]->getPathStr();
		// cout << holder << endl;

		// cout << contents[index]->getPathStr().location << "\t\t" << contents[index]->getPathStr().fileType << endl;
		cout << contents[index]->getInfo().fileType << ": " << endl;
		cout << contents[index]->getInfo().location << endl
			 << endl;
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
	// cout << returnVal << endl;

	return returnVal;
}

char *getNameFromFullPath_CStr(string pathParam)
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
	// cout << returnVal << endl;

	return returnVal.c_str();
}

string File::getFileType()
{
	// just return the thing
}

// Analyses the file generated by the File class constructor and returns a string with the correct file type
string parseFileData(fstream &fileInfoParam)
{
	string fileDataStr = "";
	getline(fileInfoParam, fileDataStr);

	if (fileDataStr.find("PNG image data", 0) != string::npos)
	{
		// cout << "test1" << endl;
		fileDataStr = "png";
	}

	else if (fileDataStr.find("JPEG image data", 0) != string::npos)
	{
		// cout << "test2" << endl;
		fileDataStr = "jpeg";
	}

	else if (fileDataStr.find("ASCII text", 0) != string::npos)
	{
		// cout << "test3" << endl;
		fileDataStr = "txt";
	}

	else if (fileDataStr.find("Audio file with ID3", 0) != string::npos)
	{
		// cout << "test4" << endl;
		fileDataStr = "mp3";
	}

	else if (fileDataStr.find("ISO Media, MP4", 0) != string::npos)
	{
		// cout << "test5" << endl;
		fileDataStr = "mp4";
	}

	else
	{
		cout << "undetected" << endl;
	}

	return fileDataStr;
}
