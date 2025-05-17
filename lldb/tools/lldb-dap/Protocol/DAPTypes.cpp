#include "Protocol/DAPTypes.h"
// #include "llvm/Support/JSON.h"

using namespace llvm;

namespace lldb_dap::protocol {

bool fromJSON(const llvm::json::Value &Params, SourceLLDBData &SLD, llvm::json::Path P) {
  json::ObjectMapper O(Params, P);
  return O && O.map("module_path", SLD.module_path) && O.map("symbol_mangled_name", SLD.symbol_mangled_name);
}

llvm::json::Value toJSON(const SourceLLDBData &SLD) {
  json::Object result;
  if (SLD.module_path)
    result.insert({"module_path", SLD.module_path});
  if (SLD.symbol_mangled_name)
    result.insert({"symbol_mangled_name", SLD.symbol_mangled_name});
  return result;
}

} // namespace lldb_dap::protocol