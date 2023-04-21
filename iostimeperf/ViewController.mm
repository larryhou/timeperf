//
//  ViewController.m
//  iostimeperf
//
//  Created by larryhou on 2023/4/20.
//

#import "ViewController.h"
#import "test.hpp"
#import "timeperf.hpp"
#include <sstream>

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidAppear: (BOOL) animated {
    [super viewDidAppear: animated];
    timeperf::enter(0);
    runtest();
    std::stringstream ss;
    timeperf::exit()->dump(ss);
    NSString* report = [NSString stringWithUTF8String:ss.str().c_str()];
    NSLog(@"Summary:\n%@", report);
};


@end
