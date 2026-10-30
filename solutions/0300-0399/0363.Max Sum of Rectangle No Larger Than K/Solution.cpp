// 题目：363. 矩形区域不超过 K 的最大数值和（Max Sum of Rectangle No Larger Than K）
// 思路：枚举上下边界把二维压缩成一维列和，再用有序集合维护前缀和，二分找 >= s-k 的最小前缀和来更新答案。
// 时间复杂度：O(m²·n·log n)，枚举上下边界后每列一次二分；空间复杂度：O(n)，列和数组与有序集合。
class Solution {  // LeetCode 题解类
public:  // 对外接口
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {  // matrix 是二维矩阵，k 是子矩阵和的上限
        int m = matrix.size(), n = matrix[0].size();  // 行列数
        const int inf = 1 << 30;  // 用足够大的常数表示负无穷
        int ans = -inf;  // 记录不超过 k 的最大子矩阵和
        for (int i = 0; i < m; ++i) {  // 枚举子矩阵的上边界
            vector<int> nums(n);  // 压缩后的一维列和数组，初值全 0
            for (int j = i; j < m; ++j) {  // 枚举下边界，从上边界开始向下扩展
                for (int h = 0; h < n; ++h) {  // 把第 j 行按列累加进 nums
                    nums[h] += matrix[j][h];  // 行压缩：把二维问题化为一维
                }  // 行压缩结束
                set<int> ts;  // 有序集合，存历史前缀和
                int s = 0;  // 当前前缀和
                ts.insert(0);  // 前缀和 0 代表「什么都不取」，先放入
                for (int x : nums) {  // 遍历压缩后的一维数组
                    s += x;  // 累加得到当前前缀和
                    auto it = ts.lower_bound(s - k);  // 找最小且 >= s-k 的历史前缀和
                    if (it != ts.end()) {  // 存在这样的前缀和，说明子数组和不超过 k
                        ans = max(ans, s - *it);  // 用 s - *it 更新答案（该值不超过 k 且尽量大）
                    }  // 判断结束
                    ts.insert(s);  // 把当前前缀和存入集合，供后续位置使用
                }  // 一维遍历结束
            }  // 下边界枚举结束
        }  // 上边界枚举结束
        return ans;  // 返回最大子矩阵和
    }  // 方法结束
};  // 题解类结束