#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

struct thueBao {
    int soDT;
    string tenTB;
    double tienCuoc;
};

struct Node {
    thueBao data;
    Node *next;
    Node *prev; 
};

struct doubleList {
    Node *head;
    Node *tail; 
};

void initialize(doubleList &list) {
    list.head = NULL;
    list.tail = NULL;
}

Node *createNode(thueBao d) {
    Node *pNode = new Node;
    pNode->data = d;
    pNode->next = NULL;
    pNode->prev = NULL;
    return pNode;
}

void insertFirst(doubleList &list, thueBao d) {
    Node *pNode = createNode(d);
    if (list.head == NULL) {
        list.head = pNode;
        list.tail = pNode;
    } else {
        pNode->next = list.head;
        list.head->prev = pNode;
        list.head = pNode;
    }
}

void insertLast(doubleList &list, thueBao d) {
    Node *pNode = createNode(d);
    if (list.head == NULL) {
        list.head = pNode;
        list.tail = pNode;
    } else {
        pNode->prev = list.tail;
        list.tail->next = pNode;
        list.tail = pNode;
    }
}

void deleteFirst(doubleList &list) {
    if (list.head == NULL) {
        cout << "Danh sach rong!\n";
        return;
    }
    Node *temp = list.head;
    if (list.head == list.tail) {
        list.head = NULL;
        list.tail = NULL;
    } else {
        list.head = list.head->next;
        list.head->prev = NULL;
    }
    delete temp;
    cout << "Da xoa phan tu dau tien.\n";
}

void deleteLast(doubleList &list) {
    if (list.head == NULL) {
        cout << "Danh sach rong!\n";
        return;
    }
    Node *temp = list.tail;
    if (list.head == list.tail) {
        list.head = NULL;
        list.tail = NULL;
    } else {
        list.tail = list.tail->prev;
        list.tail->next = NULL;
    }
    delete temp;
    cout << "Da xoa phan tu cuoi cung.\n";
}

void deletePhoneBySoDT(doubleList &list, int id) {
    if (list.head == NULL) {
        cout << "Danh sach rong!\n";
        return;
    }
    Node *current = list.head;
    while (current != NULL) {
        if (current->data.soDT == id) {
            if (current == list.head) {
                deleteFirst(list);
            } else if (current == list.tail) {
                deleteLast(list);
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
                cout << "Da xoa so dien thoai " << id << "\n";
            }
            return;
        }
        current = current->next;
    }
    cout << "Khong tim thay dien thoai voi ma " << id << "\n";
}

void deletePhoneByName(doubleList &list, string name) {
    if (list.head == NULL) {
        cout << "Danh sach rong!\n";
        return;
    }
    Node *current = list.head;
    while (current != NULL) {
        if (current->data.tenTB == name) {
            if (current == list.head) {
                deleteFirst(list);
            } else if (current == list.tail) {
                deleteLast(list);
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
                cout << "Da xoa dien thoai co ten la " << name << "\n";
            }
            return;
        }
        current = current->next;
    }
    cout << "Khong tim thay dien thoai voi ten " << name << "\n";
}

void insertMiddle(doubleList &list, thueBao d, int position) {
    if (position <= 0) {
        cout << "Vi tri chen khong hop le!\n";
        return;
    }
    if (position == 1) {
        insertFirst(list, d);
        return;
    }
    Node *pNode = createNode(d);
    Node *p = list.head;
    for (int i = 1; i < position - 1 && p != NULL; i++) {
        p = p->next;
    }
    if (p == NULL) {
        cout << "Vi tri chen vuot qua so luong dien thoai hien co!\n";
        return;
    }
    pNode->next = p->next;
    if (p->next != NULL) {
        p->next->prev = pNode;
    }
    pNode->prev = p;
    p->next = pNode;
    if (pNode->next == NULL) {
        list.tail = pNode;
    }
    cout << "Da chen dien thoai vao vi tri " << position << " trong danh sach.\n";
}

void timSoDT(doubleList list, int soCT) {
    Node *p = list.head;
    bool found = false;
    while (p != NULL) {
        if (p->data.soDT == soCT) {
            cout << "Thong tin dien thoai co so DT " << soCT << ":\n";
            cout << "Ten: " << p->data.tenTB << endl;
            cout << "Tien cuoc(USD): " << p->data.tienCuoc << endl;
            found = true;
            break;
        }
        p = p->next;
    }
    if (!found) {
        cout << "Khong tim thay dien thoai voi so DT " << soCT << endl;
    }
}

