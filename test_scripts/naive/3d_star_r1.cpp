template<typename T>
void stencil_Grid_3d_star_radius1(T *p0, T *p1, int ker_size_x, int ker_size_y, int ker_size_z, int sy, int sz, int dy, int dz, float *yc){
	for (int k = 0; k < ker_size_z; k += 1)
	{
		for (int j = 0; j < ker_size_y; j += 1)
		{
			for (int i = 0; i < ker_size_x; i += 1)
			{
				int src_idx = i + j * sy + k * sz;
				int dst_idx = i + j * dy + k * dz;
				p1[dst_idx] = yc[0] * (p0[src_idx + (-1)] + p0[src_idx + (-1) * sy] + p0[src_idx + (-1) * sz])
							 + yc[1] * (p0[src_idx + (0)] + p0[src_idx + (0) * sy] + p0[src_idx + (0) * sz])
							 + yc[2] * (p0[src_idx + (1)] + p0[src_idx + (1) * sy] + p0[src_idx + (1) * sz]);
			}
		}
	}
}
