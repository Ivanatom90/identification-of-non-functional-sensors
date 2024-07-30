#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>
#include "domain.h"


namespace read {

using namespace std;

vector<string> ReadlineS(const std::string& str);
string GetTime(const string& str);
vector<double> ReadlineNum(const string& str);



class ParseSVRK{
public:
    ParseSVRK(std::string title_par, std::string title_kks, ostream& out);
    void ParseParameters(std::string title_par);
    void ParseKKS(std::string title_kks);
    std::string KKStran(std::string& str);

    std::vector<Parameter>& GetParameters();

private:
    Parameters parameters_;
    std::map<std::string, std::string> kks_translate_;
    ostream& out_;
};


//std::map<std::string, std::string> ParseKKS(const std::string& title);
}
