#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long long int ll;
typedef unsigned int ui;
typedef unsigned long long ull;
typedef unsigned long long int ulli;

vector<pair<int, int> > g[10000];
vector<pair<int, int> > REV[100000];
vector<pair<int, pair<int, int> > > edges;
vector<int> parent(100000);
vector<bool> visited(10000, false);
map<string, int> mp;
map<int, string> revmp;
int hash_value=0;

void fast_io(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
}

//intializes DSU
void init(){
    for(int i = 0; i <= hash_value+5; i++){
        visited[i]=false;
        parent[i]=i;
    }
}

//To map an airport name to an index
void H(string s){
    hash_value++;
    mp[s] = hash_value;
    revmp[hash_value] = s;
}

//To get the index of an airport
int getHash(string s){
    return mp[s];
}

//To get airport name from index
string getAirport(int x){
    return revmp[x];
}

//creates a node
void create_airport(string s){
    H(s);
    cout << "Airport has been created." << endl << endl;
}

//creates and edge
void create_route(string a, string b, int c){
    int x = getHash(a);
    int y = getHash(b);
    g[x].push_back({y, c});
    REV[y].push_back({x, c});
    edges.push_back({c, {x, y}});
    cout << "Route has been created." << endl << endl;
}

//test function
void dfs(int x){
    visited[x] = true;
    cout << getAirport(x) << " ";
    vector<pair<int, int> >::iterator y;
    for(y = g[x].begin(); y != g[x].end(); y++){
        if(!visited[y->first]){
            dfs(y->first);
        }
    }
}

//Dijkstra
void findCheapest(string s, string d){
    int src = getHash(s);
    int dest = getHash(d);

    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    vector<int> dist(hash_value+10, 100000);

    pq.push({0, src});
    dist[src]=0;

    while(!pq.empty()){

        int u = pq.top().second;
        pq.pop();

        vector<pair<int, int> >::iterator i;
        for(i = g[u].begin(); i != g[u].end(); i++){
            int v = i->first;
            int wgt = i->second;
            if(dist[v] > dist[u]+wgt){
                dist[v] = dist[u]+wgt;
                pq.push({dist[v], v});
            }
        }

    }

    cout << "Cheapest Route is : " << dist[dest] << endl;

    vector<string> answer;
    int curr = dest;
    while(curr != src){
        answer.push_back(getAirport(curr));
        vector<pair<int, int> >::iterator it;
        int select = -1;
        for(it = REV[curr].begin(); it != REV[curr].end(); it++){
            if(dist[curr] == dist[it->first] + it->second){
                select = it->first;
            }
        }
        curr = select;
    }
    cout << getAirport(src) << " -> ";
    for(int i = answer.size()-1; i >= 0; i--){
        cout << answer[i] << " -> ";
    }
    cout << endl << endl;

}

int find_set(int v){
    if(v==parent[v])return v;
    return parent[v] = find_set(parent[v]);
}

void merge(int a, int b){
    a = find_set(a);
    b = find_set(b);
    if(a != b){
        parent[b]=a;
    }
}

//Disjoint Set Union
void dsu(){
    init();
    for(int i = 0; i <= hash_value; i++){
        vector<pair<int, int> >::iterator it;
        for(it = g[i].begin(); it != g[i].end(); it++){
            merge(i, it->first);
        }
    }

    set<int> st;
    for(int i = 1; i <= hash_value; i++){
        st.insert(find_set(i));
    }

    vector<int> disjoint;
    for(set<int>::iterator it = st.begin(); it != st.end(); it++){
        disjoint.push_back(*it);
    }

    if(disjoint.size()==1){
        cout << "All cities are connected. No new flight routes are necessary." << endl << endl;
    } else {
        cout << "Required New Routes are :- " << endl;
        for(int i = 1; i < disjoint.size(); i++){
            cout << getAirport(disjoint[i-1]) << " -> " << getAirport(disjoint[i]) << endl;
        }
    }

}

//Kruskal's MST
void kruskal(){
    init();
    sort(edges.begin(), edges.end());
    cout << "The following Flight Routes can be cancelled : " << endl;
    for(int e = 0; e < edges.size(); e++){
        int u = edges[e].second.first;
        int v = edges[e].second.second;
        if(find_set(u) != find_set(v)){
            merge(u, v);
        } else {
            cout << getAirport(u) << " -> " << getAirport(v) << endl;
        }
    }
    cout << endl;
}

int main(){

    fast_io();
    //code starts here

    int flag=1;
    cout << "--------- Flight Route Analyzer ---------" << endl;
    while(flag){

        cout << "Enter Operation to Perform :- " << endl;
        cout << "1) Create New Airport" << endl;
        cout << "2) Create New Flight Route" << endl;
        cout << "3) Find Cheapest Route" << endl;
        cout << "4) Recommend New Flight Route" << endl;
        cout << "5) Recommend Cancellation of Flight Routes" << endl;
        cout << "6) Stop" << endl;

        int inp;
        cin >> inp;

        if(inp==1){
            cout << "Enter name of the Airport : " << endl;
            string name;
            cin >> name;
            create_airport(name);
            cout << endl;
        } else if(inp==2){
            cout << "Enter source and destination city : " << endl;
            string src, dest;
            cin >> src >> dest;
            cout << "Enter cost of ticket : " << endl;
            int cost;
            cin >> cost;
            create_route(src, dest, cost);
            cout << endl;
        } else if(inp==3){
            cout << "Enter source and destination city : " << endl;
            string src, dest;
            cin >> src >> dest;
            cout << endl;
            findCheapest(src, dest);
        } else if(inp==4){
            dsu();
        } else if(inp==5){
            kruskal();
        } else if(inp==6){
            flag=0;
            break;
        } else {
            flag=0;
            break;
        }

    }


    return 0;
}
