#!/bin/bash

run=../bin/a10

suffix=$1

prefix=../tests/a10_

if [ ! -x $run ]
then
  echo "Error - cannot run '$run' (bad command or filename)"
  exit
fi

numTests=`ls ${prefix}testInput*$suffix.txt | wc -w`

for i in `seq 1 $numTests`
do
  if [ ! -f ${prefix}testInput$i$suffix.txt ]
  then
    echo "Error - cannot open ${prefix}testInput$i$suffix.txt"
    exit
  fi

  for j in {h,m,l}
  do
    if [ ! -f ${prefix}correctOutput$i${suffix}$j.txt ]
    then
      echo "Error - cannot open ${prefix}correctOutput$i${suffix}$j.txt"
      exit
    fi

    ./$run ${prefix}testInput$i$suffix.txt $j > ${prefix}testOutput$i${suffix}${j}.txt
    if diff ${prefix}testOutput$i${suffix}${j}.txt ${prefix}correctOutput$i${suffix}${j}.txt > /dev/null
    then
      echo Test $i$j passed
      rm ${prefix}testOutput$i$suffix$j.txt
    else
      echo ***Test $i$j failed! See ${prefix}diff$i$suffix$j$.txt for differences
      diff ${prefix}testOutput$i$suffix$j.txt ${prefix}correctOutput$i$suffix$j.txt > ${prefix}diff$i$suffix$j.txt
    fi
  done
done

