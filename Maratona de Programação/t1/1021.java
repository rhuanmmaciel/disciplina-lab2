    import java.math.BigDecimal;
    import java.util.Scanner;
    class Main {

        public static void main(String[] args) {

            Scanner sc = new Scanner(System.in);
            BigDecimal value = sc.nextBigDecimal();

            int[] possibleBankNotes = {100, 50, 20, 10, 5, 2};

            BigDecimal[] possibleCoins = {new BigDecimal("1.00"), new BigDecimal("0.50"), new BigDecimal("0.25"),
                    new BigDecimal("0.10"), new BigDecimal("0.05"), new BigDecimal("0.01")};

            int i = 0;

            System.out.println("NOTAS:");

            while(i < possibleBankNotes.length){

                BigDecimal layer = new BigDecimal(possibleBankNotes[i]);
                BigDecimal amount = getAmount(value, layer);
                System.out.println(amount + " nota(s) de R$ " + layer + ".00");
                value = value.subtract(amount.multiply(layer));
                i++;

            }

            i = 0;

            System.out.println("MOEDAS:");

            while(i < possibleCoins.length){

                BigDecimal layer = possibleCoins[i];
                BigDecimal amount = getAmount(value, layer);
                System.out.println(amount.intValue() + " moeda(s) de R$ " + String.format("%.2f", layer.floatValue()));
                value = value.subtract(amount.multiply(layer));
                i++;

            }

        }

        private static BigDecimal getAmount(BigDecimal value, BigDecimal divisor){

            int i = 0;

            for(; value.compareTo(divisor) >= 0; i++)
                value = value.subtract(divisor);

            return BigDecimal.valueOf(i);
        }

    }