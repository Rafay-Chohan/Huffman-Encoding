# Huffman-Encoding
Implementation of Huffman Encoding using heap in C++
This C++ code defines a program that implements a Huffman coding algorithm for compressing and decompressing text data. Here's a summarized description of the code's functionality:

1. **Header Includes:** The code includes necessary header files for input/output, string manipulation, file handling, and data structures like vectors.

2. **Queue Class:** Defines a template class `Queue` for a linked-list-based queue. It implements enqueue, dequeue, search, and other queue operations.

3. **Node Class:** Defines a template class `Node` for constructing binary tree nodes. It contains methods for displaying nodes and inserting nodes into the tree.

4. **Heap Resizing Function:** `GrowByTen` function resizes a dynamic array (heap) by reallocating memory in chunks of 10 elements.

5. **Heap Class:** Defines a template class `Heap` for a min-heap data structure. It supports updating, extracting the minimum element, heapifying, and swapping values.

6. **Function to Fill Min Heap:** `fillHeap` function takes characters and their frequencies from a queue and populates a min-heap of nodes containing pairs of frequency and character.

7. **Function to Build Huffman Tree:** `buildhuffmanTree` constructs a Huffman tree using the min-heap. It repeatedly extracts two minimum nodes, combines them into a new node, and inserts the new node back into the heap until a single root node remains.

8. **Functions for Text Handling:** The code includes functions for reading data from a file or user input and converting it into a string.

9. **Encoding Function:** The `Encode` function generates individual Huffman codes for each character in the Huffman tree.

10. **Decoding Function:** The `Decode` function takes a binary encoded string and uses the Huffman tree to decode it into the original text.

11. **Main Function:** The main function initializes the Huffman encoding process. It collects input text, builds the Huffman tree, encodes the text, and provides options for decoding or saving the encoded code.

Overall, the code implements the Huffman coding algorithm, a widely used technique for lossless data compression. It constructs a Huffman tree based on character frequencies, generates codes for each character, and allows for text compression and decompression.
