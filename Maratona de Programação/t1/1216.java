    import java.util.ArrayList;
    import java.util.List;
    import java.util.Scanner;

    class Main {

        public static void main(String[] args) {

            List<Integer> meters = new ArrayList<>();

            Scanner sc = new Scanner(System.in);

            while (sc.hasNextLine()) {

                try{

                    meters.add(Integer.parseInt(sc.nextLine()));

                }catch (NumberFormatException ignored){}

            }

            double average = ((double)meters.stream().reduce(Integer::sum).get())/meters.size();

            System.out.printf("%.1f\n",average);

        }

    }