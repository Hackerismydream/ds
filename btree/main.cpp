#include <iostream>
#include "main.h"
#include "BTree.h"

using namespace std;

int btreeStatus = NOT_INIT; // B��״̬����ʼֵΪδ��ʼ��

/**
 * ��ʼ��һ��B��
 *
 * @param t B��
 */
void InitBTreeOperation(BTree &t) {
    if (btreeStatus == HAVE_BEEN_INIT) {
        printf("����һ��B���Ѿ��������Ƿ����������´�������Y����, ���������Ϊ��");
        char choice = getchar();
        fflush(stdin);
        if (toupper(choice) == 'Y') {
            DestoryBTree(t);
            btreeStatus = NOT_INIT;
        } else {
            return;
        }
    }
    InitBTree(t);
    btreeStatus = HAVE_BEEN_INIT;
}

/**
 * ���������
 *
 * @param t B��
 */
void InsertKeyOperation(BTree &t) {
    Result r;
    KeyType key;
    if (NOT_INIT == btreeStatus) {
        printf("B����δ��ʼ�������ȳ�ʼ����\n");
        return;
    }
    if (NULL == t) {
        printf("����B���ǿյģ�");
    } else {
        printf("B���İ������ʾ���£�\n\n");
        printf("------------------------------------------------------\n");
        PrintBTree(t, 1);
        printf("\n------------------------------------------------------\n");
    }
    while (1) {
        printf("�������������Ĺؼ��֣�");
        while (1 != scanf("%d", &key)) {
            getchar();
            fflush(stdin);
            printf("��������ȷ��ֵ��\n");
            printf("�������������Ĺؼ��֣�");
        }
        SearchBTree(t, key, r);
        if (1 == r.tag) {
            printf("�ùؼ����Ѿ�������B-���С�\n");
        } else if (0 == r.tag) {
            InsertBTree(t, key, r.pt, r.i);
            printf("����ɹ���������B-�����£�\n");
            printf("------------------------------------------------------\n");
            PrintBTree(t, 1);
            printf("\n------------------------------------------------------\n");
        }
        printf("�Ƿ�������룿��Y/y����, ���������Ϊ�񣩣�");
        char c;
        getchar();
        scanf("%c", &c);
        fflush(stdin);
        if (toupper(c) != 'Y') {
            break;
        }
        printf("\n");
    }
}

/**
 * ɾ��������
 *
 * @param t B��
 */
void DeleteKeyOperation(BTree &t) {
    Result r;
    KeyType key;
    if (NOT_INIT == btreeStatus) {
        printf("B����δ��ʼ�������ȳ�ʼ����\n");
        return;
    }
    if (NULL == t) {
        printf("����B���ǿյģ��޷�����ɾ��������\n");
        return;
    } else {
        printf("B���İ������ʾ���£�\n\n");
        printf("------------------------------------------------------\n");
        PrintBTree(t, 1);
        printf("\n------------------------------------------------------\n");
        while (1) {
            printf("����������ɾ���Ĺؼ��֣�");
            while (1 != scanf("%d", &key)) {
                getchar();
                fflush(stdin);
                printf("��������ȷ��ֵ��\n");
                printf("����������ɾ���Ĺؼ��֣�");
            }
            SearchBTree(t, key, r);
            if (1 == r.tag) {
                DeleteBTree(t, r.pt, r.i);
                if (BTreeKeyNumber(t) == 0) {
                    t = NULL;
                    printf("ɾ���ɹ�B���Ĺؼ����Ѿ�ȫ����ɾ���ˣ�\n");
                    break;
                } else {
                    printf("ɾ���ɹ���ɾ�����B-�����£�\n");
                    printf("------------------------------------------------------\n");
                    PrintBTree(t, 1);
                    printf("\n------------------------------------------------------\n");
                }
            } else if (0 == r.tag) {
                printf("�ùؼ��ֲ���B���У��޷�ɾ����\n");
            }
            printf("�Ƿ����ɾ������Y/y����, ���������Ϊ�񣩣�");
            char c;
            getchar();
            scanf("%c", &c);
            fflush(stdin);
            if (toupper(c) != 'Y') {
                break;
            }
            printf("\n");
        }

    }
}

/**
 * ���ҽ�����
 *
 * @param t B��
 */
void SearchOperation(BTree t) {
    KeyType key;
    Result r;
    if (NOT_INIT == btreeStatus) {
        printf("B����δ��ʼ�������ȳ�ʼ����\n");
        return;
    }
    if (NULL == t) {
        printf("����B���ǿյģ��޷����в��Ҳ�����\n");
        return;
    } else {
        printf("B���İ������ʾ���£�\n\n");
        printf("------------------------------------------------------\n");
        PrintBTree(t, 1);
        printf("\n------------------------------------------------------\n");
        printf("��������Ҫ���ҵĹؼ��֣�");
        scanf("%d", &key);
        SearchBTree(t, key, r);
        if (0 == r.tag) {
            printf("û�в鵽�ùؼ��֡�\n");
        } else {
            printf("�Թؼ������ڽ����������£�\n");
            printf("------------------------------------------------------\n");
            PrintBTree(r.pt, 1);
            printf("\n------------------------------------------------------\n");
        }
    }
}

/**
 * �������ָ����С��B��
 *
 * @param t B��
 */
