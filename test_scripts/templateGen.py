import json
import os 
import argparse
import math 
import re 
import sys 
sys.path.append('../')
from utility import *

argParser = argparse.ArgumentParser()
argParser.add_argument("--datatype", type=str, default="float", choices=["float", "double"], help="datatype of benchmark")
argParser.add_argument("--tile_size", nargs='+', type=int, default=[128, 32, 8], help="the tile block size of stencil")
argParser.add_argument("--brick_size", nargs='+', type=int, help="the brick block size of stencil")
argParser.add_argument("--input_layout", type=str, default="grid", choices=["grid", "brick"], help="the memory layout of input grid")
argParser.add_argument("--output_layout", type=str, default="grid", choices=["grid", "brick"], help="the memory layout of output grid")
argParser.add_argument("--function", type=str, default=None, help="path of function to be tested")
argParser.add_argument("--check_path", type=str, default=None, help="path of function used for checking result")
argParser.add_argument("--output", type=str, default="benchmark", help="name of generated benchmark")
argParser.add_argument("--align",  action='store_true', help="use align malloc and align grid")
argParser.add_argument("--affine",  action='store_true', help="use affine omp parallel loop")
argParser.add_argument("--radius",  type=int, default=None, help="radius of stencil grid")
argParser.add_argument("--message",  type=str, default=None, help="extra message for generated benchmark")
argParser.add_argument("--throughput",  type=int, default=2, help="memory traffic of this kernel")
argParser.add_argument("--nflops",  type=int, default=None, help="number of fma per grid point")

def gen_index_macros(args):
    retval = []
    #
    if args.brick_size != None:
        BX, BY, BZ = args.brick_size

    retval = retval + ["#define index_g(i, j, k, sx, sy) ((i) + (j)*(sx) + (k)*(sy))"]
    if args.brick_size != None:
        retval = retval + [f"#define index_b(i, j, k, sx, sy) (((i)/{BX})*{BX*BY*BZ} + ((j)/{BY})*(sx) + ((k)/{BZ})*(sy))"]











        retval = [line + "\n" for line in retval]
        return retval 

def gen_functions(args):
    retval = []
    if args.check_path != None and args.input_layout == "brick" or args.output_layout == "brick":
        with open("./funcs/bricklize.cpp") as f:
            brick_func = f.readlines()
            func = re.findall(r'(?<=(?<=int\s)|(?<=void\s)|(?<=string\s)|(?<=double\s)|(?<=float\s)|(?<=char\s)).*?(?=\s?\()', brick_func[0])

            if len(func) != 1:
                func = re.findall(r'(?<=(?<=int\s)|(?<=void\s)|(?<=string\s)|(?<=double\s)|(?<=float\s)|(?<=char\s)).*?(?=\s?\()', brick_func[1])
            args.func_bricklize = func[0]
        retval = retval + brick_func 

        with open("./funcs/debricklize.cpp") as f:
            debrick_func = f.readlines()
            func = re.findall(r'(?<=(?<=int\s)|(?<=void\s)|(?<=string\s)|(?<=double\s)|(?<=float\s)|(?<=char\s)).*?(?=\s?\()', debrick_func[0])
            #
            if len(func) != 1:
                func = re.findall(r'(?<=(?<=int\s)|(?<=void\s)|(?<=string\s)|(?<=double\s)|(?<=float\s)|(?<=char\s)).*?(?=\s?\()', debrick_func[1])
            args.func_debricklize = func[0]
        
        retval = retval + debrick_func

    if args.check_path != None:
        with open(args.check_path, "r") as f:
            check_func = f.readlines()
            func = re.findall(r'(?<=(?<=int\s)|(?<=void\s)|(?<=string\s)|(?<=double\s)|(?<=float\s)|(?<=char\s)).*?(?=\s?\()', check_func[0])
            #
            if len(func) != 1:
                func = re.findall(r'(?<=(?<=int\s)|(?<=void\s)|(?<=string\s)|(?<=double\s)|(?<=float\s)|(?<=char\s)).*?(?=\s?\()', check_func[1])
            args.func_check = func[0]

        retval = retval + check_func

    assert args.function != None, "the input function must be assigned!"
    with open(args.function, "r") as f:
        input_func = f.readlines()
        func = re.findall(r'(?<=(?<=int\s)|(?<=void\s)|(?<=string\s)|(?<=double\s)|(?<=float\s)|(?<=char\s)).*?(?=\s?\()', input_func[0])
        if len(func) != 1:
            func = re.findall(r'(?<=(?<=int\s)|(?<=void\s)|(?<=string\s)|(?<=double\s)|(?<=float\s)|(?<=char\s)).*?(?=\s?\()', input_func[1])
        
        args.func_input = func[0]
    input_func = ["#if defined(__ARM_FEATURE_SME)\n", "__arm_new(\"za\")" + input_func[0] + "__arm_streaming", input_func[1], "#else\n", input_func[0], input_func[1], "#endif\n"] + input_func[2:-1] + [input_func[-1]]

    retval = retval + input_func 

    return retval 


