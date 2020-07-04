/*
Minimal Mapping of Quantum Circuits to IBM QX Architectures by JKU Linz, Austria

Developer: Robert Wille, Lukas Burgholzer, Alwin Zulehner

For more information, please visit http://iic.jku.at/eda/research/ibm_qx_mapping

If you have any questions feel free to contact us using
robert.wille@jku.at, lukas.burgholzer@jku.at or alwin.zulehner@jku.at

If you use the compiler for your research, we would be thankful if you referred to it
by citing the following publication:

@inproceedings{wille2019mapping,
    title={Mapping Quantum Circuits to {IBM QX} Architectures Using the Minimal Number of {SWAP} and {H} Operations},
    author={Wille, Robert and Burgholzer, Lukas and Zulehner, Alwin},
    booktitle={Design Automation Conference},
    year={2019}
}
*/
#include <vector>
#include <iostream>
#include <sstream>
#include "Circuit.hpp"

#include <list>
#include <map>
#include <time.h>


/*
/// Cost of permutations on IBM QX2/QX4 architecture.
/// \param pi permutation
/// \return cost of permutation (=7*numberOfSwaps)
unsigned int costIBMQX4(std::vector<int>& pi) {
	std::stringstream pi_name;
	for (int i : pi) {
		pi_name << i;
	}
	const int COST_PER_SWAP = 7;
	switch (std::stoi(pi_name.str())) {
		case 1234:
			return 0;
		case 10234: case 21034: case 2134: case 1432: case 1324: case 1243:
			return 1 * COST_PER_SWAP;
		case 31204: case 41230: case 3214: case 4231:
			return 3 * COST_PER_SWAP;
		case 12034: case 1342: case 21304: case 2431: case 21430: case 2314:
		case 20134: case 1423: case 31024: case 4132: case 41032: case 3124:
			return 2 * COST_PER_SWAP;
		case 13204: case 14230: case 31240: case 3241:
		case 30214: case 40231: case 41203: case 4213:
			return 4 * COST_PER_SWAP;
		case 21043: case 2143: case 10243: case 10432: case 10324:
			return 2 * COST_PER_SWAP;
		case 42130: case 41320: case 23014: case 3412: case 32104: case 31402: case 24031: case 4321:
			return 4 * COST_PER_SWAP;
		case 43210: case 34201:
			return 6 * COST_PER_SWAP;
		case 12304: case 12430: case 20314: case 20431: case 31042: case 3142:
		case 41023: case 4123: case 24130: case 3421: case 41302: case 32014:
		case 30124: case 40132: case 13024: case 14032: case 21403: case 2413:
		case 21340: case 2341: case 42031: case 4312: case 31420: case 23104:
			return 3 * COST_PER_SWAP;
		case 13240: case 34210: case 30241:
		case 40213: case 43201: case 14203:
			return 5 * COST_PER_SWAP;
		case 12043: case 10342:
		case 20143: case 10423:
			return 3 * COST_PER_SWAP;
		case 24301: case 32401: case 23410: case 42310: case 13402: case 14320: case 32140: case 23041:
		case 34021: case 34102: case 43012: case 43120: case 30412: case 40321: case 42103: case 24013:
			return 5 * COST_PER_SWAP;
		case 12340: case 12403: case 13042: case 13420: case 14023: case 14302:
		case 20341: case 20413: case 23140: case 23401: case 24103: case 24310:
		case 30142: case 30421: case 32041: case 32410: case 34012: case 34120:
		case 40123: case 40312: case 42013: case 42301: case 43021: case 43102:
			return 4 * COST_PER_SWAP;

		default:
			std::cout << "Permutation with no associated cost: " << std::stoi(pi_name.str()) << std::endl;
			return 0;
	}
}

/// Coupling map of the IBM QX4 architecture
const CouplingMap ibmQX4 = {
		{ 1, 0 }, {0, 1},
		{ 2, 0 }, {0, 2},
		{ 2, 1 }, {1, 2},
		{ 3, 2 }, {2, 3},
		{ 3, 4 }, {4, 3},
		{ 2, 4 }, {4, 2}
};
std::vector<std::vector<int> > connections = {{0, 1}, {1, 2}, {2, 0}, {3, 4}, {4, 2}, {2, 3}};
std::vector<int> physicalQubits = { 0, 1, 2, 3, 4};
int n_qubit = 5; // qubit count
*/


// Daniel Tan

/*
// Rigetti agave device
const CouplingMap biconnections = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 0},
														{1, 0}, {2, 1}, {3, 2}, {4, 3}, {5, 4}, {0, 5}};
std::vector<std::vector<int> > connections = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 0}};
std::vector<int> physicalQubits = { 0, 1, 2, 3, 4, 5};
int n_qubit = 6; // qubit count
*/


