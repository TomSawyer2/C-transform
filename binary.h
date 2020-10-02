//将一个数字转化为二进制
int Binary(int d){
    int sum=0;int r=1;
    while(d){
        sum+=(d%2*r);
        r*=10;
        d=d/2;
    }
    return sum;  
}
