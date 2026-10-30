// 题目：3318. 计算子数组的 x-sum I（Find X-Sum of All K-Long Subarrays I）
// 核心思路：长度为 k 的滑动窗口 + 两个有序集合（按 (出现次数, 数值) 排序）：l 保存前 x 大的元素并维护它们的「次数×数值」之和 s，r 是备选；每一步先加入新元素、调整 l 的规模、记录答案，再移除左端旧元素。
// 时间复杂度：O(n·x·log n)；空间复杂度：O(n)，用于答案数组与频次表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findXSum(vector<int>& nums, int k, int x) {  // nums：原数组；k：窗口长度；x：取出现次数最多的前 x 种元素
        using pii = pair<int, int>;  // 排序键用 (出现次数, 数值)，次数相同时数值大的排更前
        set<pii> l, r;  // l：前 x 大的元素；r：其余元素，均按 (次数, 值) 升序排列
        int s = 0;  // s 就是当前窗口的 x-sum（l 中所有元素的 次数×值 之和）
        unordered_map<int, int> cnt;  // cnt[v]：值 v 在当前窗口内的出现次数
        auto add = [&](int v) {  // 把值 v 按当前出现次数插入合适的集合
            if (cnt[v] == 0) {  // 出现 0 次的值不该出现在任何集合里
                return;  // 直接返回
            }  // if 结束
            pii p = {cnt[v], v};  // 用当前次数和数值组成排序键
            if (!l.empty() && p > *l.begin()) {  // 比 l 的最小元素还大，说明它应当排进前 x 名
                s += p.first * p.second;  // 计入 x-sum
                l.insert(p);  // 放进 l
            } else {  // 否则只能先待在备选区
                r.insert(p);  // 放进 r
            }  // else 结束
        };  // lambda add 结束
        auto remove = [&](int v) {  // 把值 v 从它当前所在的集合里移走
            if (cnt[v] == 0) {  // 没出现过就没什么可删
                return;  // 直接返回
            }  // if 结束
            pii p = {cnt[v], v};  // 用当前次数和数值组成排序键
            auto it = l.find(p);  // 先看它是否在 l 中
            if (it != l.end()) {  // 在 l 里
                s -= p.first * p.second;  // 从 x-sum 中扣除它的贡献
                l.erase(it);  // 从 l 中删除
            } else {  // 否则它在 r 里
                r.erase(p);  // 从 r 中删除
            }  // else 结束
        };  // lambda remove 结束
        vector<int> ans;  // 依次保存每个窗口的 x-sum
        for (int i = 0; i < nums.size(); ++i) {  // 右指针 i 从左往右扫描
            remove(nums[i]);  // 先按旧次数把该值从集合中摘下
            ++cnt[nums[i]];  // 出现次数加一
            add(nums[i]);  // 再按新次数插回集合

            int j = i - k + 1;  // 窗口左端点 j = i-k+1
            if (j < 0) {  // 窗口还没凑满 k 个元素
                continue;  // 不产生答案，直接进入下一轮
            }  // if 结束

            while (!r.empty() && l.size() < x) {  // 前 x 名数量不足时从备选区补
                pii p = *r.rbegin();  // 取 r 中最大的元素
                s += p.first * p.second;  // 计入 x-sum
                r.erase(p);  // 从 r 中移除
                l.insert(p);  // 加入 l
            }  // while 结束
            while (l.size() > x) {  // 前 x 名个数超出 x
                pii p = *l.begin();  // 取 l 中最小的元素
                s -= p.first * p.second;  // 从 x-sum 中扣除
                l.erase(p);  // 从 l 中移除
                r.insert(p);  // 退回备选区 r
            }  // while 结束
            ans.push_back(s);  // 记录窗口 [i-k+1, i] 的 x-sum

            remove(nums[j]);  // 把即将移出窗口的左端值摘下
            --cnt[nums[j]];  // 出现次数减一
            add(nums[j]);  // 按新次数重新插回集合
        }  // for 结束
        return ans;  // 返回所有长度为 k 的窗口的 x-sum
    }  // 方法结束
};  // 类定义结束
