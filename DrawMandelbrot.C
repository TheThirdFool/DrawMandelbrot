
// ========================= INCLUDES ========================

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

// ========================= GLOBALS =========================

double pi = 3.14159265359;

// ======================== STRUCTURES =======================

struct Complex{

	// Constructor
	Complex(double a, double b){
		x = a;
		y = b;
	}

	// Null constructor
	Complex(){
		x = 0.0;
		y = 0.0;
	}
	
	// Return magnitude |z|
	double Mag(){
		double temp = pow(x,2.0) + pow(y,2.0);
		double Z = pow(temp,0.5);
		return Z;
	}

	// Print
	void Print(){
		printf("Z = %.2f + %.2f i\n", x,y);
		printf("|Z| = %.4f\n", Mag());
	}

	// Z = x + iy
	double x;
	double y;
};

struct Coord{

	Coord(double lowx, double highx, double lowy, double highy, double step){
		numx = (highx - lowx) / step;
		numy = (highy - lowy) / step;
	
		x = (double*)malloc(numx * numy * sizeof(double));
		y = (double*)malloc(numx * numy * sizeof(double));
		z = (double*)malloc(numx * numy * sizeof(double));

		int xcount = 0;
		int ycount = 0;
		for(double i = lowx; i <= highx; i+=step){
			for(double j = lowy; j <= highy; j+=step){
				x[xcount] = i;
				y[ycount] = j;
				xcount++;
				ycount++;
			}
		}

		total = xcount;
	}

	void FPrint(char * filename){
		printf("Total = %i\n", total);

		FILE * ofile;
		ofile = fopen(filename, "w+");

		for(int i=0; i < total; i++){
			fprintf(ofile,"%f, %f, %f\n", x[i], y[i], z[i]);
			printf("%i / %i\r", i, total);
			fflush(stdout);
		}

		printf("Data printed to '%s'!\n", filename);
		fclose(ofile);
	
	}

	int total;

	double numx;
	double numy;
	double * x;
	double * y;
	double * z;
};

// ======================== FUNCTIONS ========================

Complex Sq(Complex z){
	Complex q;
	q.x = pow(z.x,2.0) - pow(z.y, 2.0);
	q.y = 2.0 * z.x * z.y;
	return q;
}

Complex Add(Complex z, Complex q){
	Complex p = Complex((z.x + q.x), (z.y + q.y));
	return p;
}


double NoIt(Complex z, Complex c, double lim, double max){
	
	double i = 0;
	while(z.Mag() < lim){
		z = Add(Sq(z),c);
//		z.Print();
//		printf("Count = %i\n",i);
		if(i > max) return max;
		i++;
	}

	return i;
}

void GetDataMB(Coord *Data, Complex m, double lim, double max){
	int zcount = 0;
	for(int i=0; i < Data->numx; i++){
		for(int j=0; j < Data->numy; j++){
			Complex c = Complex(Data->x[zcount],Data->y[zcount]);
			Data->z[zcount] = NoIt(m, c, lim, max); // Mandelbrot	
			zcount++;
		}
		printf("%i / %i\r", zcount, Data->total);
		fflush(stdout);
	}

}

void GetDataJ(Coord *Data, Complex m, double lim, double max){
	int zcount = 0;
	for(int i=0; i < Data->numx; i++){
		for(int j=0; j < Data->numy; j++){
			Complex c = Complex(Data->x[zcount],Data->y[zcount]);
			Data->z[zcount] = NoIt(c, m, lim, max);	// Julia
			zcount++;
		}
		printf("%i / %i\r", zcount, Data->total);
		fflush(stdout);
	}

}

void DrawMandelbrot(double xlow, double xhigh, double ylow, double yhigh, double step, double bound, double lim, char* filename){
	Complex z = Complex(0.0, 0.0);
	Coord Data = Coord(xlow, xhigh, ylow, yhigh, step);
	GetDataMB(&Data, z, bound, lim);
	Data.FPrint(filename);
}

void DrawJulia(double xlow, double xhigh, double ylow, double yhigh, double step, double bound, double lim, char* filename){
	Complex z = Complex(-0.8, 0.156);
	Coord Data = Coord(xlow, xhigh, ylow, yhigh, step);
	GetDataJ(&Data, z, bound, lim);
	Data.FPrint(filename);
}

// ========================== MAIN ===========================

int main(int argc, char* argv[]){

	printf("\n");
	printf("Getting Mandelbrot data:\n");

	//DrawMandelbrot(xlow, xhigh, ylow, yhigh, step, bound, lim, filename);
	DrawMandelbrot(-2.0, 1.0, -1.5, 1.5, 0.0075, 2, 200, (char*)"MandelbrotData.txt");
	DrawMandelbrot(-1.0, -0.5, 0.0, 0.5, 0.001, 2, 200, (char*)"Mandelbrot_ValleyData.txt");

	printf("\n");
	printf("Getting Julia data:\n");

	//DrawJulia(xlow, xhigh, ylow, yhigh, step, bound, lim, filename);
	DrawJulia(-2.0, 2.0, -1.5, 1.5, 0.01, 2, 200, (char*)"JuliaData.txt");

	printf("\n");
	printf("Done!\n");
	printf("\n");

	return 0.0;






}


