// Copyright (c) 2015-present, Qihoo, Inc.  All rights reserved.
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree. An additional grant
// of patent rights can be found in the PATENTS file in the same directory.

#ifndef PIKA_ZSET_H_
#define PIKA_ZSET_H_

#include "storage/storage.h"

#include "include/pika_command.h"
#include "include/pika_partition.h"

/*
 * zset
 */
class ZAddCmd : public Cmd {
 public:
  ZAddCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag) {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Partition> partition = nullptr) override;
  void Split(std::shared_ptr<Partition> partition, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new ZAddCmd(*this); }

 private:
  std::string key_;
  std::vector<storage::ScoreMember> score_members;
  void DoInitial() override;
};

class ZCardCmd : public Cmd {
 public:
  ZCardCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag) {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Partition> partition = nullptr) override;
  void Split(std::shared_ptr<Partition> partition, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new ZCardCmd(*this); }

 private:
  std::string key_;
  void DoInitial() override;
};

class ZScanCmd : public Cmd {
 public:
  ZScanCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag), pattern_("*") {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Partition> partition = nullptr) override;
  void Split(std::shared_ptr<Partition> partition, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new ZScanCmd(*this); }

 private:
  std::string key_, pattern_ = "*";
  int64_t cursor_ = 0, count_ = 10;
  void DoInitial() override;
  void Clear() override {
    pattern_ = "*";
    count_ = 10;
  }
};

class ZIncrbyCmd : public Cmd {
 public:
  ZIncrbyCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag) {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Partition> partition = nullptr) override;
  void Split(std::shared_ptr<Partition> partition, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new ZIncrbyCmd(*this); }

 private:
  std::string key_, member_;
  double by_ = 0;
  void DoInitial() override;
};

class ZsetRangeParentCmd : public Cmd {
 public:
  ZsetRangeParentCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag) {}

 protected:
  std::string key_;
  int64_t start_ = 0, stop_ = -1;
  bool is_ws_ = false;
  void DoInitial() override;
  void Clear() override { is_ws_ = false; }
};

class ZRangeCmd : public ZsetRangeParentCmd {
 public:
  ZRangeCmd(const std::string& name, int arity, uint16_t flag) : ZsetRangeParentCmd(name, arity, flag) {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Partition> partition = nullptr) override;
  void Split(std::shared_ptr<Partition> partition, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new ZRangeCmd(*this); }

 private:
  void DoInitial() override;
};

class ZRevrangeCmd : public ZsetRangeParentCmd {
 public:
  ZRevrangeCmd(const std::string& name, int arity, uint16_t flag) : ZsetRangeParentCmd(name, arity, flag) {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Partition> partition = nullptr) override;
  void Split(std::shared_ptr<Partition> partition, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new ZRevrangeCmd(*this); }

 private:
  void DoInitial() override;
};

class ZsetRangebyscoreParentCmd : public Cmd {
 public:
  ZsetRangebyscoreParentCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag) {}

 protected:
  std::string key_;
  double min_score_ = 0, max_score_ = 0;
  bool left_close_ = true, right_close_ = true, with_scores_ = false;
  int64_t offset_ = 0, count_ = -1;
  void DoInitial() override;
  void Clear() override {
    left_close_ = right_close_ = true;
    with_scores_ = false;
    offset_ = 0;
    count_ = -1;
  }
};

class ZRangebyscoreCmd : public ZsetRangebyscoreParentCmd {
 public:
  ZRangebyscoreCmd(const std::string& name, int arity, uint16_t flag) : ZsetRangebyscoreParentCmd(name, arity, flag) {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Partition> partition = nullptr) override;
  void Split(std::shared_ptr<Partition> partition, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new ZRangebyscoreCmd(*this); }

 private:
  void DoInitial() override;
};

class ZRevrangebyscoreCmd : public ZsetRangebyscoreParentCmd {
 public:
  ZRevrangebyscoreCmd(const std::string& name, int arity, uint16_t flag)
      : ZsetRangebyscoreParentCmd(name, arity, flag) {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Partition> partition = nullptr) override;
  void Split(std::shared_ptr<Partition> partition, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new ZRevrangebyscoreCmd(*this); }

 private:
  void DoInitial() override;
};

class ZCountCmd : public Cmd {
 public:
  ZCountCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag) {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Partition> partition = nullptr) override;
  void Split(std::shared_ptr<Partition> partition, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new ZCountCmd(*this); }

 private:
  std::string key_;
  double min_score_ = 0, max_score_ = 0;
  bool left_close_ = true, right_close_ = true;
  void DoInitial() override;
  void Clear() override {
    left_close_ = true;
    right_close_ = true;
  }
};

class ZRemCmd : public Cmd {
 public:
  ZRemCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag) {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Partition> partition = nullptr) override;
  void Split(std::shared_ptr<Partition> partition, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new ZRemCmd(*this); }

 private:
  std::string key_;
  std::vector<std::string> members_;
  void DoInitial() override;
};

class ZsetUIstoreParentCmd : public Cmd {
 public:
  ZsetUIstoreParentCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag), aggregate_(storage::SUM) {}

 protected:
  std::string dest_key_;
  int64_t num_keys_ = 0;
  storage::AGGREGATE aggregate_;
  std::vector<std::string> keys_;
  std::vector<double> weights_;
  void DoInitial() override;
  void Clear() override { aggregate_ = storage::SUM; }
};

class ZUnionstoreCmd : public ZsetUIstoreParentCmd {
 public:
  ZUnionstoreCmd(const std::string& name, int arity, uint16_t flag) : ZsetUIstoreParentCmd(name, arity, flag) {}
  void Do(std::shared_ptr<Partition> partition = nullptr) override;
  void Split(std::shared_ptr<Partition> partition, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new ZUnionstoreCmd(*this); }

