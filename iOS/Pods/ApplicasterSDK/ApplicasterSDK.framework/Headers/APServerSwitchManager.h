//
//  APServerSwitchManager.h
//  applicaster
//
//  Created by Philip Kramarov on 7/1/13.
//  Copyright (c) 2013 Applicaster Ltd. All rights reserved.
//

typedef NS_ENUM(NSUInteger, APServerSwitchServerType) {
    APServerSwitchDefaultServer,
    APServerSwitchProductionServer,
    APServerSwitchDemoServer,
    APServerSwitchDevelopmentServer,
    APServerSwitchQAServer,
    APServerSwitchTestServer,
    APServerSwitchServerServer,
    APServerSwitchCustomServer
};

@interface APServerSwitchManager : NSObject

/**
 Applicaster settings server
 @returns The url of selected server in the settings server.
 */
+ (NSString *)applicasterSettingsServer;

/**
 Server type enum. Default server is set as APSettingProductionServer.
 Changing between servers in device settings will call exit(0) to restart application.
 @returns The enum @see APServerSwitchServerType of selected server in the settings of the device.
 */
+ (APServerSwitchServerType)serverType;

/**
 Override used servers used by applicaster services.
 @param serverType The enum @see APServerSwitchServerType of selected server.
 */
+ (void)overrideServerType:(APServerSwitchServerType)serverType;


@end
