#import <UIKit/UIKit.h>
#import "EAGLView.h"

@interface GLViewController : UIViewController
{
    EAGLView *glView;
}
@property(nonatomic, retain) /*IBOutlet*/ EAGLView *glView;
@end
