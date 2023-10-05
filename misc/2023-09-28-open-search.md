# OpenSearch

## Installing OpenSearch
- Install docker desktop
- Download yaml: https://opensearch.org/downloads.html#docker-compose
- Run `docker-compose up` and open in browswer. admin admin login.

## Installing py-ml
- Dev guide: https://github.com/opensearch-project/opensearch-py-ml/blob/main/DEVELOPER_GUIDE.md
```
# Create a fork
git clone https://github.com/faradawn/opensearch-py-ml.git
cd opensearch-py-ml

# Install dependencies
python3 -m venv env
source env/bin/activate
pip install -r requirements-dev.txt
```


## Logs
[2023-10-05] Cannot import Pandas core for demo notebook

Problem: Third cell of [demo notebook](https://opensearch-project.github.io/opensearch-py-ml/examples/demo_notebook.html).
```
importError: cannot import name 'is_datetime_or_timedelta_dtype' from 'pandas.core.dtypes.common'
```

Solution: 1) try install docker on linux, 2)
