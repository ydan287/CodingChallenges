#include <iostream>

using namespace std;

#define GROWTH_FACTOR 2

template<typename T>
class ResizableArray {
  int allocated_size;
  int size;
  T *arr;

  void resize(int new_size) {
    allocated_size = new_size;
    int *new_array = new int[allocated_size];
    for (int i = 0; i < size; i++) {
      new_array[i] = arr[i];
    }
    delete arr;
    arr = new_array;
  }

public:
  ResizableArray(int arr_size) {
    arr = new int[arr_size];
    allocated_size = arr_size;
    size = 0;
  }
  int at(int index) { return arr[index]; }
  bool is_empty() { return size == 0; }
  void append(T data) {
    arr[size++] = data;
    if (size >= allocated_size) {
      resize(allocated_size * GROWTH_FACTOR);
    }
  }

  T remove_last() {
    if (is_empty()) {
      return -1;
    }
    T last = arr[--size];
    if (size < allocated_size / (GROWTH_FACTOR * GROWTH_FACTOR)) {
      resize(allocated_size / GROWTH_FACTOR);
    }
    return last;
  }

  void print_array() {
    cout << "size: " << size << endl;
    cout << "allocated_size: " << allocated_size << endl;
    for (int i = 0; i < size; i++) {
      cout << arr[i] << " ";
    }
    cout << endl;
  }
};

int main(int argc, char const *argv[]) {
  ResizableArray<int> arr(4);
  arr.print_array();
  arr.append(1);
  arr.print_array();
  arr.append(2);
  arr.print_array();
  arr.append(3);
  arr.print_array();
  arr.append(4);
  arr.print_array();
  arr.append(5);
  arr.print_array();
  arr.append(6);
  arr.print_array();
  arr.append(7);
  arr.print_array();
  arr.append(8);
  arr.print_array();
  arr.append(9);
  arr.print_array();
  arr.append(10);
  arr.print_array();
  arr.append(11);
  arr.print_array();
  arr.append(12);
  arr.print_array();
  arr.remove_last();
  arr.print_array();
  arr.remove_last();
  arr.print_array();
  arr.remove_last();
  arr.print_array();
  arr.remove_last();
  arr.print_array();
  arr.remove_last();
  arr.print_array();
  arr.remove_last();
  arr.print_array();
  arr.remove_last();
  arr.print_array();
  arr.remove_last();
  arr.print_array();
  arr.remove_last();
  arr.print_array();
  arr.remove_last();
  arr.print_array();
  arr.remove_last();
  arr.print_array();
  arr.remove_last();
  arr.print_array();

  return 0;
}
