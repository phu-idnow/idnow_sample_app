//
//  ViewController.swift
//  CheckIDNowSDK
//
//  Created by Phu Nguyen on 9/4/19.
//  Copyright © 2019 Phu Nguyen. All rights reserved.
//

import UIKit
import IDnowSDK

class ViewController: UIViewController {

    @IBOutlet weak var textField: UITextField!
    
    private var idnController: IDnowController!
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    
    @IBAction func confirm(_ sender: UIButton) {
        view.endEditing(true)
        guard textField.hasText, let text = textField.text else {
            return
        }
        let settings = IDnowSettings()
        settings.ignoreCompanyID = true
        settings.transactionToken = text
        idnController = IDnowController(settings: settings)
        idnController.delegate = self
        idnController.initialize()
        UIApplication.shared.isNetworkActivityIndicatorVisible = true
    }
}

extension ViewController: IDnowControllerDelegate {
    func idnowControllerDidFinishInitializing(_ idnowController: IDnowController) {
        print("\nidnowControllerDidFinishInitializing invoked")
        idnowController.startIdentification(from: self)
        UIApplication.shared.isNetworkActivityIndicatorVisible = false
    }

    func idnowController(_ idnowController: IDnowController, initializationDidFailWithError error: Error) {
        print("\nInitializationDidFailWithError invoked")
        showAlert(message: "InitializationDidFailWithError invoked")
        UIApplication.shared.isNetworkActivityIndicatorVisible = false
    }

    func idnowControllerCanceled(byUser idnowController: IDnowController) {
        print("\nidnowControllerCanceled invoked")
        showAlert(message: "nidnowControllerCanceled invoked")
    }

    func idnowControllerDidFinishIdentification(_ idnowController: IDnowController) {
        print("\nidnowControllerDidFinishIdentification invoked")
        showAlert(message: "nidnowControllerDidFinishIdentification invoked")
    }
}

extension ViewController {
    func showAlert(message: String? = nil) {
        let alert = UIAlertController(title: "Sample App", message: message, preferredStyle: .alert)
        let okAction = UIAlertAction(title: "OK", style: .default, handler: nil)
        alert.addAction(okAction)
        self.present(alert, animated: true, completion: nil)
    }
}

