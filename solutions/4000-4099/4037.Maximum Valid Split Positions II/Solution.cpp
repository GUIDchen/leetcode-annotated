// 题目：4037. 最多有效分割位置 II / Maximum Valid Split Positions II
// 核心思路：先算不删除时的答案，再用正序与倒序前缀 gcd 的变化位置筛出真正值得尝试的删除下标，从而避开全部下标的 O(n^2) 重算
// 复杂度：时间复杂度 O(n^2 log V)（候选下标大幅减少），空间复杂度 O(n)
class Solution {  // 定义 LeetCode 题解类
public:  // 公有接口
    int maxValidSplits(vector<int>& nums) {  // 最多允许删除一个元素，返回能得到的最大有效分割位置个数
        int n = nums.size();  // 数组长度

        vector<bool> pos1 = mark(nums);  // 标记正序前缀 gcd 首次发生变化的位置

        vector<int> rev = nums;  // 复制一份数组用于倒序
        reverse(rev.begin(), rev.end());  // 原地反转
        vector<bool> pos2 = mark(rev);  // 标记倒序前缀 gcd 变化位置，用来从另一侧筛选关键删除点

        int ans = calc(nums);  // 基准答案：不删除任何元素时的有效分割数

        for (int i = 0; i < n; ++i) {  // 枚举要删除的下标 i
            if (pos1[i] || pos2[n - 1 - i]) {  // 只有确实会让某一侧前缀 gcd 改变的删除点才可能提升答案
                vector<int> arr;  // 保存删除后的数组
                arr.reserve(n - 1);  // 预留容量

                for (int j = 0; j < n; ++j) {  // 按原顺序拷贝除 i 以外的元素
                    if (i != j) {  // 跳过被删除的下标
                        arr.push_back(nums[j]);  // 保留该元素
                    }  // 结束跳过判断
                }  // 结束拷贝循环

                ans = max(ans, calc(arr));  // 用该删除方案的有效分割数更新答案
            }  // 结束候选点判断
        }  // 结束删除下标枚举

        return ans;  // 返回最大有效分割位置个数
    }  // 结束方法

private:  // 私有辅助函数
    vector<bool> mark(const vector<int>& nums) {  // 标记前缀 gcd 首次发生变化的位置
        int n = nums.size();  // 数组长度
        vector<bool> pos(n);  // pos[i] 为真表示删掉 nums[i] 会改变前缀 gcd

        pos[0] = true;  // 首个元素必然参与前缀 gcd
        int g = nums[0];  // 当前前缀 gcd

        for (int i = 1; i < n; ++i) {  // 依次向前扩展前缀
            int ng = gcd(g, nums[i]);  // 加入 nums[i] 之后的新前缀 gcd
            pos[i] = ng != g;  // gcd 变小说明 nums[i] 起了作用，是关键位置
            g = ng;  // 更新前缀 gcd
        }  // 结束前缀遍历

        return pos;  // 返回标记数组
    }  // 结束 mark 函数

    int calc(const vector<int>& arr) {  // 统计 arr 中满足前缀 gcd 等于后缀 gcd 的分割位置个数
        int n = arr.size();  // 数组长度
        vector<int> pre(n), suf(n);  // 前缀 gcd 与后缀 gcd 数组

        pre[0] = arr[0];  // 前缀 gcd 首项
        for (int i = 1; i < n; ++i) {  // 从左到右递推前缀 gcd
            pre[i] = gcd(pre[i - 1], arr[i]);  // 前缀 gcd 等于前一项与当前元素求 gcd
        }  // 结束前缀 gcd 计算

        suf[n - 1] = arr[n - 1];  // 后缀 gcd 首项（最右元素）
        for (int i = n - 2; i >= 0; --i) {  // 从右到左递推后缀 gcd
            suf[i] = gcd(suf[i + 1], arr[i]);  // 后缀 gcd 等于后一项与当前元素求 gcd
        }  // 结束后缀 gcd 计算

        int ans = 0;  // 有效分割位置计数
        for (int i = 0; i + 1 < n; ++i) {  // 枚举分割点 i，左段 [0, i]，右段 [i+1, n-1]
            if (pre[i] == suf[i + 1]) {  // 左右两段 gcd 相等则为有效分割
                ++ans;  // 计数加一
            }  // 结束有效判定
        }  // 结束分割点枚举

        return ans;  // 返回有效分割位置个数
    }  // 结束 calc 函数
};  // 结束类定义
