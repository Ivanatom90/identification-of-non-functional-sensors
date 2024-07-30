#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>
#include <string_view>
#include <cmath>
#include <list>
#include <set>

#include "reader.h"
#include "domain.h"
#include "datchic.h"


#include <iomanip>

using namespace std;


ofstream outfile("answer/result.txt");
ofstream filepogr("answer/pogr.txt");

template <typename T>
ostream& operator<<(ostream& out, vector<T> vec){
    for(auto par:vec){
        out<<par<<endl;
    }
    return out;
}

ostream& Razdelen(ostream&, char, std::string);
ostream& Razdelen(ostream&, char);


int main()
{
    string wordpad_name,
     wordpad_name_nk,
     wordpad_name_f,
     wordpad_name_knit,
     wordpad_name_Tpet;
    int blok_number;
    cout<<"Created by Baskakov Ivan"<<endl;
    cout<<"Enter block number = ";
    cin>>blok_number;
    if(blok_number == 1){
        wordpad_name = "DPZ_tok_names_b1.txt"s;
        wordpad_name_knit = "KNIT_T_names_b1.txt"s;
        wordpad_name_f = "DPZ_f_tok_names_b1.txt"s;
        wordpad_name_nk = "DPZ_nk_tok_names_b1.txt"s;
        wordpad_name_Tpet = "T_pet_names_b1.txt"s;
    } else {
        wordpad_name = "DPZ_tok_names_b2.txt"s;
        wordpad_name_knit = "KNIT_T_names_b2.txt"s;
        wordpad_name_f = "DPZ_f_tok_names_b2.txt"s;
        wordpad_name_nk = "DPZ_nk_tok_names_b2.txt"s;
        wordpad_name_Tpet = "T_pet_names_b2.txt"s;
    }

    outfile<<"Created by Baskakov Ivan"<<'\n'<<endl;
    filepogr<<"Created by Baskakov Ivan"<<'\n'<<endl;
    Razdelen(outfile, '*', "DPZ"s);
//    outfile<<"__________________DPZ_______________________________"<<endl;
    {
        read::ParseSVRK DPZ_Parse("DPZ_tok_hour_step.txt"s, wordpad_name, outfile);
        DatchicHour DPZ(DPZ_Parse);
        DPZ.GreateLostDatAtWeek();
        DPZ.PrintDatchic(outfile);
    }
    Razdelen(outfile, '-');

    Razdelen(outfile, '*', "Pogresh_DPZ"s);
     //outfile<<"__________________Pogresh_DPZ_______________________________"<<endl;

        read::ParseSVRK DPZ_Parse("DPZ_tok_sec_step.txt"s, wordpad_name, outfile);
        DatchicSec DPZp(DPZ_Parse);
        DPZp.GreateLostDatAtWeek();
        DPZp.PrintDatchic(outfile);
        DPZp.PrintPogrDat(filepogr);

    Razdelen(outfile, '-');
    Razdelen(outfile, '*', "DPZ_nk_tok"s);
    //outfile<<"__________________DPZ_nk_tok_______________________________"<<endl;
    {
       read::ParseSVRK DPZ_Parse2("DPZ_nk_tok_hour_step.txt"s, wordpad_name_nk, outfile);
       DatchicHour DPZ2(DPZ_Parse2);
       DPZ2.GreateLostDatAtWeek();
       DPZ2.PrintDatchic(outfile);
    }
    Razdelen(outfile, '-');
    Razdelen(outfile, '*', "Pogresh_DPZ_nk_tok"s);
    //outfile<<"__________________Pogresh_DPZ_nk_tok_______________________________"<<endl;

    {
       read::ParseSVRK DPZ_Parse2("DPZ_nk_tok_sec_step.txt"s, wordpad_name_nk, outfile);
       DatchicSec DPZ2(DPZ_Parse2);
       DPZ2.GreateLostDatAtWeek();
       DPZ2.PrintDatchic(outfile);
       DPZ2.PrintPogrDat(filepogr);

    }

/*    outfile<<"__________________DPZ_f_______________________________"<<endl;
    {
        read::ParseSVRK DPZ_f_Parse("DPZ_f_tok_hour_step.txt"s, wordpad_name_f);
        DatchicHour DPZ_f(DPZ_f_Parse);
        DPZ_f.GreateLostDatAtWeek();
        DPZ_f.PrintDatchic(outfile);
    }
*/
    Razdelen(outfile, '-');
    Razdelen(outfile, '*', "Pogresh_DPZ_f"s);
    //outfile<<"__________________Pogresh_DPZ_f_______________________________"<<endl;

        read::ParseSVRK DPZ_f_Parse2("DPZ_f_tok_sec_step.txt"s, wordpad_name_f, outfile);
        DatchicSec DPZ_f2(DPZ_f_Parse2);
        DPZ_f2.GreateLostDatAtWeek();
        DPZ_f2.PrintDatchic(outfile);
        DPZ_f2.PrintPogrDat(filepogr);

    Razdelen(outfile, '-');
    Razdelen(outfile, '*', "KNIT"s);
    //outfile<<"__________________KNIT______________________________"<<endl;

    {
        read::ParseSVRK Knit_parse("KNIT_T_hour_step.txt"s, wordpad_name_knit, outfile);
        DatchicHour Knit(Knit_parse);
        Knit.GreateLostDatAtWeek();
        Knit.PrintDatchic(outfile);



        Razdelen(outfile, '-');
        Razdelen(outfile, '*', "KNIT_pogr"s);
   //  outfile<<"__________________KNIT_pogr______________________________"<<endl;
        read::ParseSVRK Knitparse("KNIT_T_sec_step.txt"s, wordpad_name_knit, outfile);
        DatchicSec KnitS(Knitparse, 1.0);
      //  DatchicSec KnitS(Knit.GetParameters(), 1.00);
        KnitS.GreateLostDatAtWeek();
        KnitS.PrintDatchic(outfile);
        KnitS.PrintPogrDat(filepogr);
    }
    Razdelen(outfile, '-');
    Razdelen(outfile, '*', "T_petli"s);
    {
        read::ParseSVRK Tpet_parse("T_pet_sec_step.txt"s, wordpad_name_Tpet, outfile);
        DatchicSec Tpet(Tpet_parse, 0.5);
        Tpet.GreateLostDatAtWeek();
        Tpet.PrintDatchic(outfile);
        Tpet.PrintPogrDat(filepogr);
    }
    Razdelen(outfile, '-');

Razdelen(filepogr, '*', "Dolya_fon_tok_on_dpz"s);
DPZ Dpz_d(DPZp, DPZ_f2);
Dpz_d.PrintDoly(filepogr);
Razdelen(filepogr, '-');


Razdelen(outfile, '*', " Dolya_fon_tok_on_dpz_narushena > 10% "s);
Dpz_d.PrintDolyaFtok(outfile);
Razdelen(outfile, '-');

//  cout<<"____________________The_biggest_pogreshnost_______________________________"<<endl;
//    KNIT.GetBigPogr();


//    outfile<<"_________________Big_f_tok_____________________"<<endl;


    cout << "Good_job" << endl;
    return 0;
}



ostream& Razdelen(ostream& out_, char ch, std::string text){

    int max = (100 - text.size())/2;
    for(int i = 0; i<max; i++){
        out_<<ch;
    }

    out_<<text;

    for(int i = 0; i<max; i++){
        out_<<ch;
    }
    out_<<endl;
    return out_;
}


ostream& Razdelen(ostream& out_, char ch){
    for(int i = 0; i<100; i++){
        out_<<ch;
    }
    out_<<'\n'<<'\n'<<endl;
    return out_;
}
