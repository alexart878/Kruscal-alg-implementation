#pragma once
#include <iostream>
#include "data_structures.h";

class edges_list {

private:

    struct edge {

        std::string fvert, svert;
        size_t weight;

        edge() {
            fvert = svert = "";
            weight = -1;
        };

        edge(std::string s) {
            size_t spacenum = s.find(" ");
            fvert = s.substr(0, spacenum);
            spacenum = s.find(" ", spacenum + 1);
            svert = s.substr(fvert.length() + 1, spacenum - fvert.length() - 1);
            weight = std::stoi(s.substr(spacenum + 1, s.length() - spacenum - 1));
        }
    };

public:
    Vector<edge> list;
    Vector<std::string> dictionary;
    size_t all_weight;
    
    edges_list() {};
    ~edges_list() {};
    void add_edge(std::string line);
    void add_edge(edge e);
    void add_weight(size_t weight);
    void sort();
    edge& operator[] (size_t index) { return list[index]; };
    int f_indict(std::string vert);
    void print();
};

void edges_list::add_edge(std::string line) {
    edge temp(line);
    if (f_indict(temp.fvert) == -1) dictionary.push_back(temp.fvert);
    if (f_indict(temp.svert) == -1) dictionary.push_back(temp.svert);
    list.push_back(temp);
}

void edges_list::add_edge(edge e) {
    if (f_indict(e.fvert) == -1) dictionary.push_back(e.fvert);
    if (f_indict(e.svert) == -1) dictionary.push_back(e.svert);
    list.push_back(e);
};

void edges_list::add_weight(size_t weight) { all_weight += weight; };

void edges_list::sort()
{
    for (size_t i = 0; i < list.size(); i++)
    {
        size_t minindex = i;

        for (size_t j = i + 1; j < list.size(); j++) {
            if (list[j].weight < list[minindex].weight) minindex = j;
        }

        if (minindex != i) std::swap(list[i], list[minindex]);
    }
}

int edges_list::f_indict(std::string vert) {
    for (int i = 0; i < dictionary.size(); i++) if (dictionary[i] == vert) return i;
    return -1;
}

void edges_list::print() {
    std::cout << std::endl;
    for (size_t i = 0; i < list.size(); i++) std::cout << list[i].fvert << " " << list[i].svert << "\n";
}

//adj matrix, DFS and BFS
class adjacency_matrix 
{
private:
    Vector<Vector<int>> matrix;
    bool is_oriented;
    Vector<bool> visited;

public:

    adjacency_matrix() {};
    
    adjacency_matrix(int size, bool b) {
        matrix.resize(size);
        visited.resize(size);
        is_oriented = b;
        for (int i = 0; i < size; i++) {
            matrix[i].resize(size);
            visited[i] = false;
            for (int j = 0; j < size; j++) matrix[i][j] = -1;
        }
    };
    
    void add_edge(int u, int v, int weight) {
        is_oriented == true ? matrix[u][v] = weight : matrix[u][v] = matrix[v][u] = weight;
    }
    
    void print_matr() {
        std::cout << std::endl;
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix.size(); j++) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void bfs(int start) {
        for (int i = 0; i < matrix.size(); i++) visited[i] = false;
        Queue<int> q;

        q.enQueue(start);
        visited[start] = true;

        int vis;
        while (!q.is_empty()) {
            vis = q.front->data;

            std::cout << vis << " ";
            q.deQueue();

            for (int i = 0; i < matrix[vis].size(); i++) {
                if ((matrix[vis][i] != -1) && (!visited[i])) {
                    q.enQueue(i);
                    visited[i] = true;
                }
            }
        }
    }

    void dfs(int start) {
        std::cout << start << " ";

        visited[start] = true;

        for (int i = 0; i < matrix[start].size(); i++) {
            if (matrix[start][i] != -1 && (visited[i] == false)) {
                dfs(i);
            }
        }
    }

    void visit_clean() {
        for (int i = 0; i < matrix.size(); i++) visited[i] = 0;
    }
};