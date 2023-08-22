    import java.util.Scanner;
    class Main {

        public static void main(String[] args) {

            Scanner sc = new Scanner(System.in);
            float n1 = sc.nextFloat();
            float n2 = sc.nextFloat();

            System.out.printf("MEDIA = %.5f\n", ((n1 * 3.5 + n2 * 7.5))/11);
        }

    }