#include "lista.h"
#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>

void pruebas_insertar_inicio_final(){

	printf("\n");
	printf("%s\n","=============== PRUEBAS INSERTAR CON ITERADOR ===============" );

	lista_t* lista = lista_crear();
	lista_iter_t* iter = lista_iter_crear(lista);

	print_test("lista esta vacia", lista_esta_vacia(lista));

	int valor = 1;
	int* dato =&valor;
	print_test("el primer elmento se inserto correctamente", lista_iter_insertar(iter,dato));
	print_test("Al insertar un elemento en la posición en la que se crea el iterador, efectivamente se inserta al principio.",lista_ver_primero(lista) == dato);

	int valor2 = 2;
	int* dato2 =&valor2;
	lista_insertar_ultimo(lista,dato2);

	int valor3 = 3;
	int* dato3 =&valor3;
	lista_insertar_ultimo(lista,dato3);

	int* aux = lista_ver_ultimo(lista);
	print_test("el ultimo elmento es:", *aux == 3);

	while(!lista_iter_al_final(iter)){
		lista_iter_avanzar(iter);
	}

	int valor4 = 4;
	int* dato4 =&valor4;
	lista_iter_insertar(iter,dato4);
	print_test("Insertar un elemento cuando el iterador está al final efectivamente es equivalente a insertar al final.",lista_ver_ultimo(lista) == dato4);


	lista_iter_destruir(iter);
	lista_destruir(lista,NULL);
}

void remover_primer_ultimo_elemento(){

	printf("\n");
	printf("%s\n","=============== PRUEBAS BORRAR CON ITERADOR ===============" );

	lista_t* lista = lista_crear();
	
	int valor = 1;
	int* dato =&valor;
	lista_insertar_ultimo(lista,dato);

	int valor2 = 2;
	int* dato2 =&valor2;
	lista_insertar_ultimo(lista,dato2);

	int valor3 = 3;
	int* dato3 =&valor3;
	lista_insertar_ultimo(lista,dato3);

	int valor4 = 4;
	int* dato4 =&valor4;
	lista_insertar_ultimo(lista,dato4);
	
	int* aux = lista_ver_primero(lista);
	print_test("el primer elemento es 1",*(aux) == 1);
	int* aux1 = lista_ver_ultimo(lista);
	print_test("el ultimo elemento es 4",*(aux1) == 4);

	lista_iter_t* iter = lista_iter_crear(lista);

	printf("\n");
	printf("%s\n","Al remover el elemento cuando se crea el iterador, cambia el primer elemento de la lista" );

	aux = lista_iter_borrar(iter);
	print_test("el elemento borrado al crear iterador es 1",*(aux) == 1);
	aux1 = lista_ver_primero(lista);
	print_test("despues de borrar ,el primer elemento de la lista es: 2",*(aux1) == 2);

	printf("\n");
	printf("%s\n","Remover el último elemento con el iterador cambia el último de la lista." );

	for (int i = 0; i <2 ; ++i){
		lista_iter_avanzar(iter);
	}
	aux = lista_iter_borrar(iter);
	print_test("borramos el ultimo elemento que es 4",*(aux) == 4);
	aux1 = lista_ver_ultimo(lista);
	print_test("despues de borrar el ultimo elemento es: 3",*(aux1) == 3);

	lista_iter_destruir(iter);
	lista_destruir(lista,NULL);

}

void prueba_insertar_medio(){

	printf("\n");
	printf("%s\n","============ PRUEBAS INSERTAR MEDIO =============" );

	lista_t* lista = lista_crear();

	int valor = 1;
	int* dato =&valor;
	lista_insertar_ultimo(lista,dato);

	int valor2 = 2;
	int* dato2 =&valor2;
	lista_insertar_ultimo(lista,dato2);

	int valor3 = 3;
	int* dato3 =&valor3;
	lista_insertar_ultimo(lista,dato3);

	lista_iter_t* iter =lista_iter_crear(lista);
	lista_iter_avanzar(iter);

	printf("\n");
	printf("%s\n","Insertar un elemento en el medio se hace en la posición correcta." );

	int* medio = lista_iter_ver_actual(iter);
	print_test("el elemento del medio es: 2", *medio == 2);

	int valor4 = 4;
	int* dato4 =&valor4;
	lista_iter_insertar(iter,dato4);

	medio = lista_iter_ver_actual(iter);
	print_test("despues de insertar el 4 ,el medio es 4", *medio == 4);
	

	lista_iter_destruir(iter);
	lista_destruir(lista,NULL);
}

