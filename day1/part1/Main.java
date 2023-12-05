import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Main {
    public static void main(String[] args) {
        String filePath = "./input.in";
        List<Character> StringNumList = new ArrayList<>();
        List<Integer> finalNumList = new ArrayList<>();

        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            String line;

            while ((line = reader.readLine()) != null) {
                StringNumList = new ArrayList<>();

                for (int i = 0; i < line.length(); i++) {
                    char symbol = line.charAt(i);

                    if (Character.isDigit(symbol)) {
                        StringNumList.add(symbol);
                    }
                }

                finalNumList.add(addDigits(StringNumList));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        System.out.println(sum(finalNumList));
    }

    static int addDigits(List<Character> originalList) {
        List<Character> newList;

        if (originalList.size() > 1) {
            newList = Arrays.asList(originalList.get(0), originalList.get(originalList.size() - 1));
        } else {
            originalList.add(originalList.get(0));
            newList = originalList;
        }

        StringBuilder sb = new StringBuilder();
        for (Character ch : newList) {
            sb.append(ch);
        }

        return Integer.parseInt(sb.toString());
    }

    static int sum(List<Integer> numbers) {
        return numbers.stream()
                .mapToInt(Integer::intValue)
                .sum();
    }
}
