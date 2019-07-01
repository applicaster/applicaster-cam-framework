//
//  UIViewController + Extension.swift
//  CAM
//
//  Created by Egor Brel on 4/29/19.
//

import UIKit

// swiftlint:disable all

public extension UIViewController {
    class func instantiateVC() -> Self {
        return initFromStoryboard()
    }
    
    private class func initFromStoryboard<T>() -> T {
        let bundle = Bundle(for: T.self as! AnyClass)
        return UIStoryboard.init(name: String(describing: T.self), bundle: bundle).instantiateViewController(withIdentifier: String(describing: T.self)) as! T
    }
    
    func showAlert(description: String?) {
        let alert = UIAlertController(title: "", message: description, preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: "Ok", style: .default, handler: nil))
        self.present(alert, animated: true, completion: nil)
    }
    
    func showConfirmationScreen(config: [String: String], titleKey: CAMKeys, descriptionKey: CAMKeys, buttonKey: CAMKeys, action: @escaping () -> Void) {
        let confirmationPopover = ConfirmationPopover.nibInstance()
        confirmationPopover.frame = self.view.frame
        confirmationPopover.buttonPressedAction = action
        confirmationPopover.titleLabel.setStyle(config: config, camTextKey: titleKey, style: .confirmationTitleFont)
        confirmationPopover.descriptionLabel.setStyle(config: config, camTextKey: descriptionKey, style: .confirmationDescriptionFont)
        confirmationPopover.actionButton.setStyle(config: config, backgroundAsset: .alertButtonImage, camTitleKey: buttonKey, style: .actionButtonFont)
        self.view.addSubview(confirmationPopover)
    }
    
    func showErrorPopover(config: [String: String], message: String?, sourceRect: CGRect, bubbleWidth: CGFloat) {
        let controller = ErrorPopoverViewController.instantiateVC()
        controller.modalPresentationStyle = .popover
        controller.preferredContentSize = CGSize(width: bubbleWidth, height: 90)
        if let popoverPresentationController = controller.popoverPresentationController {
            if let delegate = self as? UIPopoverPresentationControllerDelegate {
                popoverPresentationController.delegate = delegate
            }
            popoverPresentationController.sourceView = self.view
            popoverPresentationController.permittedArrowDirections = .up
            popoverPresentationController.popoverBackgroundViewClass = ErrorPopoverBackgroundView.self
            popoverPresentationController.sourceRect = sourceRect
            present(controller, animated: true, completion: {
                controller.messageLabel.setStyle(config: config, style: .inputFieldFont)
                controller.messageLabel.text = message
                controller.bubbleWidthConstraint.constant = bubbleWidth
                controller.view.layoutIfNeeded()
            })
        }
    }
}
