# Simran_Shah_Google_Girl_Hackathon_Ideathon_Round


** All the related code and input files are attached **


Manufactured chips generally consist of several complex combinational circuits, in designing those chips, sometimes, the gate gets faulty and stuck. When a signal or gate output is stuck at 0 or 1 value, independent of the inputs provided to the circuit, the signal is said to be stuck. This fault is generally of two types, firstly SA0(Stuck at 0) in which the signal is stuck at 0, and secondly SA1(Stuck at 1)in which the signal is stuck at 1. Now these faults can cause the logic operation to vary from the result required, So it is essential to find and check if the combinational circuit is faulty or right. In the given scenario, we are provided with the input in the form of a Circuit file which consists of the logic of the circuit, and a fault file which explains the type of fault and location of the fault. The task is to find a vector of inputs that can help in detecting the fault along with the expected output due to the fault.


The approach used to generate the algorithm is by breaking it down into smaller, manageable steps.

STEP 1: It begins by reading the circuit file, which contains information about the different parts and logic equations of the circuit.

STEP 2: Next, the algorithm parses the circuit information to extract the nodes and their corresponding equations. This allows the algorithm to understand the structure of the circuit and how it operates.

STEP 3: To identify the fault, the algorithm looks for the specified fault node in the circuit. It determines the type of fault (SA0 or SA1) and assigns the corresponding fault value (false for SA0, true for SA1).

STEP 4: The algorithm then generates a series of  input vectors for testing the circuit with the fault. It assigns the fault value to the fault node and the complement of the fault value to other inputs in the equation and obtains corresponding outputs.

STEP 5: Using the generated input vector, the algorithm evaluates the circuit by calculating the output value based on the circuit equations and input values. It compares the calculated output with the expected output to identify the fault at the specified node.

STEP 6: For each test case, the algorithm prints the input vector and the expected output. This information helps in identifying and understanding the fault in the circuit.

Finally, the algorithm writes the output, including the input vector and expected output, to a file named "output.txt". This file can be used for further analysis and comparison.


The main data structures used here is 2d vector and an unordered map. The language used for implementing the given algorithm is C++ as it is close to low-level design. We read first all the input files, using ifstream method, and then the circuit parameters are passed in the function, evaluateCircuit, for deriving the logical output of the given circuit.
In evaluate function, we read through the string files and try to obtain the operators and operation line-wise and perform the logic as usual, then we have also sent the fault type and fault location, using which at position, we can obtain both expected and real output.
Now, using the expected and real output is provided through, and then in the function we do logic circuit operation, and compare both the results, now we can infer fault effect on the circuit.
Then the output vector which shows a mismatch, is printed in output.txt along with the value of z, and we can use it for further test access.
