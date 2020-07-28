// FileInOut.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Player
{
private:


public:
	Player();
	~Player();

	char hp;
	char max_hp;
	char str;
	char def;

};

Player::Player()
{
}

Player::~Player()
{
}

int main()
{

	//string text;
	//string temp;
	//string num;
	//ifstream inFile;
	//Player play;
	//inFile.open("test.txt");
	//if (inFile.is_open())
	//{
	//	inFile.read((char *)& play, sizeof(play));
	//	
	//	//cout << play.str;
	//	/* 하나하나 읽어오기 
	//	while (getline(inFile, text)) 
	//	{
	//		cout << text << endl;
	//		int fin;
	//		fin = text.find(":");
	//		temp = "";
	//		num = "";
	//		for (int i = 0; i < fin; i++)
	//		{
	//			temp += text[i];
	//		}
	//		temp = text.substr(0, fin);
	//		num = text.substr(fin);
	//		double *input = nullptr;
	//		if (temp == "STR")
	//		{
	//			for (int i = fin + 1; i < text.length(); i++)
	//			{
	//				num += text[i];
	//			}
	//			input = &play.str;
	//			play.str =stod(num);
	//		}
	//		else if (temp == "DEF")
	//		{
	//			for (int i = fin + 1; i < text.length(); i++)
	//			{
	//				num += text[i];
	//			}
	//			play.def = stod(num);
	//		}
	//		else if (temp == "HP")
	//		{
	//			for (int i = fin + 1; i < text.length(); i++)
	//			{
	//				num += text[i];
	//			}
	//			play.hp = stod(num);
	//		}
	//		else if (temp == "MAX_HP")
	//		{
	//			for (int i = fin + 1; i < text.length(); i++)
	//			{
	//				num += text[i];
	//			}
	//			play.max_hp = stod(num);
	//		}
	//		*input = stod(num);
	//	}*/
	//}
	//inFile.close();
	//cout << "확인" << endl;
	//cout << play.str << " " << play.def << " " << play.hp << " " << play.max_hp;



	ofstream outFile;
	outFile.open("test.txt");
	//cin >> text;
	if (outFile.is_open())
	{
		//outFile << text;
		Player play;
		play.str = 10;
		play.def = 20;
		play.hp = 100;
		play.max_hp = 100;
		//outFile << "STR:"<<play.str << endl <<"DEF:"<< play.def << endl <<"HP:"<< play.hp << endl <<"MAX_HP:"<< play.max_hp ;
		outFile.write((char *)& play, sizeof(play));

	}
	else
	{
		cout << "실패";
	}
	outFile.close();


    return 0;
}



string text;
string temp;
string num;
ifstream inFile;
Player play;
inFile.open("test.txt");
if (inFile.is_open())
{
	inFile.read((char *)& play, sizeof(play));
	
	//cout << play.str;
	/* 하나하나 읽어오기 
	while (getline(inFile, text)) 
	{
		cout << text << endl;
		int fin;
		fin = text.find(":");
		temp = "";
		num = "";
		for (int i = 0; i < fin; i++)
		{
			temp += text[i];
		}
	
	}
	*/
}
inFile.close();
//cout << "확인" << endl;
//cout << play.str << " " << play.def << " " << play.hp << " " << play.max_hp;



/*
// C++ program to demonstrate read/write of class 
// objects in C++. 
#include <iostream> 
#include <fstream> 
#include <iostream>
#include <string>
using namespace std;

// Class to define the properties 
class Contestant {
public:
	// Instance variables 
	string Name;
	int Age, Ratings;

	// Function declaration of input() to input info 
	int input();

	// Function declaration of output_highest_rated() to 
	// extract info from file Data Base 
	int output_highest_rated();
};

// Function definition of input() to input info 
int Contestant::input()
{
	// Object to write in file 
	ofstream file_obj;

	// Opening file in append mode 
	file_obj.open("Input.txt", ios::app);

	// Object of class contestant to input data in file 
	Contestant obj;

	// Feeding appropriate data in variables 
	string str = "Micheal";
	int age = 18, ratings = 2500;

	// Assigning data into object 
	obj.Name = str;
	obj.Age = age;
	obj.Ratings = ratings;

	// Writing the object's data in file 
	file_obj.write((char*)&obj, sizeof(obj));

	// Feeding appropriate data in variables 
	str = "Terry";
	age = 21;
	ratings = 3200;

	// Assigning data into object 
	obj.Name = str;
	obj.Age = age;
	obj.Ratings = ratings;

	// Writing the object's data in file 
	file_obj.write((char*)&obj, sizeof(obj));

	return 0;
}

// Function definition of output_highest_rated() to 
// extract info from file Data Base 
int Contestant::output_highest_rated()
{
	// Object to read from file 
	ifstream file_obj;

	// Opening file in input mode 
	file_obj.open("Input.txt", ios::in);

	// Object of class contestant to input data in file 
	Contestant obj;

	// Reading from file into object "obj" 
	file_obj.read((char*)&obj, sizeof(obj));

	// max to store maximum ratings 
	int max = 0;

	// Highest_rated stores the name of highest rated contestant 
	string Highest_rated;

	// Checking till we have the feed 
	while (!file_obj.eof()) {
		// Assigning max ratings 
		if (obj.Ratings > max) {
			max = obj.Ratings;
			Highest_rated = obj.Name;
		}

		// Checking further 
		file_obj.read((char*)&obj, sizeof(obj));
	}

	// Output is the highest rated contestant 
	cout << Highest_rated;
	return 0;
}

// Driver code 
int main()
{
	// Creating object of the class 
	Contestant object;

	// Inputting the data 
	object.input();

	// Extracting the max rated contestant 
	object.output_highest_rated();

	return 0;
}
*/