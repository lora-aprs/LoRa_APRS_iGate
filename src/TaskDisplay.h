#ifndef TASK_DISPLAY_H_
#define TASK_DISPLAY_H_

#include "Display/Display.h"
#include "System/TaskManager.h"

class DisplayTask : public Task {
public:
  DisplayTask();
  virtual ~DisplayTask();

  virtual bool setup(System &system) override;
  virtual bool loop(System &system) override;
};

#endif
