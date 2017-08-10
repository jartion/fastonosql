/*  Copyright (C) 2014-2017 FastoGT. All right reserved.

    This file is part of FastoNoSQL.

    FastoNoSQL is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    FastoNoSQL is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FastoNoSQL.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <stddef.h>  // for size_t
#include <stdint.h>  // for uint64_t

#include <string>  // for string
#include <vector>  // for vector

#include <common/error.h>   // for Error
#include <common/macros.h>  // for WARN_UNUSED_RESULT

#include "core/connection_types.h"         // for connectionTypes::UPSCALEDB
#include "core/db_key.h"                   // for NDbKValue, NKey, NKeys
#include "core/internal/cdb_connection.h"  // for CDBConnection

#include "core/db/upscaledb/config.h"
#include "core/db/upscaledb/server_info.h"  // for ServerInfo

namespace fastonosql {
namespace core {
class CDBConnectionClient;
}
}  // namespace fastonosql
namespace fastonosql {
namespace core {
class IDataBaseInfo;
}
}  // namespace fastonosql
namespace fastonosql {
namespace core {
namespace upscaledb {
struct upscaledb;
}
}  // namespace core
}  // namespace fastonosql

namespace fastonosql {
namespace core {
namespace upscaledb {

typedef upscaledb NativeConnection;

common::Error CreateConnection(const Config& config, NativeConnection** context);
common::Error TestConnection(const Config& config);

class DBConnection : public core::internal::CDBConnection<NativeConnection, Config, UPSCALEDB> {
 public:
  typedef core::internal::CDBConnection<NativeConnection, Config, UPSCALEDB> base_class;
  explicit DBConnection(CDBConnectionClient* client);

  common::Error Connect(const config_t& config);

  std::string CurrentDBName() const;
  common::Error Info(const std::string& args, ServerInfo::Stats* statsout) WARN_UNUSED_RESULT;

 private:
  common::Error SetInner(key_t key, const std::string& value) WARN_UNUSED_RESULT;
  common::Error GetInner(key_t key, std::string* ret_val) WARN_UNUSED_RESULT;
  common::Error DelInner(key_t key) WARN_UNUSED_RESULT;

  virtual common::Error ScanImpl(uint64_t cursor_in,
                                 const std::string& pattern,
                                 uint64_t count_keys,
                                 std::vector<std::string>* keys_out,
                                 uint64_t* cursor_out) override;
  virtual common::Error KeysImpl(const std::string& key_start,
                                 const std::string& key_end,
                                 uint64_t limit,
                                 std::vector<std::string>* ret) override;
  virtual common::Error DBkcountImpl(size_t* size) override;
  virtual common::Error FlushDBImpl() override;
  virtual common::Error SelectImpl(const std::string& name, IDataBaseInfo** info) override;
  virtual common::Error SetImpl(const NDbKValue& key, NDbKValue* added_key) override;
  virtual common::Error GetImpl(const NKey& key, NDbKValue* loaded_key) override;
  virtual common::Error DeleteImpl(const NKeys& keys, NKeys* deleted_keys) override;
  virtual common::Error RenameImpl(const NKey& key, string_key_t new_key) override;
  virtual common::Error SetTTLImpl(const NKey& key, ttl_t ttl) override;
  virtual common::Error GetTTLImpl(const NKey& key, ttl_t* ttl) override;
  virtual common::Error QuitImpl() override;
};

}  // namespace upscaledb
}  // namespace core
}  // namespace fastonosql
