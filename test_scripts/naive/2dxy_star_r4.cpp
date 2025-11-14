template<typename T>
void stencil_xy_Grid_2d_star_radius4(T *p0, T *p1, int ker_size_x, int ker_size_y, int ker_size_z, int sy, int sz, int dy, int dz, float *yc){
	for (int k = 0; k < ker_size_z; k += 1)
	{
		for (int j = 0; j < ker_size_y; j += 1)
		{
			for (int i = 0; i < ker_size_x; i += 1)
			{
				int src_idx = i + j * sy + k * sz;
				int dst_idx = i + j * dy + k * dz;
				p1[dst_idx] = yc[0] * (p0[src_idx + (-4) * 1] + p0[src_idx + (-4) * sy])
							 + yc[1] * (p0[src_idx + (-3) * 1] + p0[src_idx + (-3) * sy])
							 + yc[2] * (p0[src_idx + (-2) * 1] + p0[src_idx + (-2) * sy])
							 + yc[3] * (p0[src_idx + (-1) * 1] + p0[src_idx + (-1) * sy])
							 + yc[4] * (p0[src_idx + (0) * 1] + p0[src_idx + (0) * sy])
							 + yc[5] * (p0[src_idx + (1) * 1] + p0[src_idx + (1) * sy])
							 + yc[6] * (p0[src_idx + (2) * 1] + p0[src_idx + (2) * sy])
							 + yc[7] * (p0[src_idx + (3) * 1] + p0[src_idx + (3) * sy])
							 + yc[8] * (p0[src_idx + (4) * 1] + p0[src_idx + (4) * sy]);
			}
		}
	}
}