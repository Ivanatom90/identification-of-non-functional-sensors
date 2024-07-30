#pragma once

#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <memory>

#include "domain.h"
#include "reader.h"



class Datchic{


  public:
    Datchic() = default;

    std::ostream& PrintDatchic(std::ostream& out) const;
    virtual void GreateLostDatAtWeek() = 0;
    Parameters parameters_;
    Parameters lost_datchic_at_week_;


};

class DatchicSec : public Datchic{
  public:
    DatchicSec(read::ParseSVRK& psv);
    DatchicSec(read::ParseSVRK& psv, double pogr);
    DatchicSec(Parameters& psv, double pogr);

    double GetCKO(const std::vector<double>& vec) const;
    double GetMid(const std::vector<double>& vec) const;
    double GetPogr(const std::vector<double>& vec) const;
    void SortDatchic();
    void SortDatchicKKS();
    void GreateLostDatAtWeek() override;
    std::ostream& PrintPogrDat(std::ostream& out);

    private:
    double pogr_ = 0.002;

};

class DatchicHour : public Datchic{
public:
    DatchicHour(read::ParseSVRK& psv);    
    Parameters& GetParameters();

    void GreateLostDatAtWeek() override;
private:
     bool DatchikLostAtWeek(const std::vector<double>& numbers) const;
};

class DPZ {
  public:
    DPZ(DatchicSec& dpz, DatchicSec& dpz_f);
    void MakeDoly();
    std::ostream& PrintDoly(std::ostream& out);
    std::ostream& PrintDolyaFtok(std::ostream& out);

private:
   std::unique_ptr<DatchicSec> dpz_;
   std::unique_ptr<DatchicSec> dpz_f_;
   std::vector<std::pair<std::string, double>> doly_;
   std::vector<std::pair<std::string, double>> dolya_ftok_in_dpz_is_big_;
};
