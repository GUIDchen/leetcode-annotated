// 题目：109. 有序链表转换二叉搜索树（Convert Sorted List to Binary Search Tree）
// 思路：先把链表的值依次搬进数组（保持有序），再用「区间中点作根」的方式递归建平衡 BST。
// 时间复杂度：O(n)，遍历链表一次、每个元素建一个结点；空间复杂度：O(n)，额外数组与递归栈。
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* dfs(int* nums, int i, int j) {  // 递归建树：nums 是升序数组，[i, j] 是当前子树用到的区间
    if (i > j) {  // 区间为空，没有元素可建
        return NULL;  // 空区间返回空子树
    }  // 空区间处理完毕
    int mid = (i + j) >> 1;  // 取中点作根，左右两侧元素个数尽量相等，从而保证平衡
    struct TreeNode* left = dfs(nums, i, mid - 1);  // 先用左半区间递归建左子树
    struct TreeNode* right = dfs(nums, mid + 1, j);  // 再用右半区间递归建右子树
    struct TreeNode* root = (struct TreeNode*) malloc(sizeof(struct TreeNode));  // 为根结点申请内存（LeetCode 判题器负责释放）
    root->val = nums[mid];  // 根的值取中点元素
    root->left = left;  // 挂上左子树
    root->right = right;  // 挂上右子树
    return root;  // 返回当前子树的根
}  // 递归函数结束

struct TreeNode* sortedListToBST(struct ListNode* head) {  // 有序链表转平衡 BST 的入口
    int size = 0;  // 记录链表结点个数
    struct ListNode* temp = head;  // 遍历指针，从表头开始
    while (temp) {  // 第一趟：数出链表长度
        size++;  // 结点数加一
        temp = temp->next;  // 指针后移
    }  // 统计结束

    int* nums = (int*) malloc(size * sizeof(int));  // 申请等长数组，把链表的值按顺序存成数组
    temp = head;  // 遍历指针重置回表头
    for (int i = 0; i < size; i++) {  // 第二趟：逐项拷贝到数组
        nums[i] = temp->val;  // 取出当前结点的值
        temp = temp->next;  // 指针后移
    }  // 拷贝结束

    struct TreeNode* root = dfs(nums, 0, size - 1);  // 用有序数组递归建平衡 BST
    free(nums);  // 数组已用完，及时释放
    return root;  // 返回整棵树的根
}  // 入口函数结束
