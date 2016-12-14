class Main {
    public static void main(String[] args) {
        int a;
        Summator sr;
        sr = new Summator();
        a = sr.sum(3, 5);
        a = sr.subtract(5, 3);
    }
}

class Summator {
    public int sum(int a, int b) {
        int c;
        c = this.subtract(a, b);
        return a + b;
    }
    
    private int subtract(int a, int b)
    {
        return a - b;
    }
}