void CreateBTreeRandomOperation(BTree &t) {
    if (btreeStatus == HAVE_BEEN_INIT) {
        printf("����һ��B���Ѿ��������Ƿ����������´�������Y����, ���������Ϊ��");
        char choice = getchar();
        fflush(stdin);
        if (toupper(choice) == 'Y') {
            DestoryBTree(t);
            btreeStatus = NOT_INIT;
        } else {
            return;
        }
    }
    printf("�����������ɵ�B���ؼ���������ֻ֧��1-1000�����룩��");
    int keyNumber;
    while (1) {
        int result = scanf("%d", &keyNumber);
        getchar();
        fflush(stdin);
        if (result == 1) {
            if (keyNumber >= 1 && keyNumber <= 1000) {
                break;
            }
        }
        printf("��������ȷ��ֵ��\n");
        printf("�������������ɵ�B���ؼ���������ֻ֧��1-1000�����룩��");
    }
    CreateBTreeRandom(t, keyNumber);
    printf("\n���ɳɹ���������B���İ������ʾ��\n");
    printf("------------------------------------------------------\n");
    PrintBTree(t, 1);
    printf("\n------------------------------------------------------\n");
    btreeStatus = HAVE_BEEN_INIT;
}

/**
 * ˳�����B������
 *
 * @param t B��
 */
void OrderTraverseBTreeOperation(BTree t) {
    if (NOT_INIT == btreeStatus) {
        printf("B����û��ʼ�������ȳ�ʼ��\n");
    } else if (NULL == t) {
        printf("B��Ϊ��\n");
    } else {
        printf("B���Ĺؼ�������Ϊ%d��˳��������£�\n", BTreeKeyNumber(t));
        OrderTraverseBTree(t);
        printf("\n");
    }
}

/**
 * ������ӡB������
 *
 * @param t B��
 */
void PrintBTreeOperation(BTree t) {
    if (NOT_INIT == btreeStatus) {
            printf("B����û��ʼ�������ȳ�ʼ��\n");
    } else if (NULL == t) {
        printf("B��Ϊ��\n");
    } else {
        printf("B���İ������ʾ���£�\n\n");
        printf("------------------------------------------------------\n");
        PrintBTree(t, 1);
        printf("\n------------------------------------------------------\n");
    }
}

/**
 * ����B������
 *
 * @param t B��
 */
void DestoryBTreeOperation(BTree &t) {
    if (btreeStatus == NOT_INIT) {
        printf("B����û��������������\n");
    } else if (t == NULL) {
        printf("B��Ϊ�գ���������\n");
    } else {
        DestoryBTree(t);
        btreeStatus = NOT_INIT;
        printf("���ٳɹ�\n");
    }
}

/**
 * B-��������ʾѡ��˵�
 */
void BTreeMenu() {
    system("color 0D");
    printf("**************************************************************************\n");
    printf("*                                                                        *\n");
    printf("***************************B-������ѡ��˵�*******************************\n");
    printf("*                                                                        *\n");
    printf("****************�����ˣ�֣������3116005120��16�����׿Խ******************\n");
    printf("*                                                                        *\n");
    printf("*                         1. ����һ�ÿ�B-��                              *\n");
    printf("*                         2. �������һ��B-��                            *\n");
    printf("*                         3. ����ؼ���                                  *\n");
    printf("*                         4. ɾ���ؼ���                                  *\n");
    printf("*                         5. ���ҹؼ���                                  *\n");
    printf("*                         6. �ؼ�������                                  *\n");
    printf("*                         7. �������B-���ؼ���                          *\n");
    printf("*                         8. ������ӡB-��                              *\n");
    printf("*                         9. ����B-��                                    *\n");
    printf("*                         0. �˳�                                        *\n");
    printf("*                                                                        *\n");
    printf("**************************************************************************\n");
}

/**
 * ������
 */
int main()
{
    BTree t;
    int selectNum;
    while (1) {
        BTreeMenu();
        printf("����������ѡ��");
        scanf("%d", &selectNum);
        getchar();
        fflush(stdin);
        if (0 == selectNum) {
            printf("\n�Ƿ��˳�����Y����, ���������Ϊ��");
            char option;
            option = getchar();
            fflush(stdin);
            if (toupper(option) == 'Y') {
                if (btreeStatus == HAVE_BEEN_INIT) {
                    DestoryBTree(t);
                }
                exit(EXIT_SUCCESS);
            }
        } else {
            switch (selectNum) {
                case 1: InitBTreeOperation(t); break;
                case 2: CreateBTreeRandomOperation(t); break;
                case 3: InsertKeyOperation(t); break;
                case 4: DeleteKeyOperation(t); break;
                case 5: SearchOperation(t); break;
                case 6: {
                    if (NOT_INIT == btreeStatus) {
                        printf("B����û��ʼ�������ȳ�ʼ��\n");
                    } else {
                        printf("\n�ؼ�������Ϊ: %d\n\n", BTreeKeyNumber(t));
                    }
                    break;
                }
                case 7: OrderTraverseBTreeOperation(t); break;
                case 8: PrintBTreeOperation(t); break;
                case 9: DestoryBTreeOperation(t); break;
                default: printf("�������ѡ����ȷ�����������룡\n"); break;
            }
        }
        system("PAUSE");
        system("cls"); // ��������
    }
    system("PAUSE");
    getch();
    return 0;
}
