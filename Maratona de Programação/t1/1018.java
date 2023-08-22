    import java.util.Scanner;
    class Main {

        public static void main(String[] args) {

            Scanner sc = new Scanner(System.in);
            int value = sc.nextInt();

            int[] possibleBankNotes = {100, 50, 20, 10, 5, 2, 1};

            int i = 0;

            System.out.println(value);

            while(i < possibleBankNotes.length){

                int layer = possibleBankNotes[i];
                int amount = (int) Math.floor((float) value / layer);
                System.out.println(amount + " nota(s) de R$ " + layer + ",00");
                value -= amount * layer;
                i++;

            }

        }

    }