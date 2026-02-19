template <typename T>
DoublyList<T>::DoublyList() : header(new Node), trailer(new Node) {
  header->next = trailer;
  trailer->prev = header;
}

template <typename T>
DoublyList<T>::DoublyList(const DoublyList<T> &copyObj)
    : header(new Node), trailer(new Node) {
  copy(copyObj);
}

template <typename T>
DoublyList<T> &DoublyList<T>::operator=(const DoublyList<T> &rightObj) {
  if (this != &rightObj) {
    clear();
    copy(rightObj);
  }
  return *this;
}

template <typename T>
DoublyList<T>::~DoublyList() {
  clear();
  delete header;
  delete trailer;
  header = trailer = nullptr;
}

template <typename T> 
void DoublyList<T>::append(const T &elem) {
  // Create the new node with the value 'elem'
  Node *newNode = new Node(elem);

  // Insert 'newNode' before 'trailer'
  // The current last node is 'trailer->prev'
  Node *lastNode = this->trailer->prev;

  // Link newNode to its neighbors
  newNode->next = this->trailer;
  newNode->prev = lastNode;

  // Link neighbors to newNode
  lastNode->next = newNode;
  this->trailer->prev = newNode;

  // Increase the length
  this->length++;
}

template <typename T>
void DoublyList<T>::clear() {
  for (Node *curr = nullptr; header->next != trailer;) {
    curr = header->next->next;
    delete header->next;
    header->next = curr;
  }

  trailer->prev = header;
  this->length = 0;
}

template <typename T>
void DoublyList<T>::copy(const DoublyList<T> &copyObj) {
  this->length = copyObj.length;
  Node *myCurr = header;
  Node *copyCurr = copyObj.header->next;

  while (copyCurr != copyObj.trailer) {
    Node *n = new Node(copyCurr->value);
    myCurr->next = n;
    n->prev = myCurr;
    myCurr = n;
    copyCurr = copyCurr->next;
  }

  myCurr->next = trailer;
  trailer->prev = myCurr;
}

template <typename T>
T DoublyList<T>::getElement(int position) const {
  // TO DO: Implent code for getElement at position
  if (position < 0 || position >= this->length)
    throw string("getElement: error, position out of bounds.");

    Node* curr = this->header->next;

  for (int i = 0; i < position; ++i) {
    curr = curr->next;
  }

  return curr->value;
}

template <typename T>
int DoublyList<T>::getLength() const {
  return this->length;
}

template <typename T>
void DoublyList<T>::insert(int position, const T &elem) {
  // TO DO: Implement code to insert an element to list
  if (position < 0 || position >= this->length)
    throw string("insert: error, position out of bounds.");

  // Start at the first node(header isn't the first node, like in simple list)
  Node *curr = this->header->next;

  // Traverse to the node currently at 'position'
  for (int i = 0; i < position; ++i) {
    curr = curr->next;
  }

  // Insert newNode BEFORE curr
  Node *newNode = new Node(elem);
  Node *prevNode = curr->prev;

  newNode->next = curr;
  newNode->prev = prevNode;

  prevNode->next = newNode;
  curr->prev = newNode;

  this->length++;
}

template <typename T>
bool DoublyList<T>::isEmpty() const {
  return this->length == 0 && header->next == trailer &&
         trailer->prev == header;
}

template <typename T>
void DoublyList<T>::remove(int position) {
  // TO DO: Implement code to remove element at given position
  if (position < 0 || position >= this->length)
    throw string("remove: error, position out of bounds.");

  Node *curr = this->header->next;
  for (int i = 0; i < position; ++i) {
    curr = curr->next;
  }

  Node *newNode = curr->next;
  Node *prevNode = curr->prev;

  prevNode->next = newNode;
  newNode->prev = prevNode;

  delete curr;
  this->length--;
}

template <typename T>
bool DoublyList<T>::search(const T &elem) const {
  // TO DO: Implement code to search for element
  //if (position < 0 || position >= this->length)
    //throw string("search: error, position out of bounds.");

  Node *curr = this->header->next;
  while (curr != nullptr){
    curr = curr->next;

  if (curr->value == elem) {
    return true;
  }
}
  return false;
}

template <typename T>
void DoublyList<T>::replace(int position, const T &elem) {
  // TO DO: Add code for replace method
  if (position < 0 || position >= this->length)
    throw string("replace: error, position out of bounds.");

  Node *curr = this->header->next;
  for (int i = 0; i < position; ++i) {
    curr = curr->next;
  }

  curr->value = elem;
}

template <typename T>
ostream &operator<<(ostream &outStream, const DoublyList<T> &myObj) {
  if (myObj.isEmpty()) {
    outStream << "List is empty, no elements to display.\n";
  } else {
    typename DoublyList<T>::Node *curr = myObj.header->next;
    while (curr != myObj.trailer) {
      outStream << curr->value;
      if (curr->next != myObj.trailer) {
        outStream << " <--> ";
      }
      curr = curr->next;
    }
    outStream << endl;
  }

  return outStream;
}


