template<typename T>
void stencil_xy_Grid_2d_box_radius2(T *p0, T *p1, int ker_size_x, int ker_size_y, int ker_size_z, int sy, int sz, int dy, int dz, float *yc){
	for (int k = 0; k < ker_size_z; k += 1)
	{
		for (int j = 0; j < ker_size_y; j += 1)
		{
			for (int i = 0; i < ker_size_x; i += 1)
			{
				int src_idx = i + j * sy + k * sz;
				int dst_idx = i + j * dy + k * dz;
				p1[dst_idx] = yc[0] * p0[src_idx + (-2) * 1 + (-2) * sy]
							 + yc[1] * p0[src_idx + (-1) * 1 + (-2) * sy]
							 + yc[2] * p0[src_idx + (0) * 1 + (-2) * sy]
							 + yc[3] * p0[src_idx + (1) * 1 + (-2) * sy]
							 + yc[4] * p0[src_idx + (2) * 1 + (-2) * sy]
							 + yc[5] * p0[src_idx + (-2) * 1 + (-1) * sy]
							 + yc[6] * p0[src_idx + (-1) * 1 + (-1) * sy]
							 + yc[7] * p0[src_idx + (0) * 1 + (-1) * sy]
							 + yc[8] * p0[src_idx + (1) * 1 + (-1) * sy]
							 + yc[9] * p0[src_idx + (2) * 1 + (-1) * sy]
							 + yc[10] * p0[src_idx + (-2) * 1 + (0) * sy]
							 + yc[11] * p0[src_idx + (-1) * 1 + (0) * sy]
							 + yc[12] * p0[src_idx + (0) * 1 + (0) * sy]
							 + yc[13] * p0[src_idx + (1) * 1 + (0) * sy]
							 + yc[14] * p0[src_idx + (2) * 1 + (0) * sy]
							 + yc[15] * p0[src_idx + (-2) * 1 + (1) * sy]
							 + yc[16] * p0[src_idx + (-1) * 1 + (1) * sy]
							 + yc[17] * p0[src_idx + (0) * 1 + (1) * sy]
							 + yc[18] * p0[src_idx + (1) * 1 + (1) * sy]
							 + yc[19] * p0[src_idx + (2) * 1 + (1) * sy]
							 + yc[20] * p0[src_idx + (-2) * 1 + (2) * sy]
							 + yc[21] * p0[src_idx + (-1) * 1 + (2) * sy]
							 + yc[22] * p0[src_idx + (0) * 1 + (2) * sy]
							 + yc[23] * p0[src_idx + (1) * 1 + (2) * sy]
							 + yc[24] * p0[src_idx + (2) * 1 + (2) * sy];
			}
		}
	}
}