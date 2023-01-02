#include <iostream>

using namespace std;

struct Node {
  Node *next;
  int data;
};

Node *initLinkedList(int arr[], int size) {
  Node *head = new Node;
  head->next = nullptr;
  head->data = arr[0];
  Node *curr = nullptr;
  for (int i = 0; i < size; i++) {
    Node *newNode = new Node;
    newNode->next = nullptr;
    newNode->data = arr[i];
    if (i == 0) {
      head = newNode;
      curr = newNode;
    } else {
      curr->next = newNode;
      curr = curr->next;
    }
  }
  return head;
}

Node *removeNextNode(Node *node) {
  if (node->next == nullptr) {
    return nullptr;
  }
  Node *tmp = node->next;
  node->next = node->next->next;
  return tmp;
}

Node *appendToHead(Node *head, Node *node) {
  node->next = head;
  return node;
}

void printLinkedList(Node *head) {
  Node *curr = head;
  cout << head->data;
  while (curr->next != nullptr) {
    cout << " -> " << curr->next->data;
    curr = curr->next;
  }
  cout << endl;
}

void partitions(Node *head, int P) {
  Node *rightPartHead = nullptr;
  Node *curr = head;
  int i = 0;
  while (curr->next != nullptr) {
    if (curr->next->data >= P) {
      Node *tmp = removeNextNode(curr);
      rightPartHead = appendToHead(rightPartHead, tmp);
    } else {
      curr = curr->next;
    }
  }
  if (head->data >= P) {
    int tmp = head->data;
    head->data = curr->data;
    curr->data = tmp;
  }
  curr->next = rightPartHead;
}

int main(int argc, char const *argv[]) {
  int arr[] = {10, 3, 5, 8, 5, 10, 2, 1};
  Node *head = initLinkedList(arr, 8);
  printLinkedList(head);
  partitions(head, 5);
  printLinkedList(head);
  return 0;
}
