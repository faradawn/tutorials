# Question 3 (Rice 14-39)
tank<-read.csv("./hwdata/hw7-tankvolume.txt", header=T, sep='\t')
volume<-tank$X.Volume.
pressure<-tank$X.Pressure.
lm_tank<-lm(pressure~volume)
summary(lm_tank)
plot(volume,pressure)
lines(volume, lm_tank$fitted.values)
# plot(volume, lm_tank$residuals)

volume_sqr<-volume^2
lm_tank_quadratic<-lm(pressure~volume+volume_sqr)
summary(lm_tank_quadratic)
# plot(volume, lm_tank_quadratic$residuals)
plot(volume,pressure)
lines(volume, lm_tank_quadratic$fitted.values, col="green")

plot(volume, lm_tank$residuals)



# Question 4 (Rice 14-40)
ring<-read.csv("./hwdata/hw7-provingring.txt", header=TRUE, sep = "\t")
load<-ring$X.Load.
deflect<-ring$X.Deflection.
load_sqr<-load^2
lm1<-lm(deflect~load)
plot(load,deflect)
lines(load, lm1$coefficients[1] + load*lm1$coefficients[2], col="blue")
# quadratic
lm2<-lm(deflect~load+load_sqr)
plot(load,deflect)
lines(load, lm2$fitted.values, col="green")
plot(load,lm2$residuals)
summary(lm2)
plot(lm2)



# Question 5: two data sets 
as<-read.csv("./hwdata/asthma.txt", header=T, sep='\t') # 42 rows
cy<-read.csv("./hwdata/hw7-cystfibr.txt", header=T, sep='\t') # 24 rows

z<-c(rep(0,42), rep(1,24))
height<-c(as$height, cy$X.height.)
resist<-c(as$resistance, cy$X.resistance.)

# Four t-test
lm5<-lm(resist ~ height + z + I(height*z))
summary(lm5)

## F-test between two models
lm5_small<-lm(resist ~ height)
anova(lm5_small, lm5)
plot(lm5$fitted.values, lm5$residuals)



# Question 6: Quadratic model
ring<-read.csv("./hwdata/hw7-provingring.txt", header=TRUE, sep = "\t")
load<-ring$X.Load.
deflect<-ring$X.Deflection.
lm6_1<-lm(deflect ~ load + I(load^2) + I(load^3) + I(load^4))
mean<-mean(load)
lm6_2<-lm(deflect ~ I(load-mean) + I((load-mean)^2) + I((load-mean)^3) + I((load-mean)^4))
summary(lm6_2)



# Question 7: Mann-Whitney 
MA<-read.csv("./hwdata/hw7-methodA.txt")
MB<-read.csv("./hwdata/hw7-methodB.txt")
t.test(MA, MB, alternative = "two.sided", var.equal = TRUE)
wilcox.test(MA$methodA, MB$methodB)


