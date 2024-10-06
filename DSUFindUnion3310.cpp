class Solution {
public:
    bool buggy[200007],visited[200007],connected[200007];
    int  parent[200007],size[200007];
    // absolete parent of current node
    // size of absolete parent of current node
    // if absolete parent of current node includes non-buggy node then every element in that 
    // set need to be included.
    vector<vector<int>>adj;
    vector<int>st;bool include=false;
    void spreaddfs(int s){ // dfs - o(n)
        visited[s]= true;
        buggy[s] = true;
        for(auto itr: adj[s]){
            if(!visited[itr]){
                spreaddfs(itr);
            }
        }
    }
    int findparent(int node,bool containsNB){
        if(node==parent[node]){
            connected[node] |= containsNB;
            return node;
        }
        parent[node] = findparent(parent[node],containsNB);
        return parent[node];
    }
    void make_set(int nd){
        if(size[nd]==0) size[nd] = 1;
    }
    void  unite(int node1,int node2){
        int abparent1 = findparent(node1,!buggy[node1]);
        int abparent2 = findparent(node2,!buggy[node2]);
        //printf("(%d,%d)-",abparent1,abparent2);
        if(abparent1!=abparent2) // not united
        {
            make_set(abparent1);make_set(abparent2);
            if(size[abparent1]<=size[abparent2]){
                size[abparent2] += size[abparent1];                
                parent[abparent1] = abparent2;
                connected[abparent2] |= connected[abparent1]; 
            }  
            else {
                size[abparent1] += size[abparent2];
                parent[abparent2] = abparent1;
                connected[abparent1] |= connected[abparent2]; 
            }
        }
    }
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<int> res;
        memset(buggy,false,sizeof(buggy));memset(visited,false,sizeof(visited));
        memset(buggy,false,sizeof(connected));
        memset(size,0,sizeof(size));
        adj.clear();
        for(int y=0;y<n;y++){
            vector<int> vec;
            adj.push_back(vec);
            parent[y] = y;
        }
        int invs=invocations.size();
        for(int y=0;y<invs;y++){
            adj[invocations[y][0]].push_back(invocations[y][1]);
        }
        spreaddfs(k); // dfs , B -> NB this is done 
        memset(connected,false,sizeof(connected)); 
        for(int y=0;y<invs;y++){
            unite(invocations[y][0],invocations[y][1]); //  NB -> B
        }
        for(int y=0;y<n;y++){
             parent[y]=findparent(y,!buggy[y]);
        }
        for(int y=0;y<n;y++){
           
            if(!buggy[y]){
                res.push_back(y);
            }
            else if(((parent[y]!=-1)&&(connected[parent[y]]))||(connected[y])){
                    res.push_back(y);
            }
        }
        return res;
    }
};
