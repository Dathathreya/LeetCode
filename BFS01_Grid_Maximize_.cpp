class Solution {
    public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
       int rowSize = grid.size(), colSize = grid[0].size();
       int minimize[rowSize+1][colSize+1];
       memset(minimize,0,sizeof(minimize));
       minimize[0][0] = health - grid[0][0];
       queue<pair<int,int>>pq;
       pq.push({0,0});
       int dr[4][2] = {{0,-1},{0,+1},{1,0},{-1,0}};
       while(!pq.empty()){
            auto Top = pq.front();
            pq.pop();
            int row = Top.first;
            int col = Top.second;
            int currentHealth = minimize[row][col]; // current 
            if((row==(rowSize-1))&&(col==(colSize-1))){
                return true;
            }
            // neigbours 
            for(int w = 0;w<4;w++){ // get using up ,down, left, right directions
                int nX = row + dr[w][0];    
                int nY = col + dr[w][1];    
                if((nX>=0)&&(nY>=0)&&(nX<rowSize)&&(nY<colSize)){
                       int newHealth = currentHealth - grid[nX][nY];
                       if(minimize[nX][nY]<newHealth){ // can we maximize as we get better value at this node
                            minimize[nX][nY] = newHealth;
                            pq.push({nX,nY});
                       } 
                }
            }
       } 
       return false;
    }
};
