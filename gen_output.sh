#! /bin/sh
set -e

function single() {
  echo "sh$ time ./vlg $1 data/$2" > "outputs/$1_$2.txt"
  { time ./vlg "$1" "data/$2"; } &>> "outputs/$1_$2.txt"
}

for s in classic center_chain balanced; do
  for d in inet ip p2p; do
    echo "$s $d"
    single $s $d
  done
done
echo "OK"
