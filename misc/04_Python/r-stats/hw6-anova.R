# question 3
names<-character(30)
for(i in 1:30){
  if(i<=10){
    names[i]<-"A"
  }else if(i>10&&i<=20){
    names[i]<-"B"
  }else{
    names[i]<-"C"
  }
}

p<-numeric(20)
count=0
for(i in 1:20){
  r <- rnorm(30) # can change this to t or chisq
  for(j in 1:10){
    r[j]=r[j]+2
  }
  aov.model <- aov(r ~ names)
  x<-summary(aov.model)[[1]][["Pr(>F)"]][[1]]
  x=round(x,2)
  p[i]<-x
  if(x<0.1){
    count=count+1
  }
}

boxplot(p,ylim = c(0, 1))
print(c("reject count", count, "p-avg", sum(p)/20))


# question 5 
asthma<-read.table("./hwdata/asthma.txt",header = T)
attach(asthma)
gfit<-lm(resistance~height)
summary(gfit) # summary table

plot(asthma) # scatter plot 
plot(asthma$height, gfit$residuals) # raw residual plot
qqnorm(gfit$residuals) # raw qq-plot
plot(gfit) # standarized plots



