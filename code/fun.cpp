#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <unistd.h>
#include "fun.h"

// FUNCTION DEFS
// --------------------------------------------------------------------

string returnParentDirStr(string currentPath)
{
	string newStr = currentPath;

	int index = newStr.length() - 1;
	while (currentPath[index] != '/')
	{
		cout << "current str: " << newStr << endl;
		newStr = newStr.substr(0, newStr.length() - 1);
		cout << "new str: " << newStr << endl;
		cout << endl;
		index--;
	}	
	

	return newStr;
}

coordInfo calculateSquare(int xPos, int yPos)
{
	coordInfo returnSq;

	returnSq.topLeft.x = xPos;
	returnSq.topLeft.y = yPos;

	returnSq.bottomLeft.x = xPos;
	returnSq.bottomLeft.y = yPos + 91;

	returnSq.topRight.x = xPos + 91;
	returnSq.topRight.y =  yPos;

	returnSq.bottomRight.x = xPos + 91;
	returnSq.bottomRight.y = yPos + 91;

	return returnSq;
}

void Directory::displayContents(RenderWindow &windowParam, RectangleShape &background, View &mainView)
{
	Vector2f size = static_cast<Vector2f>(windowParam.getSize());
	mainView = View(FloatRect(0.f, 0.f, size.x, size.y));
	windowParam.setView(mainView);
	windowParam.draw(background);
	Vector2f itemCoords(0.0, 0.0);
	int horizontalWidth = size.x;
	int verticalWidth = size.y;
	vector<Vector2f> gridCoords;
	coordinates.clear();

	int yPos = 0;
	int xPos = 0;
	for (int index = 0; index < verticalWidth; index = index + 120)		// Determining locations on screen to print items
	{
		for (int subIndex = 0; subIndex < (horizontalWidth - 120 - 300); subIndex = subIndex + 120)
		{
			xPos = subIndex + 300;
			gridCoords.push_back(Vector2f(xPos, yPos + 45));						

			
			coordInfo itemSquare = calculateSquare(xPos, yPos + 45);
			try 
			{
				if (coordinates.size() < contents.size()) { coordinates.push_back(itemSquare); }	
			}
			catch(...) { cout << "ERROR" << endl; }
		}
		xPos = 0;
		yPos = index + 120;
		gridCoords.push_back(Vector2f(xPos, yPos));
	}

	for (int index = 0; index < contents.size(); index++)		// and now setting up and drawing everything to its location
	{
		try { contents.at(index)->setIcon(); } catch(...) {cout << "ERROR 1" << endl; }
		Sprite tempSprite;
		tempSprite.setTexture(*contents.at(index)->getInfo().iconPtr);
		try
		{
			try { tempSprite.setPosition(gridCoords.at(index)); } catch(...) {cout << "ERROR 2" << endl; }
			try {iconScreenCoords = gridCoords.at(index); } catch(...) {cout << "ERROR 3" << endl; }
			windowParam.draw(tempSprite);
			setUpAndDrawTextBox(iconScreenCoords, windowParam, index);
			try {contents.at(index)->cleanTexture(); } catch(...) {cout << "ERROR 4" << endl;}
		}
		catch (out_of_range &outOfRangeException) { cout << "ERROR 5" << endl; }
	}
}

void Directory::setUpAndDrawTextBox(Vector2f& iconScreenCoords, RenderWindow& windowParam, int& index)
{
	Text text; 
			string title;
			title = getTitle(contents.at(index)->getInfo().location);			
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

}

string getTitle(string titleParam)
{
	titleParam = getNameFromFullPath(titleParam);
	titleParam = titleParam.substr(0, 5);
	titleParam += "...";
	return titleParam;
}

void Directory::setIcon()
{
	info.iconPtr = new Texture;
	info.iconPtr->loadFromFile("images/folder.png"); // generic directory image																							
}

void File::setIcon()
{
	info.iconPtr = new Texture; 
	info.iconPtr->loadFromFile("images/folder.png");
}

void ImageFile::setIcon()
{
	info.iconPtr = new Texture; 
	info.iconPtr->loadFromFile("images/image.png");
}

