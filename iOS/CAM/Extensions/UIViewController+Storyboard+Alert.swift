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
    
    func showConfirmationScreen(title: String, description: String, buttonText: String, action: @escaping () -> Void) {
        let confirmationPopover = ConfirmationPopover.nibInstance()
        confirmationPopover.frame = self.view.frame
        confirmationPopover.buttonPressedAction = action
        confirmationPopover.titleLabel.setZappStyle(text: title, style: .alertTitle)
        confirmationPopover.descriptionLabel.setZappStyle(text: description, style: .alertDescription)
        confirmationPopover.actionButton.setZappStyle(backgroundAsset: .alertButtonImage, title: buttonText, style: .actionButton)
        self.view.addSubview(confirmationPopover)
    }
    
    func showErrorPopover(message: String?, sourceRect: CGRect) {
        let controller = ErrorPopoverViewController.instantiateVC()
        controller.modalPresentationStyle = .popover
        controller.preferredContentSize = CGSize(width: 390, height: 91)
        if let popoverPresentationController = controller.popoverPresentationController {
            popoverPresentationController.sourceView = self.view
            popoverPresentationController.permittedArrowDirections = .up
            popoverPresentationController.popoverBackgroundViewClass = ErrorPopoverBackgroundView.self
            popoverPresentationController.sourceRect = sourceRect
            present(controller, animated: true, completion: {
                controller.messageLabel.text = message
            })
        }
    }
}
