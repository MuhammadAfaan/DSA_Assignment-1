#include <iostream>
#include <string>

using namespace std;

class Node {
public:
    string value;
    Node* next;

    Node(const string& v) : value(v), next(nullptr) {}
};

class PrimeList {
public:
    Node* head;
    Node* tail;
    int length;

    PrimeList() : head(nullptr), tail(nullptr), length(0) {}

    void addNode(const string& v) {
        Node* newNode = new Node(v);
        if (length == 0) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        length++;
    }

    bool isDivisibleByPrime(long long p) {
        long long remainder = 0;
        Node* current = head;

        while (current != nullptr) {
            string numStr = current->value;

            for (char d : numStr) {
                remainder = (remainder * 10 + (d - '0')) % p;
            }

            current = current->next;
        }

        return remainder == 0;
    }

    bool checkPrime() {
        for (long long p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47}) {
            if (isDivisibleByPrime(p)) {
                cout << "The number is divisible by " << p << endl;
                return false;
            }
        }

        return true;
    }

    ~PrimeList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

int main() {
    PrimeList* primeList = new PrimeList();

    primeList->addNode("87345761283");
    primeList->addNode("84576343829");
    primeList->addNode("73689827365");
    primeList->addNode("53827365982");
    primeList->addNode("73653826398");
    primeList->addNode("73659823659");
    primeList->addNode("87236598273");
    primeList->addNode("65928736598");
    primeList->addNode("15735649871");
    primeList->addNode("59232635422");
    primeList->addNode("27365982736");
    primeList->addNode("59283659827");
    primeList->addNode("49827365498");
    primeList->addNode("72365982736");
    primeList->addNode("36298273559");
    primeList->addNode("82736598273");
    primeList->addNode("65985736598");
    primeList->addNode("36598273659");
    primeList->addNode("82736598273");
    primeList->addNode("73659827365");
    primeList->addNode("98273659827");
    primeList->addNode("65982736599");

    cout << "Checking the number is prime or not..." << endl;
    cout << "Prime Check: " << endl;

    if (primeList->checkPrime()) {
        cout << "True, is Prime" << endl;
    } else {
        cout << "False, Not Prime" << endl;
    }

    delete primeList;
    return 0;
}