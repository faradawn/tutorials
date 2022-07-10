data <- read.table("calcium.txt", header=TRUE)
oxalate <- log(data[,1])
flame <- log(data[,2])

control <- read.table("ozonecontrol.txt", header=TRUE)[,1]
treat <- read.table("ozonetreat.txt", header=TRUE)[,1]

t_test <- function(X_arr, Y_arr, paired=0){
  alpha=0.05
  X_bar <- mean(X_arr)
  Y_bar <- mean(Y_arr)
  n1 <- length(X_arr)
  n2 <- length(Y_arr)
  s1 <- sqrt(sum((X_arr-X_bar)^2)/(n1-1))
  s2 <- sqrt(sum((Y_arr-Y_bar)^2)/(n2-1))
  sp <- sqrt(((n1-1)*s1^2+(n2-1)*s2^2)/(n1+n2-2))
  t <- (X_bar-Y_bar)/(sp*sqrt(1/n1 + 1/n2))
  df <- n1+n2-2
  p_val <- 2*(1-pt(abs(t), df))
  
  if(paired){
    D_arr <- X_arr-Y_arr
    D_bar <- mean(D_arr)
    S_D <- sqrt(sum((X_arr-Y_arr-X_bar+Y_bar)^2)/(n1-1))
    t <-(X_bar-Y_bar)/S_D
    df <- (n1-1)
    p_val <- 2*(1-pt(abs(t), df))
    r <- sum((X_arr-X_bar)*(Y_arr-Y_bar))/(s1*sqrt(n1-1)*s2*sqrt(n2-1))
    z_prime <- log((1+r)/(1-r))/2
    SE <- qnorm(1-alpha/2)*1/sqrt(n1-1)
    L<-z_prime-SE
    R<-z_prime+SE
    Lb <- (exp(2*L)-1)/(exp(2*L)+1)
    Rb <- (exp(2*R)-1)/(exp(2*R)+1)
    
    print(c("paired S_D", S_D))
    print(c("correlation", r))
    print(c("C.I. for correlation", Lb, Rb))
  }else{
    print(c("pooled sp", sp))
  }
  
  print(c("t", t))
  print(c("df", df))
  print(c("p_val", p_val))
  
}

t_test(oxalate, flame, 1)

# question 5: test for equal variance

var.test(control, treat, alternative = "two.sided") # p-val=0.0049, reject H0

welch_test <- function(X_arr, Y_arr){
  alpha=0.05
  X_bar <- mean(X_arr)
  Y_bar <- mean(Y_arr)
  n1 <- length(X_arr)
  n2 <- length(Y_arr)
  s1 <- sqrt(sum((X_arr-X_bar)^2)/(n1-1))
  s2 <- sqrt(sum((Y_arr-Y_bar)^2)/(n2-1))
  nu <- (s1^2/n1+s2^2/n2)^2/(s1^4/(n1*(n1-1)) + s2^4/(n2*(n2-1)))
  t <- (X_bar-Y_bar)/sqrt(s1^2/n1 + s2^2/n2)
  df <- nuX
  p_val <- 2*(1-pt(abs(t), df))
  print(c("t", t))
  print(c("df", df))
  print(c("p_val", p_val))
  
}

welch_test(control, treat)


