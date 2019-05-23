//
//  EntitlementCollectionViewCell.swift
//  CAMFramework
//
//  Created by Egor Brel on 5/3/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import UIKit

final class OfferViewModel {
    let title: String
    let description: String
    let buyAction: () -> Void
    let redeemAction: () -> Void
    
    init(title: String,
         description: String,
         buyAction: @escaping () -> Void,
         redeemAction: @escaping () -> Void) {
        self.title = title
        self.description = description
        self.buyAction = buyAction
        self.redeemAction = redeemAction
    }
}

class EntitlementCollectionViewCell: UICollectionViewCell {
    @IBOutlet private var titleLabel: UILabel!
    @IBOutlet private var infoLabel: UILabel!
    @IBOutlet private var purchaseButton: UIButton!
    
    private var buyAction: () -> Void = {}
    private var redeemAction: () -> Void = {}
    
    public func configure(from viewModel: OfferViewModel) {
        self.titleLabel.text = viewModel.title
        self.infoLabel.text = viewModel.description
        self.buyAction = viewModel.buyAction
        self.redeemAction = viewModel.redeemAction
        self.purchaseButton.setZappStyle(backgroundAsset: .purchaseButtonImage, title: "SUBSCRIBE FOR $4.99")
    }

    @IBAction private func purchaseItem(_ sender: UIButton) {
        buyAction()
    }
    
    @IBAction private func purchaseWithRedeemCode(_ sender: UIButton) {
        redeemAction()
    }
}