def gen_extra_declare(args):
    retval = []
    if args.input_layout == "grid" or args.output_layout == "grid" or args.check:
        retval = retval + [f"int GZ_x = {args.grid_pad[0]}, GZ_y = {args.grid_pad[1]}, GZ_z = {args.grid_pad[2]};"]
        if args.align and args.grid_pad[0] != 0:
            retval = retval + [f"int grid_dim_x = ceil(nx, {args.grid_pad[0]})*{args.grid_pad[0]} + 2*GZ_x;"]
        else:
            retval = retval + [f"int grid_dim_x = nx + 2*GZ_x;"]
        for direction in ["y", "z"]:
            retval = retval + [f"int grid_dim_{direction} = n{direction} + 2*GZ_{direction};"]
            
    if args.input_layout == "brick" or args.output_layout == "brick":
        retval = retval + [f"int BZ_x = {args.brick_pad[0]}, BZ_y = {args.brick_pad[1]}, BZ_z = {args.brick_pad[2]};"]
        for i, direction in enumerate(["x", "y", "z"]):
            retval = retval + [f"int brick_dim_{direction} = ceil(n{direction}, {args.brick_size[i]}) * {args.brick_size[i]} + 2 * BZ_{direction};"]

    retval = retval + [f"int n_threads = omp_get_max_threads();"]
    retval = retval + ['''printf("benchmark configuration:\\n");''']
    retval = retval + [f'''printf("\tbenchmark datatype: {args.datatype}:\\n");''']
    retval = retval + [f'''printf("\tinput function path: {args.function}:\\n");''']
    retval = retval + [f'''printf("\tinput grid layout: {args.input_layout}:\\n");''']
    retval = retval + [f'''printf("\toutput grid layout: {args.output_layout}:\\n");''']
    retval = retval + [f'''printf("\tgrid size: %d, %d, %d\\n", nx, ny, nz);''']
    retval = retval + [f'''printf("\ttile size: {args.tile_size}\\n");''']
    retval = retval + [f'''printf("\tnumber of threads: %d\\n", n_threads);''']
    if args.brick_size != None:
        retval = retval + [f'''printf("\tbrick size: {args.brick_size}\\n");''']
    retval = retval + [f'''printf("\tuse alignment: {args.align}\\n");''']
    if args.message != None:
        retval = retval + [f'''printf("\t-----------------MESSAGE FOR THIS BENCHMARK-----------------\\n");''']
        retval = retval + [f'''printf("\t{args.message}:\\n");''']

    retval = retval + [f'''printf("begin tests:\\n");''']



    retval = [line + "\n" for line in retval]
    return retval 

