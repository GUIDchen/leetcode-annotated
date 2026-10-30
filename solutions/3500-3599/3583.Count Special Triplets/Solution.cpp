// 3583. 统计特殊三元组（Count Special Triplets）
// 核心思路：先统计全数组频次作为右侧表，再枚举中间元素 x，用左右两张频次表统计 2x 的个数并累乘取模。
// 复杂度：时间复杂度 O(n)，空间复杂度 O(n)，其中 n 为数组长度。
class Solution {  // 定义题解类
public:  // 公有接口，判题器从这里调用
    int specialTriplets(vector<int>& nums) {  // 统计满足条件的三元组个数
        unordered_map<int, int> left, right;  // left 为左侧频次表，right 为右侧频次表
        for (int x : nums) {  // 先遍历一遍统计每个值的总频次
            right[x]++;  // 记入右侧频次表
        }  // 结束统计
        long long ans = 0;  // 答案用 long long 防止溢出
        const int mod = 1e9 + 7;  // 取模常量 1e9+7
        for (int x : nums) {  // 枚举三元组的中间位置 x
            right[x]--;  // 把当前元素从右侧移出，保证左右划分正确
            ans = (ans + 1LL * left[x * 2] * right[x * 2] % mod) % mod;  // 左侧 2x 个数乘以右侧 2x 个数，累加后取模
            left[x]++;  // 当前元素加入左侧频次表
        }  // 结束枚举
        return (int) ans;  // 转回 int 返回
    }  // 结束函数
};  // 结束类定义
