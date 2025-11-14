template<typename T>
void stencil_Grid_3d_box_radius1(T *p0, T *p1, int ker_size_x, int ker_size_y, int ker_size_z, int sy, int sz, int dy, int dz, float *yc){
	for (int k = 0; k < ker_size_z; k += 1)
	{
		for (int j = 0; j < ker_size_y; j += 1)
		{
			for (int i = 0; i < ker_size_x; i += 1)
			{
				int src_idx = i + j * sy + k * sz;
				int dst_idx = i + j * dy + k * dz;
				p1[dst_idx] = 0;
				for (int tz = 0; tz < 2*1 + 1; tz += 1)
				{
					T * yc_loc = yc + tz * (2 * 1 + 1) * (2 * 1 + 1);
					p1[dst_idx] += yc_loc[0] * p0[src_idx + (-1) + (-1) * sy + (tz - 1) * sz]
								 + yc_loc[1] * p0[src_idx + (0) + (-1) * sy + (tz - 1) * sz]
								 + yc_loc[2] * p0[src_idx + (1) + (-1) * sy + (tz - 1) * sz]
								 + yc_loc[3] * p0[src_idx + (-1) + (0) * sy + (tz - 1) * sz]
								 + yc_loc[4] * p0[src_idx + (0) + (0) * sy + (tz - 1) * sz]
								 + yc_loc[5] * p0[src_idx + (1) + (0) * sy + (tz - 1) * sz]
								 + yc_loc[6] * p0[src_idx + (-1) + (1) * sy + (tz - 1) * sz]
								 + yc_loc[7] * p0[src_idx + (0) + (1) * sy + (tz - 1) * sz]
								 + yc_loc[8] * p0[src_idx + (1) + (1) * sy + (tz - 1) * sz];
				}
			}
		}
	}
}
