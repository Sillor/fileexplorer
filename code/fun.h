//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <filesystem>
//#include <vector>
//#include <fstream>
//#include <unistd.h>  
//#include "fun.h"

using namespace std;
using namespace sf;


#ifndef FUN_H
#define FUN_H
struct itemInfo
{
	string fileType;
	string location;
	Texture icon;
	Texture* iconPtr;

	bool resizeNeeded = false;
	
};


//Color testColor(100.0, 100.0, 100.0);


// PROTOTYPES
// --------------------------------------------------------------------
string getNameFromFullPath(string pathParam);
//void populateDirectory(Directory& directoryParam);
filesystem::path getPath();
string parseFileData(fstream& fileInfoParam);

char* getNameFromFullPath_CStr(string pathParam);
bool thumbAlreadyExists(string folder, string file);
string getTitle(string titleParam);
string returnParentDirStr(string currentPath);


// --------------------------------------------------------------------

// CLASSES
// --------------------------------------------------------------------
class Item
{
	public:
		// constructors/destructor ------
		Item(filesystem::path initPath) { location = initPath; info.location = initPath; }
		~Item() { /*delete info.iconPtr* ???? ;*/ };
		// ------------------------------

		// setter -----------------------
		virtual void setIcon() = 0;								// UNDEFINED FOR NOW, will be used to determine which visual to use to represent the file/folder/sym link/whatever
		void setIconScreenCoords() {};
		void cleanTexture() { delete info.iconPtr; }
			
		// ------------------------------

		// getter -----------------------
		filesystem::path getPath() const;						// returns a filesystem::path object for the thing
		virtual itemInfo getInfo() const = 0;		// returns the full path on the filesystem of the thing and the file type
		Vector2f getIconScreenCoords() const {};
		// ------------------------------

		// void -------------------------
		virtual void openItem() const = 0;
		// ------------------------------								

	protected:
		// attributes -------------------
		filesystem::path location;								// filesystem::path object for the item
		Texture icon;
		Vector2f iconScreenCoords;

		itemInfo info;

		vector<Texture*> textureIcons;	
		// ------------------------------
};

struct coordInfo
{
	Vector2f topLeft; // = x + y
	Vector2f bottomLeft; // add 91 to y
	Vector2f topRight;    // add 91 to x
	Vector2f bottomRight; // add 91 to both

	//Item* thing;
};


coordInfo calculateSquare(int xPos, int yPos);		// LEAVE HERE

class Directory : public Item
{
	public:
		// constructors/destructor -----------------------------------
		Directory(filesystem::path initPath) : Item(initPath)  {/*coordinates.resize(1000);*/ }
		~Directory() {};
		// -----------------------------------------------------------

		// setter ---------------------------
		void populate();										// collects the things stored in the directory and saves them in the vector variable "location"
		virtual void setIcon() override;
		void setPath(string param) {location = param; info.location = param; contents.clear(); }
		void emptyCoordList() {coordinates.clear(); }
		// ----------------------------------

		// getter ---------------------------
		virtual itemInfo getInfo() const override;
		vector<coordInfo> getCoordinates() { return coordinates; }
		vector<Item*> getContents() { return contents; }
		// ----------------------------------

		// void -----------------------------
		void printContents() const;				// print the names and paths of the things in the directory
		void displayContents(RenderWindow& windowParam, RectangleShape& background, View& mainView);							// display the directory in the browser
		virtual void openItem() const override;
		// ----------------------------------

	protected:
		// attributes -----------------------
		vector<Item*> contents;	
		vector<coordInfo> coordinates;							// contains a list of Item pointers for every item in the directory.
		// Vector2i iconScreenCoords
		// ----------------------------------
};



// the generic parent of all actual files, derives from Item. Called GenericFile in UML diagram
class File : public Item
{	
	public:
		// constructors/destructor -------------------
		File(filesystem::path initPath);
		~File() {};
		// -------------------------------------------

		// setter ------------------------------------
		virtual void setIcon() override;
		// -------------------------------------------

		// getter ------------------------------------
		virtual itemInfo getInfo() const override;
		// -------------------------------------------

		// void --------------------------------------
		string getFileType();
		virtual void openItem() const override;
		// -------------------------------------------
	
	protected:
		// attributes --------------------------------
		string fileType;
		// -------------------------------------------
};
// --------------------------------------------------------------------

class ImageFile : public File				
{	
	public:
		// constructors/destructor -------------------
		ImageFile(filesystem::path initPath);
		~ImageFile() {};
		// -------------------------------------------

		// setter ------------------------------------
		virtual void setIcon() override;
		// -------------------------------------------

		// getter ------------------------------------
		virtual itemInfo getInfo() const override;
		// -------------------------------------------

		// void --------------------------------------
		string getFileType();
		virtual void openItem() const override;
		// -------------------------------------------
	
	protected:
		// attributes --------------------------------
		string fileType;
		// -------------------------------------------
};

class TextFile : public File				
{	
	public:
		// constructors/destructor -------------------
		TextFile(filesystem::path initPath);
		~TextFile() {};
		// -------------------------------------------

		// setter ------------------------------------
		virtual void setIcon() override;
		// -------------------------------------------

		// getter ------------------------------------
		virtual itemInfo getInfo() const override;
		// -------------------------------------------

		// void --------------------------------------
		string getFileType();
		virtual void openItem() const override;
		// -------------------------------------------
	
	protected:
		// attributes --------------------------------
		string fileType;
		// -------------------------------------------
};

class AudioFile : public File				
{	
	public:
		// constructors/destructor -------------------
		AudioFile(filesystem::path initPath);
		~AudioFile() {};
		// -------------------------------------------

		// setter ------------------------------------
		virtual void setIcon() override;
		// -------------------------------------------

		// getter ------------------------------------
		virtual itemInfo getInfo() const override;
		// -------------------------------------------

		// void --------------------------------------
		string getFileType();
		virtual void openItem() const override;
		// -------------------------------------------
	
	protected:
		// attributes --------------------------------
		string fileType;
		// -------------------------------------------
};

class VideoFile : public File				
{	
	public:
		// constructors/destructor -------------------
		VideoFile(filesystem::path initPath);
		~VideoFile() {};
		// -------------------------------------------

		// setter ------------------------------------
		virtual void setIcon() override;
		// -------------------------------------------

		// getter ------------------------------------
		virtual itemInfo getInfo() const override;
		// -------------------------------------------

		// void --------------------------------------
		string getFileType();
		virtual void openItem() const override;
		// -------------------------------------------
	
	protected:
		// attributes --------------------------------
		string fileType;
		// -------------------------------------------
};






#endif 