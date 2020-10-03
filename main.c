#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getlength.h" 
#include "isletter.h"
#include "isdigit.h"
#include "binary.h"
#include "cJSON.h"
//保留字表
char keywords[15][12]={"int","float","double","printf","scanf","getchar","break","else","char","return","continue","for","if","while","void"};    
//分隔符表
char delimiters[20][5]={"=","+","-","&","*","**",",",";","(",")","{","}","<",">","#","[","]","."};   
//标识符表
char id[50][30]={""};    
//常数表
int digitals[100]={};
//sp1->.h,sp2->() 
int i;
int p=0,q=0;
int num;
int main(void){

    FILE *file,*file1;
    file1=fopen("词法分析器（结果）.txt","w");
    //malloc(400*sizeof(int));
    char string[380];
    int j0,k0=0;
    file=fopen("词法分析器.txt","r");//打开文件 
    char ch0;
    while((ch0=fgetc(file))!=EOF){
        string[k0++]=ch0;
    }
    string[k0]='\0';
    char str[380]={};
    strcpy(str,string);
    str[k0]='\0';

    char ch;
    int length=getLength(str);
    //printf("length=%d",length);
    printf("成功，请前往文件:词法分析器（结果）.txt中查看！"); 
    fprintf(file1,"类别码  值   操作\n");
	//fprintf(file1,"start              开始\n");                                                                                       
    for(i=0;i<length;i++){
        char strToken[]={""};
        ch=str[i];
        if(ch==' '|| ch=='\n' ||ch=='\t'){
        }
        else if(IsLetter(ch)){      //第一位为字母 
            while((IsLetter(ch) || IsDigit(ch)) && i<length){
                Concat(getLength(strToken),strToken,ch);      //将ch连接在strToken后面 
                i++;     //指针向后移一位 
                ch=str[i];   //ch变为下一个ch 
            }
            i--;   //指针向前移一位 
            int keyword=IsKeyword(strToken);    //判断是否为保留字 
            if(keyword==0){      //为标识符 
                InsertId(strToken);
                fprintf(file1,"34   %s\n",strToken);      
            }
            else{//为保留字
			    if(keyword==4){
			    	fprintf(file1,"%d    %s    输出\n",keyword,strToken); 
				}else if(keyword==5||keyword==6){
					fprintf(file1,"%d    %s    输入\n",keyword,strToken);
					}else if(keyword==10){
						while(str[i+1]!='}'){
							i++;
						}fprintf(file1,"end      函数结束\n");
						i++;
						}else if(keyword==1){
							//char strToken2[]={""};
							while(str[i]!=';'){
								if(str[i]=='='){
									i++;
									num=0;
									//ch=str[i];
									while(IsDigit(str[i])){
										num=num*10+((int)str[i]-48);
										i++;
									}
									fprintf(file1,"anl1      赋值x为%d\n",num);
								}else{
										i++;
									}
								}
						}else{
							fprintf(file1,"%d    %s\n",keyword,strToken);
						}
					}
				}        
        else if(str[i]&0x80 && str[i+1]&0x80){//为汉字 
        	//fprintf(file1,"35      %c%c\n",str[i],str[i+1]);
        	i+=2; 
		}
        else if(IsDigit(ch)){   //为数字 
            while(IsDigit(ch)){
                Concat(getLength(strToken),strToken,ch);
                i=i+1;
                ch=str[i];
            }
            i--;
            InsertDigit(Binary(atoi(strToken)));    //将strToken字符串转化为数字插入到常数表中 
            fprintf(file1,"35   %d\n",atoi(strToken));
        }
        else if(ch=='='){
            fprintf(file1,"%d    =\n",IsDelimiter(ch));
        }
        else if(ch=='+'){
            fprintf(file1,"%d    +\n",IsDelimiter(ch));
        }
        else if(ch=='-'){
            fprintf(file1,"%d    -\n",IsDelimiter(ch));
        }
        else if(ch=='*'){
            i++;
            ch=str[i];
            if(ch=='*'){
                fprintf(file1,"20   **\n");

            }else{
                fprintf(file1,"19   *\n");
                i--;
            } 
        }
        else if(ch==';'){
            fprintf(file1,"%d    ;\n",IsDelimiter(ch));
        }
        else if(ch=='('){
        	if(str[i+1]==')'){
        		fprintf(file1,"sp2   ()\n");
        		i++;
			}else{
				fprintf(file1,"%d    (\n",IsDelimiter(ch));
			}
        }
        else if(ch==')'){
            fprintf(file1,"%d    )\n",IsDelimiter(ch));
        }
        else if(ch=='{'){
            fprintf(file1,"%d    {\n",IsDelimiter(ch));
        }
        else if(ch=='}'){
            fprintf(file1,"%d    }\n",IsDelimiter(ch));
        }
        else if(ch=='&'){
        	fprintf(file1,"%d    &\n",IsDelimiter(ch));
		}
        else if(ch=='['){
        	fprintf(file1,"%d    [\n",IsDelimiter(ch));
		}
		else if(ch==']'){
        	fprintf(file1,"%d    ]\n",IsDelimiter(ch));
		}
        else if(ch=='>'){
            fprintf(file1,"%d    >\n",IsDelimiter(ch));
        }
        else if(ch=='<'){
            fprintf(file1,"%d    <\n",IsDelimiter(ch));
        }
        else if(ch=='#'){
        	if(str[i+1]=='i'&&str[i+2]=='n'){
        		while(str[i+1]!='>'){
        		i++;
				}
				i++;
				fprintf(file1,"start              开始\n");
			}else{
				fprintf(file1,"%d    #\n",IsDelimiter(ch));
			}
        }
        else if(ch==','){
        	fprintf(file1,"%d    ,\n",IsDelimiter(ch));
		}
        else if(ch=='.'){
        	if(str[i+1]=='h'){
        		fprintf(file1,"sp1    .h\n");
        		i++;
			}else{
				fprintf(file1,"%d    .\n",IsDelimiter(ch));
			}
        }
 		else if(ch=='/'){
 			if(str[i+1]=='/'){
 				//fprintf(file1,"0    跳过\n");
 				i++;
 				while(str[i+1]!='\n'){
 					i++;
				 }
			 }else {
			 	if(str[i+1]=='*'){
			 		i++;
			 		while(str[i+1]!='*'){
			 			i++;
					 }
					 i+=3;
				 }else{
				 	fprintf(file1,"/    /\n");
				 }
			 }
        }
        else if(ch=='"'){
        	fprintf(file1,"36    \"\n");
		}
		else if(ch=='%'){
			fprintf(file1,"37    %%\n");
		} 
        else{
            fprintf(file1,"错误！\n"); 
        }
    }
    return 0;
}

//将字符连接到字符串后面
void Concat(int len,char *str,char ch){
    str+=len;
    *str=ch;    
    *(++str)='\0'; 
    return;
} 
//判断是否为保留字
int IsKeyword(char *ch){
    int s;
    for(s=0;s<15;s++){
        if(strcmp(keywords[s],ch)==0){
            return s+1;     //若是保留字，则返回它的类别码 
        }
    }
    return 0;
}
//将标识符插入到标识符表中
InsertId(char *ch){
    int t,j=0;
    for(t=0;t<getLength(ch);t++){
        id[p][j]=ch[j];
        j++;
    } 
    p++;    
}
//将常数插入到常数表中
InsertDigit(int d){
    digitals[q]=d;
    q++;
} 
//判断是否为分隔符
int IsDelimiter(char *ch){
    int h;
    for(h=0;h<20;h++){
        if(delimiters[h][0]==ch){
            return h+16;     //若是保留字，则返回它的类别码 
        }
    }
    return 0;
}
