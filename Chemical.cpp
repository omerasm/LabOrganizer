#include <iostream>
using namespace std;
#include "Chemical.h"

//simple chemical constructor
Chemical::Chemical()
{
    ChemicalId = 0;
    ChemicalName = "+";
}

//checks whether chemical is combustive or not
bool Chemical::isCombustive()
{
    if(ChemicalName == "combustive")
        return true;
    return false;
}

//initializes the chemical with given values
void Chemical::init(int id, string name)
{
    ChemicalId = id;
    ChemicalName = name;
}

//getter for chemical id
int Chemical::getChemicalId()
{
    return ChemicalId;
}

//getter for chemical name
string Chemical::getChemicalName()
{
    return ChemicalName;
}

//setter for chemical id
void Chemical::setChemicalId(int id)
{
    ChemicalId = id;
}

//setter for chemical name
void Chemical::setChemicalName(string name)
{
    ChemicalName = name;
}
