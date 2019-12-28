//Java对几个基本数据类型提供了类的包装机器
//分别有: 
//1.Integer
//2.Long
//3.Float
//4.Double
//5.Short
//6.Byte
//7.Character
//8.Void
//9.Boolean
//我们以 Integer 来作为切入点
//首先看下 Integer 的定义:
//public final class Integer extends Number implements Comparable<Integer>
public class IntegerTest {
    public static void main(String[] main) {
        //Integer 包含的数据域不能被修改,除非指向新引用
        //Integet 支持对int自动拆解包
    	Integer value = Integer.valueOf(3);

    	//value 自动拆解为 value.intValue();
    	System.out.println("value = " + value);
    }


}

class IntegerHandler {



}
