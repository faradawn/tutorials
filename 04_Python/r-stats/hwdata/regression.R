#Using R to fit a linear model

# The dataset is the Fuel Assumption data (Weisberg, page 35). You can download
# the data from my website.

# POP = 1971 population, in thousands.
# TAX = 1972 motor fuel tax rate, in cents per gallon.
# NLIC = 1971 thousands of licensed drivers.
# INC = 1972 per capita income in thousands of dollars.
# ROAD = 1971 thousands of miles of federal-aid primary highways.
# FUELC = 1972 fuel consumption, in millions of gallons.
# FUEL = 1000*FUELC/POP=motor fuel consumption (gallons per person)

# The purpose is to investigate how FUEL depend on other factors such as
# POP, TAX, NLIC, INC, ROAD and DLIC etc.

# First we read in the table. Since we want to keep the head, we use the option "head=T"

fuel = read.table("fuel-all.txt",head=T)
head(fuel)
summary(fuel)

# We use the command attach(fuel) so that we can visit variables POP, TAX etc.

attach(fuel)
POP

# Now we fit a linear model:
  
gfit = lm(FUEL~TAX+DLIC+INC+ROAD, data=fuel)
gfit2 = lm(FUEL~TAX+DLIC+INC-1,data=fuel)
anova(gfit,gfit2)
summary(gfit)

#The fitted values are

gfit$fit

#Is  FUEL-gfit$fit = gfit$res?

sum((FUEL-gfit$fit - gfit$res)^2) #4.959095e-26

#The estimated standard error:
sigma = (sum(gfit$res^2)/(43))^.5 #66.30619

#How to get the model matrix?

X = model.matrix(gfit)
CC<-(sum(gfit$res^2)/(gfit$df))*solve(t(X)%*%X)
sqrt(diag(CC))

aa = diag(solve(t(X)%*%X))
sigma*aa^.5
summary(gfit)$coef

plot(gfit)

########################################################################

asthma<-read.table("asthma.txt",header = T)
attach(asthma)
gfit<-lm(resistance~height)
summary(gfit)
plot(gfit)

gfit2<-lm(sqrt(resistance)~height)
summary(gfit2)

#######################################################################

barium<-read.table("barium.txt",header=T)
attach(barium)
Temp = temperature
Press = pressure..torr.
gfit<-lm(log(Press)~I(1/Temp))
summary(gfit)

plot(gfit)
















