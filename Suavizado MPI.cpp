// Suavizado.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

//#include <opencv2/core.hpp>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui.hpp>
#define _CRT_SECURE_NO_WARNINGS





#include <mpi.h>
#include <iostream>
#include <vector>
#include <stdio.h>

#include <windows.h>
#include <string>

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\imgproc.hpp>
#include <iostream>
#include <tchar.h>  

#include <direct.h>
#define GetCurrentDir _getcwd


using namespace cv;
using namespace std;


Mat image;
Mat outputImage;
Mat prueba;
Mat pruebaOpernCV;
Mat outputImage2;
Mat outputImage3;
int filas;
int columnas;

// int MAX_KERNEL_LENGTH = 5;


std::string get_current_dir() {
    char buff[FILENAME_MAX]; //create string buffer to hold path
    GetCurrentDir(buff, FILENAME_MAX);
    string current_working_dir(buff);
    return current_working_dir;
}

void calcularBorde() { // suavizado de 3*3, calculo del borde

    // primero calcular las cuatro esquinas

    outputImage.at<Vec3b>(0, 0)[0] = (image.at<Vec3b>(0, 1)[0] + image.at<Vec3b>(1, 1)[0] + image.at<Vec3b>(1, 0)[0]) / 3;
    outputImage.at<Vec3b>(0, 0)[1] = (image.at<Vec3b>(0, 1)[1] + image.at<Vec3b>(1, 1)[1] + image.at<Vec3b>(1, 0)[1]) / 3;
    outputImage.at<Vec3b>(0, 0)[2] = (image.at<Vec3b>(0, 1)[2] + image.at<Vec3b>(1, 1)[2] + image.at<Vec3b>(1, 0)[2]) / 3;

    outputImage.at<Vec3b>(0, image.cols - 1)[0] = (image.at<Vec3b>(0, image.cols - 2)[0] + image.at<Vec3b>(1, image.cols - 2)[0] + image.at<Vec3b>(1, image.cols - 1)[0]) / 3;
    outputImage.at<Vec3b>(0, image.cols - 1)[1] = (image.at<Vec3b>(0, image.cols - 2)[1] + image.at<Vec3b>(1, image.cols - 2)[1] + image.at<Vec3b>(1, image.cols - 1)[1]) / 3;
    outputImage.at<Vec3b>(0, image.cols - 1)[2] = (image.at<Vec3b>(0, image.cols - 2)[2] + image.at<Vec3b>(1, image.cols - 2)[2] + image.at<Vec3b>(1, image.cols - 1)[2]) / 3;

    outputImage.at<Vec3b>(image.rows - 1, 0)[0] = (image.at<Vec3b>(image.rows - 2, 0)[0] + image.at<Vec3b>(image.rows - 2, 1)[0] + image.at<Vec3b>(image.rows - 1, 1)[0]) / 3;
    outputImage.at<Vec3b>(image.rows - 1, 0)[1] = (image.at<Vec3b>(image.rows - 2, 0)[1] + image.at<Vec3b>(image.rows - 2, 1)[1] + image.at<Vec3b>(image.rows - 1, 1)[1]) / 3;
    outputImage.at<Vec3b>(image.rows - 1, 0)[2] = (image.at<Vec3b>(image.rows - 2, 0)[2] + image.at<Vec3b>(image.rows - 2, 1)[2] + image.at<Vec3b>(image.rows - 1, 1)[2]) / 3;

    outputImage.at<Vec3b>(image.rows - 1, image.cols - 1)[0] = (image.at<Vec3b>(image.rows - 1, image.cols - 2)[0] + image.at<Vec3b>(image.rows - 2, image.cols - 2)[0] + image.at<Vec3b>(image.rows - 2, image.cols - 1)[0]) / 3;
    outputImage.at<Vec3b>(image.rows - 1, image.cols - 1)[1] = (image.at<Vec3b>(image.rows - 1, image.cols - 2)[1] + image.at<Vec3b>(image.rows - 2, image.cols - 2)[1] + image.at<Vec3b>(image.rows - 2, image.cols - 1)[1]) / 3;
    outputImage.at<Vec3b>(image.rows - 1, image.cols - 1)[2] = (image.at<Vec3b>(image.rows - 1, image.cols - 2)[2] + image.at<Vec3b>(image.rows - 2, image.cols - 2)[2] + image.at<Vec3b>(image.rows - 2, image.cols - 1)[2]) / 3;


    // luego calcular los cuatro bordes

    //Borde superior
    for (int i = 1; i < image.cols - 1; i++) {
        outputImage.at<Vec3b>(0, i)[0] = (image.at<Vec3b>(0, i - 1)[0] + image.at<Vec3b>(1, i - 1)[0] + image.at<Vec3b>(1, i)[0] + image.at<Vec3b>(1, i + 1)[0] + image.at<Vec3b>(0, i + 1)[0]) / 5;
        outputImage.at<Vec3b>(0, i)[1] = (image.at<Vec3b>(0, i - 1)[1] + image.at<Vec3b>(1, i - 1)[1] + image.at<Vec3b>(1, i)[1] + image.at<Vec3b>(1, i + 1)[1] + image.at<Vec3b>(0, i + 1)[1]) / 5;
        outputImage.at<Vec3b>(0, i)[2] = (image.at<Vec3b>(0, i - 1)[2] + image.at<Vec3b>(1, i - 1)[2] + image.at<Vec3b>(1, i)[2] + image.at<Vec3b>(1, i + 1)[2] + image.at<Vec3b>(0, i + 1)[2]) / 5;
    }

    //Borde inferior
    for (int i = 1; i < image.cols - 1; i++) {
        outputImage.at<Vec3b>(image.rows - 1, i)[0] = (image.at<Vec3b>(image.rows - 1, i - 1)[0] + image.at<Vec3b>(image.rows - 2, i - 1)[0] + image.at<Vec3b>(image.rows - 2, i)[0] + image.at<Vec3b>(image.rows - 2, i + 1)[0] + image.at<Vec3b>(image.rows - 1, i + 1)[0]) / 5;
        outputImage.at<Vec3b>(image.rows - 1, i)[1] = (image.at<Vec3b>(image.rows - 1, i - 1)[1] + image.at<Vec3b>(image.rows - 2, i - 1)[1] + image.at<Vec3b>(image.rows - 2, i)[1] + image.at<Vec3b>(image.rows - 2, i + 1)[1] + image.at<Vec3b>(image.rows - 1, i + 1)[1]) / 5;
        outputImage.at<Vec3b>(image.rows - 1, i)[2] = (image.at<Vec3b>(image.rows - 1, i - 1)[2] + image.at<Vec3b>(image.rows - 2, i - 1)[2] + image.at<Vec3b>(image.rows - 2, i)[2] + image.at<Vec3b>(image.rows - 2, i + 1)[2] + image.at<Vec3b>(image.rows - 1, i + 1)[2]) / 5;
    }

    //Borde oriental
    for (int i = 1; i < image.rows - 1; i++) {
        outputImage.at<Vec3b>(i, image.cols - 1)[0] = (image.at<Vec3b>(i - 1, image.cols - 1)[0] + image.at<Vec3b>(i - 1, image.cols - 2)[0] + image.at<Vec3b>(i, image.cols - 2)[0] + image.at<Vec3b>(i + 1, image.cols - 2)[0] + image.at<Vec3b>(i + 1, image.cols - 1)[0]) / 5;
        outputImage.at<Vec3b>(i, image.cols - 1)[1] = (image.at<Vec3b>(i - 1, image.cols - 1)[1] + image.at<Vec3b>(i - 1, image.cols - 2)[1] + image.at<Vec3b>(i, image.cols - 2)[1] + image.at<Vec3b>(i + 1, image.cols - 2)[1] + image.at<Vec3b>(i + 1, image.cols - 1)[1]) / 5;
        outputImage.at<Vec3b>(i, image.cols - 1)[2] = (image.at<Vec3b>(i - 1, image.cols - 1)[2] + image.at<Vec3b>(i - 1, image.cols - 2)[2] + image.at<Vec3b>(i, image.cols - 2)[2] + image.at<Vec3b>(i + 1, image.cols - 2)[2] + image.at<Vec3b>(i + 1, image.cols - 1)[2]) / 5;
    }

    //Borde occidental
    for (int i = 1; i < image.rows - 1; i++) {
        outputImage.at<Vec3b>(i, 0)[0] = (image.at<Vec3b>(i - 1, 0)[0] + image.at<Vec3b>(i - 1, 1)[0] + image.at<Vec3b>(i, 1)[0] + image.at<Vec3b>(i + 1, 1)[0] + image.at<Vec3b>(i + 1, 0)[0]) / 5;
        outputImage.at<Vec3b>(i, 0)[1] = (image.at<Vec3b>(i - 1, 0)[1] + image.at<Vec3b>(i - 1, 1)[1] + image.at<Vec3b>(i, 1)[1] + image.at<Vec3b>(i + 1, 1)[1] + image.at<Vec3b>(i + 1, 0)[1]) / 5;
        outputImage.at<Vec3b>(i, 0)[2] = (image.at<Vec3b>(i - 1, 0)[2] + image.at<Vec3b>(i - 1, 1)[2] + image.at<Vec3b>(i, 1)[2] + image.at<Vec3b>(i + 1, 1)[2] + image.at<Vec3b>(i + 1, 0)[2]) / 5;
    }

}


