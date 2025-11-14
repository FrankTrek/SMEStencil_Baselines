void stencil_2d_star_BrickBrick_1644_radius2(float *p0, float *p1, int ker_size_x, int ker_size_y, int ker_size_z, int sy, int sz, int dy, int dz, float *coef)
{
	svbool_t mask_x_0,mask_y,mask_z,mask_xy,mask_xz,mask_yz,mask_xyz,mask_ext;
	svbool_t p32_all = svdup_b32(true); 
	svfloat32_t pv000,pv100,pv200,pv300,pv010,pv110,pv210,pv310,pv020,pv120,pv220,pv320,pv030,pv130,pv230,pv330; 
	svfloat32_t iv000,iv100,iv200,iv300,iv010,iv110,iv210,iv310,iv020,iv120,iv220,iv320,iv030,iv130,iv230,iv330; 
	svfloat32_t nv000,nv100,nv200,nv300,nv010,nv110,nv210,nv310,nv020,nv120,nv220,nv320,nv030,nv130,nv230,nv330; 
	svfloat32_t ov000,ov100,ov200,ov300,ov010,ov110,ov210,ov310,ov020,ov120,ov220,ov320,ov030,ov130,ov230,ov330; 
	float *ptr_m1, *ptr_0, *ptr_1, *ptr_l, *ptr_r, *ptr_dst, *ptr_src, *temp_ptr, *coef_loc;
	for(int vz = 0; vz < ker_size_z; vz += 4) {
		for(int vy = 0; vy < ker_size_y; vy += 4) {
			int vec_size_y = min(ker_size_y - vy, 4), vec_size_z = min(ker_size_z - vz, 4);
			if(vec_size_y == 4 && vec_size_z == 4) {
				//inner loop start phase
				ptr_src = (p0 + (((vy)/4)*sy + ((vy)%4)*16+((vz)/2)*sz + ((vz)%2)*16*4)); ptr_dst = (p1 + (((vy)/4)*dy + ((vy)%4)*16+((vz)/2)*dz + ((vz)%2)*16*4)); ptr_l = ptr_src + (-1*sy+2*16); ptr_r = ptr_src + (1*sy);
				mask_ext = svwhilelt_b32(0, 14); mask_ext = sveor_z(p32_all, mask_ext, p32_all); 
				mask_x_0 = svwhilelt_b32(0, 16); 
				mask_x_0 = svand_z(p32_all, mask_x_0, mask_ext); 
				pv000 = svld1(mask_x_0, &ptr_src[(-1*16*4*2) + 0]); 
				pv010 = svld1(mask_x_0, &ptr_src[(-1*16*4*2) + (1*16)]); 
				pv020 = svld1(mask_x_0, &ptr_src[(-1*16*4*2) + (2*16)]); 
				pv030 = svld1(mask_x_0, &ptr_src[(-1*16*4*2) + (3*16)]); 
				pv100 = svld1(mask_x_0, &ptr_src[(-1*16*4*2) + (1*16*4)]); 
				pv110 = svld1(mask_x_0, &ptr_src[(-1*16*4*2) + (1*16+1*16*4)]); 
				pv120 = svld1(mask_x_0, &ptr_src[(-1*16*4*2) + (2*16+1*16*4)]); 
				pv130 = svld1(mask_x_0, &ptr_src[(-1*16*4*2) + (3*16+1*16*4)]); 
				pv200 = svld1(mask_x_0, &ptr_src[(-1*16*4*2) + (1*sz)]); 
				pv210 = svld1(mask_x_0, &ptr_src[(-1*16*4*2) + (1*16+1*sz)]); 
				pv220 = svld1(mask_x_0, &ptr_src[(-1*16*4*2) + (2*16+1*sz)]); 
				pv230 = svld1(mask_x_0, &ptr_src[(-1*16*4*2) + (3*16+1*sz)]); 
				pv300 = svld1(mask_x_0, &ptr_src[(-1*16*4*2) + (1*sz+1*16*4)]); 
				pv310 = svld1(mask_x_0, &ptr_src[(-1*16*4*2) + (1*16+1*sz+1*16*4)]); 
				pv320 = svld1(mask_x_0, &ptr_src[(-1*16*4*2) + (2*16+1*sz+1*16*4)]); 
				pv330 = svld1(mask_x_0, &ptr_src[(-1*16*4*2) + (3*16+1*sz+1*16*4)]); 
				mask_x_0 = svwhilelt_b32(0, ker_size_x + 2); 
				iv000 = svld1(mask_x_0, &ptr_src[0 + 0]); 
				iv010 = svld1(mask_x_0, &ptr_src[0 + (1*16)]); 
				iv020 = svld1(mask_x_0, &ptr_src[0 + (2*16)]); 
				iv030 = svld1(mask_x_0, &ptr_src[0 + (3*16)]); 
				iv100 = svld1(mask_x_0, &ptr_src[0 + (1*16*4)]); 
				iv110 = svld1(mask_x_0, &ptr_src[0 + (1*16+1*16*4)]); 
				iv120 = svld1(mask_x_0, &ptr_src[0 + (2*16+1*16*4)]); 
				iv130 = svld1(mask_x_0, &ptr_src[0 + (3*16+1*16*4)]); 
				iv200 = svld1(mask_x_0, &ptr_src[0 + (1*sz)]); 
				iv210 = svld1(mask_x_0, &ptr_src[0 + (1*16+1*sz)]); 
				iv220 = svld1(mask_x_0, &ptr_src[0 + (2*16+1*sz)]); 
				iv230 = svld1(mask_x_0, &ptr_src[0 + (3*16+1*sz)]); 
				iv300 = svld1(mask_x_0, &ptr_src[0 + (1*sz+1*16*4)]); 
				iv310 = svld1(mask_x_0, &ptr_src[0 + (1*16+1*sz+1*16*4)]); 
				iv320 = svld1(mask_x_0, &ptr_src[0 + (2*16+1*sz+1*16*4)]); 
				iv330 = svld1(mask_x_0, &ptr_src[0 + (3*16+1*sz+1*16*4)]); 
				//loop in x dimension starts
				for(int vx = 0; vx < ker_size_x; vx += 16) {
					ptr_1 = ptr_src + (1*16*4*2);
					ov000 = svdup_f32_x(p32_all, 0); ov010 = svdup_f32_x(p32_all, 0); ov020 = svdup_f32_x(p32_all, 0); ov030 = svdup_f32_x(p32_all, 0); 
					ov100 = svdup_f32_x(p32_all, 0); ov110 = svdup_f32_x(p32_all, 0); ov120 = svdup_f32_x(p32_all, 0); ov130 = svdup_f32_x(p32_all, 0); 
					ov200 = svdup_f32_x(p32_all, 0); ov210 = svdup_f32_x(p32_all, 0); ov220 = svdup_f32_x(p32_all, 0); ov230 = svdup_f32_x(p32_all, 0); 
					ov300 = svdup_f32_x(p32_all, 0); ov310 = svdup_f32_x(p32_all, 0); ov320 = svdup_f32_x(p32_all, 0); ov330 = svdup_f32_x(p32_all, 0); 
					{
						svfloat32_t temp000,temp100,temp200,temp300; 
						mask_x_0 = svwhilelt_b32(0, ker_size_x - vx + 2); 
						//compute using grid[:, -2, :]
						temp000 = svld1(mask_x_0, &ptr_l[0 + 0]); 
						ov000 = svmla_x(p32_all, ov000, temp000, coef[0]); 
						temp100 = svld1(mask_x_0, &ptr_l[0 + (1*16*4)]); 
						ov100 = svmla_x(p32_all, ov100, temp100, coef[0]); 
						temp200 = svld1(mask_x_0, &ptr_l[0 + (1*sz)]); 
						ov200 = svmla_x(p32_all, ov200, temp200, coef[0]); 
						temp300 = svld1(mask_x_0, &ptr_l[0 + (1*sz+1*16*4)]); 
						ov300 = svmla_x(p32_all, ov300, temp300, coef[0]); 
						//compute using grid[:, -1, :]
						temp000 = svld1(mask_x_0, &ptr_l[0 + (1*16)]); 
						ov000 = svmla_x(p32_all, ov000, temp000, coef[1]); ov010 = svmla_x(p32_all, ov010, temp000, coef[0]); 
						temp100 = svld1(mask_x_0, &ptr_l[0 + (1*16+1*16*4)]); 
						ov100 = svmla_x(p32_all, ov100, temp100, coef[1]); ov110 = svmla_x(p32_all, ov110, temp100, coef[0]); 
						temp200 = svld1(mask_x_0, &ptr_l[0 + (1*16+1*sz)]); 
						ov200 = svmla_x(p32_all, ov200, temp200, coef[1]); ov210 = svmla_x(p32_all, ov210, temp200, coef[0]); 
						temp300 = svld1(mask_x_0, &ptr_l[0 + (1*16+1*sz+1*16*4)]); 
						ov300 = svmla_x(p32_all, ov300, temp300, coef[1]); ov310 = svmla_x(p32_all, ov310, temp300, coef[0]); 
						//compute using grid[:, 0, :]
						ov000 = svmla_x(p32_all, ov000, iv000, coef[2]); ov010 = svmla_x(p32_all, ov010, iv000, coef[1]); ov020 = svmla_x(p32_all, ov020, iv000, coef[0]); 
						ov100 = svmla_x(p32_all, ov100, iv100, coef[2]); ov110 = svmla_x(p32_all, ov110, iv100, coef[1]); ov120 = svmla_x(p32_all, ov120, iv100, coef[0]); 
						ov200 = svmla_x(p32_all, ov200, iv200, coef[2]); ov210 = svmla_x(p32_all, ov210, iv200, coef[1]); ov220 = svmla_x(p32_all, ov220, iv200, coef[0]); 
						ov300 = svmla_x(p32_all, ov300, iv300, coef[2]); ov310 = svmla_x(p32_all, ov310, iv300, coef[1]); ov320 = svmla_x(p32_all, ov320, iv300, coef[0]); 
						//compute using grid[:, 1, :]
						ov000 = svmla_x(p32_all, ov000, iv010, coef[3]); ov010 = svmla_x(p32_all, ov010, iv010, coef[2]); ov020 = svmla_x(p32_all, ov020, iv010, coef[1]); ov030 = svmla_x(p32_all, ov030, iv010, coef[0]); 
						ov100 = svmla_x(p32_all, ov100, iv110, coef[3]); ov110 = svmla_x(p32_all, ov110, iv110, coef[2]); ov120 = svmla_x(p32_all, ov120, iv110, coef[1]); ov130 = svmla_x(p32_all, ov130, iv110, coef[0]); 
						ov200 = svmla_x(p32_all, ov200, iv210, coef[3]); ov210 = svmla_x(p32_all, ov210, iv210, coef[2]); ov220 = svmla_x(p32_all, ov220, iv210, coef[1]); ov230 = svmla_x(p32_all, ov230, iv210, coef[0]); 
						ov300 = svmla_x(p32_all, ov300, iv310, coef[3]); ov310 = svmla_x(p32_all, ov310, iv310, coef[2]); ov320 = svmla_x(p32_all, ov320, iv310, coef[1]); ov330 = svmla_x(p32_all, ov330, iv310, coef[0]); 
						//compute using grid[:, 2, :]
						ov000 = svmla_x(p32_all, ov000, iv020, coef[4]); ov010 = svmla_x(p32_all, ov010, iv020, coef[3]); ov020 = svmla_x(p32_all, ov020, iv020, coef[2]); ov030 = svmla_x(p32_all, ov030, iv020, coef[1]); 
						ov100 = svmla_x(p32_all, ov100, iv120, coef[4]); ov110 = svmla_x(p32_all, ov110, iv120, coef[3]); ov120 = svmla_x(p32_all, ov120, iv120, coef[2]); ov130 = svmla_x(p32_all, ov130, iv120, coef[1]); 
						ov200 = svmla_x(p32_all, ov200, iv220, coef[4]); ov210 = svmla_x(p32_all, ov210, iv220, coef[3]); ov220 = svmla_x(p32_all, ov220, iv220, coef[2]); ov230 = svmla_x(p32_all, ov230, iv220, coef[1]); 
						ov300 = svmla_x(p32_all, ov300, iv320, coef[4]); ov310 = svmla_x(p32_all, ov310, iv320, coef[3]); ov320 = svmla_x(p32_all, ov320, iv320, coef[2]); ov330 = svmla_x(p32_all, ov330, iv320, coef[1]); 
						//compute using grid[:, 3, :]
						ov010 = svmla_x(p32_all, ov010, iv030, coef[4]); ov020 = svmla_x(p32_all, ov020, iv030, coef[3]); ov030 = svmla_x(p32_all, ov030, iv030, coef[2]); 
						ov110 = svmla_x(p32_all, ov110, iv130, coef[4]); ov120 = svmla_x(p32_all, ov120, iv130, coef[3]); ov130 = svmla_x(p32_all, ov130, iv130, coef[2]); 
						ov210 = svmla_x(p32_all, ov210, iv230, coef[4]); ov220 = svmla_x(p32_all, ov220, iv230, coef[3]); ov230 = svmla_x(p32_all, ov230, iv230, coef[2]); 
						ov310 = svmla_x(p32_all, ov310, iv330, coef[4]); ov320 = svmla_x(p32_all, ov320, iv330, coef[3]); ov330 = svmla_x(p32_all, ov330, iv330, coef[2]); 
						//compute using grid[:, 4, :]
						temp000 = svld1(mask_x_0, &ptr_r[0 + 0]); 
						ov020 = svmla_x(p32_all, ov020, temp000, coef[4]); ov030 = svmla_x(p32_all, ov030, temp000, coef[3]); 
						temp100 = svld1(mask_x_0, &ptr_r[0 + (1*16*4)]); 
						ov120 = svmla_x(p32_all, ov120, temp100, coef[4]); ov130 = svmla_x(p32_all, ov130, temp100, coef[3]); 
						temp200 = svld1(mask_x_0, &ptr_r[0 + (1*sz)]); 
						ov220 = svmla_x(p32_all, ov220, temp200, coef[4]); ov230 = svmla_x(p32_all, ov230, temp200, coef[3]); 
						temp300 = svld1(mask_x_0, &ptr_r[0 + (1*sz+1*16*4)]); 
						ov320 = svmla_x(p32_all, ov320, temp300, coef[4]); ov330 = svmla_x(p32_all, ov330, temp300, coef[3]); 
						//compute using grid[:, 5, :]
						temp000 = svld1(mask_x_0, &ptr_r[0 + (1*16)]); 
						ov030 = svmla_x(p32_all, ov030, temp000, coef[4]); 
						temp100 = svld1(mask_x_0, &ptr_r[0 + (1*16+1*16*4)]); 
						ov130 = svmla_x(p32_all, ov130, temp100, coef[4]); 
						temp200 = svld1(mask_x_0, &ptr_r[0 + (1*16+1*sz)]); 
						ov230 = svmla_x(p32_all, ov230, temp200, coef[4]); 
						temp300 = svld1(mask_x_0, &ptr_r[0 + (1*16+1*sz+1*16*4)]); 
						ov330 = svmla_x(p32_all, ov330, temp300, coef[4]); 
					}
					{
						svfloat32_t temp000,temp100,temp200,temp300,temp010,temp110,temp210,temp310,temp020,temp120,temp220,temp320,temp030,temp130,temp230,temp330; 
						//compute using [-VX:0] and [0:VX]
						//generate vector: [-Radius + 0: VX - Radius + 0]
						temp000 = svext(pv000, iv000, 14); temp010 = svext(pv010, iv010, 14); temp020 = svext(pv020, iv020, 14); temp030 = svext(pv030, iv030, 14); 
						ov000 = svmla_x(p32_all, ov000, temp000, coef[0]); ov010 = svmla_x(p32_all, ov010, temp010, coef[0]); ov020 = svmla_x(p32_all, ov020, temp020, coef[0]); ov030 = svmla_x(p32_all, ov030, temp030, coef[0]); 
						temp100 = svext(pv100, iv100, 14); temp110 = svext(pv110, iv110, 14); temp120 = svext(pv120, iv120, 14); temp130 = svext(pv130, iv130, 14); 
						ov100 = svmla_x(p32_all, ov100, temp100, coef[0]); ov110 = svmla_x(p32_all, ov110, temp110, coef[0]); ov120 = svmla_x(p32_all, ov120, temp120, coef[0]); ov130 = svmla_x(p32_all, ov130, temp130, coef[0]); 
						temp200 = svext(pv200, iv200, 14); temp210 = svext(pv210, iv210, 14); temp220 = svext(pv220, iv220, 14); temp230 = svext(pv230, iv230, 14); 
						ov200 = svmla_x(p32_all, ov200, temp200, coef[0]); ov210 = svmla_x(p32_all, ov210, temp210, coef[0]); ov220 = svmla_x(p32_all, ov220, temp220, coef[0]); ov230 = svmla_x(p32_all, ov230, temp230, coef[0]); 
						temp300 = svext(pv300, iv300, 14); temp310 = svext(pv310, iv310, 14); temp320 = svext(pv320, iv320, 14); temp330 = svext(pv330, iv330, 14); 
						ov300 = svmla_x(p32_all, ov300, temp300, coef[0]); ov310 = svmla_x(p32_all, ov310, temp310, coef[0]); ov320 = svmla_x(p32_all, ov320, temp320, coef[0]); ov330 = svmla_x(p32_all, ov330, temp330, coef[0]); 
						//generate vector: [-Radius + 1: VX - Radius + 1]
						temp000 = svext(pv000, iv000, 15); temp010 = svext(pv010, iv010, 15); temp020 = svext(pv020, iv020, 15); temp030 = svext(pv030, iv030, 15); 
						ov000 = svmla_x(p32_all, ov000, temp000, coef[1]); ov010 = svmla_x(p32_all, ov010, temp010, coef[1]); ov020 = svmla_x(p32_all, ov020, temp020, coef[1]); ov030 = svmla_x(p32_all, ov030, temp030, coef[1]); 
						temp100 = svext(pv100, iv100, 15); temp110 = svext(pv110, iv110, 15); temp120 = svext(pv120, iv120, 15); temp130 = svext(pv130, iv130, 15); 
						ov100 = svmla_x(p32_all, ov100, temp100, coef[1]); ov110 = svmla_x(p32_all, ov110, temp110, coef[1]); ov120 = svmla_x(p32_all, ov120, temp120, coef[1]); ov130 = svmla_x(p32_all, ov130, temp130, coef[1]); 
						temp200 = svext(pv200, iv200, 15); temp210 = svext(pv210, iv210, 15); temp220 = svext(pv220, iv220, 15); temp230 = svext(pv230, iv230, 15); 
						ov200 = svmla_x(p32_all, ov200, temp200, coef[1]); ov210 = svmla_x(p32_all, ov210, temp210, coef[1]); ov220 = svmla_x(p32_all, ov220, temp220, coef[1]); ov230 = svmla_x(p32_all, ov230, temp230, coef[1]); 
						temp300 = svext(pv300, iv300, 15); temp310 = svext(pv310, iv310, 15); temp320 = svext(pv320, iv320, 15); temp330 = svext(pv330, iv330, 15); 
						ov300 = svmla_x(p32_all, ov300, temp300, coef[1]); ov310 = svmla_x(p32_all, ov310, temp310, coef[1]); ov320 = svmla_x(p32_all, ov320, temp320, coef[1]); ov330 = svmla_x(p32_all, ov330, temp330, coef[1]); 
						//compute using [0:VX]
						ov000 = svmla_x(p32_all, ov000, iv000, coef[2]); ov010 = svmla_x(p32_all, ov010, iv010, coef[2]); ov020 = svmla_x(p32_all, ov020, iv020, coef[2]); ov030 = svmla_x(p32_all, ov030, iv030, coef[2]); 
						ov100 = svmla_x(p32_all, ov100, iv100, coef[2]); ov110 = svmla_x(p32_all, ov110, iv110, coef[2]); ov120 = svmla_x(p32_all, ov120, iv120, coef[2]); ov130 = svmla_x(p32_all, ov130, iv130, coef[2]); 
						ov200 = svmla_x(p32_all, ov200, iv200, coef[2]); ov210 = svmla_x(p32_all, ov210, iv210, coef[2]); ov220 = svmla_x(p32_all, ov220, iv220, coef[2]); ov230 = svmla_x(p32_all, ov230, iv230, coef[2]); 
						ov300 = svmla_x(p32_all, ov300, iv300, coef[2]); ov310 = svmla_x(p32_all, ov310, iv310, coef[2]); ov320 = svmla_x(p32_all, ov320, iv320, coef[2]); ov330 = svmla_x(p32_all, ov330, iv330, coef[2]); 
						//compute using [0:VX] and [VX:2VX]
						mask_x_0 = svwhilelt_b32(0, ker_size_x - vx + 2 - 16); 
						nv000 = svld1(mask_x_0, &ptr_1[0 + 0]); 
						nv010 = svld1(mask_x_0, &ptr_1[0 + (1*16)]); 
						nv020 = svld1(mask_x_0, &ptr_1[0 + (2*16)]); 
						nv030 = svld1(mask_x_0, &ptr_1[0 + (3*16)]); 
						nv100 = svld1(mask_x_0, &ptr_1[0 + (1*16*4)]); 
						nv110 = svld1(mask_x_0, &ptr_1[0 + (1*16+1*16*4)]); 
						nv120 = svld1(mask_x_0, &ptr_1[0 + (2*16+1*16*4)]); 
						nv130 = svld1(mask_x_0, &ptr_1[0 + (3*16+1*16*4)]); 
						nv200 = svld1(mask_x_0, &ptr_1[0 + (1*sz)]); 
						nv210 = svld1(mask_x_0, &ptr_1[0 + (1*16+1*sz)]); 
						nv220 = svld1(mask_x_0, &ptr_1[0 + (2*16+1*sz)]); 
						nv230 = svld1(mask_x_0, &ptr_1[0 + (3*16+1*sz)]); 
						nv300 = svld1(mask_x_0, &ptr_1[0 + (1*sz+1*16*4)]); 
						nv310 = svld1(mask_x_0, &ptr_1[0 + (1*16+1*sz+1*16*4)]); 
						nv320 = svld1(mask_x_0, &ptr_1[0 + (2*16+1*sz+1*16*4)]); 
						nv330 = svld1(mask_x_0, &ptr_1[0 + (3*16+1*sz+1*16*4)]); 
						//generate vector: [0: VX + 0]
						temp000 = svext(iv000, nv000, 1); temp010 = svext(iv010, nv010, 1); temp020 = svext(iv020, nv020, 1); temp030 = svext(iv030, nv030, 1); 
						ov000 = svmla_x(p32_all, ov000, temp000, coef[3]); ov010 = svmla_x(p32_all, ov010, temp010, coef[3]); ov020 = svmla_x(p32_all, ov020, temp020, coef[3]); ov030 = svmla_x(p32_all, ov030, temp030, coef[3]); 
						temp100 = svext(iv100, nv100, 1); temp110 = svext(iv110, nv110, 1); temp120 = svext(iv120, nv120, 1); temp130 = svext(iv130, nv130, 1); 
						ov100 = svmla_x(p32_all, ov100, temp100, coef[3]); ov110 = svmla_x(p32_all, ov110, temp110, coef[3]); ov120 = svmla_x(p32_all, ov120, temp120, coef[3]); ov130 = svmla_x(p32_all, ov130, temp130, coef[3]); 
						temp200 = svext(iv200, nv200, 1); temp210 = svext(iv210, nv210, 1); temp220 = svext(iv220, nv220, 1); temp230 = svext(iv230, nv230, 1); 
						ov200 = svmla_x(p32_all, ov200, temp200, coef[3]); ov210 = svmla_x(p32_all, ov210, temp210, coef[3]); ov220 = svmla_x(p32_all, ov220, temp220, coef[3]); ov230 = svmla_x(p32_all, ov230, temp230, coef[3]); 
						temp300 = svext(iv300, nv300, 1); temp310 = svext(iv310, nv310, 1); temp320 = svext(iv320, nv320, 1); temp330 = svext(iv330, nv330, 1); 
						ov300 = svmla_x(p32_all, ov300, temp300, coef[3]); ov310 = svmla_x(p32_all, ov310, temp310, coef[3]); ov320 = svmla_x(p32_all, ov320, temp320, coef[3]); ov330 = svmla_x(p32_all, ov330, temp330, coef[3]); 
						//generate vector: [1: VX + 1]
						temp000 = svext(iv000, nv000, 2); temp010 = svext(iv010, nv010, 2); temp020 = svext(iv020, nv020, 2); temp030 = svext(iv030, nv030, 2); 
						ov000 = svmla_x(p32_all, ov000, temp000, coef[4]); ov010 = svmla_x(p32_all, ov010, temp010, coef[4]); ov020 = svmla_x(p32_all, ov020, temp020, coef[4]); ov030 = svmla_x(p32_all, ov030, temp030, coef[4]); 
						temp100 = svext(iv100, nv100, 2); temp110 = svext(iv110, nv110, 2); temp120 = svext(iv120, nv120, 2); temp130 = svext(iv130, nv130, 2); 
						ov100 = svmla_x(p32_all, ov100, temp100, coef[4]); ov110 = svmla_x(p32_all, ov110, temp110, coef[4]); ov120 = svmla_x(p32_all, ov120, temp120, coef[4]); ov130 = svmla_x(p32_all, ov130, temp130, coef[4]); 
						temp200 = svext(iv200, nv200, 2); temp210 = svext(iv210, nv210, 2); temp220 = svext(iv220, nv220, 2); temp230 = svext(iv230, nv230, 2); 
						ov200 = svmla_x(p32_all, ov200, temp200, coef[4]); ov210 = svmla_x(p32_all, ov210, temp210, coef[4]); ov220 = svmla_x(p32_all, ov220, temp220, coef[4]); ov230 = svmla_x(p32_all, ov230, temp230, coef[4]); 
						temp300 = svext(iv300, nv300, 2); temp310 = svext(iv310, nv310, 2); temp320 = svext(iv320, nv320, 2); temp330 = svext(iv330, nv330, 2); 
						ov300 = svmla_x(p32_all, ov300, temp300, coef[4]); ov310 = svmla_x(p32_all, ov310, temp310, coef[4]); ov320 = svmla_x(p32_all, ov320, temp320, coef[4]); ov330 = svmla_x(p32_all, ov330, temp330, coef[4]); 
					}
					mask_x_0 = svwhilelt_b32(0, ker_size_x - vx); 
					svst1(mask_x_0, &ptr_dst[0 + 0], ov000); 
					svst1(mask_x_0, &ptr_dst[0 + (1*16)], ov010); 
					svst1(mask_x_0, &ptr_dst[0 + (2*16)], ov020); 
					svst1(mask_x_0, &ptr_dst[0 + (3*16)], ov030); 
					svst1(mask_x_0, &ptr_dst[0 + (1*16*4)], ov100); 
					svst1(mask_x_0, &ptr_dst[0 + (1*16+1*16*4)], ov110); 
					svst1(mask_x_0, &ptr_dst[0 + (2*16+1*16*4)], ov120); 
					svst1(mask_x_0, &ptr_dst[0 + (3*16+1*16*4)], ov130); 
					svst1(mask_x_0, &ptr_dst[0 + (1*dz)], ov200); 
					svst1(mask_x_0, &ptr_dst[0 + (1*16+1*dz)], ov210); 
					svst1(mask_x_0, &ptr_dst[0 + (2*16+1*dz)], ov220); 
					svst1(mask_x_0, &ptr_dst[0 + (3*16+1*dz)], ov230); 
					svst1(mask_x_0, &ptr_dst[0 + (1*dz+1*16*4)], ov300); 
					svst1(mask_x_0, &ptr_dst[0 + (1*16+1*dz+1*16*4)], ov310); 
					svst1(mask_x_0, &ptr_dst[0 + (2*16+1*dz+1*16*4)], ov320); 
					svst1(mask_x_0, &ptr_dst[0 + (3*16+1*dz+1*16*4)], ov330); 
					pv000 = iv000; pv010 = iv010; pv020 = iv020; pv030 = iv030; 
					pv100 = iv100; pv110 = iv110; pv120 = iv120; pv130 = iv130; 
					pv200 = iv200; pv210 = iv210; pv220 = iv220; pv230 = iv230; 
					pv300 = iv300; pv310 = iv310; pv320 = iv320; pv330 = iv330; 
					iv000 = nv000; iv010 = nv010; iv020 = nv020; iv030 = nv030; 
					iv100 = nv100; iv110 = nv110; iv120 = nv120; iv130 = nv130; 
					iv200 = nv200; iv210 = nv210; iv220 = nv220; iv230 = nv230; 
					iv300 = nv300; iv310 = nv310; iv320 = nv320; iv330 = nv330; 
					ptr_src += (1*16*4*2); ptr_l += (1*16*4*2); ptr_r += (1*16*4*2); ptr_dst += (1*16*4*2);
				}
			} else {
				//inner loop start phase
				ptr_src = (p0 + (((vy)/4)*sy + ((vy)%4)*16+((vz)/2)*sz + ((vz)%2)*16*4)); ptr_dst = (p1 + (((vy)/4)*dy + ((vy)%4)*16+((vz)/2)*dz + ((vz)%2)*16*4)); ptr_l = ptr_src + (-1*sy+2*16); ptr_r = ptr_src + (1*sy);
				mask_ext = svwhilelt_b32(0, 14); mask_ext = sveor_z(p32_all, mask_ext, p32_all); 
				mask_x_0 = svwhilelt_b32(0, 16); 
				mask_x_0 = svand_z(p32_all, mask_x_0, mask_ext); 
				mask_z = svdup_b32(0 < ker_size_z - vz); 
				mask_y = svdup_b32(0 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); pv000 = svld1(mask_xyz, &ptr_src[(-1*16*4*2) + 0]); 
				mask_y = svdup_b32(1 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); pv010 = svld1(mask_xyz, &ptr_src[(-1*16*4*2) + (1*16)]); 
				mask_y = svdup_b32(2 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); pv020 = svld1(mask_xyz, &ptr_src[(-1*16*4*2) + (2*16)]); 
				mask_y = svdup_b32(3 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); pv030 = svld1(mask_xyz, &ptr_src[(-1*16*4*2) + (3*16)]); 
				mask_z = svdup_b32(1 < ker_size_z - vz); 
				mask_y = svdup_b32(0 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); pv100 = svld1(mask_xyz, &ptr_src[(-1*16*4*2) + (1*16*4)]); 
				mask_y = svdup_b32(1 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); pv110 = svld1(mask_xyz, &ptr_src[(-1*16*4*2) + (1*16+1*16*4)]); 
				mask_y = svdup_b32(2 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); pv120 = svld1(mask_xyz, &ptr_src[(-1*16*4*2) + (2*16+1*16*4)]); 
				mask_y = svdup_b32(3 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); pv130 = svld1(mask_xyz, &ptr_src[(-1*16*4*2) + (3*16+1*16*4)]); 
				mask_z = svdup_b32(2 < ker_size_z - vz); 
				mask_y = svdup_b32(0 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); pv200 = svld1(mask_xyz, &ptr_src[(-1*16*4*2) + (1*sz)]); 
				mask_y = svdup_b32(1 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); pv210 = svld1(mask_xyz, &ptr_src[(-1*16*4*2) + (1*16+1*sz)]); 
				mask_y = svdup_b32(2 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); pv220 = svld1(mask_xyz, &ptr_src[(-1*16*4*2) + (2*16+1*sz)]); 
				mask_y = svdup_b32(3 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); pv230 = svld1(mask_xyz, &ptr_src[(-1*16*4*2) + (3*16+1*sz)]); 
				mask_z = svdup_b32(3 < ker_size_z - vz); 
				mask_y = svdup_b32(0 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); pv300 = svld1(mask_xyz, &ptr_src[(-1*16*4*2) + (1*sz+1*16*4)]); 
				mask_y = svdup_b32(1 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); pv310 = svld1(mask_xyz, &ptr_src[(-1*16*4*2) + (1*16+1*sz+1*16*4)]); 
				mask_y = svdup_b32(2 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); pv320 = svld1(mask_xyz, &ptr_src[(-1*16*4*2) + (2*16+1*sz+1*16*4)]); 
				mask_y = svdup_b32(3 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); pv330 = svld1(mask_xyz, &ptr_src[(-1*16*4*2) + (3*16+1*sz+1*16*4)]); 
				mask_x_0 = svwhilelt_b32(0, ker_size_x + 2); 
				mask_z = svdup_b32(0 < ker_size_z - vz); 
				mask_y = svdup_b32(0 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); iv000 = svld1(mask_xyz, &ptr_src[0 + 0]); 
				mask_y = svdup_b32(1 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); iv010 = svld1(mask_xyz, &ptr_src[0 + (1*16)]); 
				mask_y = svdup_b32(2 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); iv020 = svld1(mask_xyz, &ptr_src[0 + (2*16)]); 
				mask_y = svdup_b32(3 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); iv030 = svld1(mask_xyz, &ptr_src[0 + (3*16)]); 
				mask_z = svdup_b32(1 < ker_size_z - vz); 
				mask_y = svdup_b32(0 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); iv100 = svld1(mask_xyz, &ptr_src[0 + (1*16*4)]); 
				mask_y = svdup_b32(1 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); iv110 = svld1(mask_xyz, &ptr_src[0 + (1*16+1*16*4)]); 
				mask_y = svdup_b32(2 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); iv120 = svld1(mask_xyz, &ptr_src[0 + (2*16+1*16*4)]); 
				mask_y = svdup_b32(3 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); iv130 = svld1(mask_xyz, &ptr_src[0 + (3*16+1*16*4)]); 
				mask_z = svdup_b32(2 < ker_size_z - vz); 
				mask_y = svdup_b32(0 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); iv200 = svld1(mask_xyz, &ptr_src[0 + (1*sz)]); 
				mask_y = svdup_b32(1 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); iv210 = svld1(mask_xyz, &ptr_src[0 + (1*16+1*sz)]); 
				mask_y = svdup_b32(2 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); iv220 = svld1(mask_xyz, &ptr_src[0 + (2*16+1*sz)]); 
				mask_y = svdup_b32(3 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); iv230 = svld1(mask_xyz, &ptr_src[0 + (3*16+1*sz)]); 
				mask_z = svdup_b32(3 < ker_size_z - vz); 
				mask_y = svdup_b32(0 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); iv300 = svld1(mask_xyz, &ptr_src[0 + (1*sz+1*16*4)]); 
				mask_y = svdup_b32(1 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); iv310 = svld1(mask_xyz, &ptr_src[0 + (1*16+1*sz+1*16*4)]); 
				mask_y = svdup_b32(2 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); iv320 = svld1(mask_xyz, &ptr_src[0 + (2*16+1*sz+1*16*4)]); 
				mask_y = svdup_b32(3 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); iv330 = svld1(mask_xyz, &ptr_src[0 + (3*16+1*sz+1*16*4)]); 
				//loop in x dimension starts
				for(int vx = 0; vx < ker_size_x; vx += 16) {
					ptr_1 = ptr_src + (1*16*4*2);
					ov000 = svdup_f32_x(p32_all, 0); ov010 = svdup_f32_x(p32_all, 0); ov020 = svdup_f32_x(p32_all, 0); ov030 = svdup_f32_x(p32_all, 0); 
					ov100 = svdup_f32_x(p32_all, 0); ov110 = svdup_f32_x(p32_all, 0); ov120 = svdup_f32_x(p32_all, 0); ov130 = svdup_f32_x(p32_all, 0); 
					ov200 = svdup_f32_x(p32_all, 0); ov210 = svdup_f32_x(p32_all, 0); ov220 = svdup_f32_x(p32_all, 0); ov230 = svdup_f32_x(p32_all, 0); 
					ov300 = svdup_f32_x(p32_all, 0); ov310 = svdup_f32_x(p32_all, 0); ov320 = svdup_f32_x(p32_all, 0); ov330 = svdup_f32_x(p32_all, 0); 
					{
						svfloat32_t temp000,temp100,temp200,temp300; 
						mask_x_0 = svwhilelt_b32(0, ker_size_x - vx + 2); 
						//compute using grid[:, -2, :]
						mask_y = svdup_b32(-2 < ker_size_y - vy + 2); 
						mask_z = svdup_b32(0 < ker_size_z - vz); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						mask_xyz = svand_z(p32_all, mask_xy, mask_z); temp000 = svld1(mask_xyz, &ptr_l[0 + 0]); 
						ov000 = svmla_x(p32_all, ov000, temp000, coef[0]); 
						mask_z = svdup_b32(1 < ker_size_z - vz); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						mask_xyz = svand_z(p32_all, mask_xy, mask_z); temp100 = svld1(mask_xyz, &ptr_l[0 + (1*16*4)]); 
						ov100 = svmla_x(p32_all, ov100, temp100, coef[0]); 
						mask_z = svdup_b32(2 < ker_size_z - vz); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						mask_xyz = svand_z(p32_all, mask_xy, mask_z); temp200 = svld1(mask_xyz, &ptr_l[0 + (1*sz)]); 
						ov200 = svmla_x(p32_all, ov200, temp200, coef[0]); 
						mask_z = svdup_b32(3 < ker_size_z - vz); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						mask_xyz = svand_z(p32_all, mask_xy, mask_z); temp300 = svld1(mask_xyz, &ptr_l[0 + (1*sz+1*16*4)]); 
						ov300 = svmla_x(p32_all, ov300, temp300, coef[0]); 
						//compute using grid[:, -1, :]
						mask_y = svdup_b32(-1 < ker_size_y - vy + 2); 
						mask_z = svdup_b32(0 < ker_size_z - vz); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						mask_xyz = svand_z(p32_all, mask_xy, mask_z); temp000 = svld1(mask_xyz, &ptr_l[0 + (1*16)]); 
						ov000 = svmla_x(p32_all, ov000, temp000, coef[1]); ov010 = svmla_x(p32_all, ov010, temp000, coef[0]); 
						mask_z = svdup_b32(1 < ker_size_z - vz); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						mask_xyz = svand_z(p32_all, mask_xy, mask_z); temp100 = svld1(mask_xyz, &ptr_l[0 + (1*16+1*16*4)]); 
						ov100 = svmla_x(p32_all, ov100, temp100, coef[1]); ov110 = svmla_x(p32_all, ov110, temp100, coef[0]); 
						mask_z = svdup_b32(2 < ker_size_z - vz); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						mask_xyz = svand_z(p32_all, mask_xy, mask_z); temp200 = svld1(mask_xyz, &ptr_l[0 + (1*16+1*sz)]); 
						ov200 = svmla_x(p32_all, ov200, temp200, coef[1]); ov210 = svmla_x(p32_all, ov210, temp200, coef[0]); 
						mask_z = svdup_b32(3 < ker_size_z - vz); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						mask_xyz = svand_z(p32_all, mask_xy, mask_z); temp300 = svld1(mask_xyz, &ptr_l[0 + (1*16+1*sz+1*16*4)]); 
						ov300 = svmla_x(p32_all, ov300, temp300, coef[1]); ov310 = svmla_x(p32_all, ov310, temp300, coef[0]); 
						//compute using grid[:, 0, :]
						mask_y = svdup_b32(0 < ker_size_y - vy + 2); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						ov000 = svmla_x(p32_all, ov000, iv000, coef[2]); ov010 = svmla_x(p32_all, ov010, iv000, coef[1]); ov020 = svmla_x(p32_all, ov020, iv000, coef[0]); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						ov100 = svmla_x(p32_all, ov100, iv100, coef[2]); ov110 = svmla_x(p32_all, ov110, iv100, coef[1]); ov120 = svmla_x(p32_all, ov120, iv100, coef[0]); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						ov200 = svmla_x(p32_all, ov200, iv200, coef[2]); ov210 = svmla_x(p32_all, ov210, iv200, coef[1]); ov220 = svmla_x(p32_all, ov220, iv200, coef[0]); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						ov300 = svmla_x(p32_all, ov300, iv300, coef[2]); ov310 = svmla_x(p32_all, ov310, iv300, coef[1]); ov320 = svmla_x(p32_all, ov320, iv300, coef[0]); 
						//compute using grid[:, 1, :]
						mask_y = svdup_b32(1 < ker_size_y - vy + 2); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						ov000 = svmla_x(p32_all, ov000, iv010, coef[3]); ov010 = svmla_x(p32_all, ov010, iv010, coef[2]); ov020 = svmla_x(p32_all, ov020, iv010, coef[1]); ov030 = svmla_x(p32_all, ov030, iv010, coef[0]); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						ov100 = svmla_x(p32_all, ov100, iv110, coef[3]); ov110 = svmla_x(p32_all, ov110, iv110, coef[2]); ov120 = svmla_x(p32_all, ov120, iv110, coef[1]); ov130 = svmla_x(p32_all, ov130, iv110, coef[0]); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						ov200 = svmla_x(p32_all, ov200, iv210, coef[3]); ov210 = svmla_x(p32_all, ov210, iv210, coef[2]); ov220 = svmla_x(p32_all, ov220, iv210, coef[1]); ov230 = svmla_x(p32_all, ov230, iv210, coef[0]); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						ov300 = svmla_x(p32_all, ov300, iv310, coef[3]); ov310 = svmla_x(p32_all, ov310, iv310, coef[2]); ov320 = svmla_x(p32_all, ov320, iv310, coef[1]); ov330 = svmla_x(p32_all, ov330, iv310, coef[0]); 
						//compute using grid[:, 2, :]
						mask_y = svdup_b32(2 < ker_size_y - vy + 2); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						ov000 = svmla_x(p32_all, ov000, iv020, coef[4]); ov010 = svmla_x(p32_all, ov010, iv020, coef[3]); ov020 = svmla_x(p32_all, ov020, iv020, coef[2]); ov030 = svmla_x(p32_all, ov030, iv020, coef[1]); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						ov100 = svmla_x(p32_all, ov100, iv120, coef[4]); ov110 = svmla_x(p32_all, ov110, iv120, coef[3]); ov120 = svmla_x(p32_all, ov120, iv120, coef[2]); ov130 = svmla_x(p32_all, ov130, iv120, coef[1]); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						ov200 = svmla_x(p32_all, ov200, iv220, coef[4]); ov210 = svmla_x(p32_all, ov210, iv220, coef[3]); ov220 = svmla_x(p32_all, ov220, iv220, coef[2]); ov230 = svmla_x(p32_all, ov230, iv220, coef[1]); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						ov300 = svmla_x(p32_all, ov300, iv320, coef[4]); ov310 = svmla_x(p32_all, ov310, iv320, coef[3]); ov320 = svmla_x(p32_all, ov320, iv320, coef[2]); ov330 = svmla_x(p32_all, ov330, iv320, coef[1]); 
						//compute using grid[:, 3, :]
						mask_y = svdup_b32(3 < ker_size_y - vy + 2); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						ov010 = svmla_x(p32_all, ov010, iv030, coef[4]); ov020 = svmla_x(p32_all, ov020, iv030, coef[3]); ov030 = svmla_x(p32_all, ov030, iv030, coef[2]); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						ov110 = svmla_x(p32_all, ov110, iv130, coef[4]); ov120 = svmla_x(p32_all, ov120, iv130, coef[3]); ov130 = svmla_x(p32_all, ov130, iv130, coef[2]); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						ov210 = svmla_x(p32_all, ov210, iv230, coef[4]); ov220 = svmla_x(p32_all, ov220, iv230, coef[3]); ov230 = svmla_x(p32_all, ov230, iv230, coef[2]); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						ov310 = svmla_x(p32_all, ov310, iv330, coef[4]); ov320 = svmla_x(p32_all, ov320, iv330, coef[3]); ov330 = svmla_x(p32_all, ov330, iv330, coef[2]); 
						//compute using grid[:, 4, :]
						mask_y = svdup_b32(4 < ker_size_y - vy + 2); 
						mask_z = svdup_b32(0 < ker_size_z - vz); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						mask_xyz = svand_z(p32_all, mask_xy, mask_z); temp000 = svld1(mask_xyz, &ptr_r[0 + 0]); 
						ov020 = svmla_x(p32_all, ov020, temp000, coef[4]); ov030 = svmla_x(p32_all, ov030, temp000, coef[3]); 
						mask_z = svdup_b32(1 < ker_size_z - vz); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						mask_xyz = svand_z(p32_all, mask_xy, mask_z); temp100 = svld1(mask_xyz, &ptr_r[0 + (1*16*4)]); 
						ov120 = svmla_x(p32_all, ov120, temp100, coef[4]); ov130 = svmla_x(p32_all, ov130, temp100, coef[3]); 
						mask_z = svdup_b32(2 < ker_size_z - vz); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						mask_xyz = svand_z(p32_all, mask_xy, mask_z); temp200 = svld1(mask_xyz, &ptr_r[0 + (1*sz)]); 
						ov220 = svmla_x(p32_all, ov220, temp200, coef[4]); ov230 = svmla_x(p32_all, ov230, temp200, coef[3]); 
						mask_z = svdup_b32(3 < ker_size_z - vz); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						mask_xyz = svand_z(p32_all, mask_xy, mask_z); temp300 = svld1(mask_xyz, &ptr_r[0 + (1*sz+1*16*4)]); 
						ov320 = svmla_x(p32_all, ov320, temp300, coef[4]); ov330 = svmla_x(p32_all, ov330, temp300, coef[3]); 
						//compute using grid[:, 5, :]
						mask_y = svdup_b32(5 < ker_size_y - vy + 2); 
						mask_z = svdup_b32(0 < ker_size_z - vz); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						mask_xyz = svand_z(p32_all, mask_xy, mask_z); temp000 = svld1(mask_xyz, &ptr_r[0 + (1*16)]); 
						ov030 = svmla_x(p32_all, ov030, temp000, coef[4]); 
						mask_z = svdup_b32(1 < ker_size_z - vz); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						mask_xyz = svand_z(p32_all, mask_xy, mask_z); temp100 = svld1(mask_xyz, &ptr_r[0 + (1*16+1*16*4)]); 
						ov130 = svmla_x(p32_all, ov130, temp100, coef[4]); 
						mask_z = svdup_b32(2 < ker_size_z - vz); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						mask_xyz = svand_z(p32_all, mask_xy, mask_z); temp200 = svld1(mask_xyz, &ptr_r[0 + (1*16+1*sz)]); 
						ov230 = svmla_x(p32_all, ov230, temp200, coef[4]); 
						mask_z = svdup_b32(3 < ker_size_z - vz); 
						mask_xy = svand_z(p32_all, mask_x_0, mask_y); 
						mask_xyz = svand_z(p32_all, mask_xy, mask_z); temp300 = svld1(mask_xyz, &ptr_r[0 + (1*16+1*sz+1*16*4)]); 
						ov330 = svmla_x(p32_all, ov330, temp300, coef[4]); 
					}
					{
						svfloat32_t temp000,temp100,temp200,temp300,temp010,temp110,temp210,temp310,temp020,temp120,temp220,temp320,temp030,temp130,temp230,temp330; 
						//compute using [-VX:0] and [0:VX]
						//generate vector: [-Radius + 0: VX - Radius + 0]
						temp000 = svext(pv000, iv000, 14); temp010 = svext(pv010, iv010, 14); temp020 = svext(pv020, iv020, 14); temp030 = svext(pv030, iv030, 14); 
						ov000 = svmla_x(p32_all, ov000, temp000, coef[0]); ov010 = svmla_x(p32_all, ov010, temp010, coef[0]); ov020 = svmla_x(p32_all, ov020, temp020, coef[0]); ov030 = svmla_x(p32_all, ov030, temp030, coef[0]); 
						temp100 = svext(pv100, iv100, 14); temp110 = svext(pv110, iv110, 14); temp120 = svext(pv120, iv120, 14); temp130 = svext(pv130, iv130, 14); 
						ov100 = svmla_x(p32_all, ov100, temp100, coef[0]); ov110 = svmla_x(p32_all, ov110, temp110, coef[0]); ov120 = svmla_x(p32_all, ov120, temp120, coef[0]); ov130 = svmla_x(p32_all, ov130, temp130, coef[0]); 
						temp200 = svext(pv200, iv200, 14); temp210 = svext(pv210, iv210, 14); temp220 = svext(pv220, iv220, 14); temp230 = svext(pv230, iv230, 14); 
						ov200 = svmla_x(p32_all, ov200, temp200, coef[0]); ov210 = svmla_x(p32_all, ov210, temp210, coef[0]); ov220 = svmla_x(p32_all, ov220, temp220, coef[0]); ov230 = svmla_x(p32_all, ov230, temp230, coef[0]); 
						temp300 = svext(pv300, iv300, 14); temp310 = svext(pv310, iv310, 14); temp320 = svext(pv320, iv320, 14); temp330 = svext(pv330, iv330, 14); 
						ov300 = svmla_x(p32_all, ov300, temp300, coef[0]); ov310 = svmla_x(p32_all, ov310, temp310, coef[0]); ov320 = svmla_x(p32_all, ov320, temp320, coef[0]); ov330 = svmla_x(p32_all, ov330, temp330, coef[0]); 
						//generate vector: [-Radius + 1: VX - Radius + 1]
						temp000 = svext(pv000, iv000, 15); temp010 = svext(pv010, iv010, 15); temp020 = svext(pv020, iv020, 15); temp030 = svext(pv030, iv030, 15); 
						ov000 = svmla_x(p32_all, ov000, temp000, coef[1]); ov010 = svmla_x(p32_all, ov010, temp010, coef[1]); ov020 = svmla_x(p32_all, ov020, temp020, coef[1]); ov030 = svmla_x(p32_all, ov030, temp030, coef[1]); 
						temp100 = svext(pv100, iv100, 15); temp110 = svext(pv110, iv110, 15); temp120 = svext(pv120, iv120, 15); temp130 = svext(pv130, iv130, 15); 
						ov100 = svmla_x(p32_all, ov100, temp100, coef[1]); ov110 = svmla_x(p32_all, ov110, temp110, coef[1]); ov120 = svmla_x(p32_all, ov120, temp120, coef[1]); ov130 = svmla_x(p32_all, ov130, temp130, coef[1]); 
						temp200 = svext(pv200, iv200, 15); temp210 = svext(pv210, iv210, 15); temp220 = svext(pv220, iv220, 15); temp230 = svext(pv230, iv230, 15); 
						ov200 = svmla_x(p32_all, ov200, temp200, coef[1]); ov210 = svmla_x(p32_all, ov210, temp210, coef[1]); ov220 = svmla_x(p32_all, ov220, temp220, coef[1]); ov230 = svmla_x(p32_all, ov230, temp230, coef[1]); 
						temp300 = svext(pv300, iv300, 15); temp310 = svext(pv310, iv310, 15); temp320 = svext(pv320, iv320, 15); temp330 = svext(pv330, iv330, 15); 
						ov300 = svmla_x(p32_all, ov300, temp300, coef[1]); ov310 = svmla_x(p32_all, ov310, temp310, coef[1]); ov320 = svmla_x(p32_all, ov320, temp320, coef[1]); ov330 = svmla_x(p32_all, ov330, temp330, coef[1]); 
						//compute using [0:VX]
						ov000 = svmla_x(p32_all, ov000, iv000, coef[2]); ov010 = svmla_x(p32_all, ov010, iv010, coef[2]); ov020 = svmla_x(p32_all, ov020, iv020, coef[2]); ov030 = svmla_x(p32_all, ov030, iv030, coef[2]); 
						ov100 = svmla_x(p32_all, ov100, iv100, coef[2]); ov110 = svmla_x(p32_all, ov110, iv110, coef[2]); ov120 = svmla_x(p32_all, ov120, iv120, coef[2]); ov130 = svmla_x(p32_all, ov130, iv130, coef[2]); 
						ov200 = svmla_x(p32_all, ov200, iv200, coef[2]); ov210 = svmla_x(p32_all, ov210, iv210, coef[2]); ov220 = svmla_x(p32_all, ov220, iv220, coef[2]); ov230 = svmla_x(p32_all, ov230, iv230, coef[2]); 
						ov300 = svmla_x(p32_all, ov300, iv300, coef[2]); ov310 = svmla_x(p32_all, ov310, iv310, coef[2]); ov320 = svmla_x(p32_all, ov320, iv320, coef[2]); ov330 = svmla_x(p32_all, ov330, iv330, coef[2]); 
						//compute using [0:VX] and [VX:2VX]
						mask_x_0 = svwhilelt_b32(0, ker_size_x - vx + 2 - 16); 
						mask_z = svdup_b32(0 < ker_size_z - vz); 
						mask_y = svdup_b32(0 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); nv000 = svld1(mask_xyz, &ptr_1[0 + 0]); 
						mask_y = svdup_b32(1 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); nv010 = svld1(mask_xyz, &ptr_1[0 + (1*16)]); 
						mask_y = svdup_b32(2 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); nv020 = svld1(mask_xyz, &ptr_1[0 + (2*16)]); 
						mask_y = svdup_b32(3 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); nv030 = svld1(mask_xyz, &ptr_1[0 + (3*16)]); 
						mask_z = svdup_b32(1 < ker_size_z - vz); 
						mask_y = svdup_b32(0 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); nv100 = svld1(mask_xyz, &ptr_1[0 + (1*16*4)]); 
						mask_y = svdup_b32(1 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); nv110 = svld1(mask_xyz, &ptr_1[0 + (1*16+1*16*4)]); 
						mask_y = svdup_b32(2 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); nv120 = svld1(mask_xyz, &ptr_1[0 + (2*16+1*16*4)]); 
						mask_y = svdup_b32(3 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); nv130 = svld1(mask_xyz, &ptr_1[0 + (3*16+1*16*4)]); 
						mask_z = svdup_b32(2 < ker_size_z - vz); 
						mask_y = svdup_b32(0 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); nv200 = svld1(mask_xyz, &ptr_1[0 + (1*sz)]); 
						mask_y = svdup_b32(1 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); nv210 = svld1(mask_xyz, &ptr_1[0 + (1*16+1*sz)]); 
						mask_y = svdup_b32(2 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); nv220 = svld1(mask_xyz, &ptr_1[0 + (2*16+1*sz)]); 
						mask_y = svdup_b32(3 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); nv230 = svld1(mask_xyz, &ptr_1[0 + (3*16+1*sz)]); 
						mask_z = svdup_b32(3 < ker_size_z - vz); 
						mask_y = svdup_b32(0 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); nv300 = svld1(mask_xyz, &ptr_1[0 + (1*sz+1*16*4)]); 
						mask_y = svdup_b32(1 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); nv310 = svld1(mask_xyz, &ptr_1[0 + (1*16+1*sz+1*16*4)]); 
						mask_y = svdup_b32(2 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); nv320 = svld1(mask_xyz, &ptr_1[0 + (2*16+1*sz+1*16*4)]); 
						mask_y = svdup_b32(3 < ker_size_y - vy + 2); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); nv330 = svld1(mask_xyz, &ptr_1[0 + (3*16+1*sz+1*16*4)]); 
						//generate vector: [0: VX + 0]
						temp000 = svext(iv000, nv000, 1); temp010 = svext(iv010, nv010, 1); temp020 = svext(iv020, nv020, 1); temp030 = svext(iv030, nv030, 1); 
						ov000 = svmla_x(p32_all, ov000, temp000, coef[3]); ov010 = svmla_x(p32_all, ov010, temp010, coef[3]); ov020 = svmla_x(p32_all, ov020, temp020, coef[3]); ov030 = svmla_x(p32_all, ov030, temp030, coef[3]); 
						temp100 = svext(iv100, nv100, 1); temp110 = svext(iv110, nv110, 1); temp120 = svext(iv120, nv120, 1); temp130 = svext(iv130, nv130, 1); 
						ov100 = svmla_x(p32_all, ov100, temp100, coef[3]); ov110 = svmla_x(p32_all, ov110, temp110, coef[3]); ov120 = svmla_x(p32_all, ov120, temp120, coef[3]); ov130 = svmla_x(p32_all, ov130, temp130, coef[3]); 
						temp200 = svext(iv200, nv200, 1); temp210 = svext(iv210, nv210, 1); temp220 = svext(iv220, nv220, 1); temp230 = svext(iv230, nv230, 1); 
						ov200 = svmla_x(p32_all, ov200, temp200, coef[3]); ov210 = svmla_x(p32_all, ov210, temp210, coef[3]); ov220 = svmla_x(p32_all, ov220, temp220, coef[3]); ov230 = svmla_x(p32_all, ov230, temp230, coef[3]); 
						temp300 = svext(iv300, nv300, 1); temp310 = svext(iv310, nv310, 1); temp320 = svext(iv320, nv320, 1); temp330 = svext(iv330, nv330, 1); 
						ov300 = svmla_x(p32_all, ov300, temp300, coef[3]); ov310 = svmla_x(p32_all, ov310, temp310, coef[3]); ov320 = svmla_x(p32_all, ov320, temp320, coef[3]); ov330 = svmla_x(p32_all, ov330, temp330, coef[3]); 
						//generate vector: [1: VX + 1]
						temp000 = svext(iv000, nv000, 2); temp010 = svext(iv010, nv010, 2); temp020 = svext(iv020, nv020, 2); temp030 = svext(iv030, nv030, 2); 
						ov000 = svmla_x(p32_all, ov000, temp000, coef[4]); ov010 = svmla_x(p32_all, ov010, temp010, coef[4]); ov020 = svmla_x(p32_all, ov020, temp020, coef[4]); ov030 = svmla_x(p32_all, ov030, temp030, coef[4]); 
						temp100 = svext(iv100, nv100, 2); temp110 = svext(iv110, nv110, 2); temp120 = svext(iv120, nv120, 2); temp130 = svext(iv130, nv130, 2); 
						ov100 = svmla_x(p32_all, ov100, temp100, coef[4]); ov110 = svmla_x(p32_all, ov110, temp110, coef[4]); ov120 = svmla_x(p32_all, ov120, temp120, coef[4]); ov130 = svmla_x(p32_all, ov130, temp130, coef[4]); 
						temp200 = svext(iv200, nv200, 2); temp210 = svext(iv210, nv210, 2); temp220 = svext(iv220, nv220, 2); temp230 = svext(iv230, nv230, 2); 
						ov200 = svmla_x(p32_all, ov200, temp200, coef[4]); ov210 = svmla_x(p32_all, ov210, temp210, coef[4]); ov220 = svmla_x(p32_all, ov220, temp220, coef[4]); ov230 = svmla_x(p32_all, ov230, temp230, coef[4]); 
						temp300 = svext(iv300, nv300, 2); temp310 = svext(iv310, nv310, 2); temp320 = svext(iv320, nv320, 2); temp330 = svext(iv330, nv330, 2); 
						ov300 = svmla_x(p32_all, ov300, temp300, coef[4]); ov310 = svmla_x(p32_all, ov310, temp310, coef[4]); ov320 = svmla_x(p32_all, ov320, temp320, coef[4]); ov330 = svmla_x(p32_all, ov330, temp330, coef[4]); 
					}
					mask_x_0 = svwhilelt_b32(0, ker_size_x - vx); 
					mask_z = svdup_b32(0 < ker_size_z - vz); 
					mask_y = svdup_b32(0 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); svst1(mask_xyz, &ptr_dst[0 + 0], ov000); 
					mask_y = svdup_b32(1 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); svst1(mask_xyz, &ptr_dst[0 + (1*16)], ov010); 
					mask_y = svdup_b32(2 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); svst1(mask_xyz, &ptr_dst[0 + (2*16)], ov020); 
					mask_y = svdup_b32(3 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); svst1(mask_xyz, &ptr_dst[0 + (3*16)], ov030); 
					mask_z = svdup_b32(1 < ker_size_z - vz); 
					mask_y = svdup_b32(0 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); svst1(mask_xyz, &ptr_dst[0 + (1*16*4)], ov100); 
					mask_y = svdup_b32(1 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); svst1(mask_xyz, &ptr_dst[0 + (1*16+1*16*4)], ov110); 
					mask_y = svdup_b32(2 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); svst1(mask_xyz, &ptr_dst[0 + (2*16+1*16*4)], ov120); 
					mask_y = svdup_b32(3 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); svst1(mask_xyz, &ptr_dst[0 + (3*16+1*16*4)], ov130); 
					mask_z = svdup_b32(2 < ker_size_z - vz); 
					mask_y = svdup_b32(0 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); svst1(mask_xyz, &ptr_dst[0 + (1*dz)], ov200); 
					mask_y = svdup_b32(1 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); svst1(mask_xyz, &ptr_dst[0 + (1*16+1*dz)], ov210); 
					mask_y = svdup_b32(2 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); svst1(mask_xyz, &ptr_dst[0 + (2*16+1*dz)], ov220); 
					mask_y = svdup_b32(3 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); svst1(mask_xyz, &ptr_dst[0 + (3*16+1*dz)], ov230); 
					mask_z = svdup_b32(3 < ker_size_z - vz); 
					mask_y = svdup_b32(0 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); svst1(mask_xyz, &ptr_dst[0 + (1*dz+1*16*4)], ov300); 
					mask_y = svdup_b32(1 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); svst1(mask_xyz, &ptr_dst[0 + (1*16+1*dz+1*16*4)], ov310); 
					mask_y = svdup_b32(2 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); svst1(mask_xyz, &ptr_dst[0 + (2*16+1*dz+1*16*4)], ov320); 
					mask_y = svdup_b32(3 < ker_size_y - vy); mask_yz = svand_z(p32_all, mask_y, mask_z); mask_xyz = svand_z(p32_all, mask_yz, mask_x_0); svst1(mask_xyz, &ptr_dst[0 + (3*16+1*dz+1*16*4)], ov330); 
					pv000 = iv000; pv010 = iv010; pv020 = iv020; pv030 = iv030; 
					pv100 = iv100; pv110 = iv110; pv120 = iv120; pv130 = iv130; 
					pv200 = iv200; pv210 = iv210; pv220 = iv220; pv230 = iv230; 
					pv300 = iv300; pv310 = iv310; pv320 = iv320; pv330 = iv330; 
					iv000 = nv000; iv010 = nv010; iv020 = nv020; iv030 = nv030; 
					iv100 = nv100; iv110 = nv110; iv120 = nv120; iv130 = nv130; 
					iv200 = nv200; iv210 = nv210; iv220 = nv220; iv230 = nv230; 
					iv300 = nv300; iv310 = nv310; iv320 = nv320; iv330 = nv330; 
					ptr_src += (1*16*4*2); ptr_l += (1*16*4*2); ptr_r += (1*16*4*2); ptr_dst += (1*16*4*2);
				}
			}
		}
	}
}
