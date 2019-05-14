//
//  AuthFieldsJsonParser.swift
//  CAMFramework
//
//  Created by Egor Brel on 4/24/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import Foundation

struct AuthFields : Codable {
    let signup : [AuthField]?
    let login : [AuthField]?
    
    enum CodingKeys: String, CodingKey {
        case signup = "signup"
        case login = "login"
    }
}

enum AuthFieldInputType: String, Codable {
    case text = "TEXT"
    case password = "PASSWORD"
    case number = "NUMBER"
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
    var text: String?
}
