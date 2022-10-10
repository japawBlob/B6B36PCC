#include "crusoe.hpp"

// ------------------- stage 1 -------------------

vertex::vertex(std::string str, int x, int y, std::string  col):
    xy(x, y),
    name(str),
    c_forward(col)
{}

bool vertex::add_neighbour(size_t vv, const std::string& col){
    for (auto & blob : this->neighbours) {
        if (blob.first == vv) {
            return false;
        }
    }
    this->neighbours.push_back(std::make_pair(vv, col));
    return true;
}

std::vector<std::pair<size_t, std::string>> vertex::get_neighbour() const {
    return this->neighbours;
}

std::pair<int, int> vertex::get_xy() const {
    return this->xy;
}

void vertex::set_color(const std::string& col) {
    this->c_forward = col;
}

std::string vertex::get_color() const {
    return this->c_forward;
}

void vertex::set_edge_color(size_t vv, const std::string& col){
    for (auto & blob : this->neighbours){
        if (blob.first == vv){
            blob.second = col;
            break;
        }
    }
}

std::string vertex::get_edge_color(size_t vv){
    for ( const auto & blob : this->neighbours){
        if (blob.first == vv){
            return blob.second;
        }
    }
    return "#FFFFFF";
}

void graph::add_vertex(int x, int y, const std::string& col){
    this->vertices.push_back(vertex(std::to_string(this->num_elem++), x, y, col));
}

void graph::add_edge(size_t v1, size_t v2, const std::string& col){
    if (this->vertices[v1].add_neighbour(v2, col)){
        this->vertices[v2].add_neighbour(v1, col);
    }
}

bool graph::is_edge(size_t v1, size_t v2) const {
    for ( auto & blob : this->vertices[v1].get_neighbour()){
        if (blob.first == v2) {
            return true;
        }
    }
    return false;
}

std::string graph::edge_color(size_t v1, size_t v2) const {
    for ( auto & blob : this->vertices[v1].get_neighbour()){
        if (blob.first == v2) {
            return blob.second;
        }
    }
    return "#FFFFFF";
}

std::string graph::vertex_color(size_t v1) const {
    if (v1 >= num_elem){
        return "#FFFFFF";
    }
    return this->vertices[v1].get_color();
}

void graph::set_vertex_color(size_t v1, const std::string& col) {
    if (v1 >= num_elem){
        return ;
    }
    this->vertices[v1].set_color(col);
}

void graph::set_edge_color(size_t v1, size_t v2, const std::string& col) {
    this->vertices[v1].set_edge_color(v2, col);
    this->vertices[v2].set_edge_color(v1, col);
}

bool graph::empty() const {
    if (this->num_elem == 0){
        return true;
    } else {
        return false;
    }
}

size_t graph::size() const {
    return num_elem;
}

size_t graph::num_edge() const {
    size_t num_edge = 0;
    for (auto & blob : this->vertices) {
        num_edge += blob.get_neighbour().size();
    }
    return num_edge/2; 
}

// ------------------- stage 2 -------------------

vertex graph::get_vertex(size_t num) const{
}

void graph::is_achievable(size_t from, std::vector<size_t>& achieved){

}

void graph::color_component(std::vector<size_t> cmp, const std::string& col){

}

std::vector<size_t> graph::path(size_t v1, size_t v2){

}

void graph::color_path(std::vector<size_t> pth, const std::string& col){
    
}

graph::graph_comp::graph_comp(graph& gg) :
    gg(gg)
{}

void graph::graph_comp::color_componennts(){

}

size_t graph::graph_comp::count() const {

}

size_t graph::graph_comp::count_without_one() const {

}

size_t graph::graph_comp::max_comp() const {

}

size_t graph::graph_comp::size_of_comp(size_t i) const{

}

std::vector<size_t> graph::graph_comp::get_component(size_t i) const {

}

bool graph::graph_comp::same_comp(size_t v1, size_t v2) const {

}

graph::graph_fence::graph_fence(graph& gg, size_t vv, size_t distance) :
    gg(gg)
{}

void graph::graph_fence::color_fence(const std::string& col){

}

size_t graph::graph_fence::count_stake() const {

}

size_t graph::graph_fence::get_stake(size_t i) const {

}
