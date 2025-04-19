# Hubert Jastrzębski | Satori D (Imieniny) | 2024-11-18
# https://satori.tcs.uj.edu.pl/contest/9427987/problems/9579104

#!/bin/bash
imieniny_db=$1
dzien=$2

data=$(grep -E ":${dzien}" "$imieniny_db" | cut -d : -f 1 | sed -E -e "y/ąćęłńóśźżĄĆĘŁŃÓŚŹŻ/acelnoszzACELNOSZZ/")

usernames=""
for name in $data; do
    usernames+="$(getent passwd | grep -E ":${name}" | cut -d: -f1)"
    usernames+=$'\n'
done

echo "$usernames" | sort | sed '/^$/d'