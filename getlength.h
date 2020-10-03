//输入的字符串的长度的函数
int getLength(char *str){
    int len=0,k;
    for(k=0;k<380;k++){
        if(str[k]!='\0'){
            len++;
        }else{
            break;
        } 
    }
    return len;
} 
