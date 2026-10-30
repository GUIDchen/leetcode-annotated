// 题目：2447. 最大公因数等于 K 的子数组数目（Number of Subarrays With GCD Equal to K）
// 思路：枚举子数组左端点 i，固定 i 后向右延伸右端点 j，边延伸边维护区间 GCD（gcd 具有结合性，新值 = gcd(旧值, 新元素)），每次判断是否恰为 k。
// 时间复杂度：O(n^2 log V)，共 O(n^2) 次 gcd 调用，每次 O(log V)；空间复杂度：O(1)，只用常数个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int subarrayGCD(vector<int>& nums, int k) {  // nums 是输入数组，k 是目标最大公因数
        int n = nums.size();  // 数组长度，后面两重循环都要用到
        int ans = 0;  // 统计满足条件的子数组个数
        for (int i = 0; i < n; ++i) {  // 枚举子数组的左端点 i
            int g = 0;  // 区间 GCD 的初始值取 0，因为 gcd(0, x) = x，第一元素进来时正好得到它本身
            for (int j = i; j < n; ++j) {  // 枚举右端点 j，从 i 开始保证子数组非空
                g = gcd(g, nums[j]);  // 把 nums[j] 并入当前子数组，增量更新区间 GCD
                ans += g == k;  // 若区间 GCD 恰好等于 k 就计数加一（布尔值转 int）
            }
        }
        return ans;  // 返回所有满足条件的子数组数量
    }
};
