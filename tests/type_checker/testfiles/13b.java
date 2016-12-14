class Factorial {
    public static void main(String[] args){
        Fac fac;
        int a;
        fac = new Fac();	
        a = fac.ComputeFac(); 
        a = fac.ComputeFac2(); //bad
    }
}

class Fac {

    public int ComputeFac(){
        Fac fac;
        int a;
        fac = new Fac();	
        
        a = fac.ComputeFac(); 
        a = fac.ComputeFac2(); //bad
        return 0;
    }
}
