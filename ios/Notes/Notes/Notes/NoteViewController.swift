//
//  NoteViewController.swift
//  Notes
//
//  Created by Cristi Cretu on 27.05.2021.
//

import Foundation
import UIKit

class NoteViewController: UIViewController {
    var note: Note!
    
    @IBOutlet var textView : UITextView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        textView.text = note.contents
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        note.contents = textView.text 
        NoteManager.main.save(note: note)
    }
    
    @IBAction func deleteNote(_ sender: Any) {
        let _ = NoteManager.main.delete(id: note!.id)
        navigationController?.popViewController(animated: true)
    }
}
