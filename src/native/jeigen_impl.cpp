#include "jeigen.h"
#include "jeigen_JeigenJna_Jeigen.h"

template<typename T>
struct JArrayHelper{
};

template<>
struct JArrayHelper<double>{
  typedef jdoubleArray type;
};


template<>
struct JArrayHelper<int>{
  typedef jintArray type;
};

template <typename T>
struct JConverter {
public:
  JNIEnv* env;
  typename JArrayHelper<T>::type arr;
  T* actualArr;
  JConverter(JNIEnv *a_env, typename JArrayHelper<T>::type a_arr) :
    env(a_env),
    arr(a_arr),
    actualArr((T*)env->GetPrimitiveArrayCritical(arr, NULL))
  {
  }

  operator T*()
  {
    return actualArr;
  }

  ~JConverter()
  {
    env->ReleasePrimitiveArrayCritical(arr, actualArr, 0);
  }
};

typedef JConverter<double>  JDoubleConverter;
typedef JConverter<int>  JIntConverter;


JNIEXPORT void JNICALL Java_jeigen_JeigenJna_00024Jeigen_init
  (JNIEnv *env, jclass myself)
{
  init();

}

/*
 * Class:     jeigen_JeigenJna_Jeigen
 * Method:    dense_multiply
 * Signature: (III[D[D[D)V
 */
JNIEXPORT void JNICALL Java_jeigen_JeigenJna_00024Jeigen_dense_1multiply
  (JNIEnv *env, jclass myself, jint rows, jint middle, jint cols, jdoubleArray first, jdoubleArray second, jdoubleArray result)
{
  dense_multiply(rows,middle,cols, JDoubleConverter(env,first), JDoubleConverter(env,second), JDoubleConverter(env,result));
}

/*
 * Class:     jeigen_JeigenJna_Jeigen
 * Method:    sparse_multiply
 * Signature: (IIIII)I
 */
JNIEXPORT jint JNICALL Java_jeigen_JeigenJna_00024Jeigen_sparse_1multiply
  (JNIEnv *env, jclass myself, jint rows, jint middle, jint cols, jint oneHandle, jint twoHandle)
{
  return sparse_multiply(rows, middle, cols, oneHandle,twoHandle);
}

/*
 * Class:     jeigen_JeigenJna_Jeigen
 * Method:    sparse_dense_multiply
 * Signature: (IIII[D[D)V
 */
JNIEXPORT void JNICALL Java_jeigen_JeigenJna_00024Jeigen_sparse_1dense_1multiply
  (JNIEnv * env, jclass myself, jint rows, jint middle, jint cols, jint oneHandle, jdoubleArray second, jdoubleArray result)
  {
    sparse_dense_multiply(rows, middle, cols, oneHandle, JDoubleConverter(env,second), JDoubleConverter(env,result));
  }
/*
 * Class:     jeigen_JeigenJna_Jeigen
 * Method:    dense_sparse_multiply
 * Signature: (III[DI[D)V
 */
JNIEXPORT void JNICALL Java_jeigen_JeigenJna_00024Jeigen_dense_1sparse_1multiply
  (JNIEnv *env, jclass myself, jint rows, jint middle, jint cols, jdoubleArray first, jint twoHandle, jdoubleArray result)
  {
    dense_sparse_multiply(rows, middle, cols, JDoubleConverter(env,first), twoHandle, JDoubleConverter(env,result));
  }

/*
 * Class:     jeigen_JeigenJna_Jeigen
 * Method:    svd_dense
 * Signature: (II[D[D[D[D)V
 */
JNIEXPORT void JNICALL Java_jeigen_JeigenJna_00024Jeigen_svd_1dense
  (JNIEnv *env, jclass myself, jint numrows, jint numcols, jdoubleArray in, jdoubleArray u, jdoubleArray s, jdoubleArray v)
{
  svd_dense(numrows,numcols, JDoubleConverter(env,in), JDoubleConverter(env,u), JDoubleConverter(env,s), JDoubleConverter(env,v) );
}
/*
 * Class:     jeigen_JeigenJna_Jeigen
 * Method:    jeigen_exp
 * Signature: (I[D[D)V
 */
JNIEXPORT void JNICALL Java_jeigen_JeigenJna_00024Jeigen_jeigen_1exp
  (JNIEnv *env, jclass myself, jint n, jdoubleArray in, jdoubleArray result)
  {
    jeigen_exp( n, JDoubleConverter(env,in), JDoubleConverter(env,result));
  }

/*
 * Class:     jeigen_JeigenJna_Jeigen
 * Method:    jeigen_log
 * Signature: (I[D[D)V
 */
JNIEXPORT void JNICALL Java_jeigen_JeigenJna_00024Jeigen_jeigen_1log
  (JNIEnv *env, jclass myself, jint n, jdoubleArray in, jdoubleArray result)
  {
    jeigen_log( n, JDoubleConverter(env,in), JDoubleConverter(env,result));
  }

