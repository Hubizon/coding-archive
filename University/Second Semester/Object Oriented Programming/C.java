/**
 * PO 2024/25, Problem C - Widok Grafu
 * 2025-03-29 : https://satori.tcs.uj.edu.pl/contest/9753924/problems/9816023
 * @author Hubert Jastrzębski
 */

import java.util.*;

public class GraphView {
    ArrayList<ArrayList<Boolean>> matrix;

    public GraphView() {
        matrix = new ArrayList<>();
    }

    private boolean isValidVertex(int vertex) {
        return vertex >= 0 && vertex < size();
    }

    public int size() {
        return matrix.size();
    }

    public void addVertex() {
        for (var row : matrix)
            row.add(false);
        matrix.add(new ArrayList<Boolean>());
        for (int i = 0; i < size(); i++)
            matrix.get(size() - 1).add(false);
    }

    public void removeVertex() {
        if (size() == 0)
            return;

        matrix.remove(size() - 1);
        for (var row : matrix)
            row.remove(size());
    }

    public void addEdge(int from, int to) {
        if (!isValidVertex(from) || !isValidVertex(to))
            return;
        matrix.get(from).set(to, true);
    }

    public void removeEdge(int from, int to) {
        if (!isValidVertex(from) || !isValidVertex(to))
            return;
        matrix.get(from).set(to, false);
    }

    public List asAdjacencyMatrix() {
        return new AbstractList<List<Boolean>>() {
            @Override
            public int size() {
                return GraphView.this.size();
            }

            @Override
            public List<Boolean> get(int index) {
                if (!isValidVertex(index))
                    throw new IndexOutOfBoundsException();
                return new AbstractList<Boolean>() {

                    @Override
                    public int size() {
                        return GraphView.this.size();
                    }

                    @Override
                    public Boolean get(int index2) {
                        return matrix.get(index).get(index2);
                    }

                    @Override
                    public Boolean set(int index2, Boolean element) {
                        if (element == null)
                            throw new NullPointerException();
                        boolean prev = matrix.get(index).get(index2);
                        matrix.get(index).set(index2, element);
                        return prev;
                    }
                };
            }

            @Override
            public List<Boolean> set(int index, List<Boolean> element) {
                if (!isValidVertex(index))
                    throw new IndexOutOfBoundsException();
                if (element.size() != size())
                    throw new IllegalArgumentException();

                var prev = List.copyOf(matrix.get(index));
                for (int i = 0; i < size(); i++)
                    if (element.get(i) == null)
                        throw new IllegalArgumentException();
                for (int i = 0; i < size(); i++)
                    matrix.get(index).set(i, element.get(i));
                return prev;
            }

            @Override
            public void clear() {
                matrix.clear();
            }

            @Override
            public Iterator<List<Boolean>> iterator() {
                return new Iterator<List<Boolean>>() {
                    int index = 0;

                    @Override
                    public boolean hasNext() {
                        return index < size();
                    }

                    @Override
                    public List<Boolean> next() {
                        if (!hasNext())
                            throw new NoSuchElementException();
                        return matrix.get(index++);
                    }
                };
            }
        };
    }

    public Map asAdjacencyMap() {
        return new AbstractMap<Integer, Set<Integer>>() {
            @Override
            public Set<Integer> get(Object key) {
                if (key == null)
                    throw new NullPointerException();

                if (!(key instanceof Integer))
                    throw new ClassCastException();

                int vertex = (int) key;
                if (!isValidVertex(vertex))
                    return null;

                return new AbstractSet<Integer>() {
                    @Override
                    public Iterator<Integer> iterator() {
                        return new Iterator<Integer>() {
                            int index = 0;

                            private void toNext() {
                                while (index < matrix.size() && !matrix.get(vertex).get(index))
                                    index++;
                            }

                            @Override
                            public boolean hasNext() {
                                toNext();
                                return index < matrix.size();
                            }

                            @Override
                            public Integer next() {
                                if (!hasNext())
                                    throw new NoSuchElementException();
                                return index++;
                            }
                        };
                    }

                    @Override
                    public int size() {
                        int s = 0;
                        for (int i = 0; i < matrix.size(); i++) {
                            if (matrix.get(vertex).get(i))
                                s++;
                        }
                        return s;
                    }

                    @Override
                    public boolean add(Integer to) {
                        if (!isValidVertex(to))
                            throw new IllegalArgumentException();
                        if (matrix.get(vertex).get(to))
                            return false;
                        matrix.get(vertex).set(to, true);
                        return true;
                    }

                    @Override
                    public boolean remove(Object o) {
                        if (o == null)
                            throw new NullPointerException();

                        int index = (int) o;
                        if (!matrix.get(vertex).get(index))
                            return false;

                        matrix.get(vertex).set(index, false);
                        return true;
                    }
                };
            }

            @Override
            public Set<Integer> put(Integer key, Set<Integer> value) {
                if (key < 0 || key >= size())
                    throw new IllegalArgumentException();
                Set<Integer> prev = new HashSet<>();
                for (int i = 0; i < size(); i++)
                    if (matrix.get(key).get(i))
                        prev.add(i);

                for (int i = 0; i < size(); i++)
                    matrix.get(key).set(i, false);

                for (var cell : value)
                    if (!isValidVertex(cell))
                        throw new IllegalArgumentException();

                for (var cell : value)
                    matrix.get(key).set(cell, true);

                return prev;
            }

            @Override
            public void clear() {
                matrix.clear();
            }

            @Override
            public Set<Entry<Integer, Set<Integer>>> entrySet() {
                return new AbstractSet<Entry<Integer, Set<Integer>>>() {
                    @Override
                    public Iterator<Entry<Integer, Set<Integer>>> iterator() {
                        return new Iterator<Entry<Integer, Set<Integer>>>() {
                            int index = -1;

                            @Override
                            public boolean hasNext() {
                                return index + 1 < size();
                            }

                            @Override
                            public Entry<Integer, Set<Integer>> next() {
                                if (!hasNext())
                                    throw new NoSuchElementException();
                                index++;
                                return new Entry<Integer, Set<Integer>>() {
                                    @Override
                                    public Integer getKey() {
                                        return index;
                                    }

                                    @Override
                                    public Set<Integer> getValue() {
                                        return get(index);
                                    }

                                    @Override
                                    public Set<Integer> setValue(Set<Integer> value) {
                                        throw new UnsupportedOperationException();
                                    }

                                    @Override
                                    public String toString() {
                                        return getKey() + "=" + getValue();
                                    }

                                    @Override
                                    public boolean equals(Object o) {
                                        if (o == this) return true;
                                        if (!(o instanceof Entry)) return false;
                                        Entry e = (Entry) o;
                                        return Objects.equals(getKey(), e.getKey()) &&
                                                Objects.equals(getValue(), e.getValue());
                                    }
                                };
                            }
                        };
                    }

                    @Override
                    public int size() {
                        return GraphView.this.size();
                    }
                };
            }
        };
    }
}