EXEC= VisuNetlist tests_elementaires
all: $(EXEC)
CFLAGS= -Wall -g

# les differents structs
cell_segment.o: cell_segment.c cell_segment.h segment.h
	gcc $(CFLAGS) -c cell_segment.c
point.o: point.c point.h cell_segment.h
	gcc $(CFLAGS) -c point.c
segment.o: segment.c segment.h cell_segment.h
	gcc $(CFLAGS) -c segment.c
reseau.o: reseau.c reseau.h point.h
	gcc $(CFLAGS) -c reseau.c
netlist.o: netlist.c netlist.h
	gcc $(CFLAGS) -c netlist.c
VisuNetlist.o: VisuNetlist.c SVGwriter.h
	gcc $(CFLAGS) -c VisuNetlist.c
tests_elementaires.o: tests_elementaires.c netlist.h
	gcc $(CFLAGS) -c tests_elementaires.c 
# fonction helper
entree_sortie.o: entree_sortie.c entree_sortie.h
	gcc $(CFLAGS) -c entree_sortie.c
SVGwriter.o: SVGwriter.c SVGwriter.h
	gcc $(CFLAGS) -c SVGwriter.c


# les executables
VisuNetlist: VisuNetlist.o cell_segment.o point.o segment.o reseau.o netlist.o SVGwriter.o entree_sortie.o
	gcc $(CFLAGS) -o VisuNetlist VisuNetlist.o cell_segment.o point.o segment.o reseau.o netlist.o SVGwriter.o entree_sortie.o
tests_elementaires: tests_elementaires.o cell_segment.o point.o segment.o reseau.o netlist.o  entree_sortie.o
	gcc $(CFLAGS) -o tests_elemenaites tests_elementaires.o cell_segment.o point.o segment.o reseau.o netlist.o SVGwriter.o entree_sortie.o


clean:
	rm -rf *.o
	rm $(EXEC)
