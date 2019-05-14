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
    @IBOutlet weak var freePeriodImageView: UIImageView!
    
    @IBOutlet weak var titleLabel: UILabel!
    @IBOutlet weak var infoLabel: UILabel!
    @IBOutlet weak var purchaseButton: UIButton!
    
    var buyAction: () -> Void = {}
    var redeemAction: () -> Void = {}
    
    public func configure(from viewModel: OfferViewModel) {
        self.titleLabel.text = viewModel.title
        self.infoLabel.text = viewModel.description
        self.buyAction = viewModel.buyAction
        self.redeemAction = viewModel.redeemAction
    }

    @IBAction func purchaseItem(_ sender: UIButton) {
        buyAction()
    }
    
    @IBAction func purchaseWithRedeemCode(_ sender: UIButton) {
        redeemAction()
    }
    
    

}
