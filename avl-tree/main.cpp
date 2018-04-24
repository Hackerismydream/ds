#include <iostream>
#include "main.h"
#include "AVLTree.h"

using namespace std;

int flag = NOT_CREATED; // ȫ�ֱ����������ж�ƽ��������Ƿ��Ѿ�����

/**
 * ƽ���������ʾ���ܲ˵�
 */
void AVLMenu() {
    system("color 0D");
    printf("**************************************************************************\n");
    printf("*                                                                        *\n");
    printf("************************ƽ���������ʾ����ѡ��˵�************************\n");
    printf("*                                                                        *\n");
    printf("****************�����ˣ�֣������3116005120��16�����׿Խ******************\n");
    printf("*                                                                        *\n");
    printf("*                         1. ����һ��ƽ�������                          *\n");
    printf("*                         2. ������                                    *\n");
    printf("*                         3. ɾ�����                                    *\n");
    printf("*                         4. ���ҽ��                                    *\n");
    printf("*                         5. �������ƽ�������                          *\n");
    printf("*                         6. ��ʾƽ�������                              *\n");
    printf("*                         7. ����һ��ƽ�������                          *\n");
    printf("*                         8. �ϲ�����ƽ�������                          *\n");
    printf("*                         9. ����ƽ�������                              *\n");
    printf("*                         0. �˳�                                        *\n");
    printf("*                                                                        *\n");
    printf("**************************************************************************\n");
}

/**
 * ����ƽ�����������
 *
 * @param T ƽ�������
 */
void InitBBSTreeOperation(BBSTree &T) {
    if (flag == HAVE_BEEN_CREATED) {
        // ����Ѿ���һ��ƽ�������������
        printf("��֮ǰ�Ѿ�������һ��ƽ����������Ƿ�����֮ǰ���������´�������Y/y����, ���������Ϊ��");
        char choice = getchar();
        fflush(stdin);
        if (toupper(choice) == 'Y') {
            DestroyBBST(T);
            printf("ƽ��������Ѿ������٣����ڿ��Դ���һ���µ�ƽ���������");
        } else {
            return;
        }
    }
    printf("\n1. ����һ�ÿ�ƽ���������2. ����һ�÷ǿ�ƽ���������");
    int createOption;
    while (1) {
        scanf("%d", &createOption);
        getchar();
        fflush(stdin);
        if (createOption == 1) {
            T = NULL;
            printf("��ƽ������������ɹ�.\n");
            flag = HAVE_BEEN_CREATED;
            break;
        } else if (createOption == 2) {
            T = NULL;
            int AVLSize = 0; // AVL����С���������
            printf("\n������Ҫ������ƽ��������Ľ������ֻ֧��1-100�����룩: ");
            while (1) {
                int result = scanf("%d", &AVLSize);
                getchar();
                fflush(stdin);
                if (result == 1) {
                    if (AVLSize >= 1 && AVLSize <= 100) {
                        break;
                    }
                }
                printf("��������ȷ��ֵ��\n");
                printf("\n������Ҫ������ƽ��������Ľ������ֻ֧��1-100�����룩: ");
            }
            srand((unsigned int) time(NULL));
            int i;
            KeyType key;
            RcdType rcd;
            Status taller = FALSE;
            for (i = 1; i <= AVLSize; i++) {
                key = rand() % 1000;
                rcd.key = key;
                InsertAVL(T, rcd, taller);
            }
            flag = HAVE_BEEN_CREATED;
            printf("----------------------------------------------------\n");
            printf("������������ƽ�������������ʾ��\n");
            printf("������ʾ����\n\n");
            ConcaveTablePrintBBST(T, 1);
            printf("\n\n");
            printf("���ű�ʾ����");
            ParenthesisPrintBBST(T);
            printf("\n----------------------------------------------------\n");
            break;
        } else {
            printf("��������ȷ��ֵ\n");
            printf("\n1. ����һ�ÿ�ƽ���������2. ���������һ�÷ǿ�ƽ���������");
        }
    }
}

/**
 * ���������
 *
 * @param T ƽ�������
 */
