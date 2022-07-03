#include<iostream>
#include<vector>
#include<chrono>
#include<cmath>
#include<unistd.h>
using namespace std;
using namespace std::chrono;

vector<vector<int>> grid;
int numbers;
int no_of_groups;
long solve_duration;

void NOT_SOVABLE_MSG()
{
	system("clear");
	cout<<"Time taken: "<<solve_duration<<" microseconds"<<endl;
	cout<<"Sudoku not solvable"<<endl;
}

bool IS_EMPTY(int entry)
{
	if(entry==0)
		return true;
	else
		return false;
}

/*INPUT - 'row' in which 'num' is searched
  OUTPUT - returns true if 'num' is present in row 'row' else false*/
bool IS_PRESENT_ROW(int row, int num)
{
	for(int i=0;i<numbers;i++)
	{
		if(grid[row][i] == num)
			return true;
	}
	return false;
}

/*INPUT - 'column' in which 'num' is searched
  OUTPUT - returns true if 'num' is present in column 'column' else false*/
bool IS_PRESENT_COLUMN(int column, int num)
{
	for(int i=0;i<numbers;i++)
	{
		if(grid[i][column] == num)
			return true;
	}
	return false;
}

bool IS_PRESENT_BOX(int row_begin, int column_begin, int num)
{
	int row_end = row_begin + no_of_groups - 1;
	int column_end = column_begin + no_of_groups - 1;

	for(int i=row_begin;i<=row_end;i++)
	{
		for(int j=column_begin;j<=column_end;j++)
			if(grid[i][j] == num)
				return true;
	}
	return false;
}

/*returns true if num is a candidate for the position grid[row][column]
  it is a candidate if num is not present in that row and column and box*/
bool IS_SAFE(int row, int column, int num)
{
	if(!IS_PRESENT_ROW(row, num) && 
	   !IS_PRESENT_COLUMN(column, num) && 
	   !IS_PRESENT_BOX(no_of_groups*(row/no_of_groups), no_of_groups*(column/no_of_groups), num))
		return true;
	else 
		return false;
}

/*returns true if the sudoku could be solved with the present entries*/
bool SOLVE()
{
	for(int row=0;row<numbers;row++)
	{
		for(int column=0;column<numbers;column++)
		{
			if(IS_EMPTY(grid[row][column]))
			{
				for(int i=1;i<=numbers;i++)
				{
					if(IS_SAFE(row, column, i))
					{
						grid[row][column] = i;
						if(SOLVE())
							return true;
						else
							grid[row][column] = 0;
					}
				}
				return false;
			}
		}
	}
	return true;
}

void PRINT()
{
	system("clear");
	cout<<"Time taken: "<<solve_duration<<" microseconds"<<endl;
	cout<<"SOLVED SUDOKU"<<endl;
	for(int i=0;i<numbers;i++)
	{
		if(i%no_of_groups == 0)
			cout<<endl;
		for(int j=0;j<numbers;j++)
		{
			if(j%no_of_groups == 0)
				cout<<" ";
			cout<<grid[i][j]<<" ";
		}
		cout<<endl<<endl;
	}
}

void PLAY()
{
	bool result;
	auto start = high_resolution_clock::now();
	result = SOLVE();
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	solve_duration=duration.count();
	
	if(result==true)
		PRINT();
	else
		NOT_SOVABLE_MSG();
}

void GET_GRID()
{
	cout<<"Enter the values in the grid"<<endl;
	cout<<"Note: Enter the elemnts row wise ie enter the first row completely then the second row and so on"<<endl;
	cout<<"For empty entries enter 0 as the number"<<endl;

	vector<int> temp_vector;
	int temp;
	for(int i=0;i<numbers;i++)
	{
		for(int j=0;j<numbers;j++)
		{
			cin>>temp;
			temp_vector.push_back(temp);
		}
		grid.push_back(temp_vector);
		temp_vector.clear();
	}
}

void INTRO_MSG()
{
	system("clear");
	cout<<"Your sudoku contains numbers from 1-n"<<endl;
	cout<<"n should be a perfect square"<<endl;
	cout<<"Enter the number n: ";
	cin>>numbers;
}

int main()
{
	double groups;
	while(1)
	{
		INTRO_MSG();

		groups = sqrt(numbers);
		if(groups-floor(groups)>0)
		{
			cout<<"Try entering a valid number"<<endl;
			cout<<"Hint: The number should be a perfect square"<<endl;
			sleep(5);
		}
		else
		{
			break;
		}
	}
	no_of_groups = (int)groups;
	GET_GRID();
	PLAY();
}
