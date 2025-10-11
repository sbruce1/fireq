#include <arrayfire.h>
#include "k.h"
#include <stdio.h>

// 1D Arrays

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

// 2D Matrix
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

// Functions
#define F1(NAME, ...) \
K1(k##NAME){\
    af_array a = K_to_array(x); \
    P(!a, krr("type")); \
    af_array s = 0; \
    af_##NAME(&s, a __VA_OPT__(, __VA_ARGS__)); \
    K r = array_to_K(s); \
    af_release_array(a); \
    af_release_array(s); \
    R r;\
};

#define F1R(NAME, NAME2, ...) \
K1(NAME2){\
    af_array a = K_to_array(x); \
    P(!a, krr("type")); \
    af_array s = 0; \
    af_##NAME(&s, a __VA_OPT__(, __VA_ARGS__)); \
    K r = array_to_K(s); \
    af_release_array(a); \
    af_release_array(s); \
    R r;\
};

F1(abs)
F1(accum, 0)
F1(acos)
// approx1
// approx2
F1(asin)
F1(atan)
F1(cos)
// cov
F1(exp)
F1(log)
F1(log10)
F1(log2)
// lu
F1(max, 0)
F1(mean, 0)
F1(median, 0)
F1(min, 0)
// mod
// nearestNeighbour
// pow
// pow2
F1(product,0)
// setintersect
// setunion
F1(sin)
// solve

// solveLu
F1R(sort, kdesc, 0, 0);
F1R(sort, kasc, 0, 1);
// F1R(sort_index, xdesc, 0, 0) // later 
// F1R(sort_index, xdesc, 0, 0)
F1(sqrt)
F1R(stdev_v2, kdev, 0, 0)
F1(sum, 0)
F1(tan)

K2(ksolve){
	af_array a = K_to_matrix(x);
	P(!a, krr("type"));
	af_array b = K_to_matrix(y);
	P(!b, krr("type"));
	af_array c = 0;

	af_solve(&c, a, b, AF_MAT_NONE);
	K r = matrix_to_K(c);

	af_release_array(a);
	af_release_array(b);
	af_release_array(c);
	R r;
 }

K2(kmmu){
	af_array a = K_to_matrix(x);
	P(!a, krr("type"));
	af_array b = K_to_matrix(y);
	P(!b, krr("type"));
	af_array c = 0;

	af_matmul(&c, a, b, AF_MAT_NONE, AF_MAT_NONE);
	K r = matrix_to_K(c);

	af_release_array(a);
	af_release_array(b);
	af_release_array(c);
	R r;
 }


K init() {
	K n=ktn(KS, 0);
	K f=ktn(0,0);
	#define _(s,a) js(&n,ss(#s));jk(&f,dl((V*)s,a));
	_(kabs, 1)
	_(kaccum, 1)
	_(kacos, 1)
	_(kasin, 1)
	_(katan, 1)
	_(kcos, 1)
	_(kexp, 1)
	_(klog, 1)
	_(klog10, 1)
	_(klog2, 1)
	_(kmax, 1)
	_(kmean, 1)
	_(kmedian, 1)
	_(kmin, 1)
	_(kproduct, 1)
	_(ksin, 1)
	_(kdesc, 1)
	_(kasc, 1)
	_(ksqrt, 1)
	_(kdev, 1)
	_(ksum,1)
	_(ktan, 1)
	_(ksolve, 2)
	_(kmmu,2)
	af_info(); // Initializes and prints info
	R xD(n,f);
}
