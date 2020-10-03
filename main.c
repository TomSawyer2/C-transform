#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getlength.h" 
#include "isletter.h"
#include "isdigit.h"
#include "binary.h"
#include "cJSON.h"
//�����ֱ�
char keywords[15][12]={"int","float","double","printf","scanf","getchar","break","else","char","return","continue","for","if","while","void"};    
//�ָ�����
char delimiters[20][5]={"=","+","-","&","*","**",",",";","(",")","{","}","<",">","#","[","]","."};   
//��ʶ����
char id[50][30]={""};    
//������
int digitals[100]={};
//sp1->.h,sp2->() 
int i;
int p=0,q=0;
int num;
int main(void){

    FILE *file,*file1;
    file1=fopen("�ʷ��������������.txt","w");
    //malloc(400*sizeof(int));
    char string[380];
    int j0,k0=0;
    file=fopen("�ʷ�������.txt","r");//���ļ� 
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
    printf("�ɹ�����ǰ���ļ�:�ʷ��������������.txt�в鿴��"); 
    fprintf(file1,"�����  ֵ   ����\n");
	//fprintf(file1,"start              ��ʼ\n");                                                                                       
    for(i=0;i<length;i++){
        char strToken[]={""};
        ch=str[i];
        if(ch==' '|| ch=='\n' ||ch=='\t'){
        }
        else if(IsLetter(ch)){      //��һλΪ��ĸ 
            while((IsLetter(ch) || IsDigit(ch)) && i<length){
                Concat(getLength(strToken),strToken,ch);      //��ch������strToken���� 
                i++;     //ָ�������һλ 
                ch=str[i];   //ch��Ϊ��һ��ch 
            }
            i--;   //ָ����ǰ��һλ 
            int keyword=IsKeyword(strToken);    //�ж��Ƿ�Ϊ������ 
            if(keyword==0){      //Ϊ��ʶ�� 
                InsertId(strToken);
                fprintf(file1,"34   %s\n",strToken);      
            }
            else{//Ϊ������
			    if(keyword==4){
			    	fprintf(file1,"%d    %s    ���\n",keyword,strToken); 
				}else if(keyword==5||keyword==6){
					fprintf(file1,"%d    %s    ����\n",keyword,strToken);
					}else if(keyword==10){
						while(str[i+1]!='}'){
							i++;
						}fprintf(file1,"end      ��������\n");
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
									fprintf(file1,"anl1      ��ֵxΪ%d\n",num);
								}else{
										i++;
									}
								}
						}else{
							fprintf(file1,"%d    %s\n",keyword,strToken);
						}
					}
				}        
        else if(str[i]&0x80 && str[i+1]&0x80){//Ϊ���� 
        	//fprintf(file1,"35      %c%c\n",str[i],str[i+1]);
        	i+=2; 
		}
        else if(IsDigit(ch)){   //Ϊ���� 
            while(IsDigit(ch)){
                Concat(getLength(strToken),strToken,ch);
                i=i+1;
                ch=str[i];
            }
            i--;
            InsertDigit(Binary(atoi(strToken)));    //��strToken�ַ���ת��Ϊ���ֲ��뵽�������� 
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
				fprintf(file1,"start              ��ʼ\n");
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
 				//fprintf(file1,"0    ����\n");
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
            fprintf(file1,"����\n"); 
        }
    }
    return 0;
}

//���ַ����ӵ��ַ�������
void Concat(int len,char *str,char ch){
    str+=len;
    *str=ch;    
    *(++str)='\0'; 
    return;
} 
//�ж��Ƿ�Ϊ������
int IsKeyword(char *ch){
    int s;
    for(s=0;s<15;s++){
        if(strcmp(keywords[s],ch)==0){
            return s+1;     //���Ǳ����֣��򷵻���������� 
        }
    }
    return 0;
}
//����ʶ�����뵽��ʶ������
InsertId(char *ch){
    int t,j=0;
    for(t=0;t<getLength(ch);t++){
        id[p][j]=ch[j];
        j++;
    } 
    p++;    
}
//���������뵽��������
InsertDigit(int d){
    digitals[q]=d;
    q++;
} 
//�ж��Ƿ�Ϊ�ָ���
int IsDelimiter(char *ch){
    int h;
    for(h=0;h<20;h++){
        if(delimiters[h][0]==ch){
            return h+16;     //���Ǳ����֣��򷵻���������� 
        }
    }
    return 0;
}