std::vector<uint8_t> arrayimagen;
std::vector<uint8_t> arrayimagen2;

uchar* array2;

void abrirImagen() { // Abre la imagen

    string path = get_current_dir();
    //path = path + "\\ruido.jpg";
    //path = path + "\\coche.jpg";

    path = path + "\\skyline.jpg";
    image = imread(path, IMREAD_COLOR);
    image.convertTo(image, CV_8UC3);

    outputImage = image.clone();
    outputImage2 = image.clone();
    //outputImage3 = image.clone();

}


void bucleInteriorParalelizado(int size, int rank){ //suavizado 5*5, paralelización del bucle interior (se dividen las columnas)
    int rangoBucle1 = floor(image.cols / size);

    int i;
    int inicio3 = 4 + rangoBucle1 * rank;
    int fin = 3 + rangoBucle1 * (rank + 1);

    if (rank + 1 == size) {
        fin = image.cols - 4;
    }



    for (int inicio2 = 4; inicio2 <= image.rows - 4; inicio2++) {
        for (int inicio = inicio3; inicio <= fin; inicio++) {
            for (int z = 0; z <= 2; z++) {

                outputImage.at<Vec3b>(inicio2, inicio)[z] =
                    (int)(image.at<Vec3b>(inicio2 - 2, inicio - 2)[z] + image.at<Vec3b>(inicio2 - 2, inicio - 1)[z] + image.at<Vec3b>(inicio2 - 2, inicio)[z] + image.at<Vec3b>(inicio2 - 2, inicio + 1)[z] + image.at<Vec3b>(inicio2 - 2, inicio + 2)[z]
                        + image.at<Vec3b>(inicio2 - 1, inicio - 2)[z] + image.at<Vec3b>(inicio2 - 1, inicio - 1)[z] + image.at<Vec3b>(inicio2 - 1, inicio)[z] + image.at<Vec3b>(inicio2 - 1, inicio + 1)[z] + image.at<Vec3b>(inicio2 - 1, inicio + 2)[z]
                        + image.at<Vec3b>(inicio2, inicio - 2)[z] + image.at<Vec3b>(inicio2, inicio - 1)[z] + image.at<Vec3b>(inicio2, inicio)[z] + image.at<Vec3b>(inicio2, inicio + 1)[z] + image.at<Vec3b>(inicio2, inicio + 2)[z]
                        + image.at<Vec3b>(inicio2 + 1, inicio - 2)[z] + image.at<Vec3b>(inicio2 + 1, inicio - 1)[z] + image.at<Vec3b>(inicio2 + 1, inicio)[z] + image.at<Vec3b>(inicio2 + 1, inicio + 1)[z] + image.at<Vec3b>(inicio2 + 1, inicio + 2)[z]
                        + image.at<Vec3b>(inicio2 + 2, inicio - 2)[z] + image.at<Vec3b>(inicio2 + 2, inicio - 1)[z] + image.at<Vec3b>(inicio2 + 2, inicio)[z] + image.at<Vec3b>(inicio2 + 2, inicio + 1)[z] + image.at<Vec3b>(inicio2 + 2, inicio + 2)[z]) / 25;
            }
        }
    }
}


