# 1.f 
N <- 10000
z <- c(N)
g <- c(N)
for(i in 1:N){
  z[i]<-sum(rcauchy(i))/N
  g[i]<-sum(rnorm(i))/N
}
print(g)
plot(g)
plot(z)

# 7.c

pfunc <- function(n, mu, sig, rep) {
  p_arr<-c(rep)
  count=0
  for(i in 1:rep){
    x_bar=sum(rnorm(n,mu,sig^2))/n
    z=abs((x_bar-mu)*sqrt(n)/sig)
    if(sig==1 && mu==0){
      z=abs(sqrt(n)*x_bar)
    }
    p_val=2*(1-pnorm(z))
    p_arr[i]<-p_val
    if(p_val<0.05){
      count=count+1
    }
    
  }
  if(rep==1){
    print(p_val)
  }
  print(count)
  plot(p_arr, ylim=c(-1,4))
  
}
pfunc(100, 0, 1, 1)

