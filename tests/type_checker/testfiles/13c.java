class Factorial {
    public static void main(String[] a){
        Fac fac;
        int ret;
        fac = new Fac();	
        
        ret = fac.ComputeFac(); 
        ret = fac.ComputeFac(1, true, true);
    }
}

class Fac {

    public int ComputeFac(int a, boolean b){
        Fac fac;
        int v;
        fac = new Fac();	
        v = fac.ComputeFac(5, true); 
        v = fac.ComputeFac(a, b); 
        v = fac.ComputeFac(a, 5); //bad
        v = fac.ComputeFac(false, false); //bad
        v = fac.ComputeFac(5 + 2, false); 
        v = fac.ComputeFac(5 + 2, 1 + 3); //bad
        return 0;
    }
}
