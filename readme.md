# CLUSTAR

> For clustering the RNA/DNA sequences.
> 
> This clustering algorithm used in [MACF](https://github.com/malabz/MACF).

## How to use?
1. git clone this repo

    ```bash
    $ git clone https://github.com/Guuhua/CLUSTAR.git
    ```

2. make

    ```bash
    $ cd CLUSTAR
    $ make
    ```

3. run

    ```bash
    $ ./CLUSTAR ./test/rna.fasta ./test/rna.clstr
    ```

clean

```bash
$ make clean
```

## Format

The input filename is required in fasta format.

The output file looks like: (similar to the cdhit's format)

```
>Cluster 0
0      1542nt, >_i1
1      1542nt, >_i2
>Cluster 1
0      1537nt, >958935
1      1534nt, >_i1375678
2      1534nt, >_i1895798
3      1534nt, >_i1895799
4      1534nt, >_i1896969
5      1534nt, >_i1900973
6      1535nt, >_i1900974
7      1535nt, >_i1900975
8      1533nt, >_i1902596
```

## License

CLUSTAR is released under the MIT license. See the file [LICENSE](./LICENSE) for more details.

## Contact

If you have any problems, please email me.(ttscj12@gmail.com)