void vector_datos(int** vector,int cantidad){
	for (int i = 1; i <= cantidad; ++i){
		vector[i-1] = &i;
	}	
}

void prueba_de_volumnen(){
	printf("\n");
	printf("%s\n","================== PRUEBA DE VOLUMEN ==================" );

	lista_t* lista = lista_crear();
	print_test("lista recien creada esta vacia",lista_esta_vacia(lista));

	bool ok = true;
	int* vector[10000];
	vector_datos(vector,10000);
	for (int i = 0; i < 10000; ++i){
		ok &= lista_insertar_ultimo(lista,vector[i]);
		ok &= (vector[i] == lista_ver_ultimo(lista));
	}
	print_test(" los 10000 elementos se insertaron correctamente", ok == true);
	ok = true;
	lista_iter_t* iter = lista_iter_crear(lista);
	int j = 0;
	while(!lista_iter_al_final(iter)){
		ok &= (vector[j] == lista_ver_primero(lista));
		ok &= (vector[j] == lista_iter_borrar(iter));
		j++;
		lista_iter_avanzar(iter);
	}

	print_test("se borraron correctamente los 10000 dato", ok == true);

	lista_iter_destruir(iter);
	lista_destruir(lista,NULL);
}

void pruebas_crear_lista(){
	printf("\n");
	printf("%s\n","============== PRUEBAS CREAR LISTA=============");
	lista_t* lista = lista_crear();
	print_test("la lista se creo correctamente", lista != NULL);
	print_test("lista_esta_vacia",lista_esta_vacia(lista));
	print_test("el primer elemento de la lista es NULL", lista_ver_primero(lista) == NULL);

	lista_iter_t* iter = lista_iter_crear(lista);
	print_test("el iterador de la lista se creo correctamente", iter != NULL);
	print_test("el iterador actual apunta a NULL", lista_iter_ver_actual(iter) == NULL);

	lista_iter_destruir(iter);
	lista_destruir(lista,NULL);
}

void prueba_insertar_NULL(){
	printf("\n");
	printf("%s\n","=============== PRUEBAS INSERTAR NULL =============");
	lista_t* lista = lista_crear();
	print_test("se inserto correctamente NULL", lista_insertar_primero(lista,NULL));
	print_test("el elemento insertado es NULL", lista_ver_primero(lista) == NULL);

	lista_destruir(lista,NULL);
}

void destruir_dato(pila_t* pila){
	pila_destruir(pila);
}

void destruir_dato_wrapper(void* pila){
	destruir_dato(pila);
}

void prueba_lista_destruir(){
	printf("\n");
	printf("%s\n","===============LISTA DESTRUIR =================" );
	lista_t* lista = lista_crear();

	bool ok = true;
	for (int i = 0; i < 10; ++i){
		pila_t* pila = pila_crear();
		ok &= lista_insertar_ultimo(lista,pila);
		ok &= (lista_ver_ultimo(lista) == pila);
	}
	print_test(" se insertaron correctamente 10 pilas ala lista",ok == true);
	lista_destruir(lista,destruir_dato_wrapper);
	printf("%s\n","se destruyeron correctamente la lista, fijarce valgrind" );
}

void pruebas_crear_iter(){
	printf("\n");
	printf("%s\n","==================PRUEBAS CREAR ITERADOR ==================== ");
	lista_t* lista = lista_crear();
	print_test("la lista se creo adecuadamente", lista != NULL);
	print_test("el primer elemento de la lsita es NULL",!lista_ver_primero(lista));
	lista_iter_t* iter = lista_iter_crear(lista);
	print_test("el iterador se creo correctamente", iter != NULL);
	print_test("al crear el iterador,iter->actual apunta al 1er elemento de la lista",lista_iter_ver_actual(iter) == lista_ver_primero(lista));
	lista_iter_destruir(iter);
	lista_destruir(lista,NULL);
}

