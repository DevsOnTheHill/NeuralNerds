// 
//

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <random>
#include <stdexcept>
#include <bitset>
#include <math.h>
#ifdef WinOS
#include "glut.h"
#else
#include "glut.h"
#include<GL\GL.h>



#endif
#include<string>
using namespace std;

//Declare decode
double decode(chromo c, bool console);


//Global variables declared here
char* decoded;
bitset<4> gene;
int counter;
double target = 25;
double num;
double val;
double num2;
const int genSize = 10;
bool op = true;
bool number = false;
bool first = true;
bool isType = true;
bool yesNum = false;
bool prevNum = false;
char* function;
char type;
double fitness;
int genNum=0;
int genomeNum=0;
const int totalGens=10;
float mutationChance = 5;
chromo*** genArr = new chromo**[totalGens];
int Button_save_x[2];
int Button_save_y[2];
char Button_save_label[] = {'S','a','v','e','\0'};
char Button_load_label[] = {'L','o','a','d','\0'};
char generation_label[] = {'G','e','n','e','r','a','t','i','o','n',' ','#',':',' ','\0'};
char chromosome_label[] = {'C','h','r','o','m','o','s','o','m','e',' ','#',':',' ','\0'};
char * genome_label;
int Button_load_x[2] = {0,10};
int Button_load_y[2] = {0,10};
int Button_play[2];
bool mouseIsDragging = false;

void draw(int x[], int y[], const char* label){
	glColor3f(255,255,255); // should be white
	glBegin(GL_POLYGON);
		glVertex2d(x[0],y[0]);
		glVertex2d(x[1],y[0]);
		glVertex2d(x[1],y[1]);
		glVertex2d(x[0],y[1]);
	glEnd();
	glRasterPos2f((x[0]+x[1])/2, y[0]+2);
	for (int i = 0; label[i] != '\0'; i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, ((int)label[i]));
	}
};


class genome {
public:
	int id;
	int totalspec=1;
	genome(int i){
		id = i;
		}
};

class chromo {
public:
	bitset<36> data; // We will be switching to strings.  They will take up more memory, but will simplify the design of the genetic algorithms.
	int fitness;
	genome *fam;
	int gid;
	int specid;
	chromo(bitset<36> in) {
		data = in;
	}
	chromo(bitset<36> in, genome *parent){
		data = in;
		fam = parent;
	}


};



int WIDTH = 320;  // width of the user window (640 + 80)
int HEIGHT = 480;  // height of the user window (480 + 60)
char programName[] = "NeuralNet Reporter";

void drawWindow()
{
  // clear the buffer
  glClear(GL_COLOR_BUFFER_BIT);
  draw(Button_load_x,Button_load_y,Button_load_label);
  // draw stuff

  // tell the graphics card that we're done-- go ahead and draw!
  //   (technically, we are switching between two color buffers...)
  glutSwapBuffers();
}

void keyboard( unsigned char c, int x, int y )
{
  int win = glutGetWindow();
  switch(c) {
    case 'q':
    case 'Q':
    case 27:
      // get rid of the window (as part of shutting down)
      glutDestroyWindow(win);
      exit(0);
      break;
    default:
      break;
  }
  glutPostRedisplay();
};

void mouse_motion(int x,int y)
{
  // the mouse button is pressed, and the mouse is moving....
  
  glutPostRedisplay();
  
  
}


void mouse(int button, int state, int x, int y)
{
  if ( GLUT_LEFT_BUTTON == button ) {
    if ( GLUT_DOWN == state ) {
      mouseIsDragging = true;
      // the user just pressed down on the mouse-- do something
    } else {
      // the user just let go the mouse-- do something
      mouseIsDragging = false;
    }
  } else if ( GLUT_RIGHT_BUTTON == button ) {
  }
  glutPostRedisplay();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   WIDTH = w;  HEIGHT = h;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0., WIDTH-1, HEIGHT-1, 0., -1.0, 1.0);
}

