#include "phantomstyle.h"
#include <QAction>
#include <QBoxLayout>
#include <QDebug>
#include <QFormLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMetaEnum>
#include <QPainter>
#include <QPushButton>
#include <QSplitter>
#include <QStatusBar>
#include <QTabBar>
#include <QTabWidget>
#include <QTableWidget>
#include <QToolBar>
#include <QToolButton>
#include <QTreeWidget>
#include <QVarLengthArray>
#include <QtEvents>

namespace {

QWidget* treeAndDetailsWidget() {
  auto w = new QWidget;
  auto hbox = new QHBoxLayout;
  auto tree = new QTreeWidget;
  for (int i = 0; i < 5; ++i) {
    auto item = new QTreeWidgetItem(tree);
    item->setText(0, QString::asprintf("Item %d", i));
    for (int j = 0; j < 5; ++j) {
      auto item0 = new QTreeWidgetItem(item);
      item0->setText(0, QString::asprintf("Nested %d", j));
      if (j == 3)
        item0->setData(0, Qt::DecorationRole, QColor(120, 120, 60));
      for (int k = 0; k < 5; ++k) {
        auto item1 = new QTreeWidgetItem(item0);
        item1->setText(0, QString::asprintf("Nested Again %d", k));
        for (int l = 0; l < 5; ++l) {
          auto item2 = new QTreeWidgetItem(item1);
          item2->setText(0, QString::asprintf("Nested Yet Again %d", l));
        }
      }
    }
  }
  hbox->addWidget(tree);
  auto form = new QFormLayout;
  form->addRow("Name", new QLineEdit("Cool Dude"));
  form->addRow("Address", new QLineEdit("Cool Place"));
  hbox->addLayout(form);
  w->setLayout(hbox);
  return w;
}

QWidget* tabsInDirections() {
  auto w = new QWidget;
  auto tabsHBox = new QHBoxLayout;
  auto tabsVBox = new QVBoxLayout;
  QTabWidget::TabPosition positions[] = {QTabWidget::North, QTabWidget::South,
                                         QTabWidget::West, QTabWidget::East};
  QBoxLayout* lays[] = {tabsVBox, tabsVBox, tabsHBox, tabsHBox};
  tabsHBox->addLayout(tabsVBox);
  for (int ipos = 0; ipos < 4; ++ipos) {
    auto tabw = new QTabWidget;
    // tabsHBox->addWidget(tabw);
    lays[ipos]->addWidget(tabw);
    tabw->setTabPosition(positions[ipos]);
    for (int tabi = 0; tabi < 3; ++tabi) {
      tabw->addTab(new QWidget, QString::asprintf("Tab %d", tabi));
    }
  }
  w->setLayout(tabsHBox);
  return w;
}

QWidget* splitTest() {
  auto w = new QSplitter;
  w->addWidget(new QPushButton("One"));
  w->addWidget(new QPushButton("Multiple text\nlines"));
  return w;
}

QWidget* toolButtonTest() {
  auto w = new QWidget;
  auto vbox = new QVBoxLayout;
  auto tb0 = new QToolButton;
  tb0->setText("Just text");
  auto tb1 = new QToolButton;
  tb1->setText("Default Both");
  tb1->setIcon(w->style()->standardIcon(QStyle::SP_DesktopIcon));
  auto tb2 = new QToolButton;
  tb2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  tb2->setText("Text Under");
  tb2->setIcon(w->style()->standardIcon(QStyle::SP_DirIcon));
  auto tb3 = new QToolButton;
  tb3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
  tb3->setText("Beside but no icon");

  auto tb4 = new QToolButton;
  tb4->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
  auto menu = new QMenu(tb4);
  menu->addAction("Foo");
  menu->addAction("Bar");
  tb4->setText("Text Beside");
  tb4->setIcon(w->style()->standardIcon(QStyle::SP_DirIcon));
  tb4->setMenu(menu);

  vbox->addWidget(tb0);
  vbox->addWidget(tb1);
  vbox->addWidget(tb2);
  vbox->addWidget(tb3);
  vbox->addWidget(tb4);
  w->setLayout(vbox);
  return w;
}

QWidget* tabBarOnly() {
  auto w = new QWidget;
  auto vbox = new QVBoxLayout;
  auto tb = new QTabBar;
  tb->addTab("Test 1");
  tb->addTab("Test 2");
  tb->setDocumentMode(true);
  tb->setDrawBase(true);
  vbox->addWidget(tb);
  w->setLayout(vbox);
  return w;
}

QWidget* coolButtons() {
  auto w = new QWidget;
  auto vbox = new QHBoxLayout;

  auto pb0 = new QPushButton;
  vbox->addWidget(pb0);
  auto pb1 = new QPushButton;
  pb1->setText("Just text");
  vbox->addWidget(pb1);
  auto pb2 = new QPushButton;
  pb2->setText("Text and icon");
  pb2->setIcon(w->style()->standardIcon(QStyle::SP_ComputerIcon));
  vbox->addWidget(pb2);
  auto pb3 = new QPushButton;
  pb3->setIcon(w->style()->standardIcon(QStyle::SP_ComputerIcon));
  vbox->addWidget(pb3);

  w->setLayout(vbox);
  return w;
}

QWidget* frames() {
  auto w = new QWidget;
  auto grid = new QGridLayout;
  const int cols = 6;
  int col = 0;
  int row = 0;
  auto addFrame = [&](QFrame::Shape shape, QFrame::Shadow shadow) {
    auto vbox = new QVBoxLayout;
    auto hbox = new QHBoxLayout;
    auto shapeStr = QMetaEnum::fromType<QFrame::Shape>().valueToKey(shape);
    auto shadowStr = QMetaEnum::fromType<QFrame::Shadow>().valueToKey(shadow);
    QString str = QString::asprintf("%s %s", shapeStr, shadowStr);
    vbox->addWidget(new QLabel(str));
    auto addSize = [&](int width, int height) {
      auto frame = new QFrame;
      frame->setFixedSize(width, height);
      frame->setFrameShape(shape);
      frame->setFrameShadow(shadow);
      hbox->addWidget(frame);
    };
    addSize(30, 30);
    addSize(1, 30);
    addSize(30, 1);
    vbox->addLayout(hbox);
    grid->addLayout(vbox, row, col);
    ++row;
    if (row == cols) {
      row = 0;
      ++col;
    }
  };
  QFrame::Shape shapes[] = {QFrame::NoFrame,    QFrame::Box,   QFrame::Panel,
                            QFrame::WinPanel,   QFrame::HLine, QFrame::VLine,
                            QFrame::StyledPanel};
  QFrame::Shadow shadows[] = {(QFrame::Shadow)QFrame::NoFrame, QFrame::Plain,
                              QFrame::Raised, QFrame::Sunken};
  int numShapes = (int)(sizeof(shapes) / sizeof(shapes[0]));
  int numShadows = (int)(sizeof(shadows) / sizeof(shadows[0]));
  for (int ishape = 0; ishape < numShapes; ++ishape) {
    for (int ishadow = 0; ishadow < numShadows; ++ishadow) {
      addFrame(shapes[ishape], shadows[ishadow]);
    }
  }
  w->setLayout(grid);
  return w;
}

QWidget* tableWithColumns() {
  auto w = new QTableWidget;
  w->setColumnCount(4);
  w->setRowCount(4);
  QList<QAction*> acts;
  auto addSep = [&] {
    auto sep = new QAction(w);
    sep->setSeparator(true);
    acts += sep;
  };
  auto sortA = new QAction(w);
  sortA->setText("Sorting");
  sortA->setCheckable(true);
  QObject::connect(sortA, &QAction::triggered, w,
                   [w](bool checked) { w->setSortingEnabled(checked); });
  acts += sortA;
  auto stretchHorizA = new QAction(w);
  stretchHorizA->setText("Stretch Last Horizontal");
  stretchHorizA->setCheckable(true);
  QObject::connect(stretchHorizA, &QAction::triggered, w, [w](bool checked) {
    w->horizontalHeader()->setStretchLastSection(checked);
  });
  auto stretchVertA = new QAction(w);
  stretchVertA->setText("Stretch Last Vertical");
  stretchVertA->setCheckable(true);
  QObject::connect(stretchVertA, &QAction::triggered, w, [w](bool checked) {
    w->verticalHeader()->setStretchLastSection(checked);
  });
  acts += stretchHorizA;
  acts += stretchVertA;
  addSep();
  for (int i = 0; i < w->rowCount(); ++i) {
    auto a = new QAction(w);
    a->setText(QString::asprintf("Row Visible: %d", i + 1));
    a->setCheckable(true);
    a->setChecked(!w->isRowHidden(i));
    QObject::connect(a, &QAction::triggered, w,
                     [w, i](bool checked) { w->setRowHidden(i, !checked); });
    acts += a;
  }
  addSep();
  for (int i = 0; i < w->columnCount(); ++i) {
    auto a = new QAction(w);
    a->setText(QString::asprintf("Column Visible: %d", i + 1));
    a->setCheckable(true);
    a->setChecked(!w->isColumnHidden(i));
    QObject::connect(a, &QAction::triggered, w,
                     [w, i](bool checked) { w->setColumnHidden(i, !checked); });
    acts += a;
  }
  w->addActions(acts);
  w->horizontalHeader()->addActions(acts);
  w->verticalHeader()->addActions(acts);
  w->setContextMenuPolicy(Qt::ActionsContextMenu);
  w->horizontalHeader()->setContextMenuPolicy(Qt::ActionsContextMenu);
  w->verticalHeader()->setContextMenuPolicy(Qt::ActionsContextMenu);
  return w;
}
} // namespace

