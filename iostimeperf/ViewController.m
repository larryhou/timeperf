//
//  ViewController.m
//  iostimeperf
//
//  Created by larryhou on 2023/4/20.
//

#import "ViewController.h"
#import "test.hpp"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidAppear: (BOOL) animated {
    [super viewDidAppear: animated];
    runtest();
};


@end
