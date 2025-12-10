import math

def brace(body):
    return ["{"] + ["\t" + line for line in body] + ["}"]

def loop(var, start, stop, step, body):
    for_head = [f"for(int {var} = {start}; {var} < {stop}; {var} += {step}) " + "{"]
    for_body = ["\t" + line for line in body]
    for_end = ["}"]
    return for_head + for_body + for_end

def parallel2D(i, j, startI, startJ, endI, endJ, stepI, stepJ, body):
    body = loop(i, startI, endI, stepI, body)
    body = loop(j, startJ, endJ, stepJ, body)
    return body 

def parallel3D(i, j, k, startI, startJ, startK, endI, endJ, endK, stepI, stepJ, stepK, body):
    body = loop(i, startI, endI, stepI, body)
    body = loop(j, startJ, endJ, stepJ, body)
    body = loop(k, startK, endK, stepK, body)
    return body

def if_statement(cond, body):
    if_head = [f"if({cond}) " + "{"]
    if_body = ["\t" + line for line in body]
    if_end = ["}"]
    return if_head + if_body + if_end

def if_else_statement(cond, ifbody, elsebody):
    if_head = [f"if({cond}) " + "{"]
    if_body = ["\t" + line for line in ifbody]
    if_end = ["} else {"]
    else_body = ["\t" + line for line in elsebody]
    else_end = ["}"]
    return if_head + if_body + if_end + else_body + else_end

def seperator():
    return ["" for i in range(5)] + ["-----------------------------------"] + ["" for i in range(5)]

def dump_func_to_file(filename, func):
    print(filename, len(func))
    with open(filename, "w") as f:
        f.writelines([ line + "\n" for line in func])