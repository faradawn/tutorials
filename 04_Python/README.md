# Python Tips and Notes

## Install venv
安装
```
python3 -m pip install --user virtualenv 
# pip install virtualenv
python3 -m venv env
source env/bin/activate
which python

# activate 之后
python3 -m pip install --upgrade pip
python3 -m pip install requests
python3 -m pip install selenium
python3 -m pip install beautifulsoup4

# use requirements.txt
python3 -m pip install -r requirements.txt
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
