/**
 * PO 2023/24, Problem B - Klasa Świra
 * 2025-03-22 : https://satori.tcs.uj.edu.pl/contest/9753924/problems/9786090
 * @author Hubert Jastrzębski
 */

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.LinkedList;

public class a {
    LinkedList<Integer> arr = new LinkedList<>();
    Boolean sorted, return_first = false;
    a a;

    public a() {
        sorted = true;
        a = new a(this);
    }

    public a(a a) {
        sorted = false;
        this.a = a;
    }

    int a() {
        if (!sorted)
            a.a();
        return_first = true;
        return arr.removeLast();
    }

    a a(int a) {
        if (!sorted)
            return this.a.a(a);
        if (return_first) {
            arr.addFirst(a);
            return_first = false;
            return this.a;
        } else {
            arr.addLast(a);
            return this;
        }
    }

    public String toString() {
        if (sorted) {
            LinkedList<Integer> sorted_arr = new LinkedList<>(arr);
            Collections.sort(sorted_arr);
            return sorted_arr.toString();
        } else
            return a.arr.toString();
    }
}