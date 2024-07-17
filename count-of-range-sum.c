typedef int  comp_self_t(const char* arr,int f,int s);
typedef void swap_self_t(const char* arr,int f,int s);
typedef  long long int lli;
#define N 100700
lli prefix[N],suffix[N],temp[N],sum[N],ni[N];
int sz;
int count=0;
 
void Imerger(lli* arr1,int low,int mid,int high){
     int start=low,start2 = mid+1,tidx=low;
     while((start<=mid)&&(start2<=high)){
            if(arr1[start]<=arr1[start2]){
               temp[tidx++] = arr1[start++]; 
            }
            else{
               temp[tidx++] = arr1[start2++]; 
            }
     }
     while(start<=mid){
        temp[tidx++] = arr1[start++]; 
     }
     while(start2<=high){
        temp[tidx++] = arr1[start2++]; 
     }
     for(int i=low;i<=high;i++){
        arr1[i]=temp[i];
     }
     return;
}

int inrange(lli x,int li,int hi){
    return ((x>=li)&&(x<=hi));
}

int max(int a,int b){ return ((a>=b)?(a):(b));}
int min(int a,int b){ return ((a<=b)?(a):(b));}

void merger(lli* arr,int low,int mid,int high,int li,int hi){
    
    int Start2=mid+1,gleast=mid,ghighest=mid;
    while(Start2<=high){
        int im_cnt=0;
        while((ghighest>=low)&&(suffix[ghighest]+prefix[Start2]>hi)){
            ghighest--;
        }
        
        ghighest = max(ghighest,low);
        gleast   = min(gleast,ghighest);
        int last_correct_glast = gleast;
        im_cnt = 0;
        while((gleast>=low)&&(suffix[gleast]+prefix[Start2]>=li)&&(suffix[ghighest]+prefix[Start2]<=hi)){
            im_cnt = (ghighest-gleast+1);
            last_correct_glast = gleast; 
            gleast--;
        }
        gleast = max(last_correct_glast,gleast); // reseting lower_range_value
        count += im_cnt;
        Start2++;
    }
    // sort prefixL,suffixL,prefixR,suffixR
    lli prefixLastLeft  = sum[mid]-((low==0)?(0):(sum[low-1]));
    lli suffixLastRight = sum[high]-sum[mid];

    for(int i=low;i<=mid;i++){
        suffix[i] = suffix[i] + suffixLastRight;
    }
    for(int i=mid+1;i<=high;i++){
        prefix[i] = prefix[i] + prefixLastLeft;
    }
    Imerger(prefix,low,mid,high);
    Imerger(suffix,low,mid,high);
    return;
} 


void mergeSort(lli* arr,int low,int high,int li,int hi){
    if(low>=high) {
        return;
    }
    int mid = low + (high-low)/2;
    mergeSort(arr,low,mid,li,hi);
    mergeSort(arr,mid+1,high,li,hi);
    merger(arr,low,mid,high,li,hi);
}
int countRangeSum(int* nums, int numsSize, int lower, int upper) {
    count=0;
    sz=numsSize;
    for(int i=0;i<numsSize;i++){
        ni[i]  =  nums[i];
        prefix[i] = suffix[i] = nums[i];
        sum[i]    = (nums[i]+((i>=1)?(sum[i-1]):(0)));
        count += inrange(ni[i],lower,upper);
    }
    mergeSort(ni,0,numsSize-1,lower,upper);
    return count;
}

// Pictorial representation
// |       |
// ||     ||   
// |||   |||
// |||| ||||
// prf   suf 
// resetting back to last proper lower and upper indices 
// Sliding Window
