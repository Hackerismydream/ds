#include "main.h"
#include "AVLTree.h"

/**
 * ����Сʧ������p����������
 *
 * @param p ��Сʧ������
 */
void R_Rotate(BBSTree &p) {
    BBSTree lc = p->lchild; // lcָ��p��������
    p->lchild = lc->rchild; // lc������������Ϊp����������
    lc->rchild = p; // ��p���Ϊlc�����Һ���
    p = lc; // pָ���µĸ����
}

/**
 * ����Сʧ������p����������
 *
 * @param p ��Сʧ������
 */
void L_Rotate(BBSTree &p) {
    BBSTree rc = p->rchild;
    p->rchild = rc->lchild;
    rc->lchild = p;
    p = rc;
}

/**
 * ��T����ƽ�⴦��
 *
 * @param T ��T
 */
void LeftBalance(BBSTree &T) {
    BBSTree lc, rd;
    lc = T->lchild;
    switch (lc->bf) {
        case LH: {
            T->bf = lc->bf = EH;
            R_Rotate(T);
            break;
        } case RH: {
            rd = lc->rchild;
            switch (rd->bf) {
                case LH: {
                    T->bf = RH;
                    lc->bf = EH;
                    break;
                } case EH: {
                    T->bf = lc->bf = EH;
                    break;
                } case RH: {
                    T->bf = EH;
                    lc->bf = LH;
                    break;
                }
            }
            rd->bf = EH;
            L_Rotate(T->lchild);
            R_Rotate(T);
            break;
        }
    }
}

/**
 * ��T����ƽ�⴦��
 *
 * @param T ��T
 */
void RightBalance(BBSTree &T) {
    BBSTree rc, ld;
    rc = T->rchild;
    switch (rc->bf) {
        case RH:
            T->bf = rc->bf = EH;
            L_Rotate(T);
            break;
        case LH:
            ld = rc->lchild;
            switch (ld->bf) {
                case RH:
                    T->bf = LH;
                    rc->bf = EH;
                    break;
                case EH:
                    T->bf = rc->bf = EH;
                    break;
                case LH:
                    T->bf = EH;
                    rc->bf = RH;
                    break;
            }
            ld->bf = EH;
            R_Rotate(T->rchild);
            L_Rotate(T);
            break;
    }
}

/**
 * ƽ��������Ĳ������
 *
 * @param T ƽ�������T
 * @param e ������Ԫ��
 * @param taller �������Ƿ�߹�������
 * @return �ɹ�����TRUE
 */
Status InsertAVL(BBSTree &T, RcdType e, Status &taller) {
    if (NULL == T) {
        // TΪ�գ�������
        T = (BBSTree)malloc(sizeof(BBSTNode));
        T->data = e;
        T->bf = EH;
        T->lchild = NULL;
        T->rchild = NULL;
        taller = TRUE;
    } else if (e.key == T->data.key) {
        // �Ѿ����ڸõ�
        taller = FALSE;
        return FALSE;
    } else if (e.key < T->data.key) {
        // ���뵽������
        if (FALSE == InsertAVL(T->lchild, e, taller)) {
            return FALSE;
        }
        if (TRUE == taller) {
            switch (T->bf) {
                case LH: {
                    LeftBalance(T);
                    taller = FALSE;
                    break;
                } case EH: {
                    T->bf = LH;
                    taller = TRUE;
                    break;
                } case RH: {
                    T->bf = EH;
                    taller = FALSE;
                    break;
                }
            }
        }
    } else {
        if (FALSE == InsertAVL(T->rchild, e, taller)) {
            return FALSE;
        }
        if (TRUE == taller) {
            switch (T->bf) {
                case LH: {
                    T->bf = EH;
                    taller = FALSE;
                    break;
                } case EH: {
                    T->bf = RH;
                    taller = TRUE;
                    break;
                } case RH: {
                    RightBalance(T);
                    taller = FALSE;
                    break;
                }
            }
        }
    }
    return TRUE;
}