void bucleExteriorParalelizado(int size, int rank) {  //suavizado 5*5, paralelización del bucle exterior (se dividen las filas)
    int rangoBucle1 = floor(image.rows / size);

    int i;
    int inicio3 = 4 + rangoBucle1 * rank;
    int fin = 3 + rangoBucle1 * (rank + 1);

    if (rank + 1 == size) {
        fin = image.rows - 4;
    }

    for (int inicio2 = inicio3; inicio2 <= fin; inicio2++) {
        for (int inicio = 4; inicio <= image.cols; inicio++) {
            for (int z = 0; z <= 2; z++) {

                outputImage.at<Vec3b>(inicio2, inicio)[z] =
                    (int)(image.at<Vec3b>(inicio2 - 2, inicio - 2)[z] + image.at<Vec3b>(inicio2 - 2, inicio - 1)[z] + image.at<Vec3b>(inicio2 - 2, inicio)[z] + image.at<Vec3b>(inicio2 - 2, inicio + 1)[z] + image.at<Vec3b>(inicio2 - 2, inicio + 2)[z]
                        + image.at<Vec3b>(inicio2 - 1, inicio - 2)[z] + image.at<Vec3b>(inicio2 - 1, inicio - 1)[z] + image.at<Vec3b>(inicio2 - 1, inicio)[z] + image.at<Vec3b>(inicio2 - 1, inicio + 1)[z] + image.at<Vec3b>(inicio2 - 1, inicio + 2)[z]
                        + image.at<Vec3b>(inicio2, inicio - 2)[z] + image.at<Vec3b>(inicio2, inicio - 1)[z] + image.at<Vec3b>(inicio2, inicio)[z] + image.at<Vec3b>(inicio2, inicio + 1)[z] + image.at<Vec3b>(inicio2, inicio + 2)[z]
                        + image.at<Vec3b>(inicio2 + 1, inicio - 2)[z] + image.at<Vec3b>(inicio2 + 1, inicio - 1)[z] + image.at<Vec3b>(inicio2 + 1, inicio)[z] + image.at<Vec3b>(inicio2 + 1, inicio + 1)[z] + image.at<Vec3b>(inicio2 + 1, inicio + 2)[z]
                        + image.at<Vec3b>(inicio2 + 2, inicio - 2)[z] + image.at<Vec3b>(inicio2 + 2, inicio - 1)[z] + image.at<Vec3b>(inicio2 + 2, inicio)[z] + image.at<Vec3b>(inicio2 + 2, inicio + 1)[z] + image.at<Vec3b>(inicio2 + 2, inicio + 2)[z]) / 25;
            }
        }
    }
}

