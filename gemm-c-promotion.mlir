!TA = tensor<32x32xf16>
!TB = tensor<32x32xf16>
!TC = tensor<32x32xf32>

func.func @matmul_16_16_32(%arg0: !TA, %arg1: !TB, %arg2: !TC) -> !TC {
  %0 = linalg.matmul ins(%arg0, %arg1 : !TA, !TB) outs(%arg2 : !TC) -> !TC
  return %0 : !TC
}
