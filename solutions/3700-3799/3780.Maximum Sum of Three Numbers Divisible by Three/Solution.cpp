// 题目：3780. 能被 3 整除的三元组最大和（Maximum Sum of Three Numbers Divisible by Three）
// 核心思路：先排序，再按模 3 的余数分成三个桶；枚举前两个数的余数 a、b，第三个余数由 (a+b+c)%3==0 唯一确定，取三个桶当前最大值求和，凑不出时返回 0。
// 复杂度：时间 O(n log n)（排序主导，枚举只有 3×3 种组合）；空间 O(n)，用于三个余数桶。
class Solution {  // LeetCode 约定的题解类
public:  // public 区的方法供判题器调用
    int maximumSum(vector<int>& nums) {  // 从 nums 中选恰好三个数使其和能被 3 整除，返回最大可能的和
        sort(nums.begin(), nums.end());  // 升序排序，这样每个余数桶的末尾就是该余数下最大的数
        vector<vector<int>> g(3);  // g[r] 存放所有模 3 余 r 的数，共三个桶
        for (int x : nums) {  // 遍历数组，把每个数按余数归类
            g[x % 3].push_back(x);  // 求出余数 x % 3 后放入对应桶
        }  // 分类结束
        int ans = 0;  // 答案初值 0：题目规定凑不出三元组时返回 0
        for (int a = 0; a < 3; a++) {  // 枚举第一个数的余数 a
            if (!g[a].empty()) {  // 第一个桶非空才可能取到第一个数
                int x = g[a].back();  // 取出 a 类里最大的数 x
                g[a].pop_back();  // 先弹出 x，保证三个数取自三个不同下标
                for (int b = 0; b < 3; b++) {  // 枚举第二个数的余数 b
                    if (!g[b].empty()) {  // 第二个桶也必须非空
                        int y = g[b].back();  // 取出 b 类里当前最大的数 y
                        g[b].pop_back();  // 同样先弹出 y，避免下标复用
                        int c = (3 - (a + b) % 3) % 3;  // 由 (a + b + c) % 3 == 0 反解出第三个余数 c
                        if (!g[c].empty()) {  // 第三个桶非空才能凑成完整三元组
                            int z = g[c].back();  // 取 c 类最大值 z（只读不弹出，稍后无需回滚）
                            ans = max(ans, x + y + z);  // 三者之和与当前答案取较大值
                        }  // 第三个桶的判断结束
                        g[b].push_back(y);  // 回滚：把 y 放回 b 桶，供后续组合继续使用
                    }  // 第二个桶的判断结束
                }  // 第二个数余数的枚举结束
                g[a].push_back(x);  // 回滚：把 x 放回 a 桶
            }  // 第一个桶的判断结束
        }  // 第一个数余数的枚举结束
        return ans;  // 返回最大和
    }  // 方法结束
};  // 类定义结束