void dobleBucleParalelizado(int size, int rank) {

    // División del trabajo entre los hilos
    bool hilos_pares = (size % 2) == 0;
    int sizeBucle1 = size / 2;
    int rangoBucle1;
    int rangoBucle2;
    if (size % 2 == 0) {
        rangoBucle1 = floor((image.rows - 1) / (size / 2.0));
        rangoBucle2 = floor(image.cols / 2);
    }
    else {
        rangoBucle1 = floor((image.cols - 1) / floor(size / 2));
        rangoBucle2 = floor(image.cols / (size - floor(size / 2)));
        //std::cout << "rangoBucle2: " << rangoBucle2 << endl;
    }


    int inicio = 4;
    int fin = inicio + rangoBucle1 - 1;
    int inicio2 = 4;
    int fin2 = inicio2 + rangoBucle2 - 1;;

    if (size > 3) {
        if (hilos_pares) {
            if (rank % 2 == 0) {
                inicio = 4;
                inicio += rangoBucle1 * (rank / 2);
                fin = inicio + rangoBucle1 - 1;
                if (fin > image.rows - 4) {
                    fin = image.rows - 4;
                }
                inicio2 = 4;
                fin2 = inicio2 + rangoBucle2 - 1;
            }
            else {
                inicio = 4 + rangoBucle2 * ((rank - 1) / 2);
                fin = inicio + rangoBucle2 - 1;
                if (fin > image.rows - 4) {
                    fin = image.rows - 4;
                }
                inicio2 = inicio2 + rangoBucle2;
                fin2 = image.cols - 4;
            }
        }
        else {
            //int turno = floor(size / 2);
            //if (rank % turno == 0) {
            //    inicio += rangoBucle1 * (rank / 2);
            //    fin = inicio + rangoBucle1 - 1;
            //}

            if (rank % 2 != 0) {
                inicio = 4;
                fin = inicio + image.rows / 2;

                inicio2 = 4 + rangoBucle1 * ((rank - 1) / 2);

                fin2 = inicio2 + rangoBucle1 + rangoBucle1 * ((rank - 1) / 2) - 1;
                if (fin2 > image.cols - 4) {
                    fin2 = image.cols - 4;
                }

            }
            else {
                inicio = (image.rows / 2) + 5;
                fin = image.rows - 4;

                inicio2 = 4 + rangoBucle2 * (rank / 2);
                fin2 = inicio2 + rangoBucle2 - 1;

                if (fin2 > image.cols - 4) {
                    fin2 = image.cols - 4;
                }
            }
        }
    }
    else {
        int rango2 = floor(image.cols / size);
        fin = image.rows - 4;
        inicio2 = 4 + rango2 * rank;

        if (rank == (size - 1)) {
            fin2 = image.cols - 4;
        }
        else {
            fin2 = inicio2 + rango2 - 1;
        }
    }

    //std::cout << "inicio: " << inicio << " fin: " << fin << " inicio2: " << inicio2 << " fin2: " << fin2 << " rank: " << rank << endl;

    for (int x = inicio; x <= fin; x++) {
        for (int y = inicio2; y <= fin2; y++) {
            //if (rank == 2) {
            //    std::cout << "x: " << x << " y: " << y << " rank: " << rank << endl;
            //}
            for (int z = 0; z <= 2; z++) {

                outputImage.at<Vec3b>(x, y)[z] =
                    (int)(image.at<Vec3b>(x - 2, y - 2)[z] + image.at<Vec3b>(x - 2, y - 1)[z] + image.at<Vec3b>(x - 2, y)[z] + image.at<Vec3b>(x - 2, y + 1)[z] + image.at<Vec3b>(x - 2, y + 2)[z]
                        + image.at<Vec3b>(x - 1, y - 2)[z] + image.at<Vec3b>(x - 1, y - 1)[z] + image.at<Vec3b>(x - 1, y)[z] + image.at<Vec3b>(x - 1, y + 1)[z] + image.at<Vec3b>(x - 1, y + 2)[z]
                        + image.at<Vec3b>(x, y - 2)[z] + image.at<Vec3b>(x, y - 1)[z] + image.at<Vec3b>(x, y)[z] + image.at<Vec3b>(x, y + 1)[z] + image.at<Vec3b>(x, y + 2)[z]
                        + image.at<Vec3b>(x + 1, y - 2)[z] + image.at<Vec3b>(x + 1, y - 1)[z] + image.at<Vec3b>(x + 1, y)[z] + image.at<Vec3b>(x + 1, y + 1)[z] + image.at<Vec3b>(x + 1, y + 2)[z]
                        + image.at<Vec3b>(x + 2, y - 2)[z] + image.at<Vec3b>(x + 2, y - 1)[z] + image.at<Vec3b>(x + 2, y)[z] + image.at<Vec3b>(x + 2, y + 1)[z] + image.at<Vec3b>(x + 2, y + 2)[z]) / 25;
            }
        }
    }



}




