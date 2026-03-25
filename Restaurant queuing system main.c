#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

// Max Heap structure
struct MaxHeap {
    int arr[MAX_SIZE];
    int size;
};

// Initialize heap
void initHeap(struct MaxHeap* heap) {
    heap->size = 0;
}

// Swap two integers
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify up - used during insertion
void heapifyUp(struct MaxHeap* heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        
        if (heap->arr[index] > heap->arr[parent]) {
            swap(&heap->arr[index], &heap->arr[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

// Heapify down - used during deletion
void heapifyDown(struct MaxHeap* heap, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    
    // Check if left child exists and is greater
    if (left < heap->size && heap->arr[left] > heap->arr[largest]) {
        largest = left;
    }
    
    // Check if right child exists and is greater
    if (right < heap->size && heap->arr[right] > heap->arr[largest]) {
        largest = right;
    }
    
    // If largest is not the parent, swap and continue
    if (largest != index) {
        swap(&heap->arr[index], &heap->arr[largest]);
        heapifyDown(heap, largest);
    }
}

// Insert a new element into the heap
void insert(struct MaxHeap* heap, int value) {
    if (heap->size >= MAX_SIZE) {
        printf("Heap is full! Cannot insert %d\n", value);
        return;
    }
    
    heap->arr[heap->size] = value;
    heap->size++;
    heapifyUp(heap, heap->size - 1);
    
    printf("Inserted %d\n", value);
}

// Delete the root element from the heap
int deleteRoot(struct MaxHeap* heap) {
    if (heap->size == 0) {
        printf("Heap is empty! Cannot delete root.\n");
        return -1;
    }
    
    int root = heap->arr[0];
    
    // Replace root with last element
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    
    // Heapify down to restore heap property
    heapifyDown(heap, 0);
    
    printf("Deleted root: %d\n", root);
    return root;
}

// Print the heap as an array
void printHeap(struct MaxHeap* heap, char* message) {
    printf("%s: [", message);
    for (int i = 0; i < heap->size; i++) {
        printf("%d", heap->arr[i]);
        if (i < heap->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

// Print heap as a tree structure
void printHeapTree(struct MaxHeap* heap) {
    if (heap->size == 0) {
        printf("Heap is empty\n");
        return;
    }
    
    printf("Heap as tree:\n");
    int level = 0;
    int index = 0;
    int nodesInLevel = 1;
    
    while (index < heap->size) {
        // Print spaces for formatting
        for (int i = 0; i < (4 - level) * 2; i++) {
            printf(" ");
        }
        
        // Print nodes at current level
        for (int i = 0; i < nodesInLevel && index < heap->size; i++) {
            printf("%d", heap->arr[index]);
            if (i < nodesInLevel - 1 && index + 1 < heap->size) {
                printf("    ");
            }
            index++;
        }
        printf("\n");
        
        level++;
        nodesInLevel *= 2;
    }
    printf("\n");
}

int main() {
    struct MaxHeap heap;
    initHeap(&heap);
    
    printf("==\n");
    printf("   MAX HEAP IMPLEMENTATION\n");
    printf("==\n\n");
    
    // Insert 7 elements
    int elements[] = {50, 30, 40, 20, 35, 45, 55};
    int numElements = 7;
    
    printf("--- INSERTING ELEMENTS ---\n");
    for (int i = 0; i < numElements; i++) {
        insert(&heap, elements[i]);
        printHeap(&heap, "Heap array after insertion");
    }
    
    printf("\n--- FINAL HEAP BEFORE DELETION ---\n");
    printHeap(&heap, "Final heap array");
    printHeapTree(&heap);
    
    // Delete the root element
    printf("\n--- DELETING ROOT ELEMENT ---\n");
    deleteRoot(&heap);
    printHeap(&heap, "Heap array after deletion");
    printHeapTree(&heap);
    
    return 0;
}