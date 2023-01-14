import os
import json
from urllib import response
import pandas as pd

def entrypoint(request_file_path: str):
    with open(request_file_path, 'r') as f:
        request = json.load(f)

    response = perform_main_business_logic(request)
    print("result response length", len(response))

    with open("response.json", "w") as outfile:
        json.dump(response, outfile, indent=2)



def month_diff(date1, date2):
    # date 1 is transaction date, date 2 is expire date
    y1 = int(date1[:4])
    m1 = int(date1[5:7])
    y2 = int(date2[:4])
    m2 = int(date2[5:7])
    return (y2 - y1) * 12 + (m2 - m1)


def calc_quantity(securities, item):
    res = 0
    raw_quantity = float(item["quantity"])
    security_obj =  securities[item["security_code"]]

    if item["asset_class"] == "mcc":
        if security_obj["commodity_1"] == "CRD":
            res = raw_quantity
        else:
            res = raw_quantity / float(security_obj["swap_rate"])
    else: # laf
        num_month = month_diff(item["date"], security_obj["expiry"])
        res = raw_quantity * num_month

    return res

def merge():

def build_portifolio(transactions, securities, request):
    if request["portfolio_code"] has children:
        new_req_1 = {request["date"], protiole["children"][0]}
        child_1 = build_portifolio((transactions, securities, new_req_1)
        new_req_2 = {request["date"], protiole["children"][0]}
        child_2 = build_portifolio((transactions, securities, new_req_1)

        return merge(child_1, child_2, op)

    dic = {}
    trans = transactions[transactions["date"] <= request["date"]]

    for idx, item in trans.iterrows():
        if item["portfolio_code"] == request["portfolio_code"]: 
            item_name = item["security_code"] + ":" + item["broker_code"]
            if item_name not in dic:
                dic[item_name] = calc_quantity(securities, item)
            else:
                dic[item_name] += calc_quantity(securities, item)
    return dic
    
    

def build_response(dic, request, securities):
    response = []
    for key, val in dic.items():
        security_code, broker_code = key.split(":")
        obj = {}
        obj["date"] = request["date"]
        obj["security"] = securities[security_code]
        obj["broker_code"] = broker_code
        obj["quantity"] = val
        response.append(obj)
    return response


def perform_main_business_logic(request):
    transactions = pd.read_csv("data/transactions.csv")
    with open("data/securities.json", 'r') as f: 
        securities = json.load(f)
    with open("data/protifolios.json", 'r') as f: 
        portifolios = json.load(f)

    
    # generalize 
    for item in portifolios:
        if item["children"]:
            arr_port = []
            while item["children"][1]["chidren"]:
                arr_port.append()
            child_one = build_portifolio(transactions, securities, request) # build a simple port


    if request["portfolio_code"] == "RIFR":
        BHSL_obj = build_portifolio(transactions, securities, request)
        BLSH = build_portifolio(transactions, securities, request)
        if operation is add:
            # row
        # finish aggregation
    
    else:
        single_obj = build_portifolio(transactions, securities, request)
        response = build_response(single_obj, request, securities)
        return response




if __name__ == "__main__":
    entrypoint("./tests/sample_request_1.json")
