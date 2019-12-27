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
    private var camScreen: CamScreen?
    private var camLinkKeys = [(text: CAMKeys, link: CAMKeys)]()
    private var configDictionary = [String: String]()
    
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
        if self.camScreen != camScreen {
            self.camScreen = camScreen
            self.configDictionary = configDictionary
            self.camLinkKeys = self.camScreen?.customLinkKeys ?? [(text: CAMKeys, link: CAMKeys)]()
            configureStackView()
        }
    }
    
    private func configureStackView() {
        if camScreen?.customLinkKeys.count != 2 {
            return
        }
        for (index,key) in camLinkKeys.enumerated() {
            let linkButton = UIButton()
            linkButton.tag = index
            if let link = configDictionary[key.link.rawValue], !link.isEmpty,
               let linkText = configDictionary[key.text.rawValue], !linkText.isEmpty {
                linkButton.addTarget(self, action: #selector(showCustomLink(sender:)), for: .touchUpInside)
                linkButton.titleLabel?.lineBreakMode = .byTruncatingTail
                linkButton.setStyle(config: configDictionary, camTitleKey: key.text, style: .customlinkFont)
                camLinksStackView.addArrangedSubview(linkButton)
            }
        }
        if camLinksStackView.subviews.count == 2 {
            (camLinksStackView.subviews[0] as? UIButton)?.contentHorizontalAlignment = .right
            (camLinksStackView.subviews[1] as? UIButton)?.contentHorizontalAlignment = .left
        }
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

        guard UIApplication.shared.canOpenURL(customURL) else {
            openLinkErrorAction?()
            return
        }
        UIApplication.shared.open(customURL)
    }
}
