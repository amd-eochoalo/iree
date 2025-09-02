// Copyright 2025 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "mlir/Pass/Pass.h"

#include "Passes.h"
namespace mlir {
#define GEN_PASS_DEF_ALIGNMEMREFOPSPASS
#include "iree/compiler/Codegen/Common/Passes.h.inc"
} // namespace mlir

using namespace mlir;

namespace {

struct AlignMemRefOpsPass
    : public impl::AlignMemRefOpsPassBase<AlignMemRefOpsPass> {
  using impl::AlignMemRefOpsPassBase<
      AlignMemRefOpsPass>::AlignMemRefOpsPassBase;

  void runOnOperation() override {}
};

} // namespace

namespace mlir::iree_compiler {
void populateAlignMemRefOpsPatterns(RewritePatternSet &patterns) {}

std::unique_ptr<Pass> createAlignMemRefOpsPass() {
  return std::make_unique<AlignMemRefOpsPass>();
}
} // namespace mlir::iree_compiler
