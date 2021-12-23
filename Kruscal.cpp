#include <iostream>
#include <fstream>
#include <string>
#include "graph.h"

using std::cout;
using std::cin;

class dsu
{
private:
    int p[50];
    int r[50];

public:
    dsu(int n) {
        for (int i = 0; i < n; i++) {
            p[i] = i;
            r[i] = 0;
        }
    }

    int find(int a) {
        if (a == p[a]) return a;
        return find(p[a]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (r[a] > r[b]) std::swap(a, b);
            p[b] = a;
            if (r[a] == r[b]) ++r[a];
        }
    }
};

void str_sort(edges_list& res) {
    int size = res.list.size();
    Vector<int> vertkey(2 * size);
    int key1 = 0;
    int key2 = 0;
    int tempindex = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < res[i].fvert.length(); j++) key1 += int(res[i].fvert[j]);
        for (int k = 0; k < res[i].svert.length(); k++) key2 += int(res[i].svert[k]);
        vertkey[i] = key1;
        vertkey[i + size] = key2;
        key1 = key2 = 0;
    }

    for (size_t i = 0; i < size; i++)
    {
        size_t minindex = i;

        for (size_t j = i + 1; j < size; j++) {
            if ((vertkey[j] < vertkey[minindex]) || ((vertkey[j] == vertkey[minindex]) && (vertkey[j + size] < vertkey[minindex + size]))) minindex = j;
        }

        if (minindex != i) {
            std::swap(res[i], res[minindex]);
            std::swap(vertkey[i], vertkey[minindex]);
        }
    }

}

void kruskal(edges_list& graph, edges_list& res) {
    dsu q(50);

    graph.sort(); //sorting by weight

    for (int i = 0; i < graph.list.size(); i++)
    {
        int u = graph.f_indict(graph[i].fvert);
        int v = graph.f_indict(graph[i].svert);

        int setu = q.find(u);
        int setv = q.find(v);

        if (setu != setv) {
            res.add_edge(graph[i]);
            res.add_weight(graph[i].weight);
            q.unite(u, v);
        }
    }

    str_sort(res); //sorting by name
}

int main()
{
    char choice;
    std::string line; //buffer
    std::ifstream i_file("input_file.txt");
    std::ofstream o_file("output_file.txt");
    edges_list g, res;

    adjacency_matrix m(5, false); //matrix graph for BFS and DFS

    while (1) {

        cout << "click f - for typing file path or click m - for typing graph manually, e - for exit, (ent for confirmation): "; //"clear" input
        cin >> choice;
        cin.seekg(1, std::ios::end);
        cin.clear();

        switch (int(choice)) { //options

        case 102: //read file
        case 70:
            if (i_file.is_open()) {
                while (std::getline(i_file, line)) {
                    cout << "\n" << line;
                    g.add_edge(line);
                }
                i_file.close();
                cout << "\n";
            }
            kruskal(g, res);
            cout << "\nMST: \n";
            res.print();
            cout << "\nWeight of MST: " << res.all_weight << "\n";
            if (o_file.is_open()) {
                for (int i = 0; i < res.list.size(); i++) {
                    o_file << res.list[i].fvert + " " + res.list[i].svert + "\n";
                }
                o_file << res.all_weight;
                o_file.close();
            }
            exit(0);
            break;

        case 109: //manual input
        case 77:
            cout << "Input your graph manually, then type \"stop\":\n";
            while (1) {
                std::getline(cin, line);
                if (line == "stop") break;
                g.add_edge(line);
            }
            kruskal(g, res);
            cout << "\nMST: \n";
            res.print();
            cout << "\nWeight of MST: " << res.all_weight << "\n";
            exit(0);
            break;

        case 101:
        case 69:
            exit(0);
            break;

        default:
            cout << "wrong input, try again\n";
            break;
        }
    }
}