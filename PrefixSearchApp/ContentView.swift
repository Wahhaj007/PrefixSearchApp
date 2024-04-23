import SwiftUI

struct ContentView: View {
    @State private var trie = TrieNode()
    @State private var searchPrefix = ""
    @State private var searchResults: [String] = []

    init() {
        // Load words from CSV during initialization
        let parser = CSVParser()
        if let csvContent = parser.loadCSV(from: "NewSongCSV") {
            let words = parser.parseCSV(content: csvContent)
            for wordArray in words {
                for word in wordArray where !word.isEmpty {
                    trie.insert(word: word)
                }
            }
        }
    }

    var body: some View {
        VStack {
            Text("Find your music!")
                .font(.title)
                .padding()
            
            TextField("Enter prefix", text: $searchPrefix)
                .textFieldStyle(RoundedBorderTextFieldStyle())
                .padding()
            
            Button("Search") {
                self.searchResults = self.trie.starts(with: self.searchPrefix)
            }
            .padding()
            .foregroundColor(.white)
            .background(Color.blue)
            .cornerRadius(10)
            
            List(searchResults, id: \.self) { result in
                Text(result)
            }
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
