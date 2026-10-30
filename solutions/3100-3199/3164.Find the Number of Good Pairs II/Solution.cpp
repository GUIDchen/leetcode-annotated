// 题目：3164. 优质数对的总数 II（Find the Number of Good Pairs II）
// 思路：枚举数对会 O(n·m) 超时，改为「枚举倍数」：先把 nums1 中 k 的倍数除以 k 计数，再按 nums2 的每个取值 x 枚举其倍数累加配对数量。
// 时间复杂度：O(n + m + mx·log mx)，mx 为 x/k 的最大值；空间复杂度：O(n + m)，两张哈希表的规模。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k) {  // 返回优质数对个数，数量可能超过 int，所以用 long long
        unordered_map<int, int> cnt1;  // cnt1：统计 nums1 中「是 k 的倍数」的元素除以 k 之后的出现次数
        for (int x : nums1) {  // 遍历 nums1 的每个元素
            if (x % k == 0) {  // 只有 k 的倍数才可能被 y * k 整除，其余直接丢弃
                cnt1[x / k]++;  // 归一化到 x / k，后面才能用「x 的倍数」来找配对
            }  // if 判断结束
        }  // 遍历 nums1 结束
        if (cnt1.empty()) {  // nums1 里没有任何可用元素，答案必然为 0
            return 0;  // 提前返回，省掉后面的建表与枚举
        }  // 提前返回分支结束
        unordered_map<int, int> cnt2;  // cnt2：统计 nums2 中每个取值的出现次数
        for (int x : nums2) {  // 遍历 nums2 的每个元素
            ++cnt2[x];  // 相同取值合并计数，稍后整批相乘
        }  // 遍历 nums2 结束
        int mx = 0;  // mx 记录 cnt1 中最大的归一化值，作为倍数枚举的上界
        for (auto& [x, _] : cnt1) {  // 结构化绑定遍历哈希表，第二项是计数（用 _ 占位表示不关心）
            mx = max(mx, x);  // 更新最大取值
        }  // 求上界的循环结束
        long long ans = 0;  // 答案累加器
        for (auto& [x, v] : cnt2) {  // 按 nums2 的不同取值 x 分组处理，同值元素的配对情况完全相同
            long long s = 0;  // s 记录与当前取值 x 配对的 nums1 元素个数
            for (int y = x; y <= mx; y += x) {  // 枚举 x 的所有倍数 y（y 就是 nums1 元素除以 k 之后可能的值）
                s += cnt1[y];  // 加上该倍数在 nums1 中出现的次数
            }  // 倍数枚举结束
            ans += s * v;  // 再乘以 x 在 nums2 中出现的次数，整批计入答案
        }  // 按取值分组的循环结束
        return ans;  // 返回优质数对总数
    }  // 方法结束
};  // 类定义结束