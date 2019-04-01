#ifndef PHANTOMSTYLEPLUGIN_H
#define PHANTOMSTYLEPLUGIN_H
#include <QtWidgets/qstyleplugin.h>

class PhantomStylePlugin : public QStylePlugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID QStyleFactoryInterface_iid FILE
                    "phantomstyleplugin.json")
public:
  PhantomStylePlugin();
  ~PhantomStylePlugin();
  QStyle* create(const QString& key) override;
};
#endif
