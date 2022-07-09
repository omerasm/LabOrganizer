class Chemical{
public:
    Chemical();
    void init(int id, string name);
    bool isCombustive();
    int getChemicalId();
    string getChemicalName();
    void setChemicalId(int id);
    void setChemicalName(string name);

private:
    int ChemicalId;
    string ChemicalName;
};