void TextFile::setIcon() 
{
	info.iconPtr = new Texture; 
	info.iconPtr->loadFromFile("images/txt.png");
}

void AudioFile::setIcon()
{
	info.iconPtr = new Texture; 
	info.iconPtr->loadFromFile("images/audio.png");
}

void VideoFile::setIcon()
{
	info.iconPtr = new Texture; 
	info.iconPtr->loadFromFile("images/vid.png");
}

File::File(filesystem::path initPath) : Item(initPath)
{
	string pathStr = getInfo().location;
	string command = ""; 					// command to pass to system() to get the file type info
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
	string command = ""; 				// command to pass to system() to get the file type info
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
{
	string command = "eog ";
	command += info.location;
	system(command.c_str());
}

void AudioFile::openItem() const 
{
	string command = "vlc ";
	command += location.c_str();
	system(command.c_str());
}

void VideoFile::openItem() const
{
	string command = "mpv ";
	command += location.c_str();
	system(command.c_str());

}

void TextFile::openItem() const
{
	string command = "gedit ";
	command += location.c_str();
	system(command.c_str());
}

void Directory::populate()
{
	for (const filesystem::directory_entry &file : filesystem::directory_iterator(getPath()))
	{
		if (filesystem::is_directory(file.path())) 
		{
			Item *tempPtr = nullptr;
			tempPtr = new Directory(file.path());
			contents.push_back(tempPtr);
		}
		else if (filesystem::is_symlink(file.path()))
		{
			Item *tempPtr = nullptr;
			tempPtr = new Directory(file.path());
			contents.push_back(tempPtr);
		}
		else // if its anything other than a directory...
		{
			Item *tempPtr2 = new File(file.path());
			string fileType = tempPtr2->getInfo().fileType;
			if (fileType == "jpeg" || fileType == "png")
			{
				Item* tempPtr3 = new ImageFile(file.path());
				contents.push_back(tempPtr3);			
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
			else if (fileType == "undetected") { contents.push_back(tempPtr2); }
			else { contents.push_back(tempPtr2); }
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
	holder.location = location.string(); 
	holder.fileType = "directory";
	holder.icon = info.icon;
	return holder;
}

itemInfo AudioFile::getInfo() const
{
	itemInfo holder = info;
	holder.location = location.string(); 
	holder.fileType = "directory";
	holder.icon = info.icon;
	return holder;
}

itemInfo VideoFile::getInfo() const
{
	itemInfo holder = info;
	holder.location = location.string(); 
	holder.fileType = "directory";
	holder.icon = info.icon;
	return holder;
}

itemInfo TextFile::getInfo() const
{
	itemInfo holder = info;
	holder.location = location.string(); 
	holder.fileType = "directory";
	holder.icon = info.icon;
	return holder;
}

itemInfo Directory::getInfo() const
{
	itemInfo holder = info;
	holder.location = location.string(); 
	holder.fileType = "directory";
	holder.icon = info.icon;
	return holder;
}



itemInfo File::getInfo() const
{
	itemInfo holder = info;
	holder.location = location.string(); 
	holder.fileType = fileType;
	return holder;
}

void Directory::printContents() const
{
	for (int index = 0; index < contents.size(); index++)
	{
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
	return returnVal.c_str();
}

string File::getFileType()
{
}

// Analyses the file generated by the File class constructor and returns a string with the correct file type
string parseFileData(fstream &fileInfoParam)
{
	string fileDataStr = "";
	getline(fileInfoParam, fileDataStr);

	if (fileDataStr.find("PNG image data", 0) != string::npos)
	{
		fileDataStr = "png";
	}

	else if (fileDataStr.find("JPEG image data", 0) != string::npos)
	{
		fileDataStr = "jpeg";
	}

	else if (fileDataStr.find("ASCII text", 0) != string::npos)
	{
		fileDataStr = "txt";
	}

	else if (fileDataStr.find("Audio file with ID3", 0) != string::npos)
	{
		fileDataStr = "mp3";
	}

	else if (fileDataStr.find("ISO Media, MP4", 0) != string::npos)
	{
		fileDataStr = "mp4";
	}

	else
	{
		cout << "undetected" << endl;
	}

	return fileDataStr;
}