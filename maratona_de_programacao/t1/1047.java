    import java.util.Scanner;
    class Main {

        public static void main(String[] args) {

            Scanner sc = new Scanner(System.in);

            int initialHour = sc.nextInt();
            int initialMinute = sc.nextInt();
            int finalHour = sc.nextInt();
            int finalMinute = sc.nextInt();

            int totalMinutes = initialHour * 60 + initialMinute;
            int totalMinutesFinal = finalHour * 60 + finalMinute;

            int difference = totalMinutesFinal - totalMinutes;

            if (difference < 0)
                difference = 24 * 60 + difference;

            int answerHours = difference / 60;
            int answerMinutes = difference % 60;

            if(difference == 0)
                answerHours = 24;

            System.out.println("O JOGO DUROU "+answerHours+" HORA(S) E "+answerMinutes+" MINUTO(S)");

        }

    }