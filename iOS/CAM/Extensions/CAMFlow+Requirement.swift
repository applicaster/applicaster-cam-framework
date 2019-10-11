//
//  CAMFlow+Requirement.swift
//  CAM
//
//  Created by Roman Karpievich on 7/26/19.
//

import Foundation

extension CAMFlow {
    mutating func update(with config: [String: String],
                         and currentState: (isAuthenticated: Bool, isPurchaseNeeded: Bool)) {
        let authRequirement = parseAuthRequirement(from: config)
        let paymentRequirement = parsePaymentRequirement(from: config)
        
        update(with: authRequirement,
               and: paymentRequirement)
        update(with: currentState)
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
    
    private mutating func update(with authRequirement: AuthRequirement,
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
            case .storefront:
                self = paymentRequirement == true ? .storefront : .no
            case .authAndStorefront:
                self = paymentRequirement == true ? .authAndStorefront : .authentication
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
    
    private mutating func update(with currentState: (isAuthenticated: Bool, isPurchaseNeeded: Bool)) {
        switch self {
        case .authentication:
            self = currentState.isAuthenticated ? .no : .authentication
        case .storefront:
            self = currentState.isPurchaseNeeded ? .no : .storefront
        case .authAndStorefront:
            switch (currentState.isAuthenticated, currentState.isPurchaseNeeded) {
            case (true, true):
                self = .no
            case (true, false):
                self = .storefront
            case (false, true):
                self = .authentication
            case (false, false):
                self = .authAndStorefront
            }
        case .no:
            break
        }
    }
}
