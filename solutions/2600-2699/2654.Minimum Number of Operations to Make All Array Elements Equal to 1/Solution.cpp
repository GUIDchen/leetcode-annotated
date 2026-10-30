// 题目：2654. 使数组所有元素变成 1 的最少操作次数（Minimum Number of Operations to Make All Array Elements Equal to 1）
// 核心思路：先数已有的 1；若没有，就找 gcd 为 1 的最短子数组，用 mi-1 次操作把它变成一个 1，再用 n-1 次把 1 传染给其余元素。
// 时间复杂度：O(n^2 log V)，枚举所有子数组并求 gcd；空间复杂度：O(1)，只用了常数个辅助变量。
class Solution {  // 题解类
public:  // 方法对外可见
    int minOperations(vector<int>& nums) {  // nums：输入数组；返回使全部元素变成 1 的最少操作次数
        int n = nums.size();  // 记录数组长度 n
        int cnt = 0;  // cnt 统计数组中等于 1 的元素个数
        for (int x : nums) {  // 逐个遍历数组元素
            if (x == 1) {  // 当前元素正好是 1
                ++cnt;  // 1 的个数加一
            }
        }
        if (cnt) {  // 数组里已经有 1，可以直接用 1 去「传染」其余元素
            return n - cnt;  // 每个非 1 元素一次操作即可变 1，共需要 n - cnt 次
        }
        int mi = n + 1;  // mi 保存能凑出 1 的最短子数组长度，n+1 表示「尚未找到」
        for (int i = 0; i < n; ++i) {  // 枚举子数组的左端点 i
            int g = 0;  // 区间 gcd 累加器，gcd(0, x) = x，便于从零开始累
            for (int j = i; j < n; ++j) {  // 右端点 j 从 i 开始向右扩展
                g = gcd(g, nums[j]);  // 把 nums[j] 并入当前区间的 gcd
                if (g == 1) {  // 该区间的 gcd 为 1，可以通过操作造出一个 1
                    mi = min(mi, j - i + 1);  // 用更短的区间长度更新 mi
                }
            }
        }
        return mi > n ? -1 : n - 1 + mi - 1;  // 找不到 gcd 为 1 的区间返回 -1；否则先花 mi-1 次造 1，再花 n-1 次传染
    }
};  // class Solution 结束