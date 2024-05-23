#!/usr/bin/perl
#**************************************************************
#     Pontificia Universidad Javeriana
#     Autores: 
#     Fecha: 9 mayo 2024
#     Materia: Sistemas Operativos
#     Tema: Taller de Evaluación de Rendimiento
#     Fichero: script automatización ejecución por lotes 
#****************************************************************/

# Configuración inicial del script
$Path = `pwd`; # Obtiene el directorio actual
chomp($Path); # Elimina el salto de línea del directorio

# Definición de variables
@Nombres_Carpetas = ("mm_Clasico","mm_Transpuesta"); # Nombres de las carpetas que contienen los ejecutables
%Ejecutables = (
    "mm_Clasico" => ["MM_ejecutable"],
    "mm_Transpuesta" => ["MM_ejecutable"]
); # Hash de ejecutables por carpeta
@Size_Matriz = ("200","400","800","1200","1600","1800","2000","2400","2800","3200","3600","4000"); # Tamaños de las matrices a procesar
@Num_Hilos = (1,2,3,4,5,6,7,8); # Números de hilos a utilizar
$Repeticiones = 30; # Número de repeticiones por configuración

# Bucle para recorrer las carpetas de ejecutables
foreach $carpeta (@Nombres_Carpetas){
    # Bucle para recorrer los ejecutables en la carpeta
    foreach $nombre (@{$Ejecutables{$carpeta}}){
        # Bucle para recorrer los tamaños de las matrices
        foreach $size (@Size_Matriz){
            # Bucle para recorrer los números de hilos
            foreach $hilo (@Num_Hilos) {
                # Creación del nombre del archivo de salida
                $file = "$Path/$carpeta/$nombre-$size-Hilos-$hilo.dat";
                # Bucle para realizar las repeticiones
                for ($i = 0; $i < $Repeticiones; $i++) {
                    # Ejecución del comando para correr el ejecutable y redirigir la salida al archivo
                    system("$Path/$carpeta/$nombre $size $hilo >> $file");
                    # Impresión del comando que se ejecutaría (comentado)
                    # printf("$Path/$carpeta/$nombre $size $hilo \n");
                }
            }
        }
    }
}
	