#include "comp_linked_list_vector.hpp"

ListVector::ListVector(int inSize, double* vector, bool ROW) : size(inSize), Head(nullptr), row(ROW) {
    Head = new Vector_Node;
    Vector_Listnp Crnt = Head;
    Head->next = NULL;
    Head->index = 0;
    Head->val = 0;
    bool headmade = false;

    for (int i = 0; i < inSize; i++) {
        if (vector[i]) {
            if (!headmade) {
                Head->val = vector[i];
                Head->index = i;
                Head->next = Crnt;
                headmade = true;
                Crnt = Head;
            } else {
                Vector_Listnp p = new Vector_Node;
                p->val = vector[i];
                p->index = i;
                p->next = NULL;
                Crnt->next = p;
                Crnt = p;
            }
        }
    }
}

void ListVector::print() {
    Vector_Listnp crnt = Head;
    bool fin = false;
    for (int i = 0; i < size; i++) {
        if (i == crnt->index && !fin) {
            std::cout << crnt->val << " ";
            if (crnt->next == NULL) fin = true;
            else crnt = crnt->next;
        } else {
            std::cout << "0 ";
        }
    }
    std::cout << std::endl;
    crnt = NULL;
    delete crnt;
}

Vector_Listnp ListVector::Valsearch(double check) {
    if (!check) {
        std::cout << "Does not work for 0" << std::endl;
        return NULL;
    }
    Vector_Listnp crnt = Head;
    while (crnt) {
        if (crnt->val == check) return crnt;
        crnt = crnt->next;
    }
    return NULL;
}

Vector_Listnp ListVector::INDsearch(int IDX) {
    if (size <= IDX) {
        std::cout << "WRONG INPUT " << std::endl;
        return NULL;
    }
    Vector_Listnp crnt = Head;
    while (crnt) {
        if (crnt->index == IDX) return crnt;
        if (crnt->index > IDX) return NULL;
        crnt = crnt->next;
    }
    return NULL;
}