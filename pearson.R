rm(list = ls())
gc()
library(dplyr)

path         <- "F:\\Ders\\Ders - Yüksek Lisans\\Machine Learning\\hw4\\netflix\\TrainingRatings.txt"
mydata       <- read.csv(path, header = FALSE)

distinct_user <- mydata %>% group_by(V2) %>%  summarise(n =n()) 
distinct_film <- mydata %>% group_by(V1) %>%  summarise(n =n()) 

distinct_film$n     <- 1:dim(distinct_film)[1]
distinct_user$n     <- 1:dim(distinct_user)[1]

matris <- matrix(0,ncol = dim(distinct_film)[1], nrow = dim(distinct_user)[1])

Rcpp::sourceCpp('deneme.cpp')
matris <- basic_function(matris, mydata, distinct_film, distinct_user)

meanUsers    <- rowMeans(matris)
weightMatrix <- matrix(0, nrow = dim(distinct_user)[1] / 3, ncol = dim(distinct_user)[1])
weightMatrix <- pearson(weightMatrix , matris , meanUsers)
