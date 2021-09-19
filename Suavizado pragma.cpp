#include <iostream>
#include <vector>
#include <stdio.h>

#include <omp.h>

#include <windows.h>
#include <string>

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\imgproc.hpp>

#include <iostream>
#include <tchar.h>
#include <direct.h>
#include <ctime> 

#define GetCurrentDir _getcwd


using namespace cv;
using namespace std;

Mat image;
Mat outputImage;
Mat pruebaOpernCV;
Mat outputImage2;
Mat outputImage3;
int filas;
int columnas;



std::string get_current_dir() {
    char buff[FILENAME_MAX]; //create string buffer to hold path
    GetCurrentDir(buff, FILENAME_MAX);
    string current_working_dir(buff);
    return current_working_dir;
}




void abrirImagenBYN() { //abrir imagen en blanco y negro
    string path = get_current_dir();
    //path = path + "\\skyline.jpg";
    path = path + "\\monte.png";
    //path = path + "\\coche.jpg";
    image = imread(path, IMREAD_GRAYSCALE);
    image.convertTo(image, CV_8UC1);

    outputImage = image.clone();

}

void preparacionAGris() {
    abrirImagenBYN();
    string path = get_current_dir();
    path = path + "\\skyline.jpg";
    //path = path + "\\monte.png";
    //path = path + "\\coche.jpg";
    image = imread(path, IMREAD_COLOR);
    image.convertTo(image, CV_8UC3);
}


void suavizadoPromedio3() { //Suavizado de 3*3
#pragma omp parallel for
    for (int x = 1; x <= image.rows - 2; x++) {
        for (int y = 1; y <= image.cols - 2; y++) {
            for (int z = 0; z <= 2; z++) {
                outputImage.at<Vec3b>(x, y)[z] = (int)(
                    image.at<Vec3b>(x - 1, y - 1)[z] + image.at<Vec3b>(x - 1, y)[z] + image.at<Vec3b>(x - 1, y + 1)[z] + 
                    image.at<Vec3b>(x, y - 1)[z] + image.at<Vec3b>(x, y + 1)[z] + image.at<Vec3b>(x + 1, y - 1)[z] + 
                    image.at<Vec3b>(x + 1, y)[z] + image.at<Vec3b>(x + 1, y + 1)[z] + image.at<Vec3b>(x, y)[z]) / 9;
                
            }

        }
    }
}


void suavizadoPromedio3BYN() { //Suavizado de 3*3 en blanco y negro
#pragma omp parallel for
    for (int x = 1; x <= image.rows - 2; x++) {
        for (int y = 1; y <= image.cols - 2; y++) {
                outputImage.at<uchar>(x, y) = (int)((int)image.at<uchar>(x - 1, y - 1) + (int)image.at<uchar>(x - 1, y) + (int)image.at<uchar>(x - 1, y + 1) + (int)image.at<uchar>(x, y - 1) + (int)image.at<uchar>(x, y + 1) + (int)image.at<uchar>(x + 1, y - 1) + (int)image.at<uchar>(x + 1, y) + (int)image.at<uchar>(x + 1, y + 1) + (int)image.at<uchar>(x, y)) / 9;
        }
    }
}

void suavizadoPromedio5() {//Suavizado de 5*5

    for (int x = 3; x <= image.rows - 4; x++) {
        #pragma omp parallel for num_threads(6)
        for (int y = 3; y <= image.cols - 4; y++) {
            for (int z = 0; z <= 2; z++) {

                outputImage.at<Vec3b>(x, y)[z] =
                    (int)(image.at<Vec3b>(x - 2, y - 2)[z] + image.at<Vec3b>(x - 2, y - 1)[z] + image.at<Vec3b>(x - 2, y)[z] + image.at<Vec3b>(x - 2, y + 1)[z] + image.at<Vec3b>(x - 2, y + 2)[z]
                        + image.at<Vec3b>(x - 1, y - 2)[z] + image.at<Vec3b>(x - 1, y - 1)[z] + image.at<Vec3b>(x - 1, y)[z] + image.at<Vec3b>(x - 1, y + 1)[z] + image.at<Vec3b>(x - 1, y + 2)[z]
                        + image.at<Vec3b>(x, y - 2)[z]     + image.at<Vec3b>(x, y - 1)[z]     + image.at<Vec3b>(x, y)[z]     + image.at<Vec3b>(x, y + 1)[z]     + image.at<Vec3b>(x, y + 2)[z]
                        + image.at<Vec3b>(x + 1, y - 2)[z] + image.at<Vec3b>(x + 1, y - 1)[z] + image.at<Vec3b>(x + 1, y)[z] + image.at<Vec3b>(x + 1, y + 1)[z] + image.at<Vec3b>(x + 1, y + 2)[z]
                        + image.at<Vec3b>(x + 2, y - 2)[z] + image.at<Vec3b>(x + 2, y - 1)[z] + image.at<Vec3b>(x + 2, y)[z] + image.at<Vec3b>(x + 2, y + 1)[z] + image.at<Vec3b>(x + 2, y + 2)[z]) / 25;

            }
        }
    }
}

