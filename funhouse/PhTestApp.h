#pragma once
#include <QtWidgets/qapplication.h>

class PhTestApp : public QApplication {
public:
  PhTestApp(int& argc, char** argv, int = ApplicationFlags);

#ifdef BUILD_WITH_EASY_PROFILER
  bool notify(QObject* receiver, QEvent* e) override;
#endif
};