void SXtheoGia(doubleList &list) {
    if (list.head == NULL || list.head->next == NULL) {
        return; 
    }
    bool swapped;
    Node *ptr;
    Node *last = NULL;
    do {
        swapped = false;
        ptr = list.head;

        while (ptr->next != last) {
            if (ptr->data.tienCuoc > ptr->next->data.tienCuoc) {
                thueBao temp = ptr->data;
                ptr->data = ptr->next->data;
                ptr->next->data = temp;
                swapped = true;
            }
            ptr = ptr->next;
        }
        last = ptr;
    } while (swapped);
}

thueBao addthueBao() {
    thueBao b;
    cout << "Nhap so DT: ";
    cin >> b.soDT;
    cin.ignore();
    cout << "Nhap ten thue bao: ";
    getline(cin, b.tenTB);
    cout << "Nhap tien cuoc(USD): ";
    cin >> b.tienCuoc;
    return b;
}

double calculateAverageFee(doubleList list) {
    double totalFee = 0;
    int count = 0;
    Node *p = list.head;
    while (p != NULL) {
        totalFee += p->data.tienCuoc;
        count++;
        p = p->next;
    }
    if (count == 0) {
        return 0; 
    }
    return totalFee / count;
}

void xoaduoi100USD(doubleList &list, double value) {
    Node *current = list.head;
    while (current != NULL) {
        if (current->data.tienCuoc < value) {
            Node *toDelete = current;
            if (current == list.head) {
                list.head = current->next;
                if (list.head != NULL) {
                    list.head->prev = NULL;
                } else {
                    list.tail = NULL;
                }
            } else if (current == list.tail) {
                list.tail = current->prev;
                list.tail->next = NULL;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            current = current->next;
            delete toDelete;
        } else {
            current = current->next;
        }
    }
    cout << "Da xoa cac thue bao co tien cuoc nho hon " << value << endl;
}

void printListToFile(doubleList list, const char* filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        Node *p = list.head;
        while (p != NULL) {
            outFile << p->data.soDT << " "
                    << p->data.tenTB << " "
                    << p->data.tienCuoc << endl;
            p = p->next;
        }
        cout << "Danh sach da duoc ghi vao tep " << filename << endl;
        outFile.close();
    } else {
        cout << "Khong the mo tep " << filename << " de ghi\n";
    }
}

void readListFromFile(doubleList &list, const char* filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        thueBao b;
        while (inFile >> b.soDT >> b.tenTB >> b.tienCuoc) {
            insertLast(list, b);
        }
        cout << "Danh sach da duoc doc tu tep " << filename << endl;
        inFile.close();
    } else {
        cout << "Khong the mo tep " << filename << " de doc\n";
    }
}

void PrintList(doubleList list) {
    Node *p = list.head;
    if (p == NULL)
        cout << "Danh sach rong!\n";
    else {
        cout << "|   soDT   |     TenTB          | Tien cuoc(USD)|\n";
        while (p != NULL) {
            cout << "|" << setw(10) << p->data.soDT
                 << "|" << setw(20) << p->data.tenTB
                 << "|" << setw(15) << p->data.tienCuoc << "|\n";
            p = p->next;
        }
    }
}

void deleteAll(doubleList &list) {
    while (list.head != NULL) {
        deleteFirst(list);
    }
    cout << "Danh sach da duoc xoa toan bo.\n";
}

void insertDescending(doubleList &list, thueBao d) {
    Node *newNode = createNode(d);
    if (list.head == NULL) {
        list.head = newNode;
        list.tail = newNode;
    } else {
        Node *current = list.head;
        while (current != NULL && current->data.tienCuoc >= newNode->data.tienCuoc) {
            current = current->next;
        }
        if (current == list.head) {
            insertFirst(list, d);
        } else if (current == NULL) {
            insertLast(list, d);
        } else {
            newNode->next = current;
            newNode->prev = current->prev;
            current->prev->next = newNode;
            current->prev = newNode;
        }
    }
    cout << "Da them thue bao theo thu tu tien cuoc giam dan.\n";
}

void PrintListReverse(doubleList list) {
    Node *p = list.tail;
    if (p == NULL)
        cout << "Danh sach rong!\n";
    else {
        cout << "|   soDT   |     TenTB          | Tien cuoc(USD)|\n";
        while (p != NULL) {
            cout << "|" << setw(10) << p->data.soDT
                 << "|" << setw(20) << p->data.tenTB
                 << "|" << setw(15) << p->data.tienCuoc << "|\n";
            p = p->prev;
        }
    }
}

int countSubscribers(doubleList list) {
    int count = 0;
    Node *p = list.head;
    while (p != NULL) {
        count++;
        p = p->next;
    }
    return count;
}

