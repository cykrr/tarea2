/* Entrada y salida estándar */
#include <stdio.h>

/* manipulación de Strings */
#include <string.h>

#include "csv.h"
#include "menu.h"
#include "util.h"
#include "search.h"
#include "carrito.h" 
#include "list.h" 
#include "map.h"
#include "item.h"

int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

/* main function */
int main(){
    Map * mapNames = createMap(is_equal_string);
    Map * mapTypes = createMap(is_equal_string);
    Map * mapBrands = createMap(is_equal_string);
    Map * mapCarts = createMap(is_equal_string);

    char in = '\0';

    int repetida = 0;

    char archivo[30];

    while(in != 'q' ){
        mostrarMenu();
        fflush(stdin);
        scanf("%c", &in);
        getchar();

        switch(in) {
            case ('i'): // Importar archivo por nombre
                listaImportarArchivo(mapNames, mapTypes, mapBrands);
                break;

            case('a'): // Agregar producto
                if(addItem(mapNames,mapTypes,mapBrands) == 1 ){
                    strcat(buf, "Stock del producto actualizado\n");
                } else{
                    strcat(buf, "Producto agregado correctamente\n");
                }
                break;
            case('x'): // Quitar producto
                showItem(mapNames -> head -> data);
                break;
            case('b'): // Buscar producto
                break;
            // Mostrar todos los productos por tipo
            case('t'):
                showItemsByType(mapTypes);
                break;
            // Mostrar todos los productos por marca
            case('m'):
                showItemsByBrand(mapBrands);
                break;
            case('M'): // Mostrar todos los productos
                showItems(mapNames);
                break;
            case('A'): // Añadir al carrito
                addToCart(mapCarts, mapNames);
                break;
            case('X'): // Quitar del carrito
                break;
            case('p'): // Concretar compra
                cartCheckout(mapCarts);
                break;
            case('C'): // Mostrar carritos
                showCarts(mapCarts);
                break;
            default:
                break;
          } 

    } // while (in != q)
    printf("Bye bye\n");
    return 0;
}

