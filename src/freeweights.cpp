//============================================================================
// Name        : freeweights.cpp
// Author      : Aonghus Lawlor
// Version     :
// Copyright   : GPL3
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <set>
#include <iterator>
#include <cmath>
using namespace std;

template<typename T> ostream& operator<<(ostream& os, const vector<T>& v) {
	os << "[ ";
	for (auto e : v) {
		os << e << " ";
	}
	os << "]";
	return os;
}

template<typename T>
bool is_paired(const vector<T>& row) {
	auto size = row.size();
	if (size == 0) {
		return true;
	}
	if (size == 1) {
		return false;
	}
	if (size % 2 != 0) {
		return false;
	}

	for (auto i = 0U; i < size; i += 2) {
		if (row[i] != row[i + 1]) {
			return false;
		}
	}
	return true;
}

template<typename T>
bool pair_weights(const vector<T>& row_1, const vector<T>& row_2, const T& M) {
	// filter weights
	auto filt = [&M](const T& val) {return val > M;};
	vector<T> row_1_filt, row_2_filt;
	copy_if(row_1.begin(), row_1.end(), back_inserter(row_1_filt), filt);
	copy_if(row_2.begin(), row_2.end(), back_inserter(row_2_filt), filt);

	return is_paired(row_1_filt) and is_paired(row_2_filt);
}

template<typename T>
T get_max_weight(vector<T>& weights, const vector<T>& row_1,
		const vector<T>& row_2) {
	// standard binary search

	T lo(0), hi(weights.size());
	while (lo < hi) {
		T mid = floor((hi + lo) / 2);
		T M = weights[mid];
		if (pair_weights(row_1, row_2, M)) {
			hi = mid;
		} else {
			lo = mid + 1;
		}
	}
	return weights[lo];
}

void f1() {
	ifstream in("1.in");
	//istream &in = cin;

	while (!in.eof()) {
		string line;
		std::getline(in, line);
		if (line.size() == 0) {
			break;
		}

		typedef unsigned long T;
		int n;
		set<T> unique_weights;

		istringstream iss(line);
		iss >> n;

		// read the weights
		std::getline(in, line);
		istringstream iss1(line);
		vector<T> weights_1((istream_iterator<T>(iss1)), istream_iterator<T>());

		// second line of weights
		std::getline(in, line);
		istringstream iss2(line);
		vector<T> weights_2((istream_iterator<T>(iss2)), istream_iterator<T>());

		// use a std::set to create a list of unique weights
		for (auto &e : weights_1) {
			unique_weights.insert(e);
		}
		for (auto &e : weights_2) {
			unique_weights.insert(e);
		}
		//unique_weights.insert(0);
		vector<T> unique_weights_v(unique_weights.begin(),
				unique_weights.end());

		// use M=0 to check if the rows of weights are already sorted
		if (pair_weights(weights_1, weights_2, 0UL)) {
			// no need for further checking:
			cout << "0" << endl;
			return;
		}

		// if they are not already sorted, use binary search to find the max weight to be moved...
		T res = get_max_weight(unique_weights_v, weights_1, weights_2);
		cout << res << endl;
	}
}
int main() {
	f1();
	return 0;
}
