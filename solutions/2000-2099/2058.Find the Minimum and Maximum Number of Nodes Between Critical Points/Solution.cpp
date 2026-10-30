// 题目：2058. 找出临界点之间的最小和最大距离（Find the Minimum and Maximum Number of Nodes Between Critical Points）
// 思路：一次遍历链表，用下标 i 标记当前中间节点；遇到波峰/波谷就更新第一个临界点位置以及最小、最大间距。
// 时间复杂度：O(n)，链表只走一遍；空间复杂度：O(1)，只用了常数个变量。
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
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {  // head：链表头结点；返回 [最小距离, 最大距离]
        vector<int> ans = {1 << 30, 0};  // ans[0] 存最小间距（先置一个大数），ans[1] 存最大间距
        int first = -1, last = -1;  // 第一个、上一个临界点的下标；-1 表示还没遇到过临界点
        for (int i = 0; head->next->next; head = head->next, ++i) {  // i 是中间节点的下标；剩余不足三个节点时停止
            int a = head->val, b = head->next->val, c = head->next->next->val;  // a、b、c 是相邻三个节点的值
            if (b < min(a, c) || b > max(a, c)) {  // b 比两边都小（波谷）或都大（波峰），即为临界点
                if (last == -1) {  // 这是遇到的第一个临界点
                    first = i;  // 记录第一个临界点的下标
                    last = i;  // 它同时也是「上一个」临界点
                } else {  // 之后遇到的临界点
                    ans[0] = min(ans[0], i - last);  // 与上一个临界点的距离用来更新最小间距
                    last = i;  // 当前点成为新的「上一个」临界点
                    ans[1] = max(ans[1], last - first);  // 当前点到第一个临界点的距离即新的最大间距
                }
            }
        }
        return first == last ? vector<int>{-1, -1} : ans;  // 临界点不足两个时（first==last）按题意返回 [-1,-1]
    }
};