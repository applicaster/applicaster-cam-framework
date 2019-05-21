//
//  CustomizableFields.swift
//  CAM
//
//  Created by Egor Brel on 5/10/19.
//

import UIKit

extension UIButton {
    func configureWith(text: String? = nil, color: String? = "#FFFFFFFF", fontName: String? = nil, fontSize: String? = "12",
                       bgImageName: String? = nil, state: UIControl.State = .normal) {
        self.setTitle(text, for: state)
        self.setTitleColor(UIColor(hexRGBA: color), for: state)
        if let imageName = bgImageName, let image = UIImage(named: imageName) {
            self.setImage(image, for: state)
        }
//        if let fontName = fontName, let fontSize = Float(fontSize), let font = UIFont(name: fontName, size: fontSize) {
//            self.titleLabel?.font = font
//        }
    }
}

extension UIImageView {
    func configureWith(bgImageName: String? = nil) {
        if let imageName = bgImageName, let image = UIImage(named: imageName) {
            self.image = image
        }
    }
}

extension UILabel {
    func configureWith(text: String? = nil, color: String? = "#FFFFFFFF", fontName: String? = nil, fontSize: String? = "12") {
        self.text = text
        self.textColor = UIColor(hexRGBA: color)
//        if let fontName = fontName, let font = UIFont(name: fontName, size: fontSize) {
//            self.font = font
//        }
    }
}

extension UITextField {
    func configureWith(text: String? = nil, color: String? = "#FFFFFFFF", fontName: String? = nil, fontSize: String? = "12",
                       bgImageName: String? = nil, placeholder: String? = nil, inputType: AuthFieldInputType = .text) {
        self.text = text
        if let imageName = bgImageName, let image = UIImage(named: imageName) {
            self.background = image
        }
        self.textColor = UIColor(hexRGBA: color)
//        if let fontName = fontName, let font = UIFont(name: fontName, size: fontSize.float) {
//            self.font = font
//        }
        self.placeholder = placeholder
        self.clipsToBounds = true
        switch inputType {
        case .text, .unknown:
            self.keyboardType = .default
        case .number:
            self.keyboardType = .numberPad
        case .password:
            self.keyboardType = .default
            self.isSecureTextEntry = true
        }
    }
    
    func configureInputField(data: AuthField) {
        self.placeholder = data.hint
        self.text = data.text
        switch data.type {
        case .text, .unknown:
            self.keyboardType = .default
        case .number:
            self.keyboardType = .numberPad
        case .password:
            self.keyboardType = .default
            self.isSecureTextEntry = true
        }
    }
}
