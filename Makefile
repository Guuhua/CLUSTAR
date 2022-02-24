CC := gcc
scriptName := staralign

$(scriptName): main.o FastCluster.o CenCluster.o dist.o cstarAlign.o PSA_fmindex.o PSA_kband.o FMindex.o getRank.o BWT.o fasta.o
	$(CC) -o $@ $^
	@echo DONE!

fasta.o: fasta.c fasta.h
	$(CC) -c $<

BWT.o: BWT.c bwt.h
	$(CC) -c $<

getRank.o: getRank.c getRank.h
	$(CC) -c $<

FMindex.o: FMindex.c FMindex.h
	$(CC) -c $<

PSA_kband.o: PSA_kband.c PSA_kband.h
	$(CC) -c $<

PSA_fmindex.o: PSA_fmindex.c PSA_fmindex.h
	$(CC) -c $<

cstarAlign.o: cstarAlign.c cstarAlign.h
	$(CC) -c $<

dist.o: dist.c dist.h
	$(CC) -c $<

CenCluster.o: CenCluster.c CenCluster.h
	$(CC) -c $<

FastCluster.o: FastCluster.c FastCluster.h
	$(CC) -c $<

main.o: main.c
	$(CC) -c $<


.PHONY: clean
clean:
	rm *.o
	rm $(scriptName)
