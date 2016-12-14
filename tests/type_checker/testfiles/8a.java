class Main {
    public static void main(String[] args) {

    }
}

class A {
	public int getInt() {
		int a;
		int b;
		int c;
		A clazz;

		clazz = new A();

		a = 1;
		b = 2;

		c = a + b;
		c = a + 1;
		c = 1 + b;

		c = a - b;
		c = a - 1;
		c = 1 - b;

		c = a * b;
		c = a * 1;
		c = 1 * b;

		c = a % b;
		c = a % 1;
		c = 1 % b;
		c = 1 % 0;

		c = 1 + true; //bad
		c = true + 1; //bad
		c = clazz.getInt() + clazz.getInt();

		return 0;
	}
}
