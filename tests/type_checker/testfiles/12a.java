class Main {
    public static void main(String[] args){
    	A a;
    	B b;
    	Main main;
    	a = new A();
    	b = new B();
    	main = new Main();

    	a = new C();
    }
}

class A {
	public int getInt() {
		A a;
    	B b;
    	Main main;
    	a = new A();
    	b = new B();
    	main = new Main();
    	
    	a = new C(); 

    	return 1;
	}
}

class B {
}
