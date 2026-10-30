// 题目：3062. 链表游戏的获胜者（Winner of the Linked List Game）
// 思路：链表每两个节点为一组（偶数下标 vs 奇数下标），比较大小累计双方得分，最后按总分判定胜者。
// 时间复杂度：O(n)，只遍历一遍链表；空间复杂度：O(1)，仅用两个计数变量。
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string gameResult(ListNode* head) {  // head 是链表头指针，返回胜者名字："Odd"、"Even" 或 "Tie"
        int odd = 0, even = 0;  // odd 记录奇数下标节点赢的组数，even 记录偶数下标节点赢的组数
        for (; head != nullptr; head = head->next->next) {  // 每次前进两个节点，恰好把链表切成若干「一组两个」；题目保证节点数为偶数
            int a = head->val;  // 组内前一个节点（偶数下标）的值
            int b = head->next->val;  // 组内后一个节点（奇数下标）的值
            odd += a < b;  // 若前一个更小，则奇数下标赢一局：比较结果布尔值会自动转成 0/1 累加
            even += a > b;  // 若前一个更大，则偶数下标赢一局；两值相等时双方都不加分
        }  // 这一组处理完毕，循环条件把 head 推进到下一组的首节点
        if (odd > even) {  // 奇数下标总分更高，奇数方获胜
            return "Odd";  // 返回奇数方获胜
        }  // 奇数不占优，继续判断偶数方
        if (odd < even) {  // 偶数下标总分更高
            return "Even";  // 返回偶数方获胜
        }  // 两边都不占优说明平局
        return "Tie";  // 返回平局
    }  // 方法结束
};  // 类定义结束