void InsertAVLOperation(BBSTree &T) {
    if (flag == NOT_CREATED) {
        // ƽ���������δ����
        printf("����δ����ƽ����������޷������㣬���ȴ�����");
        return;
    } else if (flag == HAVE_BEEN_CREATED) {
        if (NULL == T) {
            printf("����ƽ��������ǿյģ���Ϊ��������ɣ�\n");
        } else {
            printf("\n----------------------------------------------------");
            printf("\n����ƽ�������Ϊ��");
            ParenthesisPrintBBST(T);
            printf("\n�������ʾ���£�\n\n");
            ConcaveTablePrintBBST(T, 1);
            printf("\n----------------------------------------------------\n\n");
        }
        while (1) {
            printf("������Ҫ������Ĺؼ���: ");
            KeyType key;
            RcdType rcd;
            while (1 != scanf("%d", &key)) {
                getchar();
                fflush(stdin);
                fprintf(stderr, "��������ȷ��ֵ��\n");
                printf("������Ҫ������Ĺؼ���: ");
            }
            rcd.key = key;
            Status taller = FALSE;
            if (SearchBBST(T, key) != NULL) {
                printf("����ʧ���ˣ���Ϊ������Ĺؼ����Ѿ������ˣ��´���������ȷ��ֵ��\n\n");
            } else {
                InsertAVL(T, rcd, taller);
                printf("\n----------------------------------------------------");
                printf("\n������ƽ�������Ϊ��");
                ParenthesisPrintBBST(T);
                printf("\n�������ʾ���£�\n\n");
                ConcaveTablePrintBBST(T, 1);
                printf("\n----------------------------------------------------\n\n");
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
}

/**
 * ɾ��������
 *
 * @param T ƽ�������
 */
void DeleteAVLOperation(BBSTree &T) {
    if (flag == NOT_CREATED) {
        // ƽ���������δ����
        printf("����δ����ƽ����������޷�ɾ����㣬���ȴ�����");
    } else if (flag == HAVE_BEEN_CREATED) {
        if (NULL == T) {
            printf("����ƽ��������ǿյģ��޷�ɾ����㣬���Ȳ����㣡\n");
        } else {
            printf("\n----------------------------------------------------");
            printf("\n����ƽ�������Ϊ��");
            ParenthesisPrintBBST(T);
            printf("\n�������ʾ���£�\n\n");
            ConcaveTablePrintBBST(T, 1);
            printf("\n----------------------------------------------------");
            printf("\n\n");
            while (1) {
                printf("������Ҫɾ�����Ĺؼ���: ");
                KeyType key;
                while (1 != scanf("%d", &key)) {
                    getchar();
                    fflush(stdin);
                    fprintf(stderr, "��������ȷ��ֵ��\n");
                    printf("������Ҫɾ�����Ĺؼ���: ");
                }
                if (NULL == SearchBBST(T, key)) {
                    // �ؼ��ֲ���ƽ�����������
                    printf("������Ĺؼ��ֲ���ƽ��������С�\n\n");
                } else {
                    Status shorter = FALSE;
                    DeleteAVL(T, key, shorter);
                    if (NULL == T) {
                        printf("ƽ��������Ѿ�����ɾ���ɾ��ˣ����ü���ɾ����\n");
                        break;
                    } else {
                        printf("\n----------------------------------------------------");
                        printf("\nɾ�����ƽ�������Ϊ��");
                        ParenthesisPrintBBST(T);
                        printf("\n�������ʾ���£�\n\n");
                        ConcaveTablePrintBBST(T, 1);
                        printf("\n----------------------------------------------------\n\n");
                    }
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
}

/**
 * ���ҽ�����
 *
 * @param T ƽ�������
 */
void SearchBBSTOperation(BBSTree &T) {
    KeyType key;
    BBSTree p;
    if (NOT_CREATED == flag) {
        printf("����δ����ƽ����������޷����в��ң����ȴ�����\n");
        return;
    }
    if (NULL == T) {
        printf("����ƽ��������ǿյģ�\n");
        return;
    } else {
        printf("\n----------------------------------------------------");
        printf("\n����ƽ�������Ϊ��");
        ParenthesisPrintBBST(T);
        printf("\n�������ʾ���£�\n\n");
        ConcaveTablePrintBBST(T, 1);
        printf("\n----------------------------------------------------\n\n");
        printf("��������Ҫ���ҵĹؼ��֣�");
        while (scanf("%d", &key) != 1) {
            printf("��������ȷ��ֵ!\n");
            printf("��������Ҫ���ҵĹؼ��֣�");
        }
        p = SearchBBST(T, key);
        if (NULL == p) {
            printf("û���ҵ��ùؼ��֡�\n");
        } else {
            printf("�Թؼ������ڽ����������£�\n");
            printf("------------------------------------------------------\n");
            ParenthesisPrintBBST(p);
            printf("\n\n�������ʾ���£�\n\n");
            ConcaveTablePrintBBST(p, 1);
            printf("\n----------------------------------------------------\n\n");
        }
    }
}

/**
 * ����ƽ�����������
 *
 * @param T ƽ�������
 */
void VisitOperation(BBSTree T) {
    if (flag == NOT_CREATED) {
        // ƽ���������δ����
        printf("����δ����ƽ����������޷�������������ȴ�����\n");
    } else if (flag == HAVE_BEEN_CREATED) {
        if (NULL == T) {
            printf("����ƽ��������ǿյ����Ȳ����㣡\n");
        } else {
            printf("\n----------------------------------------------------");
            printf("\n����ƽ�������Ϊ��");
            ParenthesisPrintBBST(T);
            printf("\n�������ʾ���£�\n\n");
            ConcaveTablePrintBBST(T, 1);
            printf("\n\nǰ��������Ϊ��");
            PreOrderTraverse(T, visit);
            printf("\n����������Ϊ��");
            InOrderTraverse(T, visit);
            printf("\n����������Ϊ��");
            PostOrderTraverse(T, visit);
            printf("\n��α������Ϊ��");
            PrintNodeByLevel(T);
            printf("\n----------------------------------------------------\n\n");
        }
    }
}

/**
 * ��ӡƽ�����������
 *
 * @param T ƽ�������
 */
void PrintBBSTOperation(BBSTree T) {
    if (flag == NOT_CREATED) {
        // ƽ���������δ����
        printf("����δ����ƽ����������޷���ʾ�����ȴ�����\n");
    } else if (flag == HAVE_BEEN_CREATED) {
        if (NULL == T) {
            printf("����ƽ��������ǿյ����Ȳ����㣡\n");
        } else {
            printf("\n----------------------------------------------------");
            printf("\n����ƽ�������Ϊ��");
            ParenthesisPrintBBST(T);
            printf("\n�������ʾ���£�\n\n");
            ConcaveTablePrintBBST(T, 1);
            printf("\n----------------------------------------------------\n\n");
        }
    }
}

/**
 * ����ƽ�����������
 *
 * @param T ƽ�������
 */
void SpiltBBSTOperation(BBSTree T) {
    if (flag == NOT_CREATED) {
        // ƽ���������δ����
        printf("����δ����ƽ����������޷����ѣ����ȴ�����\n");
    } else if (flag == HAVE_BEEN_CREATED) {
        if (NULL == T) {
            printf("����ƽ��������ǿյ����Ȳ����㣡\n");
        } else {
            printf("\n----------------------------------------------------");
            printf("\n����ƽ�������Ϊ��");
            ParenthesisPrintBBST(T);
            printf("\n�������ʾ���£�\n\n");
            ConcaveTablePrintBBST(T, 1);
            printf("\n----------------------------------------------------\n\n");
            printf("������Ҫ���ѵĹؼ���: ");
            KeyType key;
            while (1) {
                while (1 != scanf("%d", &key)) {
                    getchar();
                    fflush(stdin);
                    fprintf(stderr, "��������ȷ��ֵ��\n");
                    printf("������Ҫ���ѵĹؼ���: ");

                }
                if (NULL == SearchBBST(T, key)) {
                    // �ؼ��ֲ���ƽ�����������
                    printf("������Ĺؼ��ֲ���ƽ��������С�\n\n");
                    printf("����������Ҫ���ѵĹؼ���: ");
                } else {
                    BBSTree T1 = NULL;
                    BBSTree T2 = NULL;
                    SpiltBBST(T, key, T1, T2);
                    printf("\n----------------------------------------------------\n");
                    printf("1. �ؼ��ֱ�%d�������Ϊ��", key);
                    ParenthesisPrintBBST(T1);
                    printf("\n�������ʾ���£�\n\n");
                    ConcaveTablePrintBBST(T1, 1);
                    printf("\n----------------------------------------------------\n\n");

                    printf("\n----------------------------------------------------\n");
                    printf("2. �ؼ���С�ڵ���%d������Ϊ��", key);
                    ParenthesisPrintBBST(T2);
                    printf("\n�������ʾ���£�\n\n");
                    ConcaveTablePrintBBST(T2, 1);
                    printf("\n----------------------------------------------------\n\n");
                    break;
                }
            }
        }
    }
}

/**
 * �ϲ�ƽ�����������
 *
 * @param T ƽ�������
 */
void MergeBBSTOperation(BBSTree &T) {
    if (flag == NOT_CREATED) {
        // ƽ���������δ����
        printf("����δ����ƽ������������ȴ�����\n");
    } else if (flag == HAVE_BEEN_CREATED) {
        if (NULL == T) {
            printf("����ƽ��������ǿյģ���������Դ���һ��ƽ��������ϲ����˶�������\n");
        } else {
            printf("\n----------------------------------------------------");
            printf("\n��������ƽ�������Ϊ��");
            ParenthesisPrintBBST(T);
            printf("\n�������ʾ���£�\n\n");
            ConcaveTablePrintBBST(T, 1);
            printf("\n----------------------------------------------------");
            printf("\n��������Դ���һ��ƽ��������ϲ����˶�������\n\n");
        }
        BBSTree T1 = NULL;
        int AVLSize = 0; // AVL����С���������
        printf("\n������Ҫ������ƽ��������Ľ������ֻ֧��1-100�����룩: ");
        while (1) {
            int result = scanf("%d", &AVLSize);
            getchar();
            fflush(stdin);
            if (result == 1) {
                if (AVLSize >= 1 && AVLSize <= 100) {
                    break;
                }
            }
            printf("��������ȷ��ֵ��\n");
            printf("\n������Ҫ������ƽ��������Ľ������ֻ֧��1-100�����룩: ");
        }
        srand((unsigned int) time(NULL));
        int i;
        KeyType key;
        RcdType rcd;
        Status taller = FALSE;
        for (i = 1; i <= AVLSize; i++) {
            key = rand() % 1000;
            rcd.key = key;
            InsertAVL(T1, rcd, taller);
        }
        printf("\n----------------------------------------------------");
        printf("\n�´�����ƽ�������Ϊ��");
        ParenthesisPrintBBST(T1);
        printf("\n�������ʾ���£�\n\n");
        ConcaveTablePrintBBST(T1, 1);
        printf("\n----------------------------------------------------\n\n");
        MergeBBST(T, T1);
        DestroyBBST(T1);
        printf("\n----------------------------------------------------");
        printf("\n�ϲ����ƽ�������Ϊ��");
        ParenthesisPrintBBST(T);
        printf("\n�������ʾ���£�\n\n");
        ConcaveTablePrintBBST(T, 1);
        printf("\n----------------------------------------------------\n\n");
    }
}

/**
 * ����ƽ�����������
 *
 * @param T ƽ�������
 */
void DestroyBBSTOperation(BBSTree &T) {
    if (flag == NOT_CREATED) {
        // ƽ���������δ����
        printf("����δ����ƽ����������������١�\n");
    } else if (flag == HAVE_BEEN_CREATED) {
        if (NULL == T) {
            printf("����ƽ��������ǿյģ���������\n");
        } else {
            printf("\n�Ƿ����٣���Y/y����, ���������Ϊ��");
            char option;
            option = getchar();
            fflush(stdin);
            if (toupper(option) == 'Y') {
                DestroyBBST(T);
                flag = NOT_CREATED;
            }
        }
    }
}

/**
 * ����������
 */
int main()
{
    system("color 0F");
    int selectNum; // �˵�ѡ��
    BBSTree T;
    while (1) {
        AVLMenu();
        printf("������������еĲ�����");
        scanf("%d", &selectNum);
        getchar();
        fflush(stdin);
        if (0 == selectNum) {
            printf("\n�Ƿ��˳�����Y/y����, ���������Ϊ��");
            char option;
            option = getchar();
            fflush(stdin);
            if (toupper(option) == 'Y') {
                if (flag == HAVE_BEEN_CREATED) {
                    DestroyBBST(T);
                }
                // ѡ���˳�����Сд�Կ�
                exit(EXIT_SUCCESS);
            }
        } else {
            switch (selectNum) {
                case 1: InitBBSTreeOperation(T); break; // ��ʼ������ƽ�������
                case 2: InsertAVLOperation(T); break; // ����
                case 3: DeleteAVLOperation(T); break; // ɾ��
                case 4: SearchBBSTOperation(T); break; // ����
                case 5: VisitOperation(T); break; // ����
                case 6: PrintBBSTOperation(T); break; // ��ӡ
                case 7: SpiltBBSTOperation(T); break; // ����
                case 8: MergeBBSTOperation(T); break; // �ϲ�
                case 9: DestroyBBSTOperation(T); break; // ����
                default: fprintf(stderr, "��������ȷ��ֵ��\n"); break;
            }
        }
        system("PAUSE");
        system("CLS"); // ��������
    }
    system("PAUSE");
    getch();
    return 0;
}
