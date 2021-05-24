import UIKit

// Catch function:
// https://github.com/casualc0der/Pokedex

var savedData = UserDefaults.standard
var pokedex = Pokedex.init(caught: [ : ])

class PokemonViewController: UIViewController {
    var url: String!

    @IBOutlet var nameLabel: UILabel!
    @IBOutlet var numberLabel: UILabel!
    @IBOutlet var type1Label: UILabel!
    @IBOutlet var type2Label: UILabel!
    @IBOutlet weak var catchButton: UIButton!
    @IBOutlet weak var pokemonImage: UIImageView!
    
    var isCatched = false
    
    @IBAction func toggleCatch(_ sender: UIButton) {
        if isCatched == false {
            catchButton.setTitle("Release", for: .normal)
            isCatched = true
            savedData.set(true, forKey: (nameLabel.text)!)
            pokedex.caught[nameLabel.text!] = true
        } else {
            catchButton.setTitle("Catch", for: .normal)
            isCatched = false
            savedData.set(false, forKey: (nameLabel.text)!)
            pokedex.caught[nameLabel.text!] = true
        }
    }
    
    func capitalize(text: String) -> String {
        return text.prefix(1).uppercased() + text.dropFirst()
    }

    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)

        nameLabel.text = ""
        numberLabel.text = ""
        type1Label.text = ""
        type2Label.text = ""

        loadPokemon()
    }

    func loadPokemon() {
        URLSession.shared.dataTask(with: URL(string: url)!) { (data, response, error) in
            guard let data = data else {
                return
            }

            do {
                let result = try JSONDecoder().decode(PokemonResult.self, from: data)
                DispatchQueue.main.async {
                    self.navigationItem.title = self.capitalize(text: result.name)
                    self.nameLabel.text = self.capitalize(text: result.name)
                    self.numberLabel.text = String(format: "#%03d", result.id)

                    for typeEntry in result.types {
                        if typeEntry.slot == 1 {
                            self.type1Label.text = typeEntry.type.name
                        }
                        else if typeEntry.slot == 2 {
                            self.type2Label.text = typeEntry.type.name
                        }
                    }
                    
                    if savedData.bool(forKey: self.nameLabel.text!) == true {
                        pokedex.caught[self.nameLabel.text!] = true
                    } else {
                        pokedex.caught[self.nameLabel.text!] = false
                    }
                    
                    if pokedex.caught[self.nameLabel.text!] == false || pokedex.caught[self.nameLabel.text!] == nil {
                        self.catchButton.setTitle("Catch", for: .normal)
                    } else if pokedex.caught[self.nameLabel.text!] == true {
                        self.catchButton.setTitle("Release", for: .normal)
                    }
                }
            }
            catch let error {
                print(error)
            }
        }.resume()
    }
}
