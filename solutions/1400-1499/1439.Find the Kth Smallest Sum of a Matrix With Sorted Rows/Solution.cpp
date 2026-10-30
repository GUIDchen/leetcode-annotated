// 题目：1439. 有序矩阵中的第 k 个最小数组和（Find the Kth Smallest Sum of a Matrix With Sorted Rows）
// 思路：逐行归并「前 k 小」：把已保留的至多 k 个和与当前行元素两两相加，排序后只留最小的 k 个。
// 时间复杂度：O(m·(n·k)·log(n·k))，m 行 n 列；空间复杂度：O(n·k)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int kthSmallest(vector<vector<int>>& mat, int k) {  // mat 是每行递增的矩阵，k 是要求的排名
        // 注意：这里用变长数组（VLA）让缓冲区长度随参数 k 变化，避免动态分配
        int pre[k];  // pre 保存上一轮处理完的前 k 小数组和（变长数组，长度由参数 k 决定）
        // 候选个数 = size × 列数，而 size ≤ k，所以这个上界足够
        int cur[mat[0].size() * k];  // cur 是本轮候选和缓冲区，最多「k 个旧和 × 每行列数」个候选
        memset(pre, 0, sizeof pre);  // 清零：零行时唯一的和是 pre[0]=0，其余位置本轮不会被读取
        int size = 1;  // size 是 pre 中的有效元素个数，初始只有 pre[0] 有效
        for (auto& row : mat) {  // 逐行把新的一行并入已有的和集合
            int i = 0;  // i 是 cur 的写入下标
            for (int j = 0; j < size; ++j) {  // 枚举上一轮保留下来的每个和
                for (int& v : row) {  // 与本行的每个元素相加，形成新一行的候选
                    cur[i++] = pre[j] + v;  // 把「旧和 + 本行元素」写入候选数组
                }
            }  // 对所有候选升序排序
            sort(cur, cur + i);  // 只需要前 k 小（不足 k 个则全要）
            size = min(i, k);  // 把最小的 size 个候选搬回 pre
            for (int j = 0; j < size; ++j) {  // 覆盖上一轮结果，作为下一轮的输入
                pre[j] = cur[j];
            }
        }
        return pre[k - 1];  // pre 已升序且长度至少 k，下标 k-1 就是第 k 小的和
    }
};