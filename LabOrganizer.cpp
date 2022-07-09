#include <iostream>
using namespace std;
#include "LabOrganizer.h"

//simple constructor
LabOrganizer::LabOrganizer()
{
    numberOfCabinets = 0;
}

//destructor
LabOrganizer::~LabOrganizer()
{
    if (numberOfCabinets)
        delete [] cabinets;
    numberOfCabinets = 0;
}

//function for adding cabinets
void LabOrganizer::addCabinet(int id, int rows, int columns)
{
    for (int i = 0; i < numberOfCabinets; ++i)
    {
        if (id == cabinets[i].getCabinetId())
        {
             cout << "Cannot add the cabinet: ID " << id << " already in the system" << endl;
             return;
        }
    }

    if( rows > 9 || columns > 9)
    {
        cout << "Cannot add the cabinet: dimensions are out of bound" << endl;
        return;
    }

    Cabinet *substitue = cabinets;
    cabinets = new Cabinet[numberOfCabinets + 1];

    for (int i = 0; i < numberOfCabinets; ++i)
    {
        cabinets[i].init(substitue[i].getCabinetId(), substitue[i].getCabinetRow(), substitue[i].getCabinetColumn());
    }

    cabinets[numberOfCabinets].init(id, rows, columns);

    numberOfCabinets++;

    //deletes the substitue
    if (numberOfCabinets != 1)
        delete [] substitue;

    cout << "Added a cabinet: ID " << id << " and dimensions " << rows << " to " << columns << endl;
}

//function for removing existing cabinets
void LabOrganizer::removeCabinet(int id)
{
    bool check = true;
    for (int i = 0; i < numberOfCabinets; ++i)
    {
        if (cabinets[i].getCabinetId() == id)
        {
            check = false;
        }
    }
    if (check)
    {
        cout<< "Cabinet "<< id << " does not exist in the system"<< endl ;
        return;
    }
    Cabinet *substitue = new Cabinet[numberOfCabinets - 1];
    int counter = 0;
    for (int i = 0; i < numberOfCabinets; ++i)
    {
        if( cabinets[i].getCabinetId() != id)
        {
            substitue[counter].init(cabinets[i].getCabinetId(), cabinets[i].getCabinetRow(), cabinets[i].getCabinetColumn());
            counter++;
        }
    }

    delete [] cabinets ;

    cabinets = substitue;
    numberOfCabinets--;
    cout<< "Cabinet " << id << " is removed" << endl;
}

//listing cabinets and their contents
void LabOrganizer::listCabinets()
{
    cout << "List of all cabinets:\n";
    for (int i = 0; i < numberOfCabinets; ++i)
        cout << "ID:" << cabinets[i].getCabinetId() << ", Dim: " << cabinets[i].getCabinetRow() << "x" << cabinets[i].getCabinetColumn() << ", Number of empty slots: " << cabinets[i].numberOfEmptySlots() << endl;
}

//listing cabinet contents in 2d table
void LabOrganizer::cabinetContents(int id)
{
    for (int i = 0; i < numberOfCabinets; ++i)
    {
        if (cabinets[i].getCabinetId() == id)
        {
            cout << "ID: " << cabinets[i].getCabinetId() << ", " << cabinets[i].getCabinetRow() << "x" << cabinets[i].getCabinetColumn() << ", empty: " <<  cabinets[i].numberOfEmptySlots() << endl;
            cout << " ";
            for(int j = 1; j < cabinets[i].getCabinetColumn() + 1; ++j)
                cout << j << " ";
            cout << endl;
            for(int k = 0; k < cabinets[i].getCabinetRow(); ++k)
            {
                cout << char(k + 65) << " ";
                for(int l = 0; l < cabinets[i].getCabinetColumn(); ++l)
                    cout << cabinets[i].cabinetArr[k][l].getChemicalName().at(0) << " ";
                cout << endl;
            }
        }
    }
}

//placing chemical
void LabOrganizer::placeChemical(int cabinetId, string location, string chemType, int chemID)
{
    int row;
    int column;
    int check = -1;
    for (int i = 0; i < numberOfCabinets; ++i)
    {
        if (cabinets[i].getCabinetId() == cabinetId)
        {
            check = i;
        }
        if(cabinets[i].isChemicalExist(chemID))
        {
            cout << "Chemical with ID " << chemID << " already exist in the system" << endl;
            return;
        }
    }

    if (check == -1)
    {
        cout<< "Cabinet "<< cabinetId << " does not exist in the system"<< endl ;
        return;
    }

    row = int(location.at(0)) - int('A');
    column = int(location.at(1)) - int('1');

    if (cabinets[check].checkAvailability(row, column))
    {
        if(chemType == "combustive")
        {
            if(cabinets[check].checkSafety(row, column))
            {
                cabinets[check].cabinetArr[row][column].setChemicalId(chemID);
                cabinets[check].cabinetArr[row][column].setChemicalName(chemType);
                cout << chemType << " chemical with ID " << chemID << " has been placed at location " << location << " in cabinet " << cabinetId << endl;
            }
        }else{
                cabinets[check].cabinetArr[row][column].setChemicalId(chemID);
                cabinets[check].cabinetArr[row][column].setChemicalName(chemType);
                cout << chemType << " chemical with ID " << chemID << " has been placed at location " << location << " in cabinet " << cabinetId << endl;
            }
    }else{
        string * arrSafe;
        arrSafe = cabinets[check].nearestSafePlaces(row, column);
        cout << "Location " << location << " in cabinet " << cabinetId << " is already occupied. Nearest possible locations for this chemical:" << arrSafe[0] << " " << arrSafe[1] << " " << arrSafe[2] << " " << arrSafe[3] << " " << arrSafe[4] << endl;
        return;
    }

}

//finding chemical in system
void LabOrganizer::findChemical(int id)
{
    for(int i = 0; i < numberOfCabinets; ++i)
    {
        for(int j = 0; j < cabinets[i].getCabinetRow(); ++j)
        {
            for(int k = 0; k < cabinets[i].getCabinetColumn(); ++k)
            {
                if(cabinets[i].cabinetArr[j][k].getChemicalId() == id)
                {
                    cout << "Chemical " << id << " is at location " << cabinets[i].locationStr(j, k) << " in cabinet " << cabinets[i].getCabinetId() << endl;
                    return;
                }
            }
        }
    }
}

//removing existing chemical
void LabOrganizer::removeChemical(int id)
{
    for(int i = 0; i < numberOfCabinets; ++i)
    {
        for(int j = 0; j < cabinets[i].getCabinetRow(); ++j)
        {
            for(int k = 0; k < cabinets[i].getCabinetColumn(); ++k)
            {
                if(cabinets[i].cabinetArr[j][k].getChemicalId() == id)
                {
                    cabinets[i].cabinetArr[j][k].setChemicalId(0);
                    cabinets[i].cabinetArr[j][k].setChemicalName("+");
                    cout << "Chemical " << id << " removed from cabinet " << cabinets[i].getCabinetId() << endl;
                    return;
                }
            }
        }
    }
    cout << "Chemical " << id << " is not in the system" << endl;
}


