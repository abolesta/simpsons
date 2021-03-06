#include <iostream>
#include <string>
#include <time.h>

static int randx = 0;

int srandinter();
int randinter(float a, float b);
int episodeGen(int c);
void print(int d, int e);
int check();
double ran2(int *idum);

int main(){
	int t = 2;
	srandinter();

	while (t == 2){
		int seasonNum = randinter(1, 27);			/* generate season suggestion */
		int episodeNum = episodeGen(seasonNum);     /* generate episode suggestion */
		print(seasonNum, episodeNum);				/* print results to screen */
		t = check();								/* prompt user to repeat process */
		srandinter();								/* generate new seed */
	}

	std::cin.get();
	std::cin.get();
	return 0;
}

int srandinter(){	/* initialize the random number generator */
	int seed = (int)time(NULL);	/* initialize from the system
								clock if seed = 0 */
	randx = -abs(seed);
	return seed;		/* return seed in case we need to repeat */
}

int randinter(float a, float b){	/* return a random number uniformly
									distributed between a and b */
	if (randx == 0) srandinter();
	return int(a + (b - a)*((float)ran2(&randx)));
}

int episodeGen(int c){    /* set bounds of episode number generated based on
						  the number of episodes in the season chosen via
						  seasonNum */
	int episode;
	if (c == 1) episode = randinter(1, 13);
	else if (c == 2 || 4 || 5 || 11 || 13 || 14 || 15 || 17 || 18 || 22 || 23 || 24 || 25 || 26 || 27) episode = randinter(1, 22);
	else if (c == 3) episode = randinter(1, 24);
	else if (c == 6 || 7 || 8 || 9) episode = randinter(1, 25);
	else if (c == 10 || 21) episode = randinter(1, 23);
	else if (c == 12 || 16 || 20) episode = randinter(1, 21);
	else if (c == 19) episode = randinter(1, 20);

	return episode;
}

void print(int d, int e){	/* prints episode suggestion based on random seed */
	std::cout << "\nYou should watch:\n" << "\nSeason: " << d << "\nEpisode: " << e << std::endl << std::endl;
}

int check(){	/* decides whether to roll again based on user input
				complete with Simpsons references for the well-
				informed*/
	std::string answer;

	std::cout << "\nBall is in ... Parking lot. Would you like to play again? \n";    /* see episode 3F07 "Marge Be Not Proud" */
	std::cin >> answer;

	if (answer == "yes"){
		std::cout << "\nWatching prevents explosion\n";    /* see episode 3F05 "King-Size Homer" */
		return 2;
	}

	else if (answer == "y"){
		std::cout << "\nYou've just tripled your efficiency!\n";	/* see episode 3F05 "King-Size Homer" */
		return 2;
	}

	else if (answer == "no" || answer == "n"){
		std::cout << "\nYou have selected 'No'.\n";    /* see episode 3F07 "Marge Be Not Proud" */
		return 1;
	}

	else{
		std::cout << "\nWhat the hell are you talking about?\n";	/* see episode 4F12 "The Itchy & Scratchy & Poochie Show" */
		return 2;
	}
}

//random number generator

#define IM1 2147483563
#define IM2 2147483399
#define AM (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS 1.e-14
#define RNMX (1.0-EPS)

double ran2(int *idum){
	int j;
	int k;
	static int idum2 = 123456789;
	static int iy = 0;
	static int iv[NTAB];
	double temp;

	if (*idum <= 0) {		// *idum < 0 ==> initialize
		if (-(*idum) < 1)
			*idum = 1;
		else
			*idum = -(*idum);
		idum2 = (*idum);

		for (j = NTAB + 7; j >= 0; j--) {
			k = (*idum) / IQ1;
			*idum = IA1*(*idum - k*IQ1) - k*IR1;
			if (*idum < 0) *idum += IM1;
			if (j < NTAB) iv[j] = *idum;
		}
		iy = iv[0];
	}
	k = (*idum) / IQ1;
	*idum = IA1*(*idum - k*IQ1) - k*IR1;
	if (*idum < 0) *idum += IM1;

	k = idum2 / IQ2;
	idum2 = IA2*(idum2 - k*IQ2) - k*IR2;
	if (idum2 < 0) idum2 += IM2;

	j = iy / NDIV;
	iy = iv[j] - idum2;
	iv[j] = *idum;
	if (iy < 1) iy += IMM1;

	if ((temp = AM*iy) > RNMX)
		return RNMX;
	else
		return temp;
}

#undef IM1
#undef IM2
#undef AM
#undef IMM1
#undef IA1
#undef IA2
#undef IQ1
#undef IQ2
#undef IR1
#undef IR2
#undef NTAB
#undef NDIV
#undef EPS
#undef RNMX