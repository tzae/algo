/**
    @file Cálculo de el elemento en su posición
 */

 #include <iostream>
 #include <ctime>
 #include <cstdlib>
 #include <chrono>
 #include <unistd.h>
 #include "generadores.h"

 using namespace std;


/**
   @brief Localiza un elemento en un vector ordenado que esté en su posición
   @pre `n` >= 0
   @param v: vector de elementos.
   @param n: número de elementos.
   @return Posición del elemento si está, `-1` en otro caso
   @note Versión obvia (búsqueda secuencial)
*/
int pos_obvia(const int v[], int n){
 for(int i = 0; i < n; i++)
  if(v[i] == i)
   return i;
 return -1;
}



/**
   @brief Localiza un elemento en un vector ordenado que esté en su posición
   @pre `n` >= 0
   @param v: vector de elementos.
   @param n: número de elementos.
   @param ajuste: número en el que difiere el primer elemento de la posición 0 real. Es necesario para la recursión.
   @return Posición del elemento si está, `-1` en otro caso
   @note Versión obvia (búsqueda secuencial)
*/
int pos_obvia_ajustada(const int v[], int n, int ajuste = 0){
  for(int i = 0; i < n; i++)
    if(v[i]-ajuste == i)
      return i;
  return -1;
}
/**
  @brief Localiza un elemento en un vector ordenado que esté en su posición
  @pre `n` >= 0
  @pre v no puede tener elementos repetidos
  @param v: vector de elementos.
  @param n: número de elementos.
  @param ajuste: número en el que difiere el primer elemento de la posición 0 real. Es necesario para la recursión.
  @return Posición del elemento si está, `-1` en otro caso
  @note Versión divide y vencerás 1 (recursiva)
  @note Separamos esta función en dos debido a su tercer parámetro por defecto (y que se pueda llamar desde el main como las otras dos funciones).
  Realmente, se puede llamar como las demás, pero no como parámetro en "ejecutar" y "ejecutar_media"
*/

int pos_dyv_rec(const int v[], int n, int ajuste = 0){
  if(n <= 3)
    return pos_obvia_ajustada(v, n, ajuste);

  int medio = n/2;
  if(medio == v[medio]-ajuste)
    return medio;
  else if(medio < v[medio]-ajuste)
    return pos_dyv_rec(v, n/2, ajuste);

  int pos_d = pos_dyv_rec(v+medio+1, (n-1)/2, medio+1+ajuste);
  return pos_d != -1 ? pos_d+medio+1 : -1;
}

int pos_dyv1(const int v[], int n){
  return pos_dyv_rec(v,n);
}

 /**
  @brief Localiza un elemento en un vector ordenado que esté en su posición
  @pre `n` >= 0
  @pre v no puede tener elementos repetidos
  @param v: vector de elementos.
  @param n: número de elementos.
  @return Posición del elemento si está, `-1` en otro caso
  @note Versión divide y vencerás 2 (no recursiva)
*/
int pos_dyv2(const int v[], int n){
	int tope_min = 0;
	int i = (n-1)/2;
	int tope_max = n-1;
	bool encontrado=false;

	if(i == v[i])
		encontrado = true;

	while( (!encontrado) && (tope_max >= tope_min) ){
		if(i == v[i])
			encontrado = true;
		else if(i < v[i]){
			tope_max = i-1;
			i = (tope_max + tope_min)/2;
		}
		else if(i > v[i]){
			tope_min = i+1;
			i = (tope_max + tope_min)/2;
		}
	}

	if(encontrado)
		return i;
	else
		return -1;
}

/**
 @brief Localiza un elemento en un vector ordenado que esté en su posición
 @pre `n` >= 0
 @param v: vector de elementos.
 @param n: número de elementos.
 @param ajuste: número en el que difiere el primer elemento de la posición 0 real. Es necesario para la recursión.
 @return Posición del elemento si está, `-1` en otro caso
 @note Versión para el caso en el que v admite repetidos
*/
int pos_dyv_rec3(const int v[], int n, int ajuste = 0){
  if(n <= 2)
    return pos_obvia_ajustada(v, n, ajuste);

 int medio = n/2;

 if(medio == v[medio]-ajuste)
    return medio;
 else if(medio < v[medio]-ajuste){
    int izquierda = pos_dyv_rec3(v,n/2,ajuste);
    if(izquierda != -1)
      return izquierda;
    else{
      int pos_der = pos_dyv_rec3(v+medio+1,(n-1)/2,ajuste+medio+1);
      return pos_der != -1 ? pos_der+medio+1 : -1;
   }
 }
 else{
   int pos_der = pos_dyv_rec3(v+medio+1,(n-1)/2,ajuste+medio+1);
   if(pos_der != -1)
     return pos_der+medio+1;
   else
     return pos_dyv_rec3(v,n/2,ajuste);
 }
}

int pos_dyv3(const int v[], int n){
  return pos_dyv_rec3(v,n);
}

 int ejecutar(int (*f)(const int*, int), int n) {
   int* T = new int[n];
   get_elementoensuposicion(T, n);

    chrono::steady_clock::time_point tantes, tdespues;
   chrono::duration<double> transcurrido;

   tantes = chrono::steady_clock::now();
   f(T,n);
   tdespues = chrono::steady_clock::now();

   transcurrido = chrono::duration_cast<chrono::duration<double>>(tdespues - tantes);
   cout << n << " " << transcurrido.count() << endl;
   delete [] T;

   return 0;
 }


const int MAX = 10;    // MAX del bucle interior (no afecta al vector)
const int MAX2 = 1000; // MAX del bucle exterior (afecta al vector)
 int ejecutar_media(int (*f)(const int*, int), int n, int MAX = MAX) {
   int* T = new int[2*n-1]; // Se necesitan 2*n-1 elementos para la función get_elementoensuposicion
   double total = 0;
for(int k = 0; k<MAX2; k++){
  //   get_elementoensuposicion(T, n);
  get_elementoensuposicion2(T,n); // GENERA ELEMENTOS REPETIDOS
   for(int m = 0; m < MAX; m++){

      chrono::steady_clock::time_point tantes, tdespues;
     chrono::duration<double> transcurrido;

     tantes = chrono::steady_clock::now();
     f(T,n);
     tdespues = chrono::steady_clock::now();

     transcurrido = chrono::duration_cast<chrono::duration<double>>(tdespues - tantes);
     total += transcurrido.count();
   }
 }
    cout << n << " " << total/(MAX*MAX2*1.0) << endl;
   delete [] T;

   return 0;
 }

 int main(int argc, char * argv[])
 {

     srand(time(0));
 if (argc != 3 || (argv[2][0] != 't' && argv[2][0] != '1' && argv[2][0] != '2' && argv[2][0] != '3')){
  cerr << "Formato " << argv[0] << " <num_elem> t/1/2" << endl;
  return -1;
 }

 int n = atoi(argv[1]);

 if (argv[2][0] == 't')
    return ejecutar_media(pos_obvia, n, MAX);
 else if (argv[2][0] == '1')
    return ejecutar_media(pos_dyv1, n, MAX);
 else if (argv[2][0] == '2')
    return ejecutar_media(pos_dyv2, n, MAX);
  else
    return ejecutar_media(pos_dyv3, n, MAX);
 }