/**
 * ��AVL������key
 *
 * @param T AVL��
 * @param key �����ҵĹؼ���
 * @return �ҵ��򷵻ظùؼ��ֵĽ�㣬�Ҳ����򷵻�NULL
 */
BBSTree SearchBBST(BBSTree T, KeyType key) {
    if (NULL == T) {
        return NULL;
    }
    if (T->data.key == key) {
        return T;
    }
    if (T->data.key > key) {
        return SearchBBST(T->lchild, key);
    }
    return SearchBBST(T->rchild, key);
}

/**
 * ������ʾ����ӡAVL��
 *
 * @param T AVL��
 */
void ConcaveTablePrintBBST(BBSTree T, int m) {
    int i;
    for (i = 1; i < m; i++) {
        printf("    ");
    }
    printf("%5d<bf:%d>", T->data.key, T->bf);
    if (T->lchild != NULL) {
        printf("\n");
        ConcaveTablePrintBBST(T->lchild, m + 1);
    }
    if (T->rchild != NULL) {
        printf("\n");
        ConcaveTablePrintBBST(T->rchild, m + 1);
    }
}

/**
 * ���ű�ʾ����ӡAVL��
 *
 * @param T AVL��
 */
void ParenthesisPrintBBST(BBSTree T) {
    if (NULL == T) {
        return;
    }
    printf("%d", T->data.key);
    if (T->lchild != NULL || T->rchild != NULL) {
        printf("(");
        if (T->lchild != NULL) {
            ParenthesisPrintBBST(T->lchild);
        } else if (T->rchild != NULL) {
            printf("#");
        }
        printf(",");
        if (T->rchild != NULL) {
            ParenthesisPrintBBST(T->rchild);
        } else if (T->lchild != NULL){
            printf("#");
        }
        printf(")");
    }
}

/**
 * ƽ���������ɾ������
 *
 * @param T
 * @param key
 * @param shorter
 * @return
 */
Status DeleteAVL(BBSTree &T, KeyType key, Status &shorter) {
    if (NULL == T) {
        // ��Ϊ��
        return FALSE;
    } else if (T->data.key == key) {
        // �ҵ�Ԫ�ؽ��
        BBSTree p = NULL;
        if (NULL == T->lchild) {
            // ������Ϊ��
            p = T;
            T = T->rchild;
            free(p);
            shorter = TRUE; // �߶ȱ䰫
        } else if (T->rchild == NULL) {
            // ������Ϊ��
            p = T;
            T = T->lchild;
            free(p);
            shorter = TRUE; // �߶ȱ䰫
        } else {
            // ��������������
            p = T->lchild;
            while (p->rchild != NULL) {
                p = p->rchild;
            }
            T->data = p->data;
            // ����������ɾ��ǰ�����
            DeleteAVL(T->lchild, p->data.key, shorter);
        }
    } else if (T->data.key > key) {
        if (DeleteAVL(T->lchild, key, shorter) == FALSE) {
            return FALSE;
        }
        if (shorter == TRUE) {
            switch (T->bf) {
                case LH: {
                    T->bf = EH;
                    shorter = TRUE;
                    break;
                } case EH: {
                    T->bf = RH;
                    shorter = FALSE;
                    break;
                } case RH: {
                    RightBalance(T);
                    if (T->rchild->bf == EH) {
                        shorter = FALSE;
                    } else {
                        shorter = TRUE;
                    }
                    break;
                }
            }
        }
    } else {
        if (DeleteAVL(T->rchild, key, shorter) == FALSE) {
            return FALSE;
        }
        if (shorter == TRUE) {
            switch (T->bf) {
                case LH: {
                    LeftBalance(T);
                    if (T->lchild->bf == EH) {
                        shorter = FALSE;
                    } else {
                        shorter = TRUE;
                    }
                    break;
                } case EH: {
                    T->bf = LH;
                    shorter = FALSE;
                    break;
                } case RH: {
                    T->bf = EH;
                    shorter = TRUE;
                    break;
                }
            }
        }
    }
    return TRUE;
}

