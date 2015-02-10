#include <iostream>
#include <fstream>
int main()
{
	using namespace std;
	int width = 100; //width
	int height = 100;//height
	ofstream myFile;
	myFile.open("LevelXMLStuff.txt");
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			cout << "<tile x=\""<<x<<"\" y=\""<<y<<"\" baseid=\"0\" walkable=\"true\"/>" << endl;
			myFile <<"\t<tile x=\"" << x << "\" y=\"" << y << "\" baseid=\"0\" walkable=\"true\" npc=\"0\"/>\n";
		}
	}
	myFile.close();
	cin.get();
	return 0;
}