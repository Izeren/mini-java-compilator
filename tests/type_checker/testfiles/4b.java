class Factorial {
    public static void main(String[] a){
        Fac2 fac; //bad
    }
}

class Fac {

    public void ComputeFac(int num){
    }
    
    public void ComputeFac2(Fac fac){
    }
    
    public void ComputeFac3(Fac2 fac){ //bad
    }
    
    public void ComputeFac4(int a, Fac2 fac, boolean b){ //bad
    }
}
