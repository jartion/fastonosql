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

#include <memory>  // for shared_ptr
#include <string>  // for string
#include <vector>  // for vector

#include "core/connection_types.h"  // for core::connectionTypes
#include "proxy/connection_settings/iconnection_settings.h"

namespace common {
namespace net {
struct HostAndPort;
}
}  // namespace common

namespace fastonosql {
namespace proxy {

class IClusterSettingsBase : public IConnectionSettings {
 public:
  typedef IConnectionSettingsBaseSPtr cluster_node_t;
  typedef std::vector<cluster_node_t> cluster_nodes_t;
  cluster_nodes_t Nodes() const;

  void AddNode(IConnectionSettingsBaseSPtr node);

  virtual std::string ToString() const override;
  virtual IClusterSettingsBase* Clone() const override = 0;

  virtual IConnectionSettingsBaseSPtr FindSettingsByHost(const common::net::HostAndPort& host) const;

 protected:
  IClusterSettingsBase(const connection_path_t& connectionName, core::connectionTypes type);

 private:
  cluster_nodes_t clusters_nodes_;
};

typedef common::shared_ptr<IClusterSettingsBase> IClusterSettingsBaseSPtr;

}  // namespace proxy
}  // namespace fastonosql
