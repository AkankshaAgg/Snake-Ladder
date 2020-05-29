//Breadth first search single source shortest path
#include<iostream>
#include<map>
#include<list>
#include<queue>
#include<climits>
using namespace std;

template<typename T>
class Graph{
    //Not a weighted graph
    //Example 2->(1,3) 
    map<T,list<T> > l;
    public:
        void addEdge(int x,int y){
            l[x].push_back(y);
        }

        int bfs(T src, T dest){
            //Queue for level order traversal
            //Visited using map<T,bool>
            map<T,int> dist;
            map<T,T> parent;
            queue<T>q;
            

            //Initialising all other nodes will have int_max
            for(auto node_pair: l){
                T node = node_pair.first;
                dist[node] = INT_MAX;
            }
            q.push(src);
            dist[src] = 0;
            parent[src] = src;

            while(!q.empty()){
                T node = q.front();
                //cout<<node<<" ";
                q.pop();

                //Neighbors of the node
                for(int nbr: l[node]){
                    if(dist[nbr]==INT_MAX){
                        q.push(nbr);
                        //Mark the neighbour as visited
                        dist[nbr] = dist[node]+1;
                        parent[nbr] = node;
                    }
                }
            }

            //To print the dist to dest node
           /* for(auto node_pair: l){
                cout<<node_pair.first<<" and dist "<<dist[node_pair.first]<<endl;
            }*/
            
            //Backtracing the path
            //Dest to src
            T temp = dest;
            while(temp!=src){
                cout<<temp<<" <-- ";
                temp = parent[temp];
            }
            cout<<src<<endl;
            return dist[dest];
        }
};

int main(){

    //Input
    int board[50] = {0};
    //Snakes and ladders
    board[2] = 13;
    board[5] = 2;
    board[9] = 18;
    board[18] = 11;
    board[17] = -13;
    board[20] = -14;
    board[24] = -8;
    board[25] = 10;
    board[32] = -2;
    board[34] = -22;

    Graph<int> g;
    for(int i=0;i<=36;i++){
        for(int dice = 1;dice<=6;dice++){
            int j = i+dice;
            j += board[j];

            if(j<=36){
                g.addEdge(i,j); //Unweighted but directed edge
            }
        }
    }
    //Graph doesnt know that egde to 36 exist because when 
    //i is 36 then j will be atleast 37 so condition is not satisfied
    g.addEdge(36, 36); //Manually
    cout<<g.bfs(0, 36);

    return 0;
}
