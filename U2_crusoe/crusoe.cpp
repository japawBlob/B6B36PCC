#include "crusoe.hpp"
#include <queue>
#include <stack>

static const std::vector<std::string> colors{"red", "olive", "orange", "lightblue", "yellow", "pink", "cyan", "purple", "brown", "magenta"};

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
    if(v1 >= this->size() || v2 >= this->size()){
        return ;
    }
    if (this->vertices[v1].add_neighbour(v2, col)){
        this->vertices[v2].add_neighbour(v1, col);
    }
}

bool graph::is_edge(size_t v1, size_t v2) const {
    if(v1 >= this->size() || v2 >= this->size()){
        return false;
    }
    for ( auto & blob : this->vertices[v1].get_neighbour()){
        if (blob.first == v2) {
            return true;
        }
    }
    return false;
}

std::string graph::edge_color(size_t v1, size_t v2) const {
    if(v1 >= this->size() || v2 >= this->size()){
        return "#FFFFFF";
    }
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
    if(v1 >= this->size() || v2 >= this->size()){
        return ;
    }
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
    return this->vertices[num];
}

void graph::is_achievable(size_t from, std::vector<size_t>& achieved){
    std::vector<bool> visited;
    visited.assign(this->size(), false);

    std::stack<size_t> q;
    q.push(from);
    while (!q.empty()){
        size_t current = q.top();
        q.pop();
        if (visited[current] == true){
            continue;
        }
        visited[current] = true;
        for (const auto & node : this->get_vertex(current).get_neighbour() ){
            if (visited[node.first] == false){
                q.push(node.first);
            }
        }
        achieved.push_back(current);
    }
}

void graph::color_component(std::vector<size_t> cmp, const std::string& col){
    size_t i;
    for (i = 0; i < cmp.size(); i++){
        this->set_vertex_color(cmp[i], col);
        for ( const auto & blob : this->get_vertex(cmp[i]).get_neighbour()) {
            this->set_edge_color(cmp[i], blob.first, col);
        }
    }
}

std::vector<size_t> graph::path(size_t v1, size_t v2){
    std::vector<size_t> cost;
    cost.assign(this->size(), this->size());
    std::vector<size_t> parent;
    parent.assign(this->size(), this->size());
    cost[v1] = 0;
    parent[v1] = v1;

    std::queue<size_t> q;
    q.push(v1);
    while (!q.empty()){
        size_t current = q.front();
        q.pop();
        for (const auto & node : this->get_vertex(current).get_neighbour() ){
            if ( cost[node.first] > cost[current]+1 ){
                cost[node.first] = cost[current]+1;
                parent[node.first] = current;
                if (node.first == v2){
                    break; // dont need to look further, since thanks to the queue functionality, and that every edge cost is 1. I can be certain, that there wont be better path
                }
                q.push(node.first);
            }
        }
    }
    size_t current = v2;
    std::vector<size_t> ret;
    if ( (parent[v2] == this->size()) ) {
        return ret;
    }
    while (current != v1){
        ret.push_back(current);
        current = parent[current];
    }
    ret.push_back(current);
    std::reverse(ret.begin(), ret.end());
    return ret;
}

void graph::color_path(std::vector<size_t> pth, const std::string& col){
    for (size_t i = 0; i < pth.size()-1; i++){
        this->set_edge_color(pth[i], pth[i+1], col);
    }
}

graph::graph_comp::graph_comp(graph& gg) :
        gg(gg)
{
    std::vector<bool> visited;
    visited.assign(gg.size(), false);

    for ( int i = 0; i < visited.size(); i++ ){
        if (visited[i]) {
            continue;
        }
        std::vector<size_t> ach;
        gg.is_achievable(i, ach);
        this->components.push_back(ach);
        for (const auto & blob : ach){
            visited[blob] = true;
        }
    }
}

void graph::graph_comp::color_componennts(){
    for (size_t i = 0; i < this->components.size(); i++){
        this->gg.color_component(this->components[i], colors[i%colors.size()]);
    }
}

size_t graph::graph_comp::count() const {
    return this->components.size();
}

size_t graph::graph_comp::count_without_one() const {
    size_t number_of_components = 0;
    for (const auto & blob : this->components) {
        if (blob.size() > 1){
            number_of_components++;
        }
    }
    return number_of_components;
}

size_t graph::graph_comp::max_comp() const {
    size_t biggest_component_i = 0;
    for (size_t i = 0; i < this->components.size(); i++) {
        if (this->components[i].size() > this->components[biggest_component_i].size()){
            biggest_component_i = i;
        }
    }
    return biggest_component_i;
}

size_t graph::graph_comp::size_of_comp(size_t i) const {
    return this->components[i].size();
}

std::vector<size_t> graph::graph_comp::get_component(size_t i) const {
    return this->components[i];
}

bool graph::graph_comp::same_comp(size_t v1, size_t v2) const {
    if (this->gg.path(v1, v2).size() > 0){
        return true;
    } else {
        return false;
    }
}

graph::graph_fence::graph_fence(graph& gg, size_t vv, size_t distance) :
        gg(gg)
{
    std::vector<size_t> cost;
    cost.assign(gg.size(), gg.size());
    std::vector<size_t> parent;
    parent.assign(gg.size(), gg.size());
    cost[vv] = 0;
    parent[vv] = vv;

    std::queue<size_t> q;
    q.push(vv);
    this->fence.push_back(vv);
    while (!q.empty()){
        size_t current = q.front();
        q.pop();
        for ( const auto & node : gg.get_vertex(current).get_neighbour() ) {
            if ( cost[node.first] <= distance ) {
                cost[node.first] = cost[current]+1;
                parent[node.first] = current;
                q.push(node.first);
                this->fence.push_back(node.first);
            }
        }
    }
}

void graph::graph_fence::color_fence(const std::string& col){
    this->gg.color_component(this->fence, col);
}

size_t graph::graph_fence::count_stake() const {
    return this->fence.size();
}

size_t graph::graph_fence::get_stake(size_t i) const {
    if (i >= this->fence.size()){
        return -1;
    }
    return this->fence[i];
}
