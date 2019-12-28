//类之间的关系
//1.依赖
//2.继承
//3.包含(聚合 has-a)
//

//package 表示 namespace,表示自身的空间
//package com.masje.test;//同时应该按照对应的目录进行放置,详见 package

//import 表示 using ,表示使用其他命名空间
import java.util.Date;
import java.time.LocalDate;
import java.time.DayOfWeek;

//一个源文件只能有一个公有类
//其他私有类/enum 会在编译成字节码时生成对应的　class 文件
public class ObjectTest
{
	public static void main(String args[])
	{
		//1.对象变量只是一个引用(指针)，并不包含实例
		//普通的对象赋值为引用,Java 对象存储在堆中
		Date testData = null;
		//等同于 Date *testData = NULL;
		
		CalendarTest();
		
		//2.其他私有类/enum 会在编译成字节码时生成对应的　class 文件
		SubObjectTest subObject = new SubObjectTest();
		String name = subObject.name();
		name = new String("hello");
		System.out.println("subObject name = " + subObject.name());
		
		//3. 对于直接返回对象的封装要注意,类比于 c++
		//此时返回的是 Date *;
		//此时可以通过.clone 进行深复制,避免这个问题
		Date createDate = subObject.createDate();
		System.out.println("create data before:" + createDate);
		createDate.setDate(11);
		System.out.println("create data after:" + subObject.createDate());
	
		//4.同名类可以访问 private 的数据
		
		//--static 关键字
		//5.static 变量同 C++ 的处理方式类似，static 变量属于类
		//6.静态常量
		//System.out 是 class System 的 public static final PrintStream out = ...
		//7.静态函数,是没有 this 参数的方法
		//调用静态函数最好直接使用类名称，而不是使用变量名称
		
		//类的静态变量可以直接通过静态函数初始化,见 subObject
		
		//8.类的单元测试可以直接使用 static void main() 进行测试
		//执行命令行的 java 对应的Object 对应的 main 才会被执行
		
		//9.Java函数的参数传递:通过值传递
		//对于C/C++这个值类似于 const Object *,对于基础类型则表示值拷贝
		Date paramDate = new Date();
		System.out.println("paramDate:" + paramDate);
		subObject.resetDate(paramDate); //默认执行了一次 Date.clone();
		System.out.println("reset paramDate:" + paramDate);

		//10.同一个构造函数可以调用另外一个构造函数
		//不过这样不好,提取出一个合适的函数可能更好
		

		//11.构造函数还可以使用初始化块,不过这个应该会令人比较难以理解

		//12.finalize 函数会在对象回收时调用,不过不应该这么处理.
		
		//13.类中未声明变量的属性(public/private)则默认为同package下的public
		//因此,最好指明类的变量属性,如果存在未指明也可以通过打包JAR 的方式
		//进行包密封(package sealing)
		

	}
	
	public static void CalendarTest()
	{
		//当前日期
		LocalDate date = LocalDate.now(); // static
		
		//获取当前日期
		int month = date.getMonthValue();
		//System.out.println("month:" + month);
		int today = date.getDayOfMonth();
		//System.out.println("today:" + today);
		
		//当月1号的日期
		date = date.minusDays(today - 1);
		//System.out.println("date:" + date.toString());
		
		//当月1号是周几
		DayOfWeek weekday = date.getDayOfWeek();
		int value = weekday.getValue(); 
		//System.out.println("fisrt data weekdata:" + value);
		
		//System.out.println("Mon Tue Wed Thu Fri Sat Sun");
		for(int i = 1; i < value; i++)
		{
			System.out.print("    ");
		}
		
		while(date.getMonthValue() == month) //当前月份
		{
			System.out.printf("%3d", date.getDayOfMonth()); // 当前日期
			if(date.getDayOfMonth() == today)
			{
				System.out.print("*");
			}
			else
			{
				System.out.print(" ");
			}
			
			date = date.plusDays(1);
			
			//换行
			if(date.getDayOfWeek().getValue() == 1)
			{
				System.out.println();
			}
		}
		if(date.getDayOfWeek().getValue() != 1)
		{
			System.out.println();
		}
	}
}

class SubObjectTest
{
	//函数不能使用声明,但是类是包含的，这些数据将在构造对象的时候被java
	//自动初始化
	private String m_sName;
	private Date m_dateCreate;
	private static int ID;
	private int m_iId = assignId();

	static
	{
		System.out.println("static SubObjectTest");
	}
	
	public static int assignId()
	{
		return ID++;
	}
	
	
	public SubObjectTest()
	{
		this.m_sName = "subObjectTest";
		m_dateCreate = new Date();
	}	
	
	public String name()
	{
		return m_sName;
	}
	
	public Date createDate()
	{
		return (Date)m_dateCreate.clone();
	}
	
	public void resetDate(Date date)
	{
		date.setDate(11);
	}
	
}
