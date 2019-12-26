//
//  CamLinksView.swift
//  CAM
//
//  Created by Egor Brel on 12/26/19.
//

import UIKit

class CamLinksView: UIView {
    
    
    @IBOutlet var camLinksStackView: UIStackView!
    
    public var camLinkKeys = [(text: CAMKeys, link: CAMKeys)]()
    
    private var configDictionary = [String: String]() {
        didSet {
            configureStackView()
        }
    }
    
    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)

        guard let view = loadViewFromNib() else { return }
        view.frame = self.bounds
        self.addSubview(view)
    }

    private func loadViewFromNib() -> UIView? {
        let bundle = Bundle(for: type(of: self))
        let nib = UINib(nibName: "CamLinksView", bundle: bundle)
        return nib.instantiate(withOwner: self, options: nil).first as? UIView
    }
    
    public func setupParameters(camLinkKeys: [(text: CAMKeys, link: CAMKeys)],
                                configDictionary: [String: String]) {
        self.camLinkKeys = camLinkKeys
        self.configDictionary = configDictionary
    }
    
    private func configureStackView() {
        if camLinkKeys.count != 2 {
            return
        }
        let linkButtonFirst = UIButton()
        let linkButtonSecond = UIButton()
        if let link = configDictionary[camLinkKeys[0].link.rawValue], !link.isEmpty,
           let linkText = configDictionary[camLinkKeys[0].text.rawValue], !linkText.isEmpty {
            linkButtonFirst.addTarget(self, action: #selector(showFirstCustomLink), for: .touchUpInside)
            linkButtonFirst.titleLabel?.lineBreakMode = .byTruncatingTail
            linkButtonFirst.setStyle(config: configDictionary, camTitleKey: camLinkKeys[0].text, style: .customlinkFont)
            camLinksStackView.addArrangedSubview(linkButtonFirst)
        }
        
        if let link = configDictionary[camLinkKeys[1].link.rawValue], !link.isEmpty,
           let linkText = configDictionary[camLinkKeys[1].text.rawValue], !linkText.isEmpty {
            linkButtonSecond.addTarget(self, action: #selector(showSecondCustomLink), for: .touchUpInside)
            linkButtonSecond.titleLabel?.lineBreakMode = .byTruncatingTail
            linkButtonSecond.setStyle(config: configDictionary, camTitleKey: camLinkKeys[1].text, style: .customlinkFont)
            camLinksStackView.addArrangedSubview(linkButtonSecond)
        }
        if camLinksStackView.subviews.count == 2 {
            linkButtonFirst.contentHorizontalAlignment = .right
            linkButtonSecond.contentHorizontalAlignment = .left
        }
        camLinksStackView.axis = .horizontal
        camLinksStackView.spacing = 5.0
        camLinksStackView.distribution = .fillEqually
        camLinksStackView.alignment = .center
    }
    
    @objc private func showFirstCustomLink() {
        guard let link = configDictionary[CAMKeys.loginScreenFirstCustomLink.rawValue],
              let customURL = URL(string: link) else {
            return
        }

        if UIApplication.shared.canOpenURL(customURL) {
            UIApplication.shared.open(customURL)
        }
    }
    
    @objc private func showSecondCustomLink() {
        guard let link = configDictionary[CAMKeys.loginScreenSecondCustomLink.rawValue],
              let customURL = URL(string: link) else {
            return
        }

        if UIApplication.shared.canOpenURL(customURL) {
            UIApplication.shared.open(customURL)
        }
    }
}
