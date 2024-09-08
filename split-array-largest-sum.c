typedef long long int lli;
lli maxiResult = 0 ,subarraysum=0; int miniResult = 0,i,n;
bool check(int* nums,lli sum,lli parititions){
    int paritition_so_far = 1; // we have entire subarray without partitions
    i=0;subarraysum=0;
    while(i<n){
        // greedily 
        if(subarraysum+nums[i] <= sum){
            subarraysum+=nums[i];
        }
        else{ 
            paritition_so_far+=1;
            subarraysum=nums[i];
        }
        i++;
    }
    return (paritition_so_far <= parititions);
}
int splitArray(int* nums, int numsSize, int k) {
     //  minimum sub-array sum  element would be that element itself 
     //  maximum sub-array sum element would be entire subarray 
     // fix min and max sums before binary search over entire range 
      n= numsSize; 
      maxiResult = 0;
      miniResult = 0;
      i=0;
      while(i<n){
         maxiResult += nums[i];
         if(nums[i]>miniResult){
            miniResult = nums[i];
         }
         i++;
      }
      // we find maximum among all the subarrays after doing k splits over n elements  - 1
      // so minimum  sum number possible is maximum single element 
      // maximum sum number would be  entire sub array  
      // we want to find minimum sum after we get sum after performing op1 for all possible combinations
      // we use binary search to pick sum which could be formed with k partitions 
      // if not search over right range 
      // if yes search over left range 
      // check function will increase parititions if sum exceeds and compare it with what we can perform vs 
      // what was performed 
      lli ans = 0;int cuts = k;
      while(maxiResult>=miniResult){
        lli mid = miniResult + (maxiResult-miniResult)/2;
        if(check(nums,mid,cuts)){
            ans = mid;
            maxiResult = mid-1 ;
        }
        else{
            miniResult = mid+1;
        }
      }  
      return ans;
}
