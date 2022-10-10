#include "telescope.hpp"
#include <sstream>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

// --------------------- STAGE 1 ---------------------
std::pair<size_t, size_t> parse_matrix(std::istream& in){
    std::string line;
    size_t numberOfRows = 0;
    size_t numberOfColumns = 0;
    while (std::getline(in, line)){
        int element;
        std::istringstream lineStream(line);
        size_t temp_counter = 0;
        while ( lineStream >> element ) {
            temp_counter++;
        }
        if (numberOfColumns == 0) {
            numberOfColumns = temp_counter;
        }
        if (temp_counter != numberOfColumns) {
            throw std::invalid_argument( "Number of columns is not consistent across rows" );
        }
        numberOfRows++;
    }
    return std::make_pair (numberOfRows, numberOfColumns);
}

std::vector<int> parse_matrix(std::istream& in, const std::pair<size_t, size_t>& m_size){
    std::string line;
    std::vector<int> matrix;
    size_t numberOfRows = 0;
    size_t numberOfColumns = 0;
    while (std::getline(in, line)){
        int element;
        std::istringstream lineStream(line);
        size_t temp_counter = 0;
        while ( lineStream >> element ) {
            temp_counter++;
            matrix.push_back(element);
        }
        if (numberOfColumns == 0) {
            numberOfColumns = temp_counter;
        }
        if (temp_counter != numberOfColumns) {
            throw std::invalid_argument( "Number of columns is not consistent across rows" );
        }
        numberOfRows++;
    }
    return matrix;
}

size_t get_widest_element (const std::vector<int> & vec){
    size_t max_width = 0;
    for (auto & element : vec){
        std::string s = std::to_string(element);
        if (s.size() > max_width) {
            max_width = s.size();
        }
    }
    return max_width;
}

void print_matrix(std::ostream& out, const std::pair<size_t, size_t>& m_size, const std::vector<int>& vec){
    size_t numberOfRows = m_size.first;
    size_t numberOfColumns = m_size.second;

    if (numberOfColumns == 0 || numberOfRows == 0){
        return;
    }
    
    size_t max_width = get_widest_element(vec);
    for ( size_t i = 0; i < numberOfColumns*(max_width+3) + 1; i++){
        out << "-";
    }
    out << std::endl; 
    for ( size_t i = 0; i < numberOfRows; i++){
        for ( size_t  j = 0; j < numberOfColumns; j++){
            out << "| " << std::setw(max_width) << vec[i*numberOfColumns+j] << " ";
        }
        out << "|" << std::endl;
    }
    for ( size_t i = 0; i < numberOfColumns*(max_width+3) + 1; i++){
        out << "-";
    }
    out << std::endl; 
}

// --------------------- STAGE 2 ---------------------

