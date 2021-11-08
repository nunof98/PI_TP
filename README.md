# PI_TP
Analysis of direct current electrical circuits

The application must be able to read a text file, which will contain the description of the circuit to be analyzed. This file, named “cirtuito.cir” and whose content will be represented in ASCII, will define a circuit with only two types of elements:
- DC Voltage Sources;
- Resistors.

The “cirtuito.cir” file must comply with the following rules:
- The first line must have the title of the circuit. This title can contain any sequence of characters (letters, numbers, spaces, punctuation marks, among others).
- The last line of the file must contain the inscription “.END” or “.end”, which indicates the end of the circuit.
- The remaining lines of the file, contained between the title and the indication of the end of the circuit, specify the elements of the circuit. Each of these lines defines a single circuit element. The order of these lines is irrelevant, and does not affect how these elements are arranged in the circuit.
- A circuit element is described according to the following format:

  < element type >< element name > < node+ > < node- > < value >

  On what:
  - < element type > consists of a single letter that specifies the element type. It can take one of the following values:
    - V or v – For a direct voltage source;
    - R or r – For a resistance.
  - The < element name > of the circuit, which must consist of a unique alphanumeric combination (ie a unique name), containing no spaces. It is specified immediately after the element type.
  - Each element is inserted between two nodes. The first node, < node+ >, will be considered the highest potential node, while the second node, < node->, will be considered the lowest potential node. Note, however, that the potential may actually be reversed.
  - The element type value is defined in the < value > field. Only voltage sources admit zero value. Both resistances and voltage sources only take integer values. In the case of resistances, the < value > field defines the resistance in Ohms. In voltage sources, the < value > field represents, in Volts, the potential difference between two nodes.
  
Example of a circuit, and respective “.cir” file:

![image](https://user-images.githubusercontent.com/58945080/140827327-e4f61b00-f533-4ab3-bf5a-ef3ab99859ac.png)
