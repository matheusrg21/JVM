class Concatenacao {
    public static void main(String[] args) {
        String string1 = new String("Tiago");
        String string2 = " ";
        String string3 = new String("Careca");
        int um = 1;
        float dois = 2.0f;
        long tres = 3;
        double quatro = 4.0;
        short cinco = 5;
        byte seis = 6;
        boolean verdadeiro = true;
        boolean falso = false;

        System.out.println((byte)6);
        System.out.println(verdadeiro);
        System.out.println(cinco);
        System.out.print(string1+string2+string3 + " " + um+ " " + dois + " " + tres + " " + quatro + " " + cinco + " " + seis + " " + verdadeiro + " " + falso);
        System.out.println();
    }
}