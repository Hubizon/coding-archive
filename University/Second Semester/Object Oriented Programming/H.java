/**
 * PO 2024/25, Problem H - Prace Zlecone
 * 2025-04-28 : https://satori.tcs.uj.edu.pl/contest/9753924/problems/9943174
 * @author Hubert Jastrzębski
 */

import java.util.Map;
import java.util.Queue;
import java.util.concurrent.Callable;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentLinkedQueue;

public class Scheduler {
    private static class Task<T> {
        final Callable<T> callable;
        T result;
        Exception exception;
        boolean done = false;

        Task(final Callable<T> callable) {
            this.callable = callable;
        }

        void run() {
            try {
                result = callable.call();
            } catch (Exception e) {
                exception = e;
            }
            finally {
                done = true;
            }
        }
    }

    private Map<Thread, ConcurrentLinkedQueue<Task<?>>> tasks = new ConcurrentHashMap<>();

    Scheduler() { }

    public <T> T delegate(Thread t, Callable<T> c) throws Exception {
        Task<T> myTask = new Task<>(c);
        var currentThread = Thread.currentThread();

        tasks.computeIfAbsent(t, key -> new ConcurrentLinkedQueue<>()).add(myTask);
        synchronized (this) {
            notifyAll();
        }

        Queue<Task<?>> queue = tasks.computeIfAbsent(currentThread, key -> new ConcurrentLinkedQueue<>());
        while (true) {
            Task<?> task;
            task = queue.poll();
            if (task == null) {
                if (myTask.done) {
                    if (myTask.exception != null)
                        throw myTask.exception;
                    return myTask.result;
                }
                synchronized (this) {
                    wait();
                }
                continue;
            }
            task.run();
            synchronized (this) {
                notifyAll();
            }
        }
    }
}
