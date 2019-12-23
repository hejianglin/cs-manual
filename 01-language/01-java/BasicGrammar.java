//基础的语法
//包含判断语句等,同C++基本类似
//不包含class说明

import static java.lang.Math.*;
import java.math.BigInteger;
import java.util.Arrays;
/**
 * BasicGrammar
 * 可以自动生成注释的方法(注释方法)
 *
 */
public class BasicGrammar
{
	//枚举不能作为局部变量
	public enum Color {RED,GREEN,BLUE}
	public static final String COMMAND = "COMMAND";

	public static void main(String[] args)
	{
		//args 只包含参数，不包含程序名称,这个蛮注意一下
		basicType();
		stringType();
		ioTest();
		flowContorl();
		bigNumberTest();
		arrayTest();
	}


	public static void basicType()
	{
		//1.整形,注意都是带符号的,也仅有带符号的
		//int-> 4字节,带符号因此范围为 -2^31 ~ 2^31-1
		//short -> 2字节,带符号
		//long -> 8字节,带符号
		//byte -> 1字节
		//上述基本类型的占用字节固定
		
		//2.浮点数
		//float -> 4字节
		//double -> 8字节
		

		//3.char
		//表示一个代码单元？？
		//关于 unicode 的编码可以参考这里:http://www.ruanyifeng.com/blog/2007/10/ascii_unicode_and_utf-8.html
		

		//4.boolean
		//存在false 和 true

		//使用注意点:
		//1. 未初始化的变量是不能被使用的(java没有声明,仅有定义)
		//2.常量 final 
		//一般使用全大写
		//int value;
//		System.out.println("value = " + value);//未初始化是禁止使用的
		System.out.println("floorMod(1-9,10) = " + floorMod(1-9,10));
		System.out.println(COMMAND);


		//3.数值的隐式类型转换,按顺序如下:
		//(1)有double则转为double
		//(2)有float则转为float
		//(3)有long则转为long
		//(4)都转为 int
		

		//4.强制类型转换
		double dValue = 9.9;
		int iValue = (int)dValue;
		System.out.println("value = " + iValue);

		//5.支持二/三元运算符号
		iValue += 2;
		System.out.println("value + 2 = " + iValue);

		iValue = true ? 12 : 10;
		System.out.println("value = " + iValue);

		//6.支持位移操作符
		//注意：移位操作和保留符号位
		iValue = 1;
		int value_left3 = iValue << 3;
		iValue = 0x80000000 >> 1;
		System.out.println("0x80000000 >> 1 = " + iValue);
	}

	public static void stringType()
	{
		String greeting = "hello";
		System.out.println("substring(0,3) = " + greeting.substring(0,3));

		//1.任何对象对可以转成字符串
		String strConnect = greeting + 1413;
		System.out.println("str = " + strConnect);

		//2.已经定义过的字符串常量被修改,如上面的hello,java的字符串采用共享存储
		//String 类比 C 类型更像为: char *
		//变量可以赋值为其他字符串
		greeting = strConnect;

		//3.使用函数 equeals 对string 进行比较,而不应该通过 == 
		//== 判断是字符串存放的位置(指针？)
		String sTest = "hel";
		if(greeting.substring(0,3) == sTest)
		{
			System.out.println("hello.substring(0,3) == \"hel\"");
		}
		else
		{
			System.out.println("hello.substring(0,3) != \"hel\"");
		}
		
		if(greeting.substring(0,3).equals(sTest))
		{
			System.out.println("hello.substring(0,3) equal \"hel\"");
		}
		else
		{
			System.out.println("hello.substring(0,3) not equal \"hel\"");
		}

		//4.获取 String 的码点(占用空间??)
		String chineseString = "🐸";
		System.out.println("lenth(🐸) = " + chineseString.length());
		System.out.println("codePointCount(🐸) = " + chineseString.codePointCount(0,chineseString.length()));
		//5.通过 StringBuilder 构建字符串,或者通过StringBuffer(适用于多线程,应该不容易用到)
		//使用时机:需要多个字符串连接
		StringBuilder cStringBuilder = new StringBuilder();
		cStringBuilder.append("hello,");
		cStringBuilder.append("world!");
		System.out.println("StringBuilder Result:" + cStringBuilder.toString());

		//6.String 可以通过format 格式化字符串
		//见 ioTest
	}

