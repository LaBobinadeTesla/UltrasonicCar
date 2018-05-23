// ---------------------------------------------------------------------------
// 		   Control de carro por medio de sensor Ultrasonico HC- SR04
//
// Autor:
// Created by Daniel Polanco - Jdanypa@gmail.com
// Github:   https://github.com/Elemeants
//
// Links:
// Facebook: https://www.facebook.com/LaBobinaDeTesla
// Github:   https://github.com/LaBobinadeTesla
// Correo: 	 BobinadeTesla8981@gmail.com
//
// Proposito:
// Este codigo esta hecho para manejar un carrito por medio de un sensor 
// ultrasonico 'HC-SR04' el cual al detectar un obstaculo gira a un lado
// de forma autonoma
//
// Conexiones:		  Arduino      Arduino     Arduino
// 						UNO		/	NANO	/	MEGA
// Motor 1 - Adelante    4			 4 			 40	
// Motor 1 - Atras		 5			 5			 41
// Motor 2 - Adelante 	 6			 6			 42
// Motor 2 - Atras		 7			 7			 43
// HC-SR04 - Echo		 2			 2			 38
// HC-SR04 - Trigger	 3			 3 			 39
// 
// Instrucciones:
//	  - Si ocupa usar otros pines los puedes cambiar en el bloque de constantes
//	  - Puedes cambiar la distancia maxima mediante la variable 'DistanciaMaxima'
//	  - Puedes calibrar el tiempo de giro con la variable 'TiempoGiro' la cual 
//	    esta en milisegundos.
//	  - Puedes configurar el giro cambiando los valores 'Derecha' e 'Izquierda'
//		Intercambiandolos.
//	  - El robot por defecto ira hacia adelante hasta que encuentre un obstaculo
//		iniciara la rutina de Derecha -> Atras -> Izquierda hasta que encuentre
//		un camino valido.
//
// Material necesario:
// 	- Sensor Ultrasonico HC-SR04
// 	- Cualquier placa Arduino
//	- Puente H (Para el control de los motores)
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// Se definen los lados a los cuales puede girar el robot
// ---------------------------------------------------------------------------
#define Derecha   0
#define Izquierda 1
#define Atras     2

// ---------------------------------------------------------------------------
// Variables de los pines a conectar
// ---------------------------------------------------------------------------
const int Motor1Adelante   = 4;
const int Motor1Atras 	   = 5;
const int Motor2Adelante   = 6;
const int Motor2Atras 	   = 7;
const int UltrasonicoECHO  = 2;
const int UltrasonicoTrigg = 3;
// Constante que define los centimetros a los cuales detecta el obstaculo
const int DistanciaMaxima  = 5;
// Constante de tiempo de giro para 90 grados
const int TiempoGiro 	   = 400;

// Prototipo de la funcion de girar
void Girar(int);
// Prototipo de la funcion del ultrasonico
int DistanciaUltrasonico();

void setup()
{
	// Definicion de las salidas y entradas
	pinMode(Motor1Adelante,   OUTPUT);	// Salidas
	pinMode(Motor1Atras, 	  OUTPUT);
	pinMode(Motor2Adelante,   OUTPUT);
	pinMode(Motor2Atras, 	  OUTPUT);
	pinMode(UltrasonicoTrigg, OUTPUT);
	pinMode(UltrasonicoECHO,  INPUT);	// Entrada
}

// Ciclo repetitivo del programa
void loop()
{
	// Ejecuta la funcion 'DistanciaUltrasonico'
	// Si la distacia en centimetros es menor a la distancia maxima
	if(DistanciaUltrasonico() < DistanciaMaxima){
		// Ejecuta la funcion Girar, la cual va a la derecha
 	    Girar(Derecha);
 	    // Si al Girar vuelve a encontrar un obstaculo
 	    if(DistanciaUltrasonico() < DistanciaMaxima){
 	    	// Gira 180° al Carro
 	        Girar(Atras);
 	        // Si vuelve a encontrar otro obstaculo (Osea esta encerrado)
 	        if(DistanciaUltrasonico() < DistanciaMaxima){
 	        	// Gira a la Izquierda (Osea de regreso por donde venia)
 	            Girar(Izquierda);
 	        }
 	    }
 	}
	// Se coloca al carro para que ambos motores vayan hacia adelante
	digitalWrite(Motor1Adelante, HIGH); // Prendido
	digitalWrite(Motor1Atras, 	 LOW);  // Apagado
	digitalWrite(Motor2Adelante, HIGH); // Prendido
 	digitalWrite(Motor2Atras,  	 LOW);  // Apagado
}

// Esta funcion permite leer el valor del ultrasonido y regresa un valor entero
// en forma de centimetros
int DistanciaUltrasonico()
{ 
	digitalWrite(UltrasonicoTrigg, LOW);	// Apaga el ultrasonico
	delayMicroseconds(2); 					// Espera 2 microsegundos
	digitalWrite(UltrasonicoTrigg, HIGH);	// Prende el ultrasonico
	delayMicroseconds(10);					// Espera 10 microsegundos
	digitalWrite(UltrasonicoTrigg, LOW);	// Lo vuelve a apagar
	// Lee el tiempo que tarda en responder el ultrasonido
	int TiempoRespuesta = pulseIn(UltrasonicoECHO, HIGH);
	// Divide el tiempo que tardo en responder en 58 y luego lo retorna
	// convertido en centimetros
	return TiempoRespuesta / 58; 
}

// Funcion que permite girar el robot a la Izquierda, Derecha o Atras
// Recibe 0 -> Derecha, 1 -> Izquierda, 2 -> Atras
void Girar(int Giro)
{
	// Si Giro es a la izquierda
	if(Giro == Izquierda)
	{
		// Hace que el motor 1 gire para atras 
		digitalWrite(Motor1Adelante, LOW);
		digitalWrite(Motor1Atras, 	 HIGH);
		// Hace que el motor 2 gire para adelante 
		digitalWrite(Motor2Adelante, HIGH);
	 	digitalWrite(Motor2Atras,  	 LOW);
		delay(TiempoGiro);		// Espera hasta que gire los 90°
	}
	// Si Giro es a la izquierda
	if(Giro == Derecha)
	{
		// Hace que el motor 1 gire para adelante 
		digitalWrite(Motor1Adelante, HIGH);
		digitalWrite(Motor1Atras, 	 LOW);
		// Hace que el motor 2 gire para atras 
		digitalWrite(Motor2Adelante, LOW);
	 	digitalWrite(Motor2Atras,  	 HIGH);
		delay(TiempoGiro);		// Espera hasta que gire los 90°
	}
	// Si Giro es a la izquierda
	if(Giro == Atras)
	{
		// Hace que el motor 1 gire para adelante 
		digitalWrite(Motor1Adelante, HIGH);
		digitalWrite(Motor1Atras, 	 LOW);
		// Hace que el motor 2 gire para atras 
		digitalWrite(Motor2Adelante, LOW);
	 	digitalWrite(Motor2Atras,  	 HIGH);
		delay(TiempoGiro * 2);		// Espera hasta que gire los 180°
	}
}