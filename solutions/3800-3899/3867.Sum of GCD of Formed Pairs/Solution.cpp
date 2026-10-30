// 3867. 数对的最大公约数之和 / Sum of GCD of Formed Pairs
// 核心思路：先维护前缀最大值 mx，令 prefix_gcd[i] = gcd(nums[i], mx) 得到每个位置可配对的数值；排序后把第 i 小与第 i 大配对，累加各对的 gcd 即为答案。
// 复杂度：时间复杂度 O(n log n)（排序主导，n 次 gcd 为 O(n log V)），空间复杂度 O(n)。
class Solution {  // LeetCode 题解类
public:  // 公有成员
    long long gcdSum(vector<int>& nums) {  // 返回按规则配对后所有数对的 gcd 之和
        int n = nums.size();  // 数组长度 n
        vector<int> prefix_gcd(n);  // 存放每个位置上的前缀 gcd
        int mx = 0;  // 维护前缀最大值，初值为 0

        for (int i = 0; i < n; i++) {  // 从左到右扫描，构造 prefix_gcd
            int x = nums[i];  // 取出当前元素
            mx = max(mx, x);  // 更新到当前位置为止的最大值
            prefix_gcd[i] = gcd(x, mx);  // 当前元素与其前缀最大值的最大公约数
        }  // prefix_gcd 构造完毕

        sort(prefix_gcd.begin(), prefix_gcd.end());  // 升序排序，为“最小配最大”做准备

        long long ans = 0;  // 累加结果，用 long long 防止溢出
        for (int i = 0; i < n / 2; i++) {  // 枚举配对：第 i 小的元素与第 i 大的元素配对
            ans += gcd(prefix_gcd[i], prefix_gcd[n - i - 1]);  // 累加这一对的最大公约数
        }  // 全部配对处理完毕

        return ans;  // 返回数对的最大公约数之和
    }  // 方法结束
};  // 类结束
