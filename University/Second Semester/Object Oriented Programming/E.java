/**
 * PO 2021/22, Problem E - Funkcje wieloargumentowe
 * 2025-04-05 : https://satori.tcs.uj.edu.pl/contest/9753924/problems/9878517
 * @author Hubert Jastrzębski
 */

import java.util.ArrayList;
import java.util.List;

public class Functions {
    public static <T, S> Function<T, S> constant (S x) {
        return new Function<>() {
            @Override
            public int arity() {
                return 0;
            }

            @Override
            public S compute(List<? extends T> args) throws GenericFunctionsException {
                if (args == null || args.size() != arity())
                    throw new GenericFunctionsException();
                return x;
            }
        };
    }

    public static <T extends S, S> Function<T, S> proj (int n, int k) throws GenericFunctionsException {
        if (k < 0 || k >= n)
            throw new GenericFunctionsException();

        return new Function<T, S>() {
            @Override
            public int arity() {
                return n;
            }

            @Override
            public S compute(List<? extends T> args) throws GenericFunctionsException {
                if (args == null || args.size() != arity())
                    throw new GenericFunctionsException();
                return args.get(k);
            }
        };
    }

    public static <K, T, S> Function<K, S> compose
            (Function<? super T, ? extends S> f, List<? extends Function<? super K, ? extends T>> inner) throws GenericFunctionsException {
        if (f == null || inner == null || f.arity() != inner.size())
            throw new GenericFunctionsException();
        for (var g : inner)
            if (g == null || g.arity() != inner.get(0).arity())
                throw new GenericFunctionsException();

        return new Function<K, S>() {
            @Override
            public int arity() {
                return inner.get(0).arity();
            }

            @Override
            public S compute(List<? extends K> args) throws GenericFunctionsException {
                List<T> innerArgs = new ArrayList<>();
                for (var g : inner)
                    innerArgs.add(g.compute(args));
                return f.compute(innerArgs);
            }
        };
    }
}