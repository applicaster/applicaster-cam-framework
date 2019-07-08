//
//  Result.swift
//  CAM
//
//  Created by Roman Karpievich on 7/4/19.
//

import Foundation

public enum Result<Success> {
    case success(Success)
    case failure(Error)
}

extension Result where Success == Void {
    public static var success: Result {
        return .success(())
    }
}

public typealias AvailableProductsResult = Result<[String]>
public typealias LoginResult = Result<Void>
public typealias SignupResult = Result<Void>
public typealias PurchaseResult = Result<Void>
