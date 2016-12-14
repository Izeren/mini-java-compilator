class Main {
    public static void main(String[] args){
    }
}

class A {
	public int getInt() {
        int[] array;
        int b;
        boolean c;

        b = 1;
        c = true;

        array = new int[10];

        array = new int[b];

        array = new int[c];

        array = new int[(1 + 2) * b];

        return 0;
	}