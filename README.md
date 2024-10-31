# Gator AVL Tree

This program is a simple CLI implementation of an AVL tree, a self-balancing binary search tree where each node maintains a balance factor. This allows for efficient insertions, deletions, and lookups, while ensuring that the tree's height remains logarithmic. It supports several commands to manage and interact with the AVL tree data. This project was completed as part of an assignment for the University of Florida.

## Features

- **Insertion**: Insert a node with a name and a unique 8-digit UFID.
- **Deletion**: Delete nodes by name or by UFID.
- **Search**: Search for nodes by name or UFID.
- **Tree Traversals**: Print tree nodes in Inorder, Preorder, Postorder, or Level Count order.
- **Remove Inorder**: Remove a node at a specific position in the Inorder traversal.

## Program Structure

The main program consists of the following components:
- **`height(Node* N)`**: Calculates the height of a node.
- **`max(int a, int b)`**: Utility function to find the maximum of two values.
- **`newNode(string name, string id)`**: Creates a new node with a name and UFID.
- **`isValidInput(string input)`**: Validates user input against expected commands and arguments.
- **Main Execution**: Processes commands from the user and interacts with the AVL tree.

## Commands

The program supports the following commands:

1. **insert "name" UFID**: Inserts a node with the given name and UFID if UFID does not already exist.
2. **remove "name"/UFID**: Removes a node by name or UFID if it exists.
3. **search "name"/UFID**: Searches for a node by name or UFID, printing the node’s details if found.
4. **printInorder / printPreorder / printPostorder**: Prints the tree nodes in the respective traversal order.
5. **printLevelCount**: Prints the number of levels in the tree.
6. **removeInorder position**: Removes a node at the specified position in the Inorder traversal.

## Usage

1. Run the program and enter the number of commands you wish to execute.
2. Enter each command, ensuring proper formatting (e.g., `insert "John Doe" 12345678`).

Example input:
```
5
insert "John Doe" 12345678
insert "Jane Doe" 87654321
search 12345678
printInorder
remove "Jane Doe"
```

## Notes

- Extensive input validation that ensures correct format for all commands.
- Commands should have valid inputs for successful execution, as specified in the `isValidInput` function.

Go Gators!