QMainWindow* FunHouse_create(QWidget* parent) {
  auto mainWindow = new QMainWindow(parent);
  auto mb = mainWindow->menuBar();
  auto fileMenu = mb->addMenu("File");
  auto viewMenu = mb->addMenu("View");
  fileMenu->addAction("New...");
  fileMenu->addAction("Open...");
  fileMenu->addSeparator();
  fileMenu->addAction("Save");
  fileMenu->addAction("Save As...");
  viewMenu->addAction("Stuff");
  viewMenu->addAction("Foo");
  auto mainTabs = new QTabWidget;
  mainTabs->setDocumentMode(true);
  mainWindow->setCentralWidget(mainTabs);
  mainTabs->addTab(tableWithColumns(), "Table");
  mainTabs->addTab(frames(), "Frames");
  mainTabs->addTab(coolButtons(), "Push Buttons");
  mainTabs->addTab(toolButtonTest(), "Tool Buttons");
  mainTabs->addTab(splitTest(), "Splitter");
  mainTabs->addTab(tabsInDirections(), "Tab Dirs");
  mainTabs->addTab(tabBarOnly(), "Tab Bar");
  mainTabs->addTab(treeAndDetailsWidget(), "Tree");
  mainWindow->statusBar()->setSizeGripEnabled(true);

  auto tbara = mainWindow->addToolBar("Tester A");
  tbara->addAction("A One");
  auto a2 = tbara->addAction("A Two");
  a2->setCheckable(true);
  tbara->addSeparator();
  tbara->addAction("B One");
  tbara->addAction("B Two");
  auto tbarb = mainWindow->addToolBar("Tester B");
  tbarb->addAction("A One");
  tbarb->addAction("A Two");
  tbarb->addSeparator();
  tbarb->addAction("B One");
  tbarb->addAction("B Two");
  return mainWindow;
}