/*
// grid2by3
const CouplingMap biconnections = {{0, 1}, {1, 2}, {0, 3}, {1, 4}, {2, 5}, {3, 4}, {4, 5},
															{1, 0}, {2, 1}, {3, 0}, {4, 1}, {5, 2}, {4, 3}, {5, 4}};
std::vector<std::vector<int> > connections = {{0, 1}, {1, 2}, {0, 3}, {1, 4}, {2, 5}, {3, 4}, {4, 5}};
std::vector<int> physicalQubits = {0, 1, 2, 3, 4, 5};
int n_qubit = 6; // qubit count
*/


/*
// grid2by3plus
const CouplingMap biconnections = {{0, 1}, {1, 2}, {0, 3}, {1, 4}, {2, 5}, {3, 4}, {4, 5}, {5, 6},
																	 {1, 0}, {2, 1}, {3, 0}, {4, 1}, {5, 2}, {4, 3}, {5, 4}, {6, 5}};
std::vector<std::vector<int> > connections = {{0, 1}, {1, 2}, {0, 3}, {1, 4}, {2, 5}, {3, 4}, {4, 5}, {5, 6}};
std::vector<int> physicalQubits = {0, 1, 2, 3, 4, 5, 6};
int n_qubit = 7; // qubit count
*/



std::map<std::vector<int>, int> picost;
std::map<std::vector<int>, long long> pinum;
std::map<long long, std::vector<int> > numpi;

unsigned int mycost(std::vector<int>& pi) {
	return picost[pi];
}



