#include <iostream>
#include <vector>

size_t get_widest_element (std::vector<int> & vec){
    size_t max_width = 0;
    for (auto & element : vec){
        std::string s = std::to_string(element);
        if (s.size() > max_width) {
            max_width = s.size();
        }
    }
    return max_width;
}

int main () {
    // std::string line;
    // getline(std::cin, line);
    // std::cout << line << std::endl;
    std::vector<int> blob = {1,2,3,4,5,-10,60001-1,12};
    std::cout << get_widest_element(blob) << "\n";

    return 0;
}