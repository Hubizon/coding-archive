/**
 * PO 2024/25, Problem D - Gestosc Zaludnienia
 * 2025-04-02 : https://satori.tcs.uj.edu.pl/contest/9753924/problems/9853121
 * @author Hubert Jastrzębski
 */

import java.util.ArrayList;
import java.util.Collections;
import java.util.Map;
import java.util.TreeMap;

class RestrictedAreaException extends RuntimeException {
    public RestrictedAreaException() {
        super();
    }

    public RestrictedAreaException(String s) {
        super(s);
    }

    public RestrictedAreaException(Throwable throwable) {
        super(throwable);
    }

    public RestrictedAreaException(String s, Throwable throwable) {
        super(s, throwable);
    }
}

class InvalidDensityException extends RuntimeException {
    public InvalidDensityException() {
        super();
    }

    public InvalidDensityException(String s) {
        super(s);
    }

    public InvalidDensityException(Throwable throwable) {
        super(throwable);
    }

    public InvalidDensityException(String s, Throwable throwable) {
        super(s, throwable);
    }
}

public class PopulationDensityAnalyzer {
    private final boolean[][] restrictedAreas;
    private final int[][] densityGrid;

    public PopulationDensityAnalyzer(int[][] densityGrid, boolean[][] restrictedAreas) {
        if (densityGrid == null || restrictedAreas == null || densityGrid[0] == null || restrictedAreas[0] == null ||
                densityGrid.length != restrictedAreas.length || densityGrid[0].length != restrictedAreas[0].length)
            throw new IllegalArgumentException("Grid dimensions mismatch");

        for (int i = 0; i < densityGrid.length; i++)
            if (densityGrid[i] == null || densityGrid[i].length != densityGrid[0].length ||
                    restrictedAreas[i] == null || restrictedAreas[i].length != restrictedAreas[0].length)
                throw new IllegalArgumentException("Grid dimensions mismatch");

        this.restrictedAreas = new boolean[restrictedAreas.length][restrictedAreas[0].length];
        this.densityGrid = new int[densityGrid.length][densityGrid[0].length];
        for (int i = 0; i < densityGrid.length; i++) {
            for (int j = 0; j < densityGrid[0].length; j++) {
                this.restrictedAreas[i][j] = restrictedAreas[i][j];
                this.densityGrid[i][j] = densityGrid[i][j];
            }
        }
    }

    private void checkCoordinates(int x, int y) {
        if (x < 0 || x >= densityGrid.length || y < 0 || y >= densityGrid[0].length)
            throw new IllegalArgumentException(String.format("Coordinates (%d,%d) out of bounds. Grid size: %dx%d",
                    x, y, densityGrid.length, densityGrid[0].length));
    }

    private void checkBoxCoordinates(int x1, int y1, int x2, int y2) {
        checkCoordinates(x1, y1);
        checkCoordinates(x2, y2);

        if (x1 > x2 || y1 > y2)
            throw new IllegalArgumentException(String.format("Invalid area coordinates: (%d,%d) to (%d,%d)", x1, y1, x2, y2));
    }

    public void updateDensity(int x, int y, int newValue) {
        checkCoordinates(x, y);
        if (restrictedAreas[x][y])
            throw new RestrictedAreaException(String.format("Cannot update restricted area at (%d,%d)", x, y));
        if (newValue < 0 || newValue > 10000)
            throw new InvalidDensityException(String.format("Density must be 0-10000. Got: %d", newValue));

        densityGrid[x][y] = newValue;
    }

    public Map<Integer, Integer> getHistogram(int x1, int y1, int x2, int y2) {
        checkBoxCoordinates(x1, y1, x2, y2);

        Map<Integer, Integer> histogram = new TreeMap<>();
        for (int x = x1; x <= x2; x++) {
            for (int y = y1; y <= y2; y++) {
                if (!restrictedAreas[x][y]) {
                    var density = densityGrid[x][y];
                    histogram.put(density, histogram.getOrDefault(densityGrid[x][y], 0) + 1);
                }
            }
        }

        return histogram;
    }

    public double getMedian(int x1, int y1, int x2, int y2) {
        checkBoxCoordinates(x1, y1, x2, y2);

        ArrayList<Integer> medianList = new ArrayList<>();
        for (int x = x1; x <= x2; x++) {
            for (int y = y1; y <= y2; y++) {
                if (!restrictedAreas[x][y])
                    medianList.add(densityGrid[x][y]);
            }
        }

        if (medianList.isEmpty())
           return 0; // ?

        Collections.sort(medianList);
        if (medianList.size() % 2 == 0)
            return (medianList.get(medianList.size() / 2 - 1) + medianList.get(medianList.size() / 2)) / 2.0;
        else
            return medianList.get(medianList.size() / 2);
    }
}