int main(int argc, char* argv[])
{

    unsigned t0, t1;
    int size = 0;
    int rank = 0;

    abrirImagen(); // se abre la imagen
    t0 = clock(); //Se inicia el temporizador

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Request request;
    MPI_Status status;
             

    // División del trabajo entre los hilos
    bool hilos_pares = (size % 2) == 0;
    int sizeBucle1 = size / 2;
    int rangoBucle1;
    int rangoBucle2;
    if (size % 2 == 0) {
        rangoBucle1 = floor(image.rows / 2.0);
        rangoBucle2 = floor(image.cols / (size/2));
    }
    else {
        rangoBucle1 = floor((image.cols - 1) / floor(size/2));
        rangoBucle2 = floor(image.cols / (size - floor(size / 2)));
        //std::cout << "rangoBucle2: " << rangoBucle2 << endl;
    }


    int inicio = 4;
    int fin = inicio + rangoBucle1 - 1;
    int inicio2 = 4;
    int fin2 = inicio2 + rangoBucle2 - 1;;

    if (size > 3) {
        if (hilos_pares) {
            //if (rank % 2 == 0) {
                if (rank < size / 2) {
                    inicio = 4;
                    fin = image.rows / 2;


                }
                else {
                    inicio = (image.rows / 2)+1;
                    fin = image.rows - 4;
                }
                //inicio += rangoBucle1 * (rank / 2);
                //fin = inicio + rangoBucle1 - 1;
                //if (fin > image.rows -4) {
                //    fin = image.rows - 4;
                //}
                inicio2 = 4 + rangoBucle2 * ((rank) % (size/2));
                fin2 = inicio2 + rangoBucle2 -1 ;// * ((rank +1) % (size/2))
                if (fin2 > image.cols - 4) {
                    fin2 = image.cols - 4;
                }
            //}
            //else {
            //    inicio = 4 + rangoBucle2 * ((rank-1) / 2);
            //    fin = inicio + rangoBucle2 -1;
            //    if (fin > image.rows -4) {
            //        fin = image.rows - 4;
            //    }
            //    inicio2 = inicio2 + rangoBucle2;
            //    fin2 = image.cols - 4;
            //}
        }
        else {
            //int turno = floor(size / 2);
            //if (rank % turno == 0) {
            //    inicio += rangoBucle1 * (rank / 2);
            //    fin = inicio + rangoBucle1 - 1;
            //}

            if (rank % 2 != 0) {
                inicio = 4;
                fin = inicio + image.rows / 2;

                inicio2 = 4 + rangoBucle1 * ((rank-1)/2);

                fin2 = inicio2 + rangoBucle1 + rangoBucle1 * ((rank - 1) / 2) -1;
                if (fin2 > image.cols -4) {
                    fin2 = image.cols - 4;
                }

            }
            else {
                inicio = (image.rows / 2) + 5;
                fin = image.rows - 4;

                inicio2 = 4 + rangoBucle2 * (rank/2);
                fin2 = inicio2 + rangoBucle2 - 1;
                
                if (fin2 > image.cols -4) {
                    fin2 = image.cols - 4;
                }
            }
        }
    }
    else {
        int rango2 = floor(image.cols / size);
        fin = image.rows -4;
        inicio2 = 4 + rango2 * rank;

        if (rank == (size - 1)) {
            fin2 = image.cols - 4;
        }
        else {
            fin2 = inicio2 + rango2 - 1;
        }
    }

    std::cout << "inicio: " << inicio << " fin: " << fin << " inicio2: " << inicio2 << " fin2: " << fin2 << " rank: " << rank << endl;

    for (int x = inicio; x <= fin; x++) {
        for (int y = inicio2; y <= fin2; y++) {
            //if (rank == 2) {
            //    std::cout << "x: " << x << " y: " << y << " rank: " << rank << endl;
            //}
            for (int z = 0; z <= 2; z++) {
                
                outputImage.at<Vec3b>(x, y)[z] =
                    (int)(image.at<Vec3b>(x - 2, y - 2)[z] + image.at<Vec3b>(x - 2, y - 1)[z] + image.at<Vec3b>(x - 2, y)[z] + image.at<Vec3b>(x - 2, y + 1)[z] + image.at<Vec3b>(x - 2, y + 2)[z]
                        + image.at<Vec3b>(x - 1, y - 2)[z] + image.at<Vec3b>(x - 1, y - 1)[z] + image.at<Vec3b>(x - 1, y)[z] + image.at<Vec3b>(x - 1, y + 1)[z] + image.at<Vec3b>(x - 1, y + 2)[z]
                        + image.at<Vec3b>(x, y - 2)[z] + image.at<Vec3b>(x, y - 1)[z] + image.at<Vec3b>(x, y)[z] + image.at<Vec3b>(x, y + 1)[z] + image.at<Vec3b>(x, y + 2)[z]
                        + image.at<Vec3b>(x + 1, y - 2)[z] + image.at<Vec3b>(x + 1, y - 1)[z] + image.at<Vec3b>(x + 1, y)[z] + image.at<Vec3b>(x + 1, y + 1)[z] + image.at<Vec3b>(x + 1, y + 2)[z]
                        + image.at<Vec3b>(x + 2, y - 2)[z] + image.at<Vec3b>(x + 2, y - 1)[z] + image.at<Vec3b>(x + 2, y)[z] + image.at<Vec3b>(x + 2, y + 1)[z] + image.at<Vec3b>(x + 2, y + 2)[z]) / 25;
            }
        }
    }


        //Conversión de Mat a array numérico
        int sizeMat = outputImage.total() * outputImage.elemSize();
        byte* bytes = new byte[sizeMat]; // you will have to delete[] that later
        byte* bytes2 = new byte[sizeMat];

        std::memset(bytes2, 0, sizeMat);

        std::memcpy(bytes, outputImage.data, sizeMat * sizeof(byte));

        //Join del resultado de los hilos en el hilo con la id = 0
        MPI_Reduce(bytes, bytes2, sizeMat , MPI_INTEGER1, MPI_MAX, 0, MPI_COMM_WORLD);




        if (rank == 0) {
            


            //Se para el temporizador
            t1 = clock();
            double time = (double(t1 - t0) / CLOCKS_PER_SEC);
            cout << "Execution Time: " << time << ", " << endl;

            //Reconversión de array numérico a Mat
            outputImage3 = Mat(outputImage.rows, outputImage.cols, CV_8UC3, bytes2).clone();
            

            //imagen original
            image.convertTo(prueba, CV_8UC3);
            imshow("Display window 1", prueba);
            waitKey(0);

            //Imagen resultante
            outputImage3.convertTo(prueba, CV_8UC3);
            imshow("Display window 2", prueba);
            waitKey(0);

        }

    
    MPI_Finalize();
//}
return 0;


}


