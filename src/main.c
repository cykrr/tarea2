/* Entrada y salida estándar */
#include <stdio.h>

/* manipulación de Strings */
#include <string.h>

#include "csv.h"
#include "menu.h"
#include "util.h"
#include "search.h"
#include "song.h"
#include "playlist.h"
/* main function */
int main(){
    List * listaCanciones = listCreate();
    strcpy(listaCanciones->name, "Lista principal");
    List *listaPlaylists = listCreate();
    listPushBack(listaPlaylists, listaCanciones);

    char in = '\0';

    mostrarMenu(listaCanciones, 0);

    int repetida = 0;

    while(in != 'q' ){
        mostrarMenu(listaCanciones, repetida);
        fflush(stdin);
        scanf("%c", &in);
        getchar();

        switch(in) {
            
            case 'i':
                addSong(listaPlaylists, listaCanciones);
                break;
            case 'x':
            	deleteSong(listaCanciones);
            	break;
            case 'b':
                mostrarMenuBuscar();
                scanf("%c", &in);
                getchar();
                switch(in){
                    case'n':
                        searchSong(listaCanciones);
                        break;
                    case 'g':
                        searchGenre(listaCanciones);
                        break;
                    case 'a':
                        searchArtist(listaCanciones);
                        break;
                    case 'q': {
                        exit(1);
                        break;
                    }
                }
                break;
            case 'm':
                mostrarLista(listaCanciones, 0);
                break;
            case 'y': {
                char archivo[20];
                printf("Nombre archivo: ");
                scanf("%s", archivo);
                getchar();
                List *list = CSVimport(archivo);
                if (!list) { 
                    strcat(buf, COLOR_RED "Error: "
                            "no se pudo leer el archivo\n"
                            COLOR_RESET);
                } else  {
                    playlistImport(listaPlaylists,
                            listaCanciones, 
                            list);
                }
                break;
            }
            case 'e':{
                char archivo[20];
                printf("Nombre archivo: ");
                scanf("%s", archivo);
                getchar();

                CSVexport(listaCanciones, archivo);
                break;
            }
            case 'p': {
                char opcion = 0;
                while( opcion != 'q') {
                    mostrarMenuPlaylists();
                    scanf("%c", &opcion);
                    getchar();
                    switch(opcion) {
                        case 'n': {
                            printf("Nombre de la nueva playlist: ");
                            char nombre[30];
                            scanf("%[^\n]*s", nombre);
                            getchar();
                            if(!findPlaylist(listaPlaylists, nombre)) { 
                                List *playlist = listCreate();
                                strcpy(playlist->name, nombre);
                                listPushBack(listaPlaylists, playlist);
                                strcat(buf, "playlist anadida. \n\n");
                            } else  {
                                strcat(buf, "playlist ya existe. \n\n");

                            }
                            break;
                        }
                        case 'm': {
                            printf("Nombre de la playlist: ");
                            char nombre[30];
                            scanf("%[^\n]*s", nombre);
                            getchar();
                            showPlaylist(nombre, listaPlaylists);

                            break;
                        }
                        case 'M': {
                            if (listaPlaylists->length)
                            for(List* list = listFirst(listaPlaylists);
                                list != NULL;
                                list = listNext(listaPlaylists)) {

                                strcat(buf, "Playlist: ");
                                strcat(buf, list->name);
                                strcat(buf, "\n");
                                strcat(buf, 
                                        "Cantidad de canciones: ");

                                char str[4];
                                sprintf(str, "%zd", list->length);
                                strcat(buf, str);
                                strcat(buf, "\n");
                                strcat(buf, "\n");
                            }
                            else {
                                strcat(buf, COLOR_RED "Error: no hay playlists\n" COLOR_RESET);
                            }
                            break;
                        }
                        case 'x': {
                            printf("Nombre de la playlist: ");
                            char nombre[30];
                            scanf("%s", nombre);
                            getchar();
                            deletePlaylist(listaPlaylists, nombre);
                            break;
                        }
                    }
                }
                break;
            } // while ? 

            case 'c': {
                listClean(listaCanciones);
                break;
          } 


        }  // switch in;

    } // while (in != q)
    printf("Bye bye\n");
    return 0;
}

