// count-connected-components-in-lcm-graph
#define N ((int)2e5+5)
typedef int compare_self_t(const void* ar,int fr,int sc);
typedef void swap_self_t(const void* ar,int fr,int sc);

int compare_self_int(const void* arr,int f,int s){
    int* a1 =(int*)arr;
    return (a1[f]<a1[s]);
}

void swap_self_int(const void *arr,int f,int s){
    int* a1 =(int*)arr; 
    int t=a1[f];
    a1[f]=a1[s];
    a1[s]=t;
    return;
}
    
void heapify(const void* arr,int root,int sz,compare_self_t compfn,swap_self_t swapfn){
    int greatest = root,left=2*root+1,right=2*root+2;
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
    for(int z=(low+(high-low)/2);z>=low;z--){
        heapify(arr,z,high+1,compfn,swapfn);    
    }
    for(int end=high;end>=low;end--){
        swapfn(arr,low,end);    
        heapify(arr,low,end,compfn,swapfn);    
    }
}

int parent[N],size[N],countOfConnectedComponents=0,hmap[N];

void DSU_init(int threshold){
    for(int index=0;index<=threshold;index++){       
        parent[index] = index;
        size[index] = 1;
    }
    return;
}
int findparent(int x){
    if(x==parent[x]){
        return x;
    }
    return parent[x]=findparent(parent[x]);
}
void unite(int num1,int num2){
    int parent1 = findparent(num1);
    int parent2 = findparent(num2);
    if(parent1==parent2){
        return;
    }
    if(size[parent1]>=size[parent2]){
        parent[parent2/*son*/] = parent1;
        size[parent1] += size[parent2];
    }   
    else{
        parent[parent1/*son*/] = parent2;
        size[parent2]+= size[parent1];
    } 
}   
int countComponents(int* nums, int numsSize, int threshold) {
    int sz = numsSize,i=0;
    heapSort(nums,0,sz-1,compare_self_int,swap_self_int); // o(n*logn)
    DSU_init(threshold);
    memset(hmap,0,sizeof(hmap));
    countOfConnectedComponents = 0;
    for(i=0;i<sz;i++){ // n
        if(nums[i] > threshold){
            countOfConnectedComponents = sz-i;
            break;           
        }
        for(int mul=nums[i];mul<=threshold;mul+=nums[i]){ // log(n)
            unite(nums[i],mul); 
        }
    }
    // find absolute parent step mandatory 
    for(i=1;i<sz;i++){ // n
        if(nums[i]>threshold){
            break;
        }
        parent[nums[i]] = findparent(nums[i]);
    }
    if(nums[0]<=threshold)
     {   countOfConnectedComponents++;  }
    hmap[parent[nums[0]]]++;
    for(i=1;i<sz;i++){ // n
        if(nums[i]>threshold){
            break;
        }
        if(hmap[parent[nums[i]]]==0){
            countOfConnectedComponents++;
        }
        hmap[parent[nums[i]]]++;
    }  
    return countOfConnectedComponents;
}