void timTenTB(doubleList list, string tenTB) {
    Node *p = list.head;
    bool found = false;
    while (p != NULL) {
        if (p->data.tenTB == tenTB) {
            cout << "Thong tin thue bao co ten " << tenTB << ":\n";
            cout << "So DT: " << p->data.soDT << endl;
            cout << "Tien cuoc(USD): " << p->data.tienCuoc << endl;
            found = true;
        }
        p = p->next;
    }
    if (!found) {
        cout << "Khong tim thay thue bao voi ten " << tenTB << endl;
    }
}

void findSubscribersByFee(doubleList list, double value) {
    Node *p = list.head;
    bool found = false;
    cout << "Cac thue bao co tien cuoc lon hon " << value << " USD:\n";
    while (p != NULL) {
        if (p->data.tienCuoc > value) {
            cout << "So DT: " << p->data.soDT << endl;
            cout << "Ten: " << p->data.tenTB << endl;
            cout << "Tien cuoc(USD): " << p->data.tienCuoc << endl << endl;
            found = true;
        }
        p = p->next;
    }
    if (!found) {
        cout << "Khong tim thay thue bao nao co tien cuoc lon hon " << value << " USD.\n";
    }
}

void findSubscribersByRange(doubleList list, int start, int end) {
    Node *p = list.head;
    bool found = false;
    cout << "Cac thue bao co so DT trong doan [" << start << ", " << end << "]:\n";
    while (p != NULL) {
        if (p->data.soDT >= start && p->data.soDT <= end) {
            cout << "So DT: " << p->data.soDT << endl;
            cout << "Ten: " << p->data.tenTB << endl;
            cout << "Tien cuoc(USD): " << p->data.tienCuoc << endl << endl;
            found = true;
        }
        p = p->next;
    }
    if (!found) {
        cout << "Khong tim thay thue bao nao co so DT trong doan [" << start << ", " << end << "].\n";
    }
}

void findSubscribersByNameStartsWith(doubleList list, string prefix) {
    Node *p = list.head;
    bool found = false;
    cout << "Cac thue bao co ten bat dau bang \"" << prefix << "\":\n";
    while (p != NULL) {
        if (p->data.tenTB.find(prefix) == 0) {
            cout << "So DT: " << p->data.soDT << endl;
            cout << "Ten: " << p->data.tenTB << endl;
            cout << "Tien cuoc(USD): " << p->data.tienCuoc << endl << endl;
            found = true;
        }
        p = p->next;
    }
    if (!found) {
        cout << "Khong tim thay thue bao nao co ten bat dau bang \"" << prefix << "\".\n";
    }
}

