#include <Rcpp.h>
using namespace Rcpp;
using namespace std;

// This is a simple example of exporting a C++ function to R. You can
// source this function into an R session using the Rcpp::sourceCpp 
// function (or via the Source button on the editor toolbar). Learn
// more about Rcpp at:
//
//   http://www.rcpp.org/
//   http://adv-r.had.co.nz/Rcpp.html
//   http://gallery.rcpp.org/
//

// [[Rcpp::export]]

NumericMatrix pearson(NumericMatrix weightMatrix, NumericMatrix puanMatrisi, NumericVector meanUsers){
  
  int row = weightMatrix.rows();
  int i,j;
  int filmSayisi = puanMatrisi.cols();
  
  
  for(i=0; i< row; i++){  
    for(j=0; j < row ; j++){
      
      double ra = 0;
      double ru = 0;
      double sum_ra2 = 0;
      double sum_ru2 = 0;
      double ra_ru  = 0;
      
      
      //matris simetrik olduğu için diğer yarısını hesaplamaya gerek yok
      if(j > i){
      
        for(int k = 0; k < filmSayisi; k++){
        
          if(puanMatrisi(j,k) > 0 && puanMatrisi(i,k) > 0){
          
            ra = puanMatrisi(i,k) - meanUsers[i];
            ru = puanMatrisi(j,k) - meanUsers[j];
            ra_ru    += ra * ru;
            sum_ra2  += ra * ra;
            sum_ru2  += ru * ru;
            
          }
        }
      }
      if(ra > 0){
        weightMatrix(i,j) = ra_ru / sqrt(sum_ra2 * sum_ru2);
        weightMatrix(j,i) = weightMatrix(i,j);
      }
     
        
        
    }
    
    Rcpp::Rcout << "i is: " << i;
    Rcpp::Rcout << "\n";
    
    
    
  }
  
  
  
  return weightMatrix;
}










NumericMatrix basic_function(NumericMatrix matriks, DataFrame df, DataFrame df_film, DataFrame df_user) {
  
  int nrow = df.nrows();
  
  NumericVector mydata_V1 = df["V1"];
  NumericVector mydata_V2 = df["V2"];
  NumericVector mydata_V3 = df["V3"];
  
  NumericVector user_V2 = df_user["V2"];
  NumericVector user_N  = df_user["n"];
  
  NumericVector film_V1 = df_film["V1"];
  NumericVector film_N  = df_film["n"];
  
  int user_id     = 0;
  int user_index  = 0;
  int film_id     = 0;
  int film_index  = 0;
  int j = 0;
  
  for (int i = 0; i < nrow ; i++) {
    
    j = 0;
    user_id  = mydata_V2[i];
    while(user_id != user_V2[j]){
      j++;
    }
    user_index = user_N[j] - 1;
    
    
    j = 0;
    film_id  = mydata_V1[i];
    while(film_id != film_V1[j]){
      j++;
    }
    film_index = film_N[j] - 1;
      
      
    matriks(user_index,film_index) = mydata_V3[i];
  
  }
  
  return matriks;
}







// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically 
// run after the compilation.
//

/*** R
weightMatrix <- pearson(weightMatrix , matris , meanUsers)

*/
