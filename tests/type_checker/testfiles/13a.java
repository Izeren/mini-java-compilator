class Factorial {
    public static void main(String[] args){
        int a;
        Fac fac;
        int b;
        
        a = 1;
        fac = new Fac();	
        
        b = fac.ComputeFac();
        b = a.ComputeFac(); //bad
    }
}

class Fac {

    public int ComputeFac(){
        int a;
        Fac fac;
        int b;
        
        a = 1;
        fac = new Fac();	
        
        b = fac.ComputeFac();
        b = a.ComputeFac(); //bad
        return 0;
    }
}
