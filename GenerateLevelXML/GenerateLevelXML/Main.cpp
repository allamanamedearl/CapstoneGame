#include <iostream>
#include <fstream>
int main()
{
	using namespace std;
	int width = 20; //width
	int height = 20;//height
	ofstream myFile;
	myFile.open("LevelXMLStuff.txt");
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			cout << "<tile x=\""<<x<<"\" y=\""<<y<<"\" baseid=\"0\" walkable=\"true\"/>" << endl;
			myFile <<"\t<tile x=\"" << x << "\" y=\"" << y << "\" baseid=\"0\" walkable=\"true\"/>\n";
		}
	}
	myFile.close();
	cin.get();
	return 0;
}