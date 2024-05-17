#include <iostream>

using namespace std;

class Node {
public:
    Node(int key): key(key), next(nullptr) {}

    int getKey() {
        return key;
    }

    Node* getNext() {
        return next;
    }

    void setNext(Node* next) {
        this->next = next;
        return;
    }

private:
    int key;
    Node *next;
};

class LinkedList {
public:
    LinkedList() {
        head = new Node(NULL);
    }

    Node* getHead() {
        return head;
    }

    void imprimir() {
        Node* aux = head;
        while(aux != nullptr) {
            cout << "Chave: " << aux->getKey() << endl;
            aux = aux->getNext();
        }

        return;
    }

    int size() {
        int size = 0;
        Node* aux = head->getNext();
        while(aux != nullptr) {
            ++size;
            aux = aux->getNext();
        }

        return size;
    }

    void inserir(int chave) {
        int size = this->size();
        Node* aux = head;

        for(int i=0; i<size; ++i){
            aux = aux->getNext();
        }

        aux->setNext(chave);

        return;
    };

    virtual void remover() {
        int size = this->size();
        Node* aux = head;

        if(size > 0) {
            for(int i=1; i<size; ++i){
                aux = aux->getNext();
            }

            delete aux->getNext();
            aux->setNext(nullptr);
        }

        return;
    }

    ~LinkedList() {
        Node *aux;
        while(head != nullptr) {
            aux = head->getNext();
            delete head;
            head = aux;
        }
    }

private:
    Node *head;
};

class Stack: public LinkedList {
public:
    Stack(): LinkedList() {}

    void inserir(int chave) override {
        int size = LinkedList::size();
        Node *aux = LinkedList::getHead();

        for(int i=0; i<size; ++i) {
            aux = aux->getNext();
        }

        aux->setNext(new Node(chave));

        return;
    }
};

class Queue: public LinkedList {
public:
    Queue(): LinkedList() {}

    void inserir(int chave) override {
        Node *temp = LinkedList::getHead()->getNext();
        Node *newNode = new Node(chave);
        newNode->setNext(temp);
        LinkedList::getHead()->setNext(newNode);

        return;
    }
};

int main() {
    Queue queue = Queue();
    Stack stack = Stack();


}