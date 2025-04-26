//===-- SetExceptionBreakpointsRequestHandler.cpp -------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "DAP.h"
#include "EventHelper.h"
#include "JSONUtils.h"
#include "RequestHandler.h"
#include <set>

namespace lldb_dap {

/// The request configures the debugger’s response to thrown exceptions. Each of
/// the `filters`, `filterOptions`, and `exceptionOptions` in the request are
/// independent configurations to a debug adapter indicating a kind of exception
/// to catch. An exception thrown in a program should result in a stopped event
/// from the debug adapter (with reason exception) if any of the configured
/// filters match. Clients should only call this request if the corresponding
/// capability exceptionBreakpointFilters returns one or more filters.
llvm::Expected<protocol::SetExceptionBreakpointsResponseBody>
SetExceptionBreakpointsRequestHandler::Run(
    const protocol::SetExceptionBreakpointsArguments &args) const {
  std::vector<protocol::Breakpoint> response_breakpoints;
  // Keep a list of any exception breakpoint filter names that weren't set
  // so we can clear any exception breakpoints if needed.
  std::set<llvm::StringRef> unset_filters;
  for (const auto &bp : *dap.exception_breakpoints)
    unset_filters.insert(bp.GetFilter());

  for (const auto &value : args.filters) {
    const auto filter = GetAsString(value);
    auto *exc_bp = dap.GetExceptionBreakpoint(std::string(filter));
    if (exc_bp) {
      exc_bp->SetBreakpoint();
      unset_filters.erase(std::string(filter));
    }
  }
  for (const auto &filter : unset_filters) {
    auto *exc_bp = dap.GetExceptionBreakpoint(filter);
    if (exc_bp)
      exc_bp->ClearBreakpoint();
  }

  return protocol::SetExceptionBreakpointsResponseBody{
      std::move(response_breakpoints)};
}

} // namespace lldb_dap
