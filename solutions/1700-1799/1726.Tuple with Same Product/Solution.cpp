// 题目：1726. 同积元组（Tuple with Same Product）
// 思路：统计每个「两数乘积」出现了多少对下标；乘积相同的两对下标可组成 8 个元组（a*b=c*d 的排列）。
// 时间复杂度：O(n^2)，需要枚举所有下标对；空间复杂度：O(n^2)，哈希表最多存 O(n^2) 个不同乘积。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int tupleSameProduct(vector<int>& nums) {  // nums：输入数组，元素互不相同
        unordered_map<int, int> cnt;  // 哈希表：键是两数乘积，值是该乘积出现的下标对数
        for (int i = 1; i < nums.size(); ++i) {  // 枚举下标对中较大的那个下标 i
            for (int j = 0; j < i; ++j) {  // 只枚举 j < i，保证每个下标对恰好统计一次
                int x = nums[i] * nums[j];  // 计算这两个数的乘积
                ++cnt[x];  // 该乘积的出现次数加一
            }  // 内层下标枚举结束
        }  // 所有下标对统计完毕
        int ans = 0;  // 记录满足条件的元组数目
        for (auto& [_, v] : cnt) {  // 遍历每个乘积及其出现次数，_ 是占位键名
            ans += v * (v - 1) / 2;  // 从 v 对下标中任取 2 对，组合数 C(v, 2)
        }  // 乘积统计结束
        return ans << 3;  // 每一对下标对可排列出 8 个元组，左移 3 位等价于乘 8
    }  // 方法结束
};  // 类结束