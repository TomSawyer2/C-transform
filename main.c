#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getlength.h" 
#include "isletter.h"
#include "isdigit.h"
#include "binary.h"
#include "cJSON.h"
#include <windows.h>
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
int IsInt=0;//判断是不是赋值，0不是，1是，2是默认为0
int IsFloat=0;//判断是不是赋值，0不是，1是，2是默认为0
int IsDouble=0;//判断是不是赋值，0不是，1是，2是默认为0
int value;
int value2=1;
char number[50]; 
int cnt=1;
int get=0;//0表示未被读取，1表示已被读取 
int start=0;
int main(void){
	unsigned char pro[100]={0};
	while(value<100){
		pro[value]=value;
		value++;
	}
	char cmd[80];
	sprintf(cmd,"Start E:\\graphviz\\bin\\gvedit.exe graph.dot");
	system(cmd);
	cJSON *json = cJSON_CreateObject();
	cJSON *array = NULL;
	cJSON *array2 = NULL;
	cJSON *array3 = NULL;
	cJSON *array4 = NULL;
	cJSON *array5 = NULL;
	cJSON *array6 = NULL;
	cJSON *array7 = NULL;
	cJSON *array8 = NULL;
	cJSON *array9 = NULL;
	cJSON *array10 = NULL;
	cJSON *array11 = NULL;
	cJSON *array12 = NULL;
	cJSON *array13 = NULL;
	cJSON *array14 = NULL;
	cJSON *array15 = NULL;
	cJSON *array16 = NULL;
	cJSON *array17 = NULL;
	cJSON *obj = NULL;
	
    FILE *file,*file1;
    file1=fopen("词法分析器（结果）.txt","w");
    FILE *file2=fopen("graph.dot","w");
    setbuf(file2,NULL);//清空缓存？ 
    //malloc(400*sizeof(int));
    char string[380];
    int j0,k0=0;
    file=fopen("词法分析器.txt","r");//打开文件 
    //file=fopen("graph.dot","r");
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
    printf("成功，请前往文件:词法分析器（结果）.txt中查看！\n"); 
    //printf("成功，请前往文件:graph.dot中查看！\n"); 
    fprintf(file2,"digraph {\nedge [fontname=\"FangSong\"];\nnode [shape=box, fontname=\"SimSun\" size=\"20,20\"];\n");
    fprintf(file1,"类别码  值   操作\n");
	char strToken2[]={""};   
	char strToken3[]={""};
	char strToken4[]={""};
	char strToken5[]={""};
	char strToken6[]={""};
	char strToken7[]={""};       
	char strToken8[]={""};    
	char strToken9[]={""};      
	char strTokenequal[]={""};                                                                         
    for(i=0;i<length;i++){
    	get=0;
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
			    	get=1;
			    	while(str[i]!='"'){
			    		i++; 
					}
					i++;
					while(str[i]!='"'){
			    		i++; 
					}
					i++;
					if(str[i]==')'){
						fprintf(file1,"输出       （其实也没输出什么）\n");
						
						i+=3;
					}else{
						while(str[i+1]!=';'){
							if(IsLetter(str[i])||IsLetter(str[i+1])||IsDigit(str[i])||IsDigit(str[i+1])){//读取变量名称 
							Concat(getLength(strToken3),strToken3,str[i]);
							i++;
							}
							if(str[i-1]==','&&(str[i-2]=='"'||str[i-3]==')')){
								for (unsigned int q = 0;q<strlen(strToken3);q++){
									strToken3[q] = '\0';
									}
							}
						}
						fprintf(file1,"输出          %s\n",strToken3); 
						i+=2;
						cJSON_AddItemToObject(json,"process",array2=cJSON_CreateArray());
						cJSON_AddItemToObject(array2,"process",cJSON_CreateString("output"));
						cJSON_AddItemToObject(array2,"process",cJSON_CreateString(strToken3));
						fprintf(file2,"equal%d;\n",cnt);
						fprintf(file2,"equal%d [shape=parallelogram, label=\"%s\"];\n",cnt,strToken3);
						fprintf(file2,"equal%d->",cnt);
						cnt++;
					}
				}else if(keyword==5||keyword==6){
					get=1;
					while(str[i]!='&'){
			    		i++;
					}
					i++;
					if(str[i]==')'){
						fprintf(file1,"输入       （如果出现这句话你程序必错）\n");
						i+=3;
					}else{
						while(str[i]!=')'){
							if(str[i-2]==','&&str[i-3]=='"'){
								for (unsigned int s = 0;s<strlen(strToken4);s++){
									strToken4[s] = '\0';
									}
							}
							if(str[i]=='&'){
								i++;
							}else{
								Concat(getLength(strToken4),strToken4,str[i]);
							}
							i++;
						}
						i++;
					fprintf(file1,"输入          %s\n",strToken4);
					cJSON_AddItemToObject(json,"process",array3=cJSON_CreateArray());
					cJSON_AddItemToObject(array3,"process",cJSON_CreateString("input"));
					cJSON_AddItemToObject(array3,"process",cJSON_CreateString(strToken4));
					value2++;
					fprintf(file2,"equal%d;\n",cnt);
					fprintf(file2,"equal%d [shape=parallelogram, label=\"%s\"];\n",cnt,strToken4);
					fprintf(file2,"equal%d->",cnt);
					cnt++;
					}
				}else if(keyword==10){
					get=1;
						while(str[i+1]!='}'){
							i++;
						}fprintf(file1,"end      函数结束\n");
						cJSON_AddItemToObject(json,"end",array9=cJSON_CreateArray());
						cJSON_AddItemToObject(array9,"end",cJSON_CreateString("end"));
						cJSON_AddItemToObject(array9,"end",cJSON_CreateString("end"));
						fprintf(file2,"end;\n");
						fprintf(file2,"end [shape=ellipse, label=\"end\"];\n");
						//fprintf(file2,"equal%d->",i);
						fprintf(file2,"}");
						sprintf(cmd,"dot -Tpng graph.dot -o graph.png");
						system(cmd);
						//dot -Tpng tree.dot -o tree.png
						//cJSON_AddItemToObject(array9,"end",cJSON_CreateString("NULL"));
						i++;
						}else if(keyword==1){//判断int
						get=1;
						i=i+1; 
							int j1=i;
							for(j1;str[j1]!=';';j1++){
								if(str[j1]=='='){
									IsInt=1;
									break;
								}else{
										IsInt=0;
									} 
								}
							if(IsInt==0){
								int m1=i;
								for(m1;str[m1]!=';';m1++){
									if(str[m1]=='('||str[m1]==')'){
										IsInt=0;
										goto escape;
									}else{
										IsInt=2;
									}
								}
							}
							escape:
							while(str[i]!=';'&&str[i]!='{'&&str[i]!='\n'){//判断int后面的内容是函数还是赋值
								if(str[i]=='='){//是赋值 
									i++;
									num=0;
									while(IsDigit(str[i])){
										num=num*10+((int)str[i]-48);
										i++;
									}
									if(IsInt==1){
										fprintf(file1,"赋值      %s->%d\n",strToken2,num);
										cJSON_AddItemToObject(json,"process",array5=cJSON_CreateArray());
										cJSON_AddItemToObject(array5,"process",cJSON_CreateString("equalint"));
										
										fprintf(file2,"equal%d\n",cnt);
										fprintf(file2,"equal%d [shape=box, label=\"%s=%d\"];\n",cnt,strToken2,num);
										fprintf(file2,"equal%d->",cnt);
										cnt++;
										//cJSON_AddItemToObject(array5,"process",cJSON_CreateString(strToken2));
										//Concat(getLength(strToken2),strToken2,'=');
										//sprintf(number, "%d", num);
										//itoa(num, strToken2, 10);
										//Concat(getLength(strToken2),strToken2,number);
										//cJSON_AddItemToObject(array5,"process",cJSON_CreateString(number));
										sprintf(number, "%s=%d",strToken2,num);
										cJSON_AddItemToObject(array5,"process",cJSON_CreateString(number));
									}
								}else if((IsLetter(str[i])||str[i]==',')&&IsInt==1){//读取赋值的变量名称，当然也可能是函数的名称，后者直接忽略 
									Concat(getLength(strToken2),strToken2,str[i]);
									i++;
								}else if((IsLetter(str[i])||str[i]==',')&&IsInt==2){//读取赋值的变量名称，当然也可能是函数的名称，后者直接忽略 
									Concat(getLength(strToken2),strToken2,str[i]);
									i++;
									num=0;
									if(IsInt==2&&IsLetter(str[i])==0){
										fprintf(file1,"赋值      %s->0\n",strToken2);
										cJSON_AddItemToObject(json,"process",array4=cJSON_CreateArray());
										cJSON_AddItemToObject(array4,"process",cJSON_CreateString("equalint"));
										//fprintf(file2,"%s->",strToken2);
										
										fprintf(file2,"equal%d\n",cnt);
										fprintf(file2,"equal%d [shape=box, label=\"%s=0\"];\n",cnt,strToken2,num);
										fprintf(file2,"equal%d->",cnt);
										cnt++;
										//cJSON_AddItemToObject(array4,"process",cJSON_CreateString(strToken2));
										//cJSON_AddItemToObject(array4,"process",cJSON_CreateString("0"));
										sprintf(number, "%s=%d",strToken2,0);
										cJSON_AddItemToObject(array4,"process",cJSON_CreateString(number));
										
									}
								}else if(str[i]==' '||str[i]=='\n'){//在赋值时一定要用两个空格，不然就会读入nt，我也不知道为什么。bug已经修复！前面写成i+=2了 
									for (unsigned int k = 0;k<strlen(strToken2);k++){
									strToken2[k] = '\0';
									}
									i++;
								}else {
									i++;
								}
							}
						}else if(keyword==2){//判断float
						get=1;
						i=i+1; 
						float num2=0.000000;
							int j2=i;
							for(j2;str[j2]!=';';j2++){
								if(str[j2]=='='){
									IsFloat=1;
									break;
								}else{
										IsFloat=0;
									} 
								}
							if(IsFloat==0){
								int m2=i;
								for(m2;str[m2]!=';';m2++){
									if(str[m2]=='('||str[m2]==')'){
										IsFloat=0;
										goto escape2;
									}else{
										IsFloat=2;
									}
								}
							}
							escape2:
							while(str[i]!=';'){//判断int后面的内容是函数还是赋值
								if(str[i]=='='){//是赋值 
									i++;
									num2=0;
									while(IsDigit(str[i])){
										num2=num2*10+((int)str[i]-48);
										i++;
									}
									if(IsInt==1){
										fprintf(file1,"赋值      %s->%f\n",strToken2,num2);
										cJSON_AddItemToObject(json,"process",array7=cJSON_CreateArray());
										cJSON_AddItemToObject(array7,"process",cJSON_CreateString("equalfloat"));
										//fprintf(file2,"%s->",strToken2);
										
										fprintf(file2,"equal%d\n",cnt);
										fprintf(file2,"equal%d [shape=box, label=\"%s=%f\"];\n",cnt,strToken2,num2);
										fprintf(file2,"equal%d->",cnt);
										cnt++;
										//cJSON_AddItemToObject(array7,"process",cJSON_CreateString(strToken2));
										//sprintf(number, "%.6lf", num2);
										//cJSON_AddItemToObject(array7,"process",cJSON_CreateString(number));
										sprintf(number, "%s=%f",strToken2,num2);
										cJSON_AddItemToObject(array7,"process",cJSON_CreateString(number));
										
									}
								}else if((IsLetter(str[i])||str[i]==',')&&IsFloat==1){//读取赋值的变量名称，当然也可能是函数的名称，后者直接忽略 
									Concat(getLength(strToken2),strToken2,str[i]);
									i++;
								}else if((IsLetter(str[i])||str[i]==',')&&IsFloat==2){//读取赋值的变量名称，当然也可能是函数的名称，后者直接忽略 
									Concat(getLength(strToken2),strToken2,str[i]);
									i++;
									
									if(IsFloat==2&&IsLetter(str[i])==0){
										fprintf(file1,"赋值      %s->0.000000\n",strToken2);
										cJSON_AddItemToObject(json,"process",array6=cJSON_CreateArray());
										cJSON_AddItemToObject(array6,"process",cJSON_CreateString("equalfloat"));
										//fprintf(file2,"%s->",strToken2);
										fprintf(file2,"equal%d\n",cnt);
										fprintf(file2,"equal%d [shape=box, label=\"%s=0.000000\"];\n",cnt,strToken2);
										fprintf(file2,"equal%d->",cnt);
										cnt++;
										//cJSON_AddItemToObject(array6,"process",cJSON_CreateString(strToken2));
										//cJSON_AddItemToObject(array6,"process",cJSON_CreateString("0.000000"));
										sprintf(number, "%s=%f",strToken2,0.000000);
										cJSON_AddItemToObject(array6,"process",cJSON_CreateString(number));
									}
								}else if(str[i]==' '||str[i]=='\n'){//在赋值时一定要用两个空格，不然就会读入nt，我也不知道为什么。bug已经修复！前面写成i+=2了 
									for (unsigned int k = 0;k<strlen(strToken2);k++){
									strToken2[k] = '\0';
									}
									i++;
								}else {
									i++;
								}
							}
						}else if(keyword==3){//判断double
						get=1;
						i=i+1; 
						double num3=0.000000;
							int j3=i;
							for(j3;str[j3]!=';';j3++){
								if(str[j3]=='='){
									IsDouble=1;
									break;
								}else{
										IsDouble=0;
									} 
								}
							if(IsDouble==0){
								int m3=i;
								for(m3;str[m3]!=';';m3++){
									if(str[m3]=='('||str[m3]==')'){
										IsDouble=0;
										goto escape3;
									}else{
										IsDouble=2;
									}
								}
							}
							escape3:
							while(str[i]!=';'){//判断int后面的内容是函数还是赋值
								if(str[i]=='='){//是赋值 
									i++;
									num3=0.000000;
									//ch=str[i];
									while(IsDigit(str[i])){
										num3=num3*10+((double)str[i]-48);
										i++;
									}
									if(IsDouble==1){
										fprintf(file1,"赋值      %s->%f\n",strToken2,num3);
										cJSON_AddItemToObject(json,"process",array11=cJSON_CreateArray());
										cJSON_AddItemToObject(array11,"process",cJSON_CreateString("equaldouble"));
										//fprintf(file2,"%s->",strToken2);
										fprintf(file2,"equal%d\n",cnt);
										fprintf(file2,"equal%d [shape=box, label=\"%s=%f\"];\n",cnt,strToken2,num3);
										fprintf(file2,"equal%d->",cnt);
										cnt++;
										//cJSON_AddItemToObject(array11,"process",cJSON_CreateString(strToken2));
										//sprintf(number, "%.6lf", num3);
										//cJSON_AddItemToObject(array11,"process",cJSON_CreateString(number));
										sprintf(number, "%s=%f",strToken2,num3);
										cJSON_AddItemToObject(array11,"process",cJSON_CreateString(number));
										
									}
								}else if((IsLetter(str[i])||str[i]==',')&&IsDouble==1){//读取赋值的变量名称，当然也可能是函数的名称，后者直接忽略 
									Concat(getLength(strToken2),strToken2,str[i]);
									i++;
								}else if((IsLetter(str[i])||str[i]==',')&&IsDouble==2){//读取赋值的变量名称，当然也可能是函数的名称，后者直接忽略 
									Concat(getLength(strToken2),strToken2,str[i]);
									i++;
									
									if(IsDouble==2&&IsLetter(str[i])==0){
										fprintf(file1,"赋值      %s->0.000000\n",strToken2);
										cJSON_AddItemToObject(json,"process",array8=cJSON_CreateArray());
										cJSON_AddItemToObject(array8,"process",cJSON_CreateString("equaldouble"));
										//fprintf(file2,"%s->",strToken2);
										fprintf(file2,"equal%d\n",cnt);
										fprintf(file2,"equal%d [shape=box, label=\"%s=0.000000\"];\n",cnt,strToken2);
										fprintf(file2,"equal%d->",cnt);
										cnt++;
										//cJSON_AddItemToObject(array8,"process",cJSON_CreateString(strToken2));
										//cJSON_AddItemToObject(array8,"process",cJSON_CreateString("0.000000"));
										sprintf(number, "%s=%f",strToken2,0.000000);
										cJSON_AddItemToObject(array8,"process",cJSON_CreateString(number));
										
									}
								}else if(str[i]==' '||str[i]=='\n'){//在赋值时一定要用两个空格，不然就会读入nt，我也不知道为什么。bug已经修复！前面写成i+=2了 
									for (unsigned int k = 0;k<strlen(strToken2);k++){
									strToken2[k] = '\0';
									}
									i++;
								}else {
									i++;
								}
							}
							
						}else if(keyword==13){
							get=1;
							i++;
							while(str[i]!=')'){
								Concat(getLength(strToken5),strToken5,str[i]);
								
								if(str[i]=='('){
									for (unsigned int z = 0;z<strlen(strToken5);z++){
									strToken5[z] = '\0';
									}
								}
								i++;
							}
							fprintf(file1,"条件         %s\n",strToken5);
							cJSON_AddItemToObject(json,"process",array12=cJSON_CreateArray());
							cJSON_AddItemToObject(array12,"process",cJSON_CreateString("judgecondition"));
							cJSON_AddItemToObject(array12,"process",cJSON_CreateString(strToken5));
							//fprintf(file2,"%s->",strToken5);
							//fprintf(file2,"%s;\n%s->",strToken5,strToken5);
							fprintf(file2,"equal%d\n",cnt);
							fprintf(file2,"equal%d [shape=diamond, label=\"%s\"];\n",cnt,strToken5);
							fprintf(file2,"equal%d->",cnt);
							cnt++;
							while(str[i]!='{'){
								i++;
							}
							i+=1;
							while(str[i]!='}'){
								Concat(getLength(strToken6),strToken6,str[i]);
								if(str[i-2]==')'){
									for (unsigned int y = 0;y<strlen(strToken6);y++){
									strToken6[y] = '\0';
									}
								}
								i++;
							}
							fprintf(file1,"要做的事      %s\n",strToken6);
							cJSON_AddItemToObject(json,"process",array13=cJSON_CreateArray());
							cJSON_AddItemToObject(array13,"process",cJSON_CreateString("judgetodo"));
							cJSON_AddItemToObject(array13,"process",cJSON_CreateString(strToken6));
							//fprintf(file2,"%s->",strToken6);
							//fprintf(file2,"%s;\n%s->",strToken6,strToken6);
							fprintf(file2,"equal%d[label=\"yes\"];\n",cnt);
							fprintf(file2,"equal%d [shape=box, label=\"%s\"];\n",cnt,strToken6);
							//fprintf(file2,"equal%d->",cnt);
							cnt++;
							if((str[i+1]=='e'&&str[i+2]=='l'&&str[i+3]=='s'&&str[i+4]=='e')||(str[i+2]=='e'&&str[i+3]=='l'&&str[i+4]=='s'&&str[i+5]=='e')){
								fprintf(file2,"equal%d->",cnt-2);
							}
						}else if(keyword==8){
							get=1;
							while(str[i]!='{'){
								i++;
							}
							i++;
							while(str[i]!='}'){
								Concat(getLength(strToken7),strToken7,str[i]);
								i++;
								if(str[i-2]=='{'){
									for (unsigned int clear = 0;clear<strlen(strToken7); clear++){
									strToken7[clear] = '\0'; 
								}
							}
							}
							fprintf(file1,"否则      %s\n",strToken7);
							cJSON_AddItemToObject(json,"process",array14=cJSON_CreateArray());
							cJSON_AddItemToObject(array14,"process",cJSON_CreateString("else"));
							cJSON_AddItemToObject(array14,"process",cJSON_CreateString(strToken7));
							//fprintf(file2,"%s->",strToken7);
							//fprintf(file2,"%s;\n%s->",strToken7,strToken7);
							//fprintf(file2,"equal%d\n",cnt);
							//fprintf(file2,"equal%d [shape=box, label=\"%s\"];\n",cnt,strToken7);
							//fprintf(file2,"equal%d->",cnt);
							fprintf(file2,"equal%d[label=\"no\"];\n",cnt);
							fprintf(file2,"equal%d [shape=box, label=\"%s\"];\n",cnt,strToken7);
							cnt++;
							fprintf(file2,"equal%d,equal%d->",cnt-2,cnt-1);
						}else if(keyword==14){
							get=1;
							i++;
							while(str[i]!=')'){
								Concat(getLength(strToken8),strToken8,str[i]);
								
								if(str[i]=='('){
									for (unsigned int clear2 = 0;clear2<strlen(strToken8);clear2++){
									strToken8[clear2] = '\0';
									}
								}
								i++;
							}
							fprintf(file1,"条件         %s\n",strToken8);
							cJSON_AddItemToObject(json,"process",array15=cJSON_CreateArray());
							cJSON_AddItemToObject(array15,"process",cJSON_CreateString("judgecondition"));
							cJSON_AddItemToObject(array15,"process",cJSON_CreateString(strToken8));
							//fprintf(file2,"%s->",strToken8);
							//fprintf(file2,"%s;\n%s->",strToken8,strToken8);
							fprintf(file2,"equal%d\n",cnt);
							fprintf(file2,"equal%d [shape=diamond, label=\"%s\"];\n",cnt,strToken8);
							fprintf(file2,"equal%d->",cnt);
							cnt++;
							//cJSON_AddItemToObject(obj,"judgecon",cJSON_CreateString(strToken5));
							//cJSON_AddItemToObject(obj,"judgecon",cJSON_CreateString(strToken5));
							//pro++;
							while(str[i]!='{'){
								i++;
							}
							i+=1;
							while(str[i]!='}'){
								if(str[i]==';'){
									i++;
								}else{
									Concat(getLength(strToken9),strToken9,str[i]);
								
								if(str[i-2]==')'){
									for (unsigned int clear3 = 0;clear3<strlen(strToken9);clear3++){
									strToken9[clear3] = '\0';
									}
								}
								i++;
								}
								
								
							}
							fprintf(file1,"要做的事      %s\n",strToken9);
							cJSON_AddItemToObject(json,"process",array16=cJSON_CreateArray());
							cJSON_AddItemToObject(array16,"process",cJSON_CreateString("judgetodo"));
							cJSON_AddItemToObject(array16,"process",cJSON_CreateString(strToken9));
							//fprintf(file2,"%s->",strToken9);
							//fprintf(file2,"%s;\n%s->",strToken9,strToken9);
							fprintf(file2,"equal%d\n",cnt);
							//fprintf(file2,"equal%d[label=\"yes\"];\n",cnt);
							fprintf(file2,"equal%d [shape=box, label=\"%s\"];\n",cnt,strToken9);
							fprintf(file2,"equal%d->equal%d\n",cnt,cnt-1);
							fprintf(file2,"equal%d->",cnt-1);
							cnt++;
						}else{
							fprintf(file1,"%d    %s\n",keyword,strToken);
						}
					}
				}        
        else if(str[i]&0x80 && str[i+1]&0x80){//为汉字 
        	//fprintf(file1,"35      %c%c\n",str[i],str[i+1]);
        	i+=2; 
		}
        else if(IsDigit(ch)){//为数字 
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
        else if(str[i]==';'){
        	while(str[i-1]!=';'&&str[i-1]!='\n'){
        		//for (unsigned int clear3 = 0;clear3<strlen(strTokenequal);clear3++){
				//strTokenequal[clear3] = '\0';
				//}
        		i--;
			}
			//i++;
			for (unsigned int clear3 = 0;clear3<strlen(strTokenequal);clear3++){
				strTokenequal[clear3] = '\0';
				}
			while(str[i]!=';'){
					Concat(getLength(strTokenequal),strTokenequal,str[i]);
					if(get==1){
					for (unsigned int clear4 = 0;clear4<strlen(strTokenequal);clear4++){
						strTokenequal[clear4] = '\0';
						i++;
						}
					}else{
						i++;
					}
				}
			i+=1;
			cJSON_AddItemToObject(json,"process",array17=cJSON_CreateArray());
			cJSON_AddItemToObject(array17,"process",cJSON_CreateString("normal"));
			cJSON_AddItemToObject(array17,"process",cJSON_CreateString(strTokenequal));
			fprintf(file1,"%s    ;\n",strTokenequal);
			fprintf(file2,"equal%d;\n",cnt);
			fprintf(file2,"equal%d [shape=box, label=\"%s\"];\n",cnt,strTokenequal);
			fprintf(file2,"equal%d->",cnt);
			cnt++;
            //fprintf(file1,"%d    ;\n",IsDelimiter(ch));
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
        	if (str[i-1]=='='){
        		fprintf(file1,"%d    {\n",IsDelimiter(ch));
			}
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
        	if(str[i+1]=='i'&&str[i+2]=='n'&&start==0){
        		while(str[i+1]!='>'){
        		i++;
				}
				i++;
				start=1;
				fprintf(file1,"start            开始\n");
				//cJSON_AddItemToObject(json,"start",cJSON_CreateString("pro=="));
				cJSON_AddItemToObject(json,"example",array10=cJSON_CreateArray());
				cJSON_AddItemToObject(array10,"example",cJSON_CreateString("type"));
				cJSON_AddItemToObject(array10,"example",cJSON_CreateString("content"));
				//cJSON_AddItemToObject(array10,"example",cJSON_CreateString("content2"));
				cJSON_AddItemToObject(json,"start",array=cJSON_CreateArray());
				cJSON_AddItemToObject(array,"start",cJSON_CreateString("start"));
				cJSON_AddItemToObject(array,"start",cJSON_CreateString("start"));
				fprintf(file2,"start [shape=ellipse, label=\"start\"];\n");
				fprintf(file2,"start->");
				
				//cJSON_AddItemToObject(array,"start",cJSON_CreateString("NULL"));
				
				//pro++;
				//cJSON *array = NULL;
				//cJSON_AddItemToObject(json,"process",array=cJSON_CreateArray());//过程
				
				//cJSON_AddItemToArray(array,obj=cJSON_CreateObject());
       			
       			
    			//cJSON_AddItemToObject(obj,"normal",cJSON_CreateString(""));
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
    printf("data:%s\n",array = cJSON_Print(json));
    //将json结构格式化到缓冲区
	char *buf = cJSON_Print(json);
	//打开文件写入json内容
	FILE *fp = fopen("create.json","w");
	fwrite(buf,strlen(buf),1,fp);
	free(buf);
	fclose(fp);
	//释放json结构所占用的内存
	cJSON_Delete(json);
	system("pause");
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
