# C3 Simulator

## Install  
```
# Install python2
conda create -n c3 python=2.7 simpy==2.2 numpy 
conda activate c3

# Install Rscript and developer pack
sudo apt-get install littler
sudo apt install liblapack-dev libopenblas-dev -y

# Install packages using the R shell
sudo R
> install.packages("ggplot2")
> install.packages("data.table")
```

## Running the simulator
```
python experiment.py --numClients 10 --numServers 2 --numRequests 10000 --numWorkload 50 --serviceTime 20 --expPrefix 2 --expScenario multipleServiceTimeServers --slowServerFraction 0.75 --slowServerSlowness 1000 --simulationDuration 1200000
Rscript ../plotting/timeseries.r 2
```

