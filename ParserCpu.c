#include "ParserCpu.h"
#include <collections/list.h>
#include <tiposDato.h>
#include <metadata_program.h>
#include <sw_sockets.h>
#include <stdio.h>
#define IP "127.0.0.1"
#define PUERTO_NUCLEO 7000
#define PUERTO_UMC 7100
/////
//extern pcb pcbActual;
t_puntero funciones_definirVariable(t_nombre_variable variable) {
	nivelDeStack* letraAAgregar;

						posicionMemoria* unaPosicion=malloc(sizeof(posicionMemoria));

						//if(dictionary_is_empty(datoAAsignar->nivelDeStack->vars))
						if(list_size(pcbActual.indiceDeStack)==1){
							letraAAgregar=(nivelDeStack*) list_get(pcbActual.indiceDeStack,0);
						if (dictionary_size(letraAAgregar->vars)==0) {



							unaPosicion->pagina= 0;
							unaPosicion->offset =dictionary_size(letraAAgregar->vars)*4;// aca a lo ultimo es *4(+4 fue para probar);
							unaPosicion->tamanio=4;
							dictionary_put(letraAAgregar->vars,charToString(variable),(void*) unaPosicion);

						} else {

							int tam = dictionary_size(letraAAgregar->vars);
							int desplazamiento = tam * 4;
									unaPosicion->pagina=0;
									unaPosicion->offset =desplazamiento;
									unaPosicion->tamanio=4;
							dictionary_put(letraAAgregar->vars,charToString(variable),
									(void*) unaPosicion);


						}
						}else{
							int tamanio=list_size(pcbActual.indiceDeStack);
							letraAAgregar= list_get(pcbActual.indiceDeStack,tamanio-2);
							int tam = dictionary_size(letraAAgregar->vars);
								int desplazamiento = tam * 4;
										unaPosicion->pagina=0;
										unaPosicion->offset =desplazamiento;
										unaPosicion->tamanio=4;
								dictionary_put(letraAAgregar->vars,charToString(variable),
										(void*) unaPosicion);

						}




					return unaPosicion->offset;
					printf("soy definirVariable\n de:%c",variable);

	}


// pedir a la umc el valor retorna la poscicion
t_puntero funciones_obtenerPosicionVariable(t_nombre_variable variable) {
//	nivelDeStack* letraAEncontrar;
//	posicionMemoria* variableABuscar;
//
//	int j = 0;
//	int i = 0;
//	while (j == 0) {
//
//		letraAEncontrar = (nivelDeStack*) list_get(pcbActual.indiceDeStack, i);
//		if (dictionary_has_key(letraAEncontrar->vars, charToString(variable))) {
//			posicionMemoria* resultado = (posicionMemoria*) dictionary_get(
//					letraAEncontrar->vars, charToString(variable));
//
//			variableABuscar = resultado;
//			j = 1;
//			printf("encontro el valor\n");
//
//		} else {
//			i++; // aca en realidad va i++;
//			printf("no encuentra nada\n");
//		}
//
//	}
	printf("sot obtenerPosicionVariable el valor es: %c \n", variable);
//	return variableABuscar->offset;
}

t_valor_variable funciones_dereferenciar(t_puntero puntero) {
//	mensaje_CPU_UMC mensajeAEnviar;
//	mensaje_UMC_CPU mensajeARecibir;
//	int socketClienteParaUmc = crearSocketCliente(PUERTO_UMC);
//	mensajeAEnviar.protocolo = LEERVARIABLE;
//	mensajeAEnviar.offset = devuelveOffset(puntero, tamPag);
//	mensajeAEnviar.pagina = devuelvePagina(puntero, tamPag);
//	mensajeAEnviar.pid = pcbActual.identificador;
//	mensajeAEnviar.tamanio = 4;
//	enviarMensajeCPU_UMC(socketClienteParaUmc, mensajeAEnviar);
//	recibirMensajeUMC_CPU(socketClienteParaUmc, mensajeARecibir);

//
//	t_hash_element *element = dictionary_get(&pcbActual->indiceDeStack,(char*)puntero);
//	t_valor_variable valorEncontrado = (t_valor_variable*) element->key;
////	printf("Dereferenciar %d y su valor es: %d\n", puntero, nivelDeStack_VARIABLE);
//	return mensajeARecibir.valor;
	printf("soy Dereferenciar\n");
}

