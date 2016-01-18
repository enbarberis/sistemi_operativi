#!/usr/bin/awk -f

BEGIN{

vettore["casa"]="house";
vettore["gatto"]="cat";
vettore["topo"]="mouse";

for (i in vettore)
{
	printf("vettore[%s] = %s\n", i, vettore[i]);
}

}