int main(int argc, const char * argv[]) {

	clock_t begin = clock();

	unsigned int timeout = 360000000; // 60min timeout


	MappingSettings settings = MappingSettings();
	std::string filename = "../testExample.qasm";
	std::string devicename = "grid2by4";

	// Use filename from command line, if specified
	if (argc == 3) {
		filename = argv[1];
		devicename = argv[2];
	}

	// grid2by4
	CouplingMap biconnections = {{0, 1}, {1, 2}, {2, 3}, {0, 4}, {1, 5}, {2, 6}, {3, 7}, {4, 5}, {5, 6}, {6, 7},
																     {1, 0}, {2, 1}, {3, 2}, {4, 0}, {5, 1}, {6, 2}, {7, 3}, {5, 4}, {6, 5}, {7, 6}};
	std::vector<std::vector<int> > connections = {{0, 1}, {1, 2}, {2, 3}, {0, 4}, {1, 5}, {2, 6}, {3, 7}, {4, 5}, {5, 6}, {6, 7}};
	std::vector<int> physicalQubits = {0, 1, 2, 3, 4, 5, 6, 7};
	int n_qubit = 8; // qubit count


	// decide the device
	if (devicename == "tokyopart1") {
		biconnections = {{0, 1}, {1, 2}, {2, 3}, {0, 4}, {1, 5}, {1, 6}, {2, 5}, {2, 6}, {3, 7}, {4, 5}, {5, 6}, {6, 7},
																	     {1, 0}, {2, 1}, {3, 2}, {4, 0}, {5, 1}, {6, 1}, {5, 2}, {6, 2}, {7, 3}, {5, 4}, {6, 5}, {7, 6}};
		connections = {{0, 1}, {1, 2}, {2, 3}, {0, 4}, {1, 5}, {1, 6}, {2, 5}, {2, 6}, {3, 7}, {4, 5}, {5, 6}, {6, 7}};
		physicalQubits = {0, 1, 2, 3, 4, 5, 6, 7};
		n_qubit = 8; // qubit count
	}
	else if (devicename == "tokyopart2") {
		biconnections = {{0, 1}, {1, 2}, {2, 3}, {0, 4}, {0, 5}, {1, 4}, {1, 5}, {2, 6}, {2, 7}, {3, 6}, {3, 7}, {4, 5}, {5, 6}, {6, 7},
																	     {1, 0}, {2, 1}, {3, 2}, {4, 0}, {5, 0}, {4, 1}, {5, 1}, {6, 2}, {7, 2}, {6, 3}, {7, 3}, {5, 4}, {6, 5}, {7, 6}};
		connections = {{0, 1}, {1, 2}, {2, 3}, {0, 4}, {0, 5}, {1, 4}, {1, 5}, {2, 6}, {2, 7}, {3, 6}, {3, 7}, {4, 5}, {5, 6}, {6, 7}};
		physicalQubits = {0, 1, 2, 3, 4, 5, 6, 7};
		n_qubit = 8; // qubit count
	}
	else if (devicename == "ibmqx2") {
		biconnections = {
				{ 1, 0 }, {0, 1},
				{ 2, 0 }, {0, 2},
				{ 2, 1 }, {1, 2},
				{ 3, 2 }, {2, 3},
				{ 3, 4 }, {4, 3},
				{ 2, 4 }, {4, 2}};
		connections = {{0, 1}, {1, 2}, {2, 0}, {3, 4}, {4, 2}, {2, 3}};
		physicalQubits = { 0, 1, 2, 3, 4};
		n_qubit = 5; // qubit count
	}
	else if (devicename == "aspen4") {
		biconnections = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7},
									 	 {0, 8}, {3, 11}, {4, 12}, {7, 15},
									 	 {8, 9}, {9, 10}, {10, 11}, {11, 12}, {12, 13}, {13, 14}, {14, 15},
									   {1, 0}, {2, 1}, {3, 2}, {4, 3}, {5, 4}, {6, 5}, {7, 6},
									   {8, 0}, {11, 3}, {12, 4}, {15, 7},
									   {9, 8}, {10, 9}, {11, 10}, {12, 11}, {13, 12}, {14, 13}, {15, 14}};
		connections = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7},
									 {0, 8}, {3, 11}, {4, 12}, {7, 15},
									 {8, 9}, {9, 10}, {10, 11}, {11, 12}, {12, 13}, {13, 14}, {14, 15}};
		n_qubit = 16;
		physicalQubits = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	}
	else if (devicename == "grid2by3") {
		biconnections = {{0, 1}, {1, 2}, {0, 3}, {1, 4}, {2, 5}, {3, 4}, {4, 5},
										 {1, 0}, {2, 1}, {3, 0}, {4, 1}, {5, 2}, {4, 3}, {5, 4}};
		connections = {{0, 1}, {1, 2}, {0, 3}, {1, 4}, {2, 5}, {3, 4}, {4, 5}};
		physicalQubits = { 0, 1, 2, 3, 4, 5};
		n_qubit = 6;
	}
	else {
		biconnections = {{0, 1}, {1, 2}, {2, 3}, {0, 4}, {1, 5}, {2, 6}, {3, 7}, {4, 5}, {5, 6}, {6, 7},
																	     {1, 0}, {2, 1}, {3, 2}, {4, 0}, {5, 1}, {6, 2}, {7, 3}, {5, 4}, {6, 5}, {7, 6}};
		connections = {{0, 1}, {1, 2}, {2, 3}, {0, 4}, {1, 5}, {2, 6}, {3, 7}, {4, 5}, {5, 6}, {6, 7}};
		physicalQubits = {0, 1, 2, 3, 4, 5, 6, 7};
		n_qubit = 8; // qubit count
		devicename == "grid2by4";
	}




	long long n_pi = 1; // permutation count
	for (int i = 2; i <= n_qubit; ++i)
		n_pi *= i;
	std::vector<int> origin;
	for (int i = 0; i < n_qubit; ++i)
		origin.push_back(i);

	std::sort(origin.begin(), origin.end());
	long long num = 0;
	do {
		//for (int j = 0; j < origin.size(); ++j)
		//	std::cout << origin[j];
		// std::cout << ' ' << num << std::endl;
		pinum[origin] = num;
		numpi[num] = origin;
		num++;
	} while (std::next_permutation(origin.begin(), origin.end()));

	// Mark all the vertices as not visited
    bool *visited = new bool[n_pi];
    for(long long i = 0; i < n_pi; i++)
        visited[i] = false;

    // Create a queue for BFS
    std::list<long long> queue;

    // Mark the current node as visited and enqueue it
    visited[0] = true;
    queue.push_back(0);
    picost[numpi[0]] = 0;


    while (!queue.empty()) {
        // Dequeue a vertex from queue and print it
        long long s = queue.front();
        // std::cout << s << " ";
        queue.pop_front();
        int curr_cost = picost[numpi[s]];

        for (int k = 0; k < connections.size(); ++k) {
			std::vector<int> tmp = numpi[s];
			int q = tmp[connections[k][0]];
			tmp[connections[k][0]] = tmp[connections[k][1]];
			tmp[connections[k][1]] = q;
			long long tmpnum = pinum[tmp];
			if (!visited[tmpnum]) {
            	visited[tmpnum] = true;
                queue.push_back(tmpnum);
                picost[tmp] = curr_cost + 1;
            }
		}
    }

	clock_t mid = clock();
	std::cout << "preprocessing time: " << (double)(mid - begin) / CLOCKS_PER_SEC << 's' << std::endl;

	std::cout << "################### Basis ###################" << std::endl;
	MappingResults basis = Circuit::run(filename, timeout, biconnections, physicalQubits, mycost, settings);

	/*
	std::cout << "################### Basis Reduced ###################" << std::endl;
	settings.considerQubitSubsets();
	MappingResults basisReduced = Circuit::run(filename, timeout, ibmQX4, physicalQubits, costIBMQX4, settings);

	std::cout << "################### Disjoint Qubits ###################" << std::endl;
	settings.useDisjointQubitsStrategy();
	MappingResults disjoint = Circuit::run(filename, timeout, ibmQX4, physicalQubits, costIBMQX4, settings);

	std::cout << "################### Odd Gates ###################" << std::endl;
	settings.useOddGatesStrategy();
	MappingResults otherGate = Circuit::run(filename, timeout, ibmQX4, physicalQubits, costIBMQX4, settings);

	std::cout << "################### Qubit Triangle ###################" << std::endl;
	settings.useQubitTriangleStrategy();
	MappingResults triangle = Circuit::run(filename, timeout, ibmQX4, physicalQubits, costIBMQX4, settings);
	*/
    return 0;
}
