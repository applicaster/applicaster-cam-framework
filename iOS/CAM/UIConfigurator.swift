//
//  CustomizableFields.swift
//  CAM
//
//  Created by Egor Brel on 5/10/19.
//

import UIKit
import ZappPlugins

extension ZAAppConnector {
    func image(forAsset asset: String) -> UIImage? {
        
        if let image = UIImage(named: asset) {
            return image
        } else if let image = UIImage(named: asset, in: self.layoutsStylesDelegate.zappLayoutsStylesBundle(), compatibleWith: nil) {
            return image
        } else if let url = self.urlDelegate.fileUrl(withName: asset, extension: "png") {
            if let image = UIImage(contentsOfFile: url.path) ?? UIImage(contentsOfFile: url.absoluteString) {
                return image
            } else if let data = try? Data(contentsOf: url), let image = UIImage(data: data, scale: 0) {
                return image
            } else {
                return nil
            }
        } else { return nil }
    }
}

extension UIView {
    func setZappStyle(withBackgroundColor color: CAMStyles) {
        ZAAppConnector.sharedInstance().layoutsStylesDelegate.setViewStyle?(self, withKeys: [kZappLayoutStylesBackgroundColorKey: color.rawValue])
    }
}

extension UIImageView {
    func setZappStyle(withAsset asset: CAMKeys,
                      stretchableImage: Bool = false) {
        ZAAppConnector.sharedInstance().layoutsStylesDelegate.setViewStyle?(self, withKeys: [kZappLayoutStylesBackgroundImageKey: asset.rawValue])
        if stretchableImage, let image = self.image {
            let halfSize = CGSize(width: (image.size.width * 0.5) - 0.5, height: (image.size.height * 0.5) - 0.5)
            self.image = image.resizableImage(withCapInsets: UIEdgeInsets(top: halfSize.height, left: halfSize.width, bottom: halfSize.height, right: halfSize.width))
        }
    }
}

extension UIButton {
    func setZappStyle(withIconAsset iconAsset: CAMKeys? = nil,
                      backgroundAsset: CAMKeys? = nil,
                      title: String? = nil,
                      style: CAMStyles? = nil,
                      forState state: UIControl.State = .normal) {
        
        if let iconAsset = iconAsset?.rawValue, let imageIcon = ZAAppConnector.sharedInstance().image(forAsset: iconAsset) {
            self.setImage(imageIcon, for: state)
        }
        
        if let style = style?.rawValue, let dict = ZAAppConnector.sharedInstance().layoutsStylesDelegate.styleParams?(byStyleName: style) as? [String: Any] {
            if state == .normal, let font = dict["font"] as? UIFont {
                self.titleLabel?.font = font
            }
            
            if let color = dict["color"] as? UIColor {
                self.setTitleColor(color, for: state)
            }
        }
        
        self.setTitle(title, for: state)
        
        if let backgroundAsset = backgroundAsset?.rawValue, var image = ZAAppConnector.sharedInstance().image(forAsset: backgroundAsset) {
            let halfSize = CGSize(width: (image.size.width * 0.5) - 0.5, height: (image.size.height * 0.5) - 0.5)
            image = image.resizableImage(withCapInsets: UIEdgeInsets(top: halfSize.height, left: halfSize.width, bottom: halfSize.height, right: halfSize.width))
            self.setBackgroundImage(image, for: state)
        }
    }
    
    func setAttributedZappStyle(withIconAsset iconAsset: CAMKeys? = nil,
                                backgroundAsset: CAMKeys? = nil,
                                attributedTitle: [(style: CAMStyles?, string: String, additionalAttributes: [NSAttributedString.Key: Any]?)]? = nil,
                                forState state: UIControl.State = .normal) {
        
        if let iconAsset = iconAsset?.rawValue, let imageIcon = ZAAppConnector.sharedInstance().image(forAsset: iconAsset) {
            self.setImage(imageIcon, for: state)
        }
        
        let str = NSMutableAttributedString(string: "")
        if let attributedTitle = attributedTitle {
            for index in 0..<attributedTitle.count {
                let subTitle = attributedTitle[index]
                
                var attrs: [NSAttributedString.Key: Any] = subTitle.additionalAttributes ?? [:]
                if let style = subTitle.style?.rawValue, let dict = ZAAppConnector.sharedInstance().layoutsStylesDelegate.styleParams?(byStyleName: style) as? [String: Any] {
                    if let font = dict["font"] as? UIFont { attrs[.font] = font }
                    if let color = dict["color"] as? UIColor { attrs[.foregroundColor] = color }
                }
                
                let space = (index + 1 < attributedTitle.count ? " " : "")
                str.append(NSAttributedString(string: "\(subTitle.string)\(space)", attributes: attrs))
            }
        }
        
        setAttributedTitle(str, for: state)
    }
}

extension UILabel {
    func setZappStyle(text: String? = nil,
                      style: CAMStyles? = nil) {
        
        var keys: [String: String] = [:]
        if let style = style { keys[kZappLayoutStylesFontKey] = style.rawValue }
        
        ZAAppConnector.sharedInstance().layoutsStylesDelegate.setLabelStyle?(self, withKeys: keys)
        self.text = text
    }
    
    func setAttributedZappStyle(attributedText: [(style: CAMStyles?, string: String,
                                additionalAttributes: [NSAttributedString.Key: Any]?)]) {
        let str = NSMutableAttributedString(string: "")
        for index in 0..<attributedText.count {
            let subText = attributedText[index]
            
            var attrs: [NSAttributedString.Key: Any] = subText.additionalAttributes ?? [:]
            if let style = subText.style?.rawValue, let dict = ZAAppConnector.sharedInstance().layoutsStylesDelegate.styleParams?(byStyleName: style) as? [String: Any] {
                if let font = dict["font"] as? UIFont { attrs[.font] = font }
                if let color = dict["color"] as? UIColor { attrs[.foregroundColor] = color }
            }
            
            let space = (index + 1 < attributedText.count ? " " : "")
            str.append(NSAttributedString(string: "\(subText.string)\(space)", attributes: attrs))
        }
        
        self.attributedText = str
    }
}

extension UITextField {
    
    func setZappStyle(backgroundAsset: CAMKeys? = nil,
                      textStyle: CAMStyles? = nil,
                      placeholder: String? = nil) {
        
        if let backgroundAsset = backgroundAsset?.rawValue, let imageIcon = ZAAppConnector.sharedInstance().image(forAsset: backgroundAsset) {
            self.background = imageIcon
            self.borderStyle = .none
        }
        
        var placeholderStyle: [String: Any]?
        if let style = textStyle?.rawValue, let dict = ZAAppConnector.sharedInstance().layoutsStylesDelegate.styleParams?(byStyleName: style) as? [String: Any] {
            placeholderStyle = dict
            self.font = dict["font"] as? UIFont
            self.textColor = dict["color"] as? UIColor
        }
        
        if let placeholder = placeholder {
            if let placeholderStyle = placeholderStyle {
                var attrs: [NSAttributedString.Key: Any] = [:]
                if let font = placeholderStyle["font"] as? UIFont { attrs[.font] = font }
                if let color = placeholderStyle["color"] as? UIColor { attrs[.foregroundColor] = color.withAlphaComponent(0.6) }
                attributedPlaceholder = NSAttributedString(string: placeholder, attributes: attrs)
            } else {
                self.placeholder = placeholder
            }
        } else {
            self.placeholder = nil
        }
    }
    
    func configureInputField(data: AuthField) {
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
