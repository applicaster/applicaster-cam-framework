//
//  ErrorPopoverViewController.swift
//  CAMFramework
//
//  Created by Egor Brel on 6/13/19.
//

import UIKit

class ErrorPopoverViewController: UIViewController {

    @IBOutlet var bubbleWidthConstraint: NSLayoutConstraint!
    @IBOutlet var shadowImageView: UIImageView!
    @IBOutlet var bubbleImageView: UIImageView!
    @IBOutlet var arrowImageView: UIImageView!
    @IBOutlet var messageLabel: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        configureElements()
    }
    
    func configureElements() {
        bubbleWidthConstraint.constant = UIDevice.current.userInterfaceIdiom == .pad ? 304 : 250
        shadowImageView.setZappStyle(withAsset: .errorPopoverShadowImage)
        bubbleImageView.setZappStyle(withAsset: .errorPopoverBubble)
        arrowImageView.setZappStyle(withAsset: .errorPopoverArrow)
        messageLabel.setZappStyle(text: nil, style: .alertTitle)
        view.layoutIfNeeded()
    }

    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        super.touchesBegan(touches, with: event)
        self.dismiss(animated: false, completion: nil)
    }
}
