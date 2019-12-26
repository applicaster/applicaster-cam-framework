//
//  CamLinksFooterReusableVIew.swift
//  CAM
//
//  Created by Egor Brel on 12/26/19.
//

import UIKit

class CamLinksFooterReusableView: UICollectionReusableView {
 
    @IBOutlet var camLinksView: CamLinksView!

    func setupParameters(camLinkKeys: [(text: CAMKeys, link: CAMKeys)],
                         configDictionary: [String: String]) {
        if camLinksView.camLinkKeys.count != 2 {
            camLinksView.setupParameters(camLinkKeys: camLinkKeys, configDictionary: configDictionary)
        }
    }
}
