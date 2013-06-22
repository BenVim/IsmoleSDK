//
//  WebView.m
//  Pay
//
//  Created by Ben on 6/18/13.
//
//

#import "WebView.h"

@implementation WebView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

-(void)openWeb:(NSString *)webURL
{
    NSURL *url =[NSURL URLWithString:webURL];
    NSURLRequest *request =[NSURLRequest requestWithURL:url];
    
    CGRect webFrame = CGRectMake(0, 0, 320, 480);
    UIWebView *webView = [[UIWebView alloc] initWithFrame:webFrame];
    [webView setBackgroundColor:[UIColor whiteColor]];//设置北京为白色
    webView.scalesPageToFit = YES;//适应屏幕大小
    [webView loadRequest:request];
    [self addSubview:webView];
    
    UIToolbar *toolBar = [[[UIToolbar alloc] initWithFrame:CGRectMake(0.0f, 440.0f, 320.0f, 40.0f) ] autorelease];
    [self addSubview:toolBar];
    
    //创建barbuttonitem
    UIBarButtonItem *item1 = [[[UIBarButtonItem alloc] initWithTitle:@"关闭" style:UIBarButtonItemStyleBordered target:self action:@selector(test:)] autorelease];
    [toolBar setItems:[NSArray arrayWithObjects:item1, nil] animated:YES];
}

-(void)test:(id)sender
{
    NSLog(@"ddd");
    [self removeFromSuperview];
}


@end
