//===-- ProtocolTypes.h ---------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains custom DAP types used in the protocol.
//
// Each struct has a toJSON and fromJSON function, that converts between
// the struct and a JSON representation. (See JSON.h)
//
//===----------------------------------------------------------------------===//

#ifndef LLDB_TOOLS_LLDB_DAP_PROTOCOL_DAP_TYPES_H
#define LLDB_TOOLS_LLDB_DAP_PROTOCOL_DAP_TYPES_H

#include "llvm/Support/JSON.h"
#include <optional>
#include <string>

namespace lldb_dap::protocol {

/// Custom source data used by lldb-dap.
/// This data should help lldb-dap identify sources correctly across different sessions.
struct SourceLLDBData {
  /// The source module path
  std::optional<std::string> module_path;

  /// The symbol unique name
  std::optional<std::string> symbol_mangled_name;
};
bool fromJSON(const llvm::json::Value &, SourceLLDBData &, llvm::json::Path);
llvm::json::Value toJSON(const SourceLLDBData &);

} // namespace lldb_dap::protocol

#endif