void funciones_asignar(t_puntero puntero, t_valor_variable variable) {
//	int socketClienteParaUmc = crearSocketCliente(PUERTO_UMC);
//	mensaje_CPU_UMC valorAEnviar;
//	valorAEnviar.protocolo = ESCRIBIR;
//	valorAEnviar.pid = pcbActual.identificador;
//	valorAEnviar.offset = devuelvePagina(puntero, tamPag);
//	valorAEnviar.tamanio = 4;
//	valorAEnviar.pagina = devuelveOffset(puntero, tamPag);
//	valorAEnviar.buffer = variable;
//
//	enviarMensajeCPU_UMC(socketClienteParaUmc, valorAEnviar);

	printf("Asignando en %d el valor %d\n", puntero, variable);
}

void funciones_imprimir(t_valor_variable valor) {
	int socketClienteParaNucleo = crearSocketCliente(PUERTO_NUCLEO);
	mensaje_NUCLEO_CPU mensajeAMandar;
	mensajeAMandar.protocolo = IMPRIMIR;
	mensajeAMandar.valor = valor;
	enviarMensajeCPU_NUCLEO(socketClienteParaNucleo, mensajeAMandar);
}

void funciones_imprimirTexto(char* texto) {
	int socketClienteParaNucleo = crearSocketCliente(PUERTO_NUCLEO);
	mensaje_CPU_NUCLEO mensajeAMandar;
	mensajeAMandar.protocolo = IMPRIMIRTEXTO;
	mensajeAMandar.parametro = texto;
	enviarMensajeCPU_NUCLEO(socketClienteParaNucleo, mensajeAMandar);
}

t_valor_variable funciones_obtenerValorCompartida(t_nombre_compartida variable) {
	mensaje_CPU_NUCLEO mensajeParaNucleo;
	mensaje_NUCLEO_CPU mensajeRecibidoDeNucleo;
	int socketClienteParaNucleo = crearSocketCliente(PUERTO_NUCLEO);
	mensajeParaNucleo.protocolo = PEDIRVALOR;
	mensajeParaNucleo.parametro = variable;
	enviarMensajeCPU_NUCLEO(socketClienteParaNucleo, mensajeParaNucleo);
	recibirMensajeNUCLLEO_CPU(socketClienteParaNucleo,
			&mensajeRecibidoDeNucleo);
	return mensajeRecibidoDeNucleo.valor;
}

t_valor_variable funciones_asignarValorCompartida(t_nombre_compartida variable,
		t_valor_variable valor) {
	mensaje_CPU_NUCLEO mensajeParaNucleo;
	mensaje_NUCLEO_CPU mensajeRecibidoDeNucleo;
	int socketClienteParaNucleo = crearSocketCliente(PUERTO_NUCLEO);
	mensajeParaNucleo.protocolo = ASIGNARVALOR;
	mensajeParaNucleo.parametro = variable;
	mensajeParaNucleo.valor = valor;
	enviarMensajeCPU_NUCLEO(socketClienteParaNucleo, mensajeParaNucleo);
	recibirMensajeCPU_NUCLEO(socketClienteParaNucleo, &mensajeRecibidoDeNucleo);
	return mensajeRecibidoDeNucleo.valor;
}

void funciones_irAlLabel(t_nombre_etiqueta t_nombre_etiqueta) {

	t_puntero_instruccion lineaDeEjecucion = metadata_buscar_etiqueta(
			t_nombre_etiqueta, pcbActual.etiquetas, pcbActual.tamano_etiquetas);
	pcbActual.program_counter = lineaDeEjecucion;
}