void deleteSubscribersByNameStartsWith(doubleList &list, string prefix) {
    Node *current = list.head;
    bool found = false;
    while (current != NULL) {
        if (current->data.tenTB.find(prefix) == 0) {
            Node *toDelete = current;
            if (current == list.head) {
                list.head = current->next;
                if (list.head != NULL) {
                    list.head->prev = NULL;
                } else {
                    list.tail = NULL;
                }
            } else if (current == list.tail) {
                list.tail = current->prev;
                list.tail->next = NULL;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            current = current->next;
            delete toDelete;
            found = true;
        } else {
            current = current->next;
        }
    }
    if (found) {
        cout << "Da xoa cac thue bao co ten bat dau bang \"" << prefix << "\"\n";
    } else {
        cout << "Khong tim thay thue bao nao co ten bat dau bang \"" << prefix << "\"\n";
    }
}


int main() {
    doubleList L;
    initialize(L);
    int choice;
    do {
        cout << "\n========= MENU =========\n";
        cout << "1. Nhap danh sach \n";
        cout << "2. Them thue bao vao dau danh sach\n";
        cout << "3. Them thue bao vao cuoi danh sach\n";
        cout << "4. Chen thue bao vao vi tri bat ky\n";
        cout << "5. Thay doi du lieu dau danh sach\n";
        cout << "6. Thay doi du lieu cuoi danh sach\n";
        cout << "7. Xoa thue bao dau danh sach\n";
        cout << "8. Xoa thue bao cuoi danh sach\n";
        cout << "9. Xoa thue bao theo so dien thoai\n";
        cout << "10. Xoa thue bao theo ten\n";
        cout << "11. Tim thue bao theo so dien thoai\n";
        cout << "12. Sap xep thue bao theo tien cuoc tang dan\n";
        cout << "13. Tinh trung binh tien cuoc\n";
        cout << "14. Xoa cac thue bao co tien cuoc nho hon 100USD\n";
        cout << "15. In danh sach ra tep\n";
        cout << "16. Nhap danh sach tu tep\n";
        cout << "17. In danh sach thue bao\n";
        cout << "18. Xoa toan bo danh sach\n";
        cout << "19. Them thue bao va sap xep thu tu tien cuoc giam dan\n";
        cout << "20. In danh sach theo thu tu nguoc lai\n";
        cout << "21. Dem so luong thue bao\n";
        cout << "22. Tim thue bao theo ten\n";
        cout << "23. Tim va in thue bao theo tien cuoc\n";
        cout << "24. Tim va in thue bao theo co SDT tu mot doan cho truoc\n";
        cout << "25. Tim va in thue bao tu mot chuoi so cho truoc\n";
        cout << "26. Xoa thue bao theo ten  tu mot chuoi so cho truoc\n";

        cout << "0. Thoat\n";
        cout << "Nhap lua chon cua ban: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                int n;
                cout << "Nhap so phan tu: ";
                cin >> n;
                for (int i = 0; i < n; i++) {
                    thueBao b = addthueBao();
                    insertLast(L, b);
                }
                break;
            }
            case 2: {
                thueBao b = addthueBao();
                insertFirst(L, b);
                break;
            }
            case 3: {
                thueBao b = addthueBao();
                insertLast(L, b);
                break;
            }
            case 4: {
                thueBao dienThoaiChen = addthueBao();
                int viTriChen;
                cout << "Nhap vi tri can chen: ";
                cin >> viTriChen;
                insertMiddle(L, dienThoaiChen, viTriChen);
                break;
            }
            case 5: {
                deleteFirst(L);
                thueBao b = addthueBao();
                insertFirst(L, b);
                break;
            }
            case 6: {
                deleteLast(L);
                thueBao b = addthueBao();
                insertLast(L, b);
                break;
            }
            case 7: {
                deleteFirst(L);
                break;
            }
            case 8: {
                deleteLast(L);
                break;
            }
            case 9: {
                int id;
                cout << "Nhap so dien thoai can xoa: ";
                cin >> id;
                deletePhoneBySoDT(L, id);
                break;
            }
            case 10: {
                cin.ignore();
                string name;
                cout << "Nhap ten can xoa: ";
                getline(cin, name);
                deletePhoneByName(L, name);
                break;
            }
            case 11: {
                int soCT;
                cout << "Nhap so dien thoai can tim: ";
                cin >> soCT;
                timSoDT(L, soCT);
                break;
            }
            case 12: {
                SXtheoGia(L);
                cout << "Danh sach da duoc sap xep.\n";
                break;
            }
            case 13: {
                double average = calculateAverageFee(L);
                cout << "Tien cuoc trung binh: " << average << " USD\n";
                break;
            }
            case 14: {
                xoaduoi100USD(L, 100);
                break;
            }
            case 15: {
                char filename[100];
                cout << "Nhap ten tep de ghi: ";
                cin >> filename;
                printListToFile(L, "1.txt");
                break;
            }
            case 16: {
                readListFromFile(L,"1.txt");
                break;
            }
            case 17: {
                PrintList(L);
                break;
            }
            case 18: {
                deleteAll(L);
                break;
            }
            case 19: {
                thueBao b = addthueBao();
                insertDescending(L, b);
                break;
            }
			case 20: {
            PrintListReverse(L);
            break;
            } 
            case 21: {
            int count = countSubscribers(L);
            cout << "So luong thue bao: " << count << "\n";
            break;
            }
            case 22: {
            cin.ignore();
            string tenTB;
            cout << "Nhap ten thue bao can tim: ";
            getline(cin, tenTB);
            timTenTB(L, tenTB);
            break;
            }    
			
			case 23: {
    double value;
    cout << "Nhap gia tri tien cuoc can tim: ";
    cin >> value;
    findSubscribersByFee(L, value);
    break;
}
case 24: {
    int start, end;
    cout << "Nhap gioi han duoi: ";
    cin >> start;
    cout << "Nhap gioi han tren: ";
    cin >> end;
    findSubscribersByRange(L, start, end);
    break;
}
case 25: {
    cin.ignore();
    string prefix;
    cout << "Nhap chuoi bat dau ten thue bao: ";
    getline(cin, prefix);
    findSubscribersByNameStartsWith(L, prefix);
    break;
}

case 26: {
    cin.ignore();
    string prefix;
    cout << "Nhap chuoi bat dau ten thue bao can xoa: ";
    getline(cin, prefix);
    deleteSubscribersByNameStartsWith(L, prefix);
    break;
}	         
            case 0:
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);
    return 0;
}


