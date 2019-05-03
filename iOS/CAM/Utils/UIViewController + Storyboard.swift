//
//  UIViewController + Extension.swift
//  CAM
//
//  Created by Egor Brel on 4/29/19.
//

import UIKit

public extension UIViewController {
    class func instantiateVC() -> Self {
        return initFromStoryboard()
    }
    
    private class func initFromStoryboard<T>() -> T {
        let bundle = Bundle(for: T.self as! AnyClass)
        return UIStoryboard.init(name: String(describing: T.self), bundle: bundle).instantiateViewController(withIdentifier: String(describing: T.self)) as! T
    }
    
    class var topMostViewController: UIViewController? {
        guard let window = UIApplication.shared.delegate?.window , let rootViewController = window?.rootViewController else {
            return nil
        }
        
        var top: UIViewController = rootViewController
        while let newTop = top.presentedViewController {
            top = newTop
        }
        
        return top
    }
}
