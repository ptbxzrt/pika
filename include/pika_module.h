// Copyright (c) 2015-present, Qihoo, Inc.  All rights reserved.
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree. An additional grant
// of patent rights can be found in the PATENTS file in the same directory.

#ifndef PIKA_MODULE_H_
#define PIKA_MODULE_H_

#include "storage/storage.h"

#include "include/pika_command.h"
#include "include/pika_partition.h"

/*
 * module
 */

class ModuleCmd : public Cmd {
 public:
  ModuleCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag) {}
  virtual void Do(std::shared_ptr<Partition> partition = nullptr) override;
  virtual void Split(std::shared_ptr<Partition> partition, const HintKeys& hint_keys){};
  virtual void Merge(){};
  virtual Cmd* Clone() override { return new ModuleCmd(*this); }

 private:
  std::string subcommand_;
  std::vector<std::string> arguments_;
  virtual void DoInitial() override;
  virtual void Clear() { arguments_.clear(); }
};

#endif