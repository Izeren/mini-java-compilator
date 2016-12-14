class Factorial {
    public static void main(String[] a){
        Fac2 fac; //bad
    }
}

class Fac {

    public int ComputeFac(int num){
        return 0;
    }
    
    public int ComputeFac2(Fac fac){
        return 0;
    }
    
    public int ComputeFac3(Fac2 fac){ //bad
        return 0;
    }
    
    public int ComputeFac4(int a, Fac2 fac, boolean b){ //bad
        return 0;
    }
}