void init(void)
{
  // clear the window to black
  glClearColor(0,0,0,1);
  glClear(GL_COLOR_BUFFER_BIT);

  // set up the coordinate system:  number of pixels along x and y
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0., WIDTH-1, HEIGHT-1, 0., -1.0, 1.0);

}
void inherit (chromo *parent,bool mute){
	gid = parent.id;
	if (mute){
		specid = parent->fam.totalspec;
		parent->fam.totalspec++;
	}
}
chromo* cross(chromo** gen){
	int r = (int)(rand()%genSize);
	chromo* a,b;
	a = gen[r];
	int r = (int)(rand()%genSize);
	b = gen[r];
	nbit = bitset<36>;
	r = (int)(rand ()%36);
	/** r will be used here to to take verything in 'a' up
	to r. The difference between chromo lengh and r will then
	be used to get the rest of the chromosome from 'b' 
	Next gen's content should be sufficient to craft this. */
	return a;
}



void init_gl_window()
{
  char *argv[] = {programName};
  int argc = sizeof(argv) / sizeof(argv[0]);
  glutInit(&argc, argv);
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInitWindowPosition(100,100);
  glutCreateWindow(programName);
  init();

  glutDisplayFunc(drawWindow);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutMotionFunc(mouse_motion);
  glutMainLoop();
}

void generate() {
	genArr[genNum] = new chromo*[genSize];
	int a;
	//char *input;
	bitset<36> input;
	//input = new char[39];
	if (genNum<1){
		for (int i = 0; i < genSize; i++) {


			for (int x = 0; x < 36; x++) {

			a = rand() % 2;
				if (a == 1) {
				input.set(x, 1);
				}
				else{
				input.set(x, 0);
				}
			}
		
		genArr[genNum][i] = new chromo(input);
		genArr[genNum][i]->fam = new genome(genomeNum);
		genomeNum++;
		
	}
}
 

	
	genNum++;
}

double selection(double tf, double fts[]){
	if (tf == 0){cout << "Warning: TotalFitness = 0";}
	tf = tf*10000;
	int tff = (int)tf;
	int len;
	for (len=0; fts[len] != '\0'; len++);
	double *ft;
	ft = new double[len];
	for (int i = 0; i<len; i++){
		ft[i] = 10000*fts[i];
	}
	double r = (rand() % tff); // This line is causing a floating point exception core dump
	int selection;
	for (selection = 0; r > 0; selection++){
		r = r - ft[selection];
	}
	return selection;
}

void nextGen(){
	genArr[genNum] = new chromo*[genSize];
 	bool mutate = false;
 	double fits[genSize];
 	double totalfit=0;
 	double odds[genSize];
 	bool crossover = false;
 	int a;
 	bitset<36> input;
 	for (int i = 0; i<genSize; i++){
 		fits[i] = decode(*genArr[genNum-1][i],false);
 		totalfit += fits[i];

	}
	if (totalfit ==0)totalfit=1;
	for (int i =0; i<genSize; i++){
		odds[i] = fits[i]/totalfit; //This results in a weighted mutation probability for each chromosome relative to its fitness value.
	}
	int index  = '\0';
	for(int i =0; i < genSize; i++){
		crossover = (rand () % 100) < crossChance;
		//if (crossover){
		//	cross(genArr[genNum]);
		//}

		index = selection(totalfit, fits);
		cout << "Chosen chromosome #: "<< index <<endl;;
		for(int x =0; x<36; x++){
			mutate = (rand () % 100) < mutationChance;
			if (genArr[genNum-1][index-1]->data[x] == 1){
				input.set(x,1);
			}
			else if(mutate){
				a = rand() % 2;
				cout << "MUTATION!\n";
				if (a == 1) {
					input.set(x, 1);
				}
				else{
					input.set(x, 0);
				}
			}
			else{
				input.set(x,0);
			}
		}
		genArr[genNum][i] = new chromo(input);
	}		
	genNum++;
}




double getNum(char n) {
	switch (n) {
	case'0': num3 = 0; break;
	case'1': num3 = 1; break;
	case'2': num3 = 2; break;
	case'3': num3 = 3; break;
	case'4': num3 = 4; break;
	case'5': num3 = 5; break;
	case'6': num3 = 6; break;
	case'7': num3 = 7; break;
	case'8': num3 = 8; break;
	case'9': num3 = 9; break;
	default: break;
	}
	return num3;

}

