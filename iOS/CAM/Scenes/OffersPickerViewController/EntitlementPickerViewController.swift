//
//  OffersPickerViewControllerPhone.swift
//  CAMFramework
//
//  Created by Egor Brel on 5/2/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import UIKit

class EntitlementPickerViewController: UIViewController {
    @IBOutlet private var backgroundImageView: UIImageView!
    @IBOutlet private var logoImageView: UIImageView!
    @IBOutlet private var closeButton: UIButton!
    @IBOutlet private var backButton: UIButton!
    @IBOutlet private var titleLabel: UILabel!
    
    @IBOutlet private var entitlementsLoadingIndicator: UIActivityIndicatorView!
    @IBOutlet private var entitlementCollectionView: UICollectionView!
    @IBOutlet private var restorePurchaseLabel: UILabel!
    
    @IBOutlet private var helpInfoContainer: UIView!
    @IBOutlet private var helpInfoTextView: UITextView!
    
    var presenter: EntitlementPickerPresenter?
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
    
    private var offerViewModels: [OfferViewModel] = []
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupCollectionView()
        presenter?.viewDidLoad()
        
        backgroundImageView.setZappStyle(withAsset: .backgroundImage)
        backButton.setZappStyle(withIconAsset: .backButtonImage)
        closeButton.setZappStyle(withIconAsset: .closeButtonImage)
        logoImageView.setZappStyle(withAsset: .headerLogo)
    }
    
    func setupCollectionView() {
        let customLayout = CustomFlowLayout()
        customLayout.itemSize = itemSize
        customLayout.minimumLineSpacing = 20
        customLayout.scrollDirection = UIDevice.current.userInterfaceIdiom == .pad ? .horizontal : .vertical
        entitlementCollectionView.collectionViewLayout = customLayout
    }
    
    @IBAction func backToPreviousScreen(_ sender: Any) {
        presenter?.backToPreviousScreen()
    }
    
    @IBAction func close(_ sender: Any) {
        presenter?.close()
    }
    
    public func showOffers(_ offers: [OfferViewModel]) {
        self.offerViewModels = offers
        self.entitlementCollectionView.reloadData()
    }
    
    public func showLoadingIndicator() {
        entitlementsLoadingIndicator.startAnimating()
    }
    
    public func hideLoadingIndicator() {
        entitlementsLoadingIndicator.stopAnimating()
    }
}

extension EntitlementPickerViewController: UICollectionViewDelegate, UICollectionViewDataSource, UICollectionViewDelegateFlowLayout {
    
    func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        return self.offerViewModels.count
    }
    
    func collectionView(_ collectionView: UICollectionView,
                        cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
        guard let cell = collectionView.dequeueReusableCell(withReuseIdentifier: "EntitlementCollectionViewCell",
                                                            for: indexPath) as? EntitlementCollectionViewCell else {
            fatalError()
        }
        
        let cellViewModel = self.offerViewModels[indexPath.row]
        cell.configure(from: cellViewModel)
        
        return cell
    }
    
    private func indexOfMajorCell() -> Int {
        let proportionalOffset = entitlementCollectionView.contentOffset.x / pageWidth
        return Int(round(proportionalOffset))
    }
    
    func scrollViewWillEndDragging(_ scrollView: UIScrollView,
                                   withVelocity velocity: CGPoint,
                                   targetContentOffset: UnsafeMutablePointer<CGPoint>) {
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
            if currentItemIndex >= self.offerViewModels.count {
                currentItemIndex = self.offerViewModels.count - 1
            }
            let point = CGPoint(x: CGFloat(currentItemIndex) * pageWidth, y: targetContentOffset.pointee.y)
            targetContentOffset.pointee = point
        }
    }
    
    func collectionView(_ collectionView: UICollectionView,
                        targetContentOffsetForProposedContentOffset proposedContentOffset: CGPoint) -> CGPoint {
        return UIDevice.current.userInterfaceIdiom == .pad
            ? CGPoint(x: CGFloat(currentItemIndex) * pageWidth, y: 0)
            : proposedContentOffset
    }
}
