EXEC= VisuNetlist tests_elementaires test_echeancier test_arbre test_graph
all: $(EXEC)
CFLAGS= -Wall -g

# les differents structs
cell_segment.o: cell_segment.c cell_segment.h segment.h
	gcc $(CFLAGS) -c cell_segment.c
point.o: point.c point.h cell_segment.h
	gcc $(CFLAGS) -c point.c
segment.o: segment.c segment.h cell_segment.h
	gcc $(CFLAGS) -c segment.c
reseau.o: reseau.c reseau.h structs.h point.h
	gcc $(CFLAGS) -c reseau.c
netlist.o: netlist.c netlist.h structs.h cell_segment.h segment.h
	gcc $(CFLAGS) -c netlist.c
VisuNetlist.o: VisuNetlist.c structs.h
	gcc $(CFLAGS) -c VisuNetlist.c
tests_elementaires.o: tests_elementaires.c netlist.h
	gcc $(CFLAGS) -c tests_elementaires.c
tests_echeacier.o: tests_echeanciers.c netlist.h
	gcc $(CFLAGS) -c tests_elementaires.c
echeancier.o: echeancier.c echeancier.h
	gcc $(CFLAGS) -c echeancier.c
graph.o: graph.c graph.h
	gcc $(CFLAGS) -c graph.c
detect_intersection.o: detect_intersection.c detect_intersection.h
	gcc $(CFLAGS) -c detect_intersection.c
test_graph.o: test_graph.c
	gcc $(CFLAGS) -c test_graph.c
# fonction helper
entree_sortie.o: entree_sortie.c entree_sortie.h
	gcc $(CFLAGS) -c entree_sortie.c

SVGwriter.o: SVGwriter.c SVGwriter.h
	gcc $(CFLAGS) -c SVGwriter.c
AVL.o: AVL.c AVL.h
	gcc $(CFLAGS) -c AVL.c
test_arbre.o: test_arbre.c
	gcc $(CFLAGS) -c test_arbre.c
# les executables
VisuNetlist: VisuNetlist.o cell_segment.o point.o segment.o reseau.o netlist.o SVGwriter.o entree_sortie.o graph.o
	gcc $(CFLAGS) -o VisuNetlist VisuNetlist.o cell_segment.o point.o segment.o reseau.o netlist.o SVGwriter.o entree_sortie.o graph.o

tests_elementaires: tests_elementaires.o cell_segment.o point.o segment.o reseau.o netlist.o  entree_sortie.o detect_intersection.o
	gcc $(CFLAGS) -o tests_elementaires tests_elementaires.o cell_segment.o point.o segment.o reseau.o netlist.o  entree_sortie.o SVGwriter.o detect_intersection.o
test_arbre: test_arbre.o cell_segment.o point.o segment.o reseau.o netlist.o  entree_sortie.o detect_intersection.o AVL.o
	gcc $(CFLAGS) -o test_arbre test_arbre.o cell_segment.o point.o segment.o reseau.o netlist.o  entree_sortie.o SVGwriter.o detect_intersection.o AVL.o
test_echeancier: test_echeancier.o cell_segment.o point.o segment.o reseau.o netlist.o  entree_sortie.o echeancier.o AVL.o detect_intersection.o
	gcc $(CFLAGS) -o test_echeancier test_echeancier.o cell_segment.o point.o segment.o reseau.o netlist.o  entree_sortie.o SVGwriter.o echeancier.o AVL.o detect_intersection.o
test_graph: test_graph.o cell_segment.o point.o segment.o reseau.o netlist.o  entree_sortie.o echeancier.o AVL.o detect_intersection.o graph.o
	gcc $(CFLAGS) -o test_graph test_graph.o cell_segment.o point.o segment.o reseau.o netlist.o  entree_sortie.o SVGwriter.o echeancier.o AVL.o detect_intersection.o graph.o
clean:
	rm -rf *.o
	rm $(EXEC)
