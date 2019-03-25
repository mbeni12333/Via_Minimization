#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SVGwriter.h"



void SVGinit(SVGwriter *svg, char *nom, int xmin, int ymin, int sizeX, int sizeY) {

  /*Allocation de l'espace*/
  char filename[100];

  strcpy(filename,nom);
  strcat(filename,".svg");

  svg->file=fopen(filename, "w");

  if (svg->file==NULL) {
    printf("Unable to create %s\n",nom);
    exit(1);
  }

  strcpy(svg->lineColor, Red);
  strcpy(svg->pointColor, Black);

  svg->sizeX=sizeX;
  svg->sizeY=sizeY;

  svg->gencol[0]='0';svg->gencol[1]='1';svg->gencol[2]='2';svg->gencol[3]='3';
  svg->gencol[4]='4';svg->gencol[5]='5';svg->gencol[6]='6';svg->gencol[7]='7';
  svg->gencol[8]='8';svg->gencol[9]='9';svg->gencol[10]='A';svg->gencol[11]='B';
  svg->gencol[12]='C';svg->gencol[13]='D';svg->gencol[14]='E';svg->gencol[15]='F';


  fprintf(svg->file,"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\"");
  fprintf(svg->file, " width=\"100%%\" height=\"100%%\"");
  //fprintf(svg->file, " viewBox=\"%d %d %d %d\"", xmin, ymin, sizeX+7, sizeY+7);
  fprintf(svg->file, " preserveAspectRatio=\"yes\">\n");
  fprintf(svg->file, "<script xlink:href=\"svgp.js\"/>\n");
  //fprintf(svg->file, "<defs><circle id=\"c\" cx=\"0.0\" cy=\"0.0\" r=\"3\" stroke=\"#000000\" stroke-width=\"3\" fill=\"#000000\" /></defs>\n");
  fprintf(svg->file, "<style>line{stroke-width:10;stroke-linecap:round ;}</style><g id=\"viewport\">");

   svg->lineColor[0]='#';
}


void SVGlineColor(SVGwriter *svg, char *col) {
  strcpy(svg->lineColor,col);
}

void SVGlineRandColor(SVGwriter *svg){
  int i;
  for (i=1;i<=6;i++) svg->lineColor[i]=svg->gencol[rand()%16];

}

void SVGpointColor(SVGwriter *svg, char *col) {
  strcpy(svg->pointColor,col);
}

void SVGpoint(SVGwriter *svg, double x, double y) {
  //fprintf(svg->file,"<use x=\"%.f\" y=\"%.f\" xlink:href=\"#c\"/>\n",x,y);
}


void SVGline(SVGwriter *svg,double xa,double ya,double xb,double yb) {
  fprintf(svg->file, "<line x1=\"%.f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" />", xa, ya, xb, yb);

}

void SVGgroup(SVGwriter *svg){
  fprintf(svg->file, "<g style=\"stroke:%s;\" >\n", svg->lineColor);;
}
void SVGgroup_end(SVGwriter *svg){
  fprintf(svg->file, "</g>\n");
}

void SVGfinalize(SVGwriter *svg) {
  fprintf(svg->file, "\n\n</g></svg>\n");
  fclose(svg->file);
  svg->file=NULL;
}
