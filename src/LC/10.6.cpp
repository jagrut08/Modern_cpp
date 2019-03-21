#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<std::string> convertToIPs(const std::vector<std::vector<int>>& ipsAsInts) {
	std::vector<std::string> res;
	for(const auto& ip : ipsAsInts) {
		std::string ipStr; // TODO can use stringstream
		for(int i = 0; i <=2; ++i) {
			ipStr += std::to_string(ip[i]) + ".";	
		}
		ipStr += std::to_string(ip[3]);
		res.emplace_back(ipStr);
	}
	return res;
}

bool isValidOctet(const std::string& str) {
	if(str.empty()) {
		return false;
	}
	return stoi(str) <= 255;
}

void getIPAddressesHelper(std::vector<int>* curIpPtr, std::vector<std::vector<int>>* resPtr, const std::string& str, const int offset) {
	if(!curIpPtr || !resPtr) {
		throw std::runtime_error("curIpPtr and/or resPtr are null");
	}

	if(offset == str.size() && curIpPtr->size() == 4) {
		resPtr->emplace_back(*curIpPtr);
}  else {
	for(int numChars = 1; numChars <= 3 ; ++numChars) {
		if(offset + numChars > str.size()) {
			break;
		}
	
		const std::string& octet = str.substr(offset, numChars);
	if(isValidOctet(octet)) { // TODO no need to convert str to int if resPtr takes strings
			curIpPtr->emplace_back(stoi(octet));
			getIPAddressesHelper(curIpPtr, resPtr, str, offset + numChars);
		}

	}

}


}

std::vector<std::string> getIPAddresses(const std::string& str) {
    if(str.size() < 4 || str.size() > 12) {
    	return std::vector<std::string>{};
    }
    
    std::vector<int> curIP;
    std::vector<std::vector<int>> res;
    getIPAddressesHelper(&curIP, &res, str, 0);
    return convertToIPs(res);	
}

int main() {
    const std::vector<std::string> inputs = {
        "25525511135",
    };
    
    for(const auto& input : inputs) {
        std::cout << input << " IPs are:\n";
        for(const auto& res : getIPAddresses(input)) {
            std::cout << res << '\n';   
        }
        
           
    }
}
