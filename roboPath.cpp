#include<iostream>
#include<string>
#include<stdio.h>
using namespace std;
class Robot {
public:
char** arr;
int rows;
int cols;
int xpose;
int ypose;
char extra;
Robot(){};

Robot(char* filename)
{
	rows=1;
	cols=0;
	char x='a';
	FILE *ptr;
	ptr=fopen(filename,"r");
	while(x!='\n')						//counting columns
	{
		fscanf(ptr,"%c",&x);
			cols++;
		
	}
	rewind(ptr);
	while(!feof(ptr))					//counting rows
	{
		fscanf(ptr,"%c",&x);
		if(x=='\n')
			rows++;
		
	}
	arr = new char*[rows];				// allocating memory
	for(int i=0;i<rows;i++)
		arr[i]=new char[cols];


	rewind(ptr);						//file pointer setting curser at begining of the file
	fflush(stdin);
	for(int i=0;i<rows;i++)		
    {
        for(int j=0;j<cols;j++)          
        {
		fread(&arr[i][j],sizeof(char),1,ptr);
		if(arr[i][j]=='R')
		{
			xpose=i;					//stores the row number of Robot
			ypose=j;					//stores the column number of Robot
		}
		}
fread(&extra,sizeof(char),1,ptr);
	}
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			std::cout<<arr[i][j];		//Grid before finding the path
		}
	}
	std::cout<<"\n";
}


int findFridge()						//function for main
{
	recFunc(xpose,ypose);
	return 1;
}


int recFunc(int x,int y)				//extra function to perform recursion to find the path
{
	if((y-1)>=0 && (x-1)>=0 && (y+1)<cols && (x+1)<rows)
		if(arr[x-1][y]=='F'||arr[x][y-1]=='F'||arr[x][y+1]=='F'||arr[x+1][y]=='F')
			return 1;
		
	if((y-1)>=0 && (x-1)>=0 && (y+1)<cols && (x+1)<rows)
	{
		if(arr[x][y-1]==' ')			//checking for left (first priority)
		{
			arr[x][y-1]='R';
			if(recFunc(x,y-1)==1)
				return 1 ;
			else
				arr[x][y-1]=' ';
		}
		if(arr[x-1][y]==' ')			//checking for up
		{
			arr[x-1][y]='R';
			if(recFunc(x-1,y)==1)
				return 1;
			else 
				arr[x-1][y]=' ';
		}
		if(arr[x][y+1]==' ')			//checking for right
		{
			arr[x][y+1]='R';
			if(recFunc(x,y+1)==1)
				return 1;
			else
				arr[x][y+1]=' ';
		}
		if(arr[x+1][y]==' ')			//at end checking for down element
		{
			arr[x+1][y]='R';
			if(recFunc(x+1,y)==1)
				return 1;
			else 
				arr[x+1][y]=' ';
		}
		

	}
	return 0;							//in case ROBOT is trapped
}

void displayMap()
{
	cout<<"\n"<<"Path of Robot to Fridge\n\n";
	for(int i=0;i<rows;i++)
		{
			for(int j=0;j<cols;j++)
			{
				
				 std::cout<<arr[i][j];	//prints all characters including '\n'
			}
		}
}

};

int main(int argc, char** argv) { 
 Robot robot(argv[1]); //read in the input map file. 
 robot.findFridge(); //find the path to the fridge 
 robot.displayMap(); //display the map with the path that was found 
} 
