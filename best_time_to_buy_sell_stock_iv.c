// 188. Best Time to Buy and Sell Stock IV
int dp[201][1001];
int max(int a,int b){
    return ((a>=b)?(a):(b));
}
int maxProfit(int k, int* prices, int pricesSize) {
        // B  S  B
        // k1 k2 k3    (100)
        // 3  2  6  5 0 3 (1000) 
        // based on length of this list we decide whether we buy or sell the stock
        // if length is even then we are allowed to buy a stock but not sell  spend money -cost
        // if length is odd then we are allowed to sell a stock but not buy  +cost
        memset(dp,0,sizeof(dp));
        int i,j,n=pricesSize,maxi=0;
        for(i=1;i<=2*k;i++){
            for(j=i-1;j<n;j++){
                  if(i==1){// kth transaction is start so its buy so we lose as we are spending money
                    dp[i][j] = -prices[j];//(((i%2)==1)?(prices[i]):());//i is odd or i is even
                  }  
                  if((i>1)&&(j>=1)){
                    // if ith transaction is even we sell so we gain 
                    // if ith transaction is odd we buy so we spend/loss money 
                      dp[i][j] = dp[i-1][j-1] + (((i%2)==1)?(-prices[j]):(prices[j]));  
                  }
                  if(j>(i-1)){
                      dp[i][j] = max(dp[i][j],dp[i][j-1]);  
                  }
                  maxi = max(maxi,dp[i][j]);// consider maximum among all as we can atmost k transactions
            }
        }
        // for(i=1;i<=2*k;i++){
        //      for(j=0;j<n;j++){
        //             printf("%d ",dp[i][j]);
        //      }   
        //      putchar('\n');
        // }
        return maxi;
        //return dp[2*k][n-1]; // k transactions among n choices 
}
