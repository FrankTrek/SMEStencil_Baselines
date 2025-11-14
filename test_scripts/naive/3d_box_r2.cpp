template<typename T>
void stencil_Grid_3d_box_radius2(T *p0, T *p1, int ker_size_x, int ker_size_y, int ker_size_z, int sy, int sz, int dy, int dz, float *yc){
	for (int k = 0; k < ker_size_z; k += 1)
	{
		for (int j = 0; j < ker_size_y; j += 1)
		{
			for (int i = 0; i < ker_size_x; i += 1)
			{
				int src_idx = i + j * sy + k * sz;
				int dst_idx = i + j * dy + k * dz;
				p1[dst_idx] = 0;
				for (int tz = 0; tz < 2*2 + 1; tz += 1)
				{
					T * yc_loc = yc + tz * (2 * 2 + 1) * (2 * 2 + 1);
					p1[dst_idx] += yc_loc[0] * p0[src_idx + (-2) + (-2) * sy + (tz - 2) * sz]
								 + yc_loc[1] * p0[src_idx + (-1) + (-2) * sy + (tz - 2) * sz]
								 + yc_loc[2] * p0[src_idx + (0) + (-2) * sy + (tz - 2) * sz]
								 + yc_loc[3] * p0[src_idx + (1) + (-2) * sy + (tz - 2) * sz]
								 + yc_loc[4] * p0[src_idx + (2) + (-2) * sy + (tz - 2) * sz]
								 + yc_loc[5] * p0[src_idx + (-2) + (-1) * sy + (tz - 2) * sz]
								 + yc_loc[6] * p0[src_idx + (-1) + (-1) * sy + (tz - 2) * sz]
								 + yc_loc[7] * p0[src_idx + (0) + (-1) * sy + (tz - 2) * sz]
								 + yc_loc[8] * p0[src_idx + (1) + (-1) * sy + (tz - 2) * sz]
								 + yc_loc[9] * p0[src_idx + (2) + (-1) * sy + (tz - 2) * sz]
								 + yc_loc[10] * p0[src_idx + (-2) + (0) * sy + (tz - 2) * sz]
								 + yc_loc[11] * p0[src_idx + (-1) + (0) * sy + (tz - 2) * sz]
								 + yc_loc[12] * p0[src_idx + (0) + (0) * sy + (tz - 2) * sz]
								 + yc_loc[13] * p0[src_idx + (1) + (0) * sy + (tz - 2) * sz]
								 + yc_loc[14] * p0[src_idx + (2) + (0) * sy + (tz - 2) * sz]
								 + yc_loc[15] * p0[src_idx + (-2) + (1) * sy + (tz - 2) * sz]
								 + yc_loc[16] * p0[src_idx + (-1) + (1) * sy + (tz - 2) * sz]
								 + yc_loc[17] * p0[src_idx + (0) + (1) * sy + (tz - 2) * sz]
								 + yc_loc[18] * p0[src_idx + (1) + (1) * sy + (tz - 2) * sz]
								 + yc_loc[19] * p0[src_idx + (2) + (1) * sy + (tz - 2) * sz]
								 + yc_loc[20] * p0[src_idx + (-2) + (2) * sy + (tz - 2) * sz]
								 + yc_loc[21] * p0[src_idx + (-1) + (2) * sy + (tz - 2) * sz]
								 + yc_loc[22] * p0[src_idx + (0) + (2) * sy + (tz - 2) * sz]
								 + yc_loc[23] * p0[src_idx + (1) + (2) * sy + (tz - 2) * sz]
								 + yc_loc[24] * p0[src_idx + (2) + (2) * sy + (tz - 2) * sz];
				}
			}
		}
	}
}
