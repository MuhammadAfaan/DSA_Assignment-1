#include <iostream>
using namespace std;

class Node {
public:
    int id;
    int total_time;
    int remaining_time;
    Node* next;

    Node(int process_id, int exec_time) 
        : id(process_id), total_time(exec_time), remaining_time(exec_time), next(nullptr) {}
};

class Scheduler {
private:
    Node* head_node;
    int time_slice;

public:
    Scheduler(int slice) : time_slice(slice), head_node(nullptr) {}

    void addNode(int id, int exec_time) {
        Node* newNode = new Node(id, exec_time);
        if (head_node == nullptr) {
            head_node = newNode;
            head_node->next = head_node;
        } else {
            Node* temp = head_node;
            while (temp->next != head_node)
                temp = temp->next;
            temp->next = newNode;
            newNode->next = head_node;
        }
        cout << "Node added: P" << id << " (Remaining: " << exec_time << ")\n";
    }

    void executeNodes() {
        if (head_node == nullptr) {
            cout << "No nodes to execute.\n";
            return;
        }

        Node* current = head_node;
        int cycle_count = 1;

        while (head_node != nullptr) {
            cout << "Cycle " << cycle_count << ": ";
            Node* temp = current;
            bool all_done = true;

            do {
                if (temp->remaining_time > 0) {
                    all_done = false;
                    int time_allocated = min(time_slice, temp->remaining_time);
                    temp->remaining_time -= time_allocated;
                    cout << "P" << temp->id << " (Remaining: " << temp->remaining_time << "), ";
                }

                temp = temp->next;
            } while (temp != current && head_node != nullptr);

            cout << endl;

            if (head_node == nullptr) {
                break;
            }

            if (current->remaining_time == 0) {
                Node* nextNode = current->next;
                removeNode(current->id);
                current = nextNode;
            } else {
                current = current->next;
            }

            cycle_count++;
        }
    }

    void removeNode(int id) {
        if (head_node == nullptr)
            return;

        Node* temp = head_node;
        Node* previous = nullptr;

        do {
            if (temp->id == id) {
                cout << "Node P" << id << " completed and removed.\n";

                if (previous == nullptr) {
                    if (temp->next == head_node) {
                        head_node = nullptr;
                    } else {
                        Node* last = head_node;
                        while (last->next != head_node)
                            last = last->next;
                        head_node = temp->next;
                        last->next = head_node;
                    }
                } else {
                    previous->next = temp->next;
                }

                delete temp;
                return;
            }

            previous = temp;
            temp = temp->next;
        } while (temp != head_node);
    }
};

int main() {
    int time_per_cycle = 80;
    Scheduler scheduler(time_per_cycle);

    scheduler.addNode(1, 100);
    scheduler.addNode(2, 500);
    scheduler.addNode(3, 800);

    scheduler.executeNodes();

    scheduler.addNode(4, 900);
    scheduler.executeNodes();

    return 0;
}