class Factorial {
    public static void main(String[] a){
        int a;
        Fac fac;
        
        a = 1;
        fac = new Fac();	
        
        fac.ComputeFac(); //bad
        a.ComputeFac();
    }
}

class Fac {

    public void ComputeFac(){
        int a;
        Fac fac;
        
        a = 1;
        fac = new Fac();	
        
        fac.ComputeFac(); //bad
        a.ComputeFac();
    }
}
