class Factorial {
    public static void main(String[] args){
        int[] a;
        int b;
        a = new int[10];
        a[0] = 5;
        b = a[false]; //bad
        b = a[0];
    }
}

class Fac {

    public int ComputeFac(int num){
        int[] a;
        int b;
        a = new int[10];
        a[0] = 5;
        b = a[false]; //bad
        b = a[0];
        return 0;
    }
}
