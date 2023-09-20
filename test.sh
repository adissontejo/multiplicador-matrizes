algorithms=("sequencial" "processos" "threads")
sizes=(100 200 400 800 1600 2240)
max=2240
pd=(32 16 8 4 2)
mkdir -p tests
mkdir -p input/tests
for n in ${sizes[@]}
do
    for i in {1..10}
    do
        echo "Gerando matrizes $n x $n, Matriz $i"
        bin/gerador $n $n $n $n $i
        cp -f input/A.txt input/tests/A_${n}_${i}.txt
        cp -f input/B.txt input/tests/B_${n}_${i}.txt
    done
done
for a in ${algorithms[@]}
do
    > tests/${a}_e1.txt
    for n in ${sizes[@]}
    do
        p=$(( $n * $n / 8))
        echo "Tamanho: $n x $n" >> tests/${a}_e1.txt
        avg=0
        for i in {1..10}
        do
            echo "Testando $a (E1): Tamanho $n x $n, Matriz $i"
            cp -f input/tests/A_${n}_${i}.txt input/A.txt
            cp -f input/tests/B_${n}_${i}.txt input/B.txt
            if [ $a = "sequencial" ]
            then
                bin/$a
            else
                bin/$a $p
                bin/formatador $a
            fi
            t=$(grep "segundos" output/$a/saida.txt | sed "s/ segundos//" | tr . ,)
            avg=$(echo "$t $avg" | awk '{printf "%f", $1 + $2}')
            echo "  Matriz $i: $t segundos" >> tests/${a}_e1.txt
        done
        avg=$(echo "$avg" | awk '{printf "%.6f", $1 / 10}')
        echo "  Média: $avg segundos" >> tests/${a}_e1.txt
    done
    if [ $a != "sequencial" ]
    then
        > tests/${a}_e2.txt
        for d in ${pd[@]}
        do
            p=$(( $max * $max / $d ))
            echo "Valor de P: $p" >> tests/${a}_e2.txt
            avg=0
            for i in {1..10}
            do
                echo "Testando $a (E2): Valor de P $p, Matriz $i"
                cp -f input/tests/A_${max}_${i}.txt input/A.txt
                cp -f input/tests/B_${max}_${i}.txt input/B.txt
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
rm -rf input/tests