 private:
  void DoInitial() override;
};

class ZInterstoreCmd : public ZsetUIstoreParentCmd {
 public:
  ZInterstoreCmd(const std::string& name, int arity, uint16_t flag) : ZsetUIstoreParentCmd(name, arity, flag) {}
  void Do(std::shared_ptr<Partition> partition = nullptr) override;
  void Split(std::shared_ptr<Partition> partition, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new ZInterstoreCmd(*this); }

 private:
  void DoInitial() override;
};

class ZsetRankParentCmd : public Cmd {
 public:
  ZsetRankParentCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag) {}

 protected:
  std::string key_, member_;
  void DoInitial() override;
};

class ZRankCmd : public ZsetRankParentCmd {
 public:
  ZRankCmd(const std::string& name, int arity, uint16_t flag) : ZsetRankParentCmd(name, arity, flag) {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Partition> partition = nullptr) override;
  void Split(std::shared_ptr<Partition> partition, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new ZRankCmd(*this); }

 private:
  void DoInitial() override;
};

class ZRevrankCmd : public ZsetRankParentCmd {
 public:
  ZRevrankCmd(const std::string& name, int arity, uint16_t flag) : ZsetRankParentCmd(name, arity, flag) {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Partition> partition = nullptr) override;
  void Split(std::shared_ptr<Partition> partition, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new ZRevrankCmd(*this); }

 private:
  void DoInitial() override;
};

class ZScoreCmd : public ZsetRankParentCmd {
 public:
  ZScoreCmd(const std::string& name, int arity, uint16_t flag) : ZsetRankParentCmd(name, arity, flag) {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Partition> partition = nullptr) override;
  void Split(std::shared_ptr<Partition> partition, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new ZScoreCmd(*this); }

 private:
  std::string key_, member_;
  void DoInitial() override;
};

class ZsetRangebylexParentCmd : public Cmd {
 public:
  ZsetRangebylexParentCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag) {}

 protected:
  std::string key_, min_member_, max_member_;
  bool left_close_ = true, right_close_ = true;
  int64_t offset_ = 0, count_ = -1;
  void DoInitial() override;
  void Clear() override {
    left_close_ = right_close_ = true;
    offset_ = 0;
    count_ = -1;
  }
};

class ZRangebylexCmd : public ZsetRangebylexParentCmd {
 public:
  ZRangebylexCmd(const std::string& name, int arity, uint16_t flag) : ZsetRangebylexParentCmd(name, arity, flag) {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Partition> partition = nullptr) override;
  void Split(std::shared_ptr<Partition> partition, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new ZRangebylexCmd(*this); }

 private:
  void DoInitial() override;
};

class ZRevrangebylexCmd : public ZsetRangebylexParentCmd {
 public:
  ZRevrangebylexCmd(const std::string& name, int arity, uint16_t flag) : ZsetRangebylexParentCmd(name, arity, flag) {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Partition> partition = nullptr) override;
  void Split(std::shared_ptr<Partition> partition, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new ZRevrangebylexCmd(*this); }

 private:
  void DoInitial() override;
};

class ZLexcountCmd : public Cmd {
 public:
  ZLexcountCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag) {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Partition> partition = nullptr) override;
  void Split(std::shared_ptr<Partition> partition, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new ZLexcountCmd(*this); }

 private:
  std::string key_, min_member_, max_member_;
  bool left_close_ = true, right_close_ = true;
  void DoInitial() override;
  void Clear() override { left_close_ = right_close_ = true; }
};

class ZRemrangebyrankCmd : public Cmd {
 public:
  ZRemrangebyrankCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag) {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Partition> partition = nullptr) override;
  void Split(std::shared_ptr<Partition> partition, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new ZRemrangebyrankCmd(*this); }

 private:
  std::string key_;
  int64_t start_rank_ = 0, stop_rank_ = -1;
  void DoInitial() override;
};

class ZRemrangebyscoreCmd : public Cmd {
 public:
  ZRemrangebyscoreCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag) {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Partition> partition = nullptr) override;
  void Split(std::shared_ptr<Partition> partition, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new ZRemrangebyscoreCmd(*this); }

 private:
  std::string key_;
  double min_score_ = 0, max_score_ = 0;
  bool left_close_ = true, right_close_ = true;
  void DoInitial() override;
  void Clear() override { left_close_ = right_close_ = true; }
};

class ZRemrangebylexCmd : public Cmd {
 public:
  ZRemrangebylexCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag) {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Partition> partition = nullptr) override;
  void Split(std::shared_ptr<Partition> partition, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new ZRemrangebylexCmd(*this); }

 private:
  std::string key_;
  std::string min_member_, max_member_;
  bool left_close_ = true, right_close_ = true;
  void DoInitial() override;
  void Clear() override { left_close_ = right_close_ = true; }
};

class ZPopmaxCmd : public Cmd {
 public:
  ZPopmaxCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag) {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.emplace_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Partition> partition = nullptr) override;
  void Split(std::shared_ptr<Partition> partition, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new ZPopmaxCmd(*this); }

 private:
  void DoInitial() override;
  std::string key_;
  int64_t count_ = 0;
};

class ZPopminCmd : public Cmd {
 public:
  ZPopminCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag) {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Partition> partition = nullptr) override;
  void Split(std::shared_ptr<Partition> partition, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new ZPopminCmd(*this); }

 private:
  void DoInitial() override;
  std::string key_;
  int64_t count_ = 0;
};

#endif
