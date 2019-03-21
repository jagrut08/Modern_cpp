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
/*DFS
Complexity is O(1) time and space - https://www.youtube.com/watch?v=KU7Ae2513h0 towards the end
Reasoning is that the number of IP addresses is finite, so that's the upper bound, a constant

Another argument: the solution is to insert 3 dots in a string of 4 - 12 chars
First dot can be inserted in 11 ways, second in 10, third in 9. All three dots identical. 
So (11x10x9)/ 3!, so N! in the range 4 <= N <= 12. But upper bound is when N = 12, so constant. 
E.g., "1234" => "1.2.3.4", only 1 IP address
*/

std::vector<std::string> getIPAddresses(const std::string& str) {
    std::vector<std::string> res;
    if(str.size() < 4 || str.size() > 12) {
    	return res;
    }
    
    std::string curIP;
    getIPAddressesHelper(&res, curIP, str, 0, 0);
    return res;
}

// Iterative solution https://leetcode.com/problems/restore-ip-addresses/discuss/30949/My-code-in-Java

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
