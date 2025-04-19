# Hubert Jastrzębski | Satori C (Wyszukałem, skompilowałem, uruchomiłem) | 2024-11-18
# https://satori.tcs.uj.edu.pl/contest/9427987/problems/9511313

#!/bin/bash
src_dir=$1
dst=$2

file=$(find ${src_dir} -name "*.c" | head -n 1)  # adres do pliku wejsciowego

(g++ ${file} -o ${dst})  # skompilowanie pliku wejsciowego do wyjsciowego

shift 2  # skipniecie dwoch pierwszych argumentow (src_dir i dst)
"${dst}" "$@"  # wlaczenie programu z przekazaniem stdin i pozostalych argumentow