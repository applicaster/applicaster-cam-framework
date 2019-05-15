//
//  LoginAuthTableCell.swift
//  CAM
//
//  Created by Egor Brel on 5/14/19.
//

import UIKit

class AuthTableCell: UITableViewCell, UITextFieldDelegate {

    @IBOutlet var textField: UITextField!
    var textChanged: ((String?) -> Void)?
    
    override func awakeFromNib() {
        super.awakeFromNib()
        textField.addTarget(self, action: #selector(textFieldDidChange), for: .editingChanged)
        textField.delegate = self
    }
    
    @objc func textFieldDidChange() {
        textChanged?(textField.text)
    }
    
    func textField(_ textField: UITextField, shouldChangeCharactersIn range: NSRange, replacementString string: String) -> Bool {
        textChanged?(textField.text)
        return true
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)
    }

}