/**
 * ���ƽ��������ؼ���
 * @param key �ؼ���
 */
void visit(KeyType key) {
    printf("%d  ", key);
}

/**
 * ǰ�����ƽ�������
 *
 * @param T ƽ�������
 * @param visit ����ָ��
 */
void PreOrderTraverse(BBSTree T, void( *visit)(KeyType)) {
    if (NULL == T) {
        return;
    }
  	visit(T->data.key);
    PreOrderTraverse(T->lchild, visit);
    PreOrderTraverse(T->rchild, visit);
}

/**
 * �������ƽ�������
 *
 * @param T ƽ�������
 * @param visit ����ָ��
 */
void InOrderTraverse(BBSTree T, void( *visit)(KeyType)) {
    if (NULL == T) {
        return;
    }
    InOrderTraverse(T->lchild, visit);
    visit(T->data.key);
    InOrderTraverse(T->rchild, visit);
}

/**
 * �������ƽ�������
 *
 * @param T ƽ�������
 * @param visit ����ָ��
 */
void PostOrderTraverse(BBSTree T, void( *visit)(KeyType)) {
    if (NULL == T) {
      	return;
    }
    PostOrderTraverse(T->lchild, visit);
    PostOrderTraverse(T->rchild, visit);
    visit(T->data.key);
}

/**
 * ��α���ƽ�������
 *
 * @param T ƽ�������
 * @param visit ����ָ��
 * @param level ���
 * @return
 */
Status LevelOrderTraverse(BBSTree T, void( *visit)(KeyType), int level) {
    if (!T || level < 0) {
        return ERROR;
    }
    if (level == 0) {
        visit(T->data.key);
        return OK;
    }
    return LevelOrderTraverse(T->lchild, visit, level - 1) +
    		LevelOrderTraverse(T->rchild, visit, level - 1);
}

/**
 * �����ӡ
 *
 * @param T ƽ�������
 */
void PrintNodeByLevel(BBSTree T) {
    if (NULL == T) {
        return;
    }
    int level;
    for (level = 0; ; level++) {
        if (!LevelOrderTraverse(T, visit, level)) {
            break;
        }
    }
}

/**
 * ����ƽ����������ֳɴ���key��С��key������
 *
 * @param T �����ѵ�ƽ�������
 * @param key ���ѵĹؼ���
 * @param T1 �ؼ���ȫ��С��key��ƽ�������
 * @param T2 �ؼ���ȫ������key��ƽ�������
 */
void SpiltBBST(BBSTree T, KeyType key, BBSTree &T1, BBSTree &T2) {
    Status taller = FALSE;
	if (T != NULL) {
		SpiltBBST(T->lchild, key, T1, T2); // �ݹ����������
		if(T->data.key > key) {
            InsertAVL(T1, T->data, taller);
		} else {
            InsertAVL(T2, T->data, taller);
		}
		SpiltBBST(T->rchild, key, T1, T2);
	}
}

/**
 * �ϲ�ƽ�������
 *
 * @param T1 �ϲ����ƽ�������
 * @param T2 ���ϲ���ƽ�������
 */
void MergeBBST(BBSTree &T1, BBSTree T2) {
    Status taller = FALSE;
    if (T2 != NULL) {
        MergeBBST(T1, T2->lchild);
        InsertAVL(T1, T2->data, taller);
        MergeBBST(T1, T2->rchild);
    }
}

/**
 * ����ƽ�������
 *
 * @param T ƽ�������
 */
void DestroyBBST(BBSTree &T) {
    if (T != NULL) {
        DestroyBBST(T->lchild);
        DestroyBBST(T->rchild);
        free(T);
    }
}