/*
 * Class:     jeigen_JeigenJna_Jeigen
 * Method:    ldlt_solve
 * Signature: (III[D[D[D)V
 */
JNIEXPORT void JNICALL Java_jeigen_JeigenJna_00024Jeigen_ldlt_1solve
  (JNIEnv *env, jclass myself, jint arow, jint acols, jint bcols, jdoubleArray avalues, jdoubleArray bvalues, jdoubleArray xvalues)
  {
    ldlt_solve(arow,acols, bcols, JDoubleConverter(env,avalues), JDoubleConverter(env,bvalues), JDoubleConverter(env,xvalues));
  }

/*
 * Class:     jeigen_JeigenJna_Jeigen
 * Method:    fullpivhouseholderqr_solve
 * Signature: (III[D[D[D)V
 */
JNIEXPORT void JNICALL Java_jeigen_JeigenJna_00024Jeigen_fullpivhouseholderqr_1solve
  (JNIEnv *env, jclass myself, jint arow, jint acols, jint bcols, jdoubleArray avalues, jdoubleArray bvalues, jdoubleArray xvalues)
  {
    fullpivhouseholderqr_solve(arow, acols, bcols, JDoubleConverter(env,avalues), JDoubleConverter(env,bvalues), JDoubleConverter(env,xvalues) );
  }

/*
 * Class:     jeigen_JeigenJna_Jeigen
 * Method:    allocateSparseMatrix
 * Signature: (III[I[I[D)I
 */
JNIEXPORT jint JNICALL Java_jeigen_JeigenJna_00024Jeigen_allocateSparseMatrix
  (JNIEnv *env, jclass myself, jint numEntries, jint numRows, jint numCols, jintArray rows, jintArray cols, jdoubleArray values)
{
  return allocateSparseMatrix( numEntries, numRows, numCols, JIntConverter(env,rows), JIntConverter(env,cols), JDoubleConverter(env,values) );
}
/*
 * Class:     jeigen_JeigenJna_Jeigen
 * Method:    getSparseMatrixStats
 * Signature: (I[I)V
 */
JNIEXPORT void JNICALL Java_jeigen_JeigenJna_00024Jeigen_getSparseMatrixStats
  (JNIEnv *env, jclass myself, jint handle, jintArray stats)
  {
    getSparseMatrixStats(handle, JIntConverter(env,stats));
  }

/*
 * Class:     jeigen_JeigenJna_Jeigen
 * Method:    getSparseMatrix
 * Signature: (I[I[I[D)V
 */
JNIEXPORT void JNICALL Java_jeigen_JeigenJna_00024Jeigen_getSparseMatrix
  (JNIEnv *env, jclass myself, jint handle, jintArray rows, jintArray cols, jdoubleArray values)
  {
    getSparseMatrix( handle, JIntConverter(env,rows), JIntConverter(env,cols), JDoubleConverter(env,values));
  }

/*
 * Class:     jeigen_JeigenJna_Jeigen
 * Method:    freeSparseMatrix
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_jeigen_JeigenJna_00024Jeigen_freeSparseMatrix
  (JNIEnv *env, jclass myself, jint handle)
  {
    freeSparseMatrix(handle);
  }

/*
 * Class:     jeigen_JeigenJna_Jeigen
 * Method:    dense_dummy_op1
 * Signature: (II[D[D)V
 */
JNIEXPORT void JNICALL Java_jeigen_JeigenJna_00024Jeigen_dense_1dummy_1op1
  (JNIEnv *env, jclass myself, jint rows, jint cols, jdoubleArray one, jdoubleArray result)
  {
    dense_dummy_op1(rows, cols, JDoubleConverter(env,one), JDoubleConverter(env,result) );
  }

/*
 * Class:     jeigen_JeigenJna_Jeigen
 * Method:    dense_dummy_op2
 * Signature: (III[D[D[D)V
 */
JNIEXPORT void JNICALL Java_jeigen_JeigenJna_00024Jeigen_dense_1dummy_1op2
  (JNIEnv *env, jclass myself, jint rows, jint middle, jint cols, jdoubleArray one, jdoubleArray two, jdoubleArray result)
  {
    dense_dummy_op2(rows,middle,cols, JDoubleConverter(env,one), JDoubleConverter(env,two), JDoubleConverter(env,result));
  }

/*
 * Class:     jeigen_JeigenJna_Jeigen
 * Method:    sparse_dummy_op2
 * Signature: (IIIIII)I
 */
JNIEXPORT jint JNICALL Java_jeigen_JeigenJna_00024Jeigen_sparse_1dummy_1op2
  (JNIEnv *env, jclass myself, jint rows, jint middle, jint cols, jint oneHandle, jint twoHandle, jint numResultElements)
  {
    return sparse_dummy_multiply( rows, middle, cols, oneHandle, twoHandle, numResultElements );
  }
