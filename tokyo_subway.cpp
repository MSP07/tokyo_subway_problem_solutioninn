#include <bits/stdc++.h>
using namespace std;

struct Edge{
    string to;
    int weight;
};

class SubwaySystem{
    unordered_map<string,vector<Edge>>graph;    
    unordered_map<string,string>stations; 
private:    
    vector<string>split(const string& line, char delimiter){
        vector<string>tokens;
        stringstream ss(line);
        string token;
        while (getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }   

public:
    void load(string& filename){
        ifstream file(filename);
        if (!file.is_open()) {
        cerr << "Error: Unable to open file" << endl;
        return;
        }string 

    string line;
    while (getline(file, line)) {
        if(line.empty() || line[0] == '#') continue;
        if(line.find("->") != string::npos){
            auto parts = split(line, ',');
            auto connection = split(parts[0], '>');
            string from = connection[0];
            string to = connection[1];
            int weight = stoi(parts[1]);
            graph[from].push_back({to, weight});
            graph[to].push_back({from, weight});
        }else{
            auto parts = split(line, ',');
            string station_id = parts[0];
            string station_name = parts[1];
            stations[station_id] = station_name;
        }
    }
        file.close();
    }

    pair<vector<string>, int>shortestPath(string& start,string& end){
        unordered_map<string, int> distances;   
        unordered_map<string, string> prev;     
        for (auto& node : graph){
            distances[node.first] = numeric_limits<int>::max();
        }
        distances[start] = 0;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
        pq.push({0, start});
        while(!pq.empty()){
            auto [currdist, currstations] = pq.top();
            pq.pop();
            if(currstations == end) break; 
            for(auto& edge : graph[currstations]){
                int new_distance = currdist + edge.weight;
                if(new_distance < distances[edge.to]){
                    distances[edge.to] = new_distance;
                    prev[edge.to] = currstations;
                    pq.push({new_distance, edge.to});
                }
            }
        }
        vector<string>path;
        string station = end;
        while(station != start){
            path.push_back(station);
            if (prev.find(station) == prev.end()){
                return {{}, -1};
            }
            station = prev[station];
        }
        path.push_back(start);
        reverse(path.begin(), path.end());
        return {path, distances[end]};
    }

    void displayPath(vector<string>& path, int tt){
        if(path.empty()){
            cout << "No path found" << endl;
            return;
        }
        cout << "Shortest path: ";
        for (size_t i = 0; i < path.size(); ++i){
        cout << path[i];
        if (i < path.size() - 1) cout << " -> ";
        }
        cout << endl;
        cout << "Total travel time: " << tt << " minutes" << endl;
    }
};

int main() {
    SubwaySystem subway;
    string filename = "tokyo_subway.txt";
    subway.load(filename);
    string start_station, end_station;
    cout << "Enter the start station ID: ";
    cin >> start_station;
    cout << "Enter the end station ID: ";
    cin >> end_station;
    auto [path, tt] = subway.shortestPath(start_station, end_station);
    subway.displayPath(path, tt);
    return 0;
}
