#include <iostream>
#include <vector>
 
using namespace std;
class Matrix{
    private:
        int row;
        int column;
    public:
        vector< vector<double> > matrix;
        Matrix(){
            row = 0;
            column = 0;
        }
        Matrix(int rows, int columns, double init_val=0.0){
            row = rows;
            column = columns;
            vector<double> row;
            row.assign(columns,init_val);//配置一個 row 的大小
            matrix.assign(rows,row);//配置2維
        }
        Matrix(int rows, int columns, vector<double> matrix_1d){
            row = rows;
            column = columns;
            matrix.resize(row);
            for(int i =0;i < rows; i++){
                matrix[i].resize(column);
            }
            for (int i =0; i < matrix_1d.size(); i++){
                int height = i / column;
                int width = i % row;
                matrix[height][width] = matrix_1d[i];
            }
        }
        int getrow(){
            return row;
        }
        int getcolumn(){
            return column;
        }
        void printmatrix(){
            for(int i=0;i<row;++i){
                for(int j=0;j<column;++j){
                    cout<<matrix[i][j]<<' ';
                }    
            cout<<endl;
            }
        }
        
        void setmatrix(){
            double entry;
            cout << "Please Enter " << (row*column) << " entry." << endl;
            for (auto &item : matrix) {
                for (auto &item1 : item) {
                    cin >> entry;
                    item1 = entry;
                    //cout  << item1 << ' ';
                }
            }
        }
        void setmatrix(int rows, int columns, double init_val=0.0){
            row = rows;
            column = columns;
            vector<double> row;
            row.assign(columns,init_val);//配置一個 row 的大小
            matrix.assign(rows,row); 
        }

        void transpose(){
            vector<vector<double> > trans_vec(column, vector<double>());
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < column; j++)
                {
                    trans_vec[j].push_back(matrix[i][j]);
                }
            }
            int tmp = row;
            row =column;
            column = tmp;
            matrix = trans_vec;    // <--- reassign here
        }
        
}; 

Matrix mulMat(Matrix former, Matrix later){
    if (former.getcolumn()==1 && later.getcolumn()==1){

    }else if (later.getcolumn()==1)
    {
        /* code */
    }else{

    }
    
    return former;

}
// Edit MACROs here, according to your Matrix Dimensions for mat1[R1][C1] and mat2[R2][C2]
// #define R1 4            // number of rows in Matrix-1
// #define C1 4            // number of columns in Matrix-1
// #define R2 4            // number of rows in Matrix-2
// #define C2 4            // number of columns in Matrix-2
 
// void mulMat(double mat1[][C1], double mat2[][C2]) {
//     // R1 = sizeof(mat1)/sizeof(mat1[0]);
//     // C1 = sizeof(mat1[0])/sizeof(double)
//     // R2 = sizeof(mat2)/sizeof(mat2[0]);
//     // C2 = sizeof(mat2[0])/sizeof(double);
//     int rslt[R1][C2];
 
//     cout << "Multiplication of given two matrices is:\n" << endl;
 
//     for (int i = 0; i < R1; i++) {
//         for (int j = 0; j < C2; j++) {
//             rslt[i][j] = 0;
 
//             for (int k = 0; k < R2; k++) {
//                 rslt[i][j] += mat1[i][k] * mat2[k][j];
//             }
 
//             cout << rslt[i][j] << "\t";
//         }
 
//         cout << endl;
//     }
// }