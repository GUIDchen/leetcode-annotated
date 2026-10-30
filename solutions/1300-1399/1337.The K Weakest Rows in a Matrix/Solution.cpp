// 题目：1337. 矩阵中战斗力最弱的 K 行（The K Weakest Rows in a Matrix）
// 思路：每行都是「前面若干个 1 后面全 0」，二分出第一个 0 的下标即为该行 1 的个数；把 (1 的个数, 行号) 组成 pair 排序，取前 k 个的行号。
// 时间复杂度：O(m log n + m log m)，m 行、n 列，二分统计加排序；空间复杂度：O(m)，pair 数组与答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int search(vector<int>& m) {  // 辅助函数：二分求出该行 1 的个数
        int l = 0;  // 左边界
        int h = m.size() - 1;  // 右边界
        while (l <= h) {  // 二分查找第一个 0 的位置
            int mid = l + (h - l) / 2;  // 防溢出的中点写法
            if (m[mid] == 0)  // 中点是 0：第一个 0 在左侧或就是它自己
                h = mid - 1;  // 收缩右边界
            else  // 中点是 1：第一个 0 一定在右侧
                l = mid + 1;  // 收缩左边界
        }  // 循环结束
        return l;  // l 落在第一个 0 的下标上，恰好也等于 1 的个数
    }  // 辅助函数结束

    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {  // mat 是只含 0/1 的矩阵，k 是要返回的行数
        vector<pair<int, int>> p;  // (1 的个数, 行号)：pair 默认按字典序比较，正好先比数量再比行号
        vector<int> res;  // 存放最终的行号
        for (int i = 0; i < mat.size(); i++) {  // 逐行统计
            int count = search(mat[i]);  // 该行军人（1）的数量
            p.push_back({count, i});  // 记录 (数量, 行号)
        }  // 行统计结束
        sort(p.begin(), p.end());  // 升序排序：数量少者优先；数量相同时行号小者优先
        for (int i = 0; i < k; i++) {  // 取最弱的前 k 行
            res.push_back(p[i].second);  // 只需要行号，丢弃数量
        }  // 取出结束
        return res;  // 返回答案
    }  // 方法结束
};  // 类定义结束