void print_matrix(const std::pair<size_t, size_t>& m_size, std::vector<unsigned char> & vec ) {
    size_t numberOfRows = m_size.first;
    size_t numberOfColumns = m_size.second;
    int counter = 0;
    std::cout << "+------------------+\n";
    for ( int i = 0; i< numberOfRows; i++){
        for (int j = 0; j < numberOfColumns; j++){
            std::cout << vec[counter++] << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<unsigned char> parse_stream(std::istream& in, const std::pair<size_t, size_t>& m_size){
    std::vector<unsigned char> vec;
    size_t numberOfRows = m_size.first;
    size_t numberOfColumns = m_size.second;

    if (numberOfColumns == 0 || numberOfRows == 0){
        return vec;
    }
    char element;
    while ( in.get(element) ){
        vec.push_back(element);
    }
    if (vec.size() != numberOfColumns*numberOfRows) {
        throw std::invalid_argument("inconsistent number of elements");
    }
    return vec;
}

void rotate_down(const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec){
    size_t numberOfRows = m_size.first;
    size_t numberOfColumns = m_size.second;
    std::rotate(vec.rbegin(), vec.rbegin() + numberOfColumns, vec.rend());
}

void rotate_up(const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec){
    size_t numberOfRows = m_size.first;
    size_t numberOfColumns = m_size.second;
    std::rotate(vec.begin(), vec.begin() + numberOfColumns, vec.end());
}

void rotate_down(const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec, int step){
    size_t numberOfRows = m_size.first;
    size_t numberOfColumns = m_size.second;
    bool up = false;
    bool down = false;
    if ( step > 0 ) {
        down = true;
    } 
    if ( step < 0){
        up = true;
    }
    step = abs(step) % numberOfRows;
    if ( down ) {
        std::rotate(vec.rbegin(), vec.rbegin() + numberOfColumns*step, vec.rend());
    } else if ( up ) {
        std::rotate(vec.begin(), vec.begin() + numberOfColumns*step, vec.end());
    }
}

void rotate_right(const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec){
    size_t numberOfRows = m_size.first;
    size_t numberOfColumns = m_size.second;

    for (size_t i = 0; i < numberOfRows*numberOfColumns; i+=numberOfColumns){
        std::rotate(vec.begin() + i, vec.begin() + i + numberOfColumns -1, vec.begin() + i + numberOfColumns);
    }   
}

void rotate_left(const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec){
    size_t numberOfRows = m_size.first;
    size_t numberOfColumns = m_size.second;

    for (size_t i = 0; i < numberOfRows*numberOfColumns; i+=numberOfColumns){
        std::rotate(vec.begin() + i, vec.begin() + i + 1, vec.begin() + i + numberOfColumns);
    }   
}

void rotate_right(const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec, int step){
    size_t numberOfRows = m_size.first;
    size_t numberOfColumns = m_size.second;
    bool up = false;
    bool down = false;
    if ( step > 0 ) {
        down = true;
    } 
    if ( step < 0){
        up = true;
    }
    step = abs(step) % numberOfColumns;
    if ( down ) {
        for (size_t i = 0; i < numberOfRows*numberOfColumns; i+=numberOfColumns){
            std::rotate(vec.begin() + i, vec.begin() + i + numberOfColumns - step, vec.begin() + i + numberOfColumns);
        }
    } else if ( up ) {
        for (size_t i = 0; i < numberOfRows*numberOfColumns; i+=numberOfColumns){
            std::rotate(vec.begin() + i, vec.begin() + i + step, vec.begin() + i + numberOfColumns);
        }   
    }
}

int get_coord (const std::pair<size_t, size_t>& m_size, const Point& p){
    size_t numberOfRows = m_size.first;
    size_t numberOfColumns = m_size.second;
    if ( p.x < 0 || p.x >= numberOfColumns || p.y < 0 || p.y >= numberOfRows ){
        throw std::invalid_argument("point out of bounds");
    }
    return p.x + p.y * numberOfColumns;
}

void swap_points(const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec, const Point& p1, const Point& p2){
    size_t numberOfRows = m_size.first;
    size_t numberOfColumns = m_size.second;

    unsigned char temp = vec[get_coord(m_size, p1)];
    vec[get_coord(m_size, p1)] = vec[get_coord(m_size, p2)];
    vec[get_coord(m_size, p2)] = temp;
}

void check_boudries(const std::pair<size_t, size_t>& m_size, const Point& p1, const Point& p2, const Point& delta){
    size_t numberOfRows = m_size.first;
    size_t numberOfColumns = m_size.second;
    size_t width = delta.x;
    size_t height = delta.y;
    if ( p1.x < 0 || p1.x >= numberOfColumns || p1.y < 0 || p1.y >= numberOfRows ){
        throw std::invalid_argument("point out of bounds");
    }
    if ( p1.x + width > numberOfColumns || p1.y + height > numberOfRows ){
        throw std::invalid_argument("rectangle out of bounds");
    }
    if ( p2.x < 0 || p2.x >= numberOfColumns || p2.y < 0 || p2.y >= numberOfRows ){
        throw std::invalid_argument("point out of bounds");
    }
    if ( p2.x + width > numberOfColumns || p2.y + height > numberOfRows ){
        throw std::invalid_argument("rectangle out of bounds");
    }
    if ( !(p1.x + width-1 < p2.x || p2.x + width-1 < p1.x) && !(p1.y > p2.y+height-1 || p2.y > p1.y+height-1) ) {
        throw std::invalid_argument("overlaping rectangles");
    }
}

void swap_points(const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec, const Point& p1, const Point& p2, const Point& delta){
    size_t numberOfRows = m_size.first;
    size_t numberOfColumns = m_size.second;
    size_t width = delta.x;
    size_t height = delta.y;
    check_boudries(m_size, p1, p2, delta);
    Point temp_p1 (p1.x, p1.y);
    Point temp_p2 (p2.x, p2.y);
    for (size_t i = 0; i < height; i++){
        for (size_t j = 0; j < width; j++){
            swap_points(m_size, vec, temp_p1, temp_p2);
            temp_p1.x++;
            temp_p2.x++;
        }
        temp_p1.x = p1.x;
        temp_p2.x = p2.x;
        temp_p1.y++;
        temp_p2.y++;
    }
}

// --------------------- STAGE 3 ---------------------

void decode_picture(const std::string& file, const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec){
    std::ifstream f;
    f.open(file);
    std::string command;

    while ( std::getline ( f, command ) ) {
        std::stringstream s (command);
        unsigned char c1;
        int cis;
        s >> c1;
        switch (c1)
        {
        case 'r': // rotate right
        {  
            if ( s >> cis) {
                rotate_right(m_size, vec, cis);
            } else {
                rotate_right(m_size, vec);
            }
            break;
        }
        case 'l': // rotate left
        {
            if ( s >> cis) {
                rotate_right(m_size, vec, -cis);
            } else {
                rotate_left(m_size, vec);
            }
            break;
        }
        case 'd': // rotate down
        {
            if ( s >> cis) {
                rotate_down(m_size, vec, cis);
            } else {
                rotate_down(m_size, vec);
            }
            break;
        }
        case 'u': // rotate up
        {
            if ( s >> cis) {
                rotate_down(m_size, vec, -cis);
            } else {
                rotate_up(m_size, vec);
            }
            break;
        }
        case 's': // swap
        {
            size_t p1_x, p1_y, p2_x, p2_y;
            s >> p1_x >> p1_y >> p2_x >> p2_y;
            Point p1 (p1_x, p1_y);
            Point p2 (p2_x, p2_y);
            size_t delta_x, delta_y;
            if ( s >> delta_x >> delta_y) {
                Point delta (delta_x, delta_y);
                swap_points(m_size, vec, p1, p2, delta);
            } else {
                swap_points(m_size, vec, p1, p2);

            }
            break;
        }
        default:
            break;
        }
    }
}