void funciones_llamarConRetorno(t_nombre_etiqueta etiqueta,
		t_puntero donde_retornar) {
	nivelDeStack *nuevonivelDeStack = malloc(sizeof(nivelDeStack));
	nuevonivelDeStack->vars = dictionary_create();
	nuevonivelDeStack->retPos = pcbActual.program_counter; // no va 0, aca en realidad se llena con metada_buscar_etiqueta(t_nombre_etiqueta etiqueta)
	nuevonivelDeStack->retVar.pagina = 0;
	nuevonivelDeStack->retVar.offset = donde_retornar;
	nuevonivelDeStack->retVar.tamanio = 4;
	list_add(pcbActual.indiceDeStack, nuevonivelDeStack);
	funciones_irAlLabel(etiqueta);

}

void funciones_entradaSalida(t_nombre_dispositivo dispositivo, int tiempo) {
	int socketClienteParaNucleo = crearSocketCliente(PUERTO_NUCLEO);
	mensaje_CPU_NUCLEO mensajeAEnviar;
	pcbActual.instruccionANucleo = ENTRADASALIDA;
	mensajeAEnviar.pcb = pcbActual;
	mensajeAEnviar.parametro = dispositivo;
	mensajeAEnviar.valor = tiempo;
	enviarMensajeCPU_NUCLEO(socketClienteParaNucleo, mensajeAEnviar);

}

//preguntar si est bien
void funciones_finalizar() {
	mensaje_CPU_NUCLEO mensajeAEnviar;
	int socketClienteParaNucleo = crearSocketCliente(PUERTO_NUCLEO);
	nivelDeStack* unnivelDeStack;
	int i;
	i = list_size(pcbActual.indiceDeStack);

	unnivelDeStack = (nivelDeStack*) list_get(pcbActual.indiceDeStack, i - 1);
	if (unnivelDeStack->retPos != 0) {
		//primero pongo al program counter con el valor del retPos del indice de stack
		pcbActual.program_counter = unnivelDeStack->retPos;
		list_remove(pcbActual.indiceDeStack, i - 1);
	} else {

		pcbActual.instruccionANucleo = FINALIZAR;
		mensajeAEnviar.pcb = pcbActual;
		enviarMensajeCPU_NUCLEO(socketClienteParaNucleo, mensajeAEnviar);
	}

}
void funciones_retornar(t_valor_variable retorno) {
	nivelDeStack* dondeRetornar;
	int tam = list_size(pcbActual.indiceDeStack);
	dondeRetornar = list_get(pcbActual.indiceDeStack, tam - 1);
	if (dondeRetornar->retPos != 0) {
		funciones_asignar(dondeRetornar->retVar.offset, retorno);
	}

}

void kernel_wait(t_nombre_variable variable) {
	mensaje_CPU_NUCLEO mensajeAEnviar;
	mensaje_NUCLEO_CPU mensajeRecibido;
	mensaje_CPU_NUCLEO mensajeAEnviar2;
	int socketClienteParaNucleo = crearSocketCliente(PUERTO_NUCLEO);
	mensajeAEnviar.pcb = pcbActual;
	pcbActual.instruccionANucleo = WAIT;
	mensajeAEnviar.parametro = charToString(variable);
	enviarMensajeCPU_NUCLEO(socketClienteParaNucleo, mensajeAEnviar);
	recibirMensajeNUCLLEO_CPU(socketClienteParaNucleo, &mensajeRecibido);
	if (mensajeRecibido.valor != 0) {
		mensajeAEnviar2.pcb = pcbActual;
		enviarMensajeCPU_NUCLEO(socketClienteParaNucleo, mensajeAEnviar2);
	}
}
void kernel_signal(t_nombre_variable variable) {
	mensaje_CPU_NUCLEO mensajeAEnviar;
	int socketClienteParaNucleo = crearSocketCliente(PUERTO_NUCLEO);

	pcbActual.instruccionANucleo = SIGNAL;
	mensajeAEnviar.parametro = charToString(variable);
	enviarMensajeCPU_NUCLEO(socketClienteParaNucleo, &mensajeAEnviar);

}

int devuelvePagina(int dividendo, int divisor) {
	return (int) (dividendo / divisor);

}

int devuelveOffset(int dividendo, int divisor) {
	return dividendo % divisor;
}
char* charToString(char element) {
	char* new = malloc(2);
	*new = element;
	*(new + 1) = '\0';
	return new;
}
