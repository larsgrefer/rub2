#include <stdio.h>
#include <stdlib.h>

void quadrat(float*);

int main()
{
	float seitenlaenge = 3.7;
	printf("Die Seitenlange ist %f\n", seitenlaenge );
	quadrat( &seitenlaenge );
	printf("Das Quadrat ist %f\n", seitenlaenge );
	return EXIT_SUCCESS;
}

void quadrat(float* zahl)
{
	*zahl = *zahl * (*zahl);
}
