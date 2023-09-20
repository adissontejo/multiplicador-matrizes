mkdir -p tests
for a in "sequencial" "processos" "threads"
do
    > tests/$a.txt
done
for (( n=100; n<=800; n*=2 ))
do
    p=$(( $n * $n / 8))
    if (( $n % 8 != 0 ))
    then
        p=$(( $p + 1 ))
    fi
    for a in "sequencial" "processos" "threads"
    do
        echo "Tamanho: $n x $n" >> tests/$a.txt
    done
    for i in {1..10}
    do
        bin/gerador $n $n $n $n
        for a in "sequencial" "processos" "threads"
        do
            if [ $a = "sequencial" ]
            then
                bin/$a
            else
                bin/$a $p
                bin/formatador $a
            fi
            echo "  Matriz $i: $(grep "segundos" output/$a/saida.txt | tr . ,)" >> tests/$a.txt
        done
    done
done
