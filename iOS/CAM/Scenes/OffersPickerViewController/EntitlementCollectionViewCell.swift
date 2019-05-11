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
    
    init(title: String,
         description: String,
         buyAction: @escaping () -> Void) {
        self.title = title
        self.description = description
        self.buyAction = buyAction
    }
}

class EntitlementCollectionViewCell: UICollectionViewCell {
    @IBOutlet weak var freePeriodImageView: UIImageView!
    
    @IBOutlet weak var titleLabel: UILabel!
    @IBOutlet weak var infoLabel: UILabel!
    @IBOutlet weak var purchaseButton: UIButton!
    @IBAction func purchaseItem(_ sender: UIButton) {
    }
    
    public func configure(from viewModel: OfferViewModel) {
        
    }
}
