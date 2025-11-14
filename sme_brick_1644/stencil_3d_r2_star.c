void stencil_3d_star_BrickBrick_16164_radius2(float *p0, float *p1, int ker_size_x, int ker_size_y, int ker_size_z, int sy, int sz, int dy, int dz, float *coef)
{
	svbool_t mask_x_0,mask_y,mask_z,mask_xy,mask_xz,mask_yz,mask_xyz,mask_ext;
	svbool_t p32_all = svdup_b32(true); 

	int brick_index[] = {0, 16, 32, 48, 64, 80, 96, 112, 128, 144, 160, 176, 192, 208, 224, 240};
	svint32_t index_vec = svld1(p32_all, brick_index);
	svbool_t prefetch_mask;

	float *ptr_m1, *ptr_0, *ptr_1, *ptr_l, *ptr_r, *ptr_dst, *ptr_src, *temp_dst, *temp_ptr, *coef_loc;
	for(int vz = 0; vz < ker_size_z; vz += 4) {
		for(int vy = 0; vy < ker_size_y; vy += 16) {
			int vec_size_y = min(ker_size_y - vy, 16), vec_size_z = min(ker_size_z - vz, 4);
			if(vec_size_y == 16 && vec_size_z == 4) {
				//inner loop start phase
				ptr_src = (p0 + (((vy)/4)*sy + ((vy)%4)*16+((vz)/4)*sz + ((vz)%4)*16*4)); ptr_dst = (p1 + (((vy)/4)*dy + ((vy)%4)*16+((vz)/4)*dz + ((vz)%4)*16*4)); ptr_l = ptr_src + (-1*sy+2*16); ptr_r = ptr_src + (4*sy);
				float buffer[1*(3072) + (1*1024)]__attribute__((aligned(64)));
				float *buffer_m1 = buffer, *buffer_0 = buffer + 1024, *buffer_1 = buffer + 2048;
				mask_ext = svwhilelt_b32(0, 14); mask_ext = sveor_z(p32_all, p32_all, mask_ext); 
				for(int iz = 0; iz < 4; iz += 4) {
					// loading from grid 
					mask_x_0 = svwhilelt_b32(0, 16); 
					mask_x_0 = svand_z(p32_all, mask_x_0, mask_ext); 
					svld1_hor_za32(0, 0, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + 0]); 
					svld1_hor_za32(0, 1, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*16)]); 
					svld1_hor_za32(0, 2, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*16)]); 
					svld1_hor_za32(0, 3, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*16)]); 
					svld1_hor_za32(0, 4, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy)]); 
					svld1_hor_za32(0, 5, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+1*16)]); 
					svld1_hor_za32(0, 6, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+2*16)]); 
					svld1_hor_za32(0, 7, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+3*16)]); 
					svld1_hor_za32(0, 8, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy)]); 
					svld1_hor_za32(0, 9, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+1*16)]); 
					svld1_hor_za32(0, 10, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+2*16)]); 
					svld1_hor_za32(0, 11, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+3*16)]); 
					svld1_hor_za32(0, 12, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy)]); 
					svld1_hor_za32(0, 13, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+1*16)]); 
					svld1_hor_za32(0, 14, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+2*16)]); 
					svld1_hor_za32(0, 15, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+3*16)]); 
					svld1_hor_za32(1, 0, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*16*4)]); 
					svld1_hor_za32(1, 1, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*16+1*16*4)]); 
					svld1_hor_za32(1, 2, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*16+1*16*4)]); 
					svld1_hor_za32(1, 3, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*16+1*16*4)]); 
					svld1_hor_za32(1, 4, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+1*16*4)]); 
					svld1_hor_za32(1, 5, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+1*16+1*16*4)]); 
					svld1_hor_za32(1, 6, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+2*16+1*16*4)]); 
					svld1_hor_za32(1, 7, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+3*16+1*16*4)]); 
					svld1_hor_za32(1, 8, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+1*16*4)]); 
					svld1_hor_za32(1, 9, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+1*16+1*16*4)]); 
					svld1_hor_za32(1, 10, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+2*16+1*16*4)]); 
					svld1_hor_za32(1, 11, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+3*16+1*16*4)]); 
					svld1_hor_za32(1, 12, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+1*16*4)]); 
					svld1_hor_za32(1, 13, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+1*16+1*16*4)]); 
					svld1_hor_za32(1, 14, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+2*16+1*16*4)]); 
					svld1_hor_za32(1, 15, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+3*16+1*16*4)]); 
					svld1_hor_za32(2, 0, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*16*4)]); 
					svld1_hor_za32(2, 1, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*16+2*16*4)]); 
					svld1_hor_za32(2, 2, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*16+2*16*4)]); 
					svld1_hor_za32(2, 3, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*16+2*16*4)]); 
					svld1_hor_za32(2, 4, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+2*16*4)]); 
					svld1_hor_za32(2, 5, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+1*16+2*16*4)]); 
					svld1_hor_za32(2, 6, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+2*16+2*16*4)]); 
					svld1_hor_za32(2, 7, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+3*16+2*16*4)]); 
					svld1_hor_za32(2, 8, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+2*16*4)]); 
					svld1_hor_za32(2, 9, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+1*16+2*16*4)]); 
					svld1_hor_za32(2, 10, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+2*16+2*16*4)]); 
					svld1_hor_za32(2, 11, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+3*16+2*16*4)]); 
					svld1_hor_za32(2, 12, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+2*16*4)]); 
					svld1_hor_za32(2, 13, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+1*16+2*16*4)]); 
					svld1_hor_za32(2, 14, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+2*16+2*16*4)]); 
					svld1_hor_za32(2, 15, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+3*16+2*16*4)]); 
					svld1_hor_za32(3, 0, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*16*4)]); 
					svld1_hor_za32(3, 1, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*16+3*16*4)]); 
					svld1_hor_za32(3, 2, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*16+3*16*4)]); 
					svld1_hor_za32(3, 3, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*16+3*16*4)]); 
					svld1_hor_za32(3, 4, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+3*16*4)]); 
					svld1_hor_za32(3, 5, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+1*16+3*16*4)]); 
					svld1_hor_za32(3, 6, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+2*16+3*16*4)]); 
					svld1_hor_za32(3, 7, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+3*16+3*16*4)]); 
					svld1_hor_za32(3, 8, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+3*16*4)]); 
					svld1_hor_za32(3, 9, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+1*16+3*16*4)]); 
					svld1_hor_za32(3, 10, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+2*16+3*16*4)]); 
					svld1_hor_za32(3, 11, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+3*16+3*16*4)]); 
					svld1_hor_za32(3, 12, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+3*16*4)]); 
					svld1_hor_za32(3, 13, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+1*16+3*16*4)]); 
					svld1_hor_za32(3, 14, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+2*16+3*16*4)]); 
					svld1_hor_za32(3, 15, mask_x_0, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+3*16+3*16*4)]); 
					//tranpose and store back to grid
					svst1_ver_za32(0, 0, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + 0]); 
					svst1_ver_za32(0, 1, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (1*16)]); 
					svst1_ver_za32(0, 2, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (2*16)]); 
					svst1_ver_za32(0, 3, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (3*16)]); 
					svst1_ver_za32(0, 4, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (4*16)]); 
					svst1_ver_za32(0, 5, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (5*16)]); 
					svst1_ver_za32(0, 6, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (6*16)]); 
					svst1_ver_za32(0, 7, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (7*16)]); 
					svst1_ver_za32(0, 8, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (8*16)]); 
					svst1_ver_za32(0, 9, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (9*16)]); 
					svst1_ver_za32(0, 10, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (10*16)]); 
					svst1_ver_za32(0, 11, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (11*16)]); 
					svst1_ver_za32(0, 12, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (12*16)]); 
					svst1_ver_za32(0, 13, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (13*16)]); 
					svst1_ver_za32(0, 14, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (14*16)]); 
					svst1_ver_za32(0, 15, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (15*16)]); 
					svst1_ver_za32(1, 0, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (1*16*16)]); 
					svst1_ver_za32(1, 1, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (1*16+1*16*16)]); 
					svst1_ver_za32(1, 2, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (2*16+1*16*16)]); 
					svst1_ver_za32(1, 3, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (3*16+1*16*16)]); 
					svst1_ver_za32(1, 4, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (4*16+1*16*16)]); 
					svst1_ver_za32(1, 5, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (5*16+1*16*16)]); 
					svst1_ver_za32(1, 6, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (6*16+1*16*16)]); 
					svst1_ver_za32(1, 7, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (7*16+1*16*16)]); 
					svst1_ver_za32(1, 8, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (8*16+1*16*16)]); 
					svst1_ver_za32(1, 9, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (9*16+1*16*16)]); 
					svst1_ver_za32(1, 10, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (10*16+1*16*16)]); 
					svst1_ver_za32(1, 11, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (11*16+1*16*16)]); 
					svst1_ver_za32(1, 12, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (12*16+1*16*16)]); 
					svst1_ver_za32(1, 13, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (13*16+1*16*16)]); 
					svst1_ver_za32(1, 14, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (14*16+1*16*16)]); 
					svst1_ver_za32(1, 15, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (15*16+1*16*16)]); 
					svst1_ver_za32(2, 0, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (2*16*16)]); 
					svst1_ver_za32(2, 1, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (1*16+2*16*16)]); 
					svst1_ver_za32(2, 2, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (2*16+2*16*16)]); 
					svst1_ver_za32(2, 3, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (3*16+2*16*16)]); 
					svst1_ver_za32(2, 4, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (4*16+2*16*16)]); 
					svst1_ver_za32(2, 5, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (5*16+2*16*16)]); 
					svst1_ver_za32(2, 6, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (6*16+2*16*16)]); 
					svst1_ver_za32(2, 7, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (7*16+2*16*16)]); 
					svst1_ver_za32(2, 8, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (8*16+2*16*16)]); 
					svst1_ver_za32(2, 9, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (9*16+2*16*16)]); 
					svst1_ver_za32(2, 10, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (10*16+2*16*16)]); 
					svst1_ver_za32(2, 11, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (11*16+2*16*16)]); 
					svst1_ver_za32(2, 12, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (12*16+2*16*16)]); 
					svst1_ver_za32(2, 13, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (13*16+2*16*16)]); 
					svst1_ver_za32(2, 14, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (14*16+2*16*16)]); 
					svst1_ver_za32(2, 15, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (15*16+2*16*16)]); 
					svst1_ver_za32(3, 0, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (3*16*16)]); 
					svst1_ver_za32(3, 1, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (1*16+3*16*16)]); 
					svst1_ver_za32(3, 2, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (2*16+3*16*16)]); 
					svst1_ver_za32(3, 3, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (3*16+3*16*16)]); 
					svst1_ver_za32(3, 4, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (4*16+3*16*16)]); 
					svst1_ver_za32(3, 5, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (5*16+3*16*16)]); 
					svst1_ver_za32(3, 6, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (6*16+3*16*16)]); 
					svst1_ver_za32(3, 7, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (7*16+3*16*16)]); 
					svst1_ver_za32(3, 8, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (8*16+3*16*16)]); 
					svst1_ver_za32(3, 9, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (9*16+3*16*16)]); 
					svst1_ver_za32(3, 10, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (10*16+3*16*16)]); 
					svst1_ver_za32(3, 11, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (11*16+3*16*16)]); 
					svst1_ver_za32(3, 12, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (12*16+3*16*16)]); 
					svst1_ver_za32(3, 13, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (13*16+3*16*16)]); 
					svst1_ver_za32(3, 14, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (14*16+3*16*16)]); 
					svst1_ver_za32(3, 15, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (15*16+3*16*16)]); 
					// loading from grid 
					mask_x_0 = svwhilelt_b32(0, ker_size_x + 2); 
					svld1_hor_za32(0, 0, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + 0]); 
					svld1_hor_za32(0, 1, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*16)]); 
					svld1_hor_za32(0, 2, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*16)]); 
					svld1_hor_za32(0, 3, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*16)]); 
					svld1_hor_za32(0, 4, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy)]); 
					svld1_hor_za32(0, 5, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+1*16)]); 
					svld1_hor_za32(0, 6, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+2*16)]); 
					svld1_hor_za32(0, 7, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+3*16)]); 
					svld1_hor_za32(0, 8, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy)]); 
					svld1_hor_za32(0, 9, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+1*16)]); 
					svld1_hor_za32(0, 10, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+2*16)]); 
					svld1_hor_za32(0, 11, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+3*16)]); 
					svld1_hor_za32(0, 12, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy)]); 
					svld1_hor_za32(0, 13, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+1*16)]); 
					svld1_hor_za32(0, 14, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+2*16)]); 
					svld1_hor_za32(0, 15, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+3*16)]); 
					svld1_hor_za32(1, 0, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*16*4)]); 
					svld1_hor_za32(1, 1, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*16+1*16*4)]); 
					svld1_hor_za32(1, 2, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*16+1*16*4)]); 
					svld1_hor_za32(1, 3, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*16+1*16*4)]); 
					svld1_hor_za32(1, 4, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+1*16*4)]); 
					svld1_hor_za32(1, 5, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+1*16+1*16*4)]); 
					svld1_hor_za32(1, 6, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+2*16+1*16*4)]); 
					svld1_hor_za32(1, 7, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+3*16+1*16*4)]); 
					svld1_hor_za32(1, 8, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+1*16*4)]); 
					svld1_hor_za32(1, 9, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+1*16+1*16*4)]); 
					svld1_hor_za32(1, 10, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+2*16+1*16*4)]); 
					svld1_hor_za32(1, 11, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+3*16+1*16*4)]); 
					svld1_hor_za32(1, 12, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+1*16*4)]); 
					svld1_hor_za32(1, 13, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+1*16+1*16*4)]); 
					svld1_hor_za32(1, 14, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+2*16+1*16*4)]); 
					svld1_hor_za32(1, 15, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+3*16+1*16*4)]); 
					svld1_hor_za32(2, 0, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*16*4)]); 
					svld1_hor_za32(2, 1, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*16+2*16*4)]); 
					svld1_hor_za32(2, 2, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*16+2*16*4)]); 
					svld1_hor_za32(2, 3, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*16+2*16*4)]); 
					svld1_hor_za32(2, 4, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+2*16*4)]); 
					svld1_hor_za32(2, 5, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+1*16+2*16*4)]); 
					svld1_hor_za32(2, 6, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+2*16+2*16*4)]); 
					svld1_hor_za32(2, 7, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+3*16+2*16*4)]); 
					svld1_hor_za32(2, 8, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+2*16*4)]); 
					svld1_hor_za32(2, 9, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+1*16+2*16*4)]); 
					svld1_hor_za32(2, 10, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+2*16+2*16*4)]); 
					svld1_hor_za32(2, 11, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+3*16+2*16*4)]); 
					svld1_hor_za32(2, 12, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+2*16*4)]); 
					svld1_hor_za32(2, 13, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+1*16+2*16*4)]); 
					svld1_hor_za32(2, 14, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+2*16+2*16*4)]); 
					svld1_hor_za32(2, 15, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+3*16+2*16*4)]); 
					svld1_hor_za32(3, 0, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*16*4)]); 
					svld1_hor_za32(3, 1, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*16+3*16*4)]); 
					svld1_hor_za32(3, 2, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*16+3*16*4)]); 
					svld1_hor_za32(3, 3, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*16+3*16*4)]); 
					svld1_hor_za32(3, 4, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+3*16*4)]); 
					svld1_hor_za32(3, 5, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+1*16+3*16*4)]); 
					svld1_hor_za32(3, 6, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+2*16+3*16*4)]); 
					svld1_hor_za32(3, 7, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+3*16+3*16*4)]); 
					svld1_hor_za32(3, 8, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+3*16*4)]); 
					svld1_hor_za32(3, 9, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+1*16+3*16*4)]); 
					svld1_hor_za32(3, 10, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+2*16+3*16*4)]); 
					svld1_hor_za32(3, 11, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+3*16+3*16*4)]); 
					svld1_hor_za32(3, 12, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+3*16*4)]); 
					svld1_hor_za32(3, 13, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+1*16+3*16*4)]); 
					svld1_hor_za32(3, 14, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+2*16+3*16*4)]); 
					svld1_hor_za32(3, 15, mask_x_0, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+3*16+3*16*4)]); 
					//tranpose and store back to grid
					svst1_ver_za32(0, 0, p32_all, &(buffer_0 + (iz/4)*3072)[0 + 0]); 
					svst1_ver_za32(0, 1, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (1*16)]); 
					svst1_ver_za32(0, 2, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (2*16)]); 
					svst1_ver_za32(0, 3, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (3*16)]); 
					svst1_ver_za32(0, 4, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (4*16)]); 
					svst1_ver_za32(0, 5, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (5*16)]); 
					svst1_ver_za32(0, 6, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (6*16)]); 
					svst1_ver_za32(0, 7, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (7*16)]); 
					svst1_ver_za32(0, 8, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (8*16)]); 
					svst1_ver_za32(0, 9, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (9*16)]); 
					svst1_ver_za32(0, 10, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (10*16)]); 
					svst1_ver_za32(0, 11, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (11*16)]); 
					svst1_ver_za32(0, 12, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (12*16)]); 
					svst1_ver_za32(0, 13, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (13*16)]); 
					svst1_ver_za32(0, 14, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (14*16)]); 
					svst1_ver_za32(0, 15, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (15*16)]); 
					svst1_ver_za32(1, 0, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (1*16*16)]); 
					svst1_ver_za32(1, 1, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (1*16+1*16*16)]); 
					svst1_ver_za32(1, 2, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (2*16+1*16*16)]); 
					svst1_ver_za32(1, 3, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (3*16+1*16*16)]); 
					svst1_ver_za32(1, 4, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (4*16+1*16*16)]); 
					svst1_ver_za32(1, 5, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (5*16+1*16*16)]); 
					svst1_ver_za32(1, 6, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (6*16+1*16*16)]); 
					svst1_ver_za32(1, 7, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (7*16+1*16*16)]); 
					svst1_ver_za32(1, 8, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (8*16+1*16*16)]); 
					svst1_ver_za32(1, 9, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (9*16+1*16*16)]); 
					svst1_ver_za32(1, 10, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (10*16+1*16*16)]); 
					svst1_ver_za32(1, 11, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (11*16+1*16*16)]); 
					svst1_ver_za32(1, 12, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (12*16+1*16*16)]); 
					svst1_ver_za32(1, 13, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (13*16+1*16*16)]); 
					svst1_ver_za32(1, 14, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (14*16+1*16*16)]); 
					svst1_ver_za32(1, 15, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (15*16+1*16*16)]); 
					svst1_ver_za32(2, 0, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (2*16*16)]); 
					svst1_ver_za32(2, 1, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (1*16+2*16*16)]); 
					svst1_ver_za32(2, 2, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (2*16+2*16*16)]); 
					svst1_ver_za32(2, 3, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (3*16+2*16*16)]); 
					svst1_ver_za32(2, 4, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (4*16+2*16*16)]); 
					svst1_ver_za32(2, 5, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (5*16+2*16*16)]); 
					svst1_ver_za32(2, 6, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (6*16+2*16*16)]); 
					svst1_ver_za32(2, 7, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (7*16+2*16*16)]); 
					svst1_ver_za32(2, 8, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (8*16+2*16*16)]); 
					svst1_ver_za32(2, 9, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (9*16+2*16*16)]); 
					svst1_ver_za32(2, 10, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (10*16+2*16*16)]); 
					svst1_ver_za32(2, 11, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (11*16+2*16*16)]); 
					svst1_ver_za32(2, 12, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (12*16+2*16*16)]); 
					svst1_ver_za32(2, 13, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (13*16+2*16*16)]); 
					svst1_ver_za32(2, 14, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (14*16+2*16*16)]); 
					svst1_ver_za32(2, 15, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (15*16+2*16*16)]); 
					svst1_ver_za32(3, 0, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (3*16*16)]); 
					svst1_ver_za32(3, 1, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (1*16+3*16*16)]); 
					svst1_ver_za32(3, 2, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (2*16+3*16*16)]); 
					svst1_ver_za32(3, 3, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (3*16+3*16*16)]); 
					svst1_ver_za32(3, 4, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (4*16+3*16*16)]); 
					svst1_ver_za32(3, 5, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (5*16+3*16*16)]); 
					svst1_ver_za32(3, 6, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (6*16+3*16*16)]); 
					svst1_ver_za32(3, 7, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (7*16+3*16*16)]); 
					svst1_ver_za32(3, 8, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (8*16+3*16*16)]); 
					svst1_ver_za32(3, 9, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (9*16+3*16*16)]); 
					svst1_ver_za32(3, 10, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (10*16+3*16*16)]); 
					svst1_ver_za32(3, 11, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (11*16+3*16*16)]); 
					svst1_ver_za32(3, 12, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (12*16+3*16*16)]); 
					svst1_ver_za32(3, 13, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (13*16+3*16*16)]); 
					svst1_ver_za32(3, 14, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (14*16+3*16*16)]); 
					svst1_ver_za32(3, 15, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (15*16+3*16*16)]); 
				}
				//loop in x dimension starts
				for(int vx = 0; vx < ker_size_x; vx += 16) {
					prefetch_mask = svdup_b32(vx + 16 < ker_size_x);
					svprfb_gather_offset(prefetch_mask, ptr_src + 2*16*4*4 + -1*sy, index_vec, SV_PLDL1KEEP);
					svprfb_gather_offset(prefetch_mask, ptr_src + 2*16*4*4 + 0*sy, index_vec, SV_PLDL1KEEP);
					svprfb_gather_offset(prefetch_mask, ptr_src + 2*16*4*4 + 1*sy, index_vec, SV_PLDL1KEEP);
					svprfb_gather_offset(prefetch_mask, ptr_src + 2*16*4*4 + 2*sy, index_vec, SV_PLDL1KEEP);
					svprfb_gather_offset(prefetch_mask, ptr_src + 2*16*4*4 + 3*sy, index_vec, SV_PLDL1KEEP);
					svprfb_gather_offset(prefetch_mask, ptr_src + 2*16*4*4 + 4*sy, index_vec, SV_PLDL1KEEP);
					svprfb_gather_offset(prefetch_mask, ptr_src + 2*16*4*4 + 0*sy + sz, index_vec, SV_PLDL1KEEP);
					svprfb_gather_offset(prefetch_mask, ptr_src + 2*16*4*4 + 1*sy + sz, index_vec, SV_PLDL1KEEP);
					svprfb_gather_offset(prefetch_mask, ptr_src + 2*16*4*4 + 2*sy + sz, index_vec, SV_PLDL1KEEP);
					svprfb_gather_offset(prefetch_mask, ptr_src + 2*16*4*4 + 3*sy + sz, index_vec, SV_PLDL1KEEP);

					for(int iz = 0; iz < 4; iz += 4) {
						temp_dst = buffer + 1*(3072) + (iz / 4)*1024;
						ptr_m1 = (buffer_m1 + (iz/4)*(3072) + 224); ptr_0 = buffer_0 + (iz/4)*(3072); ptr_1 = buffer_1 + (iz/4)*(3072);
						// loading from grid 
						mask_x_0 = svwhilelt_b32(0, ker_size_x - vx + 2 - 16); 
						svld1_hor_za32(0, 0, mask_x_0, &(ptr_src + (1*16*4*4))[0 + 0]); 
						svld1_hor_za32(0, 1, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (1*16)]); 
						svld1_hor_za32(0, 2, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (2*16)]); 
						svld1_hor_za32(0, 3, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (3*16)]); 
						svld1_hor_za32(0, 4, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (1*sy)]); 
						svld1_hor_za32(0, 5, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (1*sy+1*16)]); 
						svld1_hor_za32(0, 6, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (1*sy+2*16)]); 
						svld1_hor_za32(0, 7, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (1*sy+3*16)]); 
						svld1_hor_za32(0, 8, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (2*sy)]); 
						svld1_hor_za32(0, 9, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (2*sy+1*16)]); 
						svld1_hor_za32(0, 10, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (2*sy+2*16)]); 
						svld1_hor_za32(0, 11, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (2*sy+3*16)]); 
						svld1_hor_za32(0, 12, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (3*sy)]); 
						svld1_hor_za32(0, 13, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (3*sy+1*16)]); 
						svld1_hor_za32(0, 14, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (3*sy+2*16)]); 
						svld1_hor_za32(0, 15, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (3*sy+3*16)]); 
						svld1_hor_za32(1, 0, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (1*16*4)]); 
						svld1_hor_za32(1, 1, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (1*16+1*16*4)]); 
						svld1_hor_za32(1, 2, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (2*16+1*16*4)]); 
						svld1_hor_za32(1, 3, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (3*16+1*16*4)]); 
						svld1_hor_za32(1, 4, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (1*sy+1*16*4)]); 
						svld1_hor_za32(1, 5, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (1*sy+1*16+1*16*4)]); 
						svld1_hor_za32(1, 6, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (1*sy+2*16+1*16*4)]); 
						svld1_hor_za32(1, 7, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (1*sy+3*16+1*16*4)]); 
						svld1_hor_za32(1, 8, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (2*sy+1*16*4)]); 
						svld1_hor_za32(1, 9, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (2*sy+1*16+1*16*4)]); 
						svld1_hor_za32(1, 10, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (2*sy+2*16+1*16*4)]); 
						svld1_hor_za32(1, 11, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (2*sy+3*16+1*16*4)]); 
						svld1_hor_za32(1, 12, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (3*sy+1*16*4)]); 
						svld1_hor_za32(1, 13, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (3*sy+1*16+1*16*4)]); 
						svld1_hor_za32(1, 14, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (3*sy+2*16+1*16*4)]); 
						svld1_hor_za32(1, 15, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (3*sy+3*16+1*16*4)]); 
						svld1_hor_za32(2, 0, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (2*16*4)]); 
						svld1_hor_za32(2, 1, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (1*16+2*16*4)]); 
						svld1_hor_za32(2, 2, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (2*16+2*16*4)]); 
						svld1_hor_za32(2, 3, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (3*16+2*16*4)]); 
						svld1_hor_za32(2, 4, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (1*sy+2*16*4)]); 
						svld1_hor_za32(2, 5, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (1*sy+1*16+2*16*4)]); 
						svld1_hor_za32(2, 6, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (1*sy+2*16+2*16*4)]); 
						svld1_hor_za32(2, 7, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (1*sy+3*16+2*16*4)]); 
						svld1_hor_za32(2, 8, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (2*sy+2*16*4)]); 
						svld1_hor_za32(2, 9, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (2*sy+1*16+2*16*4)]); 
						svld1_hor_za32(2, 10, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (2*sy+2*16+2*16*4)]); 
						svld1_hor_za32(2, 11, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (2*sy+3*16+2*16*4)]); 
						svld1_hor_za32(2, 12, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (3*sy+2*16*4)]); 
						svld1_hor_za32(2, 13, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (3*sy+1*16+2*16*4)]); 
						svld1_hor_za32(2, 14, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (3*sy+2*16+2*16*4)]); 
						svld1_hor_za32(2, 15, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (3*sy+3*16+2*16*4)]); 
						svld1_hor_za32(3, 0, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (3*16*4)]); 
						svld1_hor_za32(3, 1, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (1*16+3*16*4)]); 
						svld1_hor_za32(3, 2, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (2*16+3*16*4)]); 
						svld1_hor_za32(3, 3, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (3*16+3*16*4)]); 
						svld1_hor_za32(3, 4, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (1*sy+3*16*4)]); 
						svld1_hor_za32(3, 5, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (1*sy+1*16+3*16*4)]); 
						svld1_hor_za32(3, 6, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (1*sy+2*16+3*16*4)]); 
						svld1_hor_za32(3, 7, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (1*sy+3*16+3*16*4)]); 
						svld1_hor_za32(3, 8, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (2*sy+3*16*4)]); 
						svld1_hor_za32(3, 9, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (2*sy+1*16+3*16*4)]); 
						svld1_hor_za32(3, 10, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (2*sy+2*16+3*16*4)]); 
						svld1_hor_za32(3, 11, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (2*sy+3*16+3*16*4)]); 
						svld1_hor_za32(3, 12, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (3*sy+3*16*4)]); 
						svld1_hor_za32(3, 13, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (3*sy+1*16+3*16*4)]); 
						svld1_hor_za32(3, 14, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (3*sy+2*16+3*16*4)]); 
						svld1_hor_za32(3, 15, mask_x_0, &(ptr_src + (1*16*4*4))[0 + (3*sy+3*16+3*16*4)]); 
						//tranpose and store back to grid
						svst1_ver_za32(0, 0, p32_all, &ptr_1[0 + 0]); 
						svst1_ver_za32(0, 1, p32_all, &ptr_1[0 + (1*16)]); 
						svst1_ver_za32(0, 2, p32_all, &ptr_1[0 + (2*16)]); 
						svst1_ver_za32(0, 3, p32_all, &ptr_1[0 + (3*16)]); 
						svst1_ver_za32(0, 4, p32_all, &ptr_1[0 + (4*16)]); 
						svst1_ver_za32(0, 5, p32_all, &ptr_1[0 + (5*16)]); 
						svst1_ver_za32(0, 6, p32_all, &ptr_1[0 + (6*16)]); 
						svst1_ver_za32(0, 7, p32_all, &ptr_1[0 + (7*16)]); 
						svst1_ver_za32(0, 8, p32_all, &ptr_1[0 + (8*16)]); 
						svst1_ver_za32(0, 9, p32_all, &ptr_1[0 + (9*16)]); 
						svst1_ver_za32(0, 10, p32_all, &ptr_1[0 + (10*16)]); 
						svst1_ver_za32(0, 11, p32_all, &ptr_1[0 + (11*16)]); 
						svst1_ver_za32(0, 12, p32_all, &ptr_1[0 + (12*16)]); 
						svst1_ver_za32(0, 13, p32_all, &ptr_1[0 + (13*16)]); 
						svst1_ver_za32(0, 14, p32_all, &ptr_1[0 + (14*16)]); 
						svst1_ver_za32(0, 15, p32_all, &ptr_1[0 + (15*16)]); 
						svst1_ver_za32(1, 0, p32_all, &ptr_1[0 + (1*16*16)]); 
						svst1_ver_za32(1, 1, p32_all, &ptr_1[0 + (1*16+1*16*16)]); 
						svst1_ver_za32(1, 2, p32_all, &ptr_1[0 + (2*16+1*16*16)]); 
						svst1_ver_za32(1, 3, p32_all, &ptr_1[0 + (3*16+1*16*16)]); 
						svst1_ver_za32(1, 4, p32_all, &ptr_1[0 + (4*16+1*16*16)]); 
						svst1_ver_za32(1, 5, p32_all, &ptr_1[0 + (5*16+1*16*16)]); 
						svst1_ver_za32(1, 6, p32_all, &ptr_1[0 + (6*16+1*16*16)]); 
						svst1_ver_za32(1, 7, p32_all, &ptr_1[0 + (7*16+1*16*16)]); 
						svst1_ver_za32(1, 8, p32_all, &ptr_1[0 + (8*16+1*16*16)]); 
						svst1_ver_za32(1, 9, p32_all, &ptr_1[0 + (9*16+1*16*16)]); 
						svst1_ver_za32(1, 10, p32_all, &ptr_1[0 + (10*16+1*16*16)]); 
						svst1_ver_za32(1, 11, p32_all, &ptr_1[0 + (11*16+1*16*16)]); 
						svst1_ver_za32(1, 12, p32_all, &ptr_1[0 + (12*16+1*16*16)]); 
						svst1_ver_za32(1, 13, p32_all, &ptr_1[0 + (13*16+1*16*16)]); 
						svst1_ver_za32(1, 14, p32_all, &ptr_1[0 + (14*16+1*16*16)]); 
						svst1_ver_za32(1, 15, p32_all, &ptr_1[0 + (15*16+1*16*16)]); 
						svst1_ver_za32(2, 0, p32_all, &ptr_1[0 + (2*16*16)]); 
						svst1_ver_za32(2, 1, p32_all, &ptr_1[0 + (1*16+2*16*16)]); 
						svst1_ver_za32(2, 2, p32_all, &ptr_1[0 + (2*16+2*16*16)]); 
						svst1_ver_za32(2, 3, p32_all, &ptr_1[0 + (3*16+2*16*16)]); 
						svst1_ver_za32(2, 4, p32_all, &ptr_1[0 + (4*16+2*16*16)]); 
						svst1_ver_za32(2, 5, p32_all, &ptr_1[0 + (5*16+2*16*16)]); 
						svst1_ver_za32(2, 6, p32_all, &ptr_1[0 + (6*16+2*16*16)]); 
						svst1_ver_za32(2, 7, p32_all, &ptr_1[0 + (7*16+2*16*16)]); 
						svst1_ver_za32(2, 8, p32_all, &ptr_1[0 + (8*16+2*16*16)]); 
						svst1_ver_za32(2, 9, p32_all, &ptr_1[0 + (9*16+2*16*16)]); 
						svst1_ver_za32(2, 10, p32_all, &ptr_1[0 + (10*16+2*16*16)]); 
						svst1_ver_za32(2, 11, p32_all, &ptr_1[0 + (11*16+2*16*16)]); 
						svst1_ver_za32(2, 12, p32_all, &ptr_1[0 + (12*16+2*16*16)]); 
						svst1_ver_za32(2, 13, p32_all, &ptr_1[0 + (13*16+2*16*16)]); 
						svst1_ver_za32(2, 14, p32_all, &ptr_1[0 + (14*16+2*16*16)]); 
						svst1_ver_za32(2, 15, p32_all, &ptr_1[0 + (15*16+2*16*16)]); 
						svst1_ver_za32(3, 0, p32_all, &ptr_1[0 + (3*16*16)]); 
						svst1_ver_za32(3, 1, p32_all, &ptr_1[0 + (1*16+3*16*16)]); 
						svst1_ver_za32(3, 2, p32_all, &ptr_1[0 + (2*16+3*16*16)]); 
						svst1_ver_za32(3, 3, p32_all, &ptr_1[0 + (3*16+3*16*16)]); 
						svst1_ver_za32(3, 4, p32_all, &ptr_1[0 + (4*16+3*16*16)]); 
						svst1_ver_za32(3, 5, p32_all, &ptr_1[0 + (5*16+3*16*16)]); 
						svst1_ver_za32(3, 6, p32_all, &ptr_1[0 + (6*16+3*16*16)]); 
						svst1_ver_za32(3, 7, p32_all, &ptr_1[0 + (7*16+3*16*16)]); 
						svst1_ver_za32(3, 8, p32_all, &ptr_1[0 + (8*16+3*16*16)]); 
						svst1_ver_za32(3, 9, p32_all, &ptr_1[0 + (9*16+3*16*16)]); 
						svst1_ver_za32(3, 10, p32_all, &ptr_1[0 + (10*16+3*16*16)]); 
						svst1_ver_za32(3, 11, p32_all, &ptr_1[0 + (11*16+3*16*16)]); 
						svst1_ver_za32(3, 12, p32_all, &ptr_1[0 + (12*16+3*16*16)]); 
						svst1_ver_za32(3, 13, p32_all, &ptr_1[0 + (13*16+3*16*16)]); 
						svst1_ver_za32(3, 14, p32_all, &ptr_1[0 + (14*16+3*16*16)]); 
						svst1_ver_za32(3, 15, p32_all, &ptr_1[0 + (15*16+3*16*16)]); 
						svzero_mask_za(0x1); svzero_mask_za(0x10); 
						svzero_mask_za(0x2); svzero_mask_za(0x20); 
						svzero_mask_za(0x4); svzero_mask_za(0x40); 
						svzero_mask_za(0x8); svzero_mask_za(0x80); 
						// declare input vector registers
						svfloat32_t sme_input_x0,sme_input_x1,sme_input_x2,sme_input_x3; 
						// declare input coefficients
						svfloat32_t alpha_vec_x = svdup_f32_x(p32_all, 0); 
						// load vector at (-2, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, coef[0]); 
						sme_input_x0 = svld1(p32_all, &ptr_m1[0 + 0]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_m1[0 + (1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_m1[0 + (2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_m1[0 + (3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (-1, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, coef[1]); 
						sme_input_x0 = svld1(p32_all, &ptr_m1[0 + (1*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_m1[0 + (1*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_m1[0 + (1*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_m1[0 + (1*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (0, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, coef[2]); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + 0]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (1, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, coef[3]); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (1*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (1*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (1*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (1*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (2, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, coef[4]); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (2*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (2*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (2*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (2*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (3, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (3*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (3*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (3*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (3*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (4, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (4*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (4*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (4*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (4*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (5, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (5*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (5*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (5*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (5*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (6, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (6*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (6*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (6*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (6*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (7, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (7*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (7*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (7*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (7*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (8, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (8*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (8*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (8*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (8*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (9, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (9*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (9*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (9*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (9*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (10, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (10*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (10*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (10*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (10*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (11, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (11*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (11*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (11*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (11*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (12, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (12*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (12*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (12*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (12*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (13, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (13*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (13*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (13*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (13*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (14, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (14*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (14*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (14*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (14*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (15, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (15*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (15*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (15*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (15*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (16, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_1[0 + 0]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_1[0 + (1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_1[0 + (2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_1[0 + (3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (17, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_1[0 + (1*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_1[0 + (1*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_1[0 + (1*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_1[0 + (1*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// declare input vector registers
						svfloat32_t sme_input_y00,sme_input_y10,sme_input_y20,sme_input_y30; 
						// declare input coefficients
						svfloat32_t alpha_vec_y = svdup_f32_x(p32_all, 0); 
						mask_x_0 = svwhilelt_b32(0, ker_size_x - vx + 2); 
						// load vector at (0, -2, 0)
						alpha_vec_y = svinsr(alpha_vec_y, coef[0]); 
						sme_input_y00 = svld1(mask_x_0, &ptr_l[0 + 0]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						sme_input_y10 = svld1(mask_x_0, &ptr_l[0 + (1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						sme_input_y20 = svld1(mask_x_0, &ptr_l[0 + (2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						sme_input_y30 = svld1(mask_x_0, &ptr_l[0 + (3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, -1, 0)
						alpha_vec_y = svinsr(alpha_vec_y, coef[1]); 
						sme_input_y00 = svld1(mask_x_0, &ptr_l[0 + (1*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						sme_input_y10 = svld1(mask_x_0, &ptr_l[0 + (1*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						sme_input_y20 = svld1(mask_x_0, &ptr_l[0 + (1*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						sme_input_y30 = svld1(mask_x_0, &ptr_l[0 + (1*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 0, 0)
						alpha_vec_y = svinsr(alpha_vec_y, coef[2]); 
						sme_input_y00 = svld1(mask_x_0, &ptr_src[0 + 0]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						sme_input_y10 = svld1(mask_x_0, &ptr_src[0 + (1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						sme_input_y20 = svld1(mask_x_0, &ptr_src[0 + (2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						sme_input_y30 = svld1(mask_x_0, &ptr_src[0 + (3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 1, 0)
						alpha_vec_y = svinsr(alpha_vec_y, coef[3]); 
						sme_input_y00 = svld1(mask_x_0, &ptr_src[0 + (1*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						sme_input_y10 = svld1(mask_x_0, &ptr_src[0 + (1*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						sme_input_y20 = svld1(mask_x_0, &ptr_src[0 + (1*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						sme_input_y30 = svld1(mask_x_0, &ptr_src[0 + (1*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 2, 0)
						alpha_vec_y = svinsr(alpha_vec_y, coef[4]); 
						sme_input_y00 = svld1(mask_x_0, &ptr_src[0 + (2*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						sme_input_y10 = svld1(mask_x_0, &ptr_src[0 + (2*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						sme_input_y20 = svld1(mask_x_0, &ptr_src[0 + (2*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						sme_input_y30 = svld1(mask_x_0, &ptr_src[0 + (2*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 3, 0)
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						sme_input_y00 = svld1(mask_x_0, &ptr_src[0 + (3*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						sme_input_y10 = svld1(mask_x_0, &ptr_src[0 + (3*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						sme_input_y20 = svld1(mask_x_0, &ptr_src[0 + (3*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						sme_input_y30 = svld1(mask_x_0, &ptr_src[0 + (3*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 4, 0)
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						sme_input_y00 = svld1(mask_x_0, &ptr_src[0 + (1*sy)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						sme_input_y10 = svld1(mask_x_0, &ptr_src[0 + (1*sy+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						sme_input_y20 = svld1(mask_x_0, &ptr_src[0 + (1*sy+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						sme_input_y30 = svld1(mask_x_0, &ptr_src[0 + (1*sy+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 5, 0)
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						sme_input_y00 = svld1(mask_x_0, &ptr_src[0 + (1*sy+1*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						sme_input_y10 = svld1(mask_x_0, &ptr_src[0 + (1*sy+1*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						sme_input_y20 = svld1(mask_x_0, &ptr_src[0 + (1*sy+1*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						sme_input_y30 = svld1(mask_x_0, &ptr_src[0 + (1*sy+1*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 6, 0)
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						sme_input_y00 = svld1(mask_x_0, &ptr_src[0 + (1*sy+2*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						sme_input_y10 = svld1(mask_x_0, &ptr_src[0 + (1*sy+2*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						sme_input_y20 = svld1(mask_x_0, &ptr_src[0 + (1*sy+2*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						sme_input_y30 = svld1(mask_x_0, &ptr_src[0 + (1*sy+2*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 7, 0)
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						sme_input_y00 = svld1(mask_x_0, &ptr_src[0 + (1*sy+3*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						sme_input_y10 = svld1(mask_x_0, &ptr_src[0 + (1*sy+3*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						sme_input_y20 = svld1(mask_x_0, &ptr_src[0 + (1*sy+3*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						sme_input_y30 = svld1(mask_x_0, &ptr_src[0 + (1*sy+3*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 8, 0)
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						sme_input_y00 = svld1(mask_x_0, &ptr_src[0 + (2*sy)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						sme_input_y10 = svld1(mask_x_0, &ptr_src[0 + (2*sy+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						sme_input_y20 = svld1(mask_x_0, &ptr_src[0 + (2*sy+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						sme_input_y30 = svld1(mask_x_0, &ptr_src[0 + (2*sy+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 9, 0)
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						sme_input_y00 = svld1(mask_x_0, &ptr_src[0 + (2*sy+1*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						sme_input_y10 = svld1(mask_x_0, &ptr_src[0 + (2*sy+1*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						sme_input_y20 = svld1(mask_x_0, &ptr_src[0 + (2*sy+1*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						sme_input_y30 = svld1(mask_x_0, &ptr_src[0 + (2*sy+1*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 10, 0)
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						sme_input_y00 = svld1(mask_x_0, &ptr_src[0 + (2*sy+2*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						sme_input_y10 = svld1(mask_x_0, &ptr_src[0 + (2*sy+2*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						sme_input_y20 = svld1(mask_x_0, &ptr_src[0 + (2*sy+2*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						sme_input_y30 = svld1(mask_x_0, &ptr_src[0 + (2*sy+2*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 11, 0)
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						sme_input_y00 = svld1(mask_x_0, &ptr_src[0 + (2*sy+3*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						sme_input_y10 = svld1(mask_x_0, &ptr_src[0 + (2*sy+3*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						sme_input_y20 = svld1(mask_x_0, &ptr_src[0 + (2*sy+3*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						sme_input_y30 = svld1(mask_x_0, &ptr_src[0 + (2*sy+3*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 12, 0)
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						sme_input_y00 = svld1(mask_x_0, &ptr_src[0 + (3*sy)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						sme_input_y10 = svld1(mask_x_0, &ptr_src[0 + (3*sy+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						sme_input_y20 = svld1(mask_x_0, &ptr_src[0 + (3*sy+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						sme_input_y30 = svld1(mask_x_0, &ptr_src[0 + (3*sy+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 13, 0)
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						sme_input_y00 = svld1(mask_x_0, &ptr_src[0 + (3*sy+1*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						sme_input_y10 = svld1(mask_x_0, &ptr_src[0 + (3*sy+1*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						sme_input_y20 = svld1(mask_x_0, &ptr_src[0 + (3*sy+1*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						sme_input_y30 = svld1(mask_x_0, &ptr_src[0 + (3*sy+1*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 14, 0)
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						sme_input_y00 = svld1(mask_x_0, &ptr_src[0 + (3*sy+2*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						sme_input_y10 = svld1(mask_x_0, &ptr_src[0 + (3*sy+2*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						sme_input_y20 = svld1(mask_x_0, &ptr_src[0 + (3*sy+2*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						sme_input_y30 = svld1(mask_x_0, &ptr_src[0 + (3*sy+2*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 15, 0)
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						sme_input_y00 = svld1(mask_x_0, &ptr_src[0 + (3*sy+3*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						sme_input_y10 = svld1(mask_x_0, &ptr_src[0 + (3*sy+3*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						sme_input_y20 = svld1(mask_x_0, &ptr_src[0 + (3*sy+3*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						sme_input_y30 = svld1(mask_x_0, &ptr_src[0 + (3*sy+3*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 16, 0)
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						sme_input_y00 = svld1(mask_x_0, &ptr_r[0 + 0]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						sme_input_y10 = svld1(mask_x_0, &ptr_r[0 + (1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						sme_input_y20 = svld1(mask_x_0, &ptr_r[0 + (2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						sme_input_y30 = svld1(mask_x_0, &ptr_r[0 + (3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 17, 0)
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						sme_input_y00 = svld1(mask_x_0, &ptr_r[0 + (1*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						sme_input_y10 = svld1(mask_x_0, &ptr_r[0 + (1*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						sme_input_y20 = svld1(mask_x_0, &ptr_r[0 + (1*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						sme_input_y30 = svld1(mask_x_0, &ptr_r[0 + (1*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						mask_x_0 = svwhilelt_b32(0, 16); 
						svst1_hor_za32(0, 0, mask_x_0, &temp_dst[0 + 0]); 
						svst1_hor_za32(0, 1, mask_x_0, &temp_dst[0 + (1*16)]); 
						svst1_hor_za32(0, 2, mask_x_0, &temp_dst[0 + (2*16)]); 
						svst1_hor_za32(0, 3, mask_x_0, &temp_dst[0 + (3*16)]); 
						svst1_hor_za32(0, 4, mask_x_0, &temp_dst[0 + (1*256)]); 
						svst1_hor_za32(0, 5, mask_x_0, &temp_dst[0 + (1*256+1*16)]); 
						svst1_hor_za32(0, 6, mask_x_0, &temp_dst[0 + (1*256+2*16)]); 
						svst1_hor_za32(0, 7, mask_x_0, &temp_dst[0 + (1*256+3*16)]); 
						svst1_hor_za32(0, 8, mask_x_0, &temp_dst[0 + (2*256)]); 
						svst1_hor_za32(0, 9, mask_x_0, &temp_dst[0 + (2*256+1*16)]); 
						svst1_hor_za32(0, 10, mask_x_0, &temp_dst[0 + (2*256+2*16)]); 
						svst1_hor_za32(0, 11, mask_x_0, &temp_dst[0 + (2*256+3*16)]); 
						svst1_hor_za32(0, 12, mask_x_0, &temp_dst[0 + (3*256)]); 
						svst1_hor_za32(0, 13, mask_x_0, &temp_dst[0 + (3*256+1*16)]); 
						svst1_hor_za32(0, 14, mask_x_0, &temp_dst[0 + (3*256+2*16)]); 
						svst1_hor_za32(0, 15, mask_x_0, &temp_dst[0 + (3*256+3*16)]); 
						svst1_hor_za32(1, 0, mask_x_0, &temp_dst[0 + (1*16*4)]); 
						svst1_hor_za32(1, 1, mask_x_0, &temp_dst[0 + (1*16+1*16*4)]); 
						svst1_hor_za32(1, 2, mask_x_0, &temp_dst[0 + (2*16+1*16*4)]); 
						svst1_hor_za32(1, 3, mask_x_0, &temp_dst[0 + (3*16+1*16*4)]); 
						svst1_hor_za32(1, 4, mask_x_0, &temp_dst[0 + (1*256+1*16*4)]); 
						svst1_hor_za32(1, 5, mask_x_0, &temp_dst[0 + (1*256+1*16+1*16*4)]); 
						svst1_hor_za32(1, 6, mask_x_0, &temp_dst[0 + (1*256+2*16+1*16*4)]); 
						svst1_hor_za32(1, 7, mask_x_0, &temp_dst[0 + (1*256+3*16+1*16*4)]); 
						svst1_hor_za32(1, 8, mask_x_0, &temp_dst[0 + (2*256+1*16*4)]); 
						svst1_hor_za32(1, 9, mask_x_0, &temp_dst[0 + (2*256+1*16+1*16*4)]); 
						svst1_hor_za32(1, 10, mask_x_0, &temp_dst[0 + (2*256+2*16+1*16*4)]); 
						svst1_hor_za32(1, 11, mask_x_0, &temp_dst[0 + (2*256+3*16+1*16*4)]); 
						svst1_hor_za32(1, 12, mask_x_0, &temp_dst[0 + (3*256+1*16*4)]); 
						svst1_hor_za32(1, 13, mask_x_0, &temp_dst[0 + (3*256+1*16+1*16*4)]); 
						svst1_hor_za32(1, 14, mask_x_0, &temp_dst[0 + (3*256+2*16+1*16*4)]); 
						svst1_hor_za32(1, 15, mask_x_0, &temp_dst[0 + (3*256+3*16+1*16*4)]); 
						svst1_hor_za32(2, 0, mask_x_0, &temp_dst[0 + (2*16*4)]); 
						svst1_hor_za32(2, 1, mask_x_0, &temp_dst[0 + (1*16+2*16*4)]); 
						svst1_hor_za32(2, 2, mask_x_0, &temp_dst[0 + (2*16+2*16*4)]); 
						svst1_hor_za32(2, 3, mask_x_0, &temp_dst[0 + (3*16+2*16*4)]); 
						svst1_hor_za32(2, 4, mask_x_0, &temp_dst[0 + (1*256+2*16*4)]); 
						svst1_hor_za32(2, 5, mask_x_0, &temp_dst[0 + (1*256+1*16+2*16*4)]); 
						svst1_hor_za32(2, 6, mask_x_0, &temp_dst[0 + (1*256+2*16+2*16*4)]); 
						svst1_hor_za32(2, 7, mask_x_0, &temp_dst[0 + (1*256+3*16+2*16*4)]); 
						svst1_hor_za32(2, 8, mask_x_0, &temp_dst[0 + (2*256+2*16*4)]); 
						svst1_hor_za32(2, 9, mask_x_0, &temp_dst[0 + (2*256+1*16+2*16*4)]); 
						svst1_hor_za32(2, 10, mask_x_0, &temp_dst[0 + (2*256+2*16+2*16*4)]); 
						svst1_hor_za32(2, 11, mask_x_0, &temp_dst[0 + (2*256+3*16+2*16*4)]); 
						svst1_hor_za32(2, 12, mask_x_0, &temp_dst[0 + (3*256+2*16*4)]); 
						svst1_hor_za32(2, 13, mask_x_0, &temp_dst[0 + (3*256+1*16+2*16*4)]); 
						svst1_hor_za32(2, 14, mask_x_0, &temp_dst[0 + (3*256+2*16+2*16*4)]); 
						svst1_hor_za32(2, 15, mask_x_0, &temp_dst[0 + (3*256+3*16+2*16*4)]); 
						svst1_hor_za32(3, 0, mask_x_0, &temp_dst[0 + (3*16*4)]); 
						svst1_hor_za32(3, 1, mask_x_0, &temp_dst[0 + (1*16+3*16*4)]); 
						svst1_hor_za32(3, 2, mask_x_0, &temp_dst[0 + (2*16+3*16*4)]); 
						svst1_hor_za32(3, 3, mask_x_0, &temp_dst[0 + (3*16+3*16*4)]); 
						svst1_hor_za32(3, 4, mask_x_0, &temp_dst[0 + (1*256+3*16*4)]); 
						svst1_hor_za32(3, 5, mask_x_0, &temp_dst[0 + (1*256+1*16+3*16*4)]); 
						svst1_hor_za32(3, 6, mask_x_0, &temp_dst[0 + (1*256+2*16+3*16*4)]); 
						svst1_hor_za32(3, 7, mask_x_0, &temp_dst[0 + (1*256+3*16+3*16*4)]); 
						svst1_hor_za32(3, 8, mask_x_0, &temp_dst[0 + (2*256+3*16*4)]); 
						svst1_hor_za32(3, 9, mask_x_0, &temp_dst[0 + (2*256+1*16+3*16*4)]); 
						svst1_hor_za32(3, 10, mask_x_0, &temp_dst[0 + (2*256+2*16+3*16*4)]); 
						svst1_hor_za32(3, 11, mask_x_0, &temp_dst[0 + (2*256+3*16+3*16*4)]); 
						svst1_hor_za32(3, 12, mask_x_0, &temp_dst[0 + (3*256+3*16*4)]); 
						svst1_hor_za32(3, 13, mask_x_0, &temp_dst[0 + (3*256+1*16+3*16*4)]); 
						svst1_hor_za32(3, 14, mask_x_0, &temp_dst[0 + (3*256+2*16+3*16*4)]); 
						svst1_hor_za32(3, 15, mask_x_0, &temp_dst[0 + (3*256+3*16+3*16*4)]); 
						ptr_src += (1*sz); ptr_l += (1*sz); ptr_r += (1*sz); ptr_dst += (1*dz);
					}
					//restore pointers after xy computation
					ptr_src -= 1*(1*sz); ptr_l -= 1*(1*sz); ptr_r -= 1*(1*sz); ptr_dst -= 1*(1*dz);
					for(int iy = 0; iy < 16; iy += 4) {
						temp_dst = buffer + 1*(3072) + (iy / 4)*(1*256);
						mask_x_0 = svwhilelt_b32(0, 16); 
						svld1_hor_za32(0, 0, mask_x_0, &temp_dst[0 + 0]); 
						svld1_hor_za32(1, 0, mask_x_0, &temp_dst[0 + (1*16)]); 
						svld1_hor_za32(2, 0, mask_x_0, &temp_dst[0 + (2*16)]); 
						svld1_hor_za32(3, 0, mask_x_0, &temp_dst[0 + (3*16)]); 
						svld1_hor_za32(0, 1, mask_x_0, &temp_dst[0 + (1*16*4)]); 
						svld1_hor_za32(1, 1, mask_x_0, &temp_dst[0 + (1*16+1*16*4)]); 
						svld1_hor_za32(2, 1, mask_x_0, &temp_dst[0 + (2*16+1*16*4)]); 
						svld1_hor_za32(3, 1, mask_x_0, &temp_dst[0 + (3*16+1*16*4)]); 
						svld1_hor_za32(0, 2, mask_x_0, &temp_dst[0 + (2*16*4)]); 
						svld1_hor_za32(1, 2, mask_x_0, &temp_dst[0 + (1*16+2*16*4)]); 
						svld1_hor_za32(2, 2, mask_x_0, &temp_dst[0 + (2*16+2*16*4)]); 
						svld1_hor_za32(3, 2, mask_x_0, &temp_dst[0 + (3*16+2*16*4)]); 
						svld1_hor_za32(0, 3, mask_x_0, &temp_dst[0 + (3*16*4)]); 
						svld1_hor_za32(1, 3, mask_x_0, &temp_dst[0 + (1*16+3*16*4)]); 
						svld1_hor_za32(2, 3, mask_x_0, &temp_dst[0 + (2*16+3*16*4)]); 
						svld1_hor_za32(3, 3, mask_x_0, &temp_dst[0 + (3*16+3*16*4)]); 
						// declare input vector registers
						svfloat32_t sme_input_z00,sme_input_z10,sme_input_z20,sme_input_z30; 
						// declare input coefficients
						svfloat32_t alpha_vec_z = svdup_f32_x(p32_all, 0); 
						mask_x_0 = svwhilelt_b32(0, ker_size_x - vx); 
						// load vector at (0, 0, -2)
						alpha_vec_z = svinsr(alpha_vec_z, coef[0]); 
						sme_input_z00 = svld1(mask_x_0, &ptr_src[0 + (-1*sz+2*16*4)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_z, sme_input_z00); 
						
						sme_input_z10 = svld1(mask_x_0, &ptr_src[0 + (1*16+-1*sz+2*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_z, sme_input_z10); 
						
						sme_input_z20 = svld1(mask_x_0, &ptr_src[0 + (2*16+-1*sz+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_z, sme_input_z20); 
						
						sme_input_z30 = svld1(mask_x_0, &ptr_src[0 + (3*16+-1*sz+2*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_z, sme_input_z30); 
						
						// load vector at (0, 0, -1)
						alpha_vec_z = svinsr(alpha_vec_z, coef[1]); 
						sme_input_z00 = svld1(mask_x_0, &ptr_src[0 + (-1*sz+3*16*4)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_z, sme_input_z00); 
						
						sme_input_z10 = svld1(mask_x_0, &ptr_src[0 + (1*16+-1*sz+3*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_z, sme_input_z10); 
						
						sme_input_z20 = svld1(mask_x_0, &ptr_src[0 + (2*16+-1*sz+3*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_z, sme_input_z20); 
						
						sme_input_z30 = svld1(mask_x_0, &ptr_src[0 + (3*16+-1*sz+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_z, sme_input_z30); 
						
						// load vector at (0, 0, 0)
						alpha_vec_z = svinsr(alpha_vec_z, coef[2]); 
						sme_input_z00 = svld1(mask_x_0, &ptr_src[0 + 0]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_z, sme_input_z00); 
						
						sme_input_z10 = svld1(mask_x_0, &ptr_src[0 + (1*16)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_z, sme_input_z10); 
						
						sme_input_z20 = svld1(mask_x_0, &ptr_src[0 + (2*16)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_z, sme_input_z20); 
						
						sme_input_z30 = svld1(mask_x_0, &ptr_src[0 + (3*16)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_z, sme_input_z30); 
						
						// load vector at (0, 0, 1)
						alpha_vec_z = svinsr(alpha_vec_z, coef[3]); 
						sme_input_z00 = svld1(mask_x_0, &ptr_src[0 + (1*16*4)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_z, sme_input_z00); 
						
						sme_input_z10 = svld1(mask_x_0, &ptr_src[0 + (1*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_z, sme_input_z10); 
						
						sme_input_z20 = svld1(mask_x_0, &ptr_src[0 + (2*16+1*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_z, sme_input_z20); 
						
						sme_input_z30 = svld1(mask_x_0, &ptr_src[0 + (3*16+1*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_z, sme_input_z30); 
						
						// load vector at (0, 0, 2)
						alpha_vec_z = svinsr(alpha_vec_z, coef[4]); 
						sme_input_z00 = svld1(mask_x_0, &ptr_src[0 + (2*16*4)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_z, sme_input_z00); 
						
						sme_input_z10 = svld1(mask_x_0, &ptr_src[0 + (1*16+2*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_z, sme_input_z10); 
						
						sme_input_z20 = svld1(mask_x_0, &ptr_src[0 + (2*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_z, sme_input_z20); 
						
						sme_input_z30 = svld1(mask_x_0, &ptr_src[0 + (3*16+2*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_z, sme_input_z30); 
						
						// load vector at (0, 0, 3)
						alpha_vec_z = svinsr(alpha_vec_z, 0); 
						sme_input_z00 = svld1(mask_x_0, &ptr_src[0 + (3*16*4)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_z, sme_input_z00); 
						
						sme_input_z10 = svld1(mask_x_0, &ptr_src[0 + (1*16+3*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_z, sme_input_z10); 
						
						sme_input_z20 = svld1(mask_x_0, &ptr_src[0 + (2*16+3*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_z, sme_input_z20); 
						
						sme_input_z30 = svld1(mask_x_0, &ptr_src[0 + (3*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_z, sme_input_z30); 
						
						// load vector at (0, 0, 4)
						alpha_vec_z = svinsr(alpha_vec_z, 0); 
						sme_input_z00 = svld1(mask_x_0, &ptr_src[0 + (1*sz)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_z, sme_input_z00); 
						
						sme_input_z10 = svld1(mask_x_0, &ptr_src[0 + (1*16+1*sz)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_z, sme_input_z10); 
						
						sme_input_z20 = svld1(mask_x_0, &ptr_src[0 + (2*16+1*sz)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_z, sme_input_z20); 
						
						sme_input_z30 = svld1(mask_x_0, &ptr_src[0 + (3*16+1*sz)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_z, sme_input_z30); 
						
						// load vector at (0, 0, 5)
						alpha_vec_z = svinsr(alpha_vec_z, 0); 
						sme_input_z00 = svld1(mask_x_0, &ptr_src[0 + (1*sz+1*16*4)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_z, sme_input_z00); 
						
						sme_input_z10 = svld1(mask_x_0, &ptr_src[0 + (1*16+1*sz+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_z, sme_input_z10); 
						
						sme_input_z20 = svld1(mask_x_0, &ptr_src[0 + (2*16+1*sz+1*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_z, sme_input_z20); 
						
						sme_input_z30 = svld1(mask_x_0, &ptr_src[0 + (3*16+1*sz+1*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_z, sme_input_z30); 
						
						mask_x_0 = svwhilelt_b32(0, ker_size_x - vx); 
						svst1_hor_za32(0, 0, mask_x_0, &ptr_dst[0 + 0]); 
						svst1_hor_za32(1, 0, mask_x_0, &ptr_dst[0 + (1*16)]); 
						svst1_hor_za32(2, 0, mask_x_0, &ptr_dst[0 + (2*16)]); 
						svst1_hor_za32(3, 0, mask_x_0, &ptr_dst[0 + (3*16)]); 
						svst1_hor_za32(0, 1, mask_x_0, &ptr_dst[0 + (1*16*4)]); 
						svst1_hor_za32(1, 1, mask_x_0, &ptr_dst[0 + (1*16+1*16*4)]); 
						svst1_hor_za32(2, 1, mask_x_0, &ptr_dst[0 + (2*16+1*16*4)]); 
						svst1_hor_za32(3, 1, mask_x_0, &ptr_dst[0 + (3*16+1*16*4)]); 
						svst1_hor_za32(0, 2, mask_x_0, &ptr_dst[0 + (2*16*4)]); 
						svst1_hor_za32(1, 2, mask_x_0, &ptr_dst[0 + (1*16+2*16*4)]); 
						svst1_hor_za32(2, 2, mask_x_0, &ptr_dst[0 + (2*16+2*16*4)]); 
						svst1_hor_za32(3, 2, mask_x_0, &ptr_dst[0 + (3*16+2*16*4)]); 
						svst1_hor_za32(0, 3, mask_x_0, &ptr_dst[0 + (3*16*4)]); 
						svst1_hor_za32(1, 3, mask_x_0, &ptr_dst[0 + (1*16+3*16*4)]); 
						svst1_hor_za32(2, 3, mask_x_0, &ptr_dst[0 + (2*16+3*16*4)]); 
						svst1_hor_za32(3, 3, mask_x_0, &ptr_dst[0 + (3*16+3*16*4)]); 
						ptr_src += (1*sy); ptr_dst += (1*dy);
					}
					//restore pointers after z computation
					ptr_src -= 4*(1*sy); ptr_dst -= 4*(1*dy);
					temp_ptr = buffer_m1; buffer_m1 = buffer_0; buffer_0 = buffer_1; buffer_1 = temp_ptr;
					ptr_src += (1*16*4*4); ptr_l += (1*16*4*4); ptr_r += (1*16*4*4); ptr_dst += (1*16*4*4);
				}
			} else {
				//inner loop start phase
				ptr_src = (p0 + (((vy)/4)*sy + ((vy)%4)*16+((vz)/4)*sz + ((vz)%4)*16*4)); ptr_dst = (p1 + (((vy)/4)*dy + ((vy)%4)*16+((vz)/4)*dz + ((vz)%4)*16*4)); ptr_l = ptr_src + (-1*sy+2*16); ptr_r = ptr_src + (4*sy);
				float buffer[1*(3072) + (1*1024)]__attribute__((aligned(64)));
				float *buffer_m1 = buffer, *buffer_0 = buffer + 1024, *buffer_1 = buffer + 2048;
				mask_ext = svwhilelt_b32(0, 14); mask_ext = sveor_z(p32_all, p32_all, mask_ext); 
				for(int iz = 0; iz < 4; iz += 4) {
					// loading from grid 
					mask_x_0 = svwhilelt_b32(0, 16); 
					mask_x_0 = svand_z(p32_all, mask_x_0, mask_ext); 
					mask_z = svdup_b32(0 < ker_size_z - vz - iz); 
					mask_y = svdup_b32(0 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 0, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + 0]); 
					mask_y = svdup_b32(1 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 1, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*16)]); 
					mask_y = svdup_b32(2 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 2, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*16)]); 
					mask_y = svdup_b32(3 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 3, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*16)]); 
					mask_y = svdup_b32(4 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 4, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy)]); 
					mask_y = svdup_b32(5 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 5, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+1*16)]); 
					mask_y = svdup_b32(6 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 6, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+2*16)]); 
					mask_y = svdup_b32(7 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 7, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+3*16)]); 
					mask_y = svdup_b32(8 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 8, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy)]); 
					mask_y = svdup_b32(9 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 9, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+1*16)]); 
					mask_y = svdup_b32(10 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 10, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+2*16)]); 
					mask_y = svdup_b32(11 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 11, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+3*16)]); 
					mask_y = svdup_b32(12 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 12, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy)]); 
					mask_y = svdup_b32(13 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 13, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+1*16)]); 
					mask_y = svdup_b32(14 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 14, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+2*16)]); 
					mask_y = svdup_b32(15 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 15, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+3*16)]); 
					mask_z = svdup_b32(1 < ker_size_z - vz - iz); 
					mask_y = svdup_b32(0 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 0, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*16*4)]); 
					mask_y = svdup_b32(1 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 1, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*16+1*16*4)]); 
					mask_y = svdup_b32(2 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 2, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*16+1*16*4)]); 
					mask_y = svdup_b32(3 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 3, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*16+1*16*4)]); 
					mask_y = svdup_b32(4 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 4, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+1*16*4)]); 
					mask_y = svdup_b32(5 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 5, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+1*16+1*16*4)]); 
					mask_y = svdup_b32(6 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 6, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+2*16+1*16*4)]); 
					mask_y = svdup_b32(7 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 7, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+3*16+1*16*4)]); 
					mask_y = svdup_b32(8 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 8, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+1*16*4)]); 
					mask_y = svdup_b32(9 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 9, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+1*16+1*16*4)]); 
					mask_y = svdup_b32(10 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 10, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+2*16+1*16*4)]); 
					mask_y = svdup_b32(11 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 11, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+3*16+1*16*4)]); 
					mask_y = svdup_b32(12 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 12, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+1*16*4)]); 
					mask_y = svdup_b32(13 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 13, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+1*16+1*16*4)]); 
					mask_y = svdup_b32(14 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 14, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+2*16+1*16*4)]); 
					mask_y = svdup_b32(15 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 15, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+3*16+1*16*4)]); 
					mask_z = svdup_b32(2 < ker_size_z - vz - iz); 
					mask_y = svdup_b32(0 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 0, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*16*4)]); 
					mask_y = svdup_b32(1 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 1, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*16+2*16*4)]); 
					mask_y = svdup_b32(2 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 2, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*16+2*16*4)]); 
					mask_y = svdup_b32(3 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 3, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*16+2*16*4)]); 
					mask_y = svdup_b32(4 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 4, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+2*16*4)]); 
					mask_y = svdup_b32(5 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 5, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+1*16+2*16*4)]); 
					mask_y = svdup_b32(6 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 6, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+2*16+2*16*4)]); 
					mask_y = svdup_b32(7 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 7, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+3*16+2*16*4)]); 
					mask_y = svdup_b32(8 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 8, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+2*16*4)]); 
					mask_y = svdup_b32(9 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 9, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+1*16+2*16*4)]); 
					mask_y = svdup_b32(10 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 10, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+2*16+2*16*4)]); 
					mask_y = svdup_b32(11 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 11, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+3*16+2*16*4)]); 
					mask_y = svdup_b32(12 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 12, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+2*16*4)]); 
					mask_y = svdup_b32(13 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 13, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+1*16+2*16*4)]); 
					mask_y = svdup_b32(14 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 14, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+2*16+2*16*4)]); 
					mask_y = svdup_b32(15 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 15, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+3*16+2*16*4)]); 
					mask_z = svdup_b32(3 < ker_size_z - vz - iz); 
					mask_y = svdup_b32(0 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 0, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*16*4)]); 
					mask_y = svdup_b32(1 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 1, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*16+3*16*4)]); 
					mask_y = svdup_b32(2 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 2, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*16+3*16*4)]); 
					mask_y = svdup_b32(3 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 3, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*16+3*16*4)]); 
					mask_y = svdup_b32(4 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 4, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+3*16*4)]); 
					mask_y = svdup_b32(5 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 5, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+1*16+3*16*4)]); 
					mask_y = svdup_b32(6 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 6, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+2*16+3*16*4)]); 
					mask_y = svdup_b32(7 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 7, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (1*sy+3*16+3*16*4)]); 
					mask_y = svdup_b32(8 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 8, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+3*16*4)]); 
					mask_y = svdup_b32(9 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 9, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+1*16+3*16*4)]); 
					mask_y = svdup_b32(10 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 10, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+2*16+3*16*4)]); 
					mask_y = svdup_b32(11 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 11, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (2*sy+3*16+3*16*4)]); 
					mask_y = svdup_b32(12 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 12, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+3*16*4)]); 
					mask_y = svdup_b32(13 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 13, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+1*16+3*16*4)]); 
					mask_y = svdup_b32(14 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 14, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+2*16+3*16*4)]); 
					mask_y = svdup_b32(15 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 15, mask_xyz, &(ptr_src + (iz/4)*((1*sz)) + (-1*16*4*4))[0 + (3*sy+3*16+3*16*4)]); 
					//tranpose and store back to grid
					svst1_ver_za32(0, 0, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + 0]); 
					svst1_ver_za32(0, 1, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (1*16)]); 
					svst1_ver_za32(0, 2, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (2*16)]); 
					svst1_ver_za32(0, 3, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (3*16)]); 
					svst1_ver_za32(0, 4, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (4*16)]); 
					svst1_ver_za32(0, 5, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (5*16)]); 
					svst1_ver_za32(0, 6, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (6*16)]); 
					svst1_ver_za32(0, 7, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (7*16)]); 
					svst1_ver_za32(0, 8, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (8*16)]); 
					svst1_ver_za32(0, 9, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (9*16)]); 
					svst1_ver_za32(0, 10, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (10*16)]); 
					svst1_ver_za32(0, 11, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (11*16)]); 
					svst1_ver_za32(0, 12, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (12*16)]); 
					svst1_ver_za32(0, 13, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (13*16)]); 
					svst1_ver_za32(0, 14, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (14*16)]); 
					svst1_ver_za32(0, 15, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (15*16)]); 
					svst1_ver_za32(1, 0, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (1*16*16)]); 
					svst1_ver_za32(1, 1, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (1*16+1*16*16)]); 
					svst1_ver_za32(1, 2, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (2*16+1*16*16)]); 
					svst1_ver_za32(1, 3, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (3*16+1*16*16)]); 
					svst1_ver_za32(1, 4, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (4*16+1*16*16)]); 
					svst1_ver_za32(1, 5, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (5*16+1*16*16)]); 
					svst1_ver_za32(1, 6, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (6*16+1*16*16)]); 
					svst1_ver_za32(1, 7, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (7*16+1*16*16)]); 
					svst1_ver_za32(1, 8, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (8*16+1*16*16)]); 
					svst1_ver_za32(1, 9, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (9*16+1*16*16)]); 
					svst1_ver_za32(1, 10, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (10*16+1*16*16)]); 
					svst1_ver_za32(1, 11, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (11*16+1*16*16)]); 
					svst1_ver_za32(1, 12, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (12*16+1*16*16)]); 
					svst1_ver_za32(1, 13, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (13*16+1*16*16)]); 
					svst1_ver_za32(1, 14, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (14*16+1*16*16)]); 
					svst1_ver_za32(1, 15, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (15*16+1*16*16)]); 
					svst1_ver_za32(2, 0, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (2*16*16)]); 
					svst1_ver_za32(2, 1, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (1*16+2*16*16)]); 
					svst1_ver_za32(2, 2, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (2*16+2*16*16)]); 
					svst1_ver_za32(2, 3, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (3*16+2*16*16)]); 
					svst1_ver_za32(2, 4, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (4*16+2*16*16)]); 
					svst1_ver_za32(2, 5, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (5*16+2*16*16)]); 
					svst1_ver_za32(2, 6, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (6*16+2*16*16)]); 
					svst1_ver_za32(2, 7, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (7*16+2*16*16)]); 
					svst1_ver_za32(2, 8, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (8*16+2*16*16)]); 
					svst1_ver_za32(2, 9, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (9*16+2*16*16)]); 
					svst1_ver_za32(2, 10, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (10*16+2*16*16)]); 
					svst1_ver_za32(2, 11, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (11*16+2*16*16)]); 
					svst1_ver_za32(2, 12, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (12*16+2*16*16)]); 
					svst1_ver_za32(2, 13, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (13*16+2*16*16)]); 
					svst1_ver_za32(2, 14, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (14*16+2*16*16)]); 
					svst1_ver_za32(2, 15, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (15*16+2*16*16)]); 
					svst1_ver_za32(3, 0, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (3*16*16)]); 
					svst1_ver_za32(3, 1, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (1*16+3*16*16)]); 
					svst1_ver_za32(3, 2, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (2*16+3*16*16)]); 
					svst1_ver_za32(3, 3, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (3*16+3*16*16)]); 
					svst1_ver_za32(3, 4, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (4*16+3*16*16)]); 
					svst1_ver_za32(3, 5, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (5*16+3*16*16)]); 
					svst1_ver_za32(3, 6, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (6*16+3*16*16)]); 
					svst1_ver_za32(3, 7, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (7*16+3*16*16)]); 
					svst1_ver_za32(3, 8, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (8*16+3*16*16)]); 
					svst1_ver_za32(3, 9, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (9*16+3*16*16)]); 
					svst1_ver_za32(3, 10, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (10*16+3*16*16)]); 
					svst1_ver_za32(3, 11, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (11*16+3*16*16)]); 
					svst1_ver_za32(3, 12, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (12*16+3*16*16)]); 
					svst1_ver_za32(3, 13, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (13*16+3*16*16)]); 
					svst1_ver_za32(3, 14, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (14*16+3*16*16)]); 
					svst1_ver_za32(3, 15, p32_all, &(buffer_m1 + (iz/4)*3072)[0 + (15*16+3*16*16)]); 
					// loading from grid 
					mask_x_0 = svwhilelt_b32(0, ker_size_x + 2); 
					mask_z = svdup_b32(0 < ker_size_z - vz - iz); 
					mask_y = svdup_b32(0 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 0, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + 0]); 
					mask_y = svdup_b32(1 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 1, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*16)]); 
					mask_y = svdup_b32(2 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 2, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*16)]); 
					mask_y = svdup_b32(3 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 3, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*16)]); 
					mask_y = svdup_b32(4 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 4, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy)]); 
					mask_y = svdup_b32(5 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 5, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+1*16)]); 
					mask_y = svdup_b32(6 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 6, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+2*16)]); 
					mask_y = svdup_b32(7 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 7, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+3*16)]); 
					mask_y = svdup_b32(8 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 8, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy)]); 
					mask_y = svdup_b32(9 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 9, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+1*16)]); 
					mask_y = svdup_b32(10 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 10, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+2*16)]); 
					mask_y = svdup_b32(11 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 11, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+3*16)]); 
					mask_y = svdup_b32(12 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 12, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy)]); 
					mask_y = svdup_b32(13 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 13, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+1*16)]); 
					mask_y = svdup_b32(14 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 14, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+2*16)]); 
					mask_y = svdup_b32(15 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 15, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+3*16)]); 
					mask_z = svdup_b32(1 < ker_size_z - vz - iz); 
					mask_y = svdup_b32(0 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 0, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*16*4)]); 
					mask_y = svdup_b32(1 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 1, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*16+1*16*4)]); 
					mask_y = svdup_b32(2 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 2, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*16+1*16*4)]); 
					mask_y = svdup_b32(3 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 3, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*16+1*16*4)]); 
					mask_y = svdup_b32(4 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 4, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+1*16*4)]); 
					mask_y = svdup_b32(5 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 5, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+1*16+1*16*4)]); 
					mask_y = svdup_b32(6 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 6, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+2*16+1*16*4)]); 
					mask_y = svdup_b32(7 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 7, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+3*16+1*16*4)]); 
					mask_y = svdup_b32(8 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 8, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+1*16*4)]); 
					mask_y = svdup_b32(9 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 9, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+1*16+1*16*4)]); 
					mask_y = svdup_b32(10 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 10, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+2*16+1*16*4)]); 
					mask_y = svdup_b32(11 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 11, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+3*16+1*16*4)]); 
					mask_y = svdup_b32(12 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 12, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+1*16*4)]); 
					mask_y = svdup_b32(13 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 13, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+1*16+1*16*4)]); 
					mask_y = svdup_b32(14 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 14, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+2*16+1*16*4)]); 
					mask_y = svdup_b32(15 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 15, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+3*16+1*16*4)]); 
					mask_z = svdup_b32(2 < ker_size_z - vz - iz); 
					mask_y = svdup_b32(0 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 0, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*16*4)]); 
					mask_y = svdup_b32(1 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 1, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*16+2*16*4)]); 
					mask_y = svdup_b32(2 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 2, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*16+2*16*4)]); 
					mask_y = svdup_b32(3 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 3, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*16+2*16*4)]); 
					mask_y = svdup_b32(4 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 4, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+2*16*4)]); 
					mask_y = svdup_b32(5 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 5, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+1*16+2*16*4)]); 
					mask_y = svdup_b32(6 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 6, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+2*16+2*16*4)]); 
					mask_y = svdup_b32(7 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 7, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+3*16+2*16*4)]); 
					mask_y = svdup_b32(8 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 8, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+2*16*4)]); 
					mask_y = svdup_b32(9 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 9, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+1*16+2*16*4)]); 
					mask_y = svdup_b32(10 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 10, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+2*16+2*16*4)]); 
					mask_y = svdup_b32(11 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 11, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+3*16+2*16*4)]); 
					mask_y = svdup_b32(12 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 12, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+2*16*4)]); 
					mask_y = svdup_b32(13 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 13, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+1*16+2*16*4)]); 
					mask_y = svdup_b32(14 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 14, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+2*16+2*16*4)]); 
					mask_y = svdup_b32(15 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 15, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+3*16+2*16*4)]); 
					mask_z = svdup_b32(3 < ker_size_z - vz - iz); 
					mask_y = svdup_b32(0 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 0, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*16*4)]); 
					mask_y = svdup_b32(1 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 1, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*16+3*16*4)]); 
					mask_y = svdup_b32(2 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 2, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*16+3*16*4)]); 
					mask_y = svdup_b32(3 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 3, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*16+3*16*4)]); 
					mask_y = svdup_b32(4 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 4, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+3*16*4)]); 
					mask_y = svdup_b32(5 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 5, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+1*16+3*16*4)]); 
					mask_y = svdup_b32(6 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 6, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+2*16+3*16*4)]); 
					mask_y = svdup_b32(7 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 7, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (1*sy+3*16+3*16*4)]); 
					mask_y = svdup_b32(8 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 8, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+3*16*4)]); 
					mask_y = svdup_b32(9 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 9, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+1*16+3*16*4)]); 
					mask_y = svdup_b32(10 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 10, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+2*16+3*16*4)]); 
					mask_y = svdup_b32(11 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 11, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (2*sy+3*16+3*16*4)]); 
					mask_y = svdup_b32(12 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 12, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+3*16*4)]); 
					mask_y = svdup_b32(13 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 13, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+1*16+3*16*4)]); 
					mask_y = svdup_b32(14 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 14, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+2*16+3*16*4)]); 
					mask_y = svdup_b32(15 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 15, mask_xyz, &(ptr_src + (iz/4)*((1*sz)))[0 + (3*sy+3*16+3*16*4)]); 
					//tranpose and store back to grid
					svst1_ver_za32(0, 0, p32_all, &(buffer_0 + (iz/4)*3072)[0 + 0]); 
					svst1_ver_za32(0, 1, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (1*16)]); 
					svst1_ver_za32(0, 2, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (2*16)]); 
					svst1_ver_za32(0, 3, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (3*16)]); 
					svst1_ver_za32(0, 4, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (4*16)]); 
					svst1_ver_za32(0, 5, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (5*16)]); 
					svst1_ver_za32(0, 6, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (6*16)]); 
					svst1_ver_za32(0, 7, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (7*16)]); 
					svst1_ver_za32(0, 8, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (8*16)]); 
					svst1_ver_za32(0, 9, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (9*16)]); 
					svst1_ver_za32(0, 10, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (10*16)]); 
					svst1_ver_za32(0, 11, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (11*16)]); 
					svst1_ver_za32(0, 12, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (12*16)]); 
					svst1_ver_za32(0, 13, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (13*16)]); 
					svst1_ver_za32(0, 14, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (14*16)]); 
					svst1_ver_za32(0, 15, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (15*16)]); 
					svst1_ver_za32(1, 0, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (1*16*16)]); 
					svst1_ver_za32(1, 1, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (1*16+1*16*16)]); 
					svst1_ver_za32(1, 2, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (2*16+1*16*16)]); 
					svst1_ver_za32(1, 3, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (3*16+1*16*16)]); 
					svst1_ver_za32(1, 4, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (4*16+1*16*16)]); 
					svst1_ver_za32(1, 5, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (5*16+1*16*16)]); 
					svst1_ver_za32(1, 6, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (6*16+1*16*16)]); 
					svst1_ver_za32(1, 7, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (7*16+1*16*16)]); 
					svst1_ver_za32(1, 8, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (8*16+1*16*16)]); 
					svst1_ver_za32(1, 9, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (9*16+1*16*16)]); 
					svst1_ver_za32(1, 10, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (10*16+1*16*16)]); 
					svst1_ver_za32(1, 11, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (11*16+1*16*16)]); 
					svst1_ver_za32(1, 12, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (12*16+1*16*16)]); 
					svst1_ver_za32(1, 13, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (13*16+1*16*16)]); 
					svst1_ver_za32(1, 14, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (14*16+1*16*16)]); 
					svst1_ver_za32(1, 15, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (15*16+1*16*16)]); 
					svst1_ver_za32(2, 0, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (2*16*16)]); 
					svst1_ver_za32(2, 1, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (1*16+2*16*16)]); 
					svst1_ver_za32(2, 2, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (2*16+2*16*16)]); 
					svst1_ver_za32(2, 3, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (3*16+2*16*16)]); 
					svst1_ver_za32(2, 4, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (4*16+2*16*16)]); 
					svst1_ver_za32(2, 5, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (5*16+2*16*16)]); 
					svst1_ver_za32(2, 6, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (6*16+2*16*16)]); 
					svst1_ver_za32(2, 7, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (7*16+2*16*16)]); 
					svst1_ver_za32(2, 8, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (8*16+2*16*16)]); 
					svst1_ver_za32(2, 9, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (9*16+2*16*16)]); 
					svst1_ver_za32(2, 10, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (10*16+2*16*16)]); 
					svst1_ver_za32(2, 11, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (11*16+2*16*16)]); 
					svst1_ver_za32(2, 12, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (12*16+2*16*16)]); 
					svst1_ver_za32(2, 13, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (13*16+2*16*16)]); 
					svst1_ver_za32(2, 14, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (14*16+2*16*16)]); 
					svst1_ver_za32(2, 15, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (15*16+2*16*16)]); 
					svst1_ver_za32(3, 0, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (3*16*16)]); 
					svst1_ver_za32(3, 1, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (1*16+3*16*16)]); 
					svst1_ver_za32(3, 2, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (2*16+3*16*16)]); 
					svst1_ver_za32(3, 3, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (3*16+3*16*16)]); 
					svst1_ver_za32(3, 4, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (4*16+3*16*16)]); 
					svst1_ver_za32(3, 5, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (5*16+3*16*16)]); 
					svst1_ver_za32(3, 6, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (6*16+3*16*16)]); 
					svst1_ver_za32(3, 7, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (7*16+3*16*16)]); 
					svst1_ver_za32(3, 8, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (8*16+3*16*16)]); 
					svst1_ver_za32(3, 9, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (9*16+3*16*16)]); 
					svst1_ver_za32(3, 10, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (10*16+3*16*16)]); 
					svst1_ver_za32(3, 11, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (11*16+3*16*16)]); 
					svst1_ver_za32(3, 12, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (12*16+3*16*16)]); 
					svst1_ver_za32(3, 13, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (13*16+3*16*16)]); 
					svst1_ver_za32(3, 14, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (14*16+3*16*16)]); 
					svst1_ver_za32(3, 15, p32_all, &(buffer_0 + (iz/4)*3072)[0 + (15*16+3*16*16)]); 
				}
				//loop in x dimension starts
				for(int vx = 0; vx < ker_size_x; vx += 16) {
					for(int iz = 0; iz < 4; iz += 4) {
						temp_dst = buffer + 1*(3072) + (iz / 4)*1024;
						ptr_m1 = (buffer_m1 + (iz/4)*(3072) + 224); ptr_0 = buffer_0 + (iz/4)*(3072); ptr_1 = buffer_1 + (iz/4)*(3072);
						// loading from grid 
						mask_x_0 = svwhilelt_b32(0, ker_size_x - vx + 2 - 16); 
						mask_z = svdup_b32(0 < ker_size_z - vz - iz); 
						mask_y = svdup_b32(0 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 0, mask_xyz, &(ptr_src + (1*16*4*4))[0 + 0]); 
						mask_y = svdup_b32(1 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 1, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (1*16)]); 
						mask_y = svdup_b32(2 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 2, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (2*16)]); 
						mask_y = svdup_b32(3 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 3, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (3*16)]); 
						mask_y = svdup_b32(4 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 4, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (1*sy)]); 
						mask_y = svdup_b32(5 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 5, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (1*sy+1*16)]); 
						mask_y = svdup_b32(6 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 6, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (1*sy+2*16)]); 
						mask_y = svdup_b32(7 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 7, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (1*sy+3*16)]); 
						mask_y = svdup_b32(8 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 8, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (2*sy)]); 
						mask_y = svdup_b32(9 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 9, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (2*sy+1*16)]); 
						mask_y = svdup_b32(10 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 10, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (2*sy+2*16)]); 
						mask_y = svdup_b32(11 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 11, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (2*sy+3*16)]); 
						mask_y = svdup_b32(12 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 12, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (3*sy)]); 
						mask_y = svdup_b32(13 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 13, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (3*sy+1*16)]); 
						mask_y = svdup_b32(14 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 14, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (3*sy+2*16)]); 
						mask_y = svdup_b32(15 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(0, 15, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (3*sy+3*16)]); 
						mask_z = svdup_b32(1 < ker_size_z - vz - iz); 
						mask_y = svdup_b32(0 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 0, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (1*16*4)]); 
						mask_y = svdup_b32(1 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 1, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (1*16+1*16*4)]); 
						mask_y = svdup_b32(2 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 2, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (2*16+1*16*4)]); 
						mask_y = svdup_b32(3 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 3, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (3*16+1*16*4)]); 
						mask_y = svdup_b32(4 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 4, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (1*sy+1*16*4)]); 
						mask_y = svdup_b32(5 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 5, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (1*sy+1*16+1*16*4)]); 
						mask_y = svdup_b32(6 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 6, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (1*sy+2*16+1*16*4)]); 
						mask_y = svdup_b32(7 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 7, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (1*sy+3*16+1*16*4)]); 
						mask_y = svdup_b32(8 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 8, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (2*sy+1*16*4)]); 
						mask_y = svdup_b32(9 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 9, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (2*sy+1*16+1*16*4)]); 
						mask_y = svdup_b32(10 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 10, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (2*sy+2*16+1*16*4)]); 
						mask_y = svdup_b32(11 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 11, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (2*sy+3*16+1*16*4)]); 
						mask_y = svdup_b32(12 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 12, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (3*sy+1*16*4)]); 
						mask_y = svdup_b32(13 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 13, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (3*sy+1*16+1*16*4)]); 
						mask_y = svdup_b32(14 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 14, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (3*sy+2*16+1*16*4)]); 
						mask_y = svdup_b32(15 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(1, 15, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (3*sy+3*16+1*16*4)]); 
						mask_z = svdup_b32(2 < ker_size_z - vz - iz); 
						mask_y = svdup_b32(0 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 0, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (2*16*4)]); 
						mask_y = svdup_b32(1 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 1, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (1*16+2*16*4)]); 
						mask_y = svdup_b32(2 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 2, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (2*16+2*16*4)]); 
						mask_y = svdup_b32(3 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 3, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (3*16+2*16*4)]); 
						mask_y = svdup_b32(4 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 4, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (1*sy+2*16*4)]); 
						mask_y = svdup_b32(5 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 5, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (1*sy+1*16+2*16*4)]); 
						mask_y = svdup_b32(6 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 6, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (1*sy+2*16+2*16*4)]); 
						mask_y = svdup_b32(7 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 7, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (1*sy+3*16+2*16*4)]); 
						mask_y = svdup_b32(8 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 8, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (2*sy+2*16*4)]); 
						mask_y = svdup_b32(9 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 9, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (2*sy+1*16+2*16*4)]); 
						mask_y = svdup_b32(10 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 10, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (2*sy+2*16+2*16*4)]); 
						mask_y = svdup_b32(11 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 11, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (2*sy+3*16+2*16*4)]); 
						mask_y = svdup_b32(12 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 12, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (3*sy+2*16*4)]); 
						mask_y = svdup_b32(13 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 13, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (3*sy+1*16+2*16*4)]); 
						mask_y = svdup_b32(14 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 14, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (3*sy+2*16+2*16*4)]); 
						mask_y = svdup_b32(15 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(2, 15, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (3*sy+3*16+2*16*4)]); 
						mask_z = svdup_b32(3 < ker_size_z - vz - iz); 
						mask_y = svdup_b32(0 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 0, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (3*16*4)]); 
						mask_y = svdup_b32(1 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 1, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (1*16+3*16*4)]); 
						mask_y = svdup_b32(2 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 2, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (2*16+3*16*4)]); 
						mask_y = svdup_b32(3 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 3, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (3*16+3*16*4)]); 
						mask_y = svdup_b32(4 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 4, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (1*sy+3*16*4)]); 
						mask_y = svdup_b32(5 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 5, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (1*sy+1*16+3*16*4)]); 
						mask_y = svdup_b32(6 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 6, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (1*sy+2*16+3*16*4)]); 
						mask_y = svdup_b32(7 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 7, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (1*sy+3*16+3*16*4)]); 
						mask_y = svdup_b32(8 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 8, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (2*sy+3*16*4)]); 
						mask_y = svdup_b32(9 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 9, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (2*sy+1*16+3*16*4)]); 
						mask_y = svdup_b32(10 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 10, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (2*sy+2*16+3*16*4)]); 
						mask_y = svdup_b32(11 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 11, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (2*sy+3*16+3*16*4)]); 
						mask_y = svdup_b32(12 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 12, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (3*sy+3*16*4)]); 
						mask_y = svdup_b32(13 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 13, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (3*sy+1*16+3*16*4)]); 
						mask_y = svdup_b32(14 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 14, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (3*sy+2*16+3*16*4)]); 
						mask_y = svdup_b32(15 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svld1_hor_za32(3, 15, mask_xyz, &(ptr_src + (1*16*4*4))[0 + (3*sy+3*16+3*16*4)]); 
						//tranpose and store back to grid
						svst1_ver_za32(0, 0, p32_all, &ptr_1[0 + 0]); 
						svst1_ver_za32(0, 1, p32_all, &ptr_1[0 + (1*16)]); 
						svst1_ver_za32(0, 2, p32_all, &ptr_1[0 + (2*16)]); 
						svst1_ver_za32(0, 3, p32_all, &ptr_1[0 + (3*16)]); 
						svst1_ver_za32(0, 4, p32_all, &ptr_1[0 + (4*16)]); 
						svst1_ver_za32(0, 5, p32_all, &ptr_1[0 + (5*16)]); 
						svst1_ver_za32(0, 6, p32_all, &ptr_1[0 + (6*16)]); 
						svst1_ver_za32(0, 7, p32_all, &ptr_1[0 + (7*16)]); 
						svst1_ver_za32(0, 8, p32_all, &ptr_1[0 + (8*16)]); 
						svst1_ver_za32(0, 9, p32_all, &ptr_1[0 + (9*16)]); 
						svst1_ver_za32(0, 10, p32_all, &ptr_1[0 + (10*16)]); 
						svst1_ver_za32(0, 11, p32_all, &ptr_1[0 + (11*16)]); 
						svst1_ver_za32(0, 12, p32_all, &ptr_1[0 + (12*16)]); 
						svst1_ver_za32(0, 13, p32_all, &ptr_1[0 + (13*16)]); 
						svst1_ver_za32(0, 14, p32_all, &ptr_1[0 + (14*16)]); 
						svst1_ver_za32(0, 15, p32_all, &ptr_1[0 + (15*16)]); 
						svst1_ver_za32(1, 0, p32_all, &ptr_1[0 + (1*16*16)]); 
						svst1_ver_za32(1, 1, p32_all, &ptr_1[0 + (1*16+1*16*16)]); 
						svst1_ver_za32(1, 2, p32_all, &ptr_1[0 + (2*16+1*16*16)]); 
						svst1_ver_za32(1, 3, p32_all, &ptr_1[0 + (3*16+1*16*16)]); 
						svst1_ver_za32(1, 4, p32_all, &ptr_1[0 + (4*16+1*16*16)]); 
						svst1_ver_za32(1, 5, p32_all, &ptr_1[0 + (5*16+1*16*16)]); 
						svst1_ver_za32(1, 6, p32_all, &ptr_1[0 + (6*16+1*16*16)]); 
						svst1_ver_za32(1, 7, p32_all, &ptr_1[0 + (7*16+1*16*16)]); 
						svst1_ver_za32(1, 8, p32_all, &ptr_1[0 + (8*16+1*16*16)]); 
						svst1_ver_za32(1, 9, p32_all, &ptr_1[0 + (9*16+1*16*16)]); 
						svst1_ver_za32(1, 10, p32_all, &ptr_1[0 + (10*16+1*16*16)]); 
						svst1_ver_za32(1, 11, p32_all, &ptr_1[0 + (11*16+1*16*16)]); 
						svst1_ver_za32(1, 12, p32_all, &ptr_1[0 + (12*16+1*16*16)]); 
						svst1_ver_za32(1, 13, p32_all, &ptr_1[0 + (13*16+1*16*16)]); 
						svst1_ver_za32(1, 14, p32_all, &ptr_1[0 + (14*16+1*16*16)]); 
						svst1_ver_za32(1, 15, p32_all, &ptr_1[0 + (15*16+1*16*16)]); 
						svst1_ver_za32(2, 0, p32_all, &ptr_1[0 + (2*16*16)]); 
						svst1_ver_za32(2, 1, p32_all, &ptr_1[0 + (1*16+2*16*16)]); 
						svst1_ver_za32(2, 2, p32_all, &ptr_1[0 + (2*16+2*16*16)]); 
						svst1_ver_za32(2, 3, p32_all, &ptr_1[0 + (3*16+2*16*16)]); 
						svst1_ver_za32(2, 4, p32_all, &ptr_1[0 + (4*16+2*16*16)]); 
						svst1_ver_za32(2, 5, p32_all, &ptr_1[0 + (5*16+2*16*16)]); 
						svst1_ver_za32(2, 6, p32_all, &ptr_1[0 + (6*16+2*16*16)]); 
						svst1_ver_za32(2, 7, p32_all, &ptr_1[0 + (7*16+2*16*16)]); 
						svst1_ver_za32(2, 8, p32_all, &ptr_1[0 + (8*16+2*16*16)]); 
						svst1_ver_za32(2, 9, p32_all, &ptr_1[0 + (9*16+2*16*16)]); 
						svst1_ver_za32(2, 10, p32_all, &ptr_1[0 + (10*16+2*16*16)]); 
						svst1_ver_za32(2, 11, p32_all, &ptr_1[0 + (11*16+2*16*16)]); 
						svst1_ver_za32(2, 12, p32_all, &ptr_1[0 + (12*16+2*16*16)]); 
						svst1_ver_za32(2, 13, p32_all, &ptr_1[0 + (13*16+2*16*16)]); 
						svst1_ver_za32(2, 14, p32_all, &ptr_1[0 + (14*16+2*16*16)]); 
						svst1_ver_za32(2, 15, p32_all, &ptr_1[0 + (15*16+2*16*16)]); 
						svst1_ver_za32(3, 0, p32_all, &ptr_1[0 + (3*16*16)]); 
						svst1_ver_za32(3, 1, p32_all, &ptr_1[0 + (1*16+3*16*16)]); 
						svst1_ver_za32(3, 2, p32_all, &ptr_1[0 + (2*16+3*16*16)]); 
						svst1_ver_za32(3, 3, p32_all, &ptr_1[0 + (3*16+3*16*16)]); 
						svst1_ver_za32(3, 4, p32_all, &ptr_1[0 + (4*16+3*16*16)]); 
						svst1_ver_za32(3, 5, p32_all, &ptr_1[0 + (5*16+3*16*16)]); 
						svst1_ver_za32(3, 6, p32_all, &ptr_1[0 + (6*16+3*16*16)]); 
						svst1_ver_za32(3, 7, p32_all, &ptr_1[0 + (7*16+3*16*16)]); 
						svst1_ver_za32(3, 8, p32_all, &ptr_1[0 + (8*16+3*16*16)]); 
						svst1_ver_za32(3, 9, p32_all, &ptr_1[0 + (9*16+3*16*16)]); 
						svst1_ver_za32(3, 10, p32_all, &ptr_1[0 + (10*16+3*16*16)]); 
						svst1_ver_za32(3, 11, p32_all, &ptr_1[0 + (11*16+3*16*16)]); 
						svst1_ver_za32(3, 12, p32_all, &ptr_1[0 + (12*16+3*16*16)]); 
						svst1_ver_za32(3, 13, p32_all, &ptr_1[0 + (13*16+3*16*16)]); 
						svst1_ver_za32(3, 14, p32_all, &ptr_1[0 + (14*16+3*16*16)]); 
						svst1_ver_za32(3, 15, p32_all, &ptr_1[0 + (15*16+3*16*16)]); 
						svzero_mask_za(0x1); svzero_mask_za(0x10); 
						svzero_mask_za(0x2); svzero_mask_za(0x20); 
						svzero_mask_za(0x4); svzero_mask_za(0x40); 
						svzero_mask_za(0x8); svzero_mask_za(0x80); 
						// declare input vector registers
						svfloat32_t sme_input_x0,sme_input_x1,sme_input_x2,sme_input_x3; 
						// declare input coefficients
						svfloat32_t alpha_vec_x = svdup_f32_x(p32_all, 0); 
						// load vector at (-2, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, coef[0]); 
						sme_input_x0 = svld1(p32_all, &ptr_m1[0 + 0]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_m1[0 + (1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_m1[0 + (2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_m1[0 + (3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (-1, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, coef[1]); 
						sme_input_x0 = svld1(p32_all, &ptr_m1[0 + (1*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_m1[0 + (1*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_m1[0 + (1*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_m1[0 + (1*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (0, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, coef[2]); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + 0]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (1, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, coef[3]); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (1*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (1*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (1*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (1*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (2, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, coef[4]); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (2*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (2*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (2*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (2*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (3, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (3*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (3*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (3*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (3*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (4, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (4*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (4*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (4*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (4*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (5, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (5*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (5*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (5*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (5*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (6, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (6*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (6*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (6*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (6*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (7, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (7*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (7*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (7*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (7*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (8, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (8*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (8*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (8*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (8*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (9, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (9*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (9*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (9*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (9*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (10, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (10*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (10*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (10*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (10*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (11, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (11*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (11*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (11*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (11*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (12, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (12*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (12*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (12*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (12*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (13, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (13*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (13*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (13*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (13*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (14, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (14*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (14*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (14*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (14*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (15, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_0[0 + (15*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_0[0 + (15*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_0[0 + (15*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_0[0 + (15*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (16, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_1[0 + 0]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_1[0 + (1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_1[0 + (2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_1[0 + (3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// load vector at (17, 0, 0)
						alpha_vec_x = svinsr(alpha_vec_x, 0); 
						sme_input_x0 = svld1(p32_all, &ptr_1[0 + (1*16)]); svmopa_za32_m(0, p32_all, p32_all, sme_input_x0, alpha_vec_x); 
						sme_input_x1 = svld1(p32_all, &ptr_1[0 + (1*16+1*16*16)]); svmopa_za32_m(1, p32_all, p32_all, sme_input_x1, alpha_vec_x); 
						sme_input_x2 = svld1(p32_all, &ptr_1[0 + (1*16+2*16*16)]); svmopa_za32_m(2, p32_all, p32_all, sme_input_x2, alpha_vec_x); 
						sme_input_x3 = svld1(p32_all, &ptr_1[0 + (1*16+3*16*16)]); svmopa_za32_m(3, p32_all, p32_all, sme_input_x3, alpha_vec_x); 
						// declare input vector registers
						svfloat32_t sme_input_y00,sme_input_y10,sme_input_y20,sme_input_y30; 
						// declare input coefficients
						svfloat32_t alpha_vec_y = svdup_f32_x(p32_all, 0); 
						mask_x_0 = svwhilelt_b32(0, ker_size_x - vx + 2); 
						// load vector at (0, -2, 0)
						mask_y = svdup_b32(-2 < ker_size_y - vy + 2); 
						alpha_vec_y = svinsr(alpha_vec_y, coef[0]); 
						mask_z = svdup_b32(0 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y00 = svld1(mask_xyz, &ptr_l[0 + 0]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						mask_z = svdup_b32(1 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y10 = svld1(mask_xyz, &ptr_l[0 + (1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						mask_z = svdup_b32(2 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y20 = svld1(mask_xyz, &ptr_l[0 + (2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						mask_z = svdup_b32(3 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y30 = svld1(mask_xyz, &ptr_l[0 + (3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, -1, 0)
						mask_y = svdup_b32(-1 < ker_size_y - vy + 2); 
						alpha_vec_y = svinsr(alpha_vec_y, coef[1]); 
						mask_z = svdup_b32(0 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y00 = svld1(mask_xyz, &ptr_l[0 + (1*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						mask_z = svdup_b32(1 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y10 = svld1(mask_xyz, &ptr_l[0 + (1*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						mask_z = svdup_b32(2 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y20 = svld1(mask_xyz, &ptr_l[0 + (1*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						mask_z = svdup_b32(3 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y30 = svld1(mask_xyz, &ptr_l[0 + (1*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 0, 0)
						mask_y = svdup_b32(0 < ker_size_y - vy + 2); 
						alpha_vec_y = svinsr(alpha_vec_y, coef[2]); 
						mask_z = svdup_b32(0 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y00 = svld1(mask_xyz, &ptr_src[0 + 0]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						mask_z = svdup_b32(1 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y10 = svld1(mask_xyz, &ptr_src[0 + (1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						mask_z = svdup_b32(2 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y20 = svld1(mask_xyz, &ptr_src[0 + (2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						mask_z = svdup_b32(3 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y30 = svld1(mask_xyz, &ptr_src[0 + (3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 1, 0)
						mask_y = svdup_b32(1 < ker_size_y - vy + 2); 
						alpha_vec_y = svinsr(alpha_vec_y, coef[3]); 
						mask_z = svdup_b32(0 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y00 = svld1(mask_xyz, &ptr_src[0 + (1*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						mask_z = svdup_b32(1 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y10 = svld1(mask_xyz, &ptr_src[0 + (1*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						mask_z = svdup_b32(2 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y20 = svld1(mask_xyz, &ptr_src[0 + (1*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						mask_z = svdup_b32(3 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y30 = svld1(mask_xyz, &ptr_src[0 + (1*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 2, 0)
						mask_y = svdup_b32(2 < ker_size_y - vy + 2); 
						alpha_vec_y = svinsr(alpha_vec_y, coef[4]); 
						mask_z = svdup_b32(0 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y00 = svld1(mask_xyz, &ptr_src[0 + (2*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						mask_z = svdup_b32(1 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y10 = svld1(mask_xyz, &ptr_src[0 + (2*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						mask_z = svdup_b32(2 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y20 = svld1(mask_xyz, &ptr_src[0 + (2*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						mask_z = svdup_b32(3 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y30 = svld1(mask_xyz, &ptr_src[0 + (2*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 3, 0)
						mask_y = svdup_b32(3 < ker_size_y - vy + 2); 
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						mask_z = svdup_b32(0 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y00 = svld1(mask_xyz, &ptr_src[0 + (3*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						mask_z = svdup_b32(1 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y10 = svld1(mask_xyz, &ptr_src[0 + (3*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						mask_z = svdup_b32(2 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y20 = svld1(mask_xyz, &ptr_src[0 + (3*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						mask_z = svdup_b32(3 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y30 = svld1(mask_xyz, &ptr_src[0 + (3*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 4, 0)
						mask_y = svdup_b32(4 < ker_size_y - vy + 2); 
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						mask_z = svdup_b32(0 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y00 = svld1(mask_xyz, &ptr_src[0 + (1*sy)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						mask_z = svdup_b32(1 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y10 = svld1(mask_xyz, &ptr_src[0 + (1*sy+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						mask_z = svdup_b32(2 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y20 = svld1(mask_xyz, &ptr_src[0 + (1*sy+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						mask_z = svdup_b32(3 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y30 = svld1(mask_xyz, &ptr_src[0 + (1*sy+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 5, 0)
						mask_y = svdup_b32(5 < ker_size_y - vy + 2); 
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						mask_z = svdup_b32(0 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y00 = svld1(mask_xyz, &ptr_src[0 + (1*sy+1*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						mask_z = svdup_b32(1 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y10 = svld1(mask_xyz, &ptr_src[0 + (1*sy+1*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						mask_z = svdup_b32(2 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y20 = svld1(mask_xyz, &ptr_src[0 + (1*sy+1*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						mask_z = svdup_b32(3 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y30 = svld1(mask_xyz, &ptr_src[0 + (1*sy+1*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 6, 0)
						mask_y = svdup_b32(6 < ker_size_y - vy + 2); 
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						mask_z = svdup_b32(0 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y00 = svld1(mask_xyz, &ptr_src[0 + (1*sy+2*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						mask_z = svdup_b32(1 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y10 = svld1(mask_xyz, &ptr_src[0 + (1*sy+2*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						mask_z = svdup_b32(2 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y20 = svld1(mask_xyz, &ptr_src[0 + (1*sy+2*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						mask_z = svdup_b32(3 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y30 = svld1(mask_xyz, &ptr_src[0 + (1*sy+2*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 7, 0)
						mask_y = svdup_b32(7 < ker_size_y - vy + 2); 
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						mask_z = svdup_b32(0 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y00 = svld1(mask_xyz, &ptr_src[0 + (1*sy+3*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						mask_z = svdup_b32(1 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y10 = svld1(mask_xyz, &ptr_src[0 + (1*sy+3*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						mask_z = svdup_b32(2 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y20 = svld1(mask_xyz, &ptr_src[0 + (1*sy+3*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						mask_z = svdup_b32(3 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y30 = svld1(mask_xyz, &ptr_src[0 + (1*sy+3*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 8, 0)
						mask_y = svdup_b32(8 < ker_size_y - vy + 2); 
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						mask_z = svdup_b32(0 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y00 = svld1(mask_xyz, &ptr_src[0 + (2*sy)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						mask_z = svdup_b32(1 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y10 = svld1(mask_xyz, &ptr_src[0 + (2*sy+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						mask_z = svdup_b32(2 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y20 = svld1(mask_xyz, &ptr_src[0 + (2*sy+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						mask_z = svdup_b32(3 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y30 = svld1(mask_xyz, &ptr_src[0 + (2*sy+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 9, 0)
						mask_y = svdup_b32(9 < ker_size_y - vy + 2); 
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						mask_z = svdup_b32(0 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y00 = svld1(mask_xyz, &ptr_src[0 + (2*sy+1*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						mask_z = svdup_b32(1 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y10 = svld1(mask_xyz, &ptr_src[0 + (2*sy+1*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						mask_z = svdup_b32(2 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y20 = svld1(mask_xyz, &ptr_src[0 + (2*sy+1*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						mask_z = svdup_b32(3 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y30 = svld1(mask_xyz, &ptr_src[0 + (2*sy+1*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 10, 0)
						mask_y = svdup_b32(10 < ker_size_y - vy + 2); 
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						mask_z = svdup_b32(0 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y00 = svld1(mask_xyz, &ptr_src[0 + (2*sy+2*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						mask_z = svdup_b32(1 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y10 = svld1(mask_xyz, &ptr_src[0 + (2*sy+2*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						mask_z = svdup_b32(2 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y20 = svld1(mask_xyz, &ptr_src[0 + (2*sy+2*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						mask_z = svdup_b32(3 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y30 = svld1(mask_xyz, &ptr_src[0 + (2*sy+2*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 11, 0)
						mask_y = svdup_b32(11 < ker_size_y - vy + 2); 
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						mask_z = svdup_b32(0 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y00 = svld1(mask_xyz, &ptr_src[0 + (2*sy+3*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						mask_z = svdup_b32(1 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y10 = svld1(mask_xyz, &ptr_src[0 + (2*sy+3*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						mask_z = svdup_b32(2 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y20 = svld1(mask_xyz, &ptr_src[0 + (2*sy+3*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						mask_z = svdup_b32(3 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y30 = svld1(mask_xyz, &ptr_src[0 + (2*sy+3*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 12, 0)
						mask_y = svdup_b32(12 < ker_size_y - vy + 2); 
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						mask_z = svdup_b32(0 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y00 = svld1(mask_xyz, &ptr_src[0 + (3*sy)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						mask_z = svdup_b32(1 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y10 = svld1(mask_xyz, &ptr_src[0 + (3*sy+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						mask_z = svdup_b32(2 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y20 = svld1(mask_xyz, &ptr_src[0 + (3*sy+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						mask_z = svdup_b32(3 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y30 = svld1(mask_xyz, &ptr_src[0 + (3*sy+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 13, 0)
						mask_y = svdup_b32(13 < ker_size_y - vy + 2); 
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						mask_z = svdup_b32(0 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y00 = svld1(mask_xyz, &ptr_src[0 + (3*sy+1*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						mask_z = svdup_b32(1 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y10 = svld1(mask_xyz, &ptr_src[0 + (3*sy+1*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						mask_z = svdup_b32(2 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y20 = svld1(mask_xyz, &ptr_src[0 + (3*sy+1*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						mask_z = svdup_b32(3 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y30 = svld1(mask_xyz, &ptr_src[0 + (3*sy+1*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 14, 0)
						mask_y = svdup_b32(14 < ker_size_y - vy + 2); 
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						mask_z = svdup_b32(0 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y00 = svld1(mask_xyz, &ptr_src[0 + (3*sy+2*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						mask_z = svdup_b32(1 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y10 = svld1(mask_xyz, &ptr_src[0 + (3*sy+2*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						mask_z = svdup_b32(2 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y20 = svld1(mask_xyz, &ptr_src[0 + (3*sy+2*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						mask_z = svdup_b32(3 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y30 = svld1(mask_xyz, &ptr_src[0 + (3*sy+2*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 15, 0)
						mask_y = svdup_b32(15 < ker_size_y - vy + 2); 
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						mask_z = svdup_b32(0 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y00 = svld1(mask_xyz, &ptr_src[0 + (3*sy+3*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						mask_z = svdup_b32(1 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y10 = svld1(mask_xyz, &ptr_src[0 + (3*sy+3*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						mask_z = svdup_b32(2 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y20 = svld1(mask_xyz, &ptr_src[0 + (3*sy+3*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						mask_z = svdup_b32(3 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y30 = svld1(mask_xyz, &ptr_src[0 + (3*sy+3*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 16, 0)
						mask_y = svdup_b32(16 < ker_size_y - vy + 2); 
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						mask_z = svdup_b32(0 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y00 = svld1(mask_xyz, &ptr_r[0 + 0]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						mask_z = svdup_b32(1 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y10 = svld1(mask_xyz, &ptr_r[0 + (1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						mask_z = svdup_b32(2 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y20 = svld1(mask_xyz, &ptr_r[0 + (2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						mask_z = svdup_b32(3 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y30 = svld1(mask_xyz, &ptr_r[0 + (3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						// load vector at (0, 17, 0)
						mask_y = svdup_b32(17 < ker_size_y - vy + 2); 
						alpha_vec_y = svinsr(alpha_vec_y, 0); 
						mask_z = svdup_b32(0 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y00 = svld1(mask_xyz, &ptr_r[0 + (1*16)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_y, sme_input_y00); 
						
						mask_z = svdup_b32(1 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y10 = svld1(mask_xyz, &ptr_r[0 + (1*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_y, sme_input_y10); 
						
						mask_z = svdup_b32(2 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y20 = svld1(mask_xyz, &ptr_r[0 + (1*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_y, sme_input_y20); 
						
						mask_z = svdup_b32(3 < ker_size_z - vz - iz); mask_yz = svand_z(p32_all, mask_z, mask_y); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_y30 = svld1(mask_xyz, &ptr_r[0 + (1*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_y, sme_input_y30); 
						
						mask_x_0 = svwhilelt_b32(0, 16); 
						svst1_hor_za32(0, 0, mask_x_0, &temp_dst[0 + 0]); 
						svst1_hor_za32(0, 1, mask_x_0, &temp_dst[0 + (1*16)]); 
						svst1_hor_za32(0, 2, mask_x_0, &temp_dst[0 + (2*16)]); 
						svst1_hor_za32(0, 3, mask_x_0, &temp_dst[0 + (3*16)]); 
						svst1_hor_za32(0, 4, mask_x_0, &temp_dst[0 + (1*256)]); 
						svst1_hor_za32(0, 5, mask_x_0, &temp_dst[0 + (1*256+1*16)]); 
						svst1_hor_za32(0, 6, mask_x_0, &temp_dst[0 + (1*256+2*16)]); 
						svst1_hor_za32(0, 7, mask_x_0, &temp_dst[0 + (1*256+3*16)]); 
						svst1_hor_za32(0, 8, mask_x_0, &temp_dst[0 + (2*256)]); 
						svst1_hor_za32(0, 9, mask_x_0, &temp_dst[0 + (2*256+1*16)]); 
						svst1_hor_za32(0, 10, mask_x_0, &temp_dst[0 + (2*256+2*16)]); 
						svst1_hor_za32(0, 11, mask_x_0, &temp_dst[0 + (2*256+3*16)]); 
						svst1_hor_za32(0, 12, mask_x_0, &temp_dst[0 + (3*256)]); 
						svst1_hor_za32(0, 13, mask_x_0, &temp_dst[0 + (3*256+1*16)]); 
						svst1_hor_za32(0, 14, mask_x_0, &temp_dst[0 + (3*256+2*16)]); 
						svst1_hor_za32(0, 15, mask_x_0, &temp_dst[0 + (3*256+3*16)]); 
						svst1_hor_za32(1, 0, mask_x_0, &temp_dst[0 + (1*16*4)]); 
						svst1_hor_za32(1, 1, mask_x_0, &temp_dst[0 + (1*16+1*16*4)]); 
						svst1_hor_za32(1, 2, mask_x_0, &temp_dst[0 + (2*16+1*16*4)]); 
						svst1_hor_za32(1, 3, mask_x_0, &temp_dst[0 + (3*16+1*16*4)]); 
						svst1_hor_za32(1, 4, mask_x_0, &temp_dst[0 + (1*256+1*16*4)]); 
						svst1_hor_za32(1, 5, mask_x_0, &temp_dst[0 + (1*256+1*16+1*16*4)]); 
						svst1_hor_za32(1, 6, mask_x_0, &temp_dst[0 + (1*256+2*16+1*16*4)]); 
						svst1_hor_za32(1, 7, mask_x_0, &temp_dst[0 + (1*256+3*16+1*16*4)]); 
						svst1_hor_za32(1, 8, mask_x_0, &temp_dst[0 + (2*256+1*16*4)]); 
						svst1_hor_za32(1, 9, mask_x_0, &temp_dst[0 + (2*256+1*16+1*16*4)]); 
						svst1_hor_za32(1, 10, mask_x_0, &temp_dst[0 + (2*256+2*16+1*16*4)]); 
						svst1_hor_za32(1, 11, mask_x_0, &temp_dst[0 + (2*256+3*16+1*16*4)]); 
						svst1_hor_za32(1, 12, mask_x_0, &temp_dst[0 + (3*256+1*16*4)]); 
						svst1_hor_za32(1, 13, mask_x_0, &temp_dst[0 + (3*256+1*16+1*16*4)]); 
						svst1_hor_za32(1, 14, mask_x_0, &temp_dst[0 + (3*256+2*16+1*16*4)]); 
						svst1_hor_za32(1, 15, mask_x_0, &temp_dst[0 + (3*256+3*16+1*16*4)]); 
						svst1_hor_za32(2, 0, mask_x_0, &temp_dst[0 + (2*16*4)]); 
						svst1_hor_za32(2, 1, mask_x_0, &temp_dst[0 + (1*16+2*16*4)]); 
						svst1_hor_za32(2, 2, mask_x_0, &temp_dst[0 + (2*16+2*16*4)]); 
						svst1_hor_za32(2, 3, mask_x_0, &temp_dst[0 + (3*16+2*16*4)]); 
						svst1_hor_za32(2, 4, mask_x_0, &temp_dst[0 + (1*256+2*16*4)]); 
						svst1_hor_za32(2, 5, mask_x_0, &temp_dst[0 + (1*256+1*16+2*16*4)]); 
						svst1_hor_za32(2, 6, mask_x_0, &temp_dst[0 + (1*256+2*16+2*16*4)]); 
						svst1_hor_za32(2, 7, mask_x_0, &temp_dst[0 + (1*256+3*16+2*16*4)]); 
						svst1_hor_za32(2, 8, mask_x_0, &temp_dst[0 + (2*256+2*16*4)]); 
						svst1_hor_za32(2, 9, mask_x_0, &temp_dst[0 + (2*256+1*16+2*16*4)]); 
						svst1_hor_za32(2, 10, mask_x_0, &temp_dst[0 + (2*256+2*16+2*16*4)]); 
						svst1_hor_za32(2, 11, mask_x_0, &temp_dst[0 + (2*256+3*16+2*16*4)]); 
						svst1_hor_za32(2, 12, mask_x_0, &temp_dst[0 + (3*256+2*16*4)]); 
						svst1_hor_za32(2, 13, mask_x_0, &temp_dst[0 + (3*256+1*16+2*16*4)]); 
						svst1_hor_za32(2, 14, mask_x_0, &temp_dst[0 + (3*256+2*16+2*16*4)]); 
						svst1_hor_za32(2, 15, mask_x_0, &temp_dst[0 + (3*256+3*16+2*16*4)]); 
						svst1_hor_za32(3, 0, mask_x_0, &temp_dst[0 + (3*16*4)]); 
						svst1_hor_za32(3, 1, mask_x_0, &temp_dst[0 + (1*16+3*16*4)]); 
						svst1_hor_za32(3, 2, mask_x_0, &temp_dst[0 + (2*16+3*16*4)]); 
						svst1_hor_za32(3, 3, mask_x_0, &temp_dst[0 + (3*16+3*16*4)]); 
						svst1_hor_za32(3, 4, mask_x_0, &temp_dst[0 + (1*256+3*16*4)]); 
						svst1_hor_za32(3, 5, mask_x_0, &temp_dst[0 + (1*256+1*16+3*16*4)]); 
						svst1_hor_za32(3, 6, mask_x_0, &temp_dst[0 + (1*256+2*16+3*16*4)]); 
						svst1_hor_za32(3, 7, mask_x_0, &temp_dst[0 + (1*256+3*16+3*16*4)]); 
						svst1_hor_za32(3, 8, mask_x_0, &temp_dst[0 + (2*256+3*16*4)]); 
						svst1_hor_za32(3, 9, mask_x_0, &temp_dst[0 + (2*256+1*16+3*16*4)]); 
						svst1_hor_za32(3, 10, mask_x_0, &temp_dst[0 + (2*256+2*16+3*16*4)]); 
						svst1_hor_za32(3, 11, mask_x_0, &temp_dst[0 + (2*256+3*16+3*16*4)]); 
						svst1_hor_za32(3, 12, mask_x_0, &temp_dst[0 + (3*256+3*16*4)]); 
						svst1_hor_za32(3, 13, mask_x_0, &temp_dst[0 + (3*256+1*16+3*16*4)]); 
						svst1_hor_za32(3, 14, mask_x_0, &temp_dst[0 + (3*256+2*16+3*16*4)]); 
						svst1_hor_za32(3, 15, mask_x_0, &temp_dst[0 + (3*256+3*16+3*16*4)]); 
						ptr_src += (1*sz); ptr_l += (1*sz); ptr_r += (1*sz); ptr_dst += (1*dz);
					}
					//restore pointers after xy computation
					ptr_src -= 1*(1*sz); ptr_l -= 1*(1*sz); ptr_r -= 1*(1*sz); ptr_dst -= 1*(1*dz);
					for(int iy = 0; iy < 16; iy += 4) {
						temp_dst = buffer + 1*(3072) + (iy / 4)*(1*256);
						mask_x_0 = svwhilelt_b32(0, 16); 
						svld1_hor_za32(0, 0, mask_x_0, &temp_dst[0 + 0]); 
						svld1_hor_za32(1, 0, mask_x_0, &temp_dst[0 + (1*16)]); 
						svld1_hor_za32(2, 0, mask_x_0, &temp_dst[0 + (2*16)]); 
						svld1_hor_za32(3, 0, mask_x_0, &temp_dst[0 + (3*16)]); 
						svld1_hor_za32(0, 1, mask_x_0, &temp_dst[0 + (1*16*4)]); 
						svld1_hor_za32(1, 1, mask_x_0, &temp_dst[0 + (1*16+1*16*4)]); 
						svld1_hor_za32(2, 1, mask_x_0, &temp_dst[0 + (2*16+1*16*4)]); 
						svld1_hor_za32(3, 1, mask_x_0, &temp_dst[0 + (3*16+1*16*4)]); 
						svld1_hor_za32(0, 2, mask_x_0, &temp_dst[0 + (2*16*4)]); 
						svld1_hor_za32(1, 2, mask_x_0, &temp_dst[0 + (1*16+2*16*4)]); 
						svld1_hor_za32(2, 2, mask_x_0, &temp_dst[0 + (2*16+2*16*4)]); 
						svld1_hor_za32(3, 2, mask_x_0, &temp_dst[0 + (3*16+2*16*4)]); 
						svld1_hor_za32(0, 3, mask_x_0, &temp_dst[0 + (3*16*4)]); 
						svld1_hor_za32(1, 3, mask_x_0, &temp_dst[0 + (1*16+3*16*4)]); 
						svld1_hor_za32(2, 3, mask_x_0, &temp_dst[0 + (2*16+3*16*4)]); 
						svld1_hor_za32(3, 3, mask_x_0, &temp_dst[0 + (3*16+3*16*4)]); 
						// declare input vector registers
						svfloat32_t sme_input_z00,sme_input_z10,sme_input_z20,sme_input_z30; 
						// declare input coefficients
						svfloat32_t alpha_vec_z = svdup_f32_x(p32_all, 0); 
						mask_x_0 = svwhilelt_b32(0, ker_size_x - vx); 
						// load vector at (0, 0, -2)
						mask_z = svdup_b32(-2 < ker_size_z - vz + 2); 
						alpha_vec_z = svinsr(alpha_vec_z, coef[0]); 
						mask_y = svdup_b32(0 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z00 = svld1(mask_xyz, &ptr_src[0 + (-1*sz+2*16*4)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_z, sme_input_z00); 
						
						mask_y = svdup_b32(1 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z10 = svld1(mask_xyz, &ptr_src[0 + (1*16+-1*sz+2*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_z, sme_input_z10); 
						
						mask_y = svdup_b32(2 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z20 = svld1(mask_xyz, &ptr_src[0 + (2*16+-1*sz+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_z, sme_input_z20); 
						
						mask_y = svdup_b32(3 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z30 = svld1(mask_xyz, &ptr_src[0 + (3*16+-1*sz+2*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_z, sme_input_z30); 
						
						// load vector at (0, 0, -1)
						mask_z = svdup_b32(-1 < ker_size_z - vz + 2); 
						alpha_vec_z = svinsr(alpha_vec_z, coef[1]); 
						mask_y = svdup_b32(0 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z00 = svld1(mask_xyz, &ptr_src[0 + (-1*sz+3*16*4)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_z, sme_input_z00); 
						
						mask_y = svdup_b32(1 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z10 = svld1(mask_xyz, &ptr_src[0 + (1*16+-1*sz+3*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_z, sme_input_z10); 
						
						mask_y = svdup_b32(2 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z20 = svld1(mask_xyz, &ptr_src[0 + (2*16+-1*sz+3*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_z, sme_input_z20); 
						
						mask_y = svdup_b32(3 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z30 = svld1(mask_xyz, &ptr_src[0 + (3*16+-1*sz+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_z, sme_input_z30); 
						
						// load vector at (0, 0, 0)
						mask_z = svdup_b32(0 < ker_size_z - vz + 2); 
						alpha_vec_z = svinsr(alpha_vec_z, coef[2]); 
						mask_y = svdup_b32(0 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z00 = svld1(mask_xyz, &ptr_src[0 + 0]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_z, sme_input_z00); 
						
						mask_y = svdup_b32(1 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z10 = svld1(mask_xyz, &ptr_src[0 + (1*16)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_z, sme_input_z10); 
						
						mask_y = svdup_b32(2 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z20 = svld1(mask_xyz, &ptr_src[0 + (2*16)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_z, sme_input_z20); 
						
						mask_y = svdup_b32(3 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z30 = svld1(mask_xyz, &ptr_src[0 + (3*16)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_z, sme_input_z30); 
						
						// load vector at (0, 0, 1)
						mask_z = svdup_b32(1 < ker_size_z - vz + 2); 
						alpha_vec_z = svinsr(alpha_vec_z, coef[3]); 
						mask_y = svdup_b32(0 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z00 = svld1(mask_xyz, &ptr_src[0 + (1*16*4)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_z, sme_input_z00); 
						
						mask_y = svdup_b32(1 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z10 = svld1(mask_xyz, &ptr_src[0 + (1*16+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_z, sme_input_z10); 
						
						mask_y = svdup_b32(2 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z20 = svld1(mask_xyz, &ptr_src[0 + (2*16+1*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_z, sme_input_z20); 
						
						mask_y = svdup_b32(3 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z30 = svld1(mask_xyz, &ptr_src[0 + (3*16+1*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_z, sme_input_z30); 
						
						// load vector at (0, 0, 2)
						mask_z = svdup_b32(2 < ker_size_z - vz + 2); 
						alpha_vec_z = svinsr(alpha_vec_z, coef[4]); 
						mask_y = svdup_b32(0 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z00 = svld1(mask_xyz, &ptr_src[0 + (2*16*4)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_z, sme_input_z00); 
						
						mask_y = svdup_b32(1 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z10 = svld1(mask_xyz, &ptr_src[0 + (1*16+2*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_z, sme_input_z10); 
						
						mask_y = svdup_b32(2 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z20 = svld1(mask_xyz, &ptr_src[0 + (2*16+2*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_z, sme_input_z20); 
						
						mask_y = svdup_b32(3 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z30 = svld1(mask_xyz, &ptr_src[0 + (3*16+2*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_z, sme_input_z30); 
						
						// load vector at (0, 0, 3)
						mask_z = svdup_b32(3 < ker_size_z - vz + 2); 
						alpha_vec_z = svinsr(alpha_vec_z, 0); 
						mask_y = svdup_b32(0 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z00 = svld1(mask_xyz, &ptr_src[0 + (3*16*4)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_z, sme_input_z00); 
						
						mask_y = svdup_b32(1 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z10 = svld1(mask_xyz, &ptr_src[0 + (1*16+3*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_z, sme_input_z10); 
						
						mask_y = svdup_b32(2 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z20 = svld1(mask_xyz, &ptr_src[0 + (2*16+3*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_z, sme_input_z20); 
						
						mask_y = svdup_b32(3 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z30 = svld1(mask_xyz, &ptr_src[0 + (3*16+3*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_z, sme_input_z30); 
						
						// load vector at (0, 0, 4)
						mask_z = svdup_b32(4 < ker_size_z - vz + 2); 
						alpha_vec_z = svinsr(alpha_vec_z, 0); 
						mask_y = svdup_b32(0 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z00 = svld1(mask_xyz, &ptr_src[0 + (1*sz)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_z, sme_input_z00); 
						
						mask_y = svdup_b32(1 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z10 = svld1(mask_xyz, &ptr_src[0 + (1*16+1*sz)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_z, sme_input_z10); 
						
						mask_y = svdup_b32(2 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z20 = svld1(mask_xyz, &ptr_src[0 + (2*16+1*sz)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_z, sme_input_z20); 
						
						mask_y = svdup_b32(3 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z30 = svld1(mask_xyz, &ptr_src[0 + (3*16+1*sz)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_z, sme_input_z30); 
						
						// load vector at (0, 0, 5)
						mask_z = svdup_b32(5 < ker_size_z - vz + 2); 
						alpha_vec_z = svinsr(alpha_vec_z, 0); 
						mask_y = svdup_b32(0 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z00 = svld1(mask_xyz, &ptr_src[0 + (1*sz+1*16*4)]); svmopa_za32_m(0, p32_all, p32_all, alpha_vec_z, sme_input_z00); 
						
						mask_y = svdup_b32(1 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z10 = svld1(mask_xyz, &ptr_src[0 + (1*16+1*sz+1*16*4)]); svmopa_za32_m(1, p32_all, p32_all, alpha_vec_z, sme_input_z10); 
						
						mask_y = svdup_b32(2 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z20 = svld1(mask_xyz, &ptr_src[0 + (2*16+1*sz+1*16*4)]); svmopa_za32_m(2, p32_all, p32_all, alpha_vec_z, sme_input_z20); 
						
						mask_y = svdup_b32(3 < ker_size_y - vy - iy); mask_yz = svand_z(p32_all, mask_y, mask_z); 
						mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); sme_input_z30 = svld1(mask_xyz, &ptr_src[0 + (3*16+1*sz+1*16*4)]); svmopa_za32_m(3, p32_all, p32_all, alpha_vec_z, sme_input_z30); 
						
						mask_x_0 = svwhilelt_b32(0, ker_size_x - vx); 
						mask_z = svdup_b32(0 < ker_size_z - vz); 
						mask_y = svdup_b32(0 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svst1_hor_za32(0, 0, mask_xyz, &ptr_dst[0 + 0]); 
						mask_y = svdup_b32(1 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svst1_hor_za32(1, 0, mask_xyz, &ptr_dst[0 + (1*16)]); 
						mask_y = svdup_b32(2 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svst1_hor_za32(2, 0, mask_xyz, &ptr_dst[0 + (2*16)]); 
						mask_y = svdup_b32(3 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svst1_hor_za32(3, 0, mask_xyz, &ptr_dst[0 + (3*16)]); 
						mask_z = svdup_b32(1 < ker_size_z - vz); 
						mask_y = svdup_b32(0 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svst1_hor_za32(0, 1, mask_xyz, &ptr_dst[0 + (1*16*4)]); 
						mask_y = svdup_b32(1 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svst1_hor_za32(1, 1, mask_xyz, &ptr_dst[0 + (1*16+1*16*4)]); 
						mask_y = svdup_b32(2 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svst1_hor_za32(2, 1, mask_xyz, &ptr_dst[0 + (2*16+1*16*4)]); 
						mask_y = svdup_b32(3 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svst1_hor_za32(3, 1, mask_xyz, &ptr_dst[0 + (3*16+1*16*4)]); 
						mask_z = svdup_b32(2 < ker_size_z - vz); 
						mask_y = svdup_b32(0 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svst1_hor_za32(0, 2, mask_xyz, &ptr_dst[0 + (2*16*4)]); 
						mask_y = svdup_b32(1 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svst1_hor_za32(1, 2, mask_xyz, &ptr_dst[0 + (1*16+2*16*4)]); 
						mask_y = svdup_b32(2 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svst1_hor_za32(2, 2, mask_xyz, &ptr_dst[0 + (2*16+2*16*4)]); 
						mask_y = svdup_b32(3 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svst1_hor_za32(3, 2, mask_xyz, &ptr_dst[0 + (3*16+2*16*4)]); 
						mask_z = svdup_b32(3 < ker_size_z - vz); 
						mask_y = svdup_b32(0 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svst1_hor_za32(0, 3, mask_xyz, &ptr_dst[0 + (3*16*4)]); 
						mask_y = svdup_b32(1 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svst1_hor_za32(1, 3, mask_xyz, &ptr_dst[0 + (1*16+3*16*4)]); 
						mask_y = svdup_b32(2 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svst1_hor_za32(2, 3, mask_xyz, &ptr_dst[0 + (2*16+3*16*4)]); 
						mask_y = svdup_b32(3 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_x_0, mask_yz); svst1_hor_za32(3, 3, mask_xyz, &ptr_dst[0 + (3*16+3*16*4)]); 
						ptr_src += (1*sy); ptr_dst += (1*dy);
					}
					//restore pointers after z computation
					ptr_src -= 4*(1*sy); ptr_dst -= 4*(1*dy);
					temp_ptr = buffer_m1; buffer_m1 = buffer_0; buffer_0 = buffer_1; buffer_1 = temp_ptr;
					ptr_src += (1*16*4*4); ptr_l += (1*16*4*4); ptr_r += (1*16*4*4); ptr_dst += (1*16*4*4);
				}
			}
		}
	}
}
