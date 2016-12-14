class Factorial {
    public static void main(String[] a){
        Fac fac;
        fac = new Fac();	
        
        fac.ComputeFac(); 
        fac.ComputeFac2(); //bad
    }
}

class Fac {

    public void ComputeFac(){
        Fac fac;
        fac = new Fac();	
        
        fac.ComputeFac(); 
        fac.ComputeFac2(); //bad
    }
}
