// 题目：654. 最大二叉树（Maximum Binary Tree）
// 核心思路：区间最大值作根，左右两段递归建树（分治）。
// 时间复杂度：最坏 O(n^2)（每次线性扫描找最大值）；空间复杂度：O(n)（节点数与递归栈）。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* construct(int* nums, int start, int end) {  // 递归构造左闭右开区间 [start, end) 对应的子树，返回其根节点
    if (start >= end) {  // 区间为空，说明这一段没有节点可建
        return NULL;  // 空区间返回空指针，作为递归出口
    }
    int idx = 0;  // idx 记录区间最大值所在下标，初值 0（区间非空时会被更新）
    int maxVal = -1;  // maxVal 记录当前区间最大值，元素非负，故用 -1 作初始下界
    for (int i = start; i < end; i++) {  // 线性扫描 [start, end) 找出最大值及其下标
        if (nums[i] > maxVal) {  // 发现更大的元素就更新最大值下标
            idx = i;  // 更新最大值下标
            maxVal = nums[i];  // 更新当前最大值
        }
    }
    struct TreeNode* res = (struct TreeNode*) malloc(sizeof(struct TreeNode));  // 为根节点分配内存（此时区间非空，maxVal 一定是某个真实元素）
    res->val = maxVal;  // 根节点的值就是区间最大值
    res->left = construct(nums, start, idx);  // 左子树由最大值左侧区间 [start, idx) 递归构造
    res->right = construct(nums, idx + 1, end);  // 右子树由最大值右侧区间 [idx + 1, end) 递归构造
    return res;  // 返回构造好的子树根
}

struct TreeNode* constructMaximumBinaryTree(int* nums, int numsSize) {  // 题目入口：整个数组 [0, numsSize) 的最大值作为整棵树的根
    return construct(nums, 0, numsSize);  // 直接交给递归函数，区间取左闭右开
}
