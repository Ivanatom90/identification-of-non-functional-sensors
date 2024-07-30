#pragma once
#include <string>
#include <vector>




struct Parameter{
  std::string KKS;
  std::string translate;
  std::vector<double> numbers;
  double pogreshnost;
};

bool operator==(Parameter& first, Parameter& second);

using Parameters = std::vector<Parameter>;
