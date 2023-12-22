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

# Build the module (when testing)
#   Create question_answering_model.py.
#   In opensearch-py-ml/opensearch_py_ml/ml_models/__init__.py
#   add import question answering model/
#   Then, pip install .

# Run a test
python3 setup_tests.py
pytest tests/ml_models/test_question_answering_pytest.py -k test_make_model_config_json_for_torch_script

# Problem: When runing pytest, got pandas datetime64 error. (Pandas version 2.0.3)
#   TypeError: Casting to unit-less dtype 'datetime64' is not supported. Pass e.g. 'datetime64[ns]' instead.
# Solution: Modify line 60 of "tests/common.py" to "datetime64[ns]" from "datatime64".

# Commit with sign off
git commit -s -m "added something"

# Sign off previous commits from head
discard all files
git rebase HEAD~3 --signoff
git push --force-with-lease origin feature/summarization_model_conversation
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






## My Logs

### [2023-12-21] Add more coverage tests


### [2023-11-30] New PR
- Pull upstream main. Create new branch feature/question_answering_model. Add two new files.
- Pip install -r requirements-dev.txt, which downgraded my pandas from 2.0.3 to 1.5.3.
- Python setup tests.

### [2023-11-09] Create PR
- [x] Change to AutoModelForQuestionAnswering and AutoTokenizer to support different bert models.
- [x] Create basic unit tests.
- [x] Create a unit test to check the traced model's output.
  - The question answering model will output a [start_index, end_index] to identify the answer segment within the input.
  - Thus, I plan to check the [start_index, end_index] against that of the official model.
  - Cosine similarity tests can be used to check sentence embedding models.
-  Amend sign off (in code below)
- [ ] Check PR: https://github.com/opensearch-project/opensearch-py-ml/pull/332
- [ ] Check re-invent time.

### [2023-11-02] Modify PR
- [ ] Remove the comment # Save our model as pt
- [ ] In test, 1) Add assertion test. 2) Fix tokenizer file not found.
- [ ] Remove the other test file
- [ ] Check how pytest work, work workload failed
- [ ] Test: ModuleNotFound -- solved. nox -s test
- [ ] Run pytest tests/filename. pytest tests/filename -k method_name
- [ ] Next, 1) make unit tests, 2) check distil bert support different modules (auto tokenizer!).

### [2023-10-30] How to perform inference on model
- [x] inputs = tokenizer(question, text, return_tensors="pt"), take in two what means. Answer: simply append text to question as one long string.
- [x] Change distilbert to questionansweringbert.
- [x] Done 3 tests. And created a commit.
- [ ] TODO: move test tests/ml_commons/test_model_files.
- [ ] TODO: fix onnx function


### [2023-10-24] Check input to distil bert
```
# degbugging tracing model error
torch.jit.trace(model, (input1, input2)) instead of passing in a dictionary

# use save_pretrained to save the model to get config.json
#   Check if modal has 1) Transformer, 2) Pooling, 3) Normalize modules
#   Add config.json
#   check size in bytes
#   How to CURL with credentials admin admin
POST /_plugins/_ml/model_groups/_search

curl -XGET "http://localhost:9200/_plugins/_ml/model_groups/_search" -H 'Content-Type: application/json' -d'
{
  "query": {
    "bool": {
      "must": [
        {
          "terms": {
            "_id": [
              "Q31OaIsBLjDlmCgoebAH"
            ]
          }
        }
      ]
    }
  }
}'

# Registering the model with 27 chunks, but at first chunk, got read time out
# When registering again, it said model group already have a model with the same name.
# How to delete the model group. (I don't have model id yet)


```
### [2023-10-24] Working on first project
- Following the [notebook example](https://opensearch-project.github.io/opensearch-py-ml/examples/demo_ml_commons_integration.html) of sentence transformers.
- [Q]: What calls sentencetransformers.py? A: When import opensearch_py_ml library.
- [Q]: After creating question_answering model, the cannot invoke it through API calls, right?
- [Q] What function does the API's call? What is the backend -- django?
- [Q] How are the scripts in the repo called? [A] import
```
# Procedure
inside init.py, define all = [MLCommonClient]
then import
  from opensearch_py_ml.ml_commons import MLCommonClient
  ml_client = MLCommonClient(client)

# importError: cannot import name '_generate_model_content_hash_value' 
  Solved by importing sentencetransformer.py as a module instead of a file.

# Cannot import QuestionAnsweringModel
 Solved by 1) import in init.py, 2) in root directory, pip install .

# HERE: import huggingface module: https://huggingface.co/distilbert-base-cased-distilled-squad#how-to-get-started-with-the-model
 max_position_embeddings instead of max_sequence_length
 TODO: move tokenizer file saved places
```

### [2023-10-12] Questions for Dhurbo 
- Can I download a ML model after training such as KMeans? No. How to find the undeployed model_id? Cannot find. 
- Where did my uploaded data (CSV, models) go? Not a filesystem, but a database. When deploy model, will load into cache. 
- What does it mean a model is responding on two nodes?
- TODO: download the distil cased model and create a python script.
- Resolve cannot upload model by enable upload in settings (seek Slack)

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

