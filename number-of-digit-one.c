// 233. Number of Digit One
#define mod ((int)1e9+7)
typedef long long int lli;
int prec[11]; char str[11];
int modadd(int a,int b){
    a += b;
    if(a>=mod){
        a -= mod;
    }
    return a;
}
int countDigitOne(int n) {
    int expon = 1,where=0,prefixDigit=0,ans=0,digit=1;
    sprintf(str,"%d",n);
    n = strlen(str);
    for(int i=0;i<=9;i++){
        // precompute number of 1's or any single digit from 0 to 99, 0 to 999 , 0 to 99999... under modulus 
        prec[i+1] = (1ll*(i+1)*expon)%mod;
        expon = (1ll*expon*10)%mod;
    }
    for(int where=0;where<n;where++){
        int currDigit = str[where] - '0';
        // for each digit with a prefix part , its corresponding suffix repeats D number of times if curr is tight digit 
        // from 0 to D-1 with considering prefix part as coming before this number formed.
        // so numbers formed by suffxi part counts and repeats itself for D times 
        int rem = (1ll*currDigit*prec[n-1-where])%mod;
        ans = modadd(ans,rem);
        if(currDigit>0)
        {
            // same logic as above if currentDigit is more than 1 , suffix part repeats 1 time 
            // prefixPart having d digit in it counted will repeat d times from 0 to d-1 // part2 
            // above part2 is right shifted by powers of 10 so we need to multiply by 10^(n-curr)
            int c1 = (currDigit>1)+prefixDigit*currDigit;
            rem = (1ll*(c1)*((lli)pow(10,n-1-where)))%mod; // precompute powers of 10 ? 
            ans = modadd(ans,rem);
        }
        // else its tight cant take 

        // last number formed considering everything is tight so we can take its count directly without any suffix
        prefixDigit += (currDigit==digit);
    }
    ans = modadd(ans,prefixDigit);
    return ans; 
}
