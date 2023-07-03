#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

enum class FaultType { StuckAt0, StuckAt1 };

std::unordered_map<std::string, int>
evaluateCircuit(const std::vector<int> &input,
                const std::vector<std::string> &circuit,
                const std::string &faultNode, FaultType faultType) {
  std::unordered_map<std::string, int> valueMap;
  valueMap["A"] = input[0];
  valueMap["B"] = input[1];
  valueMap["C"] = input[2];
  valueMap["D"] = input[3];

  for (const auto &line : circuit) {
    std::string variable;
    std::string leftOperand;
    std::string rightOperand;
    char op = '\0';
    size_t i = 0;

    while (line[i] != '=') {
      variable.push_back(line[i]);
      i++;
    }
    variable.resize(variable.size() - 1);
    i += 2;

    while (i < line.size()) {
      if (line[i] == '&' || line[i] == '|' || line[i] == '^' ||
          line[i] == '~') {
        op = line[i];
        break;
      }
      leftOperand.push_back(line[i]);
      i++;
    }
    if (!leftOperand.empty()) {
      leftOperand.resize(leftOperand.size() - 1);
    }
    i += 2;

    while (i < line.size()) {
      rightOperand.push_back(line[i]);
      i++;
    }

    if (variable == faultNode) {
      if (faultType == FaultType::StuckAt0) {
        valueMap[variable] = 0;
      } else {
        valueMap[variable] = 1;
      }
    } else if (leftOperand.empty()) {
      valueMap[variable] = !valueMap[rightOperand];
    } else if (op == '&') {
      valueMap[variable] = valueMap[leftOperand] & valueMap[rightOperand];
    } else if (op == '|') {
      valueMap[variable] = valueMap[leftOperand] | valueMap[rightOperand];
    } else {
      valueMap[variable] = valueMap[leftOperand] ^ valueMap[rightOperand];
    }
  }

  return valueMap;
}

bool hasMismatch(const std::vector<std::vector<int>> &inputVectors,
                 const std::vector<std::string> &circuit,
                 const std::string &faultNode, FaultType faultType) {
  for (const auto &input : inputVectors) {
    auto withFault = evaluateCircuit(input, circuit, faultNode, faultType);
    auto withoutFault =
        evaluateCircuit(input, circuit, "", FaultType::StuckAt1);

    if (withoutFault["Z"] != withFault["Z"]) {
      std::cout << "[A, B, C, D] = [";
      for (size_t i = 0; i < input.size(); i++) {
        std::cout << input[i];
        if (i != input.size() - 1) {
          std::cout << ", ";
        } else {
          std::cout << "], Z = ";
        }
      }
      std::cout << withFault["Z"] << std::endl;
      return true;
    }
  }

  std::cout << "No mismatch found." << std::endl;
  return false;
}

int main() {
  freopen("output.txt", "w", stdout);
  std::vector<std::vector<int>> inputVectors = {
      {0, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 0}, {0, 0, 1, 1},
      {0, 1, 0, 0}, {0, 1, 0, 1}, {0, 1, 1, 0}, {0, 1, 1, 1},
      {1, 0, 0, 0}, {1, 0, 0, 1}, {1, 0, 1, 0}, {1, 0, 1, 1},
      {1, 1, 0, 0}, {1, 1, 0, 1}, {1, 1, 1, 0}, {1, 1, 1, 1}};

  std::ifstream inFile("circuit_file.txt");
  std::string line;
  std::vector<std::string> circuit;

  if (inFile.is_open()) {
    while (std::getline(inFile, line)) {
      circuit.push_back(line);
    }
    inFile.close();
  } else {
    std::cerr << "Failed to open circuit file." << std::endl;
    return 1;
  }

  inFile.open("fault.txt");
  std::string faultNode;
  std::string type;

  if (inFile.is_open()) {
    std::getline(inFile, line);
    size_t pos = line.find('=');
    faultNode = line.substr(pos + 2);

    std::getline(inFile, line);
    pos = line.find('=');
    type = line.substr(pos + 2);

    inFile.close();
  } else {
    std::cerr << "Failed to open fault file." << std::endl;
    return 1;
  }

  FaultType faultType =
      (type == "SA0") ? FaultType::StuckAt0 : FaultType::StuckAt1;

  if (!hasMismatch(inputVectors, circuit, faultNode, faultType)) {
    std::cout << "Given falut has no impact on the circuit."
              << "\n";
  }

  return 0;
}
