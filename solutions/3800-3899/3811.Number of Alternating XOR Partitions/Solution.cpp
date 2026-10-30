// 3811. Number of Alternating XOR Partitions | 交替按位异或分割的数目
// 核心思路：用前缀异或做状态压缩 DP，cnt1/cnt2 分别累计“最后一段异或为 target1/target2”的方案数并以前缀异或值为键；当前前缀的方案数 = 从 cnt2 接上 target1 的方案 + 从 cnt1 接上 target2 的方案。
// 复杂度：时间 O(n)（一次遍历 + 哈希查询）；空间 O(n)（哈希表最多 n 个键）。
class Solution {  // 定义题解类
public:  // 公有接口
    int alternatingXOR(vector<int>& nums, int target1, int target2) {  // 返回把 nums 划分成若干段、使各段异或值交替等于 target1、target2 的方案数
        const int MOD = 1e9 + 7;  // 取模常量 1e9+7
        unordered_map<int, int> cnt1, cnt2;  // cnt1/cnt2：按前缀异或值累计“最后一段是 target1/target2”的方案数
        cnt2[0] = 1;  // 空前缀视为“最后一段以 target2 结尾”的合法初态，保证第一段可以是 target1

        int pre = 0, ans = 0;  // pre 为当前前缀异或，ans 为当前前缀的划分数
        for (int x : nums) {  // 逐个元素推进前缀异或
            pre ^= x;  // 把当前元素累加进前缀异或
            int a = cnt2[pre ^ target1];  // 上一段是 target2、且当前段异或为 target1 的方案数（pre ^ target1 就是上一个前缀异或）
            int b = cnt1[pre ^ target2];  // 上一段是 target1、且当前段异或为 target2 的方案数
            ans = (a + b) % MOD;  // 当前前缀的方案数 = 这两种交替衔接方式之和
            cnt1[pre] = (cnt1[pre] + a) % MOD;  // 把“以 target1 结尾”的方案累加到前缀异或 pre 的计数上
            cnt2[pre] = (cnt2[pre] + b) % MOD;  // 把“以 target2 结尾”的方案累加到前缀异或 pre 的计数上
        }  // 遍历结束

        return ans;  // 返回整个数组的划分数
    }  // 方法结束
};  // 类定义结束
