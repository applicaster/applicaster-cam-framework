//
//  OffersPickerViewControllerPhone.swift
//  CAMFramework
//
//  Created by Egor Brel on 5/2/19.
//  Copyright © 2019 Egor Brel. All rights reserved.
//

import UIKit

struct OffersViewModel {
    let title: String
    let restoreHint: String
    let restoreButtonText: String
    let legalDetails: String
}

class EntitlementPickerViewController: UIViewController {
    @IBOutlet private var backgroundImageView: UIImageView!
    @IBOutlet private var logoImageView: UIImageView!
    @IBOutlet private var closeButton: UIButton!
    @IBOutlet private var titleLabel: UILabel!
    
    @IBOutlet private var entitlementsLoadingIndicator: UIActivityIndicatorView!
    @IBOutlet private var entitlementCollectionView: UICollectionView!
    @IBOutlet private var restorePurchaseLabel: UILabel!
    @IBOutlet private var restoreButton: UIButton!
    
    @IBOutlet private var helpInfoContainer: UIView!
    @IBOutlet private var helpInfoTextView: UITextView!
    private var gradientLayer: CAGradientLayer!
    
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
    
    var viewModel: OffersViewModel? {
        didSet {
            titleLabel.text = viewModel?.title
            restorePurchaseLabel.text = viewModel?.restoreHint
            restoreButton.setTitle(viewModel?.restoreButtonText, for: .normal)
            helpInfoTextView.text = viewModel?.legalDetails
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupCollectionView()
        presenter?.viewDidLoad()
        
        backgroundImageView.setZappStyle(withAsset: .backgroundImage)
        closeButton.setZappStyle(withIconAsset: .closeButtonImage)
        logoImageView.setZappStyle(withAsset: .headerLogoImage)
        helpInfoContainer.setZappStyle(withBackgroundColor: .alternateActionBannerColor)
        
        setupGradient()
    }
    
    override func viewDidLayoutSubviews() {
        super.viewDidLayoutSubviews()
        
        self.gradientLayer.frame = self.helpInfoTextView.bounds
    }
    
    func setupCollectionView() {
        let customLayout = CustomFlowLayout()
        customLayout.itemSize = itemSize
        customLayout.minimumLineSpacing = 20
        customLayout.scrollDirection = UIDevice.current.userInterfaceIdiom == .pad ? .horizontal : .vertical
        entitlementCollectionView.collectionViewLayout = customLayout
    }
    
    @IBAction func close(_ sender: Any) {
        presenter?.close()
    }
    
    @IBAction func restore(_ sender: Any) {
        presenter?.restore()
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
    
    // MARK: - Private methods
    
    private func setupGradient() {
        self.gradientLayer = CAGradientLayer()
        self.gradientLayer.colors = [UIColor.black.cgColor,
                                     UIColor.black.cgColor,
                                     UIColor.clear.cgColor]
        self.gradientLayer.locations = [0.0, 0.3, 1.0]
        
        self.helpInfoTextView.layer.mask = self.gradientLayer
    }
    
    func scrollViewDidScroll(_ scrollView: UIScrollView) {
        if scrollView === helpInfoTextView {
            CATransaction.begin()
            CATransaction.setValue(kCFBooleanTrue, forKey: kCATransactionDisableActions)
            self.gradientLayer.frame = self.helpInfoTextView.bounds
            CATransaction.commit()
        }
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
