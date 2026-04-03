// =============================================================================
// CT15: Binary Search Tree — Implementation
// =============================================================================
//
// Student implementation file.
// Follow along in class — each TODO section will be completed together.
//
// Node structure is defined in BinarySearchTree.h.
// BST property: for every node N,
//   all values in N->left  subtree < N->data
//   all values in N->right subtree > N->data
//

#include "BinarySearchTree.h"
#include <iostream>

// =============================================================================
// 1. Constructor / Destructor  [PROVIDED]
// =============================================================================

// ---------------------------------------------------------------------------
// BinarySearchTree() — default constructor
// ---------------------------------------------------------------------------
//
// ! DISCUSSION: An empty tree has only one state: root_ == nullptr.
//   - no nodes exist yet; every operation must handle this base case
//   - height of an empty tree is -1 by convention
//
BinarySearchTree::BinarySearchTree() : root_(nullptr) {}  // : member initializer list

// ---------------------------------------------------------------------------
// ~BinarySearchTree() — destructor
// ---------------------------------------------------------------------------
//
// ! DISCUSSION: Why we must explicitly free every node.
//   - Node objects are heap-allocated (new Node(val)) and never freed
//     automatically
//   - the destructor is our only guaranteed cleanup point
//   - we delegate to destroy_() which does a post-order walk
//
BinarySearchTree::~BinarySearchTree() {
    destroy_(root_);
}

// ---------------------------------------------------------------------------
// destroy_() — post-order recursive deletion  [PROVIDED]
// ---------------------------------------------------------------------------
//
// ! DISCUSSION: Destruction must be post-order (children before parent).
//   - if we deleted the parent first we would lose the pointers to its
//     children and leak every node below it
//   - post-order guarantees every child is freed before we free the parent
//   - this is the same visit order as postorder traversal — left, right, node
//
void BinarySearchTree::destroy_(Node* node) {
    if (!node) return;
    destroy_(node->left);
    destroy_(node->right);
    delete node;
}

// =============================================================================
// 2. insert / insert_
// =============================================================================

// ---------------------------------------------------------------------------
// insert() — public wrapper  [PROVIDED]
// ---------------------------------------------------------------------------
//
// ! DISCUSSION: Why insert_ returns a Node*.
//   - the recursive helper returns the root of the subtree it just worked on
//   - this lets the parent update its child pointer in one clean assignment
//   - pattern: root_ = insert_(root_, value)
//   - avoids passing Node** or storing parent pointers
//
void BinarySearchTree::insert(int value) {
    root_ = insert_(root_, value);
}

// ---------------------------------------------------------------------------
// insert_() — recursive insert
// ---------------------------------------------------------------------------
//
// ? SEE DIAGRAM: images/insert_path.svg — insert path for value 40 into example tree
//
// ! DISCUSSION: The BST property guides every decision.
//   - at each node we ask: is value < node->data, or > node->data?
//   - less-than: the new value belongs in the LEFT subtree
//   - greater-than: the new value belongs in the RIGHT subtree
//   - equal: duplicate — silently return without inserting
//   - the new node always lands at a nullptr slot (a leaf position)
//
// ! DISCUSSION: New nodes always become leaves.
//   - we never re-link existing nodes; we only add at the bottom
//   - this keeps the logic simple but can create imbalanced trees
//     (AVL trees, the next topic, fix this)
//
Node* BinarySearchTree::insert_(Node* node, int value) {
    // TODO 1: Implement recursive insert
    //   - Base case: if node is nullptr, return a new Node(value)
    //   - If value < node->data: recurse left, assign result to node->left
    //   - If value > node->data: recurse right, assign result to node->right
    //   - If value == node->data: do nothing (duplicate)
    //   - Return node (so the parent can reattach its child pointer)
    if (!node) {
        return new Node(value);
	}
    if (value < node->data) {
        node->left = insert_(node->left, value);
    } else if (value > node->data) {
        node->right = insert_(node->right, value);
	}

    return node;
}

