class Factorial {
    public static void main(String[] a){
        Fac fac;
        int ret;
        fac = new Fac();
        ret = fac.ComputeFac(10);
    }
}

class Fac extends Base {
	int b;

    public int ComputeFac(int num){
        return this.b;
    }
}

class Base {
	int a;
}
