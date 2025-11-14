template<typename T>
void debricklize(T* brick, T* grid, int nx, int ny, int nz, int pad_x, int pad_y, int pad_z, int BX, int BY, int BZ)
{
    assert(nx % BX == 0);
    assert(ny % BY == 0);
    assert(nz % BZ == 0);

    int nbx = nx / BX;
    int nby = ny / BY;
    int nbz = nz / BZ;

    int gz_x = (pad_x + BX - 1) / BX;
    int gz_y = (pad_y + BY - 1) / BY;
    int gz_z = (pad_z + BZ - 1) / BZ;

    int stride_x = nbx + 2 * gz_x;
    int stride_y = nby + 2 * gz_y;
    int stride_z = nbz + 2 * gz_z;

    int offset_x = gz_x * BX - pad_x;
    int offset_y = gz_y * BY - pad_y;
    int offset_z = gz_z * BZ - pad_z;

    int nxf = nx + 2 * pad_x;
    int nyf = ny + 2 * pad_y;
    int nzf = nz + 2 * pad_z;

    for(int k = 0; k < nzf; k++) {
        for(int j = 0; j < nyf; j++) {
            for(int i = 0; i < nxf; i++) {
                int x = i + offset_x;
                int y = j + offset_y;
                int z = k + offset_z;

                int brick_idx = ((x/BX) + (y/BY)*stride_x + (z/BZ)*stride_x*stride_y)*BX*BY*BZ + ((x%BX) + (y%BY)*BX + (z%BZ)*BX*BY);
                int grid_idx = i + j * nxf + k * nxf * nyf;
                grid[grid_idx] = brick[brick_idx];
            }
        }
    }
}
