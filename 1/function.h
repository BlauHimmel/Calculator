#ifndef FUNCTION
#define FUNCTION

#include <stack>
#include <typeinfo>
using namespace std;

const double PI = 3.14159265354;

int inStack(char a)					//辅助函数，返回栈内优先级
{
	switch (a)
	{
	case's':case'c':case't':case'q':
		return 9;
	case '^':
		return 7;
	case '#':case'=':
		return 0;
	case'(':
		return 1;
	case '*':case'/':case'%':
		return 5;
	case'+':case'-':
		return 3;
	case')':
		return 10;
	default:
		return -1;
	}
}

int outStack(char a)				//辅助函数，返回栈外优先级
{
	switch (a)
	{
	case's':case'c':case't':case'q':
		return 8;
	case '^':
		return 6;
	case '#':case'=':
		return 0;
	case'(':
		return 10;
	case '*':case'/':case'%':
		return 4;
	case'+':case'-':
		return 2;
	case')':
		return 1;
	default:
		return -1;
	}
}

bool calculate(char* a, double &out)		//输入算式 1+1=  用out返回答案	支持正余弦正切开根号开方运算	使用三栈进行运算，栈分别储存操作数、操作符
{
	int len = strlen(a);
	stack<double> StackNum;
	stack<char> StackOp;	//s->sin,c->cos,t->tan,q->sqrt

	char opOnTop;

	StackOp.push('#');

	for (int i = 0; i < len;)
	{
		if ((a[i] == 's') && (a[i + 1] == 'i') && (a[i + 2] == 'n'))		//对类似sin17 的处理
		{
			StackOp.push('s');
			i += 3;
		}
		else if ((a[i] == 'c') && (a[i + 1] == 'o') && (a[i + 2] == 's'))		//对类似cos17 的处理
		{
			StackOp.push('c');
			i += 3;
		}
		else if ((a[i] == 't') && (a[i + 1] == 'a') && (a[i + 2] == 'n'))		//对类似tan17 的处理
		{
			StackOp.push('t');
			i += 3;
		}
		else if ((a[i] == 's') && (a[i + 1] == 'q') && (a[i + 2] == 'r') && (a[i + 3] == 't'))		//对类似sqrt17 的处理
		{
			StackOp.push('q');
			i += 4;
		}
	

		double tempData=0;
		
		bool isDecimal = false;
		int powerOfDecimal = 0;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		while (((iswdigit(a[i])) || a[i] == '.') && (i < len-1))	//读入操作数
		{
			if (a[0] == '.')
				return false;

			if (a[i] == '.')
			{
				if (isDecimal)			//出现诸如1.2.3类的非法输入
					return false;
				if (!iswdigit(a[i - 1]))	//出现诸如.. +.类的非法输入
					return false;
				if (!iswdigit(a[i + 1]))	//出现诸如.. .+类的非法输入
					return false;

				isDecimal = true;

				i++;
				if (i >= len)
					return false;

				continue;
			}

			if (isDecimal)		//小数
			{
				powerOfDecimal++;
				tempData = tempData + (a[i] - '0')*pow(0.1, powerOfDecimal);
			}
			else
				tempData = tempData * 10 + a[i] - '0';	//整数

			i++;

			if ((i >= len-1) || ((!iswdigit(a[i])) && (a[i] != '.')))	//读到数字结束
			{
				if (a[i - 1] == '.')	//出现诸如1.+3类的非法输入
					return false;
				StackNum.push(tempData);
			}
		};

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (!iswdigit(a[i]))
		{
			opOnTop = StackOp.top();
			if (inStack(opOnTop) < outStack(a[i]))
			{
				if (inStack(opOnTop) == -1 || outStack(a[i]) == -1)		//读取到非法操作符
					return false;
				StackOp.push(a[i]);
				i++;
			}
			else if (inStack(opOnTop)>outStack(a[i]))
			{
				if (inStack(opOnTop) == -1 || outStack(a[i]) == -1)		//读取到非法操作符
					return false;

				if (inStack(opOnTop) != 9)
				{
					double temp1, temp2;
					if (StackNum.empty())		//弹出操作数时检测异常的表达式（错误表达式:  + 、-、*、/）
						return false;
					else
					{
						temp1 = StackNum.top();
						StackNum.pop();
					}

					if (StackNum.empty())		//弹出操作数时检测异常的表达式（错误表达式:  + 、-、*、/）
						return false;
					else
					{
						temp2 = StackNum.top();
						StackNum.pop();
					}

					double result;

					char opInStack = StackOp.top();
					StackOp.pop();

					switch (opInStack)
					{
					case '^':
						result = pow(temp2, temp1);
						break;
					case '+':
						result = temp2 + temp1;
						break;
					case '-':
						result = temp2 - temp1;
						break;
					case '*':
						result = temp2 * temp1;
						break;
					case '/':
						if (temp1 == 0)
							return false;
						result = temp2 / temp1;
						break;
					case '%':
						result = fmod(temp2, temp1);
						break;
					}

					StackNum.push(result);
				}
				else
				{
					double temp;
					if (StackNum.empty())		//弹出操作数时检测异常的表达式（错误表达式:  + 、-、*、/）
						return false;
					else
					{
						temp = StackNum.top();
						StackNum.pop();
					}

					double result;

					char opInStack = StackOp.top();
					StackOp.pop();

					switch (opInStack)
					{
					case 's':
						result = sin(temp / 180 * PI);
						break;
					case 'c':
						result = cos(temp / 180 * PI);
						break;
					case 't':
						if (fmod(temp, 90) == 0)
							return false;
						else
							result = tan(temp / 180 * PI);
						break;
					case 'q':
						result = sqrt(temp);
						break;
					}

					StackNum.push(result);
				}
			}

			else
			{
				if (inStack(opOnTop) == -1 || outStack(a[i]) == -1)		//读取到非法操作符
					return false;

				char temp = StackOp.top();
				StackOp.pop();
				if (temp == '(')
					i++;
				if (temp == '#')
				{
					if (StackNum.empty())
						return false;
					else
						out = StackNum.top();
					return true;
				}		
			}
		}	
	}
}

#endif