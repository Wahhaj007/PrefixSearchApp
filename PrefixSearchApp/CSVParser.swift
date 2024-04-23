//
//  CSVParser.swift
//  SwiftPrefixSearch
//
//  Created by Wahhaj Malik on 4/22/24.
//

import Foundation

class CSVParser {
    
    func loadCSV(from fileName: String) -> String? {
        guard let path = Bundle.main.path(forResource: fileName, ofType: "csv") else {
            print("CSV file not found")
            return nil
        }
        
        do {
            let content = try String(contentsOfFile: path, encoding: .utf8)
            return content
        } catch {
            print("Error reading the CSV file: \(error)")
            return nil
        }
    }
    
    func parseCSV(content: String) -> [[String]] {
        var result: [[String]] = []
        let rows = content.components(separatedBy: "\n")
        
        for row in rows {
            var columns: [String] = []
            var quoteIsOpen = false
            var field: String = ""
            
            for character in row {
                switch character {
                case ",":
                    if quoteIsOpen {
                        field += String(character)
                    } else {
                        columns.append(field)
                        field = ""
                    }
                case "\"":
                    quoteIsOpen.toggle()
                default:
                    field += String(character)
                }
            }
            
            if !field.isEmpty {
                columns.append(field)
            }
            
            result.append(columns)
        }
        
        return result
    }
}
