!TA = tensor<32x32xf16>
!TB = tensor<32x32xf16>
!TC = tensor<32x32xf32>

#translation = #iree_codegen.translation_info<pipeline = LLVMGPUTileAndFuse workgroup_size = [128, 128, 1] subgroup_size = 32 >

func.func @matmul_16_16_32(%arg0: !TA, %arg1: !TB, %arg2: !TC) -> !TC attributes {translation_info = #translation} {
  %0 = linalg.matmul ins(%arg0, %arg1 : !TA, !TB) outs(%arg2 : !TC) -> !TC
  return %0 : !TC
}
