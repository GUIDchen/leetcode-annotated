// 题目：1634. 求两个多项式链表的和（Add Two Polynomials Represented as Linked Lists）
// 思路：按幂次从高到低归并两条有序链表，幂次相同时把系数相加，系数为 0 的项丢弃。
// 时间复杂度：O(m + n)，两条链表各遍历一次；空间复杂度：O(1) 额外空间（结果复用原结点，仅在系数非零时新建结点）。
/**
 * Definition for polynomial singly-linked list->
 * struct PolyNode {
 *     int coefficient, power;
 *     PolyNode *next;
 *     PolyNode(): coefficient(0), power(0), next(nullptr) {};
 *     PolyNode(int x, int y): coefficient(x), power(y), next(nullptr) {};
 *     PolyNode(int x, int y, PolyNode* next): coefficient(x), power(y), next(next) {};
 * };
 */

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    PolyNode* addPoly(PolyNode* poly1, PolyNode* poly2) {  // poly1、poly2 是两条按幂次递减排列的多项式链表，返回合并后的新链表
        PolyNode* dummy = new PolyNode();  // 哨兵头结点，它的 next 指向结果的第一个结点，省去对头结点的特殊判断
        PolyNode* curr = dummy;  // curr 指向结果链表的尾结点，始终往它后面接结点
        while (poly1 && poly2) {  // 两条链表都还有结点时归并
            if (poly1->power > poly2->power) {  // 情况一：poly1 的幂次更大，说明它的这一项应排在前面
                curr->next = poly1;  // 把 poly1 当前结点直接接到结果尾部（原地复用结点）
                poly1 = poly1->next;  // poly1 指针后移
                curr = curr->next;  // 结果尾指针后移到刚接入的结点
            } else if (poly1->power < poly2->power) {  // 情况二：poly2 的幂次更大
                curr->next = poly2;  // 把 poly2 当前结点直接接到结果尾部
                poly2 = poly2->next;  // poly2 指针后移
                curr = curr->next;  // 结果尾指针后移到刚接入的结点
            } else {  // 情况三：两者幂次相同，需要合并同类项
                int c = poly1->coefficient + poly2->coefficient;  // 合并后的系数
                if (c != 0) {  // 系数不为 0 才保留这一项
                    curr->next = new PolyNode(c, poly1->power);  // 新建结点（系数, 幂次）接到结果尾部
                    curr = curr->next;  // 结果尾指针后移
                }  // if 结束（系数为 0 时整项被丢弃）
                poly1 = poly1->next;  // poly1 指针后移，这一项已处理完
                poly2 = poly2->next;  // poly2 指针后移，这一项已处理完
            }  // 同幂次分支结束
        }  // while 结束
        if (!poly1) {  // poly1 先走完，说明剩下的是 poly2 的尾部，且幂次都更小
            curr->next = poly2;  // 直接把 poly2 剩余部分整体接到结果尾部
        }  // if 结束
        if (!poly2) {  // poly2 先走完，说明剩下的是 poly1 的尾部，且幂次都更小
            curr->next = poly1;  // 直接把 poly1 剩余部分整体接到结果尾部
        }  // if 结束
        return dummy->next;  // 跳过哨兵，返回真正的结果头结点
    }  // addPoly 方法结束
};  // 题解类定义结束