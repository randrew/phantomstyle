#include "PhTestApp.h"
#ifdef BUILD_WITH_EASY_PROFILER
#include <easy/arbitrary_value.h>
#include <easy/profiler.h>
#endif

PhTestApp::PhTestApp(int& argc, char** argv, int flags)
    : QApplication(argc, argv, flags) {}

#ifdef BUILD_WITH_EASY_PROFILER
bool PhTestApp::notify(QObject* receiver, QEvent* e) {
  const char* className = receiver->metaObject()->className();
  EASY_TEXT("MetaClass", className);
  // Generate profiling blocks for top-level events
#define EVENT_BLOCK(_ident)                                                    \
  case QEvent::_ident: {                                                       \
    EASY_BLOCK("[" #_ident "]", profiler::colors::Grey300);                    \
    return QApplication::notify(receiver, e);                                  \
  }
  switch (e->type()) {
    EVENT_BLOCK(None)
    EVENT_BLOCK(Timer)
    EVENT_BLOCK(MouseButtonPress)
    EVENT_BLOCK(MouseButtonRelease)
    EVENT_BLOCK(MouseButtonDblClick)
    EVENT_BLOCK(MouseMove)
    EVENT_BLOCK(KeyPress)
    EVENT_BLOCK(KeyRelease)
    EVENT_BLOCK(FocusIn)
    EVENT_BLOCK(FocusOut)
    EVENT_BLOCK(FocusAboutToChange)
    EVENT_BLOCK(Enter)
    EVENT_BLOCK(Leave)
    EVENT_BLOCK(Paint)
    EVENT_BLOCK(Move)
    EVENT_BLOCK(Resize)
    EVENT_BLOCK(Create)
    EVENT_BLOCK(Destroy)
    EVENT_BLOCK(Show)
    EVENT_BLOCK(Hide)
    EVENT_BLOCK(Close)
    EVENT_BLOCK(Quit)
    EVENT_BLOCK(ParentChange)
    EVENT_BLOCK(ParentAboutToChange)
    EVENT_BLOCK(ThreadChange)
    EVENT_BLOCK(WindowActivate)
    EVENT_BLOCK(WindowDeactivate)
    EVENT_BLOCK(ShowToParent)
    EVENT_BLOCK(HideToParent)
    EVENT_BLOCK(Wheel)
    EVENT_BLOCK(WindowTitleChange)
    EVENT_BLOCK(WindowIconChange)
    EVENT_BLOCK(ApplicationWindowIconChange)
    EVENT_BLOCK(ApplicationFontChange)
    EVENT_BLOCK(ApplicationLayoutDirectionChange)
    EVENT_BLOCK(ApplicationPaletteChange)
    EVENT_BLOCK(PaletteChange)
    EVENT_BLOCK(Clipboard)
    EVENT_BLOCK(Speech)
    EVENT_BLOCK(MetaCall)
    EVENT_BLOCK(SockAct)
    EVENT_BLOCK(WinEventAct)
    EVENT_BLOCK(DeferredDelete)
    EVENT_BLOCK(DragEnter)
    EVENT_BLOCK(DragMove)
    EVENT_BLOCK(DragLeave)
    EVENT_BLOCK(Drop)
    EVENT_BLOCK(DragResponse)
    EVENT_BLOCK(ChildAdded)
    EVENT_BLOCK(ChildPolished)
    EVENT_BLOCK(ChildRemoved)
    EVENT_BLOCK(ShowWindowRequest)
    EVENT_BLOCK(PolishRequest)
    EVENT_BLOCK(Polish)
    EVENT_BLOCK(LayoutRequest)
    EVENT_BLOCK(UpdateRequest)
    EVENT_BLOCK(UpdateLater)

    EVENT_BLOCK(EmbeddingControl)
    EVENT_BLOCK(ActivateControl)
    EVENT_BLOCK(DeactivateControl)
    EVENT_BLOCK(ContextMenu)
    EVENT_BLOCK(InputMethod)
    EVENT_BLOCK(TabletMove)
    EVENT_BLOCK(LocaleChange)
    EVENT_BLOCK(LanguageChange)
    EVENT_BLOCK(LayoutDirectionChange)
    EVENT_BLOCK(Style)
    EVENT_BLOCK(TabletPress)
    EVENT_BLOCK(TabletRelease)
    EVENT_BLOCK(OkRequest)
    EVENT_BLOCK(HelpRequest)

    EVENT_BLOCK(IconDrag)

    EVENT_BLOCK(FontChange)
    EVENT_BLOCK(EnabledChange)
    EVENT_BLOCK(ActivationChange)
    EVENT_BLOCK(StyleChange)
    EVENT_BLOCK(IconTextChange)
    EVENT_BLOCK(ModifiedChange)
    EVENT_BLOCK(MouseTrackingChange)

    EVENT_BLOCK(WindowBlocked)
    EVENT_BLOCK(WindowUnblocked)
    EVENT_BLOCK(WindowStateChange)

    EVENT_BLOCK(ReadOnlyChange)

    EVENT_BLOCK(ToolTip)
    EVENT_BLOCK(WhatsThis)
    EVENT_BLOCK(StatusTip)

    EVENT_BLOCK(ActionChanged)
    EVENT_BLOCK(ActionAdded)
    EVENT_BLOCK(ActionRemoved)

    EVENT_BLOCK(FileOpen)

    EVENT_BLOCK(Shortcut)
    EVENT_BLOCK(ShortcutOverride)

    EVENT_BLOCK(WhatsThisClicked)

    EVENT_BLOCK(ToolBarChange)

    EVENT_BLOCK(ApplicationActivate)
    EVENT_BLOCK(ApplicationDeactivate)

    EVENT_BLOCK(QueryWhatsThis)
    EVENT_BLOCK(EnterWhatsThisMode)
    EVENT_BLOCK(LeaveWhatsThisMode)

    EVENT_BLOCK(ZOrderChange)

    EVENT_BLOCK(HoverEnter)
    EVENT_BLOCK(HoverLeave)
    EVENT_BLOCK(HoverMove)

#ifdef QT_KEYPAD_NAVIGATION
    EVENT_BLOCK(EnterEditFocus)
    EVENT_BLOCK(LeaveEditFocus)
#endif
    EVENT_BLOCK(AcceptDropsChange)

    EVENT_BLOCK(ZeroTimerEvent)

    EVENT_BLOCK(GraphicsSceneMouseMove)
    EVENT_BLOCK(GraphicsSceneMousePress)
    EVENT_BLOCK(GraphicsSceneMouseRelease)
    EVENT_BLOCK(GraphicsSceneMouseDoubleClick)
    EVENT_BLOCK(GraphicsSceneContextMenu)
    EVENT_BLOCK(GraphicsSceneHoverEnter)
    EVENT_BLOCK(GraphicsSceneHoverMove)
    EVENT_BLOCK(GraphicsSceneHoverLeave)
    EVENT_BLOCK(GraphicsSceneHelp)
    EVENT_BLOCK(GraphicsSceneDragEnter)
    EVENT_BLOCK(GraphicsSceneDragMove)
    EVENT_BLOCK(GraphicsSceneDragLeave)
    EVENT_BLOCK(GraphicsSceneDrop)
    EVENT_BLOCK(GraphicsSceneWheel)

    EVENT_BLOCK(KeyboardLayoutChange)

    EVENT_BLOCK(DynamicPropertyChange)

    EVENT_BLOCK(TabletEnterProximity)
    EVENT_BLOCK(TabletLeaveProximity)

    EVENT_BLOCK(NonClientAreaMouseMove)
    EVENT_BLOCK(NonClientAreaMouseButtonPress)
    EVENT_BLOCK(NonClientAreaMouseButtonRelease)
    EVENT_BLOCK(NonClientAreaMouseButtonDblClick)

    EVENT_BLOCK(MacSizeChange)

    EVENT_BLOCK(ContentsRectChange)

    EVENT_BLOCK(MacGLWindowChange)

    EVENT_BLOCK(FutureCallOut)

    EVENT_BLOCK(GraphicsSceneResize)
    EVENT_BLOCK(GraphicsSceneMove)

    EVENT_BLOCK(CursorChange)
    EVENT_BLOCK(ToolTipChange)

    EVENT_BLOCK(NetworkReplyUpdated)

    EVENT_BLOCK(GrabMouse)
    EVENT_BLOCK(UngrabMouse)
    EVENT_BLOCK(GrabKeyboard)
    EVENT_BLOCK(UngrabKeyboard)
    EVENT_BLOCK(MacGLClearDrawable)

    EVENT_BLOCK(StateMachineSignal)
    EVENT_BLOCK(StateMachineWrapped)

    EVENT_BLOCK(TouchBegin)
    EVENT_BLOCK(TouchUpdate)
    EVENT_BLOCK(TouchEnd)

#ifndef QT_NO_GESTURES
    EVENT_BLOCK(NativeGesture)
#endif
    EVENT_BLOCK(RequestSoftwareInputPanel)
    EVENT_BLOCK(CloseSoftwareInputPanel)

    EVENT_BLOCK(WinIdChange)
#ifndef QT_NO_GESTURES
    EVENT_BLOCK(Gesture)
    EVENT_BLOCK(GestureOverride)
#endif
    EVENT_BLOCK(ScrollPrepare)
    EVENT_BLOCK(Scroll)

    EVENT_BLOCK(Expose)

    EVENT_BLOCK(InputMethodQuery)
    EVENT_BLOCK(OrientationChange)

    EVENT_BLOCK(TouchCancel)

    EVENT_BLOCK(ThemeChange)

    EVENT_BLOCK(SockClose)

    EVENT_BLOCK(PlatformPanel)

    EVENT_BLOCK(StyleAnimationUpdate)
    EVENT_BLOCK(ApplicationStateChange)

    EVENT_BLOCK(WindowChangeInternal)
    EVENT_BLOCK(ScreenChangeInternal)

    EVENT_BLOCK(PlatformSurface)

    EVENT_BLOCK(Pointer)
    EVENT_BLOCK(TabletTrackingChange)
#undef EVENT_BLOCK
  // Also specify these two, even though we don't care about them
  // specifically, to disable non-exhaustive warnings. This makes it easier
  // to notice missing enum cases in the future.
  case QEvent::User:
  case QEvent::MaxUser:
    break;
  }
  {
    EASY_BLOCK("E: Other");
    return QApplication::notify(receiver, e);
  }
}
#endif // BUILD_WITH_EASY_PROFILER
