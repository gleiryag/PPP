#pragma once
#include<iostream>
#include<vector>
#include<Pipeline.hpp>
#include<fstream>
#include<Eigen/Dense>
#include<Timer.hpp>

constexpr int COLLSEED =  827381;

using Row = Eigen::Matrix<double,1,Eigen::Dynamic>;


void dowork (int weight);

template<typename T>
void fill(std::vector<T>& vec,T val,int k){


	for(int i = 0 ; i < k ; i++) vec.push_back(val);


}

template<typename T>
std::ostream& operator<<(std::ostream& os,std::vector<T> const & v);
void process_results(std::string name,std::vector<Row>  results);
