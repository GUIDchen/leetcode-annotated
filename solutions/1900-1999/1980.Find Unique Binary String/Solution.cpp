// 题目：1980. 找出不同的二进制字符串（Find Unique Binary String）
// 思路：长度为 n 的串最多只有 n+1 种「1 的个数」，用位掩码记下已出现的个数，取第一个空缺 i，构造 i 个 1 加 n-i 个 0 即可。
// 时间复杂度：O(n^2)，统计 1 与构造字符串；空间复杂度：O(1)，只用一个掩码。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string findDifferentBinaryString(vector<string>& nums) {  // nums：n 个长度均为 n 的二进制串，返回一个不在其中的同长度二进制串
        int mask = 0;  // 位掩码：第 k 位为 1 表示已存在「恰好 k 个 1」的字符串
        for (auto& x : nums) {  // 遍历给定的每个字符串
            int cnt = count(x.begin(), x.end(), '1');  // 数出该字符串中字符 '1' 的个数
            mask |= 1 << cnt;  // 把对应的计数位置为 1
        }  // 统计结束
        for (int i = 0;; ++i) {  // 从 0 开始找第一个没被占用的 1 的个数 i
            if (mask >> i & 1 ^ 1) {  // 取出第 i 位再与 1 异或：该位为 0 时条件成立，说明没有串只含 i 个 1
                return string(i, '1') + string(nums.size() - i, '0');  // 构造 i 个 '1' 加 n-i 个 '0'，它不可能与任何给定串相同
            }  // 条件成立后已返回
        }  // 循环结束
    }  // 方法结束
};  // 类定义结束