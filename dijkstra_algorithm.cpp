#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
using namespace std;

const int INF = numeric_limits<int>::max();

struct DijkstraResultChar {
    unordered_map<char, char> pred;
    unordered_map<char, int> dist;
};

DijkstraResultChar DijkstraChar(
    const vector<char>& vertices, 
    const unordered_map<char, vector<pair<char, int>>>& adj_list,char s) {
    unordered_map<char, char> pred;
    unordered_map<char, int> dist;
    
    priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> pq;

    for (char v : vertices) {
        pred[v] = -1;
        if (v != s)
            dist[v] = INF;
        else
            dist[v] = 0;
        pq.push({dist[v], v});
    }

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        if (adj_list.find(u) != adj_list.end()) {
            for (const auto& neighbor : adj_list.at(u)) {
                char v = neighbor.first;
                int weight_u_v = neighbor.second;

                if (dist[u] != INF && dist[v] > dist[u] + weight_u_v) {
                    dist[v] = dist[u] + weight_u_v;
                    pred[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    return {pred, dist};
}

int main() {
    vector<char> vertices = {'1', '2', '3', '4', '5', '6', '7', '8'};

    unordered_map<char, vector<pair<char, int>>> adj_list;
    adj_list['1'] = {{'2', 8}, {'3', 2}, {'4', 4}, {'5', 3}};
    adj_list['2'] = {{'1', 8}, {'5', 6}, {'6', 3}};
    adj_list['3'] = {{'1', 2}, {'4', 6}, {'6', 7}, {'8', 4}};
    adj_list['4'] = {{'1', 4}, {'3', 6}, {'5', 1}};
    adj_list['5'] = {{'1', 3}, {'2', 6}, {'4', 1}, {'7', 4}};
    adj_list['6'] = {{'2', 3}, {'3', 7}, {'7', 3}, {'8', 1}};
    adj_list['7'] = {{'5', 4}, {'6', 3}, {'8', 5}};
    adj_list['8'] = {{'3', 4}, {'6', 1}, {'7', 5}};

    char start_node = '1';
    DijkstraResultChar result = DijkstraChar(vertices, adj_list, start_node);

    for (char v : vertices) {
        cout << "dist[" << v << "] = ";
        if (result.dist[v] == INF)
            cout << "∞";
        else
            cout << result.dist[v];
        
        cout << ", pred[" << v << "] = " << (result.pred[v] == -1 ? '?' : result.pred[v]) << "\n";
    }

    return 0;
}
