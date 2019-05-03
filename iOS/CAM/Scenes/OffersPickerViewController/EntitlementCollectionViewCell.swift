//
//  EntitlementCollectionViewCell.swift
//  CAMFramework
//
//  Created by Egor Brel on 5/3/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import UIKit

class EntitlementCollectionViewCell: UICollectionViewCell {
    @IBOutlet weak var freePeriodImageView: UIImageView!
    
    @IBOutlet weak var titleLabel: UILabel!
    @IBOutlet weak var infoLabel: UILabel!
    @IBOutlet weak var purchaseButton: UIButton!
    @IBAction func purchaseItem(_ sender: UIButton) {
    }
}
