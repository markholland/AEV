
#include <nds.h>
#include <stdio.h>

//#include <input.h>


int teclaA=0;
int teclaB=0;
int teclaL=0;
int pantallaC=0;
int pantallaA=0;

void logica(){

	// scanKeys(); //actualizamos los botones pulsadas

	// //miramos si alguna tecla está pulsada
	// if (keysHeld()) {
	// 	iprintf("\x1b[3;1HAlgun boton esta pulsado"); 
	// }
	// else {
	// 	iprintf("\x1b[3;1HNingun boton esta pulsado");
	// }
	
	// //si la tecla A está presionada (mediante repeticiones) se incrementa
	// if (KEY_A & keysDownRepeat()) {
	// 	teclaA++; 
	// }

	// if (KEY_B & keysDown()) {
	// 	teclaB++; 
	// }

	// //miramos si cerramos la táctil
	// if (KEY_LID & keysDown()) {
	// 	pantallaC++; 
	// }

	// //miramos si abrimos la táctil
	// if (KEY_LID & keysUp()) {
	// 	pantallaA++; 
	// }

	// //cuenta las veces que se presiona B
	// if (KEY_L & keysUp()) {
	// 	teclaL++;
	// }
	
	// //si hay presión sobre la táctil entonces miramos las coordenadas. 
	// //Para una selección quizás mejor keysDown touchPosition touch=touchReadXY();
	// if (KEY_TOUCH & keysHeld()) {   
	// 	iprintf("\x1b[1;1HTactil X %d, Y %d ",touch.px, touch.py);
	// }

	// iprintf("\x1b[4;1HEl boton A se ha pulsado %d",teclaA);
	// iprintf("\x1b[5;1HEl boton B se ha pulsado %d",teclaB);
	// iprintf("\x1b[6;1HEl boton L se ha levantado %d",teclaL);
	// iprintf("\x1b[8;1HPantalla cerrada %d",pantallaC);
	// iprintf("\x1b[9;1HPantalla abierta %d",pantallaA);
};