#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QComboBox;
class QDateTimeEdit;
class QDial;
class QGroupBox;
class QLabel;
class QLineEdit;
class QProgressBar;
class QPushButton;
class QRadioButton;
class QScrollBar;
class QSlider;
class QSpinBox;
class QTabWidget;
class QTableWidget;
class QTextEdit;
QT_END_NAMESPACE

class WidgetGallery : public QWidget {
  Q_OBJECT

public:
  WidgetGallery(QWidget* parent = nullptr);

private slots:
  void changeStyle(const QString& styleName);
  void changePalette();
  void advanceProgressBar();

private:
  void createTopLeftGroupBox();
  void createTopRightGroupBox();
  void createBottomLeftTabWidget();
  void createBottomRightGroupBox();
  void createProgressBar();

  QPalette originalPalette;

  QLabel* styleLabel;
  QComboBox* styleComboBox;
  QCheckBox* useStylePaletteCheckBox;
  QCheckBox* disableWidgetsCheckBox;
  QGroupBox* topLeftGroupBox;
  QRadioButton* radioButton1;
  QRadioButton* radioButton2;
  QRadioButton* radioButton3;
  QCheckBox* checkBox;
  QGroupBox* topRightGroupBox;
  QPushButton* defaultPushButton;
  QPushButton* togglePushButton;
  QPushButton* flatPushButton;
  QTabWidget* bottomLeftTabWidget;
  QTableWidget* tableWidget;
  QTextEdit* textEdit;
  QGroupBox* bottomRightGroupBox;
  QLineEdit* lineEdit;
  QSpinBox* spinBox;
  QDateTimeEdit* dateTimeEdit;
  QSlider* slider;
  QDial* dial;
  QProgressBar* progressBar;
};
