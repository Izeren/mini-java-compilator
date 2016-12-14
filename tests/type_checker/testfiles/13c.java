class Factorial {
    public static void main(String[] a){
        Fac fac;
        fac = new Fac();	
        
        fac.ComputeFac(); 
    }
}

class Fac {

    public void ComputeFac(int a, boolean b){
        Fac fac;
        fac = new Fac();	
        fac.ComputeFac(5, true); 
        fac.ComputeFac(a, b); 
        fac.ComputeFac(a, 5); //bad
        fac.ComputeFac(false, false); //bad
        fac.ComputeFac(5 + 2, false); 
        fac.ComputeFac(5 + 2, 1 + 3); 
    }
}
