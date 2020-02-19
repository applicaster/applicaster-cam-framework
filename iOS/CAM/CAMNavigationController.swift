//
//  CAMNavigationController.swift
//  CAM
//
//  Created by Egor Brel on 2/19/20.
//

import UIKit

class CAMNavigationController: UINavigationController {

    override func viewDidLoad() {
        super.viewDidLoad()
    }
    
    override var supportedInterfaceOrientations: UIInterfaceOrientationMask {
        return UIDevice.current.userInterfaceIdiom == .phone ? UIInterfaceOrientationMask.portrait : UIInterfaceOrientationMask.landscape
    }
}
