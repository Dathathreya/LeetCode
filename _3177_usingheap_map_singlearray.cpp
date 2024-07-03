class Solution {
public:
    typedef void    (*swap_self_2d_t)(const void*,int,int,int); // slot,child,parent
    typedef int (*compare_self_2d_t)(const void*,int,int,int); // slot,child,parent
    #define K     57      // atmost k variance   
    #define Items 5004    // uptill current  
    int max_(int a,int b){return ((a>=b)?(a):(b)); }

    static int compfn1(const void* arr,int slot,int child,int parent){
        int* heap = (int*)arr;
        return heap[child*K+slot]<=heap[parent*K+slot]; // follows heap property
    }
    static void swapfn1(const void* arr,int slot,int child,int parent){
            int* heap = (int*)arr;
            int v1 = heap[child*K+slot];
            heap[child*K+slot] = heap[parent*K+slot];
            heap[parent*K+slot] = v1;
            return;
    }
    static void up_heapify(const void* heapN,int root,int current,int slot,compare_self_2d_t compfn,swap_self_2d_t swapfn){
            if((current==0)||(compfn(heapN,slot,current,(current-1)/2))){
                   return; 
            }
            else{
               swapfn(heapN,slot,current,(current-1)/2);
               up_heapify(heapN,root,(current-1)/2,slot,compfn,swapfn);     
            }
    }

    int maximumLength(vector<int>& nums, int k) {
        int best[Items][K],heap[Items][K];
        unordered_map<int,int>mp;
        int n=nums.size(),curr=0,_k=0,maxim = 0;;
        
        memset(best,0,sizeof(best));  memset(heap,0,sizeof(heap));
        mp.clear();

        for(int i=0;i<=k;i++){
            best[0][i]=1;
            heap[0][i]=1;maxim= max(maxim,best[0][i]);
        }
    
        mp[nums[0]] = 0;
        for(curr=1;curr<n;curr++){
            int exists = (mp.find(nums[curr])!=mp.end());
            for(_k=k;_k>=0;_k--){
                 if(exists){
                    best[curr][_k] = max(best[curr][_k],best[mp[nums[curr]]][_k]+1);
                 }
                 else {
                    best[curr][_k] = max(best[curr][_k],1);
                 }
                 if(_k)   
                    best[curr][_k] = max(best[curr][_k],heap[0][_k-1]+1);
            }
            int prev_maxi=best[curr][0];
            for(_k=0;_k<=k;_k++){
                best[curr][_k] = max(prev_maxi,best[curr][_k]);
                heap[curr][_k] = best[curr][_k];
                up_heapify(heap,0,curr,_k,compfn1,swapfn1); // O(log(n))
                prev_maxi = max(prev_maxi,best[curr][_k]);
                maxim= max(maxim,best[curr][_k]);
            }
            mp[nums[curr]] = curr;
        }
        return maxim;  
    }
};
