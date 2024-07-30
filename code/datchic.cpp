#include "datchic.h"
#include <iomanip>
/*
Datchic::Datchic(read::ParseSVRK& psv){
    parameters_ = std::move(psv.GetParameters());
}
*/
DatchicSec::DatchicSec(read::ParseSVRK& psv){
    parameters_ = std::move(psv.GetParameters());
}

DatchicSec::DatchicSec(read::ParseSVRK& psv, double pogr): pogr_(pogr){
     parameters_ = std::move(psv.GetParameters());
}

DatchicSec::DatchicSec(Parameters& psv, double pogr): pogr_(pogr){
    parameters_ = std::move(psv);
}

DatchicHour::DatchicHour(read::ParseSVRK& psv){
    parameters_ = std::move(psv.GetParameters());
}

Parameters& DatchicHour::GetParameters(){
    return parameters_;
}

double DatchicSec::GetCKO(const std::vector<double>& vec) const{
    int viborka = vec.size();
    if(viborka<3500){
        return 0;
    }
    double mid = GetMid(vec);
    double Cko = 0.00;
    for_each(vec.end() - viborka, vec.end(), [&Cko, &mid](const double& par){
        Cko += (par-mid)*(par-mid);
    });
    Cko = sqrt(Cko/(viborka*(viborka-1)));
    return Cko;
}

double DatchicSec::GetMid(const std::vector<double>& vec) const{
    return std::accumulate(vec.begin(), vec.end(), 0.00)/vec.size();
}

double DatchicSec::GetPogr(const std::vector<double>& vec) const{
    return GetCKO(vec)*1.96;
}

bool DatchicHour::DatchikLostAtWeek(const std::vector<double>& numbers) const{

    int counter = std::count_if(numbers.begin(), numbers.end(), [](const double& num){
        if (num<1E-6){
            return true;
        }
        return false;
    });

    if(counter >20){
        return true;
    }
    return false;
}

void DatchicHour::GreateLostDatAtWeek() {
    for(const Parameter& par:parameters_){
        if(DatchikLostAtWeek(par.numbers)){
            lost_datchic_at_week_.push_back(par);
        }
    }
}

void DatchicSec::GreateLostDatAtWeek() {
    for(Parameter& par:parameters_){
        par.pogreshnost =GetPogr(par.numbers);
        if(par.pogreshnost>pogr_){
            lost_datchic_at_week_.push_back(par);
        }
    }
}

std::ostream& Datchic::PrintDatchic(std::ostream& out) const{
    if(lost_datchic_at_week_.size() ==0){
        out<<"net_narushenii"<<std::endl;
        return out;
    }
    out<<"KKS"<<"                "<<"pogreshnost         "<<"name"<<std::endl;
    for(const Parameter& par:lost_datchic_at_week_){
        out<<par.KKS<<"     "<<par.pogreshnost<<"     "<<par.translate<<std::endl;
    }
    return out;
}

void DatchicSec::SortDatchic(){
    std::sort(parameters_.begin(), parameters_.end(), [](Parameter& par1, Parameter& par2){
        return par1.pogreshnost>par2.pogreshnost;
    });
}

void DatchicSec::SortDatchicKKS(){
    std::sort(parameters_.begin(), parameters_.end(), [](Parameter& par1, Parameter& par2){
        return par1.KKS>par2.KKS;
    });
}

std::ostream& DatchicSec::PrintPogrDat(std::ostream& out) {
    out<<"***********************************************************************************************"<<std::endl;
    out<<"KKS                    Middle         "<<"pogreshnost     "<<"name"<<std::endl;
   // SortDatchic();
    SortDatchicKKS();
    for(const Parameter& par:parameters_){
        out<<par.KKS<<"  "<<std::setw(12)<<GetMid(par.numbers)<<std::setw(20)<<par.pogreshnost<<"    "<<par.translate<<std::endl;
    }
    return out;
}

bool operator==(Parameter& first, Parameter& second){
    return first.KKS == second.KKS;
}


DPZ::DPZ(DatchicSec& dpz, DatchicSec& dpz_f){
    dpz_ = std::make_unique<DatchicSec>(dpz);
    dpz_f_ = std::make_unique<DatchicSec>(dpz_f);
    MakeDoly();
}

void DPZ::MakeDoly(){
    doly_.reserve(dpz_->parameters_.size());
    //dpz_->parameters_;
    for(size_t i = 0; i<dpz_f_->parameters_.size(); i++){
        double dpzdoly =  dpz_f_->GetMid(dpz_f_->parameters_.at(i).numbers) * 100;
        double mid = dpz_->GetMid(dpz_->parameters_[i].numbers);
        if(mid > 1E-9){
             dpzdoly /= dpz_->GetMid(dpz_->parameters_[i].numbers);
        } else {
            dpzdoly = 0.00;
        }

        doly_.push_back({dpz_->parameters_[i].KKS, dpzdoly});
        if(dpzdoly>10){
            dolya_ftok_in_dpz_is_big_.push_back({dpz_->parameters_[i].KKS, dpzdoly});
        }
    }
}

std::ostream& DPZ::PrintDoly(std::ostream& out){
    out<<"KKS"<<std::setw(10)<<"                                    Dolya_fon_tok_in_DPZ"<<std::endl;

    for(const std::pair<std::string, double> &num:doly_){
            out<<num.first<<"        "<<num.second<<std::endl;
        }
return out;
}

std::ostream& DPZ::PrintDolyaFtok(std::ostream& out){
    out<<"KKS"<<std::setw(10)<<"                                    Dolya_fon_tok_in_DPZ"<<std::endl;
    if(dolya_ftok_in_dpz_is_big_.size()==0){
        out<< "net_narushen_doly_ftok_in_dpz < 10%"<<std::endl;
        return out;
    }
    for(const std::pair<std::string, double> &num:dolya_ftok_in_dpz_is_big_){
            out<<num.first<<"        "<<num.second<<std::endl;
        }
return out;
}
