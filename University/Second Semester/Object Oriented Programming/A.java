/**
 * PO 2024/25, Problem A - Książka Telefoniczna
 * 2025-03-17 : https://satori.tcs.uj.edu.pl/contest/9753924/problems/9761363
 * @author Hubert Jastrzębski
 */

public class PhoneBook {
    public enum NumberFormat {DIGITS, HYPHENED}
    public enum Type {NOTHING,NUMBERS,BOOKS}
    public static final int MAX_BOOKS = 10;

    private NumberFormat format;
    private Type type;
    private int capacity;
    private int size;
    private int[] numbers;
    private String[] str_numbers;
    private PhoneBook[] books;

    private Boolean isValidNumber(String number) {
        String regex = (format == NumberFormat.DIGITS ? "^[0-9]{9}$" : "^[0-9]{3}-[0-9]{3}-[0-9]{3}$");
        return number != null && number.matches(regex) && number.charAt(0) != '0';
    }

    private int numberToInt(String number) {
        return Integer.parseInt(number.replaceAll("-", ""));
    }

    private String formatNumber(String number) {
        if (format == NumberFormat.DIGITS)
            return number;
        else {
            return number.replaceAll("(\\d{3})(\\d{3})(\\d{3})", "$1-$2-$3");
        }
    }

    private int findNumber(int number_int) {
        int a = 0, b = size;
        while (a < b) {
            int mid = (a + b) / 2;
            if (numbers[mid] < number_int)
                a = mid + 1;
            else
                b = mid;
        }
        return a;
    }

    public PhoneBook() {
        this(NumberFormat.DIGITS, 10);
    }

    public PhoneBook(NumberFormat format) {
        this(format, 10);
    }

    public PhoneBook(int capacity) {
        this(NumberFormat.DIGITS, capacity);
    }

    public PhoneBook(NumberFormat format, int capacity) {
        if (format != NumberFormat.DIGITS && format != NumberFormat.HYPHENED)
            format = NumberFormat.DIGITS;
        if (!(capacity >= 0))
            capacity = 10;
        this.format = format;
        this.capacity = capacity;
        this.size = 0;
        this.type = Type.NOTHING;
    }

    public PhoneBook copyBook() {
        PhoneBook pb = new PhoneBook(this.format, this.capacity);
        pb.size = this.size;
        pb.type = this.type;
        if (type == Type.NUMBERS) {
            pb.numbers = new int[capacity];
            pb.str_numbers = new String[capacity];
            for (int i = 0; i < size; i++) {
                pb.numbers[i] = this.numbers[i];
                pb.str_numbers[i] = this.str_numbers[i];
            }
        }
        else if (type == Type.BOOKS) {
            pb.books = new PhoneBook[MAX_BOOKS];
            for (int i = 0; i < size; i++)
                pb.books[i] = this.books[i].copyBook();
        }
        return pb;
    }

    public int size() {
        if (this.type == Type.NUMBERS) {
            return size;
        }
        else if (this.type == Type.BOOKS) {
            int res = 0;
            for (int i = 0; i < size; i++)
                res += this.books[i].size();
            return res;
        }
        return 0;
    }

    public int capacity() {
        return capacity;
    }

    public boolean isEmpty() {
        return (size == 0);
    }

    public boolean isFull() {
        return (size() >= capacity);
    }

    public PhoneBook add(String number) {
        if (!isValidNumber(number) || size() >= capacity || type == Type.BOOKS)
            return this;

        if (type == Type.NOTHING) {
            type = Type.NUMBERS;
            numbers = new int[capacity];
            str_numbers = new String[capacity];
        }

        int number_int = numberToInt(number);
        int pos = findNumber(number_int);
        if (numbers[pos] != number_int) {
            str_numbers[size] = String.valueOf(number_int);
            for (int i = size; i > pos; i--)
                numbers[i] = numbers[i - 1];
            numbers[pos] = number_int;
            size++;
        }

        return this;
    }

