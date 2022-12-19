//
//  ViewController.swift
//  CheckIDNowSDK
//
//  Created by Phu Nguyen on 9/4/19.
//  Copyright © 2019 Phu Nguyen. All rights reserved.
//

import UIKit
import IDnowSDK
import idnow_eid
import AuthadaAuthenticationLibrary

class ViewController: UIViewController {

    @IBOutlet weak var textField: UITextField!
    private var eIDRouter: IDN_eIDRouter!
    private var idnController: IDnowController!
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        textField.text = "DV1-KFEGF"
    }
    
    
    @IBAction func confirm(_ sender: UIButton) {
        view.endEditing(true)
        guard textField.hasText, let text = textField.text else {
            return
        }
        let settings = IDnowSettings()
        settings.ignoreCompanyID = true
        settings.transactionToken = text
//        let settings = IDnowSettings(companyID: "adac", transactionToken: text)
//        settings.environment = IDnowEnvironment.test
//        settings.showErrorSuccessScreen = true
//        settings.showVideoOverviewCheck = true
//        settings.ignoreCompanyID = false
        
        idnController = IDnowController(settings: settings)
        idnController.delegate = self
//        idnController.initialize()
        UIApplication.shared.isNetworkActivityIndicatorVisible = true
        idnController.initialize(completionBlock: {(success, error, canceledByUser) in
            if success {
                
                self.eIDRouter = IDN_eIDRouter(withController: self, token: self.textField.text ?? "") { supported, error in
                    self.eIDRouter?.present({ [weak self] success, continueVideoIdent, error in
                        if let strSelf = self, continueVideoIdent {
                            self?.idnController.startIdentification(from: strSelf )
                        }
                    })
                }
            }
        })
    }
}

extension ViewController: IDnowControllerDelegate {
    func idnowControllerDidFinishInitializing(_ idnowController: IDnowController) {
//        print("\nidnowControllerDidFinishInitializing invoked")
//        idnowController.startIdentification(from: self)
//        UIApplication.shared.isNetworkActivityIndicatorVisible = false
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

