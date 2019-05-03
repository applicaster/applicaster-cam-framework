//
//  HorizontlFlowLayout.swift
//  CAMFramework
//
//  Created by Egor Brel on 5/3/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import UIKit

class CustomFlowLayout: UICollectionViewFlowLayout {
    
    override open func prepare() {
        super.prepare()
        updateInsets()
    }
    
    private func updateInsets() {
        guard let collectionView = collectionView else {
            return
        }
        if UIDevice.current.userInterfaceIdiom == .pad {
            let inset = (collectionView.bounds.size.width - itemSize.width) / 2
            self.sectionInset.left = inset
            self.sectionInset.right = inset
        } else {
            self.sectionInset.bottom = 64
        }
        
    }
    
    override func shouldInvalidateLayout(forBoundsChange newBounds: CGRect) -> Bool {
        return true
    }
}
