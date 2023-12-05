package part2;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Main {
    public static void main(String[] args) {
        String filePath = "./test_input.in";
        List<Character> StringNumList = new ArrayList<>();
        List<Integer> finalNumList = new ArrayList<>();

        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            String line;

            while ((line = reader.readLine()) != null) {
                line = line.toUpperCase();
                StringNumList = new ArrayList<>();

                // for (int i = 0; i < line.length(); i++) {
                // char symbol = line.charAt(i);

                // if (Character.isDigit(symbol)) {
                // StringNumList.add(symbol);
                // }
                // }

                System.out.println(line);

                // finalNumList.add(addDigits(StringNumList));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        // System.out.println(sum(finalNumList));
        // System.out.println();
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

enum Digit {
    ONE(1),
    TWO(2),
    THREE(3),
    FOUR(4),
    FIVE(5),
    SIX(6),
    SEVEN(7),
    EIGHT(8),
    NINE(9);

    private final int digitNumber;

    Digit(int digitNumber) {
        this.digitNumber = digitNumber;
    }

    public int getDigitNumber() {
        return this.digitNumber;
    }

    public static Digit fromString(String digitStr) {
        return Digit.valueOf(digitStr.toUpperCase());
    }
}
