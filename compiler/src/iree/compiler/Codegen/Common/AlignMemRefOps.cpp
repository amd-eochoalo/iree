// Copyright 2025 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"

#include "Passes.h"
namespace mlir {
#define GEN_PASS_DEF_ALIGNMEMREFOPSPASS
#include "iree/compiler/Codegen/Common/Passes.h.inc"
} // namespace mlir

using namespace mlir;

namespace {

template <typename T>
struct AlignMemrefOpPatternBase : public OpRewritePattern<T> {
  using OpRewritePattern<T>::OpRewritePattern;
  LogicalResult matchAndRewrite(T op,
                                PatternRewriter &rewriter) const override {
    op.setAlignment(128);
    return failure();
  }
};

struct AlignMemrefLoad : public AlignMemrefOpPatternBase<memref::LoadOp> {
  using AlignMemrefOpPatternBase<memref::LoadOp>::AlignMemrefOpPatternBase;
};

struct AlignMemrefStore : public AlignMemrefOpPatternBase<memref::StoreOp> {
  using AlignMemrefOpPatternBase<memref::StoreOp>::AlignMemrefOpPatternBase;
};

struct AlignMemRefOpsPass
    : public impl::AlignMemRefOpsPassBase<AlignMemRefOpsPass> {
  using impl::AlignMemRefOpsPassBase<
      AlignMemRefOpsPass>::AlignMemRefOpsPassBase;

  void runOnOperation() override {
    RewritePatternSet patterns(&getContext());

    mlir::iree_compiler::populateAlignMemRefOpsPatterns(patterns);

    if (failed(applyPatternsGreedily(getOperation(), std::move(patterns))))
      return signalPassFailure();
  }
};

} // namespace

namespace mlir::iree_compiler {
void populateAlignMemRefOpsPatterns(RewritePatternSet &patterns) {
  patterns.insert<AlignMemrefLoad, AlignMemrefStore>(patterns.getContext());
}

std::unique_ptr<Pass> createAlignMemRefOpsPass() {
  return std::make_unique<AlignMemRefOpsPass>();
}
} // namespace mlir::iree_compiler
