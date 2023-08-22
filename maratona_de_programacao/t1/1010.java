    import java.util.Scanner;
    class Main {

        public static void main(String[] args) {

            Scanner sc = new Scanner(System.in);
            sc.nextInt();
            float value = sc.nextInt() * sc.nextFloat() + (0 * sc.nextInt())  + sc.nextInt() * sc.nextFloat();

            System.out.printf("VALOR A PAGAR: R$ %.2f\n", value);
        }

    }