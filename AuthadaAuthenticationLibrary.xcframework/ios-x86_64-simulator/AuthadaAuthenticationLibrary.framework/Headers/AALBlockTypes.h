//
//  AALBlockTypes.h
//  AAL
//
//  Created by Samuel Florian Strupp on 29.10.19.
//  Copyright © 2019 Authada GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "EIDSecret.h"

NS_ASSUME_NONNULL_BEGIN

typedef void (^AALImageCompletionBlock)( UIImage* __nullable image, BOOL cancel);
typedef void (^AALUseImageResultBlock)(BOOL useImage, BOOL cancel);
typedef void (^AALContinueBlock)(BOOL cancel);

typedef void (^AALSecretCompletionBlock)( EIDSecret* __nullable secret, BOOL cancel);
typedef void (^AALResultBlock)(BOOL result);

NS_ASSUME_NONNULL_END
