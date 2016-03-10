#import "ViewController.h"

@implementation GLViewController

- (void)loadView 
{
    self.view = [[UIView alloc] initWithFrame:[UIScreen mainScreen].bounds];
}

-(void)viewDidLoad
{
    [super viewDidLoad];

    glView = [[EAGLView alloc] initWithFrame:[UIScreen mainScreen].bounds];
    glView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleBottomMargin;
    glView.userInteractionEnabled=YES;
    [glView initGLContext];
    [self.view addSubview:glView];
}

@end