def gen_alloc(args):
    retval = []
    if args.align:
        grid_malloc = lambda x : f"aligned_alloc(64, {x})"
    else:
        grid_malloc = lambda x : f"malloc({x})"
    brick_malloc = lambda x : f"aligned_alloc(64, {x})"

    retval = retval + ['''printf("malloc grid...\\n");''']
    if args.radius != None:
        retval = retval + [f"{args.datatype}* alpha = ({args.datatype}*)malloc(sizeof({args.datatype})*{(2*args.radius + 1)**3});"]
    else:
        retval = retval + [f"{args.datatype}* alpha = NULL;"]


    if args.input_layout == "grid":
        inputsize = f"sizeof({args.datatype})*grid_dim_x*grid_dim_y*grid_dim_z"
        retval = retval + [f"{args.datatype}* p0 = ({args.datatype}*){grid_malloc(inputsize)};"]
    else:
        inputsize = f"sizeof({args.datatype})*brick_dim_x*brick_dim_y*brick_dim_z"
        retval = retval + [f"{args.datatype}* p0 = ({args.datatype}*){brick_malloc(inputsize)};"]

    if args.output_layout == "grid":
        outputsize = f"sizeof({args.datatype})*grid_dim_x*grid_dim_y*grid_dim_z"
        retval = retval + [f"{args.datatype}* p1 = ({args.datatype}*){grid_malloc(outputsize)};"]
    else:
        outputsize = f"sizeof({args.datatype})*brick_dim_x*brick_dim_y*brick_dim_z"
        retval = retval + [f"{args.datatype}* p1 = ({args.datatype}*){brick_malloc(outputsize)};"]

    if args.check:
        ref_size = f"sizeof({args.datatype})*grid_dim_x*grid_dim_y*grid_dim_z"
        retval = retval + [f"{args.datatype}* p0_ref = ({args.datatype}*){grid_malloc(ref_size)};"]
        retval = retval + [f"{args.datatype}* p1_ref = ({args.datatype}*){grid_malloc(ref_size)};"]
        retval = retval + [f"{args.datatype}* p1_grid = ({args.datatype}*){grid_malloc(ref_size)};"]

    retval = retval + ['''printf("initalizing input grid...\\n");''']
    if args.radius != None:
        retval = retval + loop("i", 0, (2*args.radius + 1)**3, 1, [f"alpha[i] = uniform<{args.datatype}>();"])

    if args.check and args.input_layout == "brick":
        retval = retval + loop("i", 0, "grid_dim_x*grid_dim_y*grid_dim_z", 1, [f"p0_ref[i] = uniform<{args.datatype}>();"])
        retval = retval + [f"memset(p0, 0, {inputsize});"]
    else:
        npts = "grid_dim_x*grid_dim_y*grid_dim_z" if args.input_layout == "grid" else "brick_dim_x*brick_dim_y*brick_dim_z"
        retval = retval + loop("i", 0, npts, 1, [f"p0[i] = uniform<{args.datatype}>();"])

    retval = retval + ['''printf("zeroing output grid...\\n");''']
    output_npts = "grid_dim_x*grid_dim_y*grid_dim_z" if args.output_layout == "grid" else "brick_dim_x*brick_dim_y*brick_dim_z"
    retval = retval + [f"memset(p1, 0, sizeof({args.datatype})*{output_npts});"]
    if args.check:
        retval = retval + [f"memset(p1_ref, 0, sizeof({args.datatype})*grid_dim_x*grid_dim_y*grid_dim_z);"]
        retval = retval + [f"memset(p1_grid, 0, sizeof({args.datatype})*grid_dim_x*grid_dim_y*grid_dim_z);"]

    retval = [line + "\n" for line in retval]
    return retval 

