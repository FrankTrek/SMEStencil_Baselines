

def gen_loop(index, start, end, step, body):
    loop = [f"for (int {index} = {start}; {index} < {end}; {index} += {step})"]
    loop += ["{"]
    loop += ["\t" + line for line in body]
    loop += ["}"]
    return loop

def gen_1d(dir, r):
    if dir == "x":
        src_step = "1"
    elif dir == "y":
        src_step = "sy"
    elif dir == "z":
        src_step = "sz"

    declear = ["int src_idx = i + j * sy + k * sz;"] + \
            ["int dst_idx = i + j * dy + k * dz;"]
    compute = [f"p1[dst_idx] = yc[0] * p0[src_idx + ({-r}) * {src_step}]"]
    for i in range(1, 2 * r + 1):
        compute += ["\t\t\t" + f" + yc[{i}] * p0[src_idx + ({i - r}) * {src_step}]" + (";" if i == 2 * r else "")]

    func_head = f"template<typename T>\nvoid stencil_{dir}_Grid_1d_radius{r}(T *p0, T *p1, int ker_size_x, int ker_size_y, int ker_size_z, int sy, int sz, int dy, int dz, float *yc)" + "{"
    func = gen_loop("k", "0", "ker_size_z", "1", 
                gen_loop("j", "0", "ker_size_y", "1",
                    gen_loop("i", "0", "ker_size_x", "1",
                        declear + compute
                    )
                )
            )
    entire_func = [func_head] + ["\t" + line for line in func] + ["}"]
    entire_func = "\n".join(entire_func)
    return entire_func

def gen_2d_star(dir, r):
    if dir == "xy":
        src_step_1 = "1"
        src_step_2 = "sy"
    elif dir == "xz":
        src_step_1 = "1"
        src_step_2 = "sz"
    elif dir == "yz":
        src_step_1 = "sy"
        src_step_2 = "sz"

    declear = ["int src_idx = i + j * sy + k * sz;"] + \
            ["int dst_idx = i + j * dy + k * dz;"]
    compute = [f"p1[dst_idx] = yc[0] * (p0[src_idx + ({-r}) * {src_step_1}] + p0[src_idx + ({-r}) * {src_step_2}])"]
    for i in range(1, 2 * r + 1):
        compute += ["\t\t\t" + f" + yc[{i}] * (p0[src_idx + ({i - r}) * {src_step_1}] + p0[src_idx + ({i - r}) * {src_step_2}])" + (";" if i == 2 * r else "")]
    
    func_head = f"template<typename T>\nvoid stencil_{dir}_Grid_2d_star_radius{r}(T *p0, T *p1, int ker_size_x, int ker_size_y, int ker_size_z, int sy, int sz, int dy, int dz, float *yc)" + "{"
    func = gen_loop("k", "0", "ker_size_z", "1",
                gen_loop("j", "0", "ker_size_y", "1",
                    gen_loop("i", "0", "ker_size_x", "1",
                        declear + compute
                    )
                )
            )
    entire_func = [func_head] + ["\t" + line for line in func] + ["}"]
    entire_func = "\n".join(entire_func)
    return entire_func
    
def gen_2d_box(dir, r):
    if dir == "xy":
        src_step1 = "1"
        src_step2 = "sy"
    elif dir == "xz":
        src_step1 = "1"
        src_step2 = "sz"
    elif dir == "yz":
        src_step1 = "sy"
        src_step2 = "sz"

    declear = ["int src_idx = i + j * sy + k * sz;"] + \
            ["int dst_idx = i + j * dy + k * dz;"]
    compute = [f"p1[dst_idx] = yc[0] * p0[src_idx + ({-r}) * {src_step1} + ({-r}) * {src_step2}]"]

    for j in range(0, 2 * r + 1):
        for i in range(0, 2 * r + 1):
            if j == 0 and i == 0:
                continue
            compute += ["\t\t\t" + f" + yc[{j * (2 * r + 1) + i}] * p0[src_idx + ({i - r}) * {src_step1} + ({j - r}) * {src_step2}]" + (";" if j == 2 * r and i == 2 * r else "")]

    func_head = f"template<typename T>\nvoid stencil_{dir}_Grid_2d_box_radius{r}(T *p0, T *p1, int ker_size_x, int ker_size_y, int ker_size_z, int sy, int sz, int dy, int dz, float *yc)" + "{"
    func = gen_loop("k", "0", "ker_size_z", "1",
                gen_loop("j", "0", "ker_size_y", "1",
                    gen_loop("i", "0", "ker_size_x", "1",
                        declear + compute
                    )
                )
            )
    entire_func = [func_head] + ["\t" + line for line in func] + ["}"]
    entire_func = "\n".join(entire_func)
    return entire_func

