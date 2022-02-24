//
//  AALPinPadViewController.h
//  AuthadaAuthenticationLibrary
//
//  Created by Samuel Florian Strupp on 02.07.19.
//  Copyright © 2019 Authada GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "EIDSecret.h"

@class AALPinPadViewController;

NS_ASSUME_NONNULL_BEGIN

@protocol AALPinPadViewControllerDelegate <NSObject>

-(void) pinPadFinishedWithSecret:(EIDSecret*)secret pinPad:(AALPinPadViewController*)pinPad;

@optional

-(void) pinPadCanceled:(AALPinPadViewController*)pinPad;
-(void) pinPadDidAppear:(AALPinPadViewController*)pinPad;

@end



@interface AALPinPadViewController : UIViewController

-(void) addSecret:(EIDSecret *)secret withDescriptionKey:(NSString*)descKey;
-(void) addCustomButtonWithTitle:(nullable NSString*)titel image:(nullable UIImage*)image target:(id)target selector:(SEL)action;
@property (nonatomic, weak) id<AALPinPadViewControllerDelegate> pinPadDelegate;

-(void) setPINLabel:(NSString*)pinLabel;

//Identifier
@property(nonatomic, nullable) NSString* identifier;

//Colors
@property(nonatomic, nullable) UIColor *pinPadBackgroundColor;
@property(nonatomic, nullable) UIColor *controlButtonsColor;
@property(nonatomic, nullable) UIColor *secretColor;

//Font
@property UIFont *controlButtonsFont;

@end

NS_ASSUME_NONNULL_END
