    import java.math.BigDecimal;
    import java.util.Scanner;
    class Main {

        public static void main(String[] args) {

            Scanner sc = new Scanner(System.in);
            BigDecimal value = sc.nextBigDecimal();

            if(value.compareTo(BigDecimal.ZERO) < 0 || value.compareTo(new BigDecimal("100")) > 0){

                System.out.println("Fora de intervalo");
                return;

            }

            System.out.print("Intervalo ");

            if(value.compareTo(new BigDecimal("25")) <= 0){

                System.out.println("[0,25]");
                return;

            }

            if(value.compareTo(new BigDecimal("50")) <= 0){

                System.out.println("(25,50]");
                return;

            }

            if(value.compareTo(new BigDecimal("75")) <= 0){

                System.out.println("(50,75]");
                return;

            }

            System.out.println("(75,100]");

        }

    }