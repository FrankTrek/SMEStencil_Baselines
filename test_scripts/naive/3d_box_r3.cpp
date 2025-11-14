template<typename T>
void stencil_Grid_3d_box_radius3(T *p0, T *p1, int ker_size_x, int ker_size_y, int ker_size_z, int sy, int sz, int dy, int dz, float *yc){
	for (int k = 0; k < ker_size_z; k += 1)
	{
		for (int j = 0; j < ker_size_y; j += 1)
		{
			for (int i = 0; i < ker_size_x; i += 1)
			{
				int src_idx = i + j * sy + k * sz;
				int dst_idx = i + j * dy + k * dz;
				p1[dst_idx] = 0;
				for (int tz = 0; tz < 2*3 + 1; tz += 1)
				{
					T * yc_loc = yc + tz * (2 * 3 + 1) * (2 * 3 + 1);
					p1[dst_idx] += yc_loc[0] * p0[src_idx + (-3) + (-3) * sy + (tz - 3) * sz]
								 + yc_loc[1] * p0[src_idx + (-2) + (-3) * sy + (tz - 3) * sz]
								 + yc_loc[2] * p0[src_idx + (-1) + (-3) * sy + (tz - 3) * sz]
								 + yc_loc[3] * p0[src_idx + (0) + (-3) * sy + (tz - 3) * sz]
								 + yc_loc[4] * p0[src_idx + (1) + (-3) * sy + (tz - 3) * sz]
								 + yc_loc[5] * p0[src_idx + (2) + (-3) * sy + (tz - 3) * sz]
								 + yc_loc[6] * p0[src_idx + (3) + (-3) * sy + (tz - 3) * sz]
								 + yc_loc[7] * p0[src_idx + (-3) + (-2) * sy + (tz - 3) * sz]
								 + yc_loc[8] * p0[src_idx + (-2) + (-2) * sy + (tz - 3) * sz]
								 + yc_loc[9] * p0[src_idx + (-1) + (-2) * sy + (tz - 3) * sz]
								 + yc_loc[10] * p0[src_idx + (0) + (-2) * sy + (tz - 3) * sz]
								 + yc_loc[11] * p0[src_idx + (1) + (-2) * sy + (tz - 3) * sz]
								 + yc_loc[12] * p0[src_idx + (2) + (-2) * sy + (tz - 3) * sz]
								 + yc_loc[13] * p0[src_idx + (3) + (-2) * sy + (tz - 3) * sz]
								 + yc_loc[14] * p0[src_idx + (-3) + (-1) * sy + (tz - 3) * sz]
								 + yc_loc[15] * p0[src_idx + (-2) + (-1) * sy + (tz - 3) * sz]
								 + yc_loc[16] * p0[src_idx + (-1) + (-1) * sy + (tz - 3) * sz]
								 + yc_loc[17] * p0[src_idx + (0) + (-1) * sy + (tz - 3) * sz]
								 + yc_loc[18] * p0[src_idx + (1) + (-1) * sy + (tz - 3) * sz]
								 + yc_loc[19] * p0[src_idx + (2) + (-1) * sy + (tz - 3) * sz]
								 + yc_loc[20] * p0[src_idx + (3) + (-1) * sy + (tz - 3) * sz]
								 + yc_loc[21] * p0[src_idx + (-3) + (0) * sy + (tz - 3) * sz]
								 + yc_loc[22] * p0[src_idx + (-2) + (0) * sy + (tz - 3) * sz]
								 + yc_loc[23] * p0[src_idx + (-1) + (0) * sy + (tz - 3) * sz]
								 + yc_loc[24] * p0[src_idx + (0) + (0) * sy + (tz - 3) * sz]
								 + yc_loc[25] * p0[src_idx + (1) + (0) * sy + (tz - 3) * sz]
								 + yc_loc[26] * p0[src_idx + (2) + (0) * sy + (tz - 3) * sz]
								 + yc_loc[27] * p0[src_idx + (3) + (0) * sy + (tz - 3) * sz]
								 + yc_loc[28] * p0[src_idx + (-3) + (1) * sy + (tz - 3) * sz]
								 + yc_loc[29] * p0[src_idx + (-2) + (1) * sy + (tz - 3) * sz]
								 + yc_loc[30] * p0[src_idx + (-1) + (1) * sy + (tz - 3) * sz]
								 + yc_loc[31] * p0[src_idx + (0) + (1) * sy + (tz - 3) * sz]
								 + yc_loc[32] * p0[src_idx + (1) + (1) * sy + (tz - 3) * sz]
								 + yc_loc[33] * p0[src_idx + (2) + (1) * sy + (tz - 3) * sz]
								 + yc_loc[34] * p0[src_idx + (3) + (1) * sy + (tz - 3) * sz]
								 + yc_loc[35] * p0[src_idx + (-3) + (2) * sy + (tz - 3) * sz]
								 + yc_loc[36] * p0[src_idx + (-2) + (2) * sy + (tz - 3) * sz]
								 + yc_loc[37] * p0[src_idx + (-1) + (2) * sy + (tz - 3) * sz]
								 + yc_loc[38] * p0[src_idx + (0) + (2) * sy + (tz - 3) * sz]
								 + yc_loc[39] * p0[src_idx + (1) + (2) * sy + (tz - 3) * sz]
								 + yc_loc[40] * p0[src_idx + (2) + (2) * sy + (tz - 3) * sz]
								 + yc_loc[41] * p0[src_idx + (3) + (2) * sy + (tz - 3) * sz]
								 + yc_loc[42] * p0[src_idx + (-3) + (3) * sy + (tz - 3) * sz]
								 + yc_loc[43] * p0[src_idx + (-2) + (3) * sy + (tz - 3) * sz]
								 + yc_loc[44] * p0[src_idx + (-1) + (3) * sy + (tz - 3) * sz]
								 + yc_loc[45] * p0[src_idx + (0) + (3) * sy + (tz - 3) * sz]
								 + yc_loc[46] * p0[src_idx + (1) + (3) * sy + (tz - 3) * sz]
								 + yc_loc[47] * p0[src_idx + (2) + (3) * sy + (tz - 3) * sz]
								 + yc_loc[48] * p0[src_idx + (3) + (3) * sy + (tz - 3) * sz];
				}
			}
		}
	}
}