// =============================================================================
// 3. search / search_
// =============================================================================

// ---------------------------------------------------------------------------
// search() — public wrapper  [PROVIDED]
// ---------------------------------------------------------------------------
bool BinarySearchTree::search(int value) const {
    return search_(root_, value);
}

// ---------------------------------------------------------------------------
// search_() — recursive search
// ---------------------------------------------------------------------------
//
// ? SEE DIAGRAM: images/search_path.svg — search path showing halving at each node
//
// ! DISCUSSION: BST search is identical to binary search on a sorted array.
//   - at each node we eliminate an entire subtree based on one comparison
//   - if value < node->data, the value cannot be in the right subtree
//   - if value > node->data, the value cannot be in the left subtree
//   - each step reduces the problem to roughly half the remaining nodes
//
// ! DISCUSSION: Time complexity.
//   - O(log n) on a balanced tree — height is approximately log2(n)
//   - O(n) on a degenerate tree (sorted insertion creates a right spine)
//   - this is why balance matters — motivates AVL trees
//
bool BinarySearchTree::search_(Node* node, int value) const {
    // TODO 2: Implement recursive search
    //   - Base case: if node is nullptr, return false (not found)
    //   - If value == node->data, return true (found!)
    //   - If value < node->data, recurse left and return the result
    //   - Otherwise, recurse right and return the result
    if (!node) return false;
    if (value == node->data) return true;
    if (value < node->data) return search_(node->left, value);
    return search_(node->right, value);
}

// =============================================================================
// 4. Traversals
// =============================================================================
//
// ? SEE DIAGRAM: images/traversal_orders.svg — all three traversal orders on same tree
//
// A traversal visits every node in the tree exactly once.
// The three classic orders differ only in WHEN the current node is "visited"
// (i.e., when we print it) relative to its subtrees.
//

// ---------------------------------------------------------------------------
// 4a. inorder / inorder_  — Left → Root → Right
// ---------------------------------------------------------------------------
//
// ! DISCUSSION: In-order produces SORTED output on a BST.
//   - by the BST property, all left values < current < all right values
//   - visiting left first, then current, then right gives ascending order
//   - this is the most common traversal for BSTs (printing sorted data,
//     checking if a tree is a valid BST, etc.)
//
void BinarySearchTree::inorder() const {
    inorder_(root_);
    std::cout << std::endl;
}

void BinarySearchTree::inorder_(Node* node) const {
    // TODO 3: Implement in-order traversal (Left → Root → Right)
    //   - Base case: if node is nullptr, return
    //   - Recurse on node->left
    //   - Print node->data followed by a space
    //   - Recurse on node->right
    if (!node) return;
    inorder_(node->left);
    std::cout << node->data << " ";
    inorder_(node->right);
}

// ---------------------------------------------------------------------------
// 4b. preorder / preorder_  — Root → Left → Right
// ---------------------------------------------------------------------------
//
// ! DISCUSSION: Pre-order visits the root BEFORE its subtrees.
//   - the root is always the first value printed
//   - useful for: copying/cloning a tree (insert in pre-order to rebuild
//     the same shape), serializing a tree to a file
//   - if you read the output back and insert each value in order, you
//     recreate the identical tree structure
//
void BinarySearchTree::preorder() const {
    preorder_(root_);
    std::cout << std::endl;
}

void BinarySearchTree::preorder_(Node* node) const {
    // TODO 4: Implement pre-order traversal (Root → Left → Right)
    //   - Base case: if node is nullptr, return
    //   - Print node->data followed by a space
    //   - Recurse on node->left
    //   - Recurse on node->right
    if (!node) {
        return;
	}
 std::cout << node->data << " ";
    preorder_(node->left);
    preorder_(node->right);

}

