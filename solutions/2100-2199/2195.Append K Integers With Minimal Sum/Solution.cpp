// 题目：2195. 向数组中追加 K 个整数（Append K Integers With Minimal Sum）
// 思路：给数组补上哨兵 0 与 2e9 后排序，数组被切成若干段空缺区间，从最小的空缺开始贪心取数，用等差数列公式一次求和。
// 时间复杂度：O(n log n)，排序为主；空间复杂度：O(1)，只在原数组上追加两个哨兵。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minimalKSum(vector<int>& nums, int k) {  // nums：已有数组；k：还要追加的整数个数
        nums.push_back(0);  // 左哨兵 0：让 1 之前也构成一段可用的空缺区间
        nums.push_back(2e9);  // 右哨兵 2e9：数值足够大，保证一定能凑满 k 个数
        sort(nums.begin(), nums.end());  // 排序后相邻元素之间才是有序的空缺区间
        long long ans = 0;  // 追加数字的最小总和，用 long long 防止溢出
        for (int i = 0; i < nums.size() - 1 && k > 0; ++i) {  // 逐段扫描；k 用完就提前结束
            int m = max(0, min(k, nums[i + 1] - nums[i] - 1));  // 本段 (nums[i], nums[i+1]) 内可取的个数，且不超过剩余需要的 k
            ans += 1LL * (nums[i] + 1 + nums[i] + m) * m / 2;  // 取本段最小的 m 个数求和：首项 nums[i]+1，末项 nums[i]+m
            k -= m;  // 扣掉本段已经追加的个数
        }  // for 结束
        return ans;  // 返回最小总和
    }  // 方法结束
};  // 类定义结束