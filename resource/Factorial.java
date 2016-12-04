class Factorial{
    public static void main(String[] a){
    Fac fac;
    fac = new Fac();	
    System.out.println(fac.ComputeFac(10));
    }
}

class Fac {

    public int ComputeFac(int num){
    int num ;
    int num_aux ;
    if (num < 1)
        num_aux = 1 ;
    else 
        num_aux = num * (this.ComputeFac(num-1)) ;
    return num_aux ;
    }
}
