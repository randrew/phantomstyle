> And some say it's still using desktop computers, even to this day 👻

![phantom screenshot light](https://raw.githubusercontent.com/wiki/randrew/phantomstyle/images/phantom_demo_1x_light_3.png)

![phantom screenshot dark](https://raw.githubusercontent.com/wiki/randrew/phantomstyle/images/phantom_demo_1x_dark_3.png)

[More screenshots](https://github.com/randrew/phantomstyle/wiki/Comparison-Screenshots)

## Phantom Style

Phantom is a QStyle for Qt which began as an overhaul of QFusionStyle. Similar
to Fusion, it's designed to be a looks-the-same cross-platform style. It looks
native to nobody, but familiar to many. It has the visual appearance of a
traditional GUI, and does not adopt a "modern flat" style. Compared to Fusion,
it has many fixes, objective improvements, and subjective improvements:

* [Usage](#usage)
* [Compatibility](#compatibility)
* [Changes from QFusionStyle](#changes-from-qfusionstyle)
* [License](#license)
* [TODO](#todo)

## Usage

### Built into an application

Add `src/phantom/phantom.pri` to your qmake .pro file for your project. There
are no additional dependencies. It's also safe to construct a PhantomStyle
object before instantiating a QApplication, because it doesn't interact with
the environment or anything else.

### As a QStylePlugin

A style plugin is available: [phantomstyleplugin.pro](src/styleplugin/phantomstyleplugin.pro)

## Compatibility

Tested on Qt 5.9 and later, but should work on earlier versions as well. Builds
with MSVC (tested with 2017), GCC and clang.

Uses `auto` from C++11, so C++11 is needed. C++14 and later are not needed.

## Changes from QFusionStyle

* Fixed many code and logic errors: unaligned reads/writes, dead and
  unreachable code paths, redundant allocations, unused variables.

* Fixed many drawing mistakes: filled regions which are never seen, off-by-1
  and misalignment, unnecessary QPainter transformations, unnecessary use of
  anti-aliasing for solid rectangles, misaligned arrows in scrollbar buttons
  and spinboxes, garbage lines and artifacts in the grooves of scrollbars.

* Fixed bad drawing at high DPI: QPen lines which are misaligned, incorrect
  line thickness, broken and interrupted lines between connected elements (tabs
  and tab bars, etc.), misaligned or disconnect outlines and their associated
  inner fills, incorrect scaling of certain parts of a shape and others
  unscaled, unnecessary use of QPen anti-aliased lines to draw straight
  rectangles of constant width.

* Fixed bad drawing in right-to-left layout: borders and outlines on the wrong
  side of rectangles (headers in item views, spinboxes, line edit borders),
  edges and off-by-1 adjustments made to bounding rectangles (tab frame and tab
  shapes, menu bar rulers, toolbar separators, grip handles), misalignment of
  icons and shapes (indicators in menu items, check boxes, radio button
  labels), clipped and invisible text (progress bar labels.)

* Fixed broken metrics and sizing calculations for menu items, which over time
  lead to QFusionStyle having to have more and more "safety space" added to the
  horizontal size of menu items to avoid clipping stuff off. Phantom has
  correct sizing of menu items, and doesn't make menus any wider than
  necessary.

* Replaced many constant sizes and pixel metrics with font-based calculations:
  menu items (and more) now derive their metrics from the font being used, so
  that they look more consistent across platforms which may use fonts for menus
  that are distinct from other widgets. A constant, even when DPI scaled, may
  give too little or too much space when the font size varies across a larger
  range than you predicted.

* Removed all use of QPixmapCache.

  * QFusionStyle would aggressively cache the results of drawing certain shapes
    (buttons shapes, for example) based on the input parameters of the style
    option (size, state, palette, etc.) While this would speed up subsequent
    repaints with the same input parameters, the initial painting is slower.

  * QFusionStyle's use of QPixmapCache would lead to full occupancy of the
    global QPixmapCache almost immediately: create a window with a few buttons,
    then drag-resize the window. Within a few moments, all 10 megabytes of the
    default QPixmapCache have been filled. Not only does this bloat memory
    usage if the QPixmapCache would otherwise not have been used, but it causes
    legitimate uses of the QPixmapCache to have their contents evicted on a
    regular basis.

  * QFusionStyle's use of QPixmapCache requires allocating and deallocating
    string keys alongside what should have been simple painting operations.

  * QFusionStyle's generated cache keys were too fragile: in several cases, the
    cached pixmap would never be re-used, because the calculated cache key
    would never be the same on subsequent calls to draw the widget.

  * PhantomStyle draws significantly faster than QFusionStyle, and the caching
    is no longer needed.

* Removed all use of gradients and explicit alpha blending.

  * QPainter has no color management, and on pixel buffers, blends in unmanaged
    8-bit color. This means that blending operations between two colors (for
    example, a gradient, or an alpha blend of one color on top of another)
    produce unintuitive results. While your gradient that you chose and tested
    with a light color scheme might appear fine, when used with a QPalette with
    darker colors, the results may have far too little or too much contrast.
    Hue shifting and unintended darkening or lightening also may occur.

  * QPainter has no dithering capabilities, so banding would occur.

  * QPainter's gradients and alpha blending are slow.

  * The alpha blending done by QFusionStyle was almost always between two
    constant colors that were known ahead of time, such as a shadow on top of a
    base color, or a groupbox background on top of a window. The resulting
    blended color could instead simply be calculated ahead of time and painted
    as a solid rectangle, which is faster and can be color-corrected.

  * Overuse of gradients makes QFusionStyle look like it's from a specific time
    period (mid-2000s) instead of no time period at all.

  * Note that hue shifting and lightness shifting will still occur on the edges
    of anti-aliased shapes, like roundrect corners. This can only be solved by
    QPainter being changed to perform color-correct blending.

* Changed derived color calculations to use CIELUV-like colorspace

    * QColor's .darker() and .lighter() were used by QFusionStyle to calculate
      derived colors from another color. For example, outlines on a box, or
      highlights on the inside of edges. QColor's .darker(), .lighter(),
      .lightness(), and other functions have no rigor or defined meaning -- the
      numbers are arbitrary and the output is unpredictable except when the
      input color is similar to whatever the programmer or designer tested it
      with. Using .lighter(120) on a near-black color will produce a different
      amount of contrast than .lighter(120) on a brighter color.

    * PhantomStyle instead uses a pseudo-CIELUV colorspace to derive its
      colors, provided by some core code from the hsluv-c library. While not
      perfect, it's a significant improvement, and allows PhantomStyle to more
      consistently work with both light and dark QPalettes.

* Removed many implicit QPen and QBrush allocations caused by calling
  setBrush() and setPen() with QColor arguments. Instead, QPen and QBrush
  instances are now persisted in a small cache (in small flat array, not a
  QHash) that uses an accurate QPalette hash key calculation.
  (QPalette::cacheKey() is not used, because it is prone to changing even when
  the underlying values are the same.) This saves many, many small heap
  allocations that would occur when QFusionStyle was performing painting
  operations.

* Disabled animations.

  * Though there are not many uses of animations in QtWidgets, they could cause
    problems. For example, dragging a QToolBar from its location in a
    QMainWindow to another location would attempt to animate the layout changes
    in the UI. But for complicated UIs in a large window, this would be too
    slow to re-layout and repaint in realtime, and the UI would freeze up
    during the time it should have been animating. This could cause the drop
    zone detection to give incorrect results, and then the UI would both
    stutter spastically *and* repeatedly freeze up during the drag operation.

* Disabled and removed most mouse-over/hover repainting.

  * QFusionStyle, for many widgets, would paint with different colors when the
    user moused over certain elements, like buttons. However, on modern
    composited desktops and especially when combined with event coalescing and
    hardware-accelerated mouse drawing that skips the main compositing path,
    this would cause the repainting of widgets to appear to occur long after
    the mouse had already passed over the widget. The result would be a subtle
    and persistent feeling of lag throughout in the UI.
    
  * For some widgets, QFusionStyle's alternate painting in the mouseover state
    was either not noticeable or identical, resulting in redundant repainting
    and event dispatching as the user moved their mouse cursor across the UI.

  * `Qt::WA_Hover` and alternate painting is still used where it makes good
    sense: menu items, tool buttons, and a few other cases.

* Fixed style hints which affected the operation of QMenus.

  * QFusionStyle specified "sloppy" submenu closing via
    `SH_Menu_SloppySubMenus`, but didn't also specify that the submenus should
    not be closed after a timeout if nothing else is moused over
    (`SH_Menu_SubMenuDontStartSloppyOnLeave`). It also did not specify
    `SH_Menu_SubMenuUniDirection` and several other hints which should have
    been specified, which would cause the reactions of a QMenu to appear to lag
    behind the user's movements or to close submenus unnecessarily.

* Fixed QMenuBar items not being highlighted when in alt-key navigation mode.

  * QFusionStyle specified the style hint allowing alt-key navigation for menu
    bars (`SH_MenuBar_AltKeyNavigation`) but did not actually draw the focused
    or highlighted menu bar item after the user had tapped the alt key. This
    would cause Windows and Linux users to assume that alt key navigation did
    not work in the program (because it had no visible indication that alt key
    navigation mode had been entered) when in fact it actually did have an
    effect, and would also cause the subsequent keypress on the keyboard to be
    eaten by the QMenuBar.

* Altered the metrics of many widgets so that they align correctly.

  * Combo boxes are now the same height as push buttons, instead of being
    off-by-1-or-2.

  * Spinboxes are now the same height as line edits.

  * Decorations in item view items are now the same height as a line of text by
    default, so that decorated and undecorated items do not have differing row
    heights. (Manual specification of decoration size still works.)

  * Check marks and radio indicators are now visible alongside the icons in
    menu items, if both are specified.

* The border around the "current" item in an item view is now drawn in a way
  that is actually visible, and is only drawn if necessary. The "current" focus
  rect will not be drawn if there there is only one item selected and the
  selected item is also the current item.

* Added editable, compile-time parameters that control the styling of various
  things by editing a single constant in the source file:

  * Ratios for font-derived spacing and margins in menu items, line edits,
    check boxes, etc.

  * Separate and controllable roundrect radius for many widgets: group boxes,
    buttons, tool buttons, etc.

  * An alternate, faster code path using solid rect fills instead of
    anti-aliased roundrect is taken when a widget's rounding is set to 0 or
    near-0.

  * Internal "sunken" shadows on some large widgets (line edit, spinbox,
    progress bar) can be enabled or disabled.

  * Internal shadow can also be enabled or disabled for checkboxes and radio
    buttons.

  * Shadows in scrollbars can be enabled or disabled.

  * Tree view branch indicators can be made flush to the margin of the view
    (Classic Mac OS style) or aligned to the text of the item.

  * Item view decorations can be included in the visibly selected region or
    not.

  * Auto-raise for tool buttons in a tool bar by default can be enabled or
    disabled.

  * Use of QMenu or the Windows-style disclosure menu for combo boxes can be
    enabled or disabled.

  * Default decoration sizes based on fonts for item views can be enabled or
    disabled (when disabled, uses the default small pixmap size.)

* No use of private Qt classes or code.

* No warnings when building with -Wall.

## License

LGPL 2.1.

I would prefer to give it a more permissive license, or the same license that
the official code Qt has, which allows commercial projects to use the code
without LGPL restrictions if they have a Qt license. However, I don't know how
to do this, and I don't have time at the moment to figure it out. Please
contact me or open a ticket if you can help with this. The PhantomStyle code
originally started as a copy-and-paste of the Fusion code, but nearly none of
the Fusion code remains at this point (just some stuff for drawing MDI window
decorations and QDial.)

## TODO

* More screenshots
* Several things haven't been fully tested (MDI windows, tick marks on sliders,
  a few more I can't think of.)
* Probably lots of bugs

```
Phantom Style
Copyright (C) 2019 Andrew Richards

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with this library; if not, write to the
Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
Boston, MA  02110-1301, USA.
```
