class Factorial{
    public static void main(String[] a){
    Fac fac;
    int a;
    fac = new Fac();	
    System.out.println(fac.ComputeFac(10));
    }
}

class Fac {

    public int ComputeFac(int num){
    int num2;
    int num_aux ;
    num_aux = 5;
    num2 = 2;
    if (num2 < 1)
        num_aux = 1 ;
    else 
        num_aux = num2 * (this.ComputeFac(num2-1)) ;
    return num_aux;
    }
}