void mainArreglado(int argc, char* argv[])
{

    int size = 1;
    int rank = 0;


    abrirImagen();
    printf("rows: %d, cols: %d\n", image.rows, image.cols);

    int rangoBucle1 = image.cols / size;

    int i;
    int inicio3 = 2 + rangoBucle1 * rank;
    int fin = inicio3 + rangoBucle1 * (rank + 1) - 4;

    for (int inicio2 = 2; inicio2 <= image.rows - 2; inicio2++) {
        for (int inicio = inicio3; inicio <= fin; inicio++) {
            outputImage.at<Vec3b>(inicio2, inicio)[0] = (int)(image.at<Vec3b>(inicio2 - 1, inicio - 1)[0] + image.at<Vec3b>(inicio2 - 1, inicio)[0] + image.at<Vec3b>(inicio2 - 1, inicio + 1)[0] + image.at<Vec3b>(inicio2, inicio - 1)[0] + image.at<Vec3b>(inicio2, inicio)[0] + image.at<Vec3b>(inicio2, inicio + 1)[0] + image.at<Vec3b>(inicio2 + 1, inicio - 1)[0] + image.at<Vec3b>(inicio2 + 1, inicio)[0] + image.at<Vec3b>(inicio2 + 1, inicio + 1)[0]) / 9;
            outputImage.at<Vec3b>(inicio2, inicio)[1] = (int)(image.at<Vec3b>(inicio2 - 1, inicio - 1)[1] + image.at<Vec3b>(inicio2 - 1, inicio)[1] + image.at<Vec3b>(inicio2 - 1, inicio + 1)[1] + image.at<Vec3b>(inicio2, inicio - 1)[1] + image.at<Vec3b>(inicio2, inicio)[1] + image.at<Vec3b>(inicio2, inicio + 1)[1] + image.at<Vec3b>(inicio2 + 1, inicio - 1)[1] + image.at<Vec3b>(inicio2 + 1, inicio)[1] + image.at<Vec3b>(inicio2 + 1, inicio + 1)[1]) / 9;
            outputImage.at<Vec3b>(inicio2, inicio)[2] = (int)(image.at<Vec3b>(inicio2 - 1, inicio - 1)[2] + image.at<Vec3b>(inicio2 - 1, inicio)[2] + image.at<Vec3b>(inicio2 - 1, inicio + 1)[2] + image.at<Vec3b>(inicio2, inicio - 1)[2] + image.at<Vec3b>(inicio2, inicio)[2] + image.at<Vec3b>(inicio2, inicio + 1)[2] + image.at<Vec3b>(inicio2 + 1, inicio - 1)[2] + image.at<Vec3b>(inicio2 + 1, inicio)[2] + image.at<Vec3b>(inicio2 + 1, inicio + 1)[2]) / 9;
        }
    }

    outputImage.convertTo(prueba, CV_8UC3);
    imshow("Display window 2", prueba);
    waitKey(0);


    image.convertTo(prueba, CV_8UC3);
    imshow("Display window 1", prueba);
    waitKey(0);


}

