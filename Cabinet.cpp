#include <iostream>
#include <string>
using namespace std;
#include "Cabinet.h"

//simple constructor
Cabinet::Cabinet()
{
    cabinetId = 0;
    row = 0;
    column = 0;
}

//copy constructor
Cabinet::Cabinet(Cabinet &obj)
{
    cabinetId = obj.getCabinetId();
    row = obj.getCabinetRow();
    column = obj.getCabinetColumn();
    cabinetArr = new Chemical*[row];

    for (int i = 0; i < row; ++i)
    {
        cabinetArr[i] = new Chemical[column];

        for (int j = 0; j < column; ++j)
            cabinetArr[i][j] = obj.cabinetArr[i][j];
    }
}

//destructor
Cabinet::~Cabinet()
{
    if(cabinetId)
    {
        for ( int i = 0 ; i < row; ++i)
            delete [] cabinetArr[i];
        delete [] cabinetArr;
    }
}

//init functon
void Cabinet::init(int id, int rows, int columns)
{
    cabinetId = id;
    row = rows;
    column = columns;

    cabinetArr = new Chemical*[row];

    for (int i = 0; i < row; ++i)
    {
        cabinetArr[i] = new Chemical[column];
        for(int j = 0; j < column; ++j)
            cabinetArr[i][j] = Chemical();
    }
}

//getter for column
int Cabinet::getCabinetColumn()
{
    return column;
}

//getter for row
int Cabinet::getCabinetRow()
{
    return row;
}

//getter for id
int Cabinet::getCabinetId()
{
    return cabinetId;
}

//checks whether that position is available or not
bool Cabinet::checkAvailability(int rows, int columns)
{
    if ( cabinetArr[rows][columns].getChemicalName() == "+" )
        return true;
    return false;
}

//checks whether it is safe to put combustive chemical in that place
bool Cabinet::checkSafety(int rows, int columns)
{
    int rowStart = rows;
    int rowEnd = rows;
    int columnStart = columns;
    int columnEnd = columns;

    if( rows > 0 )
        rowStart = rows - 1;

    if( rows < row - 1 )
        rowEnd = rows + 1;

    if( columns > 0 )
        columnStart = columns - 1;

    if( columns + 1 < column - 1 )
        columnEnd = columns + 1;

    for(int i = rowStart; i < rowEnd + 1; ++i)
    {
        for(int j = columnStart; j < columnEnd + 1; ++j)
        {
            if(cabinetArr[i][j].isCombustive())
                return false;
        }
    }
    return true;
}

//if that position is not suitable looks for other available positions
string * Cabinet::nearestSafePlaces(int rows, int columns)
{
    static string arrS[100];
    int counter = 0;
    int rowStart = rows;
    int rowEnd = rows;
    int columnStart = columns;
    int columnEnd = columns;

    if( rows > 0 )
        rowStart = rows - 1;

    if( rows < row - 1 )
        rowEnd = rows + 1;

    if( columns > 0 )
        columnStart = columns - 1;

    if( columns + 1 < column - 1 )
        columnEnd = columns + 1;

    for(int i = rowStart; i < rowEnd + 1; ++i)
    {
        for(int j = columnStart; j < columnEnd + 1; ++j)
        {
            if(checkAvailability(i,j))
            {
                if(checkSafety(i, j))
                {
                    arrS[counter] = locationStr(i, j);
                    counter++;
                }
            }
        }
    }

    while(arrS[0] == "")
    {
        if( rowStart > 0 )
            rowStart--;
        if( rowEnd < row - 1 )
            rowEnd++;
        if( columnStart > 0 )
            columnStart--;
        if( columnEnd < column - 1 )
            columnEnd++;
        for(int i = rowStart; i < rowEnd + 1; ++i)
        {
            for(int j = columnStart; j < columnEnd + 1; ++j)
            {
                if(checkAvailability(i,j))
                {
                    if(checkSafety(i, j))
                    {
                        arrS[counter] = locationStr(i, j);
                        counter++;
                    }
                }
            }
        }
    }
    return arrS;
}

//returns positions with string from integers
string Cabinet::locationStr(int rows, int columns)
{
    string strRow;
    string strColumn;

    strRow = (char) (rows + 65);
    strColumn = to_string(columns + 1);

    return (strRow + strColumn);
}

int Cabinet::numberOfEmptySlots()
{
    int counter = 0;

    for(int i = 0; i < row; ++i)
    {
        for(int k = 0; k < column; ++k)
        {
            if(cabinetArr[i][k].getChemicalName() == "+" )
                counter++;
        }
    }
    return counter;
}

//checks whether chemical with certain id exist
bool Cabinet::isChemicalExist(int id)
{
    for(int i = 0; i < row; ++i)
    {
        for(int k = 0; k < column; ++k)
        {
            if(cabinetArr[i][k].getChemicalId() == id )
                return true;
        }
    }
    return false;
}