def call_input_func(args):
    grid_sx = "grid_dim_x"; grid_sy = "grid_dim_x*grid_dim_y"

    if args.input_layout == "brick" or args.output_layout == "brick":
        BX, BY, BZ = args.brick_size
        brick_sx = f"brick_dim_x*{BY*BZ}"; brick_sy = f"brick_dim_x*brick_dim_y*{BZ}"
    if args.input_layout == "brick":
        param_in = f"&p0[index_b(ti + BZ_x, tj + BZ_y, tk + BZ_z, {brick_sx}, {brick_sy})]"
        sx, sy = brick_sx, brick_sy 
    else:
        param_in = f"&p0[index_g(ti + GZ_x, tj + GZ_y, tk + GZ_z, {grid_sx}, {grid_sy})]"
        sx, sy = grid_sx, grid_sy 
    
    if args.output_layout == "brick":
        param_out = f"&p1[index_b(ti + BZ_x, tj + BZ_y, tk + BZ_z, {brick_sx}, {brick_sy})]"
        dx, dy = brick_sx, brick_sy 
    else:
        param_out = f"&p1[index_g(ti + GZ_x, tj + GZ_y, tk + GZ_z, {grid_sx}, {grid_sy})]"
        dx, dy = grid_sx, grid_sy 
    kernel_invoke = f"{args.func_input}({param_in}, {param_out}, tile_size_x, tile_size_y, tile_size_z, {sx}, {sy}, {dx}, {dy}, alpha);"
    kernel_invoke = [f"int tile_size_x = min(nx - ti, {args.tile_size[0]});",
                    f"int tile_size_y = min(ny - tj, {args.tile_size[1]});",
                    f"int tile_size_z = min(nz - tk, {args.tile_size[2]});",
                    kernel_invoke]
    if args.affine:
        retval = ["#pragma omp parallel for collapse(3) schedule(static, 1)"] +  parallel3D("tj", "tk", "ti", 0, 0, 0, "ny", "nz", "nx", args.tile_size[1], args.tile_size[2], args.tile_size[0], kernel_invoke)

    else:
        retval = ["#pragma omp parallel for collapse(3)"] +  parallel3D("ti", "tj", "tk", 0, 0, 0, "nx", "ny", "nz", args.tile_size[0], args.tile_size[1], args.tile_size[2], kernel_invoke)
    return retval


def gen_checkresult(args):
    retval = []
    if args.check:
        retval = retval + ['''printf("checking result...\\n");''']

        grid_sx = "grid_dim_x"; grid_sy = "grid_dim_x*grid_dim_y"
        param_in = f"&p0_ref[index_g(ti + GZ_x, tj + GZ_y, tk + GZ_z, {grid_sx}, {grid_sy})]"
        param_out = f"&p1_ref[index_g(ti + GZ_x, tj + GZ_y, tk + GZ_z, {grid_sx}, {grid_sy})]"

        if args.input_layout == "brick":
            retval = retval + [f"{args.func_bricklize}(p0_ref, p0, nx, ny, nz, GZ_x, GZ_y, GZ_z, {args.brick_size[0]}, {args.brick_size[1]}, {args.brick_size[2]});"]
        else:
            retval = retval + loop("i", 0, "grid_dim_x*grid_dim_y*grid_dim_z", 1, [f"p0_ref[i] = p0[i];"])

        check_invoke = f"{args.func_check}({param_in}, {param_out}, tile_size_x, tile_size_y, tile_size_z, {grid_sx}, {grid_sy}, {grid_sx}, {grid_sy}, alpha);"
        check_invoke = [f"int tile_size_x = min(nx - ti, {args.tile_size[0]});",
                        f"int tile_size_y = min(ny - tj, {args.tile_size[1]});",
                        f"int tile_size_z = min(nz - tk, {args.tile_size[2]});",
                        check_invoke]
        retval = retval + ["#pragma omp parallel for collapsed(3)"] + parallel3D("ti", "tj", "tk", 0, 0, 0, "nx", "ny", "nz", args.tile_size[0], args.tile_size[1], args.tile_size[2], check_invoke)

    retval = retval + ['''printf("running benchmark...\\n");''']

    if args.check:
        retval = retval + call_input_func(args)
        if args.output_layout == "brick":
            retval = retval + [f"{args.func_debricklize}(p1, p1_grid, nx, ny, nz, GZ_x, GZ_y, GZ_z, {args.brick_size[0]}, {args.brick_size[1]}, {args.brick_size[2]});"]
        else:
            retval = retval + loop("i", 0, "grid_dim_x*grid_dim_y*grid_dim_z", 1, [f"p1_grid[i] = p1[i];"])
        check_result = [f"double diff = fabs(p1_grid[index_g(i, j, k, {grid_sx}, {grid_sy})] - p1_ref[index_g(i, j, k, {grid_sx}, {grid_sy})]);"]
        check_result = check_result + [f"double rel_diff = diff / (fabs(p1_ref[index_g(i, j, k, {grid_sx}, {grid_sy})]) + 1e-3);"]
        check_result = check_result + ["if (rel_diff > 1e-3) {"]
        check_result = check_result + [f"printf(\"on position (%d, %d, %d), p1_grid=%.6f, p1_ref=%.6f\\n\", i, j, k, p1_grid[index_g(i, j, k, {grid_sx}, {grid_sy})], p1_ref[index_g(i, j, k, {grid_sx}, {grid_sy})]);"]
        check_result = check_result + ["exit(1);"] + ["}"]
        retval = retval + parallel3D("i", "j", "k", 0, 0, 0, "grid_dim_x", "grid_dim_y", "grid_dim_z", 1, 1, 1, check_result)
        retval = retval + ['''printf("pass tests\\n");''']
    retval = [line + "\n" for line in retval]
    return retval

