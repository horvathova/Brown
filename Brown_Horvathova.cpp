#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <math.h>
#include <fstream>
#include <iostream>


using namespace std;

double RandomGenerator()
{
	return ((double)(rand()) + 1.) / ((double)(RAND_MAX)+1.);
}

double normalne_rozdelenie(double mi, double sigma)
{
	double a = RandomGenerator();
	double b = RandomGenerator();
	return cos(2 * 3.14*b)*sqrt(-2.*log(a))*sigma + mi;
}

int main()
{
	srand(time(NULL));
	int i, j;
	int pocet_trajektorii = 100;
	int pocet_krokov = 20;
	double **t = new double*[pocet_trajektorii];
	int pocet = 0;
	double p;

	std::ofstream subor_vsetky_traj("subor_vsetky_traj"+to_string(pocet_trajektorii)+".dat");
	std::ofstream subor_vyhovujuce_traj("subor_vyhov_traj"+to_string(pocet_trajektorii)+".dat");
	std::ofstream vektor("vektor.dat", std::ofstream::out);
	std::ofstream inkrementy1("inkrementyN_"+to_string(pocet_trajektorii)+".dat", std::ofstream::out);
	std::ofstream inkrementy2("inkrementy_"+ to_string(pocet_trajektorii) + ".dat", std::ofstream::out);


	for (i = 0; i < pocet_trajektorii; i++)
	{
		t[i] = new double[pocet_krokov];
	}

	for (i = 0; i < pocet_trajektorii; i++)
	{
		t[i][0] = 0;
		subor_vsetky_traj << 0 << " " << t[i][0] << endl;
		for (j = 1; j <= pocet_krokov; j++)
		{
			t[i][j] = t[i][j-1] + normalne_rozdelenie(0, 1);
			subor_vsetky_traj << j << " " << t[i][j] << endl;
		}

		subor_vsetky_traj << endl;
		inkrementy1 << t[i][10] << " "<< t[i][5] << endl;

		if ((t[i][10] > 0) && ((-t[i][10] + 2 * t[i][5]) < 0))
		{
			subor_vyhovujuce_traj << 0 << " " << t[i][0] << endl;
			for (j = 1; j <= pocet_krokov; j++)
				{
					subor_vyhovujuce_traj << j << " " << t[i][j] << endl;
				}
			subor_vyhovujuce_traj << endl;

			vektor << "1 " << " " << t[i][5] << endl;
			vektor << "2 " << " " << t[i][10] << endl;
			inkrementy2 << t[i][10] << " " << t[i][5] << endl;
		pocet++;
		}
	}
	p = pocet / (double)pocet_trajektorii;
	printf("Pravdepodobnost(pocet vyhovujucich k poctu vsetkych trajektorii): %lf", pravd);

	subor_vsetky_traj.close();
	subor_vyhovujuce_traj.close();
	vektor.close();

	delete(t);

	getchar();
	return 0;
}
