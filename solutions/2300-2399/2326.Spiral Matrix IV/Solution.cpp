// 题目：2326. 螺旋矩阵 IV（Spiral Matrix IV）
// 思路：从左上角出发，按右→下→左→上的固定顺序螺旋前进，把链表节点值依次填入 m×n 矩阵；
//       方向走不通就顺时针换向，链表用完立即停止；时间复杂度：O(m×n)，空间复杂度：O(m×n)（答案矩阵）。
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
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {  // m 行 n 列的目标矩阵；head 是提供填数序列的链表头
        vector<vector<int>> ans(m, vector<int>(n, -1));  // 答案矩阵初始化为 -1，-1 同时充当“该格尚未填数”的标记
        int i = 0, j = 0, k = 0;  // (i, j) 是当前格子坐标；k 是方向下标，0 右、1 下、2 左、3 上
        const int dirs[5] = {0, 1, 0, -1, 0};  // 方向增量表，末尾多一个 0，便于一次取出 dirs[k]（行）与 dirs[k+1]（列）
        while (1) {  // 外层循环：每轮把一个链表节点值放进一个格子
            ans[i][j] = head->val;  // 把当前链表节点的值写入当前格子
            head = head->next;  // 链表指针后移，准备下一个待填的数字
            if (!head) {  // 链表已经走完
                break;  // 没有更多数字可填，结束外层循环
            }  // 头指针判空的 if 结束
            while (1) {  // 内层循环：沿当前方向试探下一个可填的相邻格子
                int x = i + dirs[k], y = j + dirs[k + 1];  // 当前方向走一步后的候选坐标
                if (x >= 0 && x < m && y >= 0 && y < n && ans[x][y] == -1) {  // 行、列都不越界，且该格仍是未填的 -1，才允许走
                    i = x;  // 候选格合法，更新行坐标
                    j = y;  // 候选格合法，更新列坐标
                    break;  // 已站在新格子上，跳出内层循环
                }  // 可走分支结束
                k = (k + 1) % 4;  // 当前方向被挡住，顺时针旋转到下一个方向再试
            }  // 内层循环结束（i、j 已指向下一个待填格）
        }  // 外层循环结束
        return ans;  // 返回填好的螺旋矩阵，未用到的格子保持 -1
    }  // 方法结束
};  // 类定义结束