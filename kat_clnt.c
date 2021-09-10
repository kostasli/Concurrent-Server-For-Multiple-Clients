/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "kat.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

float *
average_1(Y_arr *argp, CLIENT *clnt)
{
	static float clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, average,
		(xdrproc_t) xdr_Y_arr, (caddr_t) argp,
		(xdrproc_t) xdr_float, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

max_min *
maxmin_1(Y_arr *argp, CLIENT *clnt)
{
	static max_min clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, maxmin,
		(xdrproc_t) xdr_Y_arr, (caddr_t) argp,
		(xdrproc_t) xdr_max_min, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

aY *
product_1(a_mul_Y *argp, CLIENT *clnt)
{
	static aY clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, product,
		(xdrproc_t) xdr_a_mul_Y, (caddr_t) argp,
		(xdrproc_t) xdr_aY, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
