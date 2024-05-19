// https://leetcode.com/problems/beautiful-arrangement/

#define SZ 64
#define M  1<<15
int count[SZ][M]; // number of ways to build M mask using first SZ numbers

// count number of ways where p[i] permutation exists with 
// (perm[i] is divisible by i) or (i  is divisible by  perm[i])
int countArrangement(int n) {
    int items=0,bit=0,mask=0;
    memset(count,0,sizeof(count));
    for(items=0;items<n;items++) count[0][1<<items]=1;
    for(items=1;items<n;items++){
            for(bit=0;bit<n;bit++){
                    for(mask=0;mask<(1<<n);mask++){
                        if( ((1<<bit)&mask) && (((bit+1)%(items+1)==0)||((items+1)%(bit+1)==0)) )
                        {
                            // transition if condition given in question is meet 
                            // count(n+1,mask) = count(n+1,mask) + count(n,mask^(1<<bit))
                            // count(n+1,mask) =  withoutCurrent  +  withCurrent
                            count[items][mask] = count[items][mask] + count[items-1][mask^(1<<bit)];
                        }
                    }
            }
    }
    return count[n-1][(1<<items)-1];
}