def gen_3d_star(r):
    declear = ["int src_idx = i + j * sy + k * sz;"] + \
            ["int dst_idx = i + j * dy + k * dz;"]
    compute = [f"p1[dst_idx] = yc[0] * (p0[src_idx + ({-r})] + p0[src_idx + ({-r}) * sy] + p0[src_idx + ({-r}) * sz])"]
    for i in range(1, 2 * r + 1):
        compute += ["\t\t\t" + f" + yc[{i}] * (p0[src_idx + ({i - r})] + p0[src_idx + ({i - r}) * sy] + p0[src_idx + ({i - r}) * sz])" + (";" if i == 2 * r else "")]

    func_head = f"template<typename T>\nvoid stencil_Grid_3d_star_radius{r}(T *p0, T *p1, int ker_size_x, int ker_size_y, int ker_size_z, int sy, int sz, int dy, int dz, float *yc)" + "{"
    func = gen_loop("k", "0", "ker_size_z", "1",
                gen_loop("j", "0", "ker_size_y", "1",   
                    gen_loop("i", "0", "ker_size_x", "1",
                        declear + compute
                    )
                )
            )
    entire_func = [func_head] + ["\t" + line for line in func] + ["}"]
    entire_func = "\n".join(entire_func) + "\n"
    return entire_func

def gen_3d_box(r):
    declear = ["int src_idx = i + j * sy + k * sz;"] + \
            ["int dst_idx = i + j * dy + k * dz;"] + ["p1[dst_idx] = 0;"]
    compute = [f"T * yc_loc = yc + tz * (2 * {r} + 1) * (2 * {r} + 1);"] + [f"p1[dst_idx] += yc_loc[0] * p0[src_idx + ({-r}) + ({-r}) * sy + (tz - {r}) * sz]"]

    for j in range(0, 2 * r + 1):
        for i in range(0, 2 * r + 1):
            if j == 0 and i == 0:
                continue
            compute += ["\t\t\t" + f" + yc_loc[{j * (2 * r + 1) + i}] * p0[src_idx + ({i - r}) + ({j - r}) * sy + (tz - {r}) * sz]" + (";" if j == 2 * r and i == 2 * r else "")]

    func_head = f"template<typename T>\nvoid stencil_Grid_3d_box_radius{r}(T *p0, T *p1, int ker_size_x, int ker_size_y, int ker_size_z, int sy, int sz, int dy, int dz, float *yc)" + "{"
    func = gen_loop("k", "0", "ker_size_z", "1",
                gen_loop("j", "0", "ker_size_y", "1",
                    gen_loop("i", "0", "ker_size_x", "1",
                        declear + gen_loop("tz", "0", f"2*{r} + 1", "1",
                            compute
                        )
                    )
                )
            )
    entire_func = [func_head] + ["\t" + line for line in func] + ["}"]
    entire_func = "\n".join(entire_func) + "\n"
    return entire_func


if __name__ == "__main__":
    for dir in ["x", "y", "z"]:
        for r in range(1, 5):
            with open(f"1d{dir}_r{r}.cpp", "w") as f:
                f.write(gen_1d(dir, r))

    for r in range(1, 5):
        with open(f"2dxy_star_r{r}.cpp", "w") as f:
            f.write(gen_2d_star("xy", r))

    for r in range(1, 5):
        with open(f"2dxy_box_r{r}.cpp", "w") as f:
            f.write(gen_2d_box("xy", r))

    for r in range(1, 5):
        with open(f"3d_star_r{r}.cpp", "w") as f:
            f.write(gen_3d_star(r))

    for r in range(1, 5):
        with open(f"3d_box_r{r}.cpp", "w") as f:
            f.write(gen_3d_box(r))