//DECODE(chromo)  This function will take a chromo argument and return the fitness value for that chromo
double decode(chromo c, bool console) {

	decoded = new char[10];
	counter = 0;
	fitness = 0;
	for (int i = 0; i < 32; i++) {

		for (int x = 0; x<4; x++) {
			gene.set(x, c.data[x + i]);// = c.data[i];
		}
		if ((i) % 4 == 0 || i == 31) {
			if (gene == (bitset<4>)(string("0000"))) {
				decoded[counter] = '0';
				counter++;
			}
			else if (gene == (bitset<4>)(string("0001"))) {
				decoded[counter] = '1';
				counter++;
			}
			else if (gene == (bitset<4>)(string("0010"))) {
				decoded[counter] = '2';
				counter++;
			}
			else if (gene == (bitset<4>)(string("0011"))) {
				decoded[counter] = '3';
				counter++;
			}
			else if (gene == (bitset<4>)(string("0100"))) {
				decoded[counter] = '4';
				counter++;
			}
			else if (gene == (bitset<4>)(string("0101"))) {
				decoded[counter] = '5';
				counter++;
			}
			else if (gene == (bitset<4>)(string("0110"))) {
				decoded[counter] = '6';
				counter++;
			}
			else if (gene == (bitset<4>)(string("0111"))) {
				decoded[counter] = '7';
				counter++;
			}
			else if (gene == (bitset<4>)(string("1000"))) {
				decoded[counter] = '8';
				counter++;
			}
			else if (gene == (bitset<4>)(string("1001"))) {
				decoded[counter] = '9';
				counter++;
			}
			else if (gene == (bitset<4>)(string("1010"))) {
				decoded[counter] = '+';
				counter++;
			}
			else if (gene == (bitset<4>)(string("1011"))) {
				decoded[counter] = '-';
				counter++;
			}
			else if (gene == (bitset<4>)(string("1100"))) {
				decoded[counter] = '*';
				counter++;
			}
			else if (gene == (bitset<4>)(string("1101"))) {
				decoded[counter] = '/';
				counter++;
			}
			else { //This is serving as our null character in the string if the data is unintelligble.
				decoded[counter] = 'a';
				counter++;
			}
		}





	}


	decoded[9] = '\0';
	val = 0;
	num = 0;
	number = false;
	op = true;
	first = true;
	counter = 0;
	type = 'n';

	for (int i = 0; i < 9; i++) {
		if (type == 'n') {
			switch (decoded[i]) {
			case'0': type = 'o'; counter++; break;
			case'1': type = 'o'; counter++; break;
			case'2': type = 'o'; counter++; break;
			case'3': type = 'o'; counter++; break;
			case'4': type = 'o'; counter++; break;
			case'5': type = 'o'; counter++; break;
			case'6': type = 'o'; counter++; break;
			case'7': type = 'o'; counter++; break;
			case'8': type = 'o'; counter++; break;
			case'9': type = 'o'; counter++; break;
			default: type = 'n'; break;
			}
		}
		else if (type == 'o'&&i != 8) {
			switch (decoded[i]) {
			case'+': type = 'n'; counter++; break;
			case'-': type = 'n'; counter++; break;
			case'*': type = 'n'; counter++; break;
			case'/': type = 'n'; counter++; break;
			default: type = 'o'; break;
			}
		}



	}
	isType = true;
	yesNum = false;
	prevNum = false;
	function = new char[counter + 1];
	function[counter] = '\0';
	counter = 0;
	type = 'n';

	for (int i = 0; i < 9; i++) {
		if (type == 'n') {
			switch (decoded[i]) {
			case'0': type = 'o'; function[counter] = decoded[i]; counter++; break;
			case'1': type = 'o'; function[counter] = decoded[i]; counter++; break;
			case'2': type = 'o'; function[counter] = decoded[i]; counter++; break;
			case'3': type = 'o'; function[counter] = decoded[i]; counter++; break;
			case'4': type = 'o'; function[counter] = decoded[i]; counter++; break;
			case'5': type = 'o'; function[counter] = decoded[i]; counter++; break;
			case'6': type = 'o'; function[counter] = decoded[i]; counter++; break;
			case'7': type = 'o'; function[counter] = decoded[i]; counter++; break;
			case'8': type = 'o'; function[counter] = decoded[i]; counter++; break;
			case'9': type = 'o'; function[counter] = decoded[i]; counter++; break;
			default: type = 'n'; break;
			}
		}
		else if (type == 'o'&&i != 8) {
			switch (decoded[i]) {
			case'+': type = 'n'; function[counter] = decoded[i]; counter++; break;
			case'-': type = 'n'; function[counter] = decoded[i]; counter++; break;
			case'*': type = 'n'; function[counter] = decoded[i]; counter++; break;
			case'/': type = 'n'; function[counter] = decoded[i]; counter++; break;
			default: type = 'o'; break;
			}
		}




	}








	for (int i = 0; i < counter; i++) {
		switch (function[i]) {
		case'+': num2 = getNum(function[i + 1]); val += num2; break;
		case'-': num2 = getNum(function[i + 1]); val -= num2; break;
		case'*': num2 = getNum(function[i + 1]); val *= num2; break;
		case'/': num2 = getNum(function[i + 1]); if (num2 != 0) { val /= num2; }
				 else {} break;
		default:  break;
		}
		if (first) {
			val = getNum(function[i]);
			first = false;
		}

	}



	if (target == val){
		fitness = 1;
	}
	else {
		fitness = (1 / (target - val));
	}

	if (console){
	cout << endl;
	cout << "---------------------------------------------------------" << endl;
	//if (val == target) {
	//	fitness = 1;
	//	cout << "solution found: " << endl;
		
	//}
	//else {
		
		
//	}
	cout << "Chromosome data: " << c.data << endl;
	cout << "characters: " << decoded << endl;
	cout << "function: "<< function << endl;
	cout << "solution: " << val << endl;
	cout << "Fitness: " << fitness << endl;
	cout << "---------------------------------------------------------" << endl;
}


	



	


	delete[] decoded;
	delete[] function;

	return fitness;
}

