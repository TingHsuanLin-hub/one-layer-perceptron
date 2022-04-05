#include "matrix.cpp"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;
const int num_classes = 50;
const int num_features = 16;
const int batch_size = 5;

class Perceptron
{
    private:
        void update_weights(double xi[num_features+1], double yi[num_classes],double weight[num_classes][num_features+1]){
            for(int i = 0; i < num_classes; i++){
                for(int j = 0; j < num_features+1; j++){
                    weight[i][j] = weight[i][j] + learning_rate*xi[j]*yi[i];
                }
            }
        }
    public:
        double _weights[50][17] = {0};
        double learning_rate;
        int num_err;
        Perceptron(double lr){
            num_err = 1;
            learning_rate = lr;

        }
        double signum(double x){
            if (x >= 0){
                return 1.0;
            }else{
                return -1.0;
            }
        }
        double * mulMat(double a[num_classes][num_features+1], double b[num_features+1]){
            static double h1[num_classes];
            for(int i=0;i < num_classes;i++){
                h1[i] = 0;
                for(int k=0; k < num_features+1; k++){
                    h1[i] += a[i][k]*b[k];
                }

            }
            return h1;
        }
        void train(double x[], double y[]){
            double y_hat[num_classes];
            for(int i = 0; i < num_classes;i++){
                y_hat[i] = signum(mulMat(_weights,x)[i]);
                if (y[i]*y_hat[i] >= 0){
                    y[i] = 0;
                }else{
                    num_err += 1;
                }
            }
            update_weights(x,y,_weights);
        }
        int predictionclass(double x[], double y[]){
            double prediction[num_classes];
            int max_loc;
            for(int i=0; i < num_classes; i++){
                prediction[i] = mulMat(_weights,x)[i];
                if (prediction[i] > 0){
                    max_loc = i;
                    break;
                }
            }
            return max_loc;
        }

};

double * one_hot(int label){

    // double y[num_classes] = {[0 ... num_classes-1] = -1};
    static double y[num_classes] = {0};
    for(int i = 0; i < num_classes; i++){
        y[i] = -1.0;
    }
    y[label] = 1.0;
    return y;
}

double * feature_extractor(string file){
    // cout << "Handles " << file << "......." << endl;
    Mat img = imread(file,0);
    Mat hist;
    int histSize = 16;
    float range[] = { 0, 256 };
	const float* histRange = { range };
    calcHist(&img, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, true, false);
    static double feature[num_features+1] = {0};
    for (int r =0; r < hist.rows; r++){
        feature[r] = hist.at<float>(r,0); 
    }
    feature[-1] = 1.0;
    return feature; 
}


int main(){
    int epochs = 100;
    Perceptron classifier(0.01);
    for(int epoch = 0; epoch < epochs,classifier.num_err>0; epoch++){
        ifstream train_dataset("train.txt", std::ios::in);
        ifstream validation_dataset("val.txt", std::ios::in);
        ifstream test_dataset("test.txt",std::ios::in);
        if (!train_dataset.is_open()) {
            cout << "Failed to open file.\n";
        } else {
            string name;
            int score;
            //Train Stage
            int count = 0;
            double *x_train;
            double *y_train;
            while (train_dataset >> name >> score) {
                // cout << name << " " << score << "\n";
                x_train = feature_extractor(name);
                y_train = one_hot(score);
                classifier.train(x_train,y_train);
                count ++;
            }
            cout << "Iteration #" << epoch << " Weights:" <<endl; 
            for (int i = 0; i < num_classes;i++){
                for(int j = 0; j < num_features+1;j++){
                    cout << classifier._weights[i][j] << " ";  
                }
                cout << "\n";
            }
            //Validation Stage
            count = 0;
            double *x_val;
            double *y_val;
            int predict;
            while (validation_dataset >> name >> score) {
                cout << name << " " << score << "\n";
                x_val = feature_extractor(name);
                y_val = one_hot(score);
                predict = classifier.predictionclass(x_val,y_val);
                cout << name << "is label #" <<  predict << endl;
                count ++;
            
            }

            //Test Stage
            // count = 0;
            // double *x_test;
            // double *y_test;
            // int predict;
            // while (test_dataset >> name >> score) {
            //     cout << name << " " << score << "\n";
            //     x_test = feature_extractor(name);
            //     y_test = one_hot(score);
            //     predict = classifier.predictionclass(x_test,y_test);
            //     cout << name << "is label #" <<  predict << endl;
            //     count ++;
            
            // }
            
            train_dataset.close();
            validation_dataset.close();
            test_dataset.close();
        }
        train_dataset.close();
        validation_dataset.close();
        test_dataset.close();
    }
    
    

    return 0;
}
