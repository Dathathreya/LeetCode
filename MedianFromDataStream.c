typedef struct {
    int mxheap[50071],mnheap[50071],mxh_sz,mnh_sz;    
} MedianFinder;

typedef int (*comp_self_t)(const void* arr,int f,int s);
typedef void (*swap_self_t)(const void* arr,int f,int s);

int getParent(int child){ return (child>0)?((child-1)/2):(child);  }

int compfnMx_int(const void* arr,int f,int s){
    int* obj = (int*)arr;
    return obj[f] <= obj[s];    
}

int compfnMn_int(const void* arr,int f,int s){
    int* obj = (int*)arr;
    return obj[f] >= obj[s];    
}

void swap_self_int(const void* arr,int f,int s){
    int* obj = (int*)arr;
    int t = obj[f];obj[f]=obj[s];obj[s]=t;
    return;    
}

void down_heapify(const void* arr,int root,int size,comp_self_t compfn,swap_self_t swapfn){
    for(;;){
        int leftChild = (2*root)+1,rightChild = (2*root)+2,greatest = root;
        if((leftChild<size)&&(compfn(arr,greatest,leftChild))){
                greatest = leftChild;
        }
        if((rightChild<size)&&(compfn(arr,greatest,rightChild))){
                greatest = rightChild;
        }
        if(greatest!=root){
            swapfn(arr,greatest,root);
            root = greatest;
        }
        else{
            break;
        }
    }   
    return;
}

void   up_heapify(const void* arr,int child,int root,comp_self_t compfn,swap_self_t swapfn){
    for(;;){
        if((child==root)||(compfn(arr,child,getParent(child)))){
            break;
        }
        else{
            swapfn(arr,child,getParent(child));
            child=getParent(child);
        }
    }
    return;
}

MedianFinder* medianFinderCreate() {
    MedianFinder* new_mfinder = (MedianFinder*)malloc(sizeof(MedianFinder));
    memset(new_mfinder->mxheap,0,sizeof(new_mfinder->mxheap));
    memset(new_mfinder->mnheap,0,sizeof(new_mfinder->mnheap));
    new_mfinder->mxh_sz =  new_mfinder->mnh_sz = 0;
    return new_mfinder;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    assert(obj!=NULL);
    obj->mxheap[obj->mxh_sz] = num;
    up_heapify(obj->mxheap,obj->mxh_sz,0,compfnMx_int,swap_self_int);
    obj->mxh_sz++;
    int balance = obj->mxh_sz - obj->mnh_sz;
    if((balance>1)||((obj->mnh_sz>=1)&&(obj->mnheap[0]<obj->mxheap[0]))){
        int new_mini = obj->mxheap[0]; 
        swap_self_int(obj->mxheap,0,--(obj->mxh_sz));
        down_heapify(obj->mxheap,0,obj->mxh_sz,compfnMx_int,swap_self_int);
        obj->mnheap[obj->mnh_sz] = new_mini;
        up_heapify(obj->mnheap,obj->mnh_sz,0,compfnMn_int,swap_self_int);
        obj->mnh_sz++;
    }
    balance = obj->mnh_sz - obj->mxh_sz;
    if(balance>1){
        int new_maxi = obj->mnheap[0]; 
        swap_self_int(obj->mnheap,0,--(obj->mnh_sz));
        down_heapify(obj->mnheap,0,obj->mnh_sz,compfnMn_int,swap_self_int);
        obj->mxheap[obj->mxh_sz] = new_maxi;
        up_heapify(obj->mxheap,obj->mxh_sz,0,compfnMx_int,swap_self_int);
        obj->mxh_sz++;
    }
    return;
}
// Accepted
double medianFinderFindMedian(MedianFinder* obj) {
    assert(obj!=NULL);
    int mnsize = obj->mnh_sz,mxsize=obj->mxh_sz;
    if(mnsize!=mxsize){
        return (mxsize>=mnsize)?(obj->mxheap[0]):(obj->mnheap[0]);
    }
    return ((obj->mxheap[0])+(obj->mnheap[0]))/(2.0);
}

void medianFinderFree(MedianFinder* obj) {
    free(obj);
    return;
}

/**
 * Your MedianFinder struct will be instantiated and called as such:
 * MedianFinder* obj = medianFinderCreate();
 * medianFinderAddNum(obj, num);
 
 * double param_2 = medianFinderFindMedian(obj);
 
 * medianFinderFree(obj);
*/
