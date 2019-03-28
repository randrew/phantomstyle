#include "phantomcolor.h"
#include <QColorDialog>
#include <QDebug>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QtEvents>

using Rgb = Phantom::Rgb;
using Hsl = Phantom::Hsl;

Q_NEVER_INLINE static QColor
mergedColors(const QColor& colorA, const QColor& colorB, int factor = 0) {
  const int maxFactor = 255;
  QColor tmp = colorA;
  tmp.setRed((tmp.red() * factor) / maxFactor +
             (colorB.red() * (maxFactor - factor)) / maxFactor);
  tmp.setGreen((tmp.green() * factor) / maxFactor +
               (colorB.green() * (maxFactor - factor)) / maxFactor);
  tmp.setBlue((tmp.blue() * factor) / maxFactor +
              (colorB.blue() * (maxFactor - factor)) / maxFactor);
  return tmp;
}

class ColorBand : public QWidget {

public:
  explicit ColorBand(QWidget* parent = nullptr)
      : QWidget(parent), colorA(255, 0, 0), colorB(0, 60, 60), gamma(1.0) {}
  QSize sizeHint() const override { return QSize(256, 100); }
  QColor colorA, colorB;
  double gamma;

protected:
  void paintEvent(QPaintEvent* e) override {
    Q_UNUSED(e);
    QPainter p(this);
    QColor from = colorA;
    QColor to = colorB;
    for (int i = 0; i < 256; ++i) {
      p.fillRect(QRect(i, 0, 1, 25), mergedColors(to, from, i));
      QColor c = Phantom::lerpQColor(from, to, (double)i / 255.0);
      p.fillRect(QRect(i, 25, 1, 25), c);

      double alpha = (double)i / 255.0;
      Rgb rgbf = Rgb::ofQColor(from);
      Rgb rgbt = Rgb::ofQColor(to);
      Hsl hslf = Hsl::ofRgb(rgbf);
      Hsl hslt = Hsl::ofRgb(rgbt);
      double l = Phantom::lerp(hslf.l, hslt.l, alpha);
      Rgb rgbr = Rgb::lerp(rgbf, rgbt, alpha);
      Hsl hslr = Hsl::ofRgb(rgbr);
      hslr.l = l;
      rgbr = Rgb::ofHsl(hslr);
      QColor hc = hslr.toQColor();
      p.fillRect(QRect(i, 50, 1, 25), hc);
    }
  }
};


class ColorTest : public QWidget {
public:
  explicit ColorTest(QWidget* parent = nullptr);
};

ColorTest::ColorTest(QWidget* parent) : QWidget(parent) {
  // auto b = new QPushButton;
  // connect(b, &QPushButton::clicked, this, [this] {
  // });
  // vbox->addWidget(b);

  auto bandWidget = new ColorBand;
  auto slider = new QSlider;
  slider->setOrientation(Qt::Horizontal);
  slider->setRange(0, 1000);
  auto glabel = new QLabel;
  connect(slider, &QSlider::valueChanged, bandWidget,
          [bandWidget, glabel](int val) {
            double v = (double)val / 1000.0;
            v = Phantom::lerp(0.1, 12.0, v);
            bandWidget->gamma = v;
            bandWidget->update();
            glabel->setText(QString::number(v, 'g', 4));
          });
  auto vbox = new QVBoxLayout;
  vbox->addWidget(bandWidget);
  vbox->addWidget(slider, 0);
  vbox->addWidget(glabel, 0);
  setLayout(vbox);
  setBackgroundRole(QPalette::Base);
  setAutoFillBackground(true);

  auto dlga = new QColorDialog(this);
  dlga->setCurrentColor(bandWidget->colorA);
  dlga->show();
  connect(dlga, &QColorDialog::currentColorChanged, bandWidget,
          [bandWidget](const QColor& color) {
            bandWidget->colorA = color;
            bandWidget->update();
          });
  auto dlgb = new QColorDialog(this);
  dlgb->setCurrentColor(bandWidget->colorB);
  dlgb->show();
  connect(dlgb, &QColorDialog::currentColorChanged, bandWidget,
          [bandWidget](const QColor& color) {
            bandWidget->colorB = color;
            bandWidget->update();
          });
}

QWidget* ColorTest_create(QWidget* parent = nullptr) {
  return new ColorTest(parent);
}
