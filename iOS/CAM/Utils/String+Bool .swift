//
//  String + Bool .swift
//  CAM
//
//  Created by Egor Brel on 5/21/19.
//

import Foundation

extension String {
    var bool: Bool {
        switch self.lowercased() {
        case "true":
            return true
        case "false":
            return false
        default:
            return false
        }
    }
}
