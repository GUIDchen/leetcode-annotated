// 3854. 使数组奇偶交替的最少操作 / Minimum Operations to Make Array Parity Alternating（中等）
// 核心思路：奇偶交替只有两种目标模式，即 (nums[i] - i) 的奇偶全部相同；分别枚举两种模式，不匹配的位置必须加减 1（翻转奇偶），若它恰是全局最值就向区间内部调整以免扩大极差，最后按 [操作数, 极差] 字典序取较小者。
// 复杂度：时间 O(n)，空间 O(1)。
class Solution {  // 设计一个算法：用最少操作让数组奇偶交替，并让极差最小
public:  // 对外接口区
    vector<int> makeParityAlternating(vector<int>& nums) {  // 返回 [最少操作数, 该操作数下能达到的最小极差]
        if (nums.size() == 1) {  // 单元素数组天然满足交替
            return {0, 0};  // 无需操作，极差为 0
        }  // 特判分支结束

        auto [mnIt, mxIt] = minmax_element(nums.begin(), nums.end());  // 一次扫描同时拿到最小值与最大值的迭代器
        int mn = *mnIt;  // 数组最小值
        int mx = *mxIt;  // 数组最大值

        auto f = [&](int k) {  // 目标模式 k：要求 (nums[i] - i) 的奇偶恒等于 k
            int cnt = 0;  // 需要的操作次数
            int a = INT_MAX;  // 调整后的最小值
            int b = INT_MIN;  // 调整后的最大值

            for (int i = 0; i < nums.size(); i++) {  // 按下标遍历数组
                int x = nums[i];  // 取出当前元素，必要时就地调整
                if (((x - i) & 1) != k) {  // 奇偶不符合目标模式，必须加减 1 翻转一次
                    cnt++;  // 操作数加一
                    if (x == mn) {  // 若它恰是全局最小值，加 1 后不会把下界变得更低
                        ++x;  // 最小值加一，既翻转奇偶又把极差压到最小
                    } else if (x == mx) {  // 若它恰是全局最大值，减 1 后不会把上界抬得更高
                        --x;  // 最大值减一，既翻转奇偶又把极差压到最小
                    }  // 最值调整分支结束
                }  // 不匹配分支结束
                a = min(a, x);  // 维护调整后的最小值
                b = max(b, x);  // 维护调整后的最大值
            }  // 遍历结束
            return vector<int>{cnt, max(1, b - a)};  // 长度 ≥ 2 的交替数组不可能所有元素相等，故极差至少为 1
        };  // lambda 定义结束

        vector<int> r0 = f(0);  // 方案一：i 与 nums[i] 同奇偶（从偶数开头）
        vector<int> r1 = f(1);  // 方案二：i 与 nums[i] 奇偶相反（从奇数开头）

        return r0 < r1 ? r0 : r1;  // 先比操作数、再比极差，取字典序更小的方案
    }  // 方法结束
};  // 类结束
