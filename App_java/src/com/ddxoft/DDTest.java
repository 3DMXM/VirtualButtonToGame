package com.ddxoft;
import com.sun.jna.Library;
import com.sun.jna.Native;

public class DDTest {
	 public static void main(String[] args) {
		 System.out.println("测试开始");
		 
		 //DD.INSTANCE.DD_mov(500, 500);   //绝对移动
		 //DD.INSTANCE.DD_movR(100, 100); //相对移动
		 //DD.INSTANCE.DD_btn(4);DD.INSTANCE.DD_btn(8); //鼠标右键
		 DD.INSTANCE.DD_key(601, 1);DD.INSTANCE.DD_key(601, 2); //键盘win
		 DD.INSTANCE.DD_str("123@AbC"); //字符串
	 }
	 
	 public interface DD extends Library {
		   DD INSTANCE = (DD)Native.loadLibrary("DD64", DD.class);
		   //64位JAVA调用DD64.dll, 32位调用DD32.dll 。与系统本身位数无关。、
		   public int DD_mov(int x, int y);
		   public int DD_movR(int dx, int dy);
		   public int DD_btn(int btn);
		   public int DD_whl(int whl);
		   public int DD_key(int ddcode, int flag);
		   public int DD_str(String s);  
	 }
}
