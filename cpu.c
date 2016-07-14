#include <fcntl.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <resolv.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <tiposDato.h>
#include <log.h>
#include <config.h>
#include <metadata_program.h>
#include <stdio.h>
#include <config.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <pthread.h>
#include <strings.h>
#include <semaphore.h>
#include <signal.h>
#include <collections/list.h>
#include <collections/dictionary.h>

#include <sw_sockets.h>
#include <tiposDato.h>
#include <metadata_program.h>
#include <parser.h>
#include <pthread.h>
#define IP "127.0.0.1"
#include "ParserCpu.h"

#define PUERTO_PARA_CLIENTE 7100

AnSISOP_funciones functions = { .AnSISOP_definirVariable =
		funciones_definirVariable, .AnSISOP_obtenerPosicionVariable =
		funciones_obtenerPosicionVariable, .AnSISOP_dereferenciar =
		funciones_dereferenciar, .AnSISOP_asignar = funciones_asignar,
		.AnSISOP_imprimir = funciones_imprimir, .AnSISOP_imprimirTexto =
				funciones_imprimirTexto, .AnSISOP_obtenerValorCompartida =
				funciones_obtenerValorCompartida,
		.AnSISOP_asignarValorCompartida = funciones_asignarValorCompartida,
		.AnSISOP_irAlLabel = funciones_irAlLabel, .AnSISOP_llamarConRetorno =
				funciones_llamarConRetorno, .AnSISOP_finalizar =
				funciones_finalizar, .AnSISOP_retornar = funciones_retornar,
		.AnSISOP_entradaSalida = funciones_entradaSalida, };
AnSISOP_kernel kernel_functions = { .AnSISOP_wait = kernel_wait,
		.AnSISOP_signal = kernel_signal,

};





char * PUERTO_SERVIDOR= "7100";

int main() {

	nivelDeStack* nivelDeStackAVerificar;
	char *a="a";
	pcbActual.indiceDeStack=list_create();
	nivelDeStack unNivel;
	unNivel.vars=dictionary_create();
	unNivel.retPos=0;
	unNivel.retVar.pagina=0;
	unNivel.retVar.offset=1;
	unNivel.retVar.tamanio=4;
	list_add(pcbActual.indiceDeStack, &unNivel);


	printf("hola1\n");
	int socketListen = crearSocketServidor(PUERTO_SERVIDOR);
	printf("hola2\n");
	struct sockaddr_in addr;
	socklen_t addrlen =sizeof(addr);

	mensaje_UMC_CPU mensajeARecibir;
	int socketCliente = accept(socketListen,(struct sockaddr*)&addr,&addrlen);
//		int socketClienteParaConsola = crearSocketCliente(PUERTO_PARA_CLIENTE);
		printf("hola3\n");

		recibirMensajeUMC_CPU(socketCliente, &mensajeARecibir);

		printf("hola4\n");



		printf("el valor recibido es: %d \n",mensajeARecibir.valor);
			printf("Ejecutando %s\n", mensajeARecibir.texto);
//				analizadorLinea(strdup(mensajeARecibir.texto), &functions,
//					&kernel_functions);
//				printf("================\n");

//			nivelDeStackAVerificar=(nivelDeStack*)list_get(pcbActual.indiceDeStack,0);
//				posicionMemoria* posicionAVerificar=(posicionMemoria*)dictionary_get(nivelDeStackAVerificar->vars,a);
//				printf("el valor de pagina de a es:%d el valor de offset es:%d el valor de el size es: %d \n",posicionAVerificar->pagina,posicionAVerificar->offset,posicionAVerificar->tamanio);



	close(socketListen);

	printf("hola5\n");
	return 0;

}

//void obtenerTamanioDePaignaDeUMC(int socketForUMC) {
//	socketForUMC = crearSocketCliente(PUERTO_UMC);
//	mensaje_CPU_UMC mensajeAMandar;
//	mensajeAMandar.protocolo = INICIAR;
//	int enviado = enviarMensajeCPU_UMC(socketForUMC, mensajeAMandar);
//	mensaje_UMC_CPU mensajeArecibir;
//	int recibido = recibirMensajeUMC_CPU(socketForUMC, mensajeArecibir);
//	tamPag = mensajeArecibir.valor;
//
//}

/*void correrDefinirVariables() {
 printf("Ejecutando '%s'\n", DEFINICION_VARIABLES);
 analizadorLinea(strdup(DEFINICION_VARIABLES), &functions,
 &kernel_functions);
 printf("================\n");
 }

 void correrAsignar() {
 printf("Ejecutando '%s'\n", ASIGNACION);
 analizadorLinea(strdup(ASIGNACION), &functions, &kernel_functions);
 printf("================\n");
 }

 void correrImprimir() {
 printf("Ejecutando '%s'\n", IMPRIMIR);
 analizadorLinea(strdup(IMPRIMIR), &functions, &kernel_functions);
 printf("================\n");
 }

 void correrImprimirTexto() {
 printf("Ejecutando '%s'", IMPRIMIR_TEXTO);
 analizadorLinea(strdup(IMPRIMIR_TEXTO), &functions, &kernel_functions);
 printf("================\n");*/
//}

