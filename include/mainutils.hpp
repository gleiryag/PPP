#pragma once
#include<iostream>
#include<vector>
#include<Pipeline.hpp>
#include<fstream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;
constexpr int COLLSEED =  827381;

void dowork (int weight);


template<typename T>
std::ostream& operator<<(std::ostream& os,std::vector<T> const & v);

void initializeArgumentMap(int argc, char* argv[],po::variables_map& vm);
