// Suavizado.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

//#include <opencv2/core.hpp>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui.hpp>
#define _CRT_SECURE_NO_WARNINGS




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


void abrirImagen() {

    image = imread("skyline.jpg", IMREAD_COLOR);
    image.convertTo(image, CV_8UC3);

    outputImage = image.clone();

}

void calcularBorde() {

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

void calcularCuerpo() {

    //calcular la matriz sin los bordes

    for (int x = 1; x <= image.rows - 2; x++) {
        for (int y = 1; y <= image.cols - 2; y++) {
            outputImage.at<Vec3b>(x, y)[0] = (int)(image.at<Vec3b>(x - 1, y - 1)[0] + image.at<Vec3b>(x - 1, y)[0] + image.at<Vec3b>(x - 1, y + 1)[0] + image.at<Vec3b>(x, y - 1)[0] + image.at<Vec3b>(x, y + 1)[0] + image.at<Vec3b>(x + 1, y - 1)[0] + image.at<Vec3b>(x + 1, y)[0] + image.at<Vec3b>(x + 1, y + 1)[0]) / 8;
            outputImage.at<Vec3b>(x, y)[1] = (int)(image.at<Vec3b>(x - 1, y - 1)[1] + image.at<Vec3b>(x - 1, y)[1] + image.at<Vec3b>(x - 1, y + 1)[1] + image.at<Vec3b>(x, y - 1)[1] + image.at<Vec3b>(x, y + 1)[1] + image.at<Vec3b>(x + 1, y - 1)[1] + image.at<Vec3b>(x + 1, y)[1] + image.at<Vec3b>(x + 1, y + 1)[1]) / 8;
            outputImage.at<Vec3b>(x, y)[2] = (int)(image.at<Vec3b>(x - 1, y - 1)[2] + image.at<Vec3b>(x - 1, y)[2] + image.at<Vec3b>(x - 1, y + 1)[2] + image.at<Vec3b>(x, y - 1)[2] + image.at<Vec3b>(x, y + 1)[2] + image.at<Vec3b>(x + 1, y - 1)[2] + image.at<Vec3b>(x + 1, y)[2] + image.at<Vec3b>(x + 1, y + 1)[2]) / 8;
            //cout << "X: " << x << " Y: " << y << " Antes: " << image.at<Vec3b>(x, y) << " Después: " << outputImage.at<Vec3b>(x, y) << endl;
        }
    }

}


int main(int argc, char* argv[])
{


    int size;
    int rank;


    abrirImagen();
    printf("rows: %d, cols: %d\n", image.rows, image.cols);
    // calcularBorde();
    //calcularCuerpo();


    //for (int x = 1; x <= image.rows - 2; x++) {
    //    for (int y = 1; y <= image.cols - 2; y++) {
    //        outputImage.at<Vec3b>(x, y)[0] = (int)(image.at<Vec3b>(x - 1, y - 1)[0] + image.at<Vec3b>(x - 1, y)[0] + image.at<Vec3b>(x - 1, y + 1)[0] + image.at<Vec3b>(x, y - 1)[0] + image.at<Vec3b>(x, y + 1)[0] + image.at<Vec3b>(x + 1, y - 1)[0] + image.at<Vec3b>(x + 1, y)[0] + image.at<Vec3b>(x + 1, y + 1)[0]) / 8;
    //        outputImage.at<Vec3b>(x, y)[1] = (int)(image.at<Vec3b>(x - 1, y - 1)[1] + image.at<Vec3b>(x - 1, y)[1] + image.at<Vec3b>(x - 1, y + 1)[1] + image.at<Vec3b>(x, y - 1)[1] + image.at<Vec3b>(x, y + 1)[1] + image.at<Vec3b>(x + 1, y - 1)[1] + image.at<Vec3b>(x + 1, y)[1] + image.at<Vec3b>(x + 1, y + 1)[1]) / 8;
    //        outputImage.at<Vec3b>(x, y)[2] = (int)(image.at<Vec3b>(x - 1, y - 1)[2] + image.at<Vec3b>(x - 1, y)[2] + image.at<Vec3b>(x - 1, y + 1)[2] + image.at<Vec3b>(x, y - 1)[2] + image.at<Vec3b>(x, y + 1)[2] + image.at<Vec3b>(x + 1, y - 1)[2] + image.at<Vec3b>(x + 1, y)[2] + image.at<Vec3b>(x + 1, y + 1)[2]) / 8;
    //        //cout << "X: " << x << " Y: " << y << " Antes: " << image.at<Vec3b>(x, y) << " Después: " << outputImage.at<Vec3b>(x, y) << endl;
    //    }
    //}


    bool hilos_pares = (size % 2) == 0;
    int rangoBucle1;
    int rangoBucle2;
    if (size % 2 == 0) {
        rangoBucle1 = floor((image.cols - 1) / (size / 2.0));
        rangoBucle2 = floor(image.rows / 2);
    }
    else {
        rangoBucle1 = floor((image.cols - 1) / 2.0);
        rangoBucle2 = floor((image.rows / 2) / ceil(size / 2.0));
        //std::cout << "rangoBucle2: " << rangoBucle2 << endl;
    }

    int i;
    int inicio = 2;
    int fin = inicio + rangoBucle1 - 1;
    int inicio2 = 2;
    int fin2 = inicio2 + rangoBucle2 - 1;;


    for (i = 0; i < size; i++) {

        if (size > 3) {
            if (hilos_pares) {
                if (i % 2 == 0) {
                    inicio = 2;
                    inicio += rangoBucle1 * (i / 2) - 1;
                    fin = inicio + rangoBucle1 - 2;
                    inicio2 = 2;
                    fin2 = inicio2 + rangoBucle2 - 1;
                }
                else {
                    inicio2 = inicio2 + rangoBucle2 - 1;
                    fin2 = image.rows - 2;
                }
            }
            else {
                int turno = floor(size / 2);
                if (i % turno == 0) {
                    inicio += rangoBucle1 * (i / 2) - 1;
                    fin = inicio + rangoBucle1 - 2;
                }

                if (i % 2 == 0) {
                    inicio2 = 2;
                    fin2 = inicio2 + rangoBucle2 - 1;
                }
                else {
                    if (rank != size - 1) {
                        inicio2 = inicio2 + rangoBucle2 - 1;
                        fin2 = inicio2 + rangoBucle2 - 2;
                    }
                }
            }
        }
        else {
            int rango2 = floor(image.rows / size);
            fin = image.cols - 2;
            inicio2 = 2 + rango2 * rank - 1;

            if (rank == (size - 1)) {
                fin2 = image.rows - 2;
            }
            else {
                fin2 = inicio2 + rango2 - 2;
            }
        }

        if (i == rank) {

            if (rank == size - 1) {
                inicio = 2;
                fin = image.cols - 2;
                inicio2 = 2 + floor(size / 2.0) * rangoBucle2 - 1;
                fin2 = image.rows - 2;
            }
            printf("inicio: %d, fin: %d, inicio2: %d, fin2: %d, rank: %d\n", inicio, fin, inicio2, fin2, rank);
            cout << "hola";
            int j;

            for (inicio2; inicio2 <= fin2; inicio2++) {
                for (j = inicio; j <= fin; j++) {
                    outputImage.at<Vec3b>(inicio2, j)[0] = (int)(image.at<Vec3b>(inicio2 - 1, j - 1)[0] + image.at<Vec3b>(inicio2 - 1, j)[0] + image.at<Vec3b>(inicio2 - 1, j + 1)[0] + image.at<Vec3b>(inicio2, j - 1)[0] + image.at<Vec3b>(inicio2, j + 1)[0] + image.at<Vec3b>(inicio2 + 1, j - 1)[0] + image.at<Vec3b>(inicio2 + 1, j)[0] + image.at<Vec3b>(inicio2 + 1, j + 1)[0]) / 8;
                    outputImage.at<Vec3b>(inicio2, j)[1] = (int)(image.at<Vec3b>(inicio2 - 1, j - 1)[1] + image.at<Vec3b>(inicio2 - 1, j)[1] + image.at<Vec3b>(inicio2 - 1, j + 1)[1] + image.at<Vec3b>(inicio2, j - 1)[1] + image.at<Vec3b>(inicio2, j + 1)[1] + image.at<Vec3b>(inicio2 + 1, j - 1)[1] + image.at<Vec3b>(inicio2 + 1, j)[1] + image.at<Vec3b>(inicio2 + 1, j + 1)[1]) / 8;
                    outputImage.at<Vec3b>(inicio2, j)[2] = (int)(image.at<Vec3b>(inicio2 - 1, j - 1)[2] + image.at<Vec3b>(inicio2 - 1, j)[2] + image.at<Vec3b>(inicio2 - 1, j + 1)[2] + image.at<Vec3b>(inicio2, j - 1)[2] + image.at<Vec3b>(inicio2, j + 1)[2] + image.at<Vec3b>(inicio2 + 1, j - 1)[2] + image.at<Vec3b>(inicio2 + 1, j)[2] + image.at<Vec3b>(inicio2 + 1, j + 1)[2]) / 8;
                }
                //std::cout << "inicio: " << inicio << " fin: " << fin << " rank: " << rank << endl;
            }
        }

    }
    //MPI_Reduce(&outputImage2, &outputImage3, outputImage.rows * outputImage.cols / 8, MPI_INTEGER1, MPI_BAND, 0, MPI_COMM_WORLD);

    //if (rank == 0) {
    //    imprimirPrimos(primos2);
    //}


    image.convertTo(prueba, CV_8UC3);
    imshow("Display window 1", prueba);
    waitKey(0);

    outputImage3.convertTo(prueba, CV_8UC3);
    imshow("Display window 2", prueba);
    waitKey(0);


    //for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    //{
    //    blur(image, pruebaOpernCV, Size(i, i), Point(-1, -1));
    //}

    //pruebaOpernCV.convertTo(pruebaOpernCV, CV_8UC3);
    //imshow("Display window 3", pruebaOpernCV);
    //waitKey(0);

}

