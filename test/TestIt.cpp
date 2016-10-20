/*
 * TestIt.cpp
 *
 *  Created on: Oct 20, 2016
 *      Author: JohnJones
 */

#include "TestIt.h"

#include "ipfs_curl/ipfs.h"

namespace ipfs_curl {

TestIt::TestIt() {
	// TODO Auto-generated constructor stub

}

TestIt::~TestIt() {
	// TODO Auto-generated destructor stub
}

} /* namespace ipfs_curl */

int main(int argc, char** argv) {
	std::cout << "Test starting..." << std::endl;

	ipfs_curl::IPFS ipfs("localhost", 8080, 5001);

	std::cout << "Testing cat..." << std::endl;
	std::cout << "Results: [" << ipfs.cat("QmYwAPJzv5CZsnA625s3Xf2nemtYgPpHdWEz79ojWnPbdG/readme").str() << "]" << std::endl;

	std::cout << "Testing cat binary... (saving to cat.jpg)" << std::endl;
	std::ofstream f("cat.jpg");
	f << ipfs.cat("QmW2WQi7j6c7UgJTarActp7tDNikE4B2qXtFCfLPdsgaTQ/cat.jpg").str();
	std::cout << "See cat.jpg for the results" << std::endl;

	std::cout << "Testing version" << std::endl;
	std::cout << "Results: [" << ipfs.version() << "]" << std::endl;

	std::cout << "End of test." << std::endl;
}
