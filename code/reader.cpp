#include "reader.h"

namespace read {


vector<string> ReadlineS(const string& str)
{
    vector <string> strv_v;
    strv_v.reserve(129);
    string_view sv = str;
    size_t space = sv.find('|');
    sv.remove_prefix(space + 1);
    while(true){
        space = sv.find('|');
        string_view a = sv.substr(0, space);
        strv_v.push_back(string(a));
        if(space != sv.npos){
            sv.remove_prefix(space+1);
        } else {
            break;
        }

    }

return strv_v;
}

string GetTime(const string& str){
    string_view s = str;
    int space = s.find('|');
    return {string(s.substr(0, space))};
}


vector<double> ReadlineNum(const string& str)
{
    string_view s = str;
    vector <double> num;
    vector<string_view> v_str;
    int space = s.find('|');
    s.remove_prefix(space);
    while(true){
        size_t space = s.find('|');
        string_view sp = s.substr(space+1);
        size_t num_border = sp.find_first_of(' ');
        sp.remove_suffix(sp.size() - num_border);
        v_str.push_back(sp);
        if(space == s.npos){
            break;
        } else {
            s.remove_prefix(space+1);
        }
    }

    for_each(v_str.begin(), v_str.end(), [&num](string_view text){
        if((text[0]>='0' && text[0] <= '9') || text[0]=='-'){
            num.push_back(stod(string(text)));
        }
    });

return num;
}


ParseSVRK::ParseSVRK(std::string title_par, std::string title_kks, ostream& out): out_(out){
    ParseKKS("input_names/" + title_kks);
    ParseParameters("input_data/" + title_par);
}

void ParseSVRK::ParseParameters(std::string title_par){
    ifstream file(title_par);
    string str;
        for (int i=0; i<5; i++)
        {
            out_<<str<<endl;
            getline(file, str);
        }
    vector<string> KKS =  ReadlineS(str);
    KKS.pop_back();

    vector<vector<double>> parameters;
    parameters.resize(KKS.size());
    while (getline(file, str))
    {
        int i = 0;
        for (const double& num:ReadlineNum(str)){
            parameters[i].push_back(num);
            i++;
        }
    }

    int i = 0;
    for(std::vector<double>& numbers:parameters){
            parameters_.push_back(Parameter{KKS[i], KKStran(KKS[i]), std::move(numbers), 0.00});
        i++;
    }
}

std::string ParseSVRK::KKStran(std::string& str){
    try {
        return kks_translate_.at(str);
    }  catch (exception& ex) {
        std::cout<<str<<" not_find_in_map  "<<ex.what()<<endl;
        return "name_not_found"s;
    }
}


void ParseSVRK::ParseKKS(std::string title_kks){
    ifstream file(title_kks);
    string s;
    string KKS_s;
    string name;
    for (int i=0;i<5;i++)
    {
        getline(file, s);
    }

    while(getline(file, s))
    {
        string_view str = s;
        int space = str.find('|');
        KKS_s = str.substr(0, space-1);
        str.remove_prefix(space+1);
        space = str.find('|');
        name = str.substr(0, space);
        //datchics.push_front({KKS_s, name, 0.00});
        kks_translate_[KKS_s] = name;
    }
}

std::vector<Parameter>& ParseSVRK::GetParameters(){
    return parameters_;
}


}
