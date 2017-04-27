class Main {
	public static void main(String[] args) {
		A n;
		A m;
		int t;
		n = new A();
		m = new A();
		t = n.f();
		t = m.f();
	}
}

class A {
	public int f() {
		return 0;
	}
}
