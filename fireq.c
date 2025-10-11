#include <arrayfire.h>
#include "k.h"
#include <stdio.h>

af_array K_to_array(K x){
	af_array r = 0;
	P(xt!=KI && xt!=KJ && xt!=KE && xt!=KF,r);
	dim_t dims[1] = {xn};
	const V *data = NULL;
	af_dtype t;
	switch(xt){
		case KI:t=s32;data=kI(x);break;
		case KJ:t=s64;data=kJ(x);break;
		case KE:t=f32;data=kE(x);break;
		case KF:t=f64;data=kF(x);break;
		default:
			R r;
	}
	af_create_array(&r, data, 1, dims, t);
	R r;
}

K array_to_K(af_array a){
	af_dtype t;
	af_get_type(&t, a);
	dim_t d0, d1, d2, d3;
	af_get_dims(&d0, &d1, &d2, &d3, a);
	J kt;
	K r;
	V *data = NULL;
	switch (t) {
		case s32:kt=KI;r=ktn(kt,d0);data=kI(r);break;
		case s64:kt=KJ;r=ktn(kt,d0);data=kJ(r);break;
		case f32:kt=KE;r=ktn(kt,d0);data=kE(r);break;
		case f64:kt=KF;r=ktn(kt,d0);data=kF(r);break;
		default: 
			R (K)0;
	}	
	af_get_data_ptr(data, a);
	R r;
}

K1(sum){
	af_array a = K_to_array(x);
	P(!a, krr("type"));
	af_array s = 0;
	af_sum(&s, a, 0);
	K r = array_to_K(s);
	af_release_array(a);
	af_release_array(s);
	R r;
}

af_array K_to_matrix(K x){
	af_array r = 0;
	P(xt!=0,r);
	P(xx->t!=KI && xx->t!=KJ && xx->t!=KE && xx->t!=KF,r);
	dim_t dims[2] = {xx->j, xn};
	const V *data = NULL;
	af_dtype t;
	K y;
	switch(xx->t){
		case KI:t=s32;y=ktn(KI,0);DO(xn,jv(&y,kK(x)[i]));data=kI(y);break;
		case KJ:t=s64;y=ktn(KJ,0);DO(xn,jv(&y,kK(x)[i]));data=kJ(y);break;
		case KE:t=f32;y=ktn(KE,0);DO(xn,jv(&y,kK(x)[i]));data=kE(y);break;
		case KF:t=f64;y=ktn(KF,0);DO(xn,jv(&y,kK(x)[i]));data=kF(y);break;
		default:
			R r;
	}
	af_create_array(&r, data, 2, dims, t);
	af_array r2 = 0;
	af_transpose(&r2, r, false);
	af_release_array(r);
	R r2;
}

K matrix_to_K(af_array a){
	af_dtype t;
	af_get_type(&t, a);
	dim_t d0, d1, d2, d3;
	af_get_dims(&d0, &d1, &d2, &d3, a);
	J kt;
	af_array b = 0;
	af_transpose(&b, a, false);
	V *data = NULL;
	K y;
	switch (t) {
		case s32:kt=KI;y=ktn(kt,d0*d1);data=kI(y);break;
		case s64:kt=KJ;y=ktn(kt,d0*d1);data=kJ(y);break;
		case f32:kt=KE;y=ktn(kt,d0*d1);data=kE(y);break;
		case f64:kt=KF;y=ktn(kt,d0*d1);data=kF(y);break;
		default: 
			R (K)0;
	}	
	af_get_data_ptr(data, b);
	K r = k(0, "{x cut y}", kj(d1), r1(y), (K)0);
	R r;
}

K1(noop){
	af_array a = K_to_matrix(x);
	K r = matrix_to_K(a);
	af_release_array(a);
	R r;
}

K2(mmu2){
	af_array a = K_to_matrix(x);
	af_array b = K_to_matrix(y);
	af_array c = 0;

	af_matmul(&c, a, b, AF_MAT_NONE, AF_MAT_NONE);
	K r = matrix_to_K(c);

	af_release_array(a);
	af_release_array(b);
	af_release_array(c);
	R r;
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
	K mat = ktn(0, rows);
	for (J r = 0; r < rows; r++) {
	    K row = ktn(KF, cols);
	    for (J c = 0; c < cols; c++) {
		kF(row)[c] = kF(h_C)[c*rows + r];  // column-major index
	    }
	    kK(mat)[r] = row;
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
	_(sum,1)_(mmuc,6)_(noop,1)_(mmu2,2)
	af_info(); // Initializes and prints info
	R xD(n,f);
}
