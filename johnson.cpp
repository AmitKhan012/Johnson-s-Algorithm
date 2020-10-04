# include <bits/stdc++.h>
using namespace std;

# define MAX 100
# define pp pair <int, int>

vector <pp> G[MAX];
int node = 0;
int h[MAX];
int dis[MAX][MAX];
int path[MAX][MAX];

class Prioritize{
public:
    bool operator() ( const pp& p1, const pp& p2){
        return p1.second < p2.second;
    }
};

bool Bellmanford(int s){

    int len;
    for(int i = 1; i <= node; i++){
        h[i] = 10000;
    }
    h[s] = 0;

    for(int i = 1; i <= node; i++){
        for(int j = 1; j <= node + 1; j++){
            len = G[j].size();
            for(int k = 0; k < len; k++){
                if(h[j] + G[j][k].second < h[G[j][k].first]){
                    h[G[j][k].first] = h[j] + G[j][k].second;
                }
            }
        }
    }

    for(int j = 1; j <= node + 1; j++){
            len = G[j].size();
            for(int k = 0; k < len; k++){
                if(h[j] + G[j][k].second < h[G[j][k].first]){
                    return false;
                }
            }
    }
    return true;
}

void reweight(){
    int len;
    for(int j = 1; j <= node; j++){
        len = G[j].size();
        for(int k = 0; k < len; k++)
            G[j][k].second = G[j][k].second + h[j] - h[G[j][k].first];
     }
}

void dijkstra(int s){
    int len, a, b, w;
    priority_queue <pp, vector <pp>, Prioritize> q;
    for(int i = 1; i <= node; i++){
        dis[s][i] = 100000;
    }
    dis[s][s] = 0;
    path[s][s] = s;
    q.push(pp(s, dis[s][s]));
    while(!q.empty()){
        a = q.top().first;
        q.pop();
        len = G[a].size();
        for(int i = 0; i < len; i++){
            b = G[a][i].first;
            w = G[a][i].second;
            if(dis[s][b] > dis[s][a] + w){
                dis[s][b] = dis[s][a] + w;
                q.push(pp(b, dis[s][b]));
                path[s][b] = a;
            }
        }
    }
}

void getpath(int s, int d){
    if(dis[s][d] == 100000){
        cout << "No Path" << endl;
        return;
    }
    vector <int> Path;
    int distance = dis[s][d] - h[s] + h[d];
    Path.push_back(d);
    while(d != s){
        Path.push_back(path[s][d]);
        d = path[s][d];
    }
    int len = Path.size();
    cout << "Shortest path: ";
    for(int i = len - 1; i >= 0; i--){
        cout << Path[i] << " ";
    }
    cout << endl;
    cout << "Distance: " << distance  << endl;
}

int main(){

    int a, b, w, s, d;
    FILE *p = fopen("input.txt", "r");
    while(true){
        fscanf(p, "%d %d %d", &a, &b, &w);
        if(a == 0 && b == 0){
            break;
        }
        if(a > b){
            if(a > node)
                node = a;
        }
        else{
            if(b > node)
                node = b;
        }
        G[a].push_back(pp(b,w));
    }

    for(int i = 1; i <= node; i++){
        G[node+1].push_back(pp(i,0));
    }

    bool tf = Bellmanford(node+1);
    if(tf){
        reweight();
        for(int i = 1; i <= node; i++){
            dijkstra(i);
        }
        fscanf(p, "%d %d", &s, &d);
        getpath(s, d);
    }
    else{
        cout << "Negative cycle detected" << endl;
    }


}