def gen_benchmark(args):
    retval = call_input_func(args)


    retval = [line + "\n" for line in retval]
    return retval


def gen_output(args):
    retval = []
    retval = retval + ['''printf("run benchmark complete\\n");''']
    retval = retval + ['''printf("\telapsed time %lfs\\n", elapsed_time);''']
    retval = retval + [f'''printf("\tbandwidth %lfGB/s\\n", sizeof({args.datatype})*nx*ny*nz*{args.throughput} / (elapsed_time * 1024*1024*1024));''']
    if args.nflops != None:
        retval = retval + [f'''printf("\tFLOPS: %lfGFLOPS\\n", {float(args.nflops)}*nx*ny*nz / (elapsed_time * 1024*1024*1024));''']

    retval = [line + "\n" for line in retval]
    return retval 

if __name__ == '__main__':
    args = argParser.parse_args()
    args.nPad = 16 if args.datatype == "float" else 8

    args.check = args.check_path != None 

    if args.radius != None:
        args.grid_pad = [args.nPad, args.radius, args.radius] if args.align else [args.radius, args.radius, args.radius]
        if args.brick_size != None:
            BX, BY, BZ = args.brick_size 
            args.brick_pad = [math.ceil(args.grid_pad[0] / BX) * BX, math.ceil(args.grid_pad[1] / BY) * BY, math.ceil(args.grid_pad[2] / BZ) * BZ]
        else:
            args.brick_pad = [0, 0, 0]
    else:
        args.grid_pad = [0, 0, 0]
        args.brick_pad = [0, 0, 0]

    with open("template.cpp", "r") as f:
        lines = f.readlines()

    output_lines = []
    for line in lines:
        if "<INDEX MACROS>" in line:
            output_lines = output_lines + gen_index_macros(args)
        elif "<FUNCTIONS>" in line:
            output_lines = output_lines + gen_functions(args)
        elif "<EXTRA DECLARE>" in line:
            output_lines = output_lines + gen_extra_declare(args)
        elif "<ALLOC>" in line:
            output_lines = output_lines + gen_alloc(args)
        elif "<CHECK RESULT>" in line:
            output_lines = output_lines + gen_checkresult(args)
        elif "<BENCHMARK>" in line:
            output_lines = output_lines + gen_benchmark(args)
        elif "<OUTPUT>" in line:
            output_lines = output_lines + gen_output(args)
        else:
            output_lines.append(line)

    with open(f"{args.output}.cpp", "w") as f:
        f.writelines(output_lines)