// ---------------------------------------------------------------------------
// 4c. postorder / postorder_  — Left → Right → Root
// ---------------------------------------------------------------------------
//
// ! DISCUSSION: Post-order visits the root AFTER its subtrees.
//   - children are always processed before their parent
//   - this is exactly the order needed for safe deletion (destroy_() uses it)
//   - also used in expression tree evaluation: evaluate operands before
//     applying the operator at the parent node
//
void BinarySearchTree::postorder() const {
    postorder_(root_);
    std::cout << std::endl;
}

void BinarySearchTree::postorder_(Node* node) const {
    // TODO 5: Implement post-order traversal (Left → Right → Root)
    //   - Base case: if node is nullptr, return
    //   - Recurse on node->left
    //   - Recurse on node->right
    //   - Print node->data followed by a space
    if (!node) {
        return;
    }
    postorder_(node->left);
    postorder_(node->right);
    std::cout << node->data << " ";

}

// =============================================================================
// 5. height / height_
// =============================================================================

// ---------------------------------------------------------------------------
// height() — public wrapper  [PROVIDED]
// ---------------------------------------------------------------------------
int BinarySearchTree::height() const {
    return height_(root_);
}

// ---------------------------------------------------------------------------
// height_() — recursive height
// ---------------------------------------------------------------------------
//
// ! DISCUSSION: Height determines ALL operation costs.
//   - search, insert, and remove each take O(height) time
//   - balanced tree: height ≈ log2(n) → O(log n) operations
//   - degenerate tree: height = n - 1 → O(n) operations (same as linked list)
//   - AVL trees maintain height ≈ log2(n) automatically via rotations
//
// ! DISCUSSION: The base case: nullptr has height -1.
//   - a leaf node has no children (both nullptr, height -1 each)
//   - leaf height = 1 + max(-1, -1) = 1 + (-1) = 0  ✓
//   - a one-child node: 1 + max(0, -1) = 1 + 0 = 1   ✓
//   - using -1 (not 0) for nullptr avoids an off-by-one in every case
//
int BinarySearchTree::height_(Node* node) const {
    // TODO 6: Implement recursive height
    //   - Base case: if node is nullptr, return -1
    //   - Recursively get height of left subtree
    //   - Recursively get height of right subtree
    //   - Return 1 + max(left_height, right_height)
    //     (the +1 counts the edge from this node to its tallest child)
    if (!node) {
        return -1;
	}
    int lh = height_(node->left);
    int rh = height_(node->right);
    return 1 + std::max(lh, rh);
}

// =============================================================================
// 6. is_empty  [PROVIDED]
// =============================================================================

bool BinarySearchTree::is_empty() const {
    return root_ == nullptr;
}

// =============================================================================
// 7. Functors — flexible traversal
// =============================================================================
//
// ! DISCUSSION: The functor pattern in action.
//   - inorder_apply is a TEMPLATE method defined in the header
//   - the compiler generates a separate version for each functor type
//   - no virtual functions, no inheritance, no runtime overhead
//   - the functor is passed BY REFERENCE so stateful functors keep their state
//
// ! DISCUSSION: Comparing approaches.
//   - hardcoded print (inorder): simple, but can ONLY print
//   - function pointer: flexible, but can't carry state between calls
//   - functor (operator()): flexible AND stateful — best of both worlds
//   - C++11 lambdas are essentially anonymous functors (same idea, less syntax)
//
// ! DISCUSSION: Usage examples (shown in main.cpp).
//   - PrintFunctor pf; tree.inorder_apply(pf);   // same output as inorder()
//   - SumFunctor sf;   tree.inorder_apply(sf);   // sf.total now holds the sum
//   - CountFunctor cf; tree.inorder_apply(cf);   // cf.count now holds node count
//
// NOTE: inorder_apply and inorder_apply_ are template methods defined
//       entirely in the header — no .cpp code needed. This section exists
//       only for the DISCUSSION comments above.
