// 题目：1590. 使数组和能被 P 整除（Make Sum Divisible by P）
// 思路：要让总和余数 k 变成 0，需删掉一段和模 p 恰为 k 的子数组；用哈希表记录前缀余数最近出现的下标求最短长度。
// 时间复杂度：O(n)，一次遍历加哈希查询；空间复杂度：O(n)，哈希表最多保存 n 个余数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minSubarray(vector<int>& nums, int p) {  // nums：数组；p：模数
        int k = 0;  // k 保存整个数组之和对 p 的余数，也就是需要被删掉的那部分
        for (int& x : nums) {  // 逐元素累加取模
            k = (k + x) % p;  // 每加一次就取模，防止累加溢出
        }
        if (k == 0) {  // 总和本来就能整除 p
            return 0;  // 不需要删除任何元素
        }
        unordered_map<int, int> last;  // 记录某个前缀和对 p 的余数最近一次出现的下标
        last[0] = -1;  // 空前缀的余数为 0，下标记 -1，方便计算子数组长度
        int n = nums.size();  // 数组长度
        int ans = n;  // 答案初值取 n，等价于“暂时还没找到合法子数组”
        int cur = 0;  // 当前前缀和对 p 的余数
        for (int i = 0; i < n; ++i) {  // 从左到右维护前缀和
            cur = (cur + nums[i]) % p;  // 加入当前元素后的前缀和余数
            int target = (cur - k + p) % p;  // 要删掉的那段子数组的余数：删掉后整体余数才归零
            if (last.count(target)) {  // 该余数之前出现过，说明中间那段的和模 p 恰为 k
                ans = min(ans, i - last[target]);  // 用更短的长度更新答案
            }
            last[cur] = i;  // 记录当前余数的最新下标（越靠右对后续越有利）
        }
        return ans == n ? -1 : ans;  // 长度仍为 n 说明删不出合法子数组，返回 -1
    }
};