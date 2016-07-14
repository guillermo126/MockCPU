/*
 * ParserCpu.h
 *
 *  Created on: 17/5/2016
 *      Author: utnso
 */

#ifndef SRC_PARSERCPU_H_
#define SRC_PARSERCPU_H_

#include "parser.h"
#include <stdio.h>
#include <tiposDato.h>
int tamPag;
pcb pcbActual;
char* charToString(char element);
int devuelvePagina(int dividendo, int divisor);
int devuelveOffset(int dividendo, int divisor);
t_puntero funciones_definirVariable(t_nombre_variable variable);

t_puntero funciones_obtenerPosicionVariable(t_nombre_variable variable);
t_valor_variable funciones_dereferenciar(t_puntero puntero);
void funciones_asignar(t_puntero puntero, t_valor_variable variable);

void funciones_imprimir(t_valor_variable valor);
void funciones_imprimirTexto(char* texto);
t_valor_variable funciones_obtenerValorCompartida(t_nombre_compartida variable);
t_valor_variable funciones_asignarValorCompartida(t_nombre_compartida variable,
		t_valor_variable valor);
void funciones_irAlLabel(t_nombre_etiqueta t_nombre_etiqueta);
void funciones_llamarConRetorno(t_nombre_etiqueta etiqueta,
		t_puntero donde_retornar);
void funciones_finalizar(void);
void funciones_retornar(t_valor_variable retorno);
void funciones_entradaSalida(t_nombre_dispositivo dispositivo, int tiempo);

void kernel_wait(t_nombre_variable variable);
void kernel_signal(t_nombre_variable variable);

#endif /* SRC_PARSERCPU_H_ */
