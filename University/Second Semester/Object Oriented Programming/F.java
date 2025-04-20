/**
 * PO 2024/25, Problem F - Rozwijanie Funkcji
 * 2025-04-18 : https://satori.tcs.uj.edu.pl/contest/9753924/problems/9905425
 * @author Hubert Jastrzębski
 */

import java.util.ArrayList;
import java.util.Collections;
import java.util.function.IntUnaryOperator;
import java.util.function.ToIntFunction;
import java.util.stream.IntStream;

@FunctionalInterface
interface VarIntFunction extends ToIntFunction<int[]> {

    default int apply(int... args) {
        if (args == null)
            throw new IllegalArgumentException();
        return applyAsInt(args);
    }

    default VarIntFunction applyPartial(int... partialArgs) {
        if (partialArgs == null)
            throw new IllegalArgumentException();
        if (partialArgs.length == 0)
            return this;
        return args -> {
            if (args == null)
                throw new IllegalArgumentException();
            int[] allArgs = IntStream.concat(
                    IntStream.of(partialArgs),
                    IntStream.of(args)
            ).toArray();
            return apply(allArgs);
        };
    }

    /**
     * @return this function as a unary function (int -> int)
     */
    default IntUnaryOperator asUnary() {
        return x -> apply(new int[]{x});
    }

    /**
     * @param argsOrder permutation of (1, 2, ..., n)
     * @return function which first permutes the arguments as given by argsOrder, and then applies original function
     */
    default VarIntFunction withPermutedArgs(int... argsOrder) {
        if (argsOrder == null || argsOrder.length == 0)
            throw new IllegalArgumentException();
        boolean[] perm_correct = new boolean[argsOrder.length];
        for (int arg : argsOrder) {
            if (arg < 1 || arg > argsOrder.length || perm_correct[arg - 1])
                throw new IllegalArgumentException();
            perm_correct[arg - 1] = true;
        }

        return args -> {
            if (args == null || args.length != argsOrder.length)
                throw new IllegalArgumentException();

            int[] pemutatedArgs = new int[argsOrder.length];
            for (int i = 0; i < argsOrder.length; i++)
                pemutatedArgs[argsOrder[i] - 1] = args[i];
            return apply(pemutatedArgs);
        };
    }

    /**
     * @param reqArity non-negative integer representing required number of arguments
     * @return function which throws if applied to the number of arguments different than reqArity
     */
    default VarIntFunction withRequiredArity(int reqArity) {
        if (reqArity < 0)
            throw new IllegalArgumentException();
        return args -> {
            if (args == null || args.length != reqArity)
                throw new IllegalArgumentException();
            return apply(args);
        };
    }
}