/*  Copyright (C) 2014-2016 FastoGT. All right reserved.

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

#include "core/db_connection.h"
#include "core/command_handler.h"
#include "core/cdb_connection_client.h"

namespace fastonosql {
namespace core {

template <typename NConnection, typename Config, connectionTypes ContType>
class CDBConnection : public DBConnection<NConnection, Config, ContType>, public CommandHandler {
 public:
  typedef DBConnection<NConnection, Config, ContType> db_base_class;

  CDBConnection(const commands_t& commands, CDBConnectionClient* client)
      : db_base_class(), CommandHandler(commands), client_(client) {}
  virtual ~CDBConnection() {}

  common::Error select(const std::string& name, IDataBaseInfo** info) WARN_UNUSED_RESULT;

 private:
  virtual common::Error selectImpl(const std::string& name, IDataBaseInfo** info) = 0;
  CDBConnectionClient* client_;
};

template <typename NConnection, typename Config, connectionTypes ContType>
common::Error CDBConnection<NConnection, Config, ContType>::select(const std::string& name,
                                                                   IDataBaseInfo** info) {
  IDataBaseInfo* linfo = NULL;
  common::Error err = selectImpl(name, &linfo);
  if (err && err->isError()) {
    return err;
  }

  if (client_) {
    client_->currentDataBaseChanged(linfo);
  }

  if (info) {
    *info = linfo;
  } else {
    delete linfo;
  }

  return common::Error();
}

}  // namespace core
}  // namespace fastonosql
