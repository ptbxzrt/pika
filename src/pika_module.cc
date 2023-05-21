#include "include/pika_module.h"

void ModuleCmd::DoInitial() {
  if (!CheckArg(argv_.size())) {
    res_.SetRes(CmdRes::kWrongNum, kCmdNameModule);
    return;
  }
  subcommand_ = argv_[1];
  if (strcasecmp(subcommand_.data(), "load") && strcasecmp(subcommand_.data(), "unload") &&
      strcasecmp(subcommand_.data(), "loadex") && strcasecmp(subcommand_.data(), "list") &&
      strcasecmp(subcommand_.data(), "help")) {
    res_.SetRes(CmdRes::kErrOther, "Unknown MODULE subcommand or wrong number of arguments for '" + subcommand_ + "'");
    return;
  }
  for (size_t i = 2; i < argv_.size(); i++) {
    arguments_.push_back(argv_[i]);
  }
}

void ModuleCmd::Do(std::shared_ptr<Partition> partition) {
  if (!strcasecmp(subcommand_.data(), "load")) {
    res_.SetRes(CmdRes::kOk);
    return;
  } else if (!strcasecmp(subcommand_.data(), "unload")) {
    res_.SetRes(CmdRes::kErrOther, "'module " + subcommand_ + "' is not implemented yet");
    return;
  } else if (!strcasecmp(subcommand_.data(), "loadex")) {
    res_.SetRes(CmdRes::kErrOther, "'module " + subcommand_ + "' is not implemented yet");
    return;
  } else if (!strcasecmp(subcommand_.data(), "list")) {
    res_.SetRes(CmdRes::kErrOther, "'module " + subcommand_ + "' is not implemented yet");
    return;
  } else if (!strcasecmp(subcommand_.data(), "help")) {
    res_.SetRes(CmdRes::kErrOther, "'module " + subcommand_ + "' is not implemented yet");
    return;
  }
}