    public PhoneBook add(PhoneBook subBook) {
        if (subBook == null || size >= MAX_BOOKS || size() + subBook.size() > capacity || type == Type.NUMBERS)
            return this;

        PhoneBook subBookCopy = subBook.copyBook();
        subBookCopy.changeFormat(this.format);

        if (type == Type.NOTHING) {
            type = Type.BOOKS;
            books = new PhoneBook[MAX_BOOKS];
        }

        boolean is_already = false;
        for (int i = 0; i < size; i++) {
            if (books[i].equals(subBookCopy)) {
                is_already = true;
                break;
            }
        }

        if (!is_already) {
            books[size] = subBookCopy;
            size++;
        }

        return this;
    }

    public void changeFormat(NumberFormat format) {
        if (format != null && this.format != format) {
            this.format = format;
            if (type == Type.BOOKS) {
                for (int i = 0; i < size; i++) {
                    books[i].changeFormat(format);
                }
            }
        }
    }

    public boolean contains(String number) {
        if (!isValidNumber(number))
            return false;

        if (type == Type.NUMBERS) {
            int number_int = numberToInt(number);
            int pos = findNumber(number_int);
            return numbers[pos] == number_int;
        }
        else if (type == Type.BOOKS) {
            for (int i = 0; i < size; i++) {
                if (books[i].contains(number))
                    return true;
            }

            return false;
        }

        return false;
    }

    public boolean contains(PhoneBook pb) {
        if (pb == null || type != Type.BOOKS)
            return false;

        for (int i = 0; i < size; i++) {
            if (books[i].equals(pb))
                return true;
        }

        return false;
    }

    public boolean elementOf(PhoneBook pb) {
        if (pb == null)
            return false;

        return pb.contains(this);
    }

    public boolean subsetOf(PhoneBook pb) {
        if (pb == null)
            return false;
        if (type == Type.NOTHING)
            return true;
        if (type != pb.type)
            return false;

        if (type == Type.NUMBERS) {
            int i = 0, j = 0;
            while (i < size && j < pb.size) {
                if (numbers[i] == pb.numbers[j]) {
                    i++;
                    j++;
                } else if (numbers[i] > pb.numbers[j]) {
                    j++;
                } else {
                    return false;
                }
            }
            return i == size;
        }
        else if (type == Type.BOOKS) {
            for (int i = 0; i < size; i++) {
                if (!pb.contains(books[i]))
                    return false;
            }
            return true;
        }

        return true;
    }

    public boolean supersetOf(PhoneBook pb) {
        if (pb == null)
            return false;

        return pb.subsetOf(this);
    }

    @Override
    public boolean equals(Object o) {
        if (o == null || getClass() != o.getClass())
            return false;
        if (this == o)
            return true;

        PhoneBook pb = (PhoneBook) o;
        if (pb.type != type || pb.size != size)
            return false;

        if (type == Type.NUMBERS) {
            for (int i = 0; i < size; i++) {
                if (numbers[i] != pb.numbers[i])
                    return false;
            }
            return true;
        }
        else if (type == Type.BOOKS) {
            for (int i = 0; i < size; i++) {
                if (!pb.contains(books[i]))
                    return false;
            }
            return true;
        }

        return true;
    }

    @Override
    public String toString() {
        StringBuilder result = new StringBuilder();
        result.append("{\n");

        if (type == Type.NUMBERS) {
            for (int i = 0; i < size; i++) {
                if (numbers[i] != 0)
                    result.append("  ").append(formatNumber(str_numbers[i])).append("\n");
            }
        }

        else if (type == Type.BOOKS) {
            for (int i = 0; i < size; i++) {
                if (books[i] != null) {
                    String subStr = books[i].toString().replace("\n", "\n  ");
                    result.append("  ").append(subStr, 0, subStr.length() - 2);
                }
            }
        }

        result.append("}\n");
        return result.toString();
    }
}