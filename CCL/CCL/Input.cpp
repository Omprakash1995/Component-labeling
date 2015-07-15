
#include<iostream>
#include<fstream>
#include<sstream>

using namespace std; 

unsigned char** bitmap;
int** labelmap;
int** contourmap;


int read_header(char* fn, int* pwidth, int* pheight, char* option)
{
	ifstream f(fn);
	stringstream ss;
	string inputLine;
	int  x, y, w = 0, h = 0;
	getline(f, inputLine);
	getline(f, inputLine);
	ss << f.rdbuf();
	ss >> w >> h;
	*pwidth = w ;
	*pheight = h ;
	cout << *pwidth << *pheight << endl;
	cout << w*h << endl;
	int nw = w % 2;
	int nh = h % 2;
	if (nw == 0 && nh == 0)
	{
		*pwidth += 2;
		*pheight += 2;
	}
	else if (nw != 0&&nh==0){
		*pwidth += 3;
		*pheight += 2;
	}
	else if (nh != 0&&nw==0)
	{
		*pheight += 3;
		*pwidth += 2;
	}
	else if (nw != 0 && nh != 0){
		*pwidth += 3;
		*pheight += 3;
	}
	bitmap = (unsigned char**)malloc(*pheight*sizeof(unsigned char*));
	labelmap = (int**)malloc(*pheight*sizeof(int*));

	if (option == "1")
	{
		contourmap = (int**)malloc(*pheight*sizeof(int*));
		if (bitmap == NULL || labelmap == NULL || contourmap == NULL)
		{
			f.close();
			return -2;
		}
	}
	else
	{
		if (bitmap == NULL || labelmap == NULL)
		{
			f.close();
			return -2;
		}
	}

	for (y = 0; y < *pheight; y++)
	{
		bitmap[y] = (unsigned char*)malloc(*pwidth*sizeof(unsigned char));
		labelmap[y] = (int*)malloc(*pwidth*sizeof(int));

		if (option == "1")
		{
			contourmap[y] = (int*)malloc(*pwidth*sizeof(int));
			if (labelmap[y] == NULL || bitmap[y] == NULL || contourmap == NULL)
			{
				f.close();
				return -2;
			}
		}

		else
		{
			if (bitmap[y] == NULL || labelmap[y] == NULL)
			{
				f.close();
				return -2;
			}
		}
		memset(bitmap[y], 0, *pwidth);
		memset(labelmap[y], 0, *pwidth*sizeof(int));
		if (option == "1") memset(contourmap[y], 0, *pwidth*sizeof(int));
	}
	if (nw == 0 && nh == 0)
	{
		for (y = 1; y <= *pheight - 2; y++)
		{
			for (x = 1; x <= *pwidth - 2; x++)
			{ 
				ss >> (unsigned char)bitmap[y][x];
				cout << bitmap[y][x];
			}
			cout << endl;
		}
	}
	else if (nw != 0&&nh==0)
	{

		for (y = 1; y <= *pheight - 2; y++)
		{
			for (x = 1; x <= *pwidth - 2; x++)
			{
				if (x == w + 1)
				{
					bitmap[y][x] = '0';
				}
				else
					ss >> (unsigned char)bitmap[y][x];
				cout << bitmap[y][x];
			}
			cout << endl;
		}
	}
	else if (nh != 0&&nw==0){
		for (y = 1; y <= *pheight - 2; y++)
		{
			for (x = 1; x <= *pwidth - 2; x++)
			{
				if (y == h + 1)
				{
					bitmap[y][x] = '0';
				}
				else
					ss >> (unsigned char)bitmap[y][x];
				cout << bitmap[y][x];
			}
			cout << endl;
		}
	}
	else if (nw != 0 && nh != 0)
	{
		for (y = 1; y <= *pheight - 2; y++)
		{
			for (x = 1; x <= *pwidth - 2; x++)
			{
				if (x == w + 1 || y == h + 1)
				{
					bitmap[y][x] = '0';
				}
				else
					ss >> (unsigned char)bitmap[y][x];
				cout << bitmap[y][x];
			}
			cout << endl;
		}
	}
	cout << endl;
	f.close();
	return 1;
}

