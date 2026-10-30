// 3755. 最大平衡异或子数组的长度（Find Maximum Balanced XOR Subarray Length）
// 核心思路：平衡子数组要求偶数个数与奇数个数相等且异或和为 0；用（前缀异或, 偶数个数-奇数个数）作状态键，相同键的两前缀之间即为平衡区间，取最大下标差。
// 复杂度：时间 O(n)，空间 O(n)。
class Solution {  // 定义解法类
public:  // 公有接口
    int maxBalancedSubarray(vector<int>& nums) {  // 接口：返回最长的平衡异或子数组长度
        unordered_map<long long, int> d;  // d 记录某个状态键（前缀异或, 偶数-奇数计数）首次出现的下标
        int ans = 0;  // ans 保存当前找到的最大区间长度
        int a = 0, b = nums.size();  // a 为前缀异或和；b 从 n 出发，偶数 +1、奇数 -1
        d[(long long) b] = -1;  // 空前缀对应键（a = 0, b = n），下标记为 -1
        for (int i = 0; i < nums.size(); ++i) {  // 从左到右枚举子数组右端点 i
            a ^= nums[i];  // 把当前元素异或进前缀异或和
            b += nums[i] % 2 == 0 ? 1 : -1;  // 偶数个数增多、奇数个数增多分别对应加一减一
            long long key = (1LL * a << 32) | b;  // 把 a 与 b 拼成一个 long long 作为哈希键
            if (d.contains(key)) {  // 如果该状态之前出现过，说明中间这一段是平衡的
                ans = max(ans, i - d[key]);  // 用 i 减去首次出现下标更新最大长度
            } else {  // 否则说明这是该状态第一次出现
                d[key] = i;  // 记录它的下标，供后面求长度
            }  // if-else 结束
        }  // for 结束
        return ans;  // 返回最长平衡异或子数组长度
    }  // 方法结束
};  // 类定义结束
