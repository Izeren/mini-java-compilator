class Main {
    public static void main(String[] args) {

    }
}

class A {
	public int getInt() {
		boolean a;
		boolean b;
		boolean c;

		a = true;
		b = false;

		c = a && true;
		c = false || b;

		c = 1 && 2;
		c = a && -4;
		c = 7 || b;

		return 0;
	}
}
