#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;


void Deallocate ( char** arr, int size)
{
	for (int i = 0 ; i < size ; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;


}
int StringLenght(char* mystr)
{
	int lenght = 0;
	for (char* j = mystr; *j != '\0'; j++)
			lenght++;
	return lenght;

}

char* GetStringFromBuffer(char* buffer)
{
	//converts charecter array into pointer
	int strLen = StringLenght(buffer);
	char* str = 0;

	if (strLen > 0)
	{
		str = new char[strLen + 1];
		char* tempDest = str;
		for (char* tempSrc = buffer; *tempSrc != '\0'; tempSrc++, tempDest++)
		{
			*tempDest = *tempSrc;
		}
		*tempDest = '\0';
	}
	
	return str;
}


//this function checks whether the word can be fitted in the generated direction
bool Available(char** grid , char* word, int r, int c ,int row, int col, int TotalRows, int TotalCols, int size)
	{
		for (int i = row, j = col, k = 0; k < size; i += r, j += c, k++)
		{
			if (i >= TotalRows || j >= TotalCols || i < 0 || j < 0)
				return false;
			if (grid[i][j] != '*' && word[k] != grid[i][j] )
				return false;
		}
		return true;
	}

//this function fits word into grid by checking the availablity
bool SpaceCheck(char** grid , char* word, int r, int c ,int row, int col, int totalRows, int totalCols)
{
	
	int wordLength = StringLenght(word);
	if (Available(grid, word, r,c, row, col, wordLength, totalRows, totalCols) == true)
	{
		for (int i = row, j = col, k = 0; word[k] != '\0'; i += r, j += c,k++)
		{
			if (word[k] == grid[i][j] || grid[i][j] == '*')
			grid[i][j] = word[k];
		}
		return true;
	}
	return false;

}

//this function generates the grid and fits words into grid in different direction
//calls function to verify the available space for the words

char** GridMaker (char** words , int length, int rows, int cols)
{
	char** Grid = new char*[rows]; 
	for (int i = 0 ; i < rows ; i++)
	{//new char[cols+1]
		Grid[i] = new char[cols];       //for null character
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)						//initially storing asterik in the array
			Grid[i][j] = '*';
		//Grid[i][cols] = '\0';
	}
	
	int i = 0;
	int temp = length;
	srand(time(0));
	while ( temp !=0 )
	{
		int row = rand() % rows;
		int col = rand() % cols; 
		int direction = rand()% 8;
		switch (direction)
		{
			case 0: //horizontal left to right
			{
				
				bool fitWord = SpaceCheck(Grid, words[i], 0 , 1, row, col, rows, cols);
				if (fitWord)
				{
					i++;
					temp--;
				}
				break;
			}

			case 1: //vertically downward 			
			{
				bool fitWord = SpaceCheck(Grid, words[i], 1 , 0, row, col, rows, cols);
				if (fitWord)
				{
					i++;
					temp--;
				}
				break;
			}

			case 2: //horizontal  right to left
			{
				
				bool fitWord = SpaceCheck(Grid, words[i], 0 , -1, row, col, rows, cols);
				if (fitWord)
				{
					i++;
					temp--;
				}
				break;
			}

			
			case 3: //vertically upward 			
			{
				bool fitWord = SpaceCheck(Grid, words[i], -1 , 0, row, col, rows, cols);
				if (fitWord)
				{
					i++;
					temp--;
				}
				break;
			}
			case 4: //left to right diagonal  (down)
			{
				bool fitWord = SpaceCheck(Grid, words[i], 1 , 1, row, col, rows, cols);
				if (fitWord)
				{
					i++;
					temp--;
				}
				break;
			}
			case 5: //right to left diagonal (down)
			{
				bool fitWord = SpaceCheck(Grid, words[i], 1, -1, row, col, rows, cols);
				if (fitWord)
				{
					i++;
					temp--;
				}
				break;
			}

			case 6: //left to right diagonal  (up)
			{
				bool fitWord = SpaceCheck(Grid, words[i], -1 , 1, row, col, rows, cols);
				if (fitWord)
				{
					i++;
					temp--;
				}
				break;
			}
			case 7: //right to left diagonal (up)
			{
				bool fitWord = SpaceCheck(Grid, words[i], -1, -1, row, col, rows, cols);
				if (fitWord)
				{
					i++;
					temp--;
				}
				break;
			}


		}
		
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)											//filling spaces with random characters
		{
			if (Grid[i][j] == '*' ||  Grid[i][j] == ' ')
			{
				Grid[i][j]= (char)((rand() % 26) + 65);
			}
		}
	}
	return Grid;
}


// .............................................Find Words...........................................................

bool WordSearch(char* wordList, int** index, int i, int j,int k, int rows, int cols, int r, int c, char**Grid)
{
	bool found = true;
	int L = StringLenght(wordList);
	int m = i;
	int n = j;
	int l= 0;
	int count = 0;
	for ( ; l < L ; m+=r, n+=c)
	{
		if (m < 0 || m >= rows || n< 0 || n>=cols)
			return false;

		if (Grid[m][n] != wordList[l++])
		{
		return false;
		}
	}
	

	if (found)
	{
		index[k][0] = i;
		index[k][1] = j;
		index[k][2]= m;
		index[k][3] = n;
	}
	return found;
}


