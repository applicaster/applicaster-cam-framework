//
//  CamLinksView.swift
//  CAM
//
//  Created by Egor Brel on 12/26/19.
//

import UIKit
import ZappPlugins

class CamLinksView: UIView {
    
    @IBOutlet var camLinksStackView: UIStackView!
    var openLinkErrorAction: (() -> Void)?
    
    public var camScreen: CamScreen? {
        didSet {
            self.camLinkKeys = self.camScreen?.customLinkKeys ?? [(text: CAMKeys, link: CAMKeys)]()
        }
    }
    private var camLinkKeys = [(text: CAMKeys, link: CAMKeys)]()
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
    
    public func setupParameters(camScreen: CamScreen,
                                configDictionary: [String: String]) {
        self.camScreen = camScreen
        self.configDictionary = configDictionary
    }
    
    private func configureStackView() {
        if camScreen?.customLinkKeys.count != 2 {
            return
        }
        for index in 0..<camLinkKeys.count {
            let linkButton = UIButton()
            linkButton.tag = index
            if let link = configDictionary[camLinkKeys[index].link.rawValue], !link.isEmpty,
               let linkText = configDictionary[camLinkKeys[index].text.rawValue], !linkText.isEmpty {
                linkButton.addTarget(self, action: #selector(showCustomLink(sender:)), for: .touchUpInside)
                linkButton.titleLabel?.lineBreakMode = .byTruncatingTail
                linkButton.setStyle(config: configDictionary, camTitleKey: camLinkKeys[index].text, style: .customlinkFont)
                camLinksStackView.addArrangedSubview(linkButton)
            }
        }
        if camLinksStackView.subviews.count == 2 {
            (camLinksStackView.subviews[0] as? UIButton)?.contentHorizontalAlignment = .right
            (camLinksStackView.subviews[1] as? UIButton)?.contentHorizontalAlignment = .left
        }
        camLinksStackView.axis = .horizontal
        camLinksStackView.spacing = 5.0
        camLinksStackView.distribution = .fillEqually
        camLinksStackView.alignment = .center
    }
    
    @objc private func showCustomLink(sender: UIButton) {
        let tapLinkEvent = AnalyticsEvents.tapCustomLink(link: configDictionary[camLinkKeys[sender.tag].link.rawValue] ?? "",
                                                         text: configDictionary[camLinkKeys[sender.tag].text.rawValue] ?? "",
                                                         screenName: camScreen?.rawValue ?? "")
        ZAAppConnector.sharedInstance().analyticsDelegate.trackEvent(event: tapLinkEvent)
        guard let link = configDictionary[camLinkKeys[sender.tag].link.rawValue],
              let customURL = URL(string: link) else {
            openLinkErrorAction?()
            return
        }

        if UIApplication.shared.canOpenURL(customURL) {
            UIApplication.shared.open(customURL)
        } else {
            openLinkErrorAction?()
        }
    }
}
