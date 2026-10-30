// 题目：4035. 最多有效分割位置 I / Maximum Valid Split Positions I
// 核心思路：暴力枚举被删除的下标（含不删除），对得到的每个数组用前缀 gcd 与后缀 gcd 比对来统计有效分割位置
// 复杂度：时间复杂度 O(n^2 log V)，空间复杂度 O(n)
class Solution {  // 定义 LeetCode 题解类
public:  // 公有接口
    int maxValidSplits(vector<int>& nums) {  // 允许删除至多一个元素，返回能得到的最大有效分割位置个数
        int n = nums.size();  // 数组长度
        int ans = 0;  // 答案：最大有效分割位置个数
        for (int del = -1; del < n; ++del) {  // 枚举被删除的下标，del == -1 表示不删除任何元素
            vector<int> arr;  // 保存删除后的数组
            arr.reserve(n);  // 预留容量，避免反复扩容
            for (int i = 0; i < n; ++i) {  // 按原顺序拷贝不被删除的元素
                if (i != del) {  // 跳过被删除的那个下标
                    arr.push_back(nums[i]);  // 保留该元素
                }  // 结束跳过判断
            }  // 结束拷贝循环
            ans = max(ans, calc(arr));  // 用该删除方案的有效分割数更新答案
        }  // 结束删除下标枚举
        return ans;  // 返回最大有效分割位置个数
    }  // 结束方法

private:  // 私有辅助函数
    int calc(const vector<int>& arr) {  // 统计数组 arr 中满足前缀 gcd 等于后缀 gcd 的分割位置个数
        int m = arr.size();  // 当前数组长度
        vector<int> pre(m), suf(m);  // pre[i] 为前 i+1 个元素的前缀 gcd，suf[i] 为从 i 开始的后缀 gcd
        pre[0] = arr[0];  // 前缀 gcd 的首项
        for (int i = 1; i < m; ++i) {  // 从左到右递推前缀 gcd
            pre[i] = gcd(pre[i - 1], arr[i]);  // 前缀 gcd 等于前一项与当前元素求 gcd
        }  // 结束前缀 gcd 计算
        suf[m - 1] = arr[m - 1];  // 后缀 gcd 的首项（最右元素）
        for (int i = m - 2; i >= 0; --i) {  // 从右到左递推后缀 gcd
            suf[i] = gcd(suf[i + 1], arr[i]);  // 后缀 gcd 等于后一项与当前元素求 gcd
        }  // 结束后缀 gcd 计算
        int ans = 0;  // 有效分割位置计数
        for (int i = 0; i < m - 1; ++i) {  // 枚举分割点：左段为 [0, i]，右段为 [i+1, m-1]
            if (pre[i] == suf[i + 1]) {  // 两段 gcd 相等说明该处是有效分割
                ++ans;  // 计数加一
            }  // 结束有效判定
        }  // 结束分割点枚举
        return ans;  // 返回有效分割位置个数
    }  // 结束辅助函数
};  // 结束类定义
