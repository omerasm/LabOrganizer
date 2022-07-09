#include "Chemical.h"

class Cabinet{
public:
    Cabinet();
    Cabinet(Cabinet &obj);
    ~Cabinet();
    void init(int id, int rows, int columns);
    int getCabinetColumn();
    int getCabinetRow();
    int getCabinetId();
    bool checkAvailability(int rows, int columns);
    bool checkSafety(int rows, int columns);
    string * nearestSafePlaces(int rows, int columns);
    string locationStr(int rows, int columns);
    int numberOfEmptySlots();
    bool isChemicalExist(int id);

    Chemical **cabinetArr;
private:
    int cabinetId;
    int row;
    int column;
};
