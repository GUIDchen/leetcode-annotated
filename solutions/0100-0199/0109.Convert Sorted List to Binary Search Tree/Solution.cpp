// 题目：109. 有序链表转换二叉搜索树（Convert Sorted List to Binary Search Tree）
// 思路：先把链表的值搬进 vector（天然有序），再用「区间中点作根」的递归方式建平衡 BST。
// 时间复杂度：O(n)，链表遍历一次、每个元素建一个结点；空间复杂度：O(n)，vector 与递归栈。
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
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    TreeNode* sortedListToBST(ListNode* head) {  // head 是有序链表头，返回平衡 BST 的根
        vector<int> nums;  // 把链表的值按顺序存进数组，后面用下标随机访问
        for (; head; head = head->next) {  // 遍历链表，每次把 head 推进到下一个结点
            nums.push_back(head->val);  // 取出当前结点的值
        }  // 拷贝结束
        auto dfs = [&](this auto&& dfs, int i, int j) -> TreeNode* {  // C++23 的显式对象参数，让 lambda 能递归调用自己
            if (i > j) {  // 区间 [i, j] 为空，没有元素可建
                return nullptr;  // 空区间对应空子树
            }  // 空区间处理完毕
            int mid = (i + j) >> 1;  // 取中点作根，左右两侧数量均衡
            TreeNode* left = dfs(i, mid - 1);  // 先递归建左子树
            TreeNode* right = dfs(mid + 1, j);  // 再递归建右子树
            return new TreeNode(nums[mid], left, right);  // 用中点值建根结点，并挂上左右子树
        };  // 递归 lambda 定义结束
        return dfs(0, nums.size() - 1);  // 从整个数组区间开始建树
    }  // 方法结束
};  // 题解类结束
