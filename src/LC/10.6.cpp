/*
Given a string containing only digits, restore it by returning all possible valid IP address combinations.
Input: "25525511135"
Output: ["255.255.11.135", "255.255.111.35"]
*/

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

bool isValidOctet(const std::string& str) {
	if(str.empty()) {
		return false;
	}
	return stoi(str) <= 255;
}

void getIPAddressesHelper(std::vector<std::string>* resPtr, const std::string& curIp, const std::string& str, const int offset, const int octet_num) {
	if(!resPtr) {
		throw std::runtime_error("resPtr is null");
	}

	if(octet_num == 4) {
	    if(offset == str.size()) { 
		    resPtr->emplace_back(curIp);
	    } 
	     
	    return;   
	}  
	
	for(int numChars = 1; numChars <= 3 ; ++numChars) {
		if(offset + numChars > str.size()) {
			break;
		}
	
		std::string octet = str.substr(offset, numChars);
    	if(isValidOctet(octet)) { 
    	        if(curIp.size()) {
    	            octet = "." + octet;
    	        }
    			getIPAddressesHelper(resPtr, curIp + octet, str, offset + numChars, octet_num + 1);
    	}
    }
}

std::vector<std::string> getIPAddresses(const std::string& str) {
    std::vector<std::string> res;
    if(str.size() < 4 || str.size() > 12) {
    	return res;
    }
    
    std::string curIP;
    getIPAddressesHelper(&res, curIP, str, 0, 0);
    return res;
}

int main() {
    const std::vector<std::string> inputs = {
        "25525511135",
        "1234",
        "12345",
        "300123",
        "123123123123"
    };
    
    for(const auto& input : inputs) {
        std::cout << input << " IPs are:\n";
        for(const auto& res : getIPAddresses(input)) {
            std::cout << res << '\n';   
        }
        std::cout << '\n';
    }
}
