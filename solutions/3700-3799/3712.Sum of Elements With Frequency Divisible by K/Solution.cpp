// 3712. Sum of Elements With Frequency Divisible by K（3712. 出现次数能被 K 整除的元素总和）
// 核心思路：先用哈希表统计每个元素的出现次数，再遍历统计结果，把出现次数能被 k 整除的元素按“值 × 次数”累加。
// 复杂度：时间 O(n)，空间 O(n)。
class Solution {  // 定义题解类
public:  // 公有成员，供判题器调用
    int sumDivisibleByK(vector<int>& nums, int k) {  // 返回出现次数能被 k 整除的元素总和
        unordered_map<int, int> cnt;  // 哈希表统计每个元素的出现次数
        for (int x : nums) {  // 遍历数组
            ++cnt[x];  // 计数加一（键不存在时默认从 0 开始）
        }  // 统计完成
        int ans = 0;  // 累加答案
        for (auto& [x, v] : cnt) {  // 结构化绑定遍历哈希表中的每个元素与其出现次数
            if (v % k == 0) {  // 出现次数能被 k 整除
                ans += x * v;  // 该元素贡献 值 × 出现次数
            }  // 结束判断
        }  // 结束遍历
        return ans;  // 返回总和
    }  // 方法结束
};  // 类定义结束
