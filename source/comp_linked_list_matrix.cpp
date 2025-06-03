#include "comp_linked_list_matrix.hpp"

ListMatrix::ListMatrix(int inSize, double** matrix) : size(inSize), Head(nullptr) {
    Head = new Matrix_Node;
    Matrix_Listnp Crnt = NULL;
    bool headmade = false;
    size = inSize;
    Head->val = 0;
    Head->next = NULL;
    Head->row = 0;
    Head->clmn = 0;
    for (int i = 0; i < inSize; i++) {
        for (int j = 0; j < inSize; j++) {
            if (matrix[i][j]) {
                if (!headmade) {
                    Head->val = matrix[i][j];
                    Head->row = i;
                    Head->clmn = j;
                    Head->next = Crnt;
                    headmade = true;
                    Crnt = Head;
                } else {
                    Matrix_Listnp p = new Matrix_Node;
                    p->val = matrix[i][j];
                    p->row = i;
                    p->clmn = j;
                    p->next = NULL;
                    Crnt->next = p;
                    Crnt = p;
                }
            }
        }
    }
}

void ListMatrix::print() {
    Matrix_Listnp crnt = Head;
    bool fin = false;
    for (int i = 0; i < size; i++) {
        std::cout << std::endl;
        for (int j = 0; j < size; j++) {
            if (i == crnt->row && j == crnt->clmn && !fin) {
                std::cout << crnt->val << " ";
                if (crnt->next == NULL) fin = true;
                else crnt = crnt->next;
            } else std::cout << "0 ";
        }
    }
    crnt = NULL;
    delete crnt;
}

Matrix_Listnp ListMatrix::Valsearch(double check) {
    if (!check) {
        std::cout << "Does not work for 0" << std::endl;
        return NULL;
    }
    Matrix_Listnp crnt = Head;
    while (crnt) {
        if (crnt->val == check) return crnt;
        else crnt = crnt->next;
    }
    return NULL;
}

Matrix_Listnp ListMatrix::INDsearch(int ROW, int CLMN) {
    if (ROW >= size || CLMN >= size) {
        std::cout << "WRONG INPUT" << std::endl;
        return NULL;
    }
    Matrix_Listnp crnt = Head;
    while (crnt) {
        if (crnt->row == ROW && crnt->clmn == CLMN) return crnt;
        if (crnt->row >= ROW && crnt->clmn >= CLMN) {
            crnt = new Matrix_Node;
            crnt->val = 0;
            crnt->row = ROW;
            crnt->clmn = CLMN;
            return crnt;
        } else crnt = crnt->next;
    }
    crnt = new Matrix_Node;
    crnt->val = 0;
    crnt->row = ROW;
    crnt->clmn = CLMN;
    return crnt;
}

ListMatrix ListMatrix::Summ(ListMatrix A, ListMatrix B) {//REMASTERED
    if (!A.Head->val) return B;
    if (!B.Head->val) return A;
    Matrix_Listnp REScrnt = new Matrix_Node;

    double** array_for_creation = new double*[A.size];//CRUTCH!
    for(int i=0;i<A.size;i++){
        array_for_creation[i] = new double[A.size];
        for(int j=0;j<A.size;j++)array_for_creation[i][j]=0;
    }

    ListMatrix RESULT(A.size,array_for_creation);
    delete array_for_creation;

    Matrix_Listnp Acrnt = A.Head;
    Matrix_Listnp Bcrnt = B.Head;
    RESULT.Head = new Matrix_Node;
    Matrix_Listnp Non_Deplete = new Matrix_Node;

    auto create_node_no_sum = [](Matrix_Listnp A) -> Matrix_Listnp {
        Matrix_Listnp aux = new Matrix_Node;
        aux->val = A->val;
        aux->row = A->row;
        aux->clmn = A->clmn;
        aux->next = NULL;
        return aux;
    };

        auto create_node_sum = [](Matrix_Listnp A, Matrix_Listnp B) -> Matrix_Listnp {
        Matrix_Listnp aux = new Matrix_Node;
        aux->val = A->val+B->val;
        aux->row = A->row;
        aux->clmn = A->clmn;
        aux->next = NULL;
        return aux;
    };
    
    //creating Head
    if(Acrnt->row != Bcrnt->row){//diffirent rows(selecting with smaller row)
    if(Acrnt->row < Bcrnt->row){//A sooner
    RESULT.Head = create_node_no_sum(Acrnt);
    Acrnt = Acrnt->next;
    }
    else{//B sooner
    RESULT.Head = create_node_no_sum(Bcrnt);
    Bcrnt = Bcrnt->next;
    }
    }
        
    else{//equal rows(looking into columns)
    if(Acrnt->clmn < Bcrnt->clmn){//A sooner
    RESULT.Head = create_node_no_sum(Acrnt);
    Acrnt = Acrnt->next;
    }
    else{//B sooner or equal
        if(Acrnt->clmn > Bcrnt->clmn){//B sooner
        RESULT.Head = create_node_no_sum(Bcrnt);
        Bcrnt = Bcrnt->next;
        }
        else{//equal rows and columns, summing on head
        RESULT.Head = create_node_sum(Bcrnt, Acrnt);
        Bcrnt = Bcrnt->next;
        Acrnt = Acrnt->next;
        }
    }
    }
    REScrnt = RESULT.Head;
    ///
        
    while(Acrnt&&Bcrnt){//Summing while both non-depleted
        if(Acrnt->row == Bcrnt->row){
        if(Acrnt->clmn<Bcrnt->clmn){
            REScrnt->next = create_node_no_sum(Acrnt);
            REScrnt = REScrnt->next;
            Acrnt = Acrnt->next;
        }
        else{
            if(Acrnt->clmn>Bcrnt->clmn){
            REScrnt->next = create_node_no_sum(Bcrnt);
            REScrnt = REScrnt->next;
            Bcrnt = Bcrnt->next;
            }
        else{
            REScrnt->next = create_node_sum(Acrnt, Bcrnt);
            REScrnt = REScrnt->next;
            Bcrnt = Bcrnt->next;
            Acrnt = Acrnt->next;
        }
        }
        }
        else{
        if(Acrnt->row < Bcrnt->row){
            REScrnt->next = create_node_no_sum(Acrnt);
            REScrnt = REScrnt->next;
            Acrnt = Acrnt->next;
            }
        else {
            REScrnt->next = create_node_no_sum(Bcrnt);
            REScrnt = REScrnt->next;
            Bcrnt = Bcrnt->next;
            }
        }
    }
    ///

    if(Acrnt)Non_Deplete=Acrnt;//selecting non-empty
    else Non_Deplete = Bcrnt;

    while (Non_Deplete){//summing when one or both are empty(doesn't enter when both)
        REScrnt->next = create_node_no_sum(Non_Deplete);
        REScrnt = REScrnt->next;
        Non_Deplete = Non_Deplete->next;
    }
    ///
    return RESULT;
}

void ListMatrix::xScalar(ListMatrix A, int x) {
    Matrix_Listnp crnt = A.Head;
    while (crnt) {
        crnt->val *= x;
        crnt = crnt->next;
    }
}