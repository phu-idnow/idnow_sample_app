//
//  EIDSecret.h
//  EIDcore
//
//  Created by Samuel Strupp on 24.04.18.
//  Copyright © 2018 Authada GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum : int8_t {
    eIDKeyReference_Unknown = 0,
    eIDKeyReference_MRZ = 1,
    eIDKeyReference_CAN = 2,
    eIDKeyReference_PIN = 3,
    eIDKeyReference_PUK = 4
} EIDKeyReference;

NS_ASSUME_NONNULL_BEGIN

@interface EIDSecret : NSObject

-(instancetype) initWithLengthOfSecret:(NSUInteger)lengthOfSecret;
-(instancetype) initWithLengthOfSecret:(NSUInteger)lengthOfSecret
                            secretType:(EIDKeyReference)type;

@property(nonatomic, readonly) NSUInteger lengthOfSecret;
@property(readonly) EIDKeyReference secretType;

//ISO/IEC 8859-1 character set. (see TR-03110 D2.1.4. Character Strings)
-(BOOL) setCharacter:(char)character atIndex:(NSUInteger)charIndex; //returns NO when index out of bounds
-(char) characterAtIndex:(NSUInteger)charIndex; //returns 0 when not set or index out of bounds
-(void) reset; //reset secret to empty

-(BOOL)isEqualToSecret:(EIDSecret*)secret;

@end

NS_ASSUME_NONNULL_END
