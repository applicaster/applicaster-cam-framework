//
//  AuthFieldsJsonParser.swift
//  CAMFramework
//
//  Created by Egor Brel on 4/24/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import Foundation

enum AuthFieldInputType: String, Codable {
    case text = "text"
    case password = "password"
    case number = "number"
    case unknown
    
    public init(from decoder: Decoder) throws {
        self = try AuthFieldInputType(rawValue: decoder.singleValueContainer().decode(RawValue.self)) ?? .unknown
    }
}

struct AuthField: Codable {
    let key: String?
    let title: String?
    let hint: String?
    let type: AuthFieldInputType
    let mandatory: Bool
}

struct AuthorizationFields: Codable {
    let array: [AuthField]?
}
