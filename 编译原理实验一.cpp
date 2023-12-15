#include<iostream>
#include<string.h>
using namespace std;
//prog存放从文件读取的程序，token存放单词自身的字符串
char token[8], prog[1000], ch;
//columns为列数 ，sym表示单词的种别码 
int p = 0, sym = 0, n = 0, line = 1; 
//要读取的文件名 
char filename[30];
/*FLE系统定义的结构体，*fpincontent是指向文件结构体的指针变量，
通过fp可找到存放某个文件信息的结构变量，根据这个结构变量的信息找到该文件，实施对文件的操作 */
FILE *fpincontent; 
//关键字 
char *keyword[22] = {"if", "else", "while", "do", "main", "int", "float", "double", "return", "const", "void", "continue", "break", "char", "unsigned", "enum", "long", "switch", "case", "unsigned", "auto", "static"};
void GetToken()
{
  	// 清空token数组
    for(n = 0; n < 8; n++) 
    	token[n] = '\0';
  	n = 0;
  	//读取字符 
  	ch = prog[p++];
  	
  	// 删除输入的空白字符，顺便判断是否换行，增加列数
  	while(ch == ' ' || ch == '\n' || ch == '\t') 
  	{
	    //遇到‘\n’（回车换行） ，增加行数
		if (ch == '\n') 
		{ 
	      	line++;
	    } 
	    //遇到‘\t’（横向跳到下一制表符位置）、‘ ’、‘\n’对其忽略，读取下一个字符 
	    ch = prog[p++];
  	}
  	
  	//删除注释行 
  	if (ch == '/')
  	{
  		ch=prog[p++];
		if(ch=='/')   // “//” 
    	{
    		do 
			{
      			ch = prog[p++];
    		} while(ch != '\n');
		}
		sym = -1;
		if(ch=='*')  // “/**/” 
		{
			do 
			{
      			ch = prog[p++];
    		} while(ch != '*');
    		ch = prog[p++];
    		if(ch!='/')
    		{
    			sym=-2;
			}
		}
  	} 
  	
  	//识别标识符 、关键字 
  	else if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) 
	{
	    sym = 22;  //标识符 
	    do 
		{
	      	token[n++] = ch;
	      	ch = prog[p++];
	    } while((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
	    for(n = 0; n < 22; n++) //保留字 
		{
	      	if(strcmp(token, keyword[n]) == 0) 
	        	sym = 23;
	    }
	    p--;
  	}
  	
  	//识别数字 
  	else if (ch >= '0' && ch <= '9')
	{
    	sym = 24;   //整数 
    	do 
		{
	      	token[n++] = ch;
	      	ch = prog[p++];
    	} while(ch >= '0' && ch <= '9');
    	if(ch=='.')  //小数 
    	{
    		do 
			{
	      		token[n++] = ch;
	      		ch = prog[p++];
    		} while(ch >= '0' && ch <= '9');
			sym = 25;
		}
    	p--;
  	}
  	else 
	{
    	switch(ch) 
		{
	      	case '+': sym = 0; token[0] = ch; break; //加 
	      	case '-': sym = 1; token[0] = ch; break; //减 
	     	case '*': sym = 2; token[0] = ch; break; //乘 
	     	case '/': sym = 3; token[0] = ch; break; //除 
	     	case ';': sym = 4; token[0] = ch; break; //语句结束 
	     	case '(': sym = 5; token[0] = ch; break;
	    	case ')': sym = 6; token[0] = ch; break;
	      	case '\'': sym = 7; token[0] = ch; break;
	      	case '\"': sym = 8; token[0] = ch; break;
	      	case '=': 
			{
		        sym = 9;  //等于号 
		        token[0] = ch;
		        ch = prog[p++];
		        if(ch == '=') 
				{
		          	sym = 10; //判断是否相等 
		          	token[1] = ch;
		        }else {
		          p--;
		        }
		        break;
		      }
       		case '<':  
	   		{
		    	sym = 11; //小于号 
		        token[0] = ch;
		        ch = prog[p++];
		        if(ch == '=') 
				{
		          	sym = 12;//小于等于 
		          	token[1] = ch;
		        }else {
		         	p--;
		        }
		        break;
		    }
      		case '>':  
			{ 
		        sym = 13;  //大于号 
		        token[0] = ch;
		        ch = prog[p++];
		        if(ch == '=') //大于等于 
				{
		          	sym = 14;
		          	token[1] = ch;
		        }else {
		         	p--;
		        }
		        break;
		      }
      		case '!': 
	  		{
		        token[0] = ch;
		        ch = prog[p++];
		        if(ch == '=') 
				{
		          	sym = 15; //不等于 
		          	token[1] = ch;
		        }else {
		          	p--;
		          	sym = -2;
		        }
		        break;
		    }
      		case '&': 
			{
		        token[0] = ch;
		        ch = prog[p++];
		        if(ch == '&')  
				{
		          	sym = 16;  //且 
		          	token[1] = ch;
		        }else {
		         	p--;
		          	sym = -2;
		        }
		        break;
		      }
      		case '|':    
			{
		        token[0] = ch;
		        ch = prog[p++];
		        if(ch == '|') 
				{
		          	sym = 17; //或 
		          	token[1] = ch;
		        }else {
		          	p--;
		          	sym = -2;
		        }
		        break;
		    }
	  		case '#': sym = 18; token[0] = ch; break;
      		case '[': sym = 19; token[0] = ch; break;
      		case ']': sym = 20; token[0] = ch; break;
      		case ',': sym = 21; token[0] = ch; break;
      		case '{': sym = 26; token[0] = ch; break;
      		case '}': sym = 27; token[0] = ch; break;
      		default: 
			{
		        sym = -2;
		        break;
		    }
        }
    }
}
int main()
{
  	p = 0;
  	cout<< "read something from ：" << endl<<"                      ";
  	for(;;)
	{
		cin>>filename;
  		//用 fopen函数打开文件，“r”为只读模式
 		fpincontent = fopen(filename,"r");  
    	if(fpincontent!=NULL)
			break;
		else
			cout<<"文件路径错误，请输入源文件名:"<<endl<<"                              ";	
	}
  	// 将文件读取到prog数组里
  	cout<<"源程序："<<endl; 
  	do
  	{
  		//fgetc()读取一个字符
    	ch = fgetc(fpincontent); 
    	prog[p++] = ch;
    	cout<<ch;
   	}while(ch != EOF);
   	cout<<endl<<endl; 
   
  	p = 0;
  	// 按规则拼单词,并转换成二元式形式
  	do
	{
  		/*每次调用都对剩余的字符串分析得到一个单词或记号识别其种类，收集该记号的符号串属性，
		当识别一个单词完毕，采用返回值的形式返回符号的种类，同时采用程序变量的形式提供当前识别出记号的属性值。*/
	    GetToken();
		switch(sym) 
		{
	      	case -1: break;
	      	case -2: //返回值为-1、-2时，跳出switch 
	      	{
	      		cout<<"词法分析出错!，错误位于第"<<line<<"行"<<endl;
	      		break;
			}
	      	default: cout<<"第"<<line<<"行，<"<<sym<<" , "<<token<<">"<<endl; 
	    }
    }while(prog[p] != EOF);
    
    cout<<endl<<endl; 
    p=0;
    cout<<"修改后："<<endl;
    do
	{ 
    	GetToken();
		cout<<token;
   	} while(prog[p]!=EOF);
    return 0;
} 
