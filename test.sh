algorithms=("sequencial" "processos" "threads")
sizes=(100 200 400 800 1600 3200)
pd=(32 16 8 4 2)
mkdir -p tests
mkdir -p input/A
mkdir -p input/B
for n in ${sizes[@]}
do
    for i in {1..10}
    do
        bin/gerador $n $n $n $n $i
        cp -f input/A.txt input/A/A_${n}_${i}.txt
        cp -f input/B.txt input/B/B_${n}_${i}.txt
    done
done
for a in ${algorithms[@]}
do
    > tests/${a}_e1.txt
    > tests/${a}_e2.txt
    for n in ${sizes[@]}
    do
        p=$(( $n * $n / 8))
        echo "Tamanho: $n x $n" >> tests/${a}_e1.txt
        avg=0
        for i in {1..10}
        do
            cp -f input/A/A_${n}_${i}.txt input/A.txt
            cp -f input/B/B_${n}_${i}.txt input/B.txt
            if [ $a = "sequencial" ]
            then
                bin/$a
            else
                bin/$a $p
                bin/formatador $a
            fi
            t=$(grep "segundos" output/$a/saida.txt | sed "s/segundos//" | tr . ,)
            avg=$(echo "$t $avg" | awk '{printf "%f", $1 + $2}')
            echo "  Matriz $i: $t segundos" >> tests/${a}_e1.txt
        done
        avg=$(echo "$avg" | awk '{printf "%.6f", $1 / 10}')
        echo "  Média: $avg segundos" >> tests/${a}_e1.txt
    done
    if [ $a != "sequencial" ]
    then
        for d in ${pd[@]}
        do
            p=$(( 3200 * 3200 / $d ))
            echo "Valor de P: $p" >> tests/${a}_e2.txt
            avg=0
            for i in {1..10}
            do
                cp -f input/A/A_3200_${i}.txt input/A.txt
                cp -f input/B/B_3200_${i}.txt input/B.txt
                bin/$a $p
                bin/formatador $a
                t=$(grep "segundos" output/$a/saida.txt | sed "s/segundos//" | tr . ,)
                avg=$(echo "$t $avg" | awk '{printf "%f", $1 + $2}')
                echo "  Matriz $i: $t segundos" >> tests/${a}_e2.txt
            done
            avg=$(echo "$avg" | awk '{printf "%.6f", $1 / 10}')
            echo "  Média: $avg segundos" >> tests/${a}_e2.txt
        done
    fi
done
rm -rf input/A
rm -rf input/B
