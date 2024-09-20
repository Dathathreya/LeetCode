// 188. Best Time to Buy and Sell Stock IV
int dp[201][1001];
int max(int a,int b){
    return ((a>=b)?(a):(b));
}

#define Buy 0 
#define Sell 1
#define N (int)3e5+1
int dp2[N][2],maxSellAtEnd2[N],maxBuyAtEnd2[N];
int max2(int a,int b){
    return ((a>=b)?(a):(b));
}
int maxProfitII(int* prices, int pricesSize) {
    int day = 0 , end = pricesSize ,maxi=0;
    memset(dp,0,sizeof(dp));memset(maxSellAtEnd,0,sizeof(maxSellAtEnd));
    memset(maxBuyAtEnd,0,sizeof(maxBuyAtEnd));
    for(day=0;day<end;day++){
        if(day<1){
            dp[day][Buy] -= prices[day];
            maxBuyAtEnd[day] = dp[day][Buy]; //direct - wrong answer 
        }
        else{
            dp[day][Buy] = maxSellAtEnd[day-1] - prices[day];
            dp[day][Sell] = max(maxBuyAtEnd[day-1] + prices[day],maxSellAtEnd[day-1]);
            // selling at current day or we can buy and sell at current day with considering whatever max we get from previous
            // selling at day-1
             maxSellAtEnd[day] = max(maxSellAtEnd[day-1] ,dp[day][Sell]);
             maxBuyAtEnd[day] = max(maxBuyAtEnd[day-1] ,dp[day][Buy]);
        }
        maxi = max(maxi,maxSellAtEnd[day]);  
        maxi = max(maxi,maxBuyAtEnd[day]);       
    }
    //  for(day=0;day<end;day++){
    //     printf("%d ",dp[day][Buy]);
    //  }
    //  putchar('\n');
    //  for(day=0;day<end;day++){
    //     printf("%d ",dp[day][Sell]);
    //  }
    //  putchar('\n');
    return maxi;
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
