#include "WidgetGallery.h"
#include <QAction>
#include <QActionGroup>
#include <QBoxLayout>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QStyle>

struct MainWindowPrivate;
class MainWindow : public QMainWindow {
public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

private:
  MainWindowPrivate* d;
};

struct MainWindowPrivate {
  WidgetGallery* gallery;
};

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), d(new MainWindowPrivate) {
  d->gallery = new WidgetGallery;
  setCentralWidget(d->gallery);

  auto mb = menuBar();
  auto fm = mb->addMenu("&File");
  fm->addAction("New");
  auto openAction = fm->addAction("Open");
  openAction->setCheckable(true);
  fm->addSeparator();
  auto subMenu = fm->addMenu("Sub Menu");
  fm->addAction("Save");
  auto vm = mb->addMenu("&View");
  auto fooAction = vm->addAction("Foo");
  auto barAction = vm->addAction("Bar");
  auto bazAction = vm->addAction("Baz");
  auto quiteBitAction = vm->addAction("Some item with quite a bit of text");
  Q_UNUSED(quiteBitAction)
  fooAction->setCheckable(true);
  fooAction->setIcon(style()->standardIcon(QStyle::SP_DirIcon));
  vm->setDefaultAction(barAction);
  bazAction->setEnabled(false);

  subMenu->addAction("One");
  subMenu->addAction("Two");

  auto alphaMenu = mb->addMenu("Alpha");
  auto betaMenu = mb->addMenu("Beta");
  alphaMenu->addAction("One");
  auto alphaTwo = alphaMenu->addAction("Two");
  alphaTwo->setShortcut(tr("Ctrl+Alt+Shift+F"));
  betaMenu->addAction("One");
  auto betaTwo = betaMenu->addAction("Two");
  betaTwo->setShortcut(tr("Ctrl+F"));

  auto cMenu = mb->addMenu("Charlie");
  auto caGroup = new QActionGroup(this);
  auto c1 = cMenu->addAction("One");
  auto c2 = cMenu->addAction("Two");
  c1->setCheckable(true);
  c2->setCheckable(true);
  caGroup->addAction(c1);
  caGroup->addAction(c2);
  c1->setChecked(true);
  cMenu->addSeparator();
  auto c3 = cMenu->addAction("Three");
  auto c4 = cMenu->addAction("Four");
  c3->setCheckable(true);
  c4->setCheckable(true);
  c3->setChecked(true);
  auto sep2 = cMenu->addSeparator();
  sep2->setText("Hey there here's some really long text for this separator");
  cMenu->addAction("Five");

  cMenu->addSection("SomeSec");
  cMenu->addAction("Six");
}

MainWindow::~MainWindow() { delete d; }

QMainWindow* Gallery_create(QWidget* parent = nullptr) {
  return new MainWindow(parent);
}
