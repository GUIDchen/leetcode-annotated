// 题目：2910. 合法分组的最少组数（Minimum Number of Groups to Create a Valid Assignment）
// 核心思路：设每组大小为 k 或 k+1，逐种数值把频次 v 拆成若干组；k 的上界是最小频次，从大到小枚举，第一个能让所有频次都合法拆分的 k 对应最少组数。
// 时间复杂度：O(n * 最小频次 / k)，即调和级数的量级，枚举 k 与频次；空间复杂度：O(n)，计数哈希表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minGroupsForValidAssignment(vector<int>& nums) {  // nums 是输入数组，返回合法分组的最少组数
        unordered_map<int, int> cnt;  // 统计每种数值出现的次数
        for (int x : nums) {  // 遍历每个元素做计数
            cnt[x]++;  // 对应数值的频次加一
        }  // 计数结束
        int k = 1e9;  // k 表示较小的组大小，先给一个足够大的初值
        for (auto& [_, v] : cnt) {  // 结构化解包：_ 是数值（这里用不到），v 是该数值的频次
            k = min(k, v);  // 组大小不可能超过最小频次，因此上界取最小频次
        }  // 求出 k 的上界
        for (;; --k) {  // 从大到小枚举 k，第一个可行的 k 得到的组数最少
            int ans = 0;  // ans 记录当前 k 下的总组数；保持 0 也表示该 k 不可行
            for (auto& [_, v] : cnt) {  // 检查每种数值的频次 v 能否拆成若干个 k 与 k+1
                if (v / k < v % k) {  // 商小于余数说明剩下的元素凑不满一组 k，此 k 不可行
                    ans = 0;  // 标记当前 k 不可行
                    break;  // 直接放弃这个 k
                }  // if 结束
                ans += (v + k) / (k + 1);  // 频次 v 最少需要 ceil(v/(k+1)) 组，(v+k)/(k+1) 是它的整数写法
            }  // 频次检查结束
            if (ans) {  // 非 0 表示所有频次都能合法分组
                return ans;  // k 递减枚举，因此这个 ans 就是最少组数
            }  // if 结束
        }  // 枚举 k 结束（一定会命中，无需兜底返回）
    }  // 方法结束
};  // 类定义结束