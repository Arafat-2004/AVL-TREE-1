#include <iostream>
#include <algorithm> // For max() function

using namespace std;

// AVL Tree Node structure
struct Node {
    int data;
    Node* left;
    Node* right;
    int height;  // Height of the node

    Node(int val) {
        data = val;
        left = right = nullptr;
        height = 1;
    }
};
// Function to get the height of a node
int getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

// Function to get the balance factor of a node
int getBalanceFactor(Node* node) {
    if (node == nullptr)
        return 0;
     return getHeight(node->left) - getHeight(node->right);
}

// Right rotate subtree rooted at y
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x; // New root
}

// Left rotate subtree rooted at x
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y; // New root
}

// Function to insert a node with a given value
Node* insert(Node* root, int value) {
    // Step 1: Perform the normal BST insertion
    if (root == nullptr)
        return new Node(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    else
        return root; // Duplicates are not allowed

    // Step 2: Update the height of this ancestor node
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Step 3: Get the balance factor of this ancestor node to check whether it became unbalanced
    int balance = getBalanceFactor(root);

    // Step 4: If the node becomes unbalanced, then there are 4 cases to handle

    // Left Left Case (Right rotation)
    if (balance > 1 && value < root->left->data)
        return rightRotate(root);

    // Right Right Case (Left rotation)
    if (balance < -1 && value > root->right->data)
        return leftRotate(root);

    // Left Right Case (Left rotation followed by right rotation)
    if (balance > 1 && value > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case (Right rotation followed by left rotation)
    if (balance < -1 && value < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root; // Return the (unchanged) node pointer
}

// Function to print the inorder traversal of the tree
void inorderTraversal(Node* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        cout << root->data << " ";
        inorderTraversal(root->right);
    }
}
// Function to print the tree height
int treeHeight(Node* root) {
    if (root == nullptr)
        return 0;
    return root->height;
}
// Function to search for a value in the AVL tree
bool search(Node* root, int value) {
    if (root == nullptr)
        return false;
    if (root->data == value)
        return true;
    else if (value < root->data)
        return search(root->left, value);
    else
        return search(root->right, value);
}
// Function to find the minimum value node in the tree
Node* findMin(Node* root) {
    while (root->left != nullptr)
        root = root->left;
    return root;
}
// Function to delete a node from the AVL tree
Node* deleteNode(Node* root, int value) {
    if (root == nullptr)
        return root;

    if (value < root->data)
        root->left = deleteNode(root->left, value);
    else if (value > root->data)
        root->right = deleteNode(root->right, value);
    else {
        // Node with one or no child
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }

            delete temp;
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            Node* temp = findMin(root->right);

            // Copy the inorder successor's data to this node
            root->data = temp->data;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->data);
        }
    }
 // If the tree had only one node, return
    if (root == nullptr)
        return root;

    // Update the height of the current node
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Check the balance factor
    int balance = getBalanceFactor(root);

    // Balance the tree

    // Left Left Case
    if (balance > 1 && getBalanceFactor(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalanceFactor(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int main() {
    Node* root = nullptr;

    // Insert nodes into the AVL tree
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 25);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 40);

    // Print the inorder traversal of the AVL tree
    cout << "Inorder traversal of the AVL tree: ";
    inorderTraversal(root);
    cout << endl;

    return 0;
}
