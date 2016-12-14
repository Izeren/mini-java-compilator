class Factorial {
    public static void main(String[] a){
        int a;
        int b;
        boolean c;
        Fac fac1;
        Fac fac2;
        
        a = 1;
        c = true;
        fac1 = new Fac();
        fac2 = new Fac();
        
        b = a; 
        b = c; //bad
        a = fac1; //bad
        fac2 = fac1; 
        fac1 = c; //bad
        a = fac1.ComputeFac();
    }
}

class Fac {

    public int ComputeFac(int num){
        int a;
        int b;
        boolean c;
        Fac fac1;
        Fac fac2;
        
        a = 1;
        c = true;
        fac1 = new Fac();
        fac2 = new Fac();
        
        b = a; 
        b = c; //bad
        a = fac1; //bad
        fac2 = fac1; 
        fac1 = c; //bad
        a = fac1.ComputeFac();
        
        return 5;
    }
}