void decrypt(int currentGen){
	int maxFitness = 0;
	int fit = 0;
	int fitnum;
	chromo *fittest;
	for (int i = 0; i < genSize; i++) {
		fit = decode(*genArr[currentGen][i],true); 		//Note deserved here. Because Decode prints the data, we're getting a ton of values, Want to make this more efficient.
		if (maxFitness < fit) {
			maxFitness = fit;
			fittest = genArr[currentGen][i];
			fitnum = i;

		}
	}

}



int main()
{
	//init_gl_window();
	generate();
	cout << "Generation complete. Decoding..." << endl;

	decrypt(0);
	//bitset<4> test;
	//test.set(1, 1);
	//bitset<4> t2(string("0010"));
	//if (test == (bitset<4>)(string("0010"))) {//I can compare bitsets like this
	//if (test == t2) {
	//	cout << "Success" << endl;
	//}
	//cout << test << endl;
	
	//	if (fit == 1) {
	//		break;
		//}
		//cout << "pass" << endl;
	
	/*  We need a way to check for finding a solution, I don't have perfect understanding of the code yet. */

	// cout << "Solution found";
	// cout << " on try #"<<fitnum;}
	// cout << "Max fitness: " << maxFitness << endl; //changed fitness to maxFitness, allowing for tracking the fittest score
	

	//int l = 0 % 4;
	//cout << l << endl;
	//cout << "pass" << endl;
	int end;
	cin >> end;// This serves as a check to see if the second generation iteration works. If so, it can continue until all memorty is allocated.
	cout << endl<<endl;
	cout << "generation #: "<<genNum;
	cout << endl;
	nextGen();//2nd Gen should start here
	decrypt(1);
	int w=0;
	while (w<totalGens-1){
		cout << "generation #: " << genNum << endl;
		nextGen();
		decrypt(w);
		w++;
	}
	cout << endl  << w;




	//DEALLOCATION.
	for (int i = 0; i < genNum; i++) {
		for (int x = 0; x < genSize; x++) {
			delete genArr[i][x];
		}
		delete genArr[i];
	}
	delete[] genArr;

	
	
	
	
	
	return 0;
}

