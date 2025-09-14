#include <arrayfire.h>
#include "k.h"

K1(sum){
	P(xt!=KF,krr("type"));
	af_array d_arr = 0, d_sum = 0;
	dim_t dims[1] = {xn};
	af_create_array(&d_arr, kF(x), 1, dims, f64);
	af_sum(&d_sum, d_arr, 0);
	F sum = 0.0;
	af_get_scalar(&sum, d_sum);
	af_release_array(d_sum);
	af_release_array(d_arr);
	R kf(sum);
}

K mmuc(K x, K y, K dxr, K dxc, K dyr, K dyc){
	P(xt!=KF||y->t!=KF||dxr->t!=-KJ||dxc->t!=-KJ||dyr->t!=-KJ||dyc->t!=-KJ,krr("type"));
	dim_t dimsx[2] = {dxr->j, dxc->j};
	dim_t dimsy[2] = {dyr->j, dyc->j};
	af_array d_A = 0, d_B = 0, d_C = 0;
	af_create_array(&d_A, kF(x), 2, dimsx, f64);
	af_create_array(&d_B, kF(y), 2, dimsy, f64);
	af_matmul(&d_C, d_A, d_B, AF_MAT_NONE, AF_MAT_NONE);
	dim_t d0, d1, d2, d3;
	af_get_dims(&d0, &d1, &d2, &d3, d_C);
	J rows = d0, cols = d1;
	J num_elements = d0 * d1;
	K h_C = ktn(KF, num_elements);
	af_get_data_ptr(kF(h_C), d_C);
	K mat = ktn(0, cols);
	for (J c = 0; c < cols; c++) {
		K col = ktn(KF, rows);
		for (J r = 0; r < rows; r++) {
		    kF(col)[r] = kF(h_C)[c*rows + r];
		}
		kK(mat)[c] = col;
	}
	r0(h_C);
	af_release_array(d_A);
	af_release_array(d_B);
	af_release_array(d_C);
	R mat;
}

K init() {
	K n=ktn(KS, 0);
	K f=ktn(0,0);
	#define _(s,a) js(&n,ss(#s));jk(&f,dl((V*)s,a));
	_(sum,1)_(mmuc,6)
	af_info(); // Initializes and prints info
	R xD(n,f);
}
