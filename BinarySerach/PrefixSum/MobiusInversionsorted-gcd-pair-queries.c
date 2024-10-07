/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define I ((int)1e6+5) 
typedef long long int lli;
lli cnt[I],i,maxi=0,multiples;
int upperbound(lli* cnt,int low,int high,lli x){
    while((high-low)>1){
        int mid = (low+high)/2;
        if(cnt[mid]>x){
            high = mid;
        }
        else{
            low = mid;
        }
    }
    return high;
}
int* gcdValues(int* nums, int numsSize, long long* queries, int queriesSize, int* returnSize) {
    int* res = (int*)malloc(queriesSize*sizeof(int));memset(cnt,0,sizeof(cnt));*returnSize=queriesSize;maxi=0;
    int q =queriesSize;
    for(i=0;i<numsSize;i++){
        cnt[nums[i]]++;maxi=(maxi>=nums[i])?(maxi):(nums[i]);
    }   
    for(i=1;i<=maxi;i++){
        for(int mul=2*i;mul<=maxi;mul+=i){
            cnt[i] += cnt[mul]; 
        }
        cnt[i] = ((cnt[i]-1)*(cnt[i]))/2;
    }
    for(i=maxi;i>=1;i--){
        for(int mul=2*i;mul<=maxi;mul+=i){
            cnt[i] -= cnt[mul]; 
        }
    }
    for(i=1;i<=maxi;i++){
            cnt[i] += cnt[i-1];
    }
    for(i=0;i<q;i++){
        res[i] = upperbound(cnt,0,maxi,queries[i]);
    }
    return res;
}

