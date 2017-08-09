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

#include "core/db/lmdb/command_translator.h"

#include <common/sprintf.h>

#define LMDB_COMMONTYPE_GET_KEY_COMMAND COMMONTYPE_GET_KEY_COMMAND

#define LMDB_SET_KEY_PATTERN_2ARGS_SS "SET %s %s"
#define LMDB_GET_KEY_PATTERN_1ARGS_S LMDB_COMMONTYPE_GET_KEY_COMMAND " %s"
#define LMDB_DELETE_KEY_PATTERN_1ARGS_S "DEL %s"
#define LMDB_RENAME_KEY_PATTERN_2ARGS_SS "RENAME %s %s"

namespace fastonosql {
namespace core {
namespace lmdb {

CommandTranslator::CommandTranslator(const std::vector<CommandHolder>& commands) : ICommandTranslator(commands) {}

common::Error CommandTranslator::CreateKeyCommandImpl(const NDbKValue& key, std::string* cmdstring) const {
  const NKey cur = key.GetKey();
  key_t key_str = cur.GetKey();
  std::string value_str = key.ValueString();
  *cmdstring = common::MemSPrintf(LMDB_SET_KEY_PATTERN_2ARGS_SS, key_str, value_str);
  return common::Error();
}

common::Error CommandTranslator::LoadKeyCommandImpl(const NKey& key,
                                                    common::Value::Type type,
                                                    std::string* cmdstring) const {
  UNUSED(type);

  key_t key_str = key.GetKey();
  *cmdstring = common::MemSPrintf(LMDB_GET_KEY_PATTERN_1ARGS_S, key_str);
  return common::Error();
}

common::Error CommandTranslator::DeleteKeyCommandImpl(const NKey& key, std::string* cmdstring) const {
  key_t key_str = key.GetKey();
  *cmdstring = common::MemSPrintf(LMDB_DELETE_KEY_PATTERN_1ARGS_S, key_str);
  return common::Error();
}

common::Error CommandTranslator::RenameKeyCommandImpl(const NKey& key,
                                                      const std::string& new_name,
                                                      std::string* cmdstring) const {
  key_t key_str = key.GetKey();
  *cmdstring = common::MemSPrintf(LMDB_RENAME_KEY_PATTERN_2ARGS_SS, key_str, new_name);
  return common::Error();
}

common::Error CommandTranslator::ChangeKeyTTLCommandImpl(const NKey& key, ttl_t ttl, std::string* cmdstring) const {
  UNUSED(key);
  UNUSED(ttl);
  UNUSED(cmdstring);

  std::string errorMsg =
      common::MemSPrintf("Sorry, but now " PROJECT_NAME_TITLE " not supported change ttl command for LMDB.");
  return common::make_error_value(errorMsg, common::ErrorValue::E_ERROR);
}

common::Error CommandTranslator::LoadKeyTTLCommandImpl(const NKey& key, std::string* cmdstring) const {
  UNUSED(key);
  UNUSED(cmdstring);

  std::string errorMsg =
      common::MemSPrintf("Sorry, but now " PROJECT_NAME_TITLE " not supported get ttl command for LMDB.");
  return common::make_error_value(errorMsg, common::ErrorValue::E_ERROR);
}

bool CommandTranslator::IsLoadKeyCommandImpl(const CommandInfo& cmd) const {
  return cmd.IsEqualName(LMDB_COMMONTYPE_GET_KEY_COMMAND);
}

common::Error CommandTranslator::PublishCommandImpl(const NDbPSChannel& channel,
                                                    const std::string& message,
                                                    std::string* cmdstring) const {
  UNUSED(channel);
  UNUSED(message);
  UNUSED(cmdstring);

  std::string errorMsg =
      common::MemSPrintf("Sorry, but now " PROJECT_NAME_TITLE " not supported publish command for LMDB.");
  return common::make_error_value(errorMsg, common::ErrorValue::E_ERROR);
}

common::Error CommandTranslator::SubscribeCommandImpl(const NDbPSChannel& channel, std::string* cmdstring) const {
  UNUSED(channel);
  UNUSED(cmdstring);

  std::string errorMsg =
      common::MemSPrintf("Sorry, but now " PROJECT_NAME_TITLE " not supported subscribe command for LMDB.");
  return common::make_error_value(errorMsg, common::ErrorValue::E_ERROR);
}

}  // namespace lmdb
}  // namespace core
}  // namespace fastonosql
