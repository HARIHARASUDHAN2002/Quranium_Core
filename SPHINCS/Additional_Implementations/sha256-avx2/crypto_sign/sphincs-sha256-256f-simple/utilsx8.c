#include <string.h>

#include "utils.h"
#include "params.h"
#include "thashx8.h"
#include "address.h"

/**
 * For a given leaf index, computes the authentication path and the resulting
 * root node using Merkle's TreeHash algorithm.
 * Expects the layer and tree parts of the tree_addr to be set, as well as the
 * tree type (i.e. SPX_ADDR_TYPE_HASHTREE or SPX_ADDR_TYPE_FORSTREE).
 * Applies the offset idx_offset to indices before building addresses, so that
 * it is possible to continue counting indices across trees.
 */
void treehashx8(unsigned char *rootx8, unsigned char *auth_pathx8,
                const unsigned char *sk_seed, const unsigned char *pub_seed,
                uint32_t leaf_idx[8], uint32_t idx_offset[8],
                uint32_t tree_height,
                void (*gen_leafx8)(
                   unsigned char* /* leaf0 */,
                   unsigned char* /* leaf1 */,
                   unsigned char* /* leaf2 */,
                   unsigned char* /* leaf3 */,
                   unsigned char* /* leaf4 */,
                   unsigned char* /* leaf5 */,
                   unsigned char* /* leaf6 */,
                   unsigned char* /* leaf7 */,
                   const unsigned char* /* sk_seed */,
                   const unsigned char* /* pub_seed */,
                   uint32_t /* addr_idx0 */,
                   uint32_t /* addr_idx1 */,
                   uint32_t /* addr_idx2 */,
                   uint32_t /* addr_idx3 */,
                   uint32_t /* addr_idx4 */,
                   uint32_t /* addr_idx5 */,
                   uint32_t /* addr_idx6 */,
                   uint32_t /* addr_idx7 */,
                   const uint32_t[8] /* tree_addr */),
                uint32_t tree_addrx8[8*8])
{
    // Stack to store the nodes of the Merkle tree
    unsigned char stackx8[8*(tree_height + 1)*SPX_N];

    // Array to store the heights of the nodes on the stack
    unsigned int heights[tree_height + 1];

    // Offset into the stack
    unsigned int offset = 0;

    // Loop counter
    uint32_t idx;

    // Index of the node in the tree
    uint32_t tree_idx;

    // Loop counter
    unsigned int j;

    // Loop over all leaf nodes
    for (idx = 0; idx < (uint32_t)(1 << tree_height); idx++) {
        // Add the next leaf node to the stack
        gen_leafx8(stackx8 + 0*(tree_height + 1)*SPX_N + offset*SPX_N,
                   stackx8 + 1*(tree_height + 1)*SPX_N + offset*SPX_N,
                   stackx8 + 2*(tree_height + 1)*SPX_N + offset*SPX_N,
                   stackx8 + 3*(tree_height + 1)*SPX_N + offset*SPX_N,
                   stackx8 + 4*(tree_height + 1)*SPX_N + offset*SPX_N,
                   stackx8 + 5*(tree_height + 1)*SPX_N + offset*SPX_N,
                   stackx8 + 6*(tree_height + 1)*SPX_N + offset*SPX_N,
                   stackx8 + 7*(tree_height + 1)*SPX_N + offset*SPX_N,
                   sk_seed, pub_seed,
                   idx + idx_offset[0],
                   idx + idx_offset[1],
                   idx + idx_offset[2],
                   idx + idx_offset[3],
                   idx + idx_offset[4],
                   idx + idx_offset[5],
                   idx + idx_offset[6],
                   idx + idx_offset[7],
                   tree_addrx8);

        // Increment the offset
        offset++;

        // Set the height of the node
        heights[offset - 1] = 0;

        // Check if this node is needed for the authentication path
        for (j = 0; j < 8; j++) {
            if ((leaf_idx[j] ^ 0x1) == idx) {
                // Copy the node to the authentication path
                memcpy(auth_pathx8 + j*tree_height*SPX_N,
                       stackx8 + j*(tree_height + 1)*SPX_N + (offset - 1)*SPX_N, SPX_N);
            }
        }

        // While the top-most nodes are of equal height
        while (offset >= 2 && heights[offset - 1] == heights[offset - 2]) {
            // Compute the index of the new node
            tree_idx = (idx >> (heights[offset - 1] + 1));

            // Set the address of the new node
            for (j = 0; j < 8; j++) {
                set_tree_height(tree_addrx8 + j*8, heights[offset - 1] + 1);
                set_tree_index(tree_addrx8 + j*8,
                               tree_idx + (idx_offset[j] >> (heights[offset-1] + 1)));
            }

            // Hash the top-most nodes from the stack together
            thashx8(stackx8 + 0*(tree_height + 1)*SPX_N + (offset - 2)*SPX_N,
                    stackx8 + 1*(tree_height + 1)*SPX_N + (offset - 2)*SPX_N,
                    stackx8 + 2*(tree_height + 1)*SPX_N + (offset - 2)*SPX_N,
                    stackx8 + 3*(tree_height + 1)*SPX_N + (offset - 2)*SPX_N,
                    stackx8 + 4*(tree_height + 1)*SPX_N + (offset - 2)*SPX_N,
                    stackx8 + 5*(tree_height + 1)*SPX_N + (offset - 2)*SPX_N,
                    stackx8 + 6*(tree_height + 1)*SPX_N + (offset - 2)*SPX_N,
                    stackx8 + 7*(tree_height + 1)*SPX_N + (offset - 2)*SPX_N,
                    stackx8 + 0*(tree_height + 1)*SPX_N + (offset - 2)*SPX_N,
                    stackx8 + 1*(tree_height + 1)*SPX_N + (offset - 2)*SPX_N,
                    stackx8 + 2*(tree_height + 1)*SPX_N + (offset - 2)*SPX_N,
                    stackx8 + 3*(tree_height + 1)*SPX_N + (offset - 2)*SPX_N,
                    stackx8 + 4*(tree_height + 1)*SPX_N + (offset - 2)*SPX_N,
                    stackx8 + 5*(tree_height + 1)*SPX_N + (offset - 2)*SPX_N,
                    stackx8 + 6*(tree_height + 1)*SPX_N + (offset - 2)*SPX_N,
                    stackx8 + 7*(tree_height + 1)*SPX_N + (offset - 2)*SPX_N, 2, pub_seed, tree_addrx8);

            // Decrement the offset
            offset--;

            // Increment the height of the top-most node
            heights[offset - 1]++;

            // Check if this node is needed for the authentication path
            for (j = 0; j < 8; j++) {
                if (((leaf_idx[j] >> heights[offset - 1]) ^ 0x1) == tree_idx) {
                    // Copy the node to the authentication path
                    memcpy(auth_pathx8 + j*tree_height*SPX_N + heights[offset - 1]*SPX_N,
                           stackx8 + j*(tree_height + 1)*SPX_N + (offset - 1)*SPX_N, SPX_N);
                }
            }
        }
    }

    // Copy the root node to the output
    for (j = 0; j < 8; j++) {
        memcpy(rootx8 + j*SPX_N, stackx8 + j*(tree_height + 1)*SPX_N, SPX_N);
    }
}
