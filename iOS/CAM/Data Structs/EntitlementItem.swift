//
//  EntitlementItem.swift
//  CAMFramework
//
//  Created by Egor Brel on 4/25/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import Foundation

public struct CAMEntitlementItem {
    var title: String?
    var description: String?
    var price: String?
    var actionTitle: String?
    var isTrialAvailable: Bool = false
    var isRedeemCodeAvailable: Bool = false
}
