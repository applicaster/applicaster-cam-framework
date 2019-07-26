//
//  CAMFlow+Requirement.swift
//  CAM
//
//  Created by Roman Karpievich on 7/26/19.
//

import Foundation

extension CAMFlow {
    mutating func update(with config: [String: String]) {
        let authRequirement = parseAuthRequirement(from: config)
        let paymentRequirement = parsePaymentRequirement(from: config)
        
        updateFlow(with: authRequirement,
                   and: paymentRequirement)
    }
    
    // MARK: - Private methods
    
    private func parseAuthRequirement(from config: [String: String]) -> AuthRequirement {
        let rawValue = config[AuthRequirement.key] ?? ""
        let result = AuthRequirement(rawValue: rawValue) ?? .always
        
        return result
    }
    
    private func parsePaymentRequirement(from config: [String: String]) -> Bool {
        let rawValue = config[CAMKeys.paymentRequirement.rawValue] ?? ""
        let result = Bool(rawValue) ?? true
        
        return result
    }
    
    private mutating func updateFlow(with authRequirement: AuthRequirement,
                            and paymentRequirement: Bool) {
        switch authRequirement {
        case .never:
            switch self {
            case .authentication, .no:
                self = .no
            case .storefront, .authAndStorefront:
                self = paymentRequirement == true ? .storefront : .no
            }
        case .always:
            switch self {
            case .authentication, .no:
                break
            case .storefront, .authAndStorefront:
                self = paymentRequirement == true ? .authAndStorefront : .no
            }
        case .purchasableItems:
            switch self {
            case .authentication, .authAndStorefront, .no:
                break
            case .storefront:
                self = paymentRequirement == true ? .authAndStorefront : .no
            }
        case .dataSourceBased:
            switch self {
            case .authentication, .no:
                break
            case .storefront, .authAndStorefront:
                if paymentRequirement == false {
                    self = .no
                }
            }
        }
    }
}
