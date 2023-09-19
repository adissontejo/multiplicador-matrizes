# Multiplicador de Matrizes

Esse projeto tem o objetivo de implementar a operação de multiplicação entre duas matrizes utilizando diferentes soluções, sendo essas um algoritmo sequencial, um algoritmo paralelo utilizando processos e um algoritmo paralelo utilizando threads.

- [Tecnologia utilizada](#tecnologia-utilizada)
- [Estrutura de pastas](#estrutura-de-pastas)
- [Executando o projeto](#executando-o-projeto)

## Tecnologia utilizada

- [Linguagem C](https://en.cppreference.com/w/c)

## Estrutura de pastas

- Pasta raíz

  Contém pastas do projeto e o arquivo makefile para compilação do projeto.

  - /bin

    Pasta temporária que contém os arquivos executáveis para realizar a multiplicação de matrizes

  - /input

    Pasta que contém os arquivos com as matrizes a serem lidas durante a execução dos algoritmos.

  - /output

    Pasta que contém os arquivos de saída dos algoritmos executados, organizados em pastas com os nomes dos algoritmos referentes.

  - /src

    Pasta onde se concentra o código do projeto e todos os arquivos .cpp.

## Executando o projeto

Para executar o projeto, deve-se compilar todos os códigos e gerar seus respectivos executáveis na pasta /bin através do makefile:

```bash
make
```

Após isso, deve-se utilizar o gerador de matrizes para gerar duas matrizes A e B nos arquivos da pasta /input

```bash
bin/gerador <numero_de_linhas_A> <numero_de_colunas_A> <numero_de_linhas_B> <numero_de_colunas_B>
```

Depois, deve-se executar os três programas referentes à multiplicação de matrizes, informando o número de elementos por processo/thread para os programas que executam a multiplicação paralelamente.

```bash
bin/sequencial
```

```bash
bin/processos <numero_de_elementos_por_processo>
```

```bash
bin/threads <numero_de_elementos_por_thread>
```

Por fim, para facilitar a leitura do resultado, deve-se executar o programa formatador, que juntará os diferentes arquivos de saída dos algoritmos paralelos em um único arquivo, selecionando o maior tempo entre eles.

```bash
bin/formatador
```

Todos os arquivos de resultado se encontram na pasta /output, dentro da pasta referente ao nome do algoritmo, com o nome de "saida.txt".
