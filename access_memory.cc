#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

using namespace std::chrono;
using namespace std;

int main() {

	unsigned int exponent = 10;
	cout << "# Bytes \t time\n" << std::endl;

	//create vector for storing times for each buffer size
	vector<double> times;

	while(exponent<27) {

		//create buffer from size 2^N
		unsigned int buffer_size = pow(2, exponent);
		vector<int> buffer(buffer_size);
		unsigned int copy;
		vector<int> indices(buffer_size);
		iota(indices.begin(),indices.end(),0);

		//read buffer 10 times and time it
		for(unsigned int i=0;i<10;i++){

			//to beat the prefectcher, randomly select elements in the buffer
			random_shuffle(indices.begin(),indices.end());

			const auto begin = high_resolution_clock::now();

			for(unsigned int j=0;j<buffer_size;j++){
				copy = buffer[indices[j]];
			};

			const auto end = high_resolution_clock::now();
			auto time = duration_cast<microseconds>(end - begin).count();
			//measure and add to vector of times for this buffer sizes
			//divide by size of int to find per-byte access time
			times.push_back(static_cast<double>(time) * 1000.0 / (static_cast<double>(buffer_size)*sizeof(int)));

		};

		//print out minimum time for this buffer
		cout << to_string(buffer_size) + "\t" << *min_element(times.begin(),times.end()) << std::endl;
		//print copy so that prefetcher doesn't ignore it		
		cout << copy;
		//clear times for this buffer size
		times.clear();
		exponent++;

	};
	
	return 0;

}