	public static void ioTest()
	{
		//支持使用printf 对输出格式化
		String name = "Ding";
		int money = 10000;
		System.out.printf("hello, %s. How mach money do you hava? %d\n",name,money);
		String message = String.format("hello,%s",name);
		System.out.println(message);
	}

	public static void flowContorl()
	{
		//1.内层嵌套不允许使用外层嵌套的同名变量,这个写法也不好,略过
		//2.支持 if / else 语句
		//3.支持 if / else if / else 语句
		//4.支持 while 语句 # 没支持 do while 语句
		//5.支持 for 语句
		//6.支持 switch 语句,case 支持 char,byte,short,int # 少用？？
		for(int i = 10; i > 0; i--)
		{
			System.out.println("Cunting down .." + i);
		}
		System.out.println("Blastoff");
		Color mColor = Color.RED;

		//7.增强版的 break(指定标签的,类似于 goto,不同在于 goto 支持跳转其他标签)
		//而此处不行

		break_test:
		while(true)
		{
			int value = 10;
			while(value > 0)
			{
				System.out.println("current Value = " + value);
				if(value == 5)
				{
					System.out.println("vlaue == 5,break;");
					break break_test;
				}
				--value;
			}
		}

		//标签同样支持其他语句，比如 if /else /else if
		int k = 10;
		if_break_test:
		if(k > 0)
		{
			if(k > 1)
			{
				System.out.println("k > 1");
			}

			if(k > 2)
			{
				System.out.println("k > 2");
			}

			if(k == 10)
			{
				System.out.println("k == 10, break;");
				break if_break_test;
			}

			if( k > 3)
			{
				System.out.println("k > 3");
			}
		}


		//8.支持 continue, 并支持带标签的 continue.//容易混淆
	}

	public static void bigNumberTest()
	{
		//适用于基本的整数和浮点数精度不能够满足的情况
		//BigInteger: 任意精度的整数运算
		//BigDecimal: 任意精度的浮点数运算
		//需要注意的是它没有重载运算符号
		BigInteger bigValue = BigInteger.valueOf(10);
		System.out.println("bigValue = " + bigValue.multiply(BigInteger.valueOf(0x7FFFFFFF)));
	}


	public static void arrayTest()
	{
		//定义,前文说到Java 没有声明,只有定义
		int [] aiValue = new int[] {99,98,97,96,95,94,93,92,91,90};
		//另外一种写法
		int aiKey[] = new int[3];//c/c++可能更习惯这一种

		//数组默认会被初始化为对应的空值，比如 int->0 ,object -> null

		//1.支持 c/c++ 初始化的方法
		aiKey = new int[] {1,2,3};
		for(int i = 0; i < aiKey.length; i++)
		{
			System.out.printf("array[%d] = %d\n",i, aiKey[i]);
		}
		//2.数组变量的赋值是通过浅拷贝,这个和 c/c++ 是一样,比如:
		int aiKey_other[] = aiKey;
		System.out.println(Arrays.toString(aiKey_other));
		aiKey_other[1] = 99;
		System.out.println("array_key_other:" + Arrays.toString(aiKey_other));
		System.out.println("array_key:" + Arrays.toString(aiKey_other));
		//需要深拷贝则需要使用Arrays 提供的方法，或则自行循环复制
		
		int aiValue_other[] = new int[5];
		aiValue_other = Arrays.copyOf(aiValue, aiValue.length);//实际上是 new 了一个给 aiValue_other
		System.out.println("array_value_other:" + Arrays.toString(aiValue_other));

		aiValue_other = Arrays.copyOf(aiValue, aiValue.length * 2);
		System.out.println("array_value_other:" + Arrays.toString(aiValue_other));

		//排序,使用Arrays 默认提供的 sort 即可
		//3.支持2维数组，但是实际上2维数组实际上为1维数组的元素的数组构成
	}


	
}
