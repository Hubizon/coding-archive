# Hubert Jastrzębski | Satori B (Prosty program strumieniowy - wersja BASH) | 2024-11-09
# https://satori.tcs.uj.edu.pl/contest/9427987/problems/9511287

#!/bin/bash
res=0

for x in $@; do
      res=$((res + x))
done

while read x; do
    res=$((res + x))
done

echo "${res}"