void pruebas_iter_insertar_borrar(){
	printf("\n");
	printf("%s\n","=================PRUEBAS DE INSERTAR Y BORRAR CON EL ITERADOR=================" );
	lista_t* lista = lista_crear();
	lista_iter_t* iter = lista_iter_crear(lista);
	int* vector[10];
	vector_datos(vector,10);
	bool ok = true;
	for (int i = 0; i < 10; ++i){
		ok &= lista_iter_insertar(iter,vector[i]);
		ok &= (vector[i] == lista_iter_ver_actual(iter));
	}
	size_t largo = lista_largo(lista);
	printf("%ld\n",largo );
	print_test("se insertaron correctamento los 10 elemntos con el iterador", ok == true);
	lista_iter_destruir(iter);

	lista_iter_t* iter_aux = lista_iter_crear(lista);
	ok = true;
	int i = 0;
	while(!lista_iter_al_final(iter_aux)){
		ok &= (lista_iter_ver_actual(iter_aux) == vector[i]);
		ok &= (lista_iter_borrar(iter_aux) == vector[i]);
		i++;
	}

	print_test("lista esta vacia", lista_esta_vacia(lista));
	print_test("se borraron con el iterador los 10 elementos", ok == true);
	lista_iter_destruir(iter_aux);
	lista_destruir(lista,NULL);
}

void pruebas_iter_avanzar(){
	printf("\n");
	printf("%s\n","================ PRUEBAS DE AVANZAR CON EL ITERADOR ====================" );
	lista_t* lista = lista_crear();
	int* vector[5];
	vector_datos(vector,5);
	for (int i = 0; i <5 ; ++i){
		lista_insertar_ultimo(lista,vector[i]);
	}
	lista_iter_t* iter = lista_iter_crear(lista);
	print_test("al momento de crear el iter apunto al primer elemnto de la lista",lista_iter_ver_actual(iter) == vector[0]);
	int i = 0;
	bool ok = true;
	while(!lista_iter_al_final(iter)){
		ok &= (lista_iter_ver_actual(iter) == vector[i]);
		ok &= lista_iter_avanzar(iter);
		i++;
	}
	print_test("el iterador recorrio toda la lista de forma correcta",ok == true);
	print_test("el iterador se encuentra al final",lista_iter_al_final(iter));
	print_test("el iterador al final , ver actual es NULL", !lista_iter_ver_actual(iter));
	lista_iter_destruir(iter);
	lista_destruir(lista,NULL);
}

bool visitar(void* dato, void* suma){
	*(int*)suma += *(int*)dato;
	return true;
}

void pruebas_iterador_interno_con_corte(){
	printf("\n");
	printf("%s\n", "=================PRUEBAS ITERADOR INTERNO CON CORTE========================");
	lista_t* lista = lista_crear();
	int dato1 = 10;
	lista_insertar_ultimo(lista,&dato1);
	int dato2 = 20;
	lista_insertar_ultimo(lista,&dato2);
	int dato3 = 30;
	lista_insertar_ultimo(lista,&dato3);

	int suma = 0;
	lista_iterar(lista,visitar, &suma);
	print_test("con el iterador recorremos toda la lista y sumamos los 10 datos", suma == 60 );
	lista_destruir(lista,NULL);
}

bool visitar_aux(void* dato,void* extra){
	if (extra != NULL) return false;
	pila_destruir(dato);
	return true;
}

void pruebas_iterador_interno_sin_corte(){
	printf("\n");
	printf("%s\n", "=================PRUEBAS ITERADOR INTERNO SIN CORTE========================");
	lista_t* lista = lista_crear();
	for (int i = 0; i < 10; ++i){
		pila_t* pila = pila_crear();
		lista_insertar_primero(lista,pila);
	} 
	printf("%s\n","eliminamos las pilas con iterador interno, fijarce valgrind" );
	lista_iterar(lista,visitar_aux,NULL);
	lista_destruir(lista,NULL);
}

void pruebas_lista_alumno() {
    lista_t* ejemplo = NULL;

    print_test("Puntero inicializado a NULL", ejemplo == NULL);

    pruebas_crear_lista();
    pruebas_insertar_inicio_final();
    remover_primer_ultimo_elemento();
    prueba_insertar_medio();
    prueba_de_volumnen();
    prueba_insertar_NULL();
    prueba_lista_destruir();
   	pruebas_iter_avanzar();
   	pruebas_iter_insertar_borrar();
   	pruebas_crear_iter();
   	pruebas_iterador_interno_con_corte();
   	pruebas_iterador_interno_sin_corte();
}