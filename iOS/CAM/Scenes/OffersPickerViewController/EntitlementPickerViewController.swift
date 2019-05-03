//
//  OffersPickerViewControllerPhone.swift
//  CAMFramework
//
//  Created by Egor Brel on 5/2/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import UIKit

class EntitlementPickerViewController: UIViewController {
    @IBOutlet weak var backgroundImageView: UIImageView!
    @IBOutlet weak var logoImageView: UIImageView!
    @IBOutlet weak var closeButton: UIButton!
    @IBOutlet weak var backButton: UIButton!
    @IBOutlet weak var titleLabel: UILabel!
    
    @IBOutlet weak var entitlementsLoadingIndicator: UIActivityIndicatorView!
    @IBOutlet weak var entitlementCollectionView: UICollectionView!
    @IBOutlet weak var restorePurchaseLabel: UILabel!
    
    @IBOutlet weak var helpInfoContainer: UIView!
    @IBOutlet weak var helpInfoTextView: UITextView!
    
    var presenter: EntitlementsPickerPresenter?
    var entitlements = [CAMEntitlementItem]()
    var currentItemIndex = 0 // Used for store center cell for ipad
    var itemSpacing: CGFloat = 20
    
    var itemSize: CGSize {
        if UIDevice.current.userInterfaceIdiom == .pad {
            return CGSize(width: 320, height: 248)
        } else {
            return CGSize(width: 320, height: 192)
        }
    }
    
    var pageWidth: CGFloat {
        return CGFloat(itemSize.width + itemSpacing)
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupCollectionView()
    }
    
    override func viewDidLayoutSubviews() {
        super.viewDidLayoutSubviews()
    }
    
    func setupCollectionView() {
        let customLayout = CustomFlowLayout()
        customLayout.itemSize = itemSize
        customLayout.minimumLineSpacing = 20
        customLayout.scrollDirection = UIDevice.current.userInterfaceIdiom == .pad ? .horizontal : .vertical
        entitlementCollectionView.collectionViewLayout = customLayout
        entitlementCollectionView.delegate = self
        entitlementCollectionView.dataSource = self
    }
    
}

extension EntitlementPickerViewController: UICollectionViewDelegate, UICollectionViewDataSource, UICollectionViewDelegateFlowLayout  {
    
    func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        return entitlements.count
    }
    
    func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
        return collectionView.dequeueReusableCell(withReuseIdentifier: "EntitlementCollectionViewCell", for: indexPath)
    }
    
    private func indexOfMajorCell() -> Int {
        let proportionalOffset = entitlementCollectionView.contentOffset.x / pageWidth
        return Int(round(proportionalOffset))
    }
    
    func scrollViewWillEndDragging(_ scrollView: UIScrollView, withVelocity velocity: CGPoint, targetContentOffset: UnsafeMutablePointer<CGPoint>) {
        if UIDevice.current.userInterfaceIdiom == .pad {
            let majorCell = indexOfMajorCell()
            let delta = abs(majorCell - currentItemIndex)
            if velocity.x == 0 {
                currentItemIndex = majorCell
            } else {
                if delta > 1 {
                    currentItemIndex = majorCell
                } else {
                    currentItemIndex = velocity.x > 0 ? currentItemIndex + 1 : currentItemIndex - 1
                }
            }
            if currentItemIndex < 0 {
                currentItemIndex = 0
            }
            if currentItemIndex >= entitlements.count {
                currentItemIndex = entitlements.count - 1
            }
            let point = CGPoint(x: CGFloat(currentItemIndex) * pageWidth, y: targetContentOffset.pointee.y)
            targetContentOffset.pointee = point
        }
    }
    
    func collectionView(_ collectionView: UICollectionView, targetContentOffsetForProposedContentOffset proposedContentOffset: CGPoint) -> CGPoint {
        return UIDevice.current.userInterfaceIdiom == .pad ? CGPoint(x: CGFloat(currentItemIndex) * pageWidth, y: 0) : proposedContentOffset
    }
}
