// 题目：3355. 零数组变换 I（Zero Array Transformation I）
// 思路：用差分数组统计每个下标被查询区间覆盖的次数，再前缀还原；每个位置覆盖次数不少于 nums[i] 时就能减到 0。
// 时间复杂度：O(n + q)，q 为查询数量；空间复杂度：O(n)，一个长度 n+1 的差分数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isZeroArray(vector<int>& nums, vector<vector<int>>& queries) {  // nums：目标数组；queries：每个元素是一次区间减一操作 [l, r]
        int n = nums.size();  // 缓存数组长度
        int d[n + 1];  // 差分数组，多留一格用来承接 r + 1 处的减一
        memset(d, 0, sizeof(d));  // 把差分数组全部初始化为 0
        for (const auto& q : queries) {  // 遍历所有查询
            int l = q[0], r = q[1];  // 取出区间的左右端点
            ++d[l];  // 区间起点处覆盖次数加一
            --d[r + 1];  // 终点后一格减一，前缀累加时正好抵消，从而把区间标记为「覆盖一次」
        }  // 结束查询处理
        for (int i = 0, s = 0; i < n; ++i) {  // 前缀还原每个下标的覆盖次数；s 保存当前覆盖次数
            s += d[i];  // 累加差分，得到当前下标被覆盖的次数
            if (nums[i] > s) {  // 覆盖次数不足以把 nums[i] 减到 0
                return false;  // 直接判定不可行
            }  // 结束覆盖不足的判断
        }  // 结束还原循环
        return true;  // 每个位置都够减，返回 true
    }  // 结束题解方法
};  // 结束题解类
