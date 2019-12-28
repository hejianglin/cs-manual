//继承
//1.java 的继承只有共有继承
//2.java 不支持多继承,但支持实现多个 inteface
import java.time.LocalDate;
import java.util.Objects;
import java.util.ArrayList;

public class InheritTest
{
	public static void main(String[] main)
	{
		Manager manager = new Manager("jack",28,15000,3000);
		//3.同样支持多态,不希望方法具有多态则设置为 final
		//final 有重要的一点目的:确保方法或类的意图不会被改变
		Employee jack = manager;
		System.out.println("manager salary:" + manager.salary());
		System.out.println("jack salary:" + jack.salary());

		//4.进行类型转换之前应该进行 instanceof 进行关于 class 的检查
		if(jack instanceof Manager)
		{
			System.out.println("jack is manager");
		}
		else
		{
			System.out.println("jack does not manager");
		}

		//6.权限管理
		//(1).子类不能访问超类的私有域
		//(2).子类可以访问超类的proteced
		//(3).java的proteced域对于所有子类和同包中其他类可见
		//(4).若未声明权限默认情况为对同一包的其他可见

		//7.Object,所有类的超类
		//(1).因此你可以用object 类引用其他任意对象,JNI返回的jobject就是这个类型
		//(2).补充(1),所有数组类型也是[因为是指针的关系?]
		//(3).equals 用于判断2个对象是否是同一个引用? 测试一下
		Employee tom = new Employee("tom",25,10000);
		Employee mario = new Employee("mario",35,20000);
		if(tom.equals(jack))//看上去是比对 object 了,果然没什么用,需要有用的话,需要自己重载一下
		{
			System.out.println("tom no equal jack");
		}
		else
		{
			System.out.println("tom equal jack");
		}
		//注意: 
		//<1>对象的比较需要使用Object.equals进行比较,避免为 NULL
		//<2>子类的equals需要先比较 super.equals 的比较
		
		//8.一致性的检查
		//get class 可以获取正确的对象
		System.out.println("manager get class:" + manager.getClass());
		System.out.println("jack get class:" + jack.getClass());
		System.out.println("tom get class:" + tom.getClass());

		//子类instanceof 可以等于超类,反之不行
		if(manager instanceof Employee)
		{
			System.out.println("manager instanceof Employee");//output
		}
		else
		{
			System.out.println("manager not instanceof Employee");
		}

		if(jack instanceof Manager)
		{
			System.out.println("jack instanceof Manager");//output
		}
		else
		{
			System.out.println("jack not instanceof Manager");
		}

		if(tom instanceof Manager)
		{
			System.out.println("tom instanceof Manager");
		}	
		else
		{
			System.out.println("tom not instanceof Manager");//output
		}

		//比较同一引用
		if(tom == mario)
		{
			System.out.println("tom == mario");
		}
		else
		{
			System.out.println("tom != mario");//output
		}

		if(jack == manager)
		{
			System.out.println("jack == manager");
		}
		else
		{
			System.out.println("jack != manager");
		}

		//toString(),建议对每个自定义类添加toString,用于调试
		System.out.println("manager class name: " + manager.getClass().getName());
		System.out.println("employee to string:" + tom.toString());

		//hashCode
		System.out.printf("tom hash code = %X\n",tom.hashCode());


		//ArrayList
		ArrayList<Employee> atEmployee = new ArrayList<Employee>();
		atEmployee.add(jack);
		atEmployee.add(tom);
		System.out.println("ArrayList size = " + atEmployee.size());
		Employee[] arrayEmployee = new Employee[atEmployee.size()];
		atEmployee.toArray(arrayEmployee);
		System.out.println("arrayEmployee size = " + arrayEmployee.length);

		atEmployee.add(new Employee("ming",18,3000));
		System.out.println("ArrayList size = " + atEmployee.size());
		System.out.println("arrayEmployee size = " + arrayEmployee.length);
	}

}

//5.抽象类,和c/c++类似
//存在一个抽象方法的类只能是抽象类
//不含抽象方法的类可以定义为抽象类
//抽象类不能实例话不过可以用多态
abstract class Person
{
	public abstract String getDesciption(); //抽象方法
}

//BaseObject
class Employee
{
	private String name;
	private int age;
	double salary;

	public Employee()
	{}

	public Employee(String aName,int iAge,double salary)
	{
		this.name = aName;
		this.age = iAge;
		this.salary = salary;
	}

	public void setSalary(double aSalary)
	{
		this.salary = aSalary;
	}

	public double salary()
	{
		return this.salary;
	}

	public String name()
	{
		return this.name;
	}

	public void setName(String aName)
	{
		this.name = aName;
	}

	public int age()
	{
		return this.age;
	}

	public void setAge(int iAge)
	{
		this.age = iAge;
	}

//	public int hashCode()
//	{
//		return Objects.hash(this.name,this.age,this.salary);
//	}
}

//通过 extends 表示继承
class Manager extends Employee
{
	private double bonus;

	public Manager()
	{
	}

	public Manager(String name,int age, double salary, double bonus)
	{
		//2.使用supper构造基类只能放在子类的构造函数的第一句
		super(name,age,salary);
		this.bonus = bonus;
	}

	public void setBonus(double bonus)
	{
		this.bonus = bonus;
	}

	public double bonus()
	{
		return this.bonus;
	}

	//1.使用Base的私有域时,同样只能通过相应获取函数,并通过 supper 获取
	public double salary()
	{
		return super.salary() + this.bonus;
	}

}


