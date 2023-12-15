#include<iostream>
#include<string.h>
using namespace std;
//prog��Ŵ��ļ���ȡ�ĳ���token��ŵ���������ַ���
char token[8], prog[1000], ch;
//columnsΪ���� ��sym��ʾ���ʵ��ֱ��� 
int p = 0, sym = 0, n = 0, line = 1; 
//Ҫ��ȡ���ļ��� 
char filename[30];
/*FLEϵͳ����Ľṹ�壬*fpincontent��ָ���ļ��ṹ���ָ�������
ͨ��fp���ҵ����ĳ���ļ���Ϣ�Ľṹ��������������ṹ��������Ϣ�ҵ����ļ���ʵʩ���ļ��Ĳ��� */
FILE *fpincontent; 
//�ؼ��� 
char *keyword[22] = {"if", "else", "while", "do", "main", "int", "float", "double", "return", "const", "void", "continue", "break", "char", "unsigned", "enum", "long", "switch", "case", "unsigned", "auto", "static"};
void GetToken()
{
  	// ���token����
    for(n = 0; n < 8; n++) 
    	token[n] = '\0';
  	n = 0;
  	//��ȡ�ַ� 
  	ch = prog[p++];
  	
  	// ɾ������Ŀհ��ַ���˳���ж��Ƿ��У���������
  	while(ch == ' ' || ch == '\n' || ch == '\t') 
  	{
	    //������\n�����س����У� ����������
		if (ch == '\n') 
		{ 
	      	line++;
	    } 
	    //������\t��������������һ�Ʊ��λ�ã����� ������\n��������ԣ���ȡ��һ���ַ� 
	    ch = prog[p++];
  	}
  	
  	//ɾ��ע���� 
  	if (ch == '/')
  	{
  		ch=prog[p++];
		if(ch=='/')   // ��//�� 
    	{
    		do 
			{
      			ch = prog[p++];
    		} while(ch != '\n');
		}
		sym = -1;
		if(ch=='*')  // ��/**/�� 
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
  	
  	//ʶ���ʶ�� ���ؼ��� 
  	else if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) 
	{
	    sym = 22;  //��ʶ�� 
	    do 
		{
	      	token[n++] = ch;
	      	ch = prog[p++];
	    } while((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
	    for(n = 0; n < 22; n++) //������ 
		{
	      	if(strcmp(token, keyword[n]) == 0) 
	        	sym = 23;
	    }
	    p--;
  	}
  	
  	//ʶ������ 
  	else if (ch >= '0' && ch <= '9')
	{
    	sym = 24;   //���� 
    	do 
		{
	      	token[n++] = ch;
	      	ch = prog[p++];
    	} while(ch >= '0' && ch <= '9');
    	if(ch=='.')  //С�� 
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
	      	case '+': sym = 0; token[0] = ch; break; //�� 
	      	case '-': sym = 1; token[0] = ch; break; //�� 
	     	case '*': sym = 2; token[0] = ch; break; //�� 
	     	case '/': sym = 3; token[0] = ch; break; //�� 
	     	case ';': sym = 4; token[0] = ch; break; //������ 
	     	case '(': sym = 5; token[0] = ch; break;
	    	case ')': sym = 6; token[0] = ch; break;
	      	case '\'': sym = 7; token[0] = ch; break;
	      	case '\"': sym = 8; token[0] = ch; break;
	      	case '=': 
			{
		        sym = 9;  //���ں� 
		        token[0] = ch;
		        ch = prog[p++];
		        if(ch == '=') 
				{
		          	sym = 10; //�ж��Ƿ���� 
		          	token[1] = ch;
		        }else {
		          p--;
		        }
		        break;
		      }
       		case '<':  
	   		{
		    	sym = 11; //С�ں� 
		        token[0] = ch;
		        ch = prog[p++];
		        if(ch == '=') 
				{
		          	sym = 12;//С�ڵ��� 
		          	token[1] = ch;
		        }else {
		         	p--;
		        }
		        break;
		    }
      		case '>':  
			{ 
		        sym = 13;  //���ں� 
		        token[0] = ch;
		        ch = prog[p++];
		        if(ch == '=') //���ڵ��� 
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
		          	sym = 15; //������ 
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
		          	sym = 16;  //�� 
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
		          	sym = 17; //�� 
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
  	cout<< "read something from ��" << endl<<"                      ";
  	for(;;)
	{
		cin>>filename;
  		//�� fopen�������ļ�����r��Ϊֻ��ģʽ
 		fpincontent = fopen(filename,"r");  
    	if(fpincontent!=NULL)
			break;
		else
			cout<<"�ļ�·������������Դ�ļ���:"<<endl<<"                              ";	
	}
  	// ���ļ���ȡ��prog������
  	cout<<"Դ����"<<endl; 
  	do
  	{
  		//fgetc()��ȡһ���ַ�
    	ch = fgetc(fpincontent); 
    	prog[p++] = ch;
    	cout<<ch;
   	}while(ch != EOF);
   	cout<<endl<<endl; 
   
  	p = 0;
  	// ������ƴ����,��ת���ɶ�Ԫʽ��ʽ
  	do
	{
  		/*ÿ�ε��ö���ʣ����ַ��������õ�һ�����ʻ�Ǻ�ʶ�������࣬�ռ��üǺŵķ��Ŵ����ԣ�
		��ʶ��һ��������ϣ����÷���ֵ����ʽ���ط��ŵ����࣬ͬʱ���ó����������ʽ�ṩ��ǰʶ����Ǻŵ�����ֵ��*/
	    GetToken();
		switch(sym) 
		{
	      	case -1: break;
	      	case -2: //����ֵΪ-1��-2ʱ������switch 
	      	{
	      		cout<<"�ʷ���������!������λ�ڵ�"<<line<<"��"<<endl;
	      		break;
			}
	      	default: cout<<"��"<<line<<"�У�<"<<sym<<" , "<<token<<">"<<endl; 
	    }
    }while(prog[p] != EOF);
    
    cout<<endl<<endl; 
    p=0;
    cout<<"�޸ĺ�"<<endl;
    do
	{ 
    	GetToken();
		cout<<token;
   	} while(prog[p]!=EOF);
    return 0;
} 
