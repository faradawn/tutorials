# Python Tips and Notes

## Part 0 - Install venv
```
# download virtualenv
python3 -m pip install --user virtualenv 

# create a env
python3 -m venv env
source env/bin/activate

# check
which python

# install packages
pip install --upgrade pip
pip install numpy

# install with requirements.txt
pip install -r requirements.txt
```

## Part 1 - Using pandas and CSV

### 1 - Creating a dataframe
```py
import pandas as pd
data = {
    'ID': [1, 2, 3],
    'NAME': ['Jake', 'Amy', 'Bob'],
    'CITY': ['Chicago', 'LA', 'LA'],
    'COUNTRY': ['US', 'US', 'US'],
    'CONTRCNT': [5, 10, 15]
}
df = pd.DataFrame(data)
print(df)

   ID  NAME     CITY COUNTRY  CONTRCNT
0   1  Jake  Chicago      US         5
1   2   Amy       LA      US        10
2   3   Bob       LA      US        15
```

### 2 - Doing queries
- `unique() -> array`
- 'value_counts() -> series`

```py
df.shape[0] # how many rows
df.shape[1] # how many columns

# 1 - total customers
df.shape[0]

# 2 - how many customers in each city -> Series
a = df['CITY'].value_counts()

# 3 - Which country has the largest number of customers' contracts
country = df['COUNTRY'].unique()
maxName = ""
maxCnt = 0
for val in country:
    a = df.loc[df['COUNTRY'] == val, 'CONTRCNT'].sum()
    if a > maxCnt:
        maxCnt = a
        maxName = val

# 4 - How many unique cities have at least one customer in them?
len(df['CITY'].unique())
```






## Python数学
generator is an iterable
```py
def generate_permutations(items: Union[list[T], tuple[T]]) -> Iterable[tuple[T]]:
    n=len(items)
    for i in range(n):
        yield items[i]+10

arr=[n for n in range(10)]
arr2=[i for i in generate_permutations(arr)]
print(arr2)
```
