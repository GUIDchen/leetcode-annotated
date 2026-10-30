// 题目：3356. 零数组变换 II（Zero Array Transformation II）
// 思路：二分答案 k，用差分数组在 O(n+k) 内判断前 k 个区间操作能否把 nums 全减成 0；可行性随 k 单调，故可二分。
// 时间复杂度：O((n+m) log m)，每次 check 为 O(n+k)；空间复杂度：O(n)，差分数组与变长数组同阶。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露题解方法
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {  // nums：目标数组；queries：区间减操作列表
        int n = nums.size();  // 数组长度
        int d[n + 1];  // 差分数组，多开一位给 r+1 处的边界回扣留位置（GCC 的变长数组扩展）
        int m = queries.size();  // 操作总数
        int l = 0, r = m + 1;  // 二分区间 [0, m+1]，m+1 表示「全部操作也不够」
        auto check = [&](int k) -> bool {  // lambda：判断只用前 k 个操作能否让整个数组归零
            memset(d, 0, sizeof(d));  // 每次判定前先把差分数组清零
            for (int i = 0; i < k; ++i) {  // 把前 k 个操作累加到差分数组
                int l = queries[i][0], r = queries[i][1], val = queries[i][2];  // 取出当前操作的左端点 l、右端点 r 与减量 val（内层同名变量遮蔽了外层 l）
                d[l] += val;  // 区间起点加上减量
                d[r + 1] -= val;  // 区间终点后一位减去减量，作为差分的收口
            }
            for (int i = 0, s = 0; i < n; ++i) {  // s 滚动累加差分，等于位置 i 实际被减掉的总量
                s += d[i];  // 还原出当前位置的累计减量
                if (nums[i] > s) {  // 减量不足，nums[i] 还剩下正数，无法归零
                    return false;  // 该 k 不可行
                }
            }
            return true;  // 每个位置都减够，前 k 个操作可行
        };
        while (l < r) {  // 二分查找最小的可行 k
            int mid = (l + r) >> 1;  // 取中点
            if (check(mid)) {  // 前 mid 个操作可行
                r = mid;  // 答案不会超过 mid，收缩右边界
            } else {  // 前 mid 个操作不可行
                l = mid + 1;  // 答案必须更大，收缩左边界
            }
        }
        return l > m ? -1 : l;  // l 落到 m+1 说明所有操作也不够，返回 -1；否则 l 就是最少操作个数
    }  // 题解方法结束
};  // 题解类结束
