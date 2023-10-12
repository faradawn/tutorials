# OpenSearch
- [Dev guide Readme](https://github.com/opensearch-project/opensearch-py-ml/blob/main/DEVELOPER_GUIDE.md) 
- [API reference for pyml](https://opensearch-project.github.io/opensearch-py-ml/reference/index.html)
- [Official Documentation](https://opensearch.org/docs/latest/im-plugin/index/)

## Installing OpenSearch on Intel Macbook
- Install docker desktop.
- Download [docker-compose.yaml](https://opensearch.org/downloads.html#docker-compose).
- Run `docker-compose up` and open in browswer. admin admin login.

## Installing py-ml
```
# Create a fork
git clone https://github.com/faradawn/opensearch-py-ml.git
cd opensearch-py-ml

# Install dependencies
python3 -m venv env
source env/bin/activate
pip install -r requirements-dev.txt
```

## Configure cluster
- On website dev tools, paste the following config.
- Then, try [demo notebooks](https://opensearch-project.github.io/opensearch-py-ml/examples/index.html).
```
 PUT /_cluster/settings
 {
   "persistent" : {
     "plugins.ml_commons.only_run_on_ml_node" : false, 
     "plugins.ml_commons.native_memory_threshold" : 100, 
     "plugins.ml_commons.max_model_on_node": 20,
     "plugins.ml_commons.enable_inhouse_python_model": true
   }
 }
```


## Logs

### [2023-10-12] Questions for Dhurbo 
- Can I download a ML model after training such as KMeans? No. How to find the undeployed model_id? Cannot find. 
- Where did my uploaded data (CSV, models) go? Not a filesystem, but a database. When deploy model, will load into cache. 
- What does it mean a model is responding on two nodes?
- TODO: download the distil cased model and create a python script. 


### Develop ML model
- Following the [notebook example](https://opensearch-project.github.io/opensearch-py-ml/examples/demo_ml_commons_integration.html) of sentence transformers.

### TODO: try ml demo notebook

### How to show all indicies?
Left sidebar, Index Management, Indices, opensearch_dashboards_sample_data_flights



### [2023-10-11] SSL: WRONG_VERSION_NUMBER

Problem: when trying to create a dataframe, got urllib3 SSL: WRONG_VERSION_NUMBER.

Solution: 1)[not true] upgrade urllib3 from 1.26.17 to 2.0.6. (pip install --upgrade urllib3).

2) CLUSTER_URL = 'https://localhost:9200', the data node port, instead of the dashboard 5601.



### [2023-10-05] Cannot import Pandas core for demo notebook

Problem: Third cell of [demo notebook](https://opensearch-project.github.io/opensearch-py-ml/examples/demo_notebook.html).
```
importError: cannot import name 'is_datetime_or_timedelta_dtype' from 'pandas.core.dtypes.common'
```
Solution: pip install pandas 2.0.1. (downgrade it).