void conversionAGris() { //Conversión de imagen a blanco y negro

    for (int x = 1; x <= image.rows - 2; x++) {
        #pragma omp parallel for num_threads(6)
        for (int y = 1; y <= image.cols - 2; y++) {
            outputImage.at<uchar>(x, y*3) = (int)image.at<Vec3b>(x, y)[0] * 0.1140 + (int)image.at<Vec3b>(x, y)[1] * 0.5870 + (int)image.at<Vec3b>(x, y)[2] * 0.2989;
            outputImage.at<uchar>(x, y*3 +1) = (int)image.at<Vec3b>(x, y)[0] * 0.1140 + (int)image.at<Vec3b>(x, y)[1] * 0.5870 + (int)image.at<Vec3b>(x, y)[2] * 0.2989;
            outputImage.at<uchar>(x, y*3 +2) = (int)image.at<Vec3b>(x, y)[0] * 0.1140 + (int)image.at<Vec3b>(x, y)[1] * 0.5870 + (int)image.at<Vec3b>(x, y)[2] * 0.2989;
        }
    }

}

void suavizadoGauss5() { //suavizado de 5*5 con matriz de gauss
    for (int x = 3; x <= image.rows - 4; x++) {
        for (int y = 3; y <= image.cols - 4; y++) {
            for (int z = 0; z <= 2; z++) {

                outputImage.at<Vec3b>(x, y)[z] =
                    (int)(image.at<Vec3b>(x - 2, y - 2)[z]     + image.at<Vec3b>(x - 2, y - 1)[z] * 4  + image.at<Vec3b>(x - 2, y )[z] * 7  + image.at<Vec3b>(x - 2, y + 1)[z] * 4  + image.at<Vec3b>(x - 2, y + 2)[z]
                        + image.at<Vec3b>(x - 1, y - 2)[z] * 4 + image.at<Vec3b>(x - 1, y - 1)[z] * 16 + image.at<Vec3b>(x - 1, y)[z] * 26 + image.at<Vec3b>(x - 1, y + 1)[z] * 16 + image.at<Vec3b>(x - 1, y + 2)[z] * 4
                        + image.at<Vec3b>(x, y - 2)[z] * 7     + image.at<Vec3b>(x , y - 1)[z] * 26     + image.at<Vec3b>(x, y)[z] * 41     + image.at<Vec3b>(x, y + 1)[z] * 16     + image.at<Vec3b>(x, y + 2)[z] * 7
                        + image.at<Vec3b>(x + 1, y - 2)[z] * 4 + image.at<Vec3b>(x + 1, y - 1)[z] * 16 + image.at<Vec3b>(x + 1, y)[z] * 26 + image.at<Vec3b>(x + 1, y + 1)[z] * 16 + image.at<Vec3b>(x + 1, y + 2)[z] * 4
                        + image.at<Vec3b>(x + 2, y - 2)[z]     + image.at<Vec3b>(x + 2, y - 1)[z] * 4  + image.at<Vec3b>(x + 2, y)[z] * 7  + image.at<Vec3b>(x + 2, y + 1)[z] * 4  + image.at<Vec3b>(x + 2, y + 2)[z]) / 273;

            }
        }
    }
}

void abrirImagen() {
    string path = get_current_dir();
    path = path + "\\coche.jpg";
    //path = path + "\\monte.png";
    //path = path + "\\coche.jpg";
    //path = path + "\\MapaMundi_110.png";
    //path = path + "\\panorama.jpg";
    //path = path + "\\Tierra.jpg";

    //path = path + "\\panorama.jpg";
    image = imread(path, IMREAD_COLOR);
    image.convertTo(image, CV_8UC3);

    outputImage = image.clone();

}


int main(int argc, char* argv[])
{
    unsigned t0, t1;
    
    abrirImagen();

    for (int w = 0; w < 5; w++) { // ejecución del código 5 veces

        t0 = clock();
        int count = 0;
#pragma omp parallel for num_threads(2)
        for (int x = 3; x <= image.rows - 4; x++) {
            #pragma omp parallel for num_threads(2)
            for (int y = 3; y <= image.cols - 4; y++) {
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


        t1 = clock();
        double time = (double(t1 - t0) / CLOCKS_PER_SEC);
        cout << "Execution Time: " << time << ", " << endl;
    }

    try {

      //image.convertTo(prueba, CV_8UC3); //Solo a color
      //imshow("Display window 1", prueba); //Solo a color


      imshow("Display window 1", image);
      waitKey(0);


      //outputImage.convertTo(prueba, CV_8UC3); //Solo a color
      //imshow("Display window 2", prueba); //Solo a color
      imshow("Display window 2", outputImage); //gris
      waitKey(0);
    } catch (cv::Exception& ex) {
        cerr << "opencv exception: " +ex.err << endl;
    }
}


//startWindowThread();
//namedWindow("preview 2");