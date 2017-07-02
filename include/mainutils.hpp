#pragma once
#include<iostream>
#include<vector>
#include<Pipeline.hpp>
#include<fstream>
#include <boost/program_options.hpp>
#include<Eigen/Dense>
#include<Timer.hpp>


namespace po = boost::program_options;
constexpr int COLLSEED =  827381;

using Row = Eigen::Matrix<double,1,Eigen::Dynamic>;


void dowork (int weight);


template<typename T>
std::ostream& operator<<(std::ostream& os,std::vector<T> const & v);

void initializeArgumentMap(int argc, char* argv[],po::variables_map& vm);
void process_results(std::string name,std::vector<Row>  results);
