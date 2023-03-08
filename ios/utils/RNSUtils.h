#ifndef RNSUtils_h
#define RNSUtils_h

#import "../RNSEnums.h"

class RNSUtils final {
  RNSUtils() = delete;
  ~RNSUtils() = delete;

 public:
  static int getDefaultHeaderHeight(int topInset, RNSScreenStackPresentation stackPresentation)
  {
    const int formSheetModalHeight{56};
    int headerHeight{64};
    int statusBarHeight = topInset;

    UIInterfaceOrientation orientation = UIInterfaceOrientationUnknown;
    // to jest risky, bo mogą być case'y w których dostaniemy nulle...
    // więc mamy mniejsze reliability niż w kodzie JS"owym.
    if (@available(iOS 13.0, *)) {
      const auto orientation =
          [[[[[UIApplication sharedApplication] delegate] window] windowScene] interfaceOrientation];
    }
    const bool isLandscape = UIInterfaceOrientationIsLandscape(orientation);

    const bool isFormSheetModal = stackPresentation == RNSScreenStackPresentationModal ||
        stackPresentation == RNSScreenStackPresentationFormSheet;

    if (!isLandscape && isFormSheetModal) {
      statusBarHeight = 0;
    }

    // check for isPad is TV
    UIUserInterfaceIdiom interfaceIdiom = [[UIDevice currentDevice] userInterfaceIdiom];
    if (interfaceIdiom == UIUserInterfaceIdiomPad || interfaceIdiom == UIUserInterfaceIdiomTV) {
      headerHeight = isFormSheetModal ? formSheetModalHeight : 50;
    } else if (isLandscape) {
      headerHeight = 32;
    } else {
      headerHeight = isFormSheetModal ? formSheetModalHeight : 44;
    }

    return headerHeight + statusBarHeight;
  }
};

#endif /* RNSUtils_h */
