//
//  ViewController.swift
//  IDNowSampleApp
//
//  Created by Phu Nguyen on 10/28/19.
//  Copyright © 2019 IDNow. All rights reserved.
//

import UIKit
import IDnowSDK

class ViewController: UIViewController {

    private var idnController: IDnowController!
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
    }
    
    @IBAction func confirm (_ sender: Any) {
        let settings = IDnowSettings()
        settings.transactionToken = "TST-ECWNB"
        settings.ignoreCompanyID = true
        idnController = IDnowController(settings: settings)
        idnController.delegate = self
        idnController.initialize()
    }

}

extension ViewController: IDnowControllerDelegate {
    func idnowControllerDidFinishInitializing(_ idnowController: IDnowController) {
        print("\nidnowControllerDidFinishInitializing invoked")
        idnowController.startIdentification(from: self)
    }
    
    func idnowController(_ idnowController: IDnowController, initializationDidFailWithError error: Error) {
        print("\nInitializationDidFailWithError invoked")
    }
    
    func idnowControllerCanceled(byUser idnowController: IDnowController) {
        print("\nidnowControllerCanceled invoked")
    }
    
    func idnowControllerDidFinishIdentification(_ idnowController: IDnowController) {
        print("\nidnowControllerDidFinishIdentification invoked")
    }
}
