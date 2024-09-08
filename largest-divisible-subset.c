/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
typedef struct pair{
    int first;
    int second;
}pair;

typedef int compare_self_t(const void*,int,int);  
typedef void swap_self_t(const void*,int,int);  

void swap_self_int(const void* arr,int left,int right){
    int* a1 = (int*)arr;
    int  t = a1[left] ;a1[left]= a1[right];a1[right]=t;
    return;
}

int compare_self_int(const void* arr,int left,int right){
    int* a1 = (int*)arr;
    return a1[left] <= a1[right]; 
}

void heapify(const void* arr,int root,int sz,compare_self_t compfn,swap_self_t swapfn){
    int left = (root<<1)+1 , right = (root<<1)+2,greatest=root;
    if((left<sz)&&(compfn(arr,greatest,left))){
        greatest = left;
    }
    if((right<sz)&&(compfn(arr,greatest,right))){
        greatest = right;
    }
    if(greatest!=root){
        swapfn(arr,greatest,root);
        heapify(arr,greatest,sz,compfn,swapfn);
    }
}
void heapSort(const void* arr,int low,int high,compare_self_t compfn,swap_self_t swapfn){
    for(int i=low+((high+low)/2);i>=low;i--){
        heapify(arr,i,high+1,compfn,swapfn);// start from all possible roots  going upwards
    }
    for(int i=high;i>=low;i--){
        swapfn(arr,low,i);
        heapify(arr,low,i,compfn,swapfn);
    }
    return;
}
int* largestDivisibleSubset(int* nums, int numsSize, int* returnSize) {
        int* res=(int*)malloc(1001*sizeof(int));
        int n = numsSize;
        pair vec[n];
        heapSort(nums,0,n-1,compare_self_int,swap_self_int); // sort pairs of index and values
        vec[0].first = -1; 
        vec[0].second = 1; 
        int gr_cnt = 1,gr_ind = 0;
        for(int i=1;i<n;i++){
            bool found =  false;
            /// maximum possible ending index 
            int index=-1,cnt=0; 
            for(int j=i-1;j>=0;j--){
                if((nums[i]%nums[j])==0){
                        found = true;
                        if(vec[j].second>cnt){// keep finding  index having bigger count
                            index = j;
                            cnt = vec[j].second;
                        }
                }
            }
            if(!found){
                vec[i].first = -1;
                vec[i].second = 1;
            }
            else{
                vec[i].first = index; // re-construction using trace back with prev index 
                vec[i].second = cnt+1;
            }
            if(vec[i].second>gr_cnt){
                gr_ind = i;
                gr_cnt = vec[i].second;
            }
        }
        int sz = 0;
        while(gr_ind!=-1){
                res[sz++]=nums[gr_ind];
                gr_ind = vec[gr_ind].first;
        }
        *returnSize = sz;
        return res;
}