void main ()
{
	cout << "*****************************************************************************************************";
	cout << endl << endl;
	cout << "----------------------WELCOME TO THE WORD SEARCH GAME !!!! ------------------------------------------\n";
	cout << endl << endl;
	cout << "*****************************************************************************************************\n";
	char option;

	cout << "Please enter\n"
		 << "C -> To Create a Grid\n"
		 << "S -> To Search Words from a Grid\n"
		 << "Q -> To Quit Program\n";
	cin >> option;


	while (option != 'Q')
	{
	if (option == 'C')
	{

	cout << "CREATING YOUR GRID\n";
	string fileName; 
	ifstream fin;
	cout << "Please enter a file name to read words from: " ;
	cin.ignore();
	getline(cin, fileName);
	fin.open(fileName);

	cout << "Enter the number of words\n";
	int wordCount, rows, cols;
	cin >> wordCount;
	cout << "Enter number of rows and cols for your grid\n";
	cout << "It is recommended to keep the number of rows and cols greater or equal to the longest word in file\n";
	cin >> rows >> cols;
	
	
	char** wordList = new char*[wordCount];
	char tempBuffer[80];
	for (int i = 0; i < wordCount; i++)
	{
		char* word = 0;
		fin.getline(tempBuffer, 80);
		int StrLen = StringLenght(tempBuffer);
		word = GetStringFromBuffer(tempBuffer);
		 
		wordList[i] = new char[StrLen + 1];
		wordList[i] = word;
	}
	char ** grid = GridMaker(wordList, wordCount, rows, cols);
	fin.close();
	
	string fileName2;
	cout << "\nNow enter the name of file you want to display your GAME in\n";
	cout << "Do not forget to enter extension\n";
	cin.ignore();
	//getline(cin, fileName2); 
	cin>> fileName2;
	ofstream fout(fileName2);

	cout << "YOUR GRID HAS BEEN CREATED !!!\n Check Your file!!!\n";
	//displaying grid

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			fout << grid[i][j] << " ";
		}
		fout << endl;
	} 
	
	//deleting extra memory
	Deallocate(grid, rows);
	Deallocate(wordList, wordCount);
	}

	else if (option == 'S')
	{
		cout << "\n-------------------------------NOW SEARCHING FOR WORDS!!!----------------------------------------------\n";
		
		cout << "Enter the filename for grid\n";
		string grid;
		cin.ignore();
		getline(cin, grid);
		ifstream fin1 (grid);
		
		cout << "Enter the filename that contain words you want to search\n";
		string search;
		ifstream fin2(search);
		getline(cin, search);

		fin2.open(search);
		int rows, cols, wordCount;
		fin2 >> rows >> cols >> wordCount;
		char** Grid = new char*[rows]; 

		//reading grid
		for (int i = 0 ; i < rows ; i++)
		{
			Grid[i] = new char[cols + 1];       //for null character
		}

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)	//reading values for grid
				fin1 >> Grid[i][j];
			Grid[i][cols ] = '\0';
		}
	
			char buffer[80];
			char* words; 
			char** wordList = new char*[wordCount];

			for (int i = 0 ; i < wordCount; i++)
			{
				fin2 >> buffer;
				words = GetStringFromBuffer(buffer);
				wordList[i] = new char [StringLenght(words) + 1];
				wordList[i] = words;
			}

		int** index = new int*[wordCount]; //array to store index

		for (int i = 0 ; i < wordCount ; i++)
		{
			index[i] = new int [4];

		}
		for (int i = 0 ; i < wordCount ; i++)
		{
			for (int j = 0 ; j < 4 ; j++)
				index[i][j] = -1;
		}
		
		for (int i = 0 ; i < rows ; i++)
		{
			for (int j = 0 ; j < cols; j++)
			{
				for (int k = 0 ; k < wordCount ; k++)
				{
					if (WordSearch(wordList[k], index, i, j, k, rows, cols, 0, 1, Grid))
						break;
					else if (WordSearch(wordList[k], index, i, j, k, rows, cols, 1, 0, Grid))
						break;
					else if (WordSearch(wordList[k], index, i, j, k, rows, cols, 0, -1, Grid))
						break;
					else if (WordSearch(wordList[k], index, i, j, k, rows, cols, -1, 0, Grid))
						break;
					else if (WordSearch(wordList[k], index, i, j, k, rows, cols, 1, 1, Grid))
						break;
					else if (WordSearch(wordList[k], index, i, j, k, rows, cols, -1, -1, Grid))
						break;
					else if (WordSearch(wordList[k], index, i, j, k, rows, cols, 1, -1, Grid))
						break;
					else if (WordSearch(wordList[k], index, i, j, k, rows, cols, -1, 1, Grid))
						break;
				}
			}
		}
		string output;
		cout << "Enter the filename in which you want to see results\n";
		cin >> output;
		ofstream out(output);

		for (int i = 0 ; i < wordCount ; i++)
		{
				if(index[i][0] == -1)
				{
					cout << "WORD NOT FOUND !!!!";
					break;
				}
				else
				{
					cout << "{" << index[i][0] << "," << index[i][1] << "}" << endl <<
					"{" << index[i][2] << "," << index[i][3] << "}" <<endl ;

					out << "{" << index[i][0] << "," << index[i][1] << "}" << endl <<
					"{" << index[i][2] << "," << index[i][3] << "}" << endl;
				}	
		}

		//dealocating extra memory
		Deallocate(Grid, rows);
		Deallocate(wordList, wordCount);
		
	}
	cout << endl << endl;
	cout << "Please enter\n"
		 << "C -> To Create a Grid\n"
		 << "S -> To Search Words from a Grid\n"
		 << "Q -> To Quit Program\n";
		cin >> option;
}
	
	cout << endl;
	if(option == 'Q')
		cout << "\n PROGRAM TERMINATED\n";
	system("pause");

}


