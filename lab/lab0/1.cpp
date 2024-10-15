#include <iostream>
#include <string>
#include<list>
#include<algorithm>

using namespace std;


int lengthOfLongestSubstring(const string& s) {
    int maxLength = 0;
    int n = s.length();
    
    for (int i = 0; i < n; i++) {
        list<char> current; 
        for(int j = i; j < n; j++) {
            auto it = find(current.begin(),current.end(),s[j]);
            if(it != current.end()) {
                break;
            }
            current.push_back(s[j]);
            maxLength = max(maxLength,j - i + 1);
        }
    }
    return maxLength;
}

int main() {
    std::string inputStr;
    std::getline(std::cin, inputStr); // 接收用户输入的字符串
    std::cout << lengthOfLongestSubstring(inputStr) << std::endl;
    return 0;
}
