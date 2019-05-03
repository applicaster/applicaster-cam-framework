//
//  ConfirmationPopover.swift
//  CAMFramework
//
//  Created by Egor Brel on 4/25/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import UIKit

class ConfirmationPopover: UIView {

    @IBOutlet weak var titleLabel: UILabel!
    @IBOutlet weak var DescriptionLabel: UILabel!
    @IBOutlet weak var actionButton: UIButton!
    
    var buttonPressedAction = {
        
    }

    @IBAction func actionButtonPressed(_ sender: UIButton) {
        buttonPressedAction